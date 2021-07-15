/* 
ShiftRegister74HC595-Pico example by Devnol, adapted from Timo Denk's Arduino example
Wiring diagram example can be found in this folder's example_schematic files
*/
#include "../src/ShiftRegister74HC595.h"
#include <hardware/gpio.h>

/*
The pins of the 7-segment displays are as follows:
  --0--
  5   1
  --6--
  4   2
  --3--7 (7 being the decimal point)
if you have multiple displays, the rightmost one is the first one in counting for both 
set() commands and setAll() arrays. 
For example, to turn on the 4th segment of the 2nd digit from right to left you would do:
set(12,1), 12 is 8 for the first segment plus 4 (the 4th segment on the second digit), 1 is to set the segment to on.
*/


//spi interface, either spi0 or spi1, 
//make sure to pick the right pins according to the diagram provided in the pico datasheet
#define SPI_PORT spi0 

#define SCK_PIN 2 //clock pin
#define SDI_PIN 3 //data pin
#define LATCH_PIN 4 //latch pin
#define DISPLAY_SIZE 3 //number of digits in display

// create a global shift register object
// parameters: <number of shift registers> (spi port, clock pin, data pin, latch pin)
ShiftRegister74HC595<DISPLAY_SIZE> sr(SPI_PORT, SCK_PIN, SDI_PIN, LATCH_PIN);

uint8_t disp_digits[10] = { //decimal numbers, each array index corresponds to the right number
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111 //9
};

//decimal point, use bitwise or with other numbers to enable
uint8_t decimal_point = 0b10000000; 

int main() {
	//IF THE OUTPUT IS INVERTED, comment/uncomment the following line:
	gpio_set_outover(SDI_PIN, GPIO_OVERRIDE_INVERT); 

	//array with length the same as the number of digits in your display
	uint8_t test_array[DISPLAY_SIZE] = { 
		//put any numbers you want, right to left, use "| decimal_point" to add a dot to it.
		// (of course you can put any symbol you want with the correct bit sequence, consult your display datasheet for more information).
		disp_digits[0],
		disp_digits[2] | decimal_point, //use "| decimal_point to add a dot to any digit"
		disp_digits[4]
	};
	sr.setAll(test_array); //set diplay to the contents of the test array
	sleep_ms(1000);
	sr.setAllLow(); //set all pins to off
	sleep_ms(1000);
	sr.setAllHigh(); //set all pins to on
	sleep_ms(1000);
	sr.setAllLow(); //set all pins to off
	sleep_ms(1000);
	sr.set(12, 1); //set a specific pin to on, 
	sleep_ms(1000);
	sr.set(12, 0); //set a specific pin to off,
 
  	// read pin (zero based, i.e. 6th pin is get(5))
  	uint8_t stateOfPin5 = sr.get(5);
  	sr.set(6, stateOfPin5);
  	
	// set pins without immediate update
  	sr.setNoUpdate(0, 1);
  	sr.setNoUpdate(1, 0);
  	// at this point of time, pin 0 and 1 did not change yet
  	sr.updateRegisters(); // update the pins to the set values

	return 0;
}