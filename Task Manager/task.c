#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

int isTasksModified = 0;
Task taskList[100] = { 0 }; // Assuming a maximum of 100 tasks
int taskCount = 0;          // Keeps track of the current task count

void initializeTaskManager() {
    // Initialize the task manager, resetting the task count
    taskCount = 0;
}

Task* createTask(char* name, char* deadline, int priority) {
    // Create a new task with given attributes
    Task* new_task = &taskList[taskCount++];
    strcpy_s(new_task->name, NAME_MAX_LENGTH, name);
    strcpy_s(new_task->deadline, DEADLINE_MAX_LENGTH, deadline);
    new_task->priority = priority;
    new_task->isCompleted = 0;
    isTasksModified = 1;
    return new_task;
}

void editTask(Task* task, char* name, char* deadline, int priority) {
    // Check if the task list is empty
    if (taskCount == 0) {
        printf("The task list is empty. Nothing to edit.\n");
        return;
    }

    // Check if the task is null
    if (task == NULL) {
        printf("Invalid task. Cannot edit.\n");
        return;
    }

    // Edit a task with given attributes
    strcpy_s(task->name, sizeof(task->name), name);
    strcpy_s(task->deadline, sizeof(task->deadline), deadline);
    task->priority = priority;
    isTasksModified = 1;
}

void deleteTask(int taskIndex) {
    // Check if the task list is empty
    if (taskCount == 0) {
        printf("The task list is empty. Nothing to delete.\n");
        return;
    }

    // Check if the taskIndex is valid
    if (taskIndex < 0 || taskIndex >= taskCount) {
        printf("Invalid task index. Cannot delete.\n");
        return;
    }

    // Delete a task by shifting all subsequent tasks one position up
    for (int i = taskIndex; i < taskCount - 1; i++) {
        taskList[i] = taskList[i + 1];
    }
    taskCount--;
    isTasksModified = 1;
}

void markTaskAsComplete(Task* task) {
    // Check if the task list is empty
    if (taskCount == 0) {
        printf("The task list is empty. Nothing to mark as complete.\n");
        return;
    }

    // Check if the task is null
    if (task == NULL) {
        printf("Invalid task. Cannot mark as complete.\n");
        return;
    }

    // Mark a task as completed
    task->isCompleted = 1;
}

void viewTaskDetails(Task* task) {
    // Display the details of a task
    printf("Task Name: %s\n", task->name);
    printf("Deadline: %s\n", task->deadline);
    printf("Priority: %d\n", task->priority);
    printf("Status: %s\n", task->isCompleted ? "Complete" : "Incomplete");
}

void sortTasks() {
    // This function will sort tasks based on your criteria
    printf("This function will sort tasks based on your criteria.\n");
}

/*Task* searchTasks(char* name) {
    // Search for a task by name
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(taskList[i].name, name) == 0) {
            return &taskList[i];
        }
    }
    return NULL;
} */

void saveTasksToFile() {
    // Save all tasks to a file
    FILE* file;
    errno_t err = fopen_s(&file, "tasks.txt", "w");
    if (err != 0 || file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s,%s,%d,%d\n", taskList[i].name, taskList[i].deadline, taskList[i].priority, taskList[i].isCompleted);
    }
    fclose(file);
    isTasksModified = 0;
}

void loadTasksFromFile() {
    FILE* file;
    errno_t err = fopen_s(&file, "tasks.txt", "r");
    if (err != 0 || file == NULL) {
        printf("Error: Could not open file for reading.\n");
        return;
    }

    char buffer[255];
    char* next_token = NULL;
    while (fgets(buffer, 255, file)) {
        char* name = strtok_s(buffer, ",", &next_token);
        char* deadline = strtok_s(NULL, ",", &next_token);
        char* priority_str = strtok_s(NULL, ",", &next_token);
        char* isCompleted_str = strtok_s(NULL, ",", &next_token);

        if (!name || !deadline || !priority_str || !isCompleted_str) {
            printf("Error: Line format incorrect.\n");
            continue; 
        }

        int priority = atoi(priority_str);
        int isCompleted = atoi(isCompleted_str);

        Task* task = createTask(name, deadline, priority);
        task->isCompleted = isCompleted;
    }
    fclose(file);
}

