//
// Created by sam on 7/10/20.
//

#include "game_ir.h"
#include "ir_uart.h"
#include "game.h"

void check_response_and_ACK(void *data);

void send(void *data)
{
    state_t* game_state = data;
    if (game_state->state == STATE_CONNECT) {
        ir_uart_putc(choices[game_state->curr_choice]);
        game_state->state = STATE_WAIT;
    }
}


/* Checks if selection has been recieved. If there was interference
or the selection recieved wasn't P, S, or R then the other player's choice
isn't set.*/
void check_response_and_ACK(void *data)
{
    state_t* game_state = data;
    if (ir_uart_read_ready_p () && game_state->state == STATE_WAIT) {
        char temp_choice = ir_uart_getc ();
        switch (temp_choice) {
            case 'P':
                game_state->other_choice = PAPER_CHOICE;
                ir_uart_putc('$');
                break;
            case 'S':
                game_state->other_choice = SCISSOR_CHOICE;
                ir_uart_putc('$');
                break;
            case 'R':
                game_state->other_choice = ROCK_CHOICE;
                ir_uart_putc('$');
                break;
            default:
                ir_uart_putc('?');
                break;
        }
        
    }
}
