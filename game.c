/** @file   game.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup psr A simple paper, scissors, rock game.
*/

#include "system.h"
#include "tinygl.h"
#include "task.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"
#include "pio.h"

// Rates
#define DISPLAY_TASK_RATE 300
#define NAVSWITCH_TASK_RATE 20
#define GAME_TASK_RATE 100

// Choices
static char choices[3] = {'P', 'S', 'R'};
static uint8_t curr_choice = 0;
static uint8_t num_choices = 3;

typedef enum {STATE_INIT, STATE_SELECTION, 
              STATE_PLAYING, 
              STATE_OVER, } state_t;
              
static state_t state = STATE_INIT;

static void display_task (void *data)
{
    static bool init = 0;
    
    if (!init) {
        
        tinygl_init (DISPLAY_TASK_RATE);
        tinygl_font_set (&font5x7_1);
        tinygl_text_speed_set (10);
        tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

        init = 1;
    }
}

void display_choice (char choice)
{
    char buffer[2];
    buffer[0] = choice;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

static void navswitch_task (void *data)
{
    static bool init = 0;
    
    
    if (!init) {
        navswitch_init ();
        init = 1;
    }
    
    navswitch_update ();
    
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        switch (state)
        {
        case STATE_SELECTION:
            curr_choice = (curr_choice + 1) % num_choices; // Wrap Around
            display_choice (choice[curr_choice]);
            break;
        }
        case STATE_INIT:
        case STATE_PLAYING:
        case STATE_OVER:
        default:
            break;
    }
    
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        switch (state)
        {
        case STATE_SELECTION:
            if (choice != 0)
            { 
                choice = (choice - 1) % num_choices;
            } else {
                choice = 2;
            }
            display_choice (choice[curr_choice]);
            break;
        }
        case STATE_INIT:
        case STATE_PLAYING:
        case STATE_OVER:
        default:
            break;
    }
    
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        switch (state)
        {
        case STATE_INIT:
            state = STATE_SELECTION;
            display_choice (choice[curr_choice]);
            break;
        case STATE_SELECTION:
            
        }
        case STATE_PLAYING:
        case STATE_OVER:
        default:
            break;
    }
    
    // Recieve
}

static void game_task (void *data)
{
    switch (state) 
    {
    case STATE_INIT:
        tinygl_text ("  PAPER, SCISSORS, ROCK READY");
        state = STATE_READY;
        break;
    }
}

int main (void)
{
    task_t tasks[] =
    { 
        {.func = display_task, .period = TASK_RATE / DISPLAY_TASK_RATE,
         .data = 0},
        {.func = navswitch_task, .period = TASK_RATE / NAVSWITCH_TASK_RATE,
         .data = 0},
        {.func = game_task, .period = TASK_RATE / GAME_TASK_RATE,
         .data = 0},
    };
    
    system_init ();
    
    task_schedule (tasks, 3);
    return 0;
}
