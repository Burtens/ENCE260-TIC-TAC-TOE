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


#define LOOP_RATE 300
#define MESSAGE_RATE 15
#define STARTUP_MESSAGE "  PAPER SCISSORS ROCK READY"
#define CONNECT_MESSAGE "  CONNECTING"
#define NUM_CHOICES 3

#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'

#define PAPER_CHOICE 0
#define ROCK_CHOICE 2

static uint8_t curr_choice = 0;
static char choices[NUM_CHOICES] = {PAPER, SCISSORS, ROCK};

typedef enum {STATE_INIT, STATE_SELECTION, STATE_CONNECT } game_state_t;

static game_state_t game_state = STATE_INIT;


/* Once the player is ready to play and pressed the navswitch
 * the player is taken to the selection screen. 
 */
void ready (void)
{
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        game_state = STATE_SELECTION;
    }
}


void display_choice (char choice)
{
    char buffer[2];
    buffer[0] = choice;
    buffer[1] = '\0';
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text (buffer);
}

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

/* Checks whether the other player has made a selection and sets player numbers. */
void connect (void)
{
    tinygl_text (CONNECT_MESSAGE); // Wait while connection is made.
}


int main (void)
{
    
    system_init ();
    navswitch_init ();
    ir_uart_init ();
    pacer_init (LOOP_RATE);
    
    // Initialise tinygl and apply preferences.
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    
    // Display startup message
    tinygl_text (STARTUP_MESSAGE);
    
    while (1) 
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        
        switch (game_state)
        {
        case STATE_INIT: 
            ready ();
            break;
        case STATE_SELECTION:
            selection ();
            break;
        case STATE_CONNECT:
            connect ();
            break;
        default:
            break;
        }
    }
    
    return 0;
}
