/*
 * Shield.h
 *
 *  Created on: Apr 15, 2025
 *      Author: joelrsilva
 */

#ifndef INC_SHIELD_H_
#define INC_SHIELD_H_

#include <stdint.h>
#include <stdbool.h>

#define SHIELD_MAX_HEALTH 10
#define SHIELD_DAMAGE 5   // Damage per hit
#define SHIELD_DRAIN_INTERVAL 1000 // 2000 ms
#define SHIELD_BAR_COST (MAX_CAPACITOR_ENERGY / 10) // 1 bar

extern bool shield_active;
extern uint32_t shield_energy;

void StartShieldTask(void const * argument);

void ActivateShield(void);
void DeactivateShield(void);
void Shield_Update(void);
void Shield_TakeHit(void);
uint8_t GetShieldHealth(void);

#endif /* INC_SHIELD_H_ */
