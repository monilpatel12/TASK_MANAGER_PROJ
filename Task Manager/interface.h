#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

void displayMenu();							// Display the main menu to the user
char* getInput();							// Get input from the user
int validateInput(char* input);				// Validate the user's input to ensure it's within the allowed range
void displayTaskList();						// Display the list of tasks
void displayTaskDetails(Task* task);		// Display details of a specific task
void displayErrorMessage(char* message);	// Display error messages to the user
void displaySuccessMessage(char* message);	// Display success messages to the user

#endif
 