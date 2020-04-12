/**
 * This file is part of
 * 
 * NITROX ANALYZER
 * An Arduino based EANx/Nitrox analyzer
 * 
 * MIT License, see LICENSE file
 * 
 * Copyright © 2020 Charles Fourneau
 * 
 */

#include "nitrox.h"

uint16_t calc_mod(uint16_t fO2, uint16_t pO2_max = 1600u)
{
	return (uint16_t)(((uint32_t)pO2_max * 10000ul) / (uint32_t)fO2) - 1000ul;
}