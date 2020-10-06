//
// Created by sgb79 on 7/10/20.
//

#include "system.h"
#include "result.h"

/* Checks whether the player won, lost or drew. */
void result (void)
{
    if (curr_choice == other_choice) {
        tinygl_text (DRAW);
    } else if (curr_choice == ROCK_CHOICE && other_choice == SCISSOR_CHOICE) {
        tinygl_text (WIN);
    } else if (curr_choice == SCISSOR_CHOICE && other_choice == PAPER_CHOICE) {
        tinygl_text (WIN);
    } else if (curr_choice == PAPER_CHOICE && other_choice == ROCK_CHOICE) {
        tinygl_text (WIN);
    } else {
        tinygl_text (LOSS);
    }

    game_state = STATE_AGAIN;
}
