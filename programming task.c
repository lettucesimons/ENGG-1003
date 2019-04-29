/*Code for encryption and decryption of rotation and substitution ciphers given a key.
HOW TO USE:
-Specify desired operation 1-4 in the data file
-Specify the key in the line below
-Write the text to be encrypted/decrypted in the line below
-Run this program*/

/*This code first scans the file, writing the first three lines to a separate array. The first word of each line is used to help the user,
and is written to a different array so it is not included in the operation. The first array (operation) is then read to find what the user
wants to do. The length of the text array is also found using a function. The selection is applied to a switch/case which runs one of four
functions and outputs the new txt array to stdout.*/

#include<stdio.h>

char* rotencode(char*txt, char*key, int length); //rotation encryption function
char* rotdecode(char*txt, char*key, int length); //rotation decryption function
char* subencode(char*txt, char*key, int length); //substitution encryption function
char* subdecode(char*txt, char*key, int length); //substitution decryption function
int commonletter(char*txt, int length); //finds most common letter
int strlng(char*str); //function to find the length
int main()	{
	int n=0; //counter
	int length; //variable to pass strlng to other functions
	int ky;// variable to pass two digit keys to be printed as an int
	int operation; //variable to select operation found in the header
	char txt[1024]; //string to encode/decode
	char key[1024]; //key for cipher
	char rubbish[1024]; //useless variable to advance fscanf past header definitions because I have no idea how to do it properly
	FILE *input;
	input = fopen("data", "r"); //opens the input file
	if (input==NULL)	{ //returns and error and exits if file not found
	perror("fopen()");
	return 0;
	}
	/*scans the first line from a file to variable operation until a new line character is encountered. This is set to null*/
	for(n=0; n<10; n++)	{
		fscanf(input, "%c", &rubbish[n]); //advance past OPERATION:
	}
	fscanf(input, "%d", &operation); //operation string
		
	
	/*scans the first line from a file to variable key until a new line character is encountered. This is set to null*/
	for(n=0; n<5; n++)
		fscanf(input, "%c", &rubbish[n]); //advance past KEY:
	for(n=0; n<1019; n++)	{
		fscanf(input, "%c", &key[n]);
		if (key[n] == 10)	{ 
			key[n] = 'E'; //setting a marker for rotation keys
			break;
		}
	}	
	/*scans the next line from a file to variable txt until a new line character is encountered. This is set to null*/
	for(n=0; n<8; n++)
		fscanf(input, "%c", &rubbish[n]); //advance past PHRASE:
	for(n=0; n<1016; n++)	{
		fscanf(input, "%c", &txt[n]);
		if (txt[n] == 10)	{ 
			txt[n] = 0; 
			break;
		}
	}	
	length = strlng(txt);
	printf("PHRASE: '%s'\n", txt); //prints the string to the screen

		switch(operation)	{ //selects operation based on information in header file written to the operation string
			case 1:
				if (key[1] == 'E') // moving the key from an array to an int for printing (this is done in ASCII for the function
					ky=(key[0])-48;
				else  
					ky = (((key[0]-48)*10) + (key[1]-48)); // first place is multiplied by ten then second place is added (-48 to convert from ASCII)
				printf("ROTATION ENCRYPTION SELECTED\nKEY: '%d'\nROTATION ENCRYPTED PHRASE: '%s'\n", ky, rotencode(txt, key, length));
				break;
			case 2:
				if (key[1] == 'E') // moving the key from an array to an int for printing (this is done in ASCII for the function
					ky=(key[0])-48;
				else  
					ky = (((key[0]-48)*10) + (key[1]-48));
				printf("ROTATION DECRYPTION SELECTED\nKEY: '%d'\nROTATION DECRYPTED PHRASE: '%s'\n", ky, rotdecode(txt, key, length));
				break;
			case 3:
				printf("SUBSTITUTION ENCRYPTION SELECTED\nKEY: '%s'\nSUBSTITUTION ENCRYPTED PHRASE: '%s'\n", key, subencode(txt, key, length));
				break;
			case 4:
				printf("SUBSTITUTION DECRYPTION SELECTED\nKEY: '%s'\nSUBSTITUTION DECRYPTED PHRASE: '%s'\n", key, subdecode(txt, key, length));
				break;
			case 5: // this only works if the most common letter is e
				printf ("Common Letter: %c\n", commonletter(txt, length));
				ky = commonletter(txt, length)-69+48; //find the difference between most common letter and e, adding 48 to convert to ascii
				for(n=0;n<length;n++)	{
					if (txt[n]<91 && txt[n]>64) //uppercase
						txt[n] = (((txt[n]-65-(ky-48))+26)%26)+65; 
					if (txt[n]<123 && txt[n]>96) //lowercase
						txt[n] = (((txt[n]-97-(ky-48))+26)%26)+97-32; //-32 to convert to uppercase
	}
				printf("ROTATION DECRYPTION W/O KEY SELECTED\nROTATION DECRYPTED PHRASE: '%s'\n", txt);
				
break;
			
			default:
				printf("please enter a valid number\n"); //runs if the header file has the wrong value
				break;
		}

return 0;
}

