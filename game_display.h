/** @file   game_display.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  header file for game_display.c
*/

#ifndef GROUP_328_GAME_DISPLAY_H
#define GROUP_328_GAME_DISPLAY_H

#include "game.h" // Included here as the definitions for update_display and current_message require values from game.h

//Status Messages
#define STARTUP_MESSAGE "  PAPER SCISSORS ROCK READY"
#define WAIT_MESSAGE "  WAITING"
#define AGAIN_MESSAGE "  PLAY AGAIN"

//Result Chars
#define DRAW 'D'
#define WIN 'W'
#define LOSS 'L'

//Player Choices
#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'

#define TEXT_SPEED 7

void game_display_init(void);

void update_display(__unused__ void *data);

void current_message(game_states_t state);

void display_char(char char_to_disp);

void display_result (void *data);

#endif //GROUP_328_GAME_DISPLAY_H
