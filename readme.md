# OS LAB ASSIGNMENT

# (Aniruddha Date)

1. IMP_FUNCTIONS.h contains all necessary functions and structures for all other algorithms that are implemented.
2. random_process.c generates the required number of processes based on user input.
3. ROUND_ROBIN.c implements round robin algorithm with given quanta.
4. SHORTEST_JOB_FIRST.c implements shortest job first algorithm.
5. SHORTEST_REMAINING_TIME_FIRST.c implements shortest remaining time first algorithm.
6. SRTF_WITH_PRIORITY.c implements shortest remaining time first with priority assigned to each process.
7. Scheduler.c runs all algorithms one by one

**DETAILED DESCRIPTION IS BELOW**

# IMP_FUNCTIONS.h
**Features:**
- Process Struct: Defines a structure to hold information about processes including arrival time, CPU burst, I/O call, I/O burst, response time, completion time, waiting time, turnaround time, remaining time, time slice, and queue arrival times.
- Ready Queue and Waiting Queue: Implements structures to manage the ready queue and waiting queue of processes.
- Schedulers: Implements three types of schedulers:
- Long Term Scheduler: Responsible for admitting new processes into the system and adding them to the ready queue based on arrival time.
- Short Term Scheduler: Selects a process from the ready queue to run on the CPU based on a scheduling policy.
- Mid Term Scheduler: Decides whether a process should be in the ready queue or waiting queue based on its state and available resources.
**Functions:**
- intialize(): Reads process information from an input file, initializes process structures, and returns the number of processes read.
- job_schedule(int n): Creates a job queue and sorts it based on process arrival time.
- long_term_scheduler(int n, int time): Admits new processes into the system and adds them to the ready queue.
- short_term_scheduler(int time): Selects a process from the ready queue to run on the CPU.
- mid_term_scheduler(int time, int x): Decides whether a process should be in the ready queue or waiting queue.
- calculate(int n): Calculates and prints average waiting time, turnaround time, and response time for all processes.
**Utility Functions:**
- Includes utility functions like min, swap, and file handling functions.

# ROUND_ROBIN.c

## Overview
ROUND_ROBIN.c is a C program that implements the Round Robin scheduling algorithm. It simulates the scheduling of processes in an operating system environment using the Round Robin technique, which is a preemptive algorithm commonly used in CPU scheduling.

## Features
- **Round Robin Scheduling:** The program implements the Round Robin scheduling algorithm, which ensures that each process gets an equal share of CPU time.
- **Process Management:** Processes are managed efficiently with functions for inserting, removing, and updating their status in various queues.
- **Scheduler:** The program includes short-term, mid-term, and long-term schedulers to handle process scheduling at different levels.
- **Statistics Calculation:** The program calculates various statistics for the executed processes, including response time, waiting time, and completion time.

## Usage
1. **Compilation:** Compile the program using a C compiler. For example: gcc ROUND_ROBIN.c -o ROUND_ROBIN
2. **Run:**./ROUND_ROBIN

# Shortest Job First (SJF) Scheduler

## Introduction
This program simulates the Shortest Job First (SJF) scheduling algorithm in an operating system environment. SJF is a non-preemptive scheduling algorithm that selects the process with the smallest execution time to execute next.

## Files
- `SHORTEST_JOB_FIRST.c`: Contains the implementation of the SJF scheduler.
- `IMP_FUNCTIONS.h`: Header file containing necessary data structures and function prototypes.
- `README.md`: This file, providing an overview of the program.

## Compilation and Execution
To compile the program, use any C compiler such as gcc:

```bash```
gcc SHORTEST_JOB_FIRST.c -o SHORTEST_JOB_FIRST
./SHORTEST_JOB_FIRST

**Program Flow**
1. Initialization: Reads input parameters and initializes necessary data structures.
2. Job Scheduling: Determines the scheduling order of processes based on their arrival times and burst times.
3. Execution: Simulates the execution of processes according to the SJF algorithm.
4. Calculation: Calculates and prints out various metrics such as waiting time, turnaround time, and response time.

# Shortest Remaining Time First (SRTF) Process Scheduling

## Description
This program implements the Shortest Remaining Time First (SRTF) process scheduling algorithm. SRTF is a preemptive scheduling algorithm where the process with the smallest amount of remaining time to completion is selected to execute next. This scheduling ensures that shorter processes are executed first, leading to reduced average waiting time.

## Program Files
- `SHORTEST_REMAINING_TIME_FIRST.c`: This file contains the implementation of the SRTF scheduling algorithm.
- `IMP_FUNCTIONS.h`: This header file contains necessary declarations and definitions required for the program.

## Compilation Instructions
To compile the program, use the following command:
```bash```
gcc SHORTEST_REMAINING_TIME_FIRST.c -o SRTF
./SRTF

Implementation Details
- The program consists of three main functions: mid_term_scheduler, long_term_scheduler, and short_term_scheduler.
- It maintains a ready queue and a wait queue to manage processes.
- Processes are moved between the ready queue, wait queue, and execution based on their remaining execution time and IO burst.

Sample Output:
Process 1 has entered into ready queue at time 0.
Process 2 has entered into ready queue at time 3.
Process 3 has entered into ready queue at time 5.
...
Process 1 terminated at time 12.
...

# Shortest Remaining Time First (SRTF) with Priority

## Overview

This program implements the Shortest Remaining Time First (SRTF) scheduling algorithm with priority handling. SRTF is a non-preemptive scheduling algorithm that selects the process with the smallest remaining burst time to execute next. Additionally, it incorporates priority scheduling, where processes with higher priority are given preference in execution.

## Files

- `SRTF_WITH_PRIORITY.c`: This file contains the source code for the SRTF scheduling algorithm with priority handling.
- `IMP_FUNCTIONS.h`: Header file containing necessary function prototypes and data structures.
- `README.md`: This file, providing an overview of the program and instructions for usage.

## Compilation and Execution

To compile the program, use the following command:

```bash```
gcc SRTF_WITH_PRIORITY.c -o SRTF_WITH_PRIORITY
./SRTF_WITH_PRIORITY

**Usage**
- Initialization: Modify the time_slice variable according to your requirements. This variable determines the time slice for each process.
- Input: Ensure the necessary input is provided, such as process details like arrival time, burst time, priority, etc.
- Compilation: Compile the source code using the provided compilation command.
- Execution: Execute the compiled program.
- Output: The program will output the scheduling and execution details of each process, including arrival time, completion time, response time, waiting time, etc.

