/** @file   nav_tasks.h
    @author Samuel Burtenshaw, Zachary Kaye
    @date   5 October 2020
    @brief  A simple paper, scissors, rock game.

    @defgroup header file for nav_tasks.c
*/

#ifndef GROUP_328_NAV_TASKS_H
#define GROUP_328_NAV_TASKS_H

void init_nav(void);

void nav_update (__unused__ void *data);

void select_choice(void *data);

void nav_push_task(void *data);

#endif //GROUP_328_NAV_TASKS_H