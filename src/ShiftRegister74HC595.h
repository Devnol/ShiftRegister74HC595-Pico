/*
  ShiftRegister74HC595.h - Library for simplified control of 74HC595 shift registers.
  RP2040 Port by Devnol and contributors, developed and maintained since Jul 2021.
  Original Arduino Version Developed and maintained by Timo Denk and contributors, since Nov 2014.
  Additional information is available at https://timodenk.com/blog/shift-register-arduino-library/
  For usage see /example/example.cpp in this repository
*/
#pragma once

#include <inttypes.h>
#include "hardware/spi.h"

template<uint8_t Size>
class ShiftRegister74HC595 
{
public:
    ShiftRegister74HC595(spi_inst_t *spiPort, uint8_t sdiPin, uint8_t sckPin, uint8_t latchPin);
    
    void setAll(const uint8_t * digitalValues);
    uint8_t * getAll(); 
    void set(const uint8_t pin, const uint8_t value);
    void setNoUpdate(const uint8_t pin, uint8_t value);
    void updateRegisters();
    void setAllLow();
    void setAllHigh(); 
    uint8_t get(const uint8_t pin);

private:
    spi_inst_t* _spiPort;
    uint8_t _latchPin;
    uint8_t _digitalValues[Size];
};

#include "ShiftRegister74HC595.hpp"
