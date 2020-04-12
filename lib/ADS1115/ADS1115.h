/******************************************************************************
 * 
 * Library for ADS1115, 16-bit I²C ADC converter
 * 
 * Copyright (C) 2020, Charles Fourneau
 *
 * based on adafruit/Adafruit_ADS1015 code: 
 * 
 * 		(C) 2012, Adafruit Industries
 * 
 *		This is a library for the Adafruit ADS1X15 ADC breakout boards.
 *		Adafruit invests time and resources providing this open source code,
 *		please support Adafruit and open-source hardware by purchasing
 *		products from Adafruit!
 * 
 *		Written by Kevin "KTOWN" Townsend for Adafruit Industries.
 * 
 *		BSD license, all text here must be included in any redistribution
 * 
 * Features
 * - support for ADS1115 only
 * - allows continuous conversion mode
 * - explicit access functions for gain, sampling rate & mux
 * 
 * TODO:
 * - Comparator mode is not implemented
 *
 ******************************************************************************/

#ifndef _ADS1115_H_
#define _ADS1115_H_

#include <Arduino.h>

#define ADS1115_ADDRESS_GND             0x48    // 0b1001000 - ADDR = GND
#define ADS1115_ADDRESS_VDD             0x49    // 0b1001001 - ADDR = VDD
#define ADS1115_ADDRESS_SCA             0x4A    // 0b1001010 - ADDR = SCA
#define ADS1115_ADDRESS_SCL             0x4B    // 0b1001011 - ADDR = SCL
#define ADS1115_ADDRESS                 ADS1115_ADDRESS_GND

// POINTER REGISTER
#define ADS1115_REG_POINTER_MASK        0x03
#define ADS1115_REG_POINTER_CONVERT     0x00
#define ADS1115_REG_POINTER_CONFIG      0x01
#define ADS1115_REG_POINTER_LOWTHRESH   0x02
#define ADS1115_REG_POINTER_HITHRESH    0x03

// CONFIG REGISTER
#define ADS1115_REG_CONFIG_OS_MASK      0x8000
#define ADS1115_REG_CONFIG_OS_SINGLE    0x8000  // Write: Set to start a single-conversion
#define ADS1115_REG_CONFIG_OS_BUSY      0x0000  // Read: Bit = 0 when conversion is in progress
#define ADS1115_REG_CONFIG_OS_NOTBUSY   0x8000  // Read: Bit = 1 when device is not performing a conversion

#define ADS1115_REG_CONFIG_MUX_MASK     0x7000
#define ADS1115_REG_CONFIG_MUX_DIFF_0_1 0x0000  // Differential P = AIN0, N = AIN1 (default)
#define ADS1115_REG_CONFIG_MUX_DIFF_0_3 0x1000  // Differential P = AIN0, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_1_3 0x2000  // Differential P = AIN1, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_2_3 0x3000  // Differential P = AIN2, N = AIN3
#define ADS1115_REG_CONFIG_MUX_SINGLE_0 0x4000  // Single-ended AIN0
#define ADS1115_REG_CONFIG_MUX_SINGLE_1 0x5000  // Single-ended AIN1
#define ADS1115_REG_CONFIG_MUX_SINGLE_2 0x6000  // Single-ended AIN2
#define ADS1115_REG_CONFIG_MUX_SINGLE_3 0x7000  // Single-ended AIN3

#define ADS1115_REG_CONFIG_PGA_MASK     0x0E00
#define ADS1115_REG_CONFIG_PGA_6_144V   0x0000  // +/-6.144V range = Gain 2/3
#define ADS1115_REG_CONFIG_PGA_4_096V   0x0200  // +/-4.096V range = Gain 1
#define ADS1115_REG_CONFIG_PGA_2_048V   0x0400  // +/-2.048V range = Gain 2 (default)
#define ADS1115_REG_CONFIG_PGA_1_024V   0x0600  // +/-1.024V range = Gain 4
#define ADS1115_REG_CONFIG_PGA_0_512V   0x0800  // +/-0.512V range = Gain 8
#define ADS1115_REG_CONFIG_PGA_0_256V   0x0A00  // +/-0.256V range = Gain 16

#define ADS1115_REG_CONFIG_MODE_MASK    0x0100
#define ADS1115_REG_CONFIG_MODE_CONTIN  0x0000  // Continuous conversion mode
#define ADS1115_REG_CONFIG_MODE_SINGLE  0x0100  // Power-down single-shot mode (default)

#define ADS1115_REG_CONFIG_DR_MASK      0x00E0
#define ADS1115_REG_CONFIG_DR_8SPS      0x0000  // 8 samples per second
#define ADS1115_REG_CONFIG_DR_16SPS     0x0020  // 16 samples per second
#define ADS1115_REG_CONFIG_DR_32SPS     0x0040  // 32 samples per second
#define ADS1115_REG_CONFIG_DR_64SPS     0x0060  // 64 samples per second
#define ADS1115_REG_CONFIG_DR_128SPS    0x0080  // 128 samples per second (default)
#define ADS1115_REG_CONFIG_DR_250SPS    0x00A0  // 250 samples per second
#define ADS1115_REG_CONFIG_DR_475SPS    0x00C0  // 475 samples per second
#define ADS1115_REG_CONFIG_DR_860SPS    0x00E0  // 860 samples per second

