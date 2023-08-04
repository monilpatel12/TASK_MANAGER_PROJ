#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "interface.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
    initializeTaskManager(); // Initialize the task manager
    loadTasksFromFile();     // Load tasks from file if available

    while (1) {
        displayMenu(); // Display the main menu

        char* input = getInput();    // Get user choice
        if (!validateInput(input)) {
            displayErrorMessage("Invalid input, please try again.");
            continue;
        }

        int choice = atoi(input);
        free(input);

        // Process the user choice
        if (choice == 1) {
            // Create a new task
            printf("Enter task name: ");
            char* name = getInput();

            printf("Enter deadline: ");
            char* deadline = getInput();

            printf("Enter priority (1,2,3,etc...): ");
            char* priority_str = getInput();
            int priority = atoi(priority_str);
            free(priority_str);

            createTask(name, deadline, priority);
            displaySuccessMessage("Task created successfully.");
        }
        else if (choice == 2) {
            displayTaskList();  // Edit an existing task

            printf("Enter the number of the task to edit: ");
            char* taskIndex_str = getInput();
            int taskIndex = atoi(taskIndex_str) - 1;
            free(taskIndex_str);

            if (taskIndex < 0 || taskIndex >= taskCount) {
                displayErrorMessage("Invalid task number.");
                continue;
            }

            printf("Enter new task name: ");
            char* name = getInput();

            printf("Enter new deadline: ");
            char* deadline = getInput();

            printf("Enter new priority: ");
            char* priority_str = getInput();
            int priority = atoi(priority_str);
            free(priority_str);

            editTask(&taskList[taskIndex], name, deadline, priority);
            displaySuccessMessage("Task edited successfully.");
        }
        else if (choice == 3) {
            displayTaskList();  // Delete a task

            printf("Enter the number of the task to delete: ");
            char* taskIndex_str = getInput();
            int taskIndex = atoi(taskIndex_str) - 1;
            free(taskIndex_str);

            if (taskIndex < 0 || taskIndex >= taskCount) {
                displayErrorMessage("Invalid task number.");
                continue;
            }

            deleteTask(taskIndex); 
            displaySuccessMessage("Task deleted successfully.");
        }
        else if (choice == 4) {
            displayTaskList();  // Mark a task as complete

            printf("Enter the number of the task to mark as complete: ");
            char* taskIndex_str = getInput();
            int taskIndex = atoi(taskIndex_str) - 1;
            free(taskIndex_str);

            if (taskIndex < 0 || taskIndex >= taskCount) {
                displayErrorMessage("Invalid task number.");
                continue;
            }

            markTaskAsComplete(&taskList[taskIndex]);
            displaySuccessMessage("Task marked as complete.");
        }
        else if (choice == 5) {
            if (taskCount == 0) {   // View details of a task
                displayErrorMessage("No tasks available to view.");
                continue;
            }
            displayTaskList();

            printf("Enter the number of the task to view details: ");
            char* taskIndex_str = getInput();
            int taskIndex = atoi(taskIndex_str) - 1;
            free(taskIndex_str);

            if (taskIndex < 0 || taskIndex >= taskCount) {
                displayErrorMessage("Invalid task number.");
                continue;
            }

            viewTaskDetails(&taskList[taskIndex]);
        }
        else if (choice == 6) {
            // Save tasks to file
            saveTasksToFile();
            displaySuccessMessage("Tasks saved successfully.");
        }
        else if (choice == 7) {
            // Load tasks from file
            loadTasksFromFile();
            displaySuccessMessage("Tasks loaded successfully.");
        }
        else if (choice == 8) {
            // Exit the application
            // Check for unsaved changes and offer to save them before exiting
            if (isTasksModified) {
                printf("There are unsaved changes. Do you want to save before exiting? (y/n): ");
                char* saveChoice = getInput();
                if (strcmp(saveChoice, "y") == 0 || strcmp(saveChoice, "Y") == 0) {
                    saveTasksToFile();
                    displaySuccessMessage("Tasks saved successfully.");
                }
                free(saveChoice);
            }
            break;   
        }
    }

    return 0;
}
