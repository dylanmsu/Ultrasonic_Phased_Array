/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include <unistd.h>
#include "axi_delay_generator.h"
#include "xil_io.h"
#include "xgpio.h"
#include <math.h>

// math constants
#define PI 				3.1415926		//PI

// parameters defined in fpga fabric
#define FREQ			40000			//carrier frequency for the transducers
#define RESOLUTION 		128				//resolution in mm in which the phases can be adjusted.

// array pcb parameters
#define WIDTH 			5				//number of transducers in the x direction
#define HEIGTH 			5				//number of transducers in the y direction
#define DISTANCE		10.0			//distance between the transducers

// environment parameters
#define TEMPERATURE 	20.0			//ambient temperature used to calculate wavelength

// accoustic lefitation example
#define MOVEMENT_RES	10				//movement resolution in steps/mm
#define ARRAY_DISTANCE	70				//distance between the top and bottom array

// calculate wavelength in air based on temperature and frequency
double wavelength = (331000*sqrt(1 + TEMPERATURE/273.0))/FREQ; //in mm

XGpio gpio_0;

int phases[1][WIDTH][HEIGTH] = {0};

int offsets[2][5][5] = {
		{{128-28, 128-105,  128-44,  128-108,  128-36},
		{128-44,  128-105,  128-46, 128-38, 128-100},
		{128-38, 128-38,  128-38,  128-41, 128-110},
		{128-44, 128-113,  128-113, 128-97, 128-38},
		{128-30,  128-51, 128-38,  128-49,  128-110}},//*/

		{{128-113, 128-41,  128-92,  128-23,  128-105},
		{128-46,  128-97,  128-110, 128-110, 128-41},
		{128-113, 128-92,  128-46,  128-113, 128-36},
		{128-102, 128-33,  128-110, 128-113, 128-97},
		{128-41,  128-108, 128-44,  128-51,  128-100}}//*/
};

int reg_addresses[25] = {
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG0_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG1_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG2_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG3_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG4_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG5_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG6_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG7_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG8_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG9_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG10_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG11_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG12_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG13_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG14_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG15_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG16_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG17_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG18_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG19_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG20_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG21_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG22_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG23_OFFSET,
		AXI_DELAY_GENERATOR_S00_AXI_SLV_REG24_OFFSET
};

int ip_base_addresses[2] = {
		XPAR_GENERATOR_1_AXI_DELAY_GENERATOR_1_S00_AXI_BASEADDR,
		XPAR_GENERATOR_2_AXI_DELAY_GENERATOR_1_S00_AXI_BASEADDR
};

void write_phase(int idx, int x, int y, uint8_t phase) {
	int i = (x)*5 + (4-y);
	AXI_DELAY_GENERATOR_mWriteReg(ip_base_addresses[idx], reg_addresses[i], phase%RESOLUTION);
}

void writePhases() {
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGTH; j++) {
			for (int k=0; k<2; k++) {
				write_phase(k, i, j, phases[k][i][j] + offsets[k][4-i][4-j]);
			}
		}
	}
}

void setFocusPoint(int idx, double x, double y, double z) {
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGTH; j++) {
			double phase = sqrt((i*DISTANCE-x)*(i*DISTANCE-x) + (y)*(y) + (j*DISTANCE-z)*(j*DISTANCE-z));
			phases[idx][i][j] = round((RESOLUTION - 1) - fmod(phase*(RESOLUTION/wavelength), RESOLUTION));
			//phases[idx][i][j] += offsets[idx][4-i][4-j];
		}
	}
}

void levitate(double x, double y, double z) {
	setFocusPoint(0, x + 20, y + ARRAY_DISTANCE/2, z + 20);
	setFocusPoint(1, 4*DISTANCE - (x + 20), ARRAY_DISTANCE - (y + ARRAY_DISTANCE/2), z + 20);
}

int main()
{
	init_platform();

	int status;

	status = XGpio_Initialize(&gpio_0, XPAR_AXI_GPIO_0_DEVICE_ID);
	if (status != XST_SUCCESS) {
		print("paripheral GPIO 0 fail\r\n");
	} else {
		print("paripheral GPIO 0 success\r\n");
	}

	setFocusPoint(1, 20, 35, 20);
	setFocusPoint(0, 20, 35, 20);
	writePhases();

	/*for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGTH; j++) {
			for (int k=0; k<2; k++) {
				write_phase(k, i, j, offsets[k][4-i][4-j]);
			}
		}
	}*/


	/*for (int i=0; i<25; i++) {
		AXI_DELAY_GENERATOR_mWriteReg(ip_base_addresses[0], reg_addresses[i], i*4);
	}*/

	XGpio_SetDataDirection(&gpio_0, 1, 1);
	XGpio_DiscreteWrite(&gpio_0, 1, 1);

	while (1) {
		XGpio_DiscreteWrite(&gpio_0, 1, 0);
		usleep(10000);
		XGpio_DiscreteWrite(&gpio_0, 1, 1);
		usleep(10000);
	}

    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}
