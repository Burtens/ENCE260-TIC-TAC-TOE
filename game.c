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

static void checkResponse(void) {
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
        tinygl_draw_char('5',tinygl_point(0,0));
    }
}

int main (void)
{
    
    system_init ();
    navswitch_init ();
    ir_uart_init ();
    
    // Initialise tinygl and apply preferences.
    tinygl_init(TASK_RATE/250);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    
    // Display startup message
    tinygl_text (" PAPER SCISSORS ROCK READY");

    task_t tasks[] =
    {
            {.func = (task_func_t) updateScreen, .period = TASK_RATE /500},
            {.func = (task_func_t) checkResponse, .period = TASK_RATE /100}
    };

    task_schedule(tasks, 2);
    return 0;
}
