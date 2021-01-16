/*
 * STMU_program.c
 *
 *  Created on: Dec 15, 2020
 *      Author: ahmed
 */

/************************************************************************/
/*                               Includes                               */
/************************************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MSTK/MSTK_interface.h"
#include "STMU/STMU_private.h"
#include "STMU/STMU_config.h"
#include "STMU/STMU_interface.h"

/************************************************************************/
/*                        Important system macros                       */
/************************************************************************/

#define CONVERT_TO_US (1000)

/************************************************************************/
/*                         Important variables                          */
/************************************************************************/

/*A variable used in counting system ticks*/
extern u32 tick_counter;

/*A variable used in counting tasks*/
static u8 tasks_counter = 0;

/*An array of tasks (Tasks pool)*/
static task_t task_arr[TASKS_NUM];

/************************************************************************/
/*                         Functions' definitions                       */
/************************************************************************/

/*This function is responsible for scheduling between TMU tasks*/
static void STMU_voidScheduler(void)
{
    /*A variable used in looping operations*/
    u8 looping_var = 0;

    /*Looping over RTOS tasks*/
    for(looping_var = 0 ; looping_var < tasks_counter ; looping_var++)
    {
        /*Check if the task time has come or not*/
        if( (tick_counter % task_arr[looping_var].task_periodicity) == 0)
        {
            /*Execute the task function*/
            task_arr[looping_var].func();
        }
        else
        {
            /*Do nothing*/
        }
    }

    /*Return from this function*/
    return;
}

void STMU_voidInit(void)
{
	/*Initializing system tick timer*/
	MSTK_EnuTimerInit();

	/*Return from this function*/
	return;
}

void STMU_voidAddTask(task_t task)
{
	/*Adding a task to the task pool*/
	task_arr[tasks_counter] = task;

	/*Increase tasks counter*/
	tasks_counter++;

	/*Return from this function*/
	return;
}


void STMU_voidStartScheduler(u32 tick_ms)
{
	/*Checking if tasks array is full or not*/
	if(tasks_counter == TASKS_NUM)
	{
		/*Turn ON STK timer with a specific period in milliseconds*/
		MSTK_EnuPeriodicInterval( (tick_ms * CONVERT_TO_US), STMU_voidScheduler);
	}
	else
	{
		/*Report error*/
	}

	/*Return from this function*/
	return;
}

