/*
 * Difficulty.c
 *
 *  Created on: Apr 16, 2025
 *      Author: joelrsilva
 */


#include "Difficulty.h"

DifficultyLevel current_difficulty = MEDIUM;

void SetDifficulty(int selection_index) {
    if (selection_index == 0) current_difficulty = EASY;
    else if (selection_index == 1) current_difficulty = MEDIUM;
    else current_difficulty = HARD;
}

DifficultyLevel GetDifficulty() {
    return current_difficulty;
}

int GetMaxSatchels() {
    switch (current_difficulty) {
        case EASY: return 1;
        case MEDIUM: return 2;
        case HARD: return 3;
        default: return 1;
    }
}
