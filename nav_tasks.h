/** @file   nav_tasks.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  header file for nav_tasks.c
*/

#ifndef GROUP_328_NAV_TASKS_H
#define GROUP_328_NAV_TASKS_H

//Player Choices
#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'

void init_nav(void);

void nav_update (__unused__ void *data);

void select_choice(void *data);

void nav_push_task(void *data);

#endif //GROUP_328_NAV_TASKS_H
