#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define WORDLEN 30
#define PATHLEN 260
void inputname(char** filename)//можно было просто задать строку с макс длиной 260 символов но я захотела изучить malloc
{
	char c;
	int len = 1;
	*filename = (char*)malloc(sizeof(char));
	printf("input string: ");
	while ((c = getchar()) != '\n') {
		(*filename)[len - 1] = c;
		len++;
		*filename = (char*)realloc(*filename, len);
	}
	(*filename)[len - 1] = '\0';
	printf("%s", *filename);
}
int comp(char* word_compare,char* word_comparewith,char* word_toput, FILE* output_file)
{
	int flag = 0;
	if (strlen(word_compare) >= strlen(word_comparewith))
	{
		for (int i = 0; (strlen(word_compare)-i)>= strlen(word_comparewith); i++)
		{
			if ('a' <= word_compare[i] <= 'z' || 'A' <= word_compare[i] <= 'Z')
			{
				if (0 == strncmp(&(word_compare[i]), word_comparewith, strlen(word_comparewith)))//пропустит специальные символы при наличии таковых и сравнит нужное
				{
					flag = 1;
					i += strlen(word_comparewith)-1;
				}
				if (flag == 1 && i >= strlen(word_comparewith)) flag = 0;//типа после совпадающего слова все равно идут буквы (напр, слово и словосочетание)
			}

		}
	}
	if (flag == 0) {
		fputs(word_compare, output_file); 
		return 0;
	}
	else
	{
		if (strlen(word_compare) > strlen(word_comparewith))
		{
			for (int i = 0; strlen(word_compare)>i; i++)
			{
				if ((!(('a' <= word_compare[i] <= 'z' || 'A' <= word_compare[i] <= 'Z'))))
				{
					fputc(word_compare[i], output_file);
				}
				if (word_compare[i] == word_comparewith[0])
				{
					fputs(word_toput, output_file); i += strlen(word_comparewith) - 1;
				}
			}
		}
		else
		{
			fputs(word_toput, output_file);
		}
	}
	return 1;
}
int main(void)
{
	//SetConsoleCP(1251); //фор рашн
	//SetConsoleOutputCP(1251);
	char name_1[PATHLEN]={0}, name_2[PATHLEN] = { 0 }, name_3[PATHLEN] = { 0 }, name_4[PATHLEN] = { 0 };
	fgets(name_1, PATHLEN, stdin); name_1[strlen(name_1) - 1] = 0; //обрезка символа \n в конце строки
	fgets(name_2, PATHLEN, stdin); name_2[strlen(name_2) - 1] = 0;
	fgets(name_3, PATHLEN, stdin); name_3[strlen(name_3) - 1] = 0;
	fgets(name_4, PATHLEN, stdin); name_4[strlen(name_4) - 1] = 0;
	printf("%s\n%s\n%s\n%s", name_1,name_2,name_3,name_4);
	//char* name_1, * name_2, * name_3, * name_4, c;//тут может быть использован вариант с функцией inputname, но я хз будет ли этот вариант оптимальным для памяти\
	inputname(&name_1);\
	inputname(&name_2);\
	inputname(&name_3);\
	inputname(&name_4);

	FILE* file_1 = fopen(name_1, "r"), * file_2 = fopen(name_2, "r"), * file_3 = fopen(name_3, "r"), * file_4 = fopen(name_4, "w");

	if (file_1 == NULL || file_2 == NULL || file_3 == NULL || file_4 == NULL) {
		printf("ty");
		return 1;
	}
	char word_compare[WORDLEN], word_comparewith[WORDLEN],word_toput[WORDLEN];
	fscanf(file_1,"%s", word_compare);
	fscanf(file_2, "%s", word_comparewith);
	fscanf(file_3, "%s", word_toput);
	while (feof(file_2) == 0)
	{

		fscanf(file_1, "%s", word_compare);
		if (comp(word_compare, word_comparewith, word_toput, file_4))
		{
			fscanf(file_2, "%s", word_comparewith);
			fscanf(file_3, "%s", word_toput);
		}
	}
	fclose(file_1);
	fclose(file_2);
	fclose(file_3);
	fclose(file_4);
}