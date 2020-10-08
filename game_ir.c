//
// Created by sam on 7/10/20.
//

#include "game_ir.h"
#include "ir_uart.h"
#include "game.h"
#include "game_display.h"

#define NAK '?'
#define ACK '$'


//Sends the selected choice and sets state to wait for ACK response
void send(void *data)
{
    state_t* game_state = data;
    if (game_state->state == STATE_SEND) {
        ir_uart_putc_nocheck(choices[game_state->curr_choice]);
        game_state->state = STATE_WAIT;
    }
}


/* Checks if selection has been received. If there was interference
or the selection received wasn't P, S, or R then the other player's choice
isn't set.
Also waits for an ACK response before continuing*/
void check_response_and_ACK(void *data)
{
    state_t* game_state = data;
    game_state->response_timer += 1;
    if (game_state->response_timer >= 1000 && game_state->state == STATE_WAIT) {
        game_state->response_timer = 0;
        game_state->state = STATE_SEND;
    } else if (ir_uart_read_ready_p () && game_state->state == STATE_WAIT) {
        char temp_choice = ir_uart_getc ();
        game_state->response_timer = 0;
        switch (temp_choice) {
            case 'P':
                game_state->other_choice = PAPER_CHOICE;
                ir_uart_putc_nocheck(ACK);
                break;
            case 'S':
                game_state->other_choice = SCISSOR_CHOICE;
                ir_uart_putc_nocheck(ACK);
                break;
            case 'R':
                game_state->other_choice = ROCK_CHOICE;
                ir_uart_putc_nocheck(ACK);
                break;
            case NAK:
                game_state->state = STATE_SEND;
                break;
            case ACK:
                game_state->state = STATE_RESULT;
                break;
            default:
                ir_uart_putc_nocheck(NAK);
                break;
        }
    }
}


