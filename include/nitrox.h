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

#ifndef _NITROX_H_
#define _NITROX_H_

#include <stdint.h>

/**
 * Calculate MOD, given O2 fraction and O2 max partial pressure
 *
 * To keep precision and avoid using floats, units are not SI
 * 
 * @param fO2 oxygen fraction in 0.01%
 *            e.g. 20,95% -> fO2 = 2095
 * @param pO2_max max allowed oxygen partial pressure, in mbar
 *                e.g. 1,6bar -> pO2_max = 1600
 * @return MOD in cm
 */
uint16_t calc_mod(uint16_t fO2, uint16_t pO2_max = 1600u);

#endif // _NITROX_H_