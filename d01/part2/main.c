#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *numDict[10] = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	NULL
};

int	isDictNum(const char *tmp, int *dIndex)
{
	for (int i = 0; numDict[i]; i++)
	{
		if (!strncmp(numDict[i], tmp, strlen(numDict[i])))
		{
			*dIndex = i;
			return (1);
		}
	}
	return (0);
}

int getFirstNum(const char *tmp, ssize_t len)
{
	int	ret = 0;
	int	dIndex;

	for (int i = 0; i < len; i++)
	{
		if (isdigit(tmp[i]))
		{
			ret = tmp[i] - '0';
			break;
		}
		else if (isDictNum(&tmp[i], &dIndex))
		{
			ret = dIndex + 1;
			break;
		}
	}
	return (ret);
}

int getLastNum(const char *tmp, ssize_t len)
{
	int	ret = 0;
	int	dIndex;

	for (int i = 0; i < len; i++)
	{
		if (isdigit(tmp[i]))
			ret = tmp[i] - '0';
		else if (isDictNum(&tmp[i], &dIndex))
			ret = dIndex + 1;
	}
	return (ret);
}

int main()
{
	char	*tmp = NULL;
	size_t	n = 0;
	ssize_t	len = 0; // This one happens to be signed. It was previously a size_t, resulting in good 'ol segfaults.
	FILE	*inFile;
	size_t	retVal = 0;

	inFile = fopen("../input.txt", "r");
	if (!inFile)
		return (fprintf(stderr, "Failed to open the input file.\n"));

	len = getline(&tmp, &n, inFile); // Like with a normal read, the amount of bytes actually read is returned. The amount of memory allocated is stored in 'n'.
	while (len > 0)
	{
		int	firstnum = getFirstNum(tmp, len);
		int	lastnum = getLastNum(tmp, len);

		retVal += firstnum * 10 + lastnum;
		free(tmp); // The line given to getline must be manually freed.
		tmp = NULL; // If the pointer passed to getline is NULL it will take care of allocation.
		len = getline(&tmp, &n, inFile);
	}
	free(tmp);
	printf("The calibration value of the given document is: %lu\n", retVal);
	return (0);
}
