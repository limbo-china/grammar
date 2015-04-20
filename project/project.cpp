// project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "io.h"

#define EOL '\n'
#define Is_Interpreted_As_First -95
#define Is_Interpreted_As_Second -6
#define Back_Slash  '\\'
#define Blank_Space  ' '
#define Left_Square_Bracket '['
#define Right_Square_Bracket ']'
#define Comma ','
#define ExplicationN '-'
#define ExplicationP '+'
#define Colon ':'
#define Hyphen '-'
#define Left_Brace '{'
#define Right_Brace '}'
#define Syntax 0
#define Vocabulary 1

char filename[30];
char ch;
FILE *infile;
int line = 1;
int status = Syntax;
struct _finddata_t fa;
long fHandle;
	

void scanner();
bool check_term();//term检测函数声明

bool check_term() //term检测函数定义
{
	ch = fgetc(infile);
	if (ch != Back_Slash)
	{
		printf("error： missing a '\\' behind '\\' \n");
		return true;
	}
	ch = fgetc(infile);
	if (ch < 'A' || ch> 'Z') //检测upper_case；
	{
		printf("error： upper_case expected behind '\\' \n");
		return true;
	}

	do //检测id_character；
	{
		ch = fgetc(infile);
	} while ((ch >= '0'&&ch <= '9') || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'));

	if (ch == Left_Square_Bracket) //检测left_square_bracket；
	{
		ch = fgetc(infile);
		if (ch != ExplicationN && ch != ExplicationP)
		{
			printf("error: missing a '-'or'+' behind '[' \n");
			return true;
		}
		ch = fgetc(infile);
		if (ch != 'P'&&ch != 'F')
		{
			printf("error: 'FIN' or 'PL' expected \n");
			return true;
		}
		if (ch == 'P')
		{
			ch = fgetc(infile);
			if (ch != 'L')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return true;
			}
		}
		else if (ch == 'F')
		{
			ch = fgetc(infile);
			if (ch != 'I')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return true;
			}
			ch = fgetc(infile);
			if (ch != 'N')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return true;
			}
		}
		ch = fgetc(infile);
		while (ch != Right_Square_Bracket) //当还没遇到 Right_Square_Bracket时；
		{
			if (ch != Comma)
			{
				printf("error: missing a ',' or a ']'\n");
				return true;
			}
			ch = fgetc(infile);
			if (ch != ExplicationN&&ch != ExplicationP)
			{
				if (ch != Blank_Space)
				{
					printf("error: a blankspace or '-'or'+' expected behind ','\n");
					return true;
				}
				else
				{
					ch = fgetc(infile);
					if (ch != ExplicationN&&ch != ExplicationP)
					{
						printf("error: missing a '-'or'+' behind blankspace\n");
						return true;
					}
				}
			}
			ch = fgetc(infile);
			if (ch != 'P'&&ch != 'F')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return true;
			}
			if (ch == 'P')
			{
				ch = fgetc(infile);
				if (ch != 'L')
				{
					printf("error: 'FIN' or 'PL' expected \n");
					return true;
				}
			}
			else if (ch == 'F')
			{
				ch = fgetc(infile);
				if (ch != 'I')
				{
					printf("error: 'FIN' or 'PL' expected \n");
					return true;
				}
				ch = fgetc(infile);
				if (ch != 'N')
				{
					printf("error: 'FIN' or 'PL' expected \n");
					return true;
				}
			}
			ch = fgetc(infile);
		}
		ch = fgetc(infile);
	}
	return false;
	//遇到 Right_Square_Bracket跳出循环；
	//检测 term 结束；
}
void scanner(FILE *infile)
{
	
	ch = fgetc(infile);
	while (ch != EOF)
	{
		//
		if (ch == '\n')
		{
			line++;  //遇到换行符，行数加一；
			ch = fgetc(infile);
			if (ch == '\n')
			{
				line++;
				ch = fgetc(infile);
			}
			if (ch == EOF)
			{
				printf("error: can not ending with a eol\n");
				return;
			}
		}
		if (ch >= '0'&&ch <= '9')
		{
			ch = fgetc(infile);
			while ((ch >= '0'&&ch <= '9') || ch == Hyphen)
			{
				ch = fgetc(infile);
				if (ch == Hyphen)
				{
					ch = fgetc(infile);
					if (ch < '0' || ch > '9')
					{
						printf("error: digit expected behind '-'\n");
						return;
					}
				}
			}
			if (ch != Colon)
			{
				printf("error: missing a ':' \n");
				return;
			}
		}
		else
		{
			printf("error: digit expected at the beginning of a rule\n");
			return;
		}//检测 id 结束；

		//

		ch = fgetc(infile);
		if (ch != Back_Slash)  //开始检测term;
		{
			printf("error: '\\' expected behind ':'\n");
			return;
		}
		if (check_term())
			return;
		//检测 term 结束；

		if (ch != Is_Interpreted_As_First)
		{
			printf("error: '→' expected behind a term \n");
			return;
		}
		ch = fgetc(infile);
		if (ch != Is_Interpreted_As_Second)
		{
			printf("error: '→' expected behind a term \n");
			return;
		}
		
		ch = fgetc(infile); //开始检测 interpretation；
		if (!((ch == Back_Slash) || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')||(ch==Left_Brace)))
		{
			printf("error: mistakes at the beginnning of interpretation\n");
			return;
		}
		while ((ch != '\n')&&ch!=EOF)
		{
			while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')|| (ch == Back_Slash)  ) //syntax_interpretation;
			{
				if (status == Vocabulary)
				{
					printf("error: syntax_rule can not exist behind vocabulary_rule\n");
					return;
				}
				 //检测lexical_item；
				if (ch == Back_Slash)
				{
					if (check_term())
						return;
					if ((ch != '\n') && (ch != Blank_Space)&&(ch!=EOF))
					{
						printf("error: mistakes behind a term\n");
						return;
					}
					if (ch == Blank_Space)
					{
						ch = fgetc(infile);
						if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)))
						{
							printf("error: lexical_item expected behind a blankspace\n");
							return;
						}
					}
				}
				if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'))
				{
					do
					{
						ch = fgetc(infile);
					} while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'));
					if ((ch != '\n') && (ch != Blank_Space))
					{
						printf("error: mistakes behind a vocabulary_item\n");
						return;
					}
					if (ch == Blank_Space)
					{
						ch = fgetc(infile);
						if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)))
						{
							printf("error: vocabulary_item or term expected behind a blankspace\n");
							return;
						}
					}
				}
			}

			if (ch == Left_Brace) //vocabulary_interpretation;
			{
				status = Vocabulary;
				ch = fgetc(infile);
				if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
				{
					printf("error: vocabulary_item expected behind left_brace\n");
					return;
				}
				while (ch != Right_Brace)
				{
						do
						{
							if (ch == Comma)
							{
								ch = fgetc(infile);
								if ((ch != Blank_Space) && (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'))))
								{
									printf("error: blankspace or vocabulary_item expected behind a comma\n");
									return;
								}
								if (ch == Blank_Space)
								{
									ch = fgetc(infile);
									if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
									{
										printf("error: vocabulary_item expected behind a blankspace\n");
										return;
									}
								}
							}
							do
							{
								ch = fgetc(infile);
							} while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'));
							if ((ch != Blank_Space) && (ch != Comma) && (ch != Right_Brace))
							{
								printf("error: mistakes behind a vocabulary_item\n");
								return;
							}
							if (ch == Blank_Space)
							{
								ch = fgetc(infile);
								if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
								{
									printf("error: vocabulary_item expected behind a blankspace\n");
									return;
								}
							}
						} while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')||(ch==Comma));

					if (ch != Right_Brace)
					{
						printf("error: right_brace expected\n");
						return;
					}
				}
				ch = fgetc(infile);
				if ((ch != EOF) && (ch != '\n'))
				{
					printf("error: mistakes behind right_brace\n");
					return;
				}
			}
		}
	}
	printf("true\n");
}
int _tmain(int argc, _TCHAR* argv[])
{
	if ((fHandle = _findfirst("*.txt", &fa)) == -1L) 
	{
		printf("there is no file!\n");
		return 0;
	}
	else
	do
	{
		infile = fopen(fa.name, "r");
		while (!infile)
		{
			printf("error: can not open file:%s\n",fa.name);
			return 0;
		}
		printf("%s:\n", fa.name);
		scanner(infile);
		printf("line:%d\n\n", line);
	} while (_findnext(fHandle, &fa) == 0);

	_findclose(fHandle);
		
	
	return 0;
}

