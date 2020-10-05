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


#define LOOP_RATE 300
#define MESSAGE_RATE 10

static void updateScreen(void) {
    tinygl_update ();
}

int main (void)
{
    
    system_init ();
    navswitch_init ();
    ir_uart_init ();
    //pacer_init (LOOP_RATE);
    
    // Initialise tinygl and apply preferences.
    tinygl_init(250);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    
    // Display startup message
    tinygl_text (" PAPER SCISSORS ROCK READY");

    task_t tasks[] =
    {
            {.func = (task_func_t) updateScreen, .period = TASK_RATE /500.}
    };

    task_schedule(tasks, 1);
    return 0;
}