#define ADS1115_REG_CONFIG_CMODE_MASK   0x0010
#define ADS1115_REG_CONFIG_CMODE_TRAD   0x0000  // Traditional comparator with hysteresis (default)
#define ADS1115_REG_CONFIG_CMODE_WINDOW 0x0010  // Window comparator

#define ADS1115_REG_CONFIG_CPOL_MASK    0x0008
#define ADS1115_REG_CONFIG_CPOL_ACTVLOW 0x0000  // ALERT/RDY pin is low when active (default)
#define ADS1115_REG_CONFIG_CPOL_ACTVHI  0x0008  // ALERT/RDY pin is high when active

#define ADS1115_REG_CONFIG_CLAT_MASK    0x0004  // Determines if ALERT/RDY pin latches once asserted
#define ADS1115_REG_CONFIG_CLAT_NONLAT  0x0000  // Non-latching comparator (default)
#define ADS1115_REG_CONFIG_CLAT_LATCH   0x0004  // Latching comparator

#define ADS1115_REG_CONFIG_CQUE_MASK    0x0003
#define ADS1115_REG_CONFIG_CQUE_1CONV   0x0000  // Assert ALERT/RDY after one conversions
#define ADS1115_REG_CONFIG_CQUE_2CONV   0x0001  // Assert ALERT/RDY after two conversions
#define ADS1115_REG_CONFIG_CQUE_4CONV   0x0002  // Assert ALERT/RDY after four conversions
#define ADS1115_REG_CONFIG_CQUE_NONE    0x0003  // Disable the comparator and put ALERT/RDY in high state (default)


typedef enum
{
	GAIN_TWOTHIRDS = ADS1115_REG_CONFIG_PGA_6_144V,
	GAIN_ONE       = ADS1115_REG_CONFIG_PGA_4_096V,
	GAIN_TWO       = ADS1115_REG_CONFIG_PGA_2_048V,
	GAIN_FOUR      = ADS1115_REG_CONFIG_PGA_1_024V,
	GAIN_EIGHT     = ADS1115_REG_CONFIG_PGA_0_512V,
	GAIN_SIXTEEN   = ADS1115_REG_CONFIG_PGA_0_256V
} adsGain_t;


typedef enum
{
	DR_8SPS		   = ADS1115_REG_CONFIG_DR_8SPS,
	DR_16SPS	   = ADS1115_REG_CONFIG_DR_16SPS,
	DR_32SPS	   = ADS1115_REG_CONFIG_DR_32SPS,
	DR_64SPS	   = ADS1115_REG_CONFIG_DR_64SPS,
	DR_128SPS	   = ADS1115_REG_CONFIG_DR_128SPS,
	DR_250SPS	   = ADS1115_REG_CONFIG_DR_250SPS,
	DR_475SPS	   = ADS1115_REG_CONFIG_DR_475SPS,
	DR_860SPS	   = ADS1115_REG_CONFIG_DR_860SPS
} adsDataRate_t;


typedef enum {
	MUX_DIFF_0_1   = ADS1115_REG_CONFIG_MUX_DIFF_0_1,
	MUX_DIFF_0_3   = ADS1115_REG_CONFIG_MUX_DIFF_0_3,
	MUX_DIFF_1_3   = ADS1115_REG_CONFIG_MUX_DIFF_1_3,
	MUX_DIFF_2_3   = ADS1115_REG_CONFIG_MUX_DIFF_2_3,
	MUX_SINGLE_3   = ADS1115_REG_CONFIG_MUX_SINGLE_0,
	MUX_SINGLE_0   = ADS1115_REG_CONFIG_MUX_SINGLE_1,
	MUX_SINGLE_1   = ADS1115_REG_CONFIG_MUX_SINGLE_2,
	MUX_SINGLE_2   = ADS1115_REG_CONFIG_MUX_SINGLE_3,
} adsMux_t;


class ADS1115
{
public:
	ADS1115(uint8_t address =  ADS1115_ADDRESS);
	
	void      begin(void);
	bool      isBusy(void);
	void      startSingleConversion(void);
	void      startContinuousConversion(void);
	int16_t   readLastConversion(void);
	void      setGain(adsGain_t gain);
	adsGain_t getGain(void);
	void      setDataRate(adsDataRate_t rate);
	adsDataRate_t getDataRate(void);
	void      setMux(adsMux_t mux);
	adsMux_t  getMux(void);
	void      writeConfig(void);
	void      writeConfig(uint16_t config);
	uint16_t  readConfig(void);

private:
	uint8_t   address;
	uint16_t  config;
};


#endif
