#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int*	authenticationStatus = NULL;
char*	serviceName = NULL;

int	main(void)
{
	char	inputBuffer[128];
	char	authenticationString[128];
	char	*input;

	while (true)
	{
		printf("%p, %p \n",authenticationStatus, serviceName);
		input = fgets(inputBuffer, sizeof(inputBuffer), stdin);
		if (input == NULL)
			break;
		if (strncmp(inputBuffer, "auth ", 5) == 0)
		{
			authenticationStatus = malloc(4);
			if (authenticationStatus == NULL)
			{
				fprintf(stderr, "Failed to allocate memory for authenticationStatus.\n");
				return 1;
			}
			*authenticationStatus = 0;
			strncpy(authenticationString, inputBuffer + 5, sizeof(authenticationString) - 1);
			if (strlen(authenticationString) < 30)
				strcpy((char*)authenticationStatus, authenticationString);
		}

		else if (strncmp(inputBuffer, "reset", 5) == 0)
		{
			free(authenticationStatus);
			authenticationStatus = NULL;
		}

		else if (strncmp(inputBuffer, "service", 7) == 0)
		{
			serviceName = strdup(inputBuffer + 8);
			if (serviceName == NULL)
			{
				fprintf(stderr, "Failed to allocate memory for serviceName.\n");
				return 1;
			}
		}

		else if (strncmp(inputBuffer, "login", 5) == 0)
		{
			if (authenticationStatus != NULL)
			{
				if ((int)serviceName - (int)authenticationStatus == 32)
					system("/bin/sh");
				else
					fwrite("Password:\n", 1, 10, stdout);
			}
		}
	}
	free(authenticationStatus);
	free(serviceName);
	return 0;
}
