/** @file   nav_tasks.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup File that controls the nav_switch during runtime
*/

#include "system.h"
#include "nav_tasks.h"
#include "navswitch.h"
#include "game.h"
#include "game_display.h"

#define NUM_CHOICES 3

#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'


static char choices[NUM_CHOICES] = {PAPER, SCISSORS, ROCK};

void init_nav(void)
{
    navswitch_init ();
}

void nav_update (__unused__ void *data)
{
    navswitch_update();
}


/* The player is able to select between P (Paper), S (Scissors) and R (Rock).
 */
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

        display_choice (choices[game_state->curr_choice]);

    }
}

/*
* Checks for nav_switch pushes
*/
void nav_push_task (void *data) {
    state_t *game_state = data;
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        switch (game_state->state) {
            case STATE_INIT:
                game_state->state = STATE_SELECTION;
                break;
            case STATE_SELECTION:
                game_state->state = STATE_CONNECT;
        }
        current_message(game_state->state);
    }
}
