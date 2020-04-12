/******************************************************************************
 * This file is part of
 * 
 * Library for ADS1115, 16-bit I²C ADC converter
 * 
 * Copyright (C) 2020, Charles Fourneau
 *
 * based on adafruit/Adafruit_ADS1015 code: 
 * 
 * 		(C) 2012, Adafruit Industries
 * 
 * see header file for more information
 * 
 ******************************************************************************/

#include "ADS1115.h"

#include <Arduino.h>
#include <Wire.h>

#define ADS1115_CONFIG_EMPTY 0x0000

/**
 *  Write 16-bits to the specified destination register
 */
static void writeRegister(uint8_t address, uint8_t reg, uint16_t value)
{
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.write((uint8_t)(value >> 8));
	Wire.write((uint8_t)(value & 0xFF));
	Wire.endTransmission();
}

/**
 * Read & return the specified 16-bits register
 */
static uint16_t readRegister(uint8_t address, uint8_t reg)
{
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(address, (uint8_t)2);
	return (((uint16_t)Wire.read() << 8) | Wire.read());
}

/**
 * Constructor
 */
ADS1115::ADS1115(uint8_t address = ADS1115_ADDRESS) :
	address(address),
	config(ADS1115_CONFIG_EMPTY)
{
	// this->address = address;
	// this->config = ADS1115_CONFIG_EMPTY;
}

/**
 * Initialize the device, read default configuration
 */
void ADS1115::begin()
{
	// Wire.begin(); // should this be here ?
	(void) this->readConfig();
}

/**
 * Check if device is busy (conversion in progress)
 */
bool ADS1115::isBusy()
{
	(void) this->readConfig();
	if ((this->config & ADS1115_REG_CONFIG_MODE_MASK) != 0
		&& !((this->config & ADS1115_REG_CONFIG_OS_MASK) != 0))
	{
		// device is in power-down / single-shot mode
		// and conversion is in progress
		return true;
	}
	// device is either in continuous conversion mode
	// or no conversion is in progress
	return false;
}

/**
 * Start a single conversion
 */
void ADS1115::startSingleConversion()
{
	this->config |= ADS1115_REG_CONFIG_OS_SINGLE;
	this->writeConfig();
}

/**
 * Start the continuous conversion mode
 */
void ADS1115::startContinuousConversion()
{
	this->config &= ~ADS1115_REG_CONFIG_MODE_MASK; // clear the MODE bit
	// this->config |= ADS1115_REG_CONFIG_MODE_CONTIN; // unnecessary
	this->writeConfig();
}

/**
 * Read & return the result of the last conversion
 * 
 * Wait until conversion is complete if ADC is in single-shot and conversion is in progress
 * 
 * WARNING: result must be converted to signed (int16_t)
 */
int16_t ADS1115::readLastConversion()
{
	while (this->isBusy())
	{
		delay(1);
	}
	return (int16_t)readRegister(this->address, ADS1115_REG_POINTER_CONVERT);
}

/**
 * Set input voltage range / PGA
 */
void ADS1115::setGain(adsGain_t gain)
{
	this->config &= ~ADS1115_REG_CONFIG_PGA_MASK; // clear the PGA bits
	this->config |= (uint16_t)gain;
}

/**
 * Get input voltage range / PGA setting
 */
adsGain_t ADS1115::getGain()
{
	return (adsGain_t)(this->config & ADS1115_REG_CONFIG_PGA_MASK);
}

/**
 * Set data sampling rate
 */
void ADS1115::setDataRate(adsDataRate_t rate)
{
	this->config &= ~ADS1115_REG_CONFIG_DR_MASK; // clear the DR bits
	this->config |= (uint16_t)rate;
}

/**
 * Get data sampling rate
 */
adsDataRate_t ADS1115::getDataRate(void)
{
	return (adsDataRate_t)(this->config & ADS1115_REG_CONFIG_DR_MASK);
}

/**
 * Set Mux
 */
void ADS1115::setMux(adsMux_t mux)
{
	this->config &= ~ADS1115_REG_CONFIG_MUX_MASK; // clear the MUX bits
	this->config |= (uint16_t)mux;
}

/**
 * Get Mux
 */
adsMux_t ADS1115::getMux(void)
{
	return (adsMux_t)(this->config & ADS1115_REG_CONFIG_MUX_MASK);
}

/**
 * write the CONFIG register
 */
void ADS1115::writeConfig()
{
	writeRegister(this->address, ADS1115_REG_POINTER_CONFIG, this->config);
}

void ADS1115::writeConfig(uint16_t config)
{
	this->config = config;
	writeRegister(this->address, ADS1115_REG_POINTER_CONFIG, this->config);
}

/**
 * read the CONFIG register
 */
uint16_t ADS1115::readConfig()
{
	this->config = readRegister(this->address, ADS1115_REG_POINTER_CONFIG);
	return this->config;
}
