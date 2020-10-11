/** @file   game.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.
*/

#include "system.h"
#include "task.h"
#include "game.h"
#include "game_display.h"
#include "nav_tasks.h"
#include "game_ir.h"

int main (void)
{

    //Initialise the state of the game
    state_t game_state = {STATE_INIT, INIT_VAL, INIT_VAL, INIT_VAL, INIT_VAL};

    //Initialise all drivers used in the game
    system_init ();
    init_nav();
    game_display_init();
    init_ir();

    //Set the first message of the game
    current_message(game_state.state);

    //Define all game tasks
    task_t tasks[] = {
            {.func = update_display, .period = TASK_RATE / DISPLAY_RATE},
            {.func = nav_update, .period = TASK_RATE / GAME_TASK_RATE},
            {.func = nav_push_task, .period = TASK_RATE / GAME_TASK_RATE, .data = &game_state},
            {.func = select_choice, .period = TASK_RATE / GAME_TASK_RATE, .data = &game_state},
            {.func = check_response, .period = TASK_RATE / GAME_TASK_RATE, .data = &game_state},
            {.func = display_result, .period = TASK_RATE / GAME_TASK_RATE, .data = &game_state}
    };

    //Start task scheduler
    task_schedule(tasks, NUM_TASKS);
    return 0;
}
