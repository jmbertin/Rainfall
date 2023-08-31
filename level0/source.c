#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int param_1, char **argv)
{
	int		iVar1;
	char	*local_20;
	uid_t	local_18;
	gid_t	local_14;

	iVar1 = atoi(argv[1]);
	if (iVar1 == 423)
	{
		local_20 = strdup("/bin/sh");
		local_14 = getegid();
		local_18 = geteuid();
		setresgid(local_14, local_14, local_14);
		setresuid(local_18, local_18, local_18);
		execv("/bin/sh", &local_20);
	}
	else
		write(2, "No !\n", 5);
	return (0);
}
