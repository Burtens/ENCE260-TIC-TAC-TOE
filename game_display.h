/** @file   game_display.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup header file for game_display.c
*/

#ifndef GROUP_328_GAME_DISPLAY_H
#define GROUP_328_GAME_DISPLAY_H

#include "game.h"

//Status Messages
#define STARTUP_MESSAGE "  PAPER SCISSORS ROCK READY"
#define CONNECT_MESSAGE "  CONNECTING"
#define AGAIN_MESSAGE "  PLAY AGAIN"

//Game Messages
#define DRAW "  DRAW"
#define WIN "  WIN"
#define LOSS "  LOSS"


void game_display_init(void);

void update_task(__unused__ void *data);

void current_message(game_states_t state);

void display_choice(char choice);

void display_result (void *data);

#endif //GROUP_328_GAME_DISPLAY_H
