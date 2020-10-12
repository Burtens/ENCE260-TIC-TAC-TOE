/** @file   nav_tasks.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   11 October 2020
    @brief  module that controls the ir sensor on the fun-kit for the game, makes use of the ir_uart drivers.

*/

#include "game_ir.h"
#include "ir_uart.h"
#include "game.h"

// Initialises ir_uart
void init_ir(void)
{
    ir_uart_init();
}

//Sends the selected choice and sets state to wait for ACK response
void send(void *data)
{
    state_t* game_state = data;
    game_state->sent = 1; // Has sent
    ir_uart_putc(game_state->curr_choice); // Sends choice to another fun-kit
}

/* Checks if selection has been received and goes to the result state, otherwise listens for a
 * received selection from another fun-kit and saves it if it is received. */
void check_response(void *data)
{
    state_t* game_state = data;

    if (game_state->sent && game_state->received) {
        game_state->state = STATE_RESULT;
        /* Resets the received and sent values for next game. Set here in an attempt to stop game from breaking if
         * other player continues on to next game and sends before this fun-kit has started another game */
        game_state->received = INIT_VAL;
        game_state->sent = INIT_VAL;
    } else if (ir_uart_read_ready_p()) {
        game_state->other_choice = ir_uart_getc();
        game_state->received = 1; // Has Received
    }
}


