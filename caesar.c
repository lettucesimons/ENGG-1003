#include <stdio.h>

int strlng (char *str);
int main()	{
	
	char str[1024];
	int n = 0; 
	int c = 0;
	int k;
	
	printf("enter phrase\nPhrase: ");
	for (c=0;c<1024;c++){
		scanf("%c", &str[c]);
		if (str[c] == 10)
			break;
	str[c+1] = 0;
	}
	printf("enter encryption key between 1 and 25\n");
	scanf("%d", &k);
	for(;n<strlng(str);n++)	{
		if (str[n]<91 && str[n]>64) // uppercase
			str[n] = (str[n]-65+k)%26+65;
		if (str[n]<123 && str[n]>96) // lowercase
			str[n] = (str[n]-97+k)%26+97;
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
		
		
