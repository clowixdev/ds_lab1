#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORDLEN 100
#define PATHLEN 260
#define STRLEN 50

void clear(char* str, int strlen) {
	for (int i = 0; i < strlen; i++) {
		str[i] = '\0';
	}
}

void get_n_word(FILE* file, char* word) {
	int count_slash = 0;
	int j = 0;
	char c;
	for (int i = 0;; i++) {
		c = fgetc(file);
		if ((c == '\n') || (feof(file) != 0)) {
			count_slash++;
			break;
		}
		if (count_slash == 0) {
			word[j++] = c;
		}
	}
	word[j] = '\0';
}

int main(int argc, char *argv[])
{
	// char name_1[PATHLEN]={0}, name_2[PATHLEN] = { 0 }, name_3[PATHLEN] = { 0 }, name_4[PATHLEN] = { 0 };
	// printf("Enter file paths >>> ");
	// fgets(name_1, PATHLEN, stdin); name_1[strlen(name_1) - 1] = 0; //обрезка символа \n в конце строки
	// fgets(name_2, PATHLEN, stdin); name_2[strlen(name_2) - 1] = 0;
	// fgets(name_3, PATHLEN, stdin); name_3[strlen(name_3) - 1] = 0;
	// fgets(name_4, PATHLEN, stdin); name_4[strlen(name_4) - 1] = 0;

	FILE* file_1 = fopen(argv[1], "r"), * file_2 = fopen(argv[2], "r"), * file_3 = fopen(argv[3], "r"), * file_4 = fopen(argv[4], "w");

	if (file_1 == NULL || file_2 == NULL || file_3 == NULL || file_4 == NULL) {
		printf("Error\n");
		return 1;
	}
	int words_count = 1;
	while (1)
	{
		if (fgetc(file_2) == '\n') words_count++;
		if (feof(file_2) != 0) break;
	}
	fseek(file_2, 0, SEEK_SET);

	char** words_comparewith = (char**)malloc(words_count * WORDLEN * sizeof(char *));
	for (int i = 0; i < words_count; i++) {
		char* word = (char*)malloc(sizeof(char) * WORDLEN);
		clear(word, WORDLEN-1);
		get_n_word(file_2, word);
		words_comparewith[i] = word;
	}

	char** words_toput = (char**)malloc(words_count * WORDLEN * sizeof(char *));
	for (int i = 0; i < words_count; i++) {
		char* word = (char*)malloc(sizeof(char) * WORDLEN);
		clear(word, WORDLEN);
		get_n_word(file_3, word);
		words_toput[i] = word;
	}

	
	int flag = 0,i=0;
	char word_compare[WORDLEN],c;
	while (1)
	{
		c = fgetc(file_1);
		if (('a' <= c && c<= 'z' ) || ('A' <= c && c <= 'Z'))
		{
			flag = 1;
			word_compare[i] = c;//начало слова
			i++;
		}
		else
		{
			if (flag == 1)
				{
					flag = 0;
					word_compare[i] = '\0';
					int replaced = 0;
					for (int j = 0; j < words_count; j++)
					{
						if (strcmp(word_compare, words_comparewith[j]) == 0)
						{
							fputs(words_toput[j], file_4);
							replaced = 1;
							break;
						}
					}
					if (replaced==0) fputs(word_compare, file_4);
				}
			if (feof(file_1) != 0) break;
			fputc(c, file_4);
			i = 0;
		}
	}

	fclose(file_1);
	fclose(file_2);
	fclose(file_3);
	fclose(file_4);

	for (int i = 0; i < words_count; i++) {
		free(words_comparewith[i]);
		free(words_toput[i]);
	}
	free(words_comparewith);
	free(words_toput);

	printf("everything is ok\n");	

	return 0;
}