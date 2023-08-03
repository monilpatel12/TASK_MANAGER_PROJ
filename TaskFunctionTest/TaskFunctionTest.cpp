#include "pch.h"
#include "CppUnitTest.h"
#include "task.h"
#include "task.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskFunctionTest
{
	TEST_CLASS(TaskFunctionTest)
	{
	public:
		
		TEST_METHOD(Test_initializeTaskManager)
		{
			// Test initializeTaskManager
			initializeTaskManager();

			// Check that taskCount has been reset to 0
			Assert::AreEqual(0, taskCount);
		}

		TEST_METHOD(Test_CreateTask)
		{
			// Test createTask
			// Arrange
			char name[] = "Sample Task";
			char deadline[] = "01/01/2023";
			int priority = 1;

			// Act
			Task* task = createTask(name, deadline, priority);

			// Assert
			// Check that task has been created with correct attributes
			Assert::AreEqual(name, task->name);
			Assert::AreEqual(deadline, task->deadline);
			Assert::AreEqual(priority, task->priority);
			// Check that taskCount has been incremented by 1
			Assert::AreEqual(1, taskCount);
		}

		TEST_METHOD(Test_editTask)
		{
			// Test editTask
			// Arrange
			initializeTaskManager();
			char name[] = "Sample Task";
			char deadline[] = "01/01/2023";
			int priority = 1;
			Task* task = createTask(name, deadline, priority);

			char newName[] = "Edited Task";
			char newDeadline[] = "02/02/2023";
			int newPriority = 2;

			// Act
			editTask(task, newName, newDeadline, newPriority);

			// Assert
			// Check that task has been edited with correct attributes
			Assert::AreEqual(newName, task->name);
			Assert::AreEqual(newDeadline, task->deadline);
			Assert::AreEqual(newPriority, task->priority);
		}

		TEST_METHOD(Test_viewTaskDetails)
		{
			// Create a task
			Task task;
			strcpy_s(task.name, sizeof(task.name), "Test Task");
			strcpy_s(task.deadline, sizeof(task.deadline), "2022-12-31");
			task.priority = 5;
			task.isCompleted = 0;

			// Redirect stdout to a temporary file
			FILE* original_stdout = stdout;
			FILE* tempFile;
			freopen_s(&tempFile, "temp.txt", "w", stdout);

			// Call the function
			viewTaskDetails(&task);

			// Close the temporary file
			fclose(tempFile);

			// Open the temporary file for reading
			FILE* file;
			errno_t err = fopen_s(&file, "temp.txt", "r");
			if (err != 0 || file == NULL) {
				Assert::Fail(L"Failed to open the temporary file.");
				return;
			}

			char buffer[1024] = { 0 }; 
			char line[255];
			while (fgets(line, 255, file)) {
				strcat_s(buffer, 1024, line);
			}

			fclose(file);

			// Check the results
			std::string expected = "Task Name: Test Task\nDeadline: 2022-12-31\nPriority: 5\nStatus: Incomplete\n";
			Assert::AreEqual(expected, std::string(buffer));
		}
	};
}
