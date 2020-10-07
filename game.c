/** @file   game.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup psr A simple paper, scissors, rock game.
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "task.h"
#include "game.h"
#include "message_display.h"
#include "selection.h"


#define LOOP_RATE 300
#define MESSAGE_RATE 15

#define STARTUP_MESSAGE "  PAPER SCISSORS ROCK READY"
#define CONNECT_MESSAGE "  CONNECTING"
#define AGAIN_MESSAGE "  PLAY AGAIN"

#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'

#define PAPER_CHOICE 0
#define SCISSOR_CHOICE 1
#define ROCK_CHOICE 2

#define DRAW "  DRAW"
#define WIN "  WIN"
#define LOSS "  LOSS"


/* Once the player is ready to play and pressed the navswitch
 * the player is taken to the selection screen. 
 */
static void ready (void *data)
{
    game_state_t* game_state = data;

    if (navswitch_push_event_p (NAVSWITCH_PUSH) && *game_state == STATE_INIT) {
        *game_state = STATE_CONNECT;
        current_message(*game_state);
    }
}


/* Updates display by calling tinygl_update */
static void update_task(void)
{
    navswitch_update();
    tinygl_update();
}


void display_choice (char choice)
{
    char buffer[2];
    buffer[0] = choice;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    game_state_t game_state = STATE_INIT; //Current State
    uint8_t curr_choice = 0; // Your choice
    uint8_t other_choice = 0; // Other player's choice

    system_init ();
    navswitch_init ();
    
    // Initialise tinygl and apply preferences.
    tinygl_init (TASK_RATE/500);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (2);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text (STARTUP_MESSAGE); // Display startup message

    task_t tasks[] = {
            {.func = update_task, .period = TASK_RATE /500},
            {.func = ready, .period = TASK_RATE/1000, .data = &game_state}
    };

    task_schedule(tasks, 2);

//    while (1)
//    {
//        switch (game_state)
//        {
//        case STATE_INIT:
//            ready ();
//            break;
//        case STATE_SELECTION:
//            selection ();
//            break;
//        case STATE_CONNECT:
//            connect ();
//            break;
//        case STATE_RESULT:
//            result ();
//            break;
//        case STATE_AGAIN:
//            again ();
//            break;
//        default:
//            break;
//        }
//    }

    return 0;
}
