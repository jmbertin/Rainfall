#include <string.h>
#include <stdio.h>
#include <unistd.h>

char global_buffer[4096] = " - ";

void p(char *destination, char *message)
{
	char	*nl_ptr;
	char	input_buffer [4104];

	puts(message);
	read(0,input_buffer,4096);
	nl_ptr = strchr(input_buffer, '\n');
	*nl_ptr = '\0';
	strncpy(destination, input_buffer, 20);
	return;
}

void pp(char *buffer)
{
	char			current_char;
	unsigned int	counter;
	char			*buffer_ptr;
	char			bVar4 = 0;
	char			first_line [20];
	char			second_line [20];

	p(first_line, global_buffer);
	p(second_line, global_buffer);
	strcpy(buffer, first_line);
	counter = 4294967295; // equiv -1 for unsigned int
	buffer_ptr = buffer;
	while (current_char != '\0')
	{
		if (counter == 0)
			break;
		counter = counter - 1;
		current_char = *buffer_ptr;
		buffer_ptr = buffer_ptr + (unsigned int)bVar4 * -2 + 1;
	}
	buffer[strlen(buffer)] = ' ';
	strcat(buffer, second_line);
	return;
}

int main(void)
{
	char	buffer[54];

	pp(buffer);
	puts(buffer);
	return 0;
}
