/*
  ShiftRegister74HC595.hpp - Library for simplified control of 74HC595 shift registers.
  Developed and maintained by Timo Denk and contributers, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  Released into the public domain.

  Raspberry pi Pico port by Devnol
*/
#include <cstring>
#include "ShiftRegister74HC595.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
// ShiftRegister74HC595 constructor
// Size is the number of shiftregisters stacked in serial
template<uint8_t Size>
ShiftRegister74HC595<Size>::ShiftRegister74HC595(spi_inst_t *spiPort, uint8_t sdiPin, uint8_t sckPin, uint8_t latchPin)
{
    // set spi pins
    gpio_set_function(sdiPin, GPIO_FUNC_SPI);
    gpio_set_function(sckPin, GPIO_FUNC_SPI);

    // set attributes
    _spiPort = spiPort;
    _latchPin = latchPin;


    spi_init(spiPort, 500 * 1000);
 
    gpio_init(latchPin);

    gpio_set_dir(latchPin, GPIO_OUT);

    gpio_put(latchPin, 0);

    // allocates the specified number of bytes and initializes them to zero
    memset(_digitalValues, 0, Size * sizeof(uint8_t));

    updateRegisters();       // reset shift register
}

// Set all pins of the shift registers at once.
// digitalVAlues is a uint8_t array where the length is equal to the number of shift registers.
template<uint8_t Size>
void ShiftRegister74HC595<Size>::setAll(const uint8_t * digitalValues)
{
    memcpy( _digitalValues, digitalValues, Size);   // dest, src, size
    updateRegisters();
}

// Set a specific pin to either HIGH (1) or LOW (0).
// The pin parameter is a positive, zero-based integer, indicating which pin to set.
template<uint8_t Size>
void ShiftRegister74HC595<Size>::set(const uint8_t pin, const uint8_t value)
{
    setNoUpdate(pin, value);
    updateRegisters();
}

// Retrieve all states of the shift registers' output pins.
// The returned array's length is equal to the number of shift registers.
template<uint8_t Size>
uint8_t * ShiftRegister74HC595<Size>::getAll()
{
    return _digitalValues; 
}

// Updates the shift register pins to the stored output values.
// This is the function that actually writes data into the shift registers of the 74HC595.
template<uint8_t Size>
void ShiftRegister74HC595<Size>::updateRegisters()
{   

    spi_write_blocking(_spiPort, _digitalValues, sizeof _digitalValues);
    
    gpio_put(_latchPin, 1); 
    gpio_put(_latchPin, 0); 
}

// Equivalent to set(int pin, uint8_t value), except the physical shift register is not updated.
// Should be used in combination with updateRegisters().
template<uint8_t Size>
void ShiftRegister74HC595<Size>::setNoUpdate(const uint8_t pin, const uint8_t value)
{
    (value) ? (_digitalValues[pin / 8] |= (1 << pin % 8)) : (_digitalValues[pin /8] &= ~(1 << pin % 8));
}

// Returns the state of the given pin.
// Either HIGH (1) or LOW (0)
template<uint8_t Size>
uint8_t ShiftRegister74HC595<Size>::get(const uint8_t pin)
{
    return (_digitalValues[pin / 8] >> (pin % 8)) & 1;
}

// Sets all pins of all shift registers to HIGH (1).
template<uint8_t Size>
void ShiftRegister74HC595<Size>::setAllHigh()
{
    for (int i = 0; i < Size; i++) {
        _digitalValues[i] = 255;
    }
    updateRegisters();
}

// Sets all pins of all shift registers to LOW (0).
template<uint8_t Size>
void ShiftRegister74HC595<Size>::setAllLow()
{
    for (int i = 0; i < Size; i++) {
        _digitalValues[i] = 0;
    }
    updateRegisters();
}
