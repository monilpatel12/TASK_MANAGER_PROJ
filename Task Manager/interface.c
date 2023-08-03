#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "interface.h"
#define _CRT_SECURE_NO_WARNINGS

// Function to display the main menu
void displayMenu() {
    printf("\n");
    printf("1. Create a new task\n");
    printf("2. Edit an existing task\n");
    printf("3. Delete a task\n");
    printf("4. Mark task as complete\n");
    printf("5. View task details\n");
    printf("6. Save tasks to file\n");
    printf("7. Load tasks from file\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

// Function to get input from the user
char* getInput() {
    char* input = (char*)malloc(100 * sizeof(char));
    if (input == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0'; // remove the newline character
    return input;
}

// Function to validate user's input
int validateInput(char* input) {
    int choice = atoi(input);
    return choice >= 1 && choice <= 8; // Now 8 options in the menu
}

// Function to display the list of tasks
// Iterate through the tasks and print them
void displayTaskList() {
    for (int i = 0; i < taskCount; i++) {
        printf("Task %d: %s\n", i + 1, taskList[i].name);
    }
}

// Function to display the details of a specific task
// Code to display task details
void displayTaskDetails(int taskIndex) {
    if (taskIndex < 0 || taskIndex >= taskCount) {
        printf("Invalid task number\n");
        return;
    }
    viewTaskDetails(&taskList[taskIndex]);
}

// Function to display error messages
void displayErrorMessage(char* message) {
    printf("Error: %s\n", message);
}

// Function to display success messages
void displaySuccessMessage(char* message) {
    printf("Success: %s\n", message);
}