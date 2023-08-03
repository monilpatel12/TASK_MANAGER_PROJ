#include "pch.h"
#include "CppUnitTest.h"
#include "task.h"
#include "task.c"
#include "interface.c"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskInterfaceTest
{
	TEST_CLASS(TaskInterfaceTest)
	{
	public:
		
        TEST_METHOD(Test_loadTasksFromFile)
        {
            // Prepare a test file
            FILE* file;
            fopen_s(&file, "tasks.txt", "w");
            fprintf(file, "Task1,2023-08-03,1,0\n");
            fclose(file);

            // Initialize task manager
            initializeTaskManager();

            // Load tasks from the file
            loadTasksFromFile();

            // Verify the task loaded correctly
            Assert::AreEqual("Task1", taskList[0].name);
            Assert::AreEqual("2023-08-03", taskList[0].deadline);
            Assert::AreEqual(1, taskList[0].priority);
            Assert::AreEqual(0, taskList[0].isCompleted);
        }

        TEST_METHOD(Test_getInput)
        {
            // Simulate user input by writing to a temporary file
            FILE* file;
            fopen_s(&file, "temp_input.txt", "w");
            fprintf(file, "User Input Test\n");
            fclose(file);
            fclose(file); // Close the file after writing

            // Redirect standard input to the temporary file
            FILE* stream;
            freopen_s(&stream, "temp_input.txt", "r", stdin);

            // Call getInput
            char* input = getInput();

            // Verify the captured input
            Assert::AreEqual("User Input Test", input);

            // Free the allocated memory and close the file
            free(input);
            fclose(stream); // Close the redirected stdin

            // Restore standard input (optional, depending on your setup)
            freopen_s(&stream, "CON", "r", stdin);
            fclose(stream); // Close the restored stdin
        }

        TEST_METHOD(Test_saveTasksToFile)
        {
            // Initialize task manager and create a task
            initializeTaskManager();
            createTask("Task1", "2023-08-03", 1);

            // Save tasks to the file
            saveTasksToFile();

            // Read the file to verify the content
            FILE* file;
            char buffer[255];
            fopen_s(&file, "tasks.txt", "r");
            fgets(buffer, 255, file);
            fclose(file);

            // Verify the saved content
            Assert::AreEqual("Task1,2023-08-03,1,0\n", buffer);
        }
	};
}
