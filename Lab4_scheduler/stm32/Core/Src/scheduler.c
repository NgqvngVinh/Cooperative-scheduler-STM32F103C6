/*
 * scheduler.c
 *
 *  Created on: Nov 9, 2024
 *      Author: vinhd
 */


#include "scheduler.h"
#include "usart.h"
#include <stdlib.h>
#include <stdio.h>



#define TICK 10


sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

//int timer_tick_count = 0;
int global_tick_count = 0;  // Thêm biến để theo dõi tổng số tick kể từ khi hệ thống bắt đầu




//origin
void SCH_Add_Task(void (* pFunction)() , uint32_t DELAY, uint32_t PERIOD){
// Have we reached the end of the list?
if (current_index_task < SCH_MAX_TASKS){

// If we’re here, there is a space in the task array
	SCH_tasks_G[current_index_task].pTask = pFunction;
	SCH_tasks_G[current_index_task].Delay = DELAY/TICK;
	SCH_tasks_G[current_index_task].Period = PERIOD/TICK;
	SCH_tasks_G[current_index_task].RunMe = 0;

	SCH_tasks_G[current_index_task].TaskID = current_index_task;
    SCH_tasks_G[current_index_task].DeleteMe = 0;


	current_index_task++;
	}
}

void SCH_Update(void) {
    global_tick_count++;  // Cập nhật tổng số tick

    for (int i = 0; i < current_index_task; i++) {
        if (SCH_tasks_G[i].Delay > 0) {
            SCH_tasks_G[i].Delay--;
//            global_tick_count++;  // Cập nhật tổng số tick


        } else {
            SCH_tasks_G[i].RunMe += 1;

            // Nếu là one-shot task (PERIOD = 0), đánh dấu TaskID = -1 để xóa
            if (SCH_tasks_G[i].Period > 0) {
                SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;

////            	HAL_Delay(1000);
//            	printf("Current index task: %d\n\r", current_index_task);
//                SCH_Delete_Task(-1);
            } else  {
                // Đặt lại Delay nếu task định kỳ
//                SCH_tasks_G[i].TaskID = -1;  // Đánh dấu để xóa
            	SCH_tasks_G[i].DeleteMe = 1;


            }
        }
    }
}

//chỉ in ra period của task-incorrect
//void SCH_Update(void){
//	for(int i = 0; i < current_index_task; i++){
//		if(SCH_tasks_G[i].Delay > 0){
//			SCH_tasks_G[i].Delay --;
//
//
//		}
//		else{
//			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
//			SCH_tasks_G[i].RunMe += 1;
//	        timer_tick_count = SCH_tasks_G[i].Delay * TICK;  // Tính toán thời gian dựa trên Period
//		}
//	}
//}


//origin
void SCH_Dispatch_Tasks(void){

	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe --;
			(*SCH_tasks_G[i].pTask)();

            printf("Task %d executed at %d TICK\n\r", SCH_tasks_G[i].TaskID, global_tick_count);
		}

//		if(SCH_tasks_G[i].Period == 0){
		if(SCH_tasks_G[i].DeleteMe == 1){
//		if(SCH_tasks_G[i].TaskID == -1){


//			printf("Current index task: %d\n\r", current_index_task);

            printf("Task %d deleted at %d TICK\n\r", SCH_tasks_G[i].TaskID, global_tick_count);

			SCH_Delete_Task(SCH_tasks_G[i].TaskID);
//			SCH_Delete_Task(-1);

			i--;

		}
	}
}





//origin
void SCH_Delete_Task(uint32_t taskID) {
    // Find the task with the given TaskID
    for (int i = 0; i < current_index_task; i++) {
        if (SCH_tasks_G[i].TaskID == taskID) {
            // Remove the task by shifting all subsequent tasks up
            for (int j = i; j < current_index_task - 1; j++) {
                SCH_tasks_G[j] = SCH_tasks_G[j + 1];
                SCH_tasks_G[j].TaskID = j; // Cập nhật lại TaskID cho đúng vị trí


            }
            // Clear the last task slot
            SCH_tasks_G[current_index_task - 1].pTask = 0x0000;
            SCH_tasks_G[current_index_task - 1].Delay = 0;
            SCH_tasks_G[current_index_task - 1].Period = 0;
            SCH_tasks_G[current_index_task - 1].RunMe = 0;

            SCH_tasks_G[current_index_task - 1].TaskID = 0;

            // Decrement the current task index
            current_index_task--;

            printf("Current index task after delete: %d\n\r", current_index_task);

            return;
        }
    }
}





//origin
void SCH_Init(void){
    current_index_task = 0;
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
//    	SCH_Delete_Task(i);

        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
}










