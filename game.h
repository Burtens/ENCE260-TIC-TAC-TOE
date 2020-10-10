/** @file   game.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup header file for game.c, also  contains global defines such as game_state_struct and game_states enum
*/

#ifndef GROUP_328_GAME_H
#define GROUP_328_GAME_H

#include "system.h"

#define PAPER_CHOICE 0
#define SCISSOR_CHOICE 1
#define ROCK_CHOICE 2

typedef enum {STATE_INIT, STATE_SELECTION, STATE_SEND, STATE_WAIT,
    STATE_RESULT, STATE_AGAIN} game_states_t;


typedef struct game_state_struct
{
    game_states_t state; //Current State
    uint8_t curr_choice; // Your choice
    uint8_t other_choice; // Other player's choice
    uint8_t sent;
    uint8_t received;

} state_t;


#endif //GROUP_328_GAME_H