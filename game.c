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
#define MESSAGE_RATE 10

static uint8_t curr_choice = 0;
static uint8_t num_choices = 3;
static char choices[3] = {'P', 'S', 'R'};

void display_choice (char choice)
{
    char buffer[2];
    buffer[0] = choice;
    buffer[1] = '\0';
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text (buffer);
}

void selection (void) 
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) 
        curr_choice = (curr_choice + 1) % num_choices; // Wrap around
    
    if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        curr_choice = (curr_choice - 1) % num_choices; // Wrap around
    
    display_choice (choices[curr_choice]);
    
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
    tinygl_text (" PAPER SCISSORS ROCK READY");
    
    while (1) 
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            selection ();
        }
    }
    
    return 0;
}
