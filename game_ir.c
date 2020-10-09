//
// Created by sam on 7/10/20.
//

#include "game_ir.h"
#include "ir_uart.h"
#include "game.h"
#include "game_display.h"

void init_ir(void)
{
    ir_uart_init();
}


//Sends the selected choice and sets state to wait for ACK response
void send(void *data)
{
    state_t* game_state = data;
    if (game_state->state == STATE_SEND) {
        ir_uart_putc(game_state->curr_choice);

        game_state->state = STATE_WAIT;
    }

    if (game_state->state == STATE_WAIT) {
        check_response_and_ACK(data);
    }
}


/* Checks if selection has been received. If there was interference
or the selection received wasn't P, S, or R then the other player's choice
isn't set.
Also waits for an ACK response before continuing*/
void check_response_and_ACK(void *data)
{
    state_t* game_state = data;

    if (ir_uart_read_ready_p()) {
        return;
    }

    game_state->other_choice = ir_uart_getc();
    ir_uart_putc(game_state->curr_choice);
    game_state->state = STATE_RESULT;
    display_result(data);
}


