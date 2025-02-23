# Cooperative Scheduler

## Overview

- **Purpose:** Designed and implemented a cooperative scheduler to accurately provide timeouts and trigger activities.
- **Platform:** Independently developed on the STM32 platform.
- **Task Management:** Supports both periodic and one-shot tasks.

## Core Functionalities

- **Task Operations:**
  - Addition of tasks
  - Deletion of tasks
  - Dispatching of tasks
- **Timer-Based Updates:**
  - Updates with 10ms accuracy

## Technical Insights

- **Scheduler Data Structures:**
  - Utilized buffers for task management.
  - Employed O(1) search in the `SCH_Update()` function.
 
## DEMO

![Image](https://github.com/user-attachments/assets/40d1b5d7-be20-48f8-ae6c-ee4122d3288a)

In the demo above, you can observe:
- **Task 0 (LED1):** Activates after 500ms and repeats every 500ms.
- **Task 1 (LED2):** Activates after 1000ms and repeats every 1000ms.
- **Task 2 (LED3):** Added but later removed, so it does not execute.
- **Task 3 (LED4):** Activates after 2000ms and repeats every 2000ms.
- **Task 4 (LED5):** Activates after 2500ms and repeats every 2500ms.

## Author
<div align="center">
<a href="https://github.com/NgqvngVinh" target="_blank">
  <img src="https://github.com/NgqvngVinh.png" alt="Avatar của tôi" width="60" style="border-radius: 50%;">
</a>
</div>
