# BusinessCard_Rev_0
 
/* 
Firmware for Atmega32u4 for a simple pcb touch slider interactive business card

Project is an Atmel Studio project "solution" configured with Atmel Start, for easy set up and interface of touch slider

The business card assembly runs on a CR2016 battery, so the unit will sleep after about 6 seconds without input. A long hold of any slider pad will wake it from sleep

The PTC (peripheral touch controller) software libraries are able to interpolate a finger's approximate location on the slider with only a few pads. This firmware controls 7 LEDs based on the touch position with only 5 pads.
*/
