#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include <unistd.h>
#include "xgpio.h"
#include <math.h>
#include "animation.h"

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

// gpio's for the columns
XGpio gpio[2][WIDTH];

// other peripherals
XGpio gpio_0;
XGpio gpio_1;

int phases[2][WIDTH][HEIGTH] = {0};

/*
 * these values are measured in real life and
 * correspond to the phase delay offsets from
 * the individual transmitters.
 * formula: 128 - (measured_delay_us/25us) * 128
 */
int offsets[2][WIDTH][HEIGTH] = {
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

// rows for the delay generators (FPGA fabric)
int devIds[2][WIDTH] = {
		{XPAR_HIER_0_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_1_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_2_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_3_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_4_AXI_GPIO_0_DEVICE_ID},
		{XPAR_HIER_5_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_6_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_7_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_8_AXI_GPIO_0_DEVICE_ID,
		XPAR_HIER_9_AXI_GPIO_0_DEVICE_ID}
};

// store previous location
double current_x = 0;
double current_y = 0;
double current_z = 0;

// initialize the gpio's
void driverInit() {
	int status;
	for (int i=0; i<WIDTH; i++) {
		status = XGpio_Initialize(&gpio[0][i], devIds[0][i]);
		if (status != XST_SUCCESS) {
			print("GPIO array 0 fail\r\n");
		} else {
			print("GPIO array 0 success\r\n");
		}
	}
	for (int i=0; i<WIDTH; i++) {
		status = XGpio_Initialize(&gpio[1][i], devIds[1][i]);
		if (status != XST_SUCCESS) {
			print("GPIO array 1 fail\r\n");
		} else {
			print("GPIO array 1 success\r\n");
		}
	}

	status = XGpio_Initialize(&gpio_0, XPAR_AXI_GPIO_0_DEVICE_ID);
	if (status != XST_SUCCESS) {
		print("paripheral GPIO 0 fail\r\n");
	} else {
		print("paripheral GPIO 0 success\r\n");
	}

	status = XGpio_Initialize(&gpio_1, XPAR_AXI_GPIO_1_DEVICE_ID);
	if (status != XST_SUCCESS) {
		print("paripheral GPIO 1 fail\r\n");
	} else {
		print("paripheral GPIO 1 success\r\n");
	}
}

void configureGpio() {
	// set all delay driver gpio's to outputs
	for (int i=0; i<WIDTH; i++) {
		XGpio_SetDataDirection(&gpio[0][i], 1, 0);
		XGpio_SetDataDirection(&gpio[0][i], 2, 0);
	}
	for (int i=0; i<WIDTH; i++) {
		XGpio_SetDataDirection(&gpio[1][i], 1, 0);
		XGpio_SetDataDirection(&gpio[1][i], 2, 0);
	}

	XGpio_SetDataDirection(&gpio_0, 1, 0);
	XGpio_SetDataDirection(&gpio_0, 2, 1);

	XGpio_SetDataDirection(&gpio_1, 1, 1);
	XGpio_SetDataDirection(&gpio_1, 2, 0);

	XGpio_DiscreteWrite(&gpio_1, 2, 1);
}

void writePhases() {
	for (int i=0; i<WIDTH; i++) {
		XGpio_DiscreteWrite(&gpio[0][i], 1, (phases[0][i][0]%RESOLUTION) | (phases[0][i][1]%RESOLUTION) << 8 | (phases[0][i][2]%RESOLUTION) << 16 | (phases[0][i][3]%RESOLUTION) << 24);
		XGpio_DiscreteWrite(&gpio[0][i], 2, (phases[0][i][4]%RESOLUTION));
	}
	for (int i=0; i<WIDTH; i++) {
		XGpio_DiscreteWrite(&gpio[1][i], 1, (phases[1][i][0]%RESOLUTION) | (phases[1][i][1]%RESOLUTION) << 8 | (phases[1][i][2]%RESOLUTION) << 16 | (phases[1][i][3]%RESOLUTION) << 24);
		XGpio_DiscreteWrite(&gpio[1][i], 2, (phases[1][i][4]%RESOLUTION));
	}
}

void writeOffsets() {
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGTH; j++) {
			for (int k=0; k<2; k++) {
				phases[k][i][j] = offsets[k][i][j];
			}
		}
	}
}

