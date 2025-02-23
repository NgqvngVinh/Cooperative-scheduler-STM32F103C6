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

## Author
<div align="center">
<a href="https://github.com/NgqvngVinh" target="_blank">
  <img src="https://github.com/NgqvngVinh.png" alt="Avatar của tôi" width="60" style="border-radius: 50%;">
</a>
</div>
