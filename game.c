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
#include "pio.h"

// Rates
enum {DISPLAY_TASK_RATE = 300};
enum {NAVSWITCH_TASK_RATE = 20};
enum {GAME_TASK_RATE = 100};

typedef enum {STATE_INIT, STATE_SELECTION,
              STATE_PLAYING, STATE_OVER, 
              STATE_READY} state_t;
              
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
            
        }
    }
    
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        switch (state)
        {
            
        }
    }
    
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        switch (state)
        {
            
        }
    }
    
    // Recieve
}

static void game_task (void *data)
{
    switch (state) 
    {
    case STATE_INIT:
        tinygl_text ("  PAPER, SCISSORS, ROCK");
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
