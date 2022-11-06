# Ultrasonic_Phased_Array
This repository contains all the sources for a working ultrasonic phased array.
The vitis project in this repository is to be used in a accoustic levitation example.

## abstract
When we power up the system, the transducers start emitting ultrasonic sound waves each at the same frequency (40kHz) and amplitude. However, the phases of the transducers are software controllable. This gives us full control over the beam shape and direction exiting the transducer array.

## Working principle
Lets consider an example where we want to send a single pulse of airpressure to a certain point in space. We have an array of transducers we can work with. If we time the pulse at each transducer correctly, we can make all the waves arrive at that point simultaniously.
Since the waves travel in a sphere around the transducer, we can use the distance from the point to each transducer in combination with the wavelength to time the pulse correctly.

[<img src="img/gifsmos_single_focus.gif" width="250px"/>](img/gifsmos_single_focus.gif)

If we were to send a sinewave through the transducers with a delay determined by the distance from the focal point, all the peaks and troughs of those waves would ideally only add up in the focal point. The amplitude would then be the greatest at that point and cancel out everywhere else. Since the sine wave is periodic, we use the remainder of devision by the wavelength as a negative phase shift of the sine waves.

## Setup
There are two array's used in the levitation example. One is facing upwards and the other is facing downwards. They are facing eachother with a distance of 70mm. this distance is arbitrarily chosen based on the needed volume for levitation.

## FPGA
The FPGA implementation receives 7 bit values from the PS for every transducer. This value sets the phase of the output signal. This is acheived by making a fifo of length = 2^7. The 40KHz signal is fed into the fifo at 40KHz * 2^7 = 5.12MHz. The reason for this is because we want a full period of the signal in the fifo. The 7 bit value determines where the output signal is tapped from.
Im currently cleaning up the FPGA implementation and turn it into an IP-block, i will include the files in this repository once i'm finished. 
