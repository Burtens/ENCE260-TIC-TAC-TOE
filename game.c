/** @file   game.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup psr A simple paper, scissors, rock game.
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "task.h"
#include "../fonts/font5x7_1.h"

static state_t state = STATE_INIT;

static void display_task (void *data)
{
    
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
