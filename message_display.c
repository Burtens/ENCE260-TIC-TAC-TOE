//
// Created by sgb79 on 7/10/20.
//


#include "message_display.h"
#include "tinygl.h"

/*Changes the display to print a specific message based on current state*/
void current_message(game_state_t state)
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
