//
// Created by sgb79 on 7/10/20.
//

#ifndef GROUP_328_GAME_DISPLAY_H
#define GROUP_328_GAME_DISPLAY_H

#include "game.h"

#define STARTUP_MESSAGE "  PAPER SCISSORS ROCK READY"
#define CONNECT_MESSAGE "  CONNECTING"
#define AGAIN_MESSAGE "  PLAY AGAIN"

void game_display_init(void);

void update_task(__unused__ void *data);

void current_message(game_states_t state);

void display_choice(char choice);

#endif //GROUP_328_GAME_DISPLAY_H
