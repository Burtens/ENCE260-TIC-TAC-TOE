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
#include "pacer.h"
#include "task.h"
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




typedef enum {STATE_INIT, STATE_SELECTION, STATE_CONNECT,
              STATE_RESULT, STATE_AGAIN} game_state_t;



/* Once the player is ready to play and pressed the navswitch
 * the player is taken to the selection screen. 
 */
static void ready (void *data)
{
    game_state_t* game_state = data;
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        *game_state = STATE_SELECTION;
    }
}

/*Changes the display to print a specific message based on current state*/
static void current_message(game_state_t state)
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

/* Updates display by calling tinygl_update */
static void update_task(void *data)
{
    game_state_t* game_state = data;
    current_message(*game_state);
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
    tinygl_init (TASK_RATE/250);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (8);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    task_t tasks[] = {
            {.func = update_task, .period = TASK_RATE/500, .data = &game_state},
            {.func = ready, .period = TASK_RATE/300, .data = &game_state}
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
