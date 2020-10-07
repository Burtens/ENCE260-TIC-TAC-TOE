/** @file   game_display.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup File that controls the display during runtime.
*/

#define TASK_RATE (8000000 / 256)


#include "game_display.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"



// Initialise tinygl and apply preferences.
void game_display_init(void) {
    tinygl_init (TASK_RATE/250);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (7);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

// Updates display by calling tinygl_update
void update_task(__unused__ void *data)
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
        case STATE_CONNECT:
            tinygl_text (CONNECT_MESSAGE); // Display connect message
            break;
        case STATE_RESULT:
            // TODO: Get result message
            break;
        case STATE_AGAIN:
            tinygl_text (AGAIN_MESSAGE); // Display again message
            break;
        case STATE_SELECTION:
            break;
    }
}

// Displays char representing the users choice when user is selecting a choice
void display_choice (char choice)
{
    char buffer[2];
    buffer[0] = choice;
    buffer[1] = '\0';
    tinygl_text (buffer);
}
