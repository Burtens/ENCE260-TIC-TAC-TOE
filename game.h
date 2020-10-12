/** @file   game.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  header file for game.c, also  contains global defines such as game_state_struct and game_states enum
*/

#ifndef GROUP_328_GAME_H
#define GROUP_328_GAME_H

#include "system.h" // Included here as uint8_t is defined here and is required for game_state_struct

#define INIT_VAL 0
#define DISPLAY_RATE 250
#define GAME_TASK_RATE 20
#define NUM_TASKS 6
#define NUM_CHOICES 3

//Numeric values to represent game choices
#define PAPER_CHOICE 0
#define SCISSOR_CHOICE 1
#define ROCK_CHOICE 2

//Enum of all states in the game
typedef enum {
    STATE_INIT, // Initial State
    STATE_SELECTION, // State where user is selecting a choice
    STATE_WAIT, // State where user is waiting for a response
    STATE_RESULT, // State where result is shown
    STATE_AGAIN // State where user is asked if they want to play again.
    } game_states_t;

//Definition of the game_state struct that stores the state of the game
typedef struct game_state_struct
{
    game_states_t state; // Current State
    uint8_t curr_choice; // Your choice
    uint8_t other_choice; // Other player's choice
    uint8_t sent; // Has the fun-kit sent its choice
    uint8_t received; // Has the fun-kit received a choice
} state_t;

#endif //GROUP_328_GAME_H
