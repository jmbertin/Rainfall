#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	unsigned char local_98[66];
	unsigned char local_56[66];
	FILE *local_14;

	local_14 = fopen("/home/user/end/.pass","r");
	if (local_14 == NULL || argc != 2)
		return -1;
	else
	{
		fread(local_98,1,66,local_14);
		local_98[65] = 0; // Ensure null termination
		int index = atoi(argv[1]);
		local_98[index] = 0;
		fread(local_56,1,65,local_14);
		local_56[65] = 0; // Ensure null termination
		fclose(local_14);
		if (strcmp((char *)local_98,argv[1]) == 0)
			execl("/bin/sh","sh",0);
		else
			puts((char *)local_56);
		return 0;
	}
}
