/**
 * This file is part of
 * 
 * RollingAverage
 * A rolling/moving average library for Arduino
 * 
 * MIT License
 * 
 * Copyright © 2020 Charles Fourneau
 *
 */

#include <RollingAverage.h>

RollingAverage::RollingAverage() {
	size = 0;
}

RollingAverage::RollingAverage(uint8_t s) {
	size = s;
	readings = (int16_t*) malloc(size * sizeof(int16_t));
	if (readings == NULL) size = 0;
}

RollingAverage::RollingAverage(uint8_t s, int16_t* r) {
	size = s;
	readings = r;
	if (readings == NULL) size = 0;
}

void RollingAverage::begin() {
	for (uint8_t i; i < size; i++) {
		readings[i] = 0;
	}
	sum = 0;
	index = 0;
	n_readings = 0;
}

void RollingAverage::addReading(int16_t value) {
	if (n_readings < size) {
		n_readings++;
		sum += value;
	}
	else {
		sum = sum - readings[index] + value;
	}

	readings[index] = value;
	index = (index == size - 1) ? 0 : index + 1;
}

int16_t RollingAverage::getAverage() {
	if (n_readings == 0) return 0;
	return (int16_t)(sum / n_readings);	
}
