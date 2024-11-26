/*
 * scheduler.h
 *
 *  Created on: Nov 9, 2024
 *      Author: vinhd
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"
#include <stddef.h>

#define SCH_MAX_TASKS 	41


typedef struct{
	void (*pTask)(void); //con trỏ gọi đến task thực hiện khi tiến hành trừ period(Delay)
	uint32_t	Delay;  //same timer_counter
	uint32_t	Period; //same timer_counter
	uint8_t		RunMe; //same timer_flag

	uint32_t	TaskID; //hiện thực tác vụ thêm trong Lab4
    uint8_t 	DeleteMe;  // New field to mark tasks for deletion

}sTasks;

//double linked list lưu trữ các task
//typedef struct TaskNode {
//	sTasks task;
//	struct TaskNode* next;
////	struct TaskNode* prev;
//} TaskNode;

//extern TaskNode* head;
////extern TaskNode* prev;
//extern TaskNode* tail;


void SCH_Init(void);
void SCH_Add_Task ( void (*pFunction)() ,
					uint32_t DELAY,
					uint32_t PERIOD);  //same setTimer()
void SCH_Update(void); //Same timer_run->goi trong ngat timer
void SCH_Dispatch_Tasks(void); //same check timer_flag = 1 -> execute task
void SCH_Delete_Task(uint32_t taskID);
//void SCH_Delete_Task(TaskNode* node);

//void insert_task_sorted(TaskNode* new_node);





#endif /* INC_SCHEDULER_H_ */
