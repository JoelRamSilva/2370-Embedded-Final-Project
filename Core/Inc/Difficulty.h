/*
 * Difficulty.h
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */

#ifndef INC_DIFFICULTY_H_
#define INC_DIFFICULTY_H_


typedef enum {
    EASY,
    MEDIUM,
    HARD
} DifficultyLevel;

extern DifficultyLevel selected_difficulty;

void SetDifficulty(int selection_index);
DifficultyLevel GetDifficulty();
int GetMaxSatchels(void);


#endif /* INC_DIFFICULTY_H_ */
