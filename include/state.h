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

#ifndef _STATE_H_
#define _STATE_H_

enum state_t {
	STATE_START_SCREEN,
	STATE_ANALYZE,
	STATE_HOLD,
	STATE_CALIBRATE_MENU,
	STATE_CALIBRATE,
	STATE_ERROR,
};

enum state_ppo2_t {
	PPO2_1_4,
	PPO2_1_5,
	PPO2_1_6,
	MV,
	PPO2_ENUM_MAX,
};

// loop though states without overflow (increment and decrement)
inline state_ppo2_t operator++(state_ppo2_t &p, int)  {  return p = state_ppo2_t((p == PPO2_ENUM_MAX - 1) ? 0 : (p + 1));  }  
inline state_ppo2_t operator--(state_ppo2_t &p, int)  {  return p = state_ppo2_t((p == 0) ? (PPO2_ENUM_MAX - 1) : (p - 1));  }  

enum state_dialog_t {
	YES,
	NO,
};

#endif // _STATE_H_