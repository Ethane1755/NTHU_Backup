#include <stdio.h>
#include <string.h>

int isUsed[15];
char solution[15];
int length;
char str[15];

void Perm(int k, int n)
{
	char head = '0';
	int i;

	if(k == n)
	{
		solution[length] = '\0';
		printf("%s\n", solution);
		return;
	}

	for (i = 0; i < n; i++)
	{
		if(!isUsed[i] && str[i] != head)
		{
			isUsed[i] = 1;
			head = str[i];
			solution[k] = str[i];
			Perm(k+1, n);
			isUsed[i] = 0;
		}
	}
}

void Sort()
{
	int letters[26] = {0};
	int i, j, count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		letters[str[i] - 'a']++;
		isUsed[i] = 0;
	}
	for (i = 0; i < 26; i++)
	{
		for (j = 0; j < letters[i]; j++)
		{
			str[count++] = i + 'a';
		}
	}

	length = count;

	return;
}

int main(int argc, char const *argv[])
{
	scanf("%s", str);

	Sort();

	Perm(0, length);

	return 0;
}
