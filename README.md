# Ultrasonic_Phased_Array
This repository is under construction and will contain all the sources for a working ultrasonic phased array.
The vitis project in this repository is to be used in a accoustic levitation example.

## Working principle
Lets consider an example where we want to send a single pulse of airpressure to a certain point in space. We have an array of transducers we can work with. Since the waves travel in a sphere around the transducers, we can time the pulses at each transducer in such a way that all the wavefronts arrive at the same time in a single focal point. This is illustrated in the animation below.

[<img src="img/gifsmos_single_focus.gif" width="250px"/>]()

If we were to send a sinewave with the same delay through the transducers instead of a single pulse, all the peaks and troughs of those waves would ideally only add up in the focal point. The amplitude would then be the greatest at that point and ideally cancel out everywhere else. This is actually not always the case because a side effect of using a periodic signal is that we create te posibility of sidelobes. Sidelobes are areas where some of the sinewaves constructively add up unwantedly where the phase shift is a multiple of 360 degrees. To prevent the occurance of sidelobes, we need to space the transducers with a distance between 1/2 wavelength, and 1/4 wavelength. 


In the case for this project, the spacing between the sources is 10 mm wich is more than double the recommended wavelength so we expect some loss of energy through sidelobes. Even more so diagonally since the sources are placed in a rectangular grid and the diagonal spacing is 14.14 mm. Placing the sources in a hexagonal grid solves big diagonal spacing but this makes the design of the PCB more challanging. For this reason i opted to design a rectangular grid of sources anyway.

The waves exiting the transducers will look something like this.

[<img src="simulation/animation.gif" width="250px"/>]()

The red dots at the bottom are sources emitting pure sinusodial signals with an adjusted phase delay so all the waves are in phase at the red dot around the middle.

There is also an included python script called 'wave_equation.py' that focuses the waves to your mouse location by manipulating the phases of the emitters. It solves the 2d wave equation so it should be more acurate than the above animation.

## Setup
There are two array's used in the levitation example. One is facing upwards and the other is facing downwards. They are facing eachother with a distance of 70mm. This distance is arbitrarily chosen based on the needed volume for levitation.

## FPGA
The FPGA used in this project is the ZYNQ XC7Z020 on a Zybo Z7 board but any Zynq FPGA should work. The FPGA contains two distinct parts: The processing system (PS) and the programmable logic (PL):

### Programmable Logic
The PL contains an implementation which receives 7 bit values from the PS (Processing System) for every transducer. This value sets the phase of the output signal. This is acheived by making a fifo of length = 2^7 in the case of a phase resolution of 7 bits. The 40KHz signal is fed into the fifo at 40KHz * 2^7 = 5.12MHz. The reason for this is because we want exactly 1 full period of the signal in the fifo. The 7 bit value determines at which address of the fifo the output signal is tapped from. This way wan can adjust the phase of the output signal in 2^7 steps per period.


The block diagram that takes an AXI peripheral bus and outputs a serial data stream to drive the included transducer board is illustrated below. 

[<img src="Vivado\block_diagram\axi_phase_generator_to_Pmod.svg"/>]()

here is an overview of the in- and output signals:
- **signal_in**: this is the signal that will drive the transducers and whos phase will be altered, in our case this signal would have a 50% dutycycle at 40KHz.
- **fifo_clk**: this is the clock that shifts the fifo's used for the delay generation. This should be 2^7 times faster than the 40KHz signal. in this case the fifo length and so the phase resolution is 2^7. This means a frequency of 5.12MHz.
- **ser_clk**: this is the serial clock that drives the serializer and also the shift registers on the transducer board. This clock should be 5x the 'fifo_clock' if each shift register drives 5 transducers. This means a frequency of 25.6MHz.
- **s00_axi_aclk**: this is the AXI peripheral clock comming directly from the Processing system.
- **en**: enable the output signal.
- **resetn**: active low reset signal.
- **S00_AXI**: AXI slave port
- **pmod_out**: this port goes directly to a Pmod port on the FPGA-board and drives the transducer board.

The AXI peripheral IP_block generates the delayed signals and outputs them as a 25 bit vector. This vector is split into 5x 5 bit vectors that enter the seializer. The data is then clocked bit by bit to the output.

### Implementation
[<img src="Vivado\block_diagram\top_level_design.svg"/>]()

TODO

### Processing System
TODO

### Video
Below is a video showing two ultrasonic arrays levitating a piece of styrofoam in an preprogrammed path.
<a href="http://www.youtube.com/watch?feature=player_embedded&v=-Alf5AHHJVo" target="_blank">
 <img src="http://img.youtube.com/vi/-Alf5AHHJVo/mqdefault.jpg" alt="Watch the video" border="10" />
</a>
