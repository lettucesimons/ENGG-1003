#include <stdio.h>

int strlng (char *str);
int main()	{
	int n=0;
	char str[1024];
	char key[1024];
	int c = 0;
	FILE *input;
	input = fopen("data", "r");
	if (input==NULL)	{
	perror("fopen()");
	return 0;
	}
	for(n=0; n<1024; n++)	{
		fscanf(input, "%c", &key[n]);
		if (key[n] == 10)	{ 
			key[n] = 0; 
			break;
		}
	}	
	
	for(n=0; n<1024; n++)	{
		fscanf(input, "%c", &str[n]);
		if (str[n] == 10)	{ 
			str[n] = 0; 
			break;
		}
	}	
	printf("%s \n", key);
	printf("PHRASE:%s\n", str);
	for(n=0;n<strlng(str);n++)	{
		if (str[n]<91 && str[n]>64) // uppercase
			str[n] = ((str[n]-64+(key[5]-48))%26)+64; /* converts ASCII to letters 1-26 by subtracting 64 then adds k to perform the encryption and returns the number back to its ASCII by adding 64 */
		if (str[n]<123 && str[n]>96) // lowercase
			str[n] = ((str[n]-97+(key[5]-48))%26)+97; // same as uppercase
	}
	printf("Encrypted phrase: %s\n", str);
return 0;
}

int strlng (char *str)	{
	int n = 0;
	while (str[n]!=0)
		n++;
return n;
}

