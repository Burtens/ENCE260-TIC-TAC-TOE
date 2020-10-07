/** @file   game.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup psr A simple paper, scissors, rock game.
*/

#include "system.h"
#include "task.h"
#include "game.h"
#include "game_display.h"
#include "nav_tasks.h"
#include "game_ir.h"

int main (void)
{
    state_t game_state = {STATE_INIT, 0,0, 0};

    system_init ();
    init_nav();
    game_display_init();

    current_message(game_state.state);

    task_t tasks[] = {
            {.func = update_task, .period = TASK_RATE/ 250},
            {.func = nav_update, .period = TASK_RATE / 100},
            {.func = nav_push_task, .period = TASK_RATE / 100, .data = &game_state},
            {.func = select_choice, .period = TASK_RATE / 100, .data = &game_state},
            {.func = send, .period = TASK_RATE / 100, .data = &game_state}
    };

    task_schedule(tasks, 4);

//    while (1)
//    {
//        switch (game_state)
//        {
//        case STATE_INIT:
//            ready ();
//            break;
//        case STATE_SELECTION:
//            select_choice ();
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
