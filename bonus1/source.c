int main(int ac, char **av)
{
	int			return_value;
	char		buffer[40]; // -> +40 overflow
	int			av1_to_int;

	av1_to_int = atoi(av[1]);
	if (av1_to_int < 10)
	{
		memcpy(buffer, av[2], av1_to_int * 4);
		if (buffer == 0x574f4c46) // WOLF in text // 1464814662 in decimal
			execl("/bin/sh", "sh", 0);
		return_value = 0;
	}
	else
		return_value = 1;
	return (return_value);
}
