#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure definition. Each structure will hold a pair of 'number - letter'.
struct DecryptionKeys
{
	int number;
	char letter;
};

// Function that takes a number and returns the corresponding character from the key list.
char decryptNumber(int number, struct DecryptionKeys* keys, int struct_size)
{
	for (int i = 0; i < struct_size; i++) // Going through our struct array, and if the number is the same as the key number, we return the corresponding char.
	{
		if ((keys + i)->number == number)
			return (keys + i)->letter;
	}

	return ' '; // If the number was not found in our list we just return a space.
}

int main()
{
	//=====================- Handling "text.txt" -=====================
	FILE* fp;
	fp = fopen("text.txt", "r"); // Opening 'text.txt' in 'read only' mode.
	const int array_size = 26;

	int* text_content = (int*)calloc(array_size, sizeof(int)); // Allocating 'array_size' times 'sizeof(int)' bytes of memory, where we'll store our text.txt contents.

	for (int i = 0; i <= array_size; i++) // Now we go through all the numbers in 'text.txt' and store them in our dynamically allocated array of ints.
	{
		fscanf(fp, "%d", text_content + i); // Remember, we increment the address with `text_content + i`
	}

	fclose(fp); // text.txt is no longer needed, so we close it.

	printf("Numbers loaded from text.txt: ");
	for (int i = 0; i < array_size; i++)
	{
		printf("%d ", *(text_content + i));
	}

	printf("\n"); // Just printing a new line to make the output prettier
	
	//=====================- Handling "key.txt" -=====================
	fp = fopen("key.txt", "r"); // Opening the key text file with read mode.

	struct DecryptionKeys* sptr = (struct DecryptionKeys*)malloc(sizeof(struct DecryptionKeys) * array_size); // Allocating enough space that can hold our array of structs.

	char temp[20];
	char* p;

	for (int i = 0; i < array_size; i++) // Going through each line in "key.txt"
	{
		fgets(temp, 20, fp); // Reading a line to temp
		p = strtok(temp, "\t"); // Extracts a string until it reaches the first tab(\t), in our case its gonna be a number

		(sptr + i)->number = atoi(p); // Converting the string we got to an int with 'atoi()', and assigning it to the (i)th struct array's 'number' member.
		p = strtok(NULL, "\n"); // Continue "extracting" a string until we reach the end of the current line.

		(sptr + i)->letter = p[0]; // p still points to a string that 'strtok()' left for us, but the first character is what we need, so we only take that and assign it to the (i)th struct array's 'letter' member.
	}

	fclose(fp); // "key.txt" is no longer needed, so we close it.

	printf("\nNumber & letter pairs loaded from key.txt:\n"); // Just printing a new line to make the output prettier

	for (int i = 0; i < array_size; i++)
	{
		printf("Number: %d\t| Paired Letter: %c\n", (sptr + i)->number, (sptr + i)->letter);
	}

	printf("\nDecrypted message from text.txt: ");

	for (int i = 0; i < array_size; i++)
	{
		printf("%c", decryptNumber(*(text_content + i), sptr, array_size));
	}

	fp = fopen("incription.txt", "w"); // Opening "incription.txt" in write mode.

	for (int i = 0; i < array_size; i++)
	{
		fprintf(fp, "%c", decryptNumber(*(text_content + i), sptr, array_size));
	}

	printf("\n(This message has been written into 'incription.txt')\n");

	fclose(fp); // Closing "incription.txt" after writing into it.

	free(sptr); // DecryptionKeys struct array deallocation
	free(text_content); // Array of numbers from text.txt deallocation
	
	return 0;
}