/*
 * focus the waves to a point given by the x, y and z coordinates
 * referenced to the center of the first transducer (0, 0)
 */
void setFocusPoint(int idx, double x, double y, double z) {
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGTH; j++) {
			//sqrt(x*x+y*y+z*z)
			double phase = sqrt((i*DISTANCE-x)*(i*DISTANCE-x) + (y)*(y) + (j*DISTANCE-z)*(j*DISTANCE-z));
			phases[idx][i][j] = round((RESOLUTION - 1) - fmod(phase*(RESOLUTION/wavelength), RESOLUTION));
			phases[idx][i][j] += offsets[idx][i][j];
		}
	}
}


/*
 * steer a beam with angele x and y in radians relative to the normal vector of the array
 */
void setBeamDirection(int idx, double theta_x, double theta_y) {
	for (int i=0; i<WIDTH; i++) {
		for (int j=0; j<HEIGTH; j++) {
			double a = -tan(theta_y);
			double b = -tan(theta_x);
			double phase = (a*i*DISTANCE + b*j*DISTANCE) / sqrt(1+a*a+b*b);
			phases[idx][i][j] = round((RESOLUTION - 1) - fmod(phase*(RESOLUTION/wavelength), RESOLUTION));
			phases[idx][i][j] += offsets[idx][i][j];
		}
	}
}

/*
 * if there are thwo arrays faced to eachother with a given distance between them, 
 * this method will make both arrays focus a point in 3d space
 */
void levitate(double x, double y, double z) {
	setFocusPoint(0, x + 20, y + ARRAY_DISTANCE/2, z + 20);
	setFocusPoint(1, 4*DISTANCE - (x + 20), ARRAY_DISTANCE - (y + ARRAY_DISTANCE/2), z + 20);
}


/*
 * next methods are used for levitation
 */
void setPosition(double x, double y, double z) {
	current_x = x;
	current_y = y;
	current_z = z;
	levitate(current_x, current_y, current_z);
	writePhases();
}

void moveTo(double x, double y, double z, double speed) {
	double dx = x - current_x;
	double dy = y - current_y;
	double dz = z - current_z;
	double distance = sqrt(dx*dx + dy*dy + dz*dz);
	double normal_dx = dx / distance;
	double normal_dy = dy / distance;
	double normal_dz = dz / distance;
	for (double i=0; i<floor(MOVEMENT_RES*distance); i+=1) {
		double f = ((double)i / (double)MOVEMENT_RES);
		double itr_x = ((double)normal_dx) * f;;p
		double itr_y = ((double)normal_dy) * f;
		double itr_z = ((double)normal_dz) * f;
		levitate(current_x + itr_x, current_y + itr_y, current_z + itr_z);
		writePhases();
		usleep((1000000.0 / ((double)MOVEMENT_RES))/((double)speed));
	}
	setPosition(x, y, z);
	writePhases();
}

int main() {
    init_platform();
    driverInit();
    configureGpio();

	while (1) {
		int bt = XGpio_DiscreteRead(&gpio_1, 1);
		int sw = XGpio_DiscreteRead(&gpio_0, 2);
		XGpio_DiscreteWrite(&gpio_0, 1, sw);
		XGpio_DiscreteWrite(&gpio_1, 2, 1);

		int bt1 = (bt & 0b0001) >> 0;
		int bt2 = (bt & 0b0010) >> 1;
		int bt3 = (bt & 0b0100) >> 2;
		int bt4 = (bt & 0b1000) >> 3;

		setPosition(0, 0, 0);

		// wait until button press
		XGpio_DiscreteWrite(&gpio_0, 1, 1);
		while (!XGpio_DiscreteRead(&gpio_1, 1)) {
			usleep(10000);
		}
		XGpio_DiscreteWrite(&gpio_0, 1, 0);

		for (int i=0; i<198; i++) {
			moveTo(knot_animation[i][0]*3, knot_animation[i][2]*3, knot_animation[i][1]*3, 30);
		}
		moveTo(0, 0, 0, 100);
	}

    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}
