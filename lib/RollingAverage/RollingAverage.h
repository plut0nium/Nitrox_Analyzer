/**
 * RollingAverage
 * A rolling/moving average library for Arduino
 * 
 * MIT License
 * 
 * Copyright © 2020 Charles Fourneau
 *
 */

#ifndef _ROLLING_AVERAGE_H_
#define _ROLLING_AVERAGE_H_

#include <Arduino.h>

class RollingAverage {
public:
	RollingAverage();
	RollingAverage(uint8_t size);
	RollingAverage(uint8_t size, int16_t* readings);
	void begin();

public:
	void addReading(int16_t value);
	int16_t getAverage();

private:
	uint8_t size;
	uint8_t index;
	uint8_t n_readings;
	int16_t* readings;
	int32_t sum;
};

#endif // _ROLLING_AVERAGE_H_
