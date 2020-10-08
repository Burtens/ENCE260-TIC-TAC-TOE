//
// Created by sam on 7/10/20.
//

#include "game_ir.h"
#include "ir_uart.h"
#include "game.h"
#include "game_display.h"
#include "led.h"

#define NAK '?'
#define ACK '$'

static uint8_t led_state = 1;

void init_ir(void)
{
    ir_uart_init();
}


//Sends the selected choice and sets state to wait for ACK response
void send(void *data)
{
    state_t* game_state = data;
    if (game_state->state == STATE_SEND) {
        led_state = !led_state;
        led_set(LED1, led_state);
        ir_uart_putc_nocheck(choices[game_state->curr_choice]);
        game_state->state = STATE_WAIT;
    } else if (game_state->state == STATE_WAIT) {
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
    game_state->response_timer += 1;
    if (game_state->response_timer >= 100) {
        game_state->response_timer = 0;
        game_state->state = STATE_SEND;
        return;
    }

    if (!ir_uart_read_ready_p()) {
        return;
    }

    char temp_choice = ir_uart_getc ();
    display_choice(temp_choice);
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
            display_result(data);
            game_state->state = STATE_RESULT;
            break;
        default:
            ir_uart_putc_nocheck(NAK);
            break;
    }
}