char* rotencode(char*txt, char*key, int length)	{
	/*this function reads through the text string between 0 and its length and for each character:
		-moves the key from an array to an int
		-decides if it is uppercase or lowercase based on the range of ASCII values (everything else is left as is)
		-subtracts a number to get the letters between 0 and 25
		-adds the key which is the 0th element of the string converted from ASCII to a number
		-adds 26 to remove negative numbers (this is divided out in the next step)
		-takes the remainder using the modulus operator
		-returns the 0-25 to ASCII by adding a value */
	int n=0;
	int ky;
	if (key[1] == 'E') // moving the key from an array to an int
		ky=(key[0]);
	else  
		ky = (((key[0]-48)*10) + (key[1]-48))+48;
	for(n=0;n<length;n++)	{
		if (txt[n]<91 && txt[n]>64) //uppercase
			txt[n] = (((txt[n]-65+(ky-48))+26)%26)+65; 
		if (txt[n]<123 && txt[n]>96) //lowercase
			txt[n] = (((txt[n]-97+(ky-48))+26)%26)+97-32; //-32 to convert to uppercase
	}
	return txt;
}

char* rotdecode(char*txt, char*key, int length)	{
	/*this function reads through the text string between 0 and its length and for each character:
		-moves the key from an array to an int
		-decides if it is uppercase or lowercase based on the range of ASCII values (everything else is left as is)
		-subtracts a number to get the letters between 0 and 25
		-subtracts the key which is the 0th element of the string converted from ASCII to a number
		-adds 26 to remove negative numbers (this is divided out in the next step)
		-takes the remainder using the modulus operator
		-returns the 0-25 to ASCII by adding a value */
	int n=0;
	int ky;
	if (key[1] == 'E') // moving the key from an array to an int
		ky=(key[0]);
	else  
		ky = (((key[0]-48)*10) + (key[1]-48))+48;
	for(n=0;n<length;n++)	{
		if (txt[n]<91 && txt[n]>64) //uppercase
			txt[n] = (((txt[n]-65-(ky-48))+26)%26)+65; 
		if (txt[n]<123 && txt[n]>96) //lowercase
			txt[n] = (((txt[n]-97-(ky-48))+26)%26)+97-32; //-32 to convert to uppercase
	}
	return txt;
}

char* subencode(char*txt, char*key, int length)	{
	/*this function reads through the text string between 0 and its length and for each character:
		-decides if it is uppercase or lowercase based on the range of ASCII values (everything else is left as is)
		-subtracts a number to get the letters between 0 and 25
		-finds that position in the key string and reassigns the value 
		-adds 32 to the lowercase letters to convert them as the key is uppercase */
	int n=0;
	key[26]=0; //set end to null	
	for(n=0;n<length;n++)	{
		if (txt[n]<91 && txt[n]>64)	{ //uppercase
			txt[n] = txt[n]-65; 
			txt[n] = key[txt[n]]; 
		}
		if (txt[n]<123 && txt[n]>96)	{ //lowercase
			txt[n] = txt[n]-97;
			txt[n] = key[txt[n]]; 
		}			
	}
	return txt;
}

char* subdecode(char*txt, char*key, int length)  {
	/*this function reads through the text string between 0 and its length and for each character:
		-decides if it is uppercase or lowercase based on the range of ASCII values (everything else is left as is)
		-checks all values of the key against the letter to find which one it is
		-uses the position of the key within the string  
		-adds a number to convert to ASCII */
	int n=0;
	int k=0; //counter for the key
	key[26]=0; //set end to null
	for(n=0;n<length;n++)	{
		if (txt[n]<91 && txt[n]>64)	{ //uppercase
			for (k=0; k<30; k++)	{ //going through every value of the the key
				if (txt[n] == key[k])	{ //checking if the values are equal
					txt[n] = (k+65); //making the encrypted letter the old value based on where it is in the key
					k=0; //setting the counter back to 0
					break;
				}
			} 
		}
		if (txt[n]<123 && txt[n]>96)	{ //lowercase (same as above)
			for (k=0; k<30; k++)	{ 
				if (txt[n] == key[k]+32)	{ //checking if the values are equal (convert key to lowercase by -32)
					txt[n] = (k+97-32); //convert back to uppercase
					k=0; 
					break;
				}
			} 
		}			
	}
	return txt;
}

int commonletter(char*txt, int length)	{
/*this function counts the most common letter in the string by placing a counter for each letter in the part of an array corresponding to
its ASCII code. A loop then goes through each position in the uppercase range and sets the highest to max, checking each against max. The position of max corresponds to the ASCII code of the character, which is the return value */
int n=0;
int array[1024];
int max;
int position=0;

	for(n=0;n<length;n++)	{
		if (txt[n]<123 && txt[n]>96)	{ //lowercase
			txt[n] = txt[n]-32; //convert to uppercase
		}			
		if (txt[n]<91 && txt[n]>64)	{ //uppercase
			array[txt[n]]++;	
		}
			
	}
	max = array[0];
	for(n=64;n<92;n++)	{
		if (array[n] > max)	{
			max=array[n];
			position = n;
		}
	}
	return position;
}

int strlng (char *txt)	{
	/*this function determines the length of the string by scanning through each element and checking if it is null - incrementing a counter if it is not and returning the counter if it is */
	int n = 0;
	while (txt[n]!=0)
		n++;
return n;
}
	
