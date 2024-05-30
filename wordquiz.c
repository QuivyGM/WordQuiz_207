#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

// Add custom strndup function
char *custom_strndup(const char *s, size_t n)
{
	size_t len = strnlen(s, n);
	char *new = malloc(len + 1);
	if (new == NULL)
		return NULL;
	new[len] = '\0';
	return memcpy(new, s, len);
}

// Defines enumeration for command types
typedef enum
{
	C_ZERO, // Zero command
	C_LIST, // List command
	C_SHOW, // Show command
	C_TEST, // Test command
	C_EXIT, // Exit command
} command_t;

// Function to read line from file
char *read_a_line(FILE *fp)
{
	// Buffer to hold the line
	static char buf[BUFSIZ];
	// Size of the buffer
	static int buf_n = 0;
	// Current position in the buffer
	static int curr = 0;

	// If reach end of the file -> return null
	if (feof(fp) && curr == buf_n - 1)
		return 0x0;

	// Pointer to line string
	char *s = 0x0;
	// Length of line string
	size_t s_len = 0;

	// Loop: Read line from buffer
	do
	{
		// Set end of line to current position
		int end = curr;
		//
		while (!(end >= buf_n || !iscntrl(buf[end])))
		{
			end++;
		}

		// If the current position is less than the end and line string is not null, break the loop
		if (curr < end && s != 0x0)
		{
			curr = end;
			break;
		}

		// Set the current position to the end
		curr = end;

		// increase end position until (end of the buffer) or (control character)
		while (!(end >= buf_n || iscntrl(buf[end])))
		{
			end++;
		}
		// If the current position is less than the end
		if (curr < end)
		{
			// If the line string is null
			if (s == 0x0)
			{
				// Allocate memory for the line string and copy the line from the buffer
				s = custom_strndup(buf + curr, end - curr);
				s_len = end - curr;
			}
			else
			{ // If line string is not null
				s = realloc(s, s_len + end - curr + 1);
				s = strncat(s, buf + curr, end - curr);
				s_len = s_len + end - curr;
			}
		}
		if (end < buf_n)
		{ // If end is less than buffer size
			curr = end + 1;
			break;
		}

		buf_n = fread(buf, 1, sizeof(buf), fp); // Read buffer from file
		curr = 0;								// Set current position to 0
	} while (buf_n > 0); // Loop until buffer size is greater than 0
	return s; // Return line string
}

void print_menu()
{ // Print menu

	printf("1. List all wordbooks\n");
	printf("2. Show the words in a wordbook\n");
	printf("3. Test with a wordbook\n");
	printf("4. Exit\n");
}

// Fixed the error whens gets char, it never ends.
int get_command()
{ // Get command
	int cmd;

	char buffer[10];

	printf(">");
	while (1)
	{
		if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
			if (sscanf(buffer, "%d", &cmd) == 1 && cmd >= 1 && cmd <= 4)
				return cmd;
			else
				printf("Invalid input. Please enter a number between 1 and 4.\n>");
		}
		else
			printf("Input error. Please try again.\n>");
	}
}
void list_wordbooks()
{ // List wordbooks

	DIR *d = opendir("wordbooks"); // Open directory

	printf("\n  ----\n");

	struct dirent *wb; // Wordbook
	while ((wb = readdir(d)) != NULL)
	{ // Read directory
		if (strcmp(wb->d_name, ".") != 0 && strcmp(wb->d_name, "..") != 0)
		{								  // If the name is not "." or ".."
			printf("  %s\n", wb->d_name); // Print name
		}
	}
	closedir(d); // Close directory

	printf("  ----\n");
}

void show_words()
{						// Show words
	char wordbook[128]; // Wordbook
	char filepath[256]; // File path

	list_wordbooks(); // List wordbooks

	printf("Type in the name of the wordbook?\n");
	printf(">");
	scanf("%s", wordbook); // 단어장 입력

	sprintf(filepath, "wordbooks/%s", wordbook); // Set file path

	FILE *fp = fopen(filepath, "r"); // Open file

	printf("\n  -----\n");

	char *line; // Array of characters
	while (line = read_a_line(fp))
	{										// Read line from file
		char *word = strtok(line, "\"");	// word : string (strtok: divide string)
		strtok(NULL, "\"");					// Divide string
		char *meaning = strtok(NULL, "\""); // meaning : string (strtok: divide string)

		printf("  %s : %s\n", word, meaning); // Print word and meaning

		free(line); // Free string
	}
	printf("  -----\n\n");

	fclose(fp); // Close file
}

void run_test()
{
	char wordbook[128]; // wordbook
	char filepath[256]; // file path

	printf("Type in the name of the wordbook?\n");
	printf(">");
	scanf("%s", wordbook);

	sprintf(filepath, "wordbooks/%s", wordbook); // Set file path

	FILE *fp = fopen(filepath, "r"); // Open file

	printf("\n-----\n");

	int n_questions = 0; // Number of questions
	int n_correct = 0;	 // Number of correct answers

	char *line; // Array of characters (*한 이유는 문자열을 나누기 위해)
	while (line = read_a_line(fp))
	{										// Read line from file while line is not null
		char *word = strtok(line, "\"");	// word : string (strtok: divide string)
		strtok(NULL, "\"");					// Divide string
		char *meaning = strtok(NULL, "\""); // meaning : string (strtok: divide string)

		printf("Q. %s\n", meaning); // Print question
		printf("?  ");				// Print question mark

		char answer[128];	 // Answer
		scanf("%s", answer); // Input answer

		if (strcmp(answer, word) == 0)
		{ // If the answer is correct
			printf("- correct\n");
			n_correct++; // Increase the number of correct answers
		}
		else
		{ // If the answer is wrong
			printf("- wrong: %s\n", word);
		}

		n_questions++; // Increase the number of questions
		free(line);	   // Free string
	}

	printf("(%d/%d)\n", n_correct, n_questions); // Print the number of correct answers and questions

	printf("-----\n\n");

	fclose(fp); // Close file
}

int main()
{

	printf(" *** Word Quiz *** \n\n");

	int cmd; // Command
	do
	{
		print_menu(); // Print menu

		cmd = get_command(); // Get command
		switch (cmd)
		{
		case C_LIST:
		{ // List wordbooks
			list_wordbooks();
			break;
		}

		case C_SHOW:
		{ // Show words
			show_words();
			break;
		}

		case C_TEST:
		{ // Workbook test
			run_test();
			break;
		}

		case C_EXIT:
		{ // Exit
			return EXIT_SUCCESS;
		}
		// If the command is not valid, then should get it again.
		default:
		{
			printf("Invalid command\n");
			break;
		}
		}
	} while (cmd != C_EXIT); // Loop until the command is not exit
	return EXIT_SUCCESS;
}