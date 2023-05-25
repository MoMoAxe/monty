#include "monty.h"

/**
 * is_number - This will check if string is a number
 * @str: The string to be checked
 * Return: 1 for true and 0 for false
 */
int is_number(char *str)
{
	int i;

	if (str == NULL)
		return (0);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '-' && i == 0)
			continue;
		if (isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

/**
 * free_stack - this is to free a stack
 * @stack: the pointer to stack
 * Return: NULL or void
 */
void free_stack(_stack_t *stack)
{
	_stack_t *current = stack;

	while (current != NULL)
	{
		current = current->next;
		free(stack);
		stack = current;
	}
}

/**
 * free_all - This functionm frees a stack and a file
 * @stack: The pointer to stack
 * @file: The pointer to file
 * Return: Null 0r void
 */
void free_all(_stack_t *stack, FILE *file)
{
	free_stack(stack);
	fclose(file);
}

/**
 * get_op_func - This will select the correct function to perform the operation
 * @s: the operator passed as an argument
 * Return: The pointer to the function relating to the operator
 */
void (*get_op_func(char *s))(_stack_t **stack, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{NULL, NULL}
	};
	int i;

	for (i = 0; ops[i].opcode != NULL; i++)
	{
		if (strcmp(ops[i].opcode, s) == 0)
			return (ops[i].f);
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", global.line_number, s);
	free_all(global.stack, global.file);
	exit(EXIT_FAILURE);
}

/**
 * split - This function will split a string into tokens
 * @str: the string to split
 * @delim: the delimiter/what is used to split
 * Return: A pointer to an array of stringss
 */
char **split(char *str, char *delim)
{
	char **tokens = NULL;
	char *token = NULL;
	int i = 0, j;

	tokens = malloc(sizeof(char *) * 3);
	if (tokens == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_all(global.stack, global.file);
		exit(EXIT_FAILURE);
	}

	token = strtok(str, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, delim);
		i++;
	}

	for (j = 0; j < i; j++)
	{
		if (tokens[j][0] == '#')
		{
			tokens[j] = NULL;
			break;
		}
	}

	return (tokens);
}
