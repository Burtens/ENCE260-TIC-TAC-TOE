/** @file   nav_tasks.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   11 October 2020
    @brief  header file for game_ir.c

*/

#ifndef GROUP_328_GAME_IR_H
#define GROUP_328_GAME_IR_H

void init_ir(void);

void send(void *data);

void check_response(void *data);

#endif //GROUP_328_GAME_IR_H
