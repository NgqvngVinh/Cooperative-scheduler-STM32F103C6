/////*
//// * scheduler_O(1).c
//// *
//// *  Created on: Nov 12, 2024
//// *      Author: vinhd
//// */
////
////#include "scheduler.h"
////#include "usart.h"
////#include <stdlib.h>
////#include <stdio.h>
////
////#define TICK 10
////
////uint32_t next_tick_delay = 0;  // Giữ delay cho task đầu tiên để giảm trong mỗi lần update
////
////sTasks SCH_tasks_G[SCH_MAX_TASKS];
////uint8_t current_index_task = 0;
////int global_tick_count = 0;  // Tổng số tick kể từ khi hệ thống bắt đầu
////
////TaskNode* head = NULL;
//////TaskNode* tail = NULL;
////
//////void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
//////    if (current_index_task < SCH_MAX_TASKS) {
//////        // Tạo node mới
//////        TaskNode* new_node = (TaskNode*)malloc(sizeof(TaskNode));
//////
//////        new_node->task.pTask = pFunction;
//////        new_node->task.Delay = DELAY / TICK;
//////        new_node->task.Period = PERIOD / TICK;
//////        new_node->task.RunMe = 0;
//////        new_node->task.TaskID = current_index_task;
//////        new_node->next = NULL;
//////
//////        if (head == NULL || head->task.Delay > new_node->task.Delay) {
//////            // Thêm vào đầu danh sách nếu nó là task có delay nhỏ nhất
//////            new_node->next = head;
//////            head = new_node;
//////            if (tail == NULL) {
//////                tail = new_node;
//////            }
//////            next_tick_delay = new_node->task.Delay;
//////        } else {
//////            // Thêm vào giữa hoặc cuối danh sách
//////            TaskNode* current = head;
//////            while (current->next != NULL && current->next->task.Delay <= new_node->task.Delay) {
//////                new_node->task.Delay -= current->task.Delay;
//////                current = current->next;
//////            }
//////            new_node->next = current->next;
//////            current->next = new_node;
//////            if (new_node->next == NULL) {
//////                // Nếu node mới trở thành node cuối cùng
//////                tail = new_node;
//////            }
//////        }
//////
//////        current_index_task++;
//////    }
//////}
//////
//////
//////
//////
//////
//////void SCH_Update(void) {
//////    global_tick_count++;  // Cập nhật tổng số tick
//////
//////    if (head != NULL) {
//////        if (next_tick_delay > 0) {
//////            next_tick_delay--;
//////        } else {
//////            head->task.RunMe += 1;
//////
//////            if (head->task.Period == 0) {
//////                // Nếu là one-shot task, đánh dấu để xóa
//////                head->task.TaskID = -1;
//////            } else {
//////                // Đặt lại Delay nếu task định kỳ
//////                head->task.Delay = head->task.Period;
//////                next_tick_delay = head->task.Delay;
//////            }
//////        }
//////    }
//////}
//////
//////
//////
//////
//////
//////
//////void SCH_Dispatch_Tasks(void) {
//////    TaskNode* current = head;
//////    TaskNode* prev = NULL;
//////
//////    while (current != NULL) {
//////        if (current->task.RunMe > 0) {
//////            current->task.RunMe--;
//////            (*current->task.pTask)();
//////            printf("Task %d executed at %d ms\n\r", current->task.TaskID, global_tick_count * TICK);
//////
//////            // Nếu task là one-shot và đã hoàn thành, xóa task
//////            if (current->task.TaskID == -1) {
//////                TaskNode* to_delete = current;
//////
//////                if (prev == NULL) {
//////                    // Xóa node đầu tiên
//////                    head = current->next;
//////                    if (head == NULL) {
//////                        // Nếu danh sách trống sau khi xóa
//////                        tail = NULL;
//////                        next_tick_delay = 0;
//////                    } else {
//////                        next_tick_delay = head->task.Delay;
//////                    }
//////                } else {
//////                    // Xóa node ở giữa hoặc cuối
//////                    prev->next = current->next;
//////                    if (current->next == NULL) {
//////                        // Nếu xóa node cuối cùng
//////                        tail = prev;
//////                    }
//////                }
//////
//////                current = current->next;
//////                free(to_delete);
//////                current_index_task--;
//////            } else {
//////                prev = current;
//////                current = current->next;
//////            }
//////        } else {
//////            prev = current;
//////            current = current->next;
//////        }
//////    }
//////}
//////
//////
//////
//////
//////
//////
//////void SCH_Init(void) {
//////    current_index_task = 0;
//////    TaskNode* current = head;
//////
//////    while (current != NULL) {
//////        TaskNode* to_delete = current;
//////        current = current->next;
//////        free(to_delete);
//////    }
//////    head = NULL;
//////    tail = NULL;
//////    next_tick_delay = 0;
//////}
////
////
////
////
////void insert_task_sorted(TaskNode* new_node) {
////    if (head == NULL) {
////        head = new_node;
////    } else {
////        TaskNode* current = head;
////        TaskNode* prev = NULL;
////        uint32_t accumulated_delay = 0;
////
////        while (current != NULL && accumulated_delay + current->task.Delay <= new_node->task.Delay) {
////            accumulated_delay += current->task.Delay;
////            prev = current;
////            current = current->next;
////        }
////
////        new_node->task.Delay -= accumulated_delay;
////
////        if (prev == NULL) {
////            // Thêm vào đầu danh sách
////            new_node->next = head;
////            head = new_node;
////        } else {
////            // Thêm vào giữa hoặc cuối danh sách
////            new_node->next = current;
////            prev->next = new_node;
////        }
////
////        if (current != NULL) {
////            current->task.Delay -= new_node->task.Delay;
////        }
////    }
////}
////
////void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
////    if (current_index_task < SCH_MAX_TASKS) {
////        // Tạo node mới
////        TaskNode* new_node = (TaskNode*)malloc(sizeof(TaskNode));
////
////        new_node->task.pTask = pFunction;
////        new_node->task.Delay = DELAY / TICK;
////        new_node->task.Period = PERIOD / TICK;
////        new_node->task.RunMe = 0;
////        new_node->task.TaskID = current_index_task;
////        new_node->next = NULL;
////
////        // Thêm task mới vào danh sách theo thứ tự tăng dần của Delay
////        insert_task_sorted(new_node);
////
////        // Nếu thêm vào đầu danh sách thì cập nhật lại `next_tick_delay`
////        if (head == new_node) {
////            next_tick_delay = new_node->task.Delay;
////        }
////
////        current_index_task++;
////    }
////}
////
////void SCH_Update(void) {
////    global_tick_count++;  // Cập nhật tổng số tick
////
////    if (head != NULL) {
////        if (next_tick_delay > 0) {
////            next_tick_delay--;
////        } else {
////            head->task.RunMe += 1;
////
////            // Nếu là task định kỳ, đặt lại Delay và sắp xếp lại
////            if (head->task.Period > 0) {
////                TaskNode* completed_task = head;
////                head = head->next;
////
////                // Đặt lại Delay cho task định kỳ
////                completed_task->task.Delay = completed_task->task.Period;
////                completed_task->next = NULL;
////
////                // Sắp xếp lại task vào danh sách
////                insert_task_sorted(completed_task);
////
////                // Cập nhật lại `next_tick_delay`
////                if (head != NULL) {
////                    next_tick_delay = head->task.Delay;
////                }
////            } else {
////                // Nếu là one-shot task, đánh dấu để xóa
////                head->task.TaskID = -1;
////            }
////        }
////    }
////}
////
////void SCH_Dispatch_Tasks(void) {
////    TaskNode* current = head;
////    TaskNode* prev = NULL;
////
////    while (current != NULL) {
////        if (current->task.RunMe > 0) {
////            current->task.RunMe--;
////            (*current->task.pTask)();
////            printf("Task %d executed at %d ms\n\r", current->task.TaskID, global_tick_count * TICK);
////
////            // Nếu task là one-shot và đã hoàn thành, xóa task
////            if (current->task.TaskID == -1) {
////                TaskNode* to_delete = current;
////
////                if (prev == NULL) {
////                    // Xóa node đầu tiên
////                    head = current->next;
////                    if (head != NULL) {
////                        next_tick_delay = head->task.Delay;
////                    }
////                } else {
////                    prev->next = current->next;
////                }
////
////                current = current->next;
////                free(to_delete);
////                current_index_task--;
////            } else {
////                prev = current;
////                current = current->next;
////            }
////        } else {
////            prev = current;
////            current = current->next;
////        }
////    }
////}
////
////void SCH_Init(void) {
////    current_index_task = 0;
////    TaskNode* current = head;
////
////    while (current != NULL) {
////        TaskNode* to_delete = current;
////        current = current->next;
////        free(to_delete);
////    }
////    head = NULL;
////    next_tick_delay = 0;
////}
//
//
//#include "scheduler.h"
//#include "usart.h"
//#include <stdlib.h>
//#include <stdio.h>
//
//#define TICK 10
//
//
//
//sTasks SCH_tasks_G[SCH_MAX_TASKS];
//uint8_t current_index_task = 0;
//uint32_t next_tick_delay = 0;  // Giữ delay cho task đầu tiên để giảm trong mỗi lần update
//int global_tick_count = 0;  // Tổng số tick kể từ khi hệ thống bắt đầu
//
//void SCH_Init(void) {
//    current_index_task = 0;
//    for (int i = 0; i < SCH_MAX_TASKS; i++) {
//        SCH_tasks_G[i].pTask = 0;
//        SCH_tasks_G[i].Delay = 0;
//        SCH_tasks_G[i].Period = 0;
//        SCH_tasks_G[i].RunMe = 0;
//        SCH_tasks_G[i].TaskID = -1;  // TaskID=-1 nghĩa là slot này trống
//    }
//    next_tick_delay = 0;
//}
//
//void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
//    if (current_index_task < SCH_MAX_TASKS) {
//        // Tạo task mới và chèn vào mảng ở vị trí phù hợp để giữ thứ tự tăng dần của Delay
//        int i = 0;
//        while (i < current_index_task && SCH_tasks_G[i].Delay <= DELAY / TICK) {
//            DELAY -= SCH_tasks_G[i].Delay * TICK;
//            i++;
//        }
//
//        // Dịch chuyển các task phía sau để tạo khoảng trống cho task mới
//        for (int j = current_index_task; j > i; j--) {
//            SCH_tasks_G[j] = SCH_tasks_G[j - 1];
//        }
//
//        // Thêm task mới vào đúng vị trí
//        SCH_tasks_G[i].pTask = pFunction;
//        SCH_tasks_G[i].Delay = DELAY / TICK;
//        SCH_tasks_G[i].Period = PERIOD / TICK;
//        SCH_tasks_G[i].RunMe = 0;
//        SCH_tasks_G[i].TaskID = current_index_task;
//
//        // Điều chỉnh `Delay` cho task tiếp theo sau task mới chèn vào
//        if (i < current_index_task) {
//            SCH_tasks_G[i + 1].Delay -= SCH_tasks_G[i].Delay;
//        }
//
//        current_index_task++;
//        if (i == 0) {
//            next_tick_delay = SCH_tasks_G[0].Delay;
//        }
//    } else {
//        printf("No space for new task\n");
//    }
//}
//
//void SCH_Update(void) {
//    global_tick_count++;  // Cập nhật tổng số tick
//
//    if (next_tick_delay > 0) {
//        next_tick_delay--;
//    } else {
//        if (SCH_tasks_G[0].pTask != 0) {
//            SCH_tasks_G[0].RunMe += 1;
//
//            // Nếu là task định kỳ, đặt lại Delay và điều chỉnh `next_tick_delay`
//            if (SCH_tasks_G[0].Period > 0) {
//                SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
//                next_tick_delay = SCH_tasks_G[0].Delay;
//            } else {
//                // Đánh dấu để xóa nếu là one-shot task
//                SCH_tasks_G[0].TaskID = -1;
//            }
//        }
//    }
//}
//
//void SCH_Dispatch_Tasks(void) {
//    for (int i = 0; i < current_index_task; i++) {
//        if (SCH_tasks_G[i].RunMe > 0) {
//            SCH_tasks_G[i].RunMe--;
//            (*SCH_tasks_G[i].pTask)();
//            printf("Task %d executed at %d ms\n\r", SCH_tasks_G[i].TaskID, global_tick_count * TICK);
//
//            // Nếu task là one-shot và đã hoàn thành, xóa task
//            if (SCH_tasks_G[i].TaskID == -1) {
//                // Dịch chuyển các task phía sau lên để lấp khoảng trống
//                for (int j = i; j < current_index_task - 1; j++) {
//                    SCH_tasks_G[j] = SCH_tasks_G[j + 1];
//                }
//                // Giảm số lượng task hiện tại và reset slot cuối cùng
//                current_index_task--;
//                SCH_tasks_G[current_index_task].pTask = 0;
//                SCH_tasks_G[current_index_task].Delay = 0;
//                SCH_tasks_G[current_index_task].Period = 0;
//                SCH_tasks_G[current_index_task].RunMe = 0;
//                SCH_tasks_G[current_index_task].TaskID = -1;
//                i--;  // Điều chỉnh lại chỉ số để tránh bỏ qua task
//            }
//        }
//    }
//}
