/*
 * Capacitor.h
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */

#ifndef INC_CAPACITOR_H_
#define INC_CAPACITOR_H_

#include <stdint.h>


#define MAX_CAPACITOR_ENERGY 3000


extern uint32_t capacitor_energy;


void Capacitor_Update(void);
void Capacitor_DrawBar(int x, int y_base, int spacing, int max_units);
void Capacitor_Consume(uint32_t amount);
void Capacitor_Set(uint32_t amount);

#endif /* INC_CAPACITOR_H_ */
