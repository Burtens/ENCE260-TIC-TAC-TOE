/** @file   game_display.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  module that controls the display during runtime.
*/

#include "game_display.h"
#include "game.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "task.h"

// Initialise tinygl and apply preferences.
void game_display_init(void) 
{
    tinygl_init (TASK_RATE / DISPLAY_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (TEXT_SPEED);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

// Updates display by calling tinygl_update
void update_display(__unused__ void *data)
{
    tinygl_update();
}

// Changes the display to print a specific message based on current state
void current_message(game_states_t state)
{
    switch (state) {
        case STATE_INIT:
            tinygl_text (STARTUP_MESSAGE); // Display startup message
            break;
        case STATE_WAIT:
            tinygl_text (WAIT_MESSAGE); // Display connect message
            break;
        case STATE_AGAIN:
            tinygl_text (AGAIN_MESSAGE); // Display again message
            break;
        default: //If there is no message clear the screen
            tinygl_clear();
            break;
    }
}

// Checks whether the player won, lost or drew.
void display_result (void *data) 
{
    state_t *game_state = data;
    uint8_t your_choice = game_state->curr_choice;
    uint8_t opp_choice = game_state->other_choice;

    //Based on the result displays a char
    if (game_state->state == STATE_RESULT) {
        if (opp_choice != PAPER_CHOICE && opp_choice != SCISSOR_CHOICE && opp_choice != ROCK_CHOICE) {
            display_char(UNKNOWN);
        } else if  (your_choice == opp_choice) {
            display_char(DRAW);
        } else if ((your_choice == ROCK_CHOICE && opp_choice == SCISSOR_CHOICE) ||
                   (your_choice == SCISSOR_CHOICE && opp_choice ==  PAPER_CHOICE) ||
                   (your_choice == PAPER_CHOICE && opp_choice == ROCK_CHOICE)) {
            display_char(WIN);
        } else {
            display_char(LOSS);
        }
    }
}

// Method to display a char on the fun-kit display
void display_char (char char_to_disp)
{
    char buffer[2];
    buffer[0] = char_to_disp;
    buffer[1] = '\0';
    tinygl_text (buffer);
}
