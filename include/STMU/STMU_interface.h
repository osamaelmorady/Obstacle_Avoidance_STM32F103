/*
 * STMU_interface.h
 *
 *  Created on: Dec 15, 2020
 *      Author: ahmed
 */

#ifndef STMU_INTERFACE_H_
#define STMU_INTERFACE_H_

/************************************************************************/
/*                             Task data type                           */
/************************************************************************/

typedef struct
{
    /*A pointer to the task function*/
    void (*func)(void);

    /*Task periodic time*/
    u16 task_periodicity;
}task_t;

/************************************************************************/
/*                          Functions' prototypes                       */
/************************************************************************/

/*This function is responsible for initializing TMU module*/
void STMU_voidInit(void);

/*This function is responsible for adding tasks to TMU module*/
void STMU_voidAddTask(task_t task);

/*This function is responsible for starting TMU scheduler with a specific system tick (from 0 to 16777ms)*/
void STMU_voidStartScheduler(u32 tick_ms);

#endif /* STMU_INTERFACE_H_ */
