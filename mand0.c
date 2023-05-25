#include "monty.h"

/**
 * _push - stack push function
 * @stack: A pointer to stack
 * @line_number: The line number
 * Return: NULL or void
 */
void _push(_stack_t **stack, unsigned int line_number)
{
	_stack_t *new_node = NULL;
	int number;

	if (stack == NULL)
	{
		fprintf(stderr, "L%d: stack not found\n", line_number);
		exit(EXIT_FAILURE);
	}

	if (is_number(global.line[1]) == 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	number = atoi(global.line[1]);

	new_node = malloc(sizeof(_stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_all(*stack, global.file);
		exit(EXIT_FAILURE);
	}

	new_node->n = number;
	new_node->prev = NULL;
	new_node->next = NULL;

	if (*stack != NULL)
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}

/**
 * _pall - prints all stack levels
 * @stack: A pointer to the stack
 * @line_number: The line number
 * Return: NULL or void
 */
void _pall(_stack_t **stack, unsigned int line_number)
{
	_stack_t *current = *stack;

	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
