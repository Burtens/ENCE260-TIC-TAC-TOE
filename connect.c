//
// Created by sgb79 on 7/10/20.
//

#include "system.h"
#include "connect.h"
#include "ir_uart.h"

/* Checks whether the other player has made a selection and sends own selection.*/
void connect (void)
{
    ir_uart_putc (choices[curr_choice]); // Send choice.

    uint8_t recieved_choice = 1;

    // Checks if selection has been recieved. If there was interference/
    // selection recieved wasn't P, S, or R then the other player's choice
    // isn't set.
    if (ir_uart_read_ready_p ()) {
        char temp_choice;
        temp_choice = ir_uart_getc ();
        if (temp_choice == choices[PAPER_CHOICE]) {
            other_choice = PAPER_CHOICE;
        } else if (temp_choice == choices[SCISSOR_CHOICE]) {
            other_choice = SCISSOR_CHOICE;
        } else if (temp_choice == choices[ROCK_CHOICE]) {
            other_choice = ROCK_CHOICE;
        } else {
            recieved_choice = 0;
        }
    }

    if (recieved_choice) {
        game_state = STATE_RESULT;
    }

}
