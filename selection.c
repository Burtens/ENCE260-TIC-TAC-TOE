/** @file   selection.c
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup uses navswitch to allow user to select paper, scissors or rock.
*/

#include "system.h"
#include "selection.h"
#include "navswitch.h"
#include "tinygl.h"

#define NUM_CHOICES 3
#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'


static char choices[NUM_CHOICES] = {PAPER, SCISSORS, ROCK};



/* The player is able to select between P (Paper), S (Scissors) and R (Rock).
 * Once a selection is made the game switches to the connect state while it waits
 * for a selection by the other player.
 */
void selection (void)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        curr_choice = (curr_choice + 1) % NUM_CHOICES; // Wrap around
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        if (curr_choice == PAPER_CHOICE) {
            curr_choice = ROCK_CHOICE; // Unsigned int can't have negative value so formula below can't be applied.
        } else {
            curr_choice = (curr_choice - 1) % NUM_CHOICES; // Wrap around
        }
    }

    display_choice (choices[curr_choice]);

    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        game_state = STATE_CONNECT;
    }

}
