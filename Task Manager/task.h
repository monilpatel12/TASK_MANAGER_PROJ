#pragma once
#ifndef TASK_H
#define TASK_H
#define NAME_MAX_LENGTH 500
#define DEADLINE_MAX_LENGTH 30

// Task structure definition
typedef struct {
    char name[NAME_MAX_LENGTH];     // Task name
    char deadline[DEADLINE_MAX_LENGTH];  // Task deadline
    int priority;       // Task priority
    int isCompleted;    // Task completion status
} Task;

void initializeTaskManager();            // Initialize the task manager
Task* createTask(char* name, char* deadline, int priority);             // Create a new task
void editTask(Task* task, char* name, char* deadline, int priority);    // Edit an existing task
void deleteTask(Task* task);             // Delete a task
void markTaskAsComplete(Task* task);     // Mark a task as complete
void viewTaskDetails(Task* task);        // View the details of a specific task
void sortTasks();                        // Sort the tasks
Task* searchTasks(char* name);           // Search for tasks by name
void saveTasksToFile();                  // Save tasks to a file
void loadTasksFromFile();                // Load tasks from a file

extern int isTasksModified;              // Global variable to track if tasks have been modified
extern Task taskList[100];               // Global variable for the task list
extern int taskCount;                    // Global variable for the task count

#endif 
