#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	language = 0;

int	greetuser(char *buffer2)
{
	unsigned char message[30];

	if (language == 1) // Finnish Hyvää päivää! -> good day
	{
		message[0] = 'H';
		message[1] = 'y';
		message[2] = 'v';
		message[3] = '\xc3';
		message[4] = '\xa4';
		message[5] = '\xc3';
		message[6] = '\xa4';
		message[7] = ' ';
		message[8] = 'p';
		message[9] = '\xc3';
		message[10] = '\xa4';
		message[11] = '\xc3';
		message[12] = '\xa4';
		message[13] = '!';
		message[14] = '\0';
	}
	else if (language == 2) // NL Goedemiddag! -> good afternoon
	{
		message[0] = 'G';
		message[1] = 'o';
		message[2] = 'e';
		message[3] = 'd';
		message[4] = 'e';
		message[5] = 'm';
		message[6] = 'i';
		message[7] = 'd';
		message[8] = 'd';
		message[9] = 'a';
		message[10] = 'g';
		message[11] = '!';
		message[12] = '\0';
		// CONCAT22 !!!
	}
	else if (language == 0) // English Hello!
	{
		message[0] = 'H';
		message[1] = 'e';
		message[2] = 'l';
		message[3] = 'l';
		message[4] = 'o';
		message[5] = '!';
		message[6] = '\0';
	}
	strcat(message, buffer2);
	puts(message);
	return (0);
}

int	main(int ac, char **av)
{
	int		return_value;
	int		counter;
	char	*buffer;
	char	*env_lang;
	char	*buffer2;

	char	copyFlag;

	copyFlag = 0;
	if (ac == 3)
	{
		bzero(buffer, 19);
		strncpy(buffer, av[1], 40); //useless
		strncpy(buffer + 40, av[2], 32);
		env_lang = getenv("LANG");
		if (env_lang != NULL)
		{
			if (memcmp(env_lang, "nl", 2) == 0)
				language = 1;
			else if (memcmp(env_lang, "fi", 2) == 0)
				language = 2;
		}
		memcpy(buffer2, buffer, 19); // not really memcpy, copy by the end of the buffer, so will be the last 19 bytes of argv[2]
		return_value = greetuser(buffer2);
	}
	else
		return_value = 1;
	return (return_value);
}
