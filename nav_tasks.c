/** @file   nav_tasks.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  module that controls the nav_switch tasks during runtime
*/

#include "system.h"
#include "nav_tasks.h"
#include "navswitch.h"
#include "game.h"
#include "game_ir.h"
#include "game_display.h"

// Array allows char to be displayed on screen based the value of the users choice
static char choices[NUM_CHOICES] = {PAPER, SCISSORS, ROCK};

// Initialises the navswitch
void init_nav(void)
{
    navswitch_init ();
}

// Updates navswitch
void nav_update (__unused__ void *data)
{
    navswitch_update();
}

// Allows the player to select between P (Paper), S (Scissors) and R (Rock) using navswitch.
void select_choice (void *data)
{
    state_t* game_state = data;

    if (game_state->state == STATE_SELECTION){
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            game_state->curr_choice = (game_state->curr_choice + 1) % NUM_CHOICES; // Wrap around
        }
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (game_state->curr_choice == PAPER_CHOICE) {
                game_state->curr_choice = ROCK_CHOICE; // Unsigned int can't have negative value so formula below can't be applied.
            } else {
                game_state->curr_choice = (game_state->curr_choice - 1) % NUM_CHOICES; // Wrap around
            }
        }
        display_char(choices[game_state->curr_choice]);
    }
}

/*
* Checks for nav_switch pushes and changes state accordingly
* Not all states have a response when the navswitch is pushed.
*/
void nav_push_task (void *data)
{
    state_t *game_state = data;

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        switch (game_state->state) {
            case STATE_INIT:
                game_state->state = STATE_SELECTION;
                current_message(game_state->state);
                break;
            case STATE_SELECTION:
                game_state->state = STATE_WAIT;
                current_message(game_state->state);
                send(data); //Sends choice to another fun-kit
                break;
            case STATE_RESULT:
                game_state->state = STATE_AGAIN;
                current_message(game_state->state);
                break;
            case STATE_AGAIN:
                //Reset Game
                game_state->curr_choice = INIT_VAL;
                game_state->other_choice = INIT_VAL;
                game_state->state = STATE_SELECTION;
                current_message(game_state->state);
                break;
            default:
                break;
        }
    }
}
