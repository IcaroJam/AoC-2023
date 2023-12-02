#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	char	*tmp = NULL;
	size_t	n = 0;
	ssize_t	len = 0; // This one happens to be signed. It was previously a size_t, resulting in good 'ol segfaults.
	FILE	*inFile;
	size_t	retVal = 0;

	inFile = fopen("./input.txt", "r");
	if (!inFile)
		return (fprintf(stderr, "Failed to open the input file.\n"));

	len = getline(&tmp, &n, inFile); // Like with a normal read, the amount of bytes actually read is returned. The amount of memory allocated is stored in 'n'.
	while (len > 0)
	{
		int	firstnum = 0, lastnum = 0;

		for (int i = 0; i < len; i++)
		{
			if (isdigit(tmp[i]))
			{
				firstnum = tmp[i] - '0';
				break;
			}
		}
		for (--len; len >= 0; len--)
		{
			if (isdigit(tmp[len]))
			{
				lastnum = tmp[len] - '0';
				break;
			}
		}
		retVal += firstnum * 10 + lastnum;
		free(tmp); // The line given to getline must be manually freed.
		tmp = NULL; // If the pointer passed to getline is NULL it will take care of allocation.
		len = getline(&tmp, &n, inFile);
	}
	free(tmp);
	printf("The calibration value of the given document is: %lu\n", retVal);
	return (0);
}
