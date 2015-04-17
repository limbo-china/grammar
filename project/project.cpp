// project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"


//#define DIGIT '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9'
//#define LOWER_LETTER 'a'||'b'||'c'||'d'||'e'||'f'||'g'||'h'||'i'||'j'||'k'||'l'||'m'||'n'||'o'||'p'||'q'||'r'||'s'||'t'||'u'||'v'||'w'||'x'||'y'||'z'
//#define UPPER_LETTER 'A'||'B'||'C'||'D'||'E'||'F'||'G'||'H'||'I'||'J'||'K'||'L'||'M'||'N'||'O'||'P'||'Q'||'R'||'S'||'T'||'U'||'V'||'W'||'X'||'Y'||'Z'


#define EOL '\n'
#define Is_Interpreted_As '>'
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

char filename[30];
char ch;
FILE *infile;
int line = 1;


void scanner();
bool check_term();//term检测函数声明

bool check_term() //term检测函数定义
{
	ch = fgetc(infile);
	if (ch != Back_Slash)
	{
		printf("error!\n");
		return true;
	}
	ch = fgetc(infile);
	if (ch < 'A' || ch> 'Z') //检测upper_case；
	{
		printf("error!\n");
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
			printf("error!\n");
			return true;
		}
		ch = fgetc(infile);
		if (ch != 'P'&&ch != 'F')
		{
			printf("error!\n");
			return true;
		}
		if (ch == 'P')
		{
			ch = fgetc(infile);
			if (ch != 'L')
			{
				printf("error!\n");
				return true;
			}
		}
		else if (ch == 'F')
		{
			ch = fgetc(infile);
			if (ch != 'I')
			{
				printf("error!\n");
				return true;
			}
			ch = fgetc(infile);
			if (ch != 'N')
			{
				printf("error!\n");
				return true;
			}
		}
		ch = fgetc(infile);
		while (ch != Right_Square_Bracket) //当还没遇到 Right_Square_Bracket时；
		{
			if (ch != Comma)
			{
				printf("error!\n");
				return true;
			}
			ch = fgetc(infile);
			if (ch != ExplicationN&&ch != ExplicationP)
			{
				if (ch != Blank_Space)
				{
					printf("error!\n");
					return true;
				}
				else
				{
					ch = fgetc(infile);
					if (ch != ExplicationN&&ch != ExplicationP)
					{
						printf("error!\n");
						return true;
					}
				}
			}
			ch = fgetc(infile);
			if (ch != 'P'&&ch != 'F')
			{
				printf("error!\n");
				return true;
			}
			if (ch == 'P')
			{
				ch = fgetc(infile);
				if (ch != 'L')
				{
					printf("error!\n");
					return true;
				}
			}
			else if (ch == 'F')
			{
				ch = fgetc(infile);
				if (ch != 'I')
				{
					printf("error!\n");
					return true;
				}
				ch = fgetc(infile);
				if (ch != 'N')
				{
					printf("error!\n");
					return true;
				}
			}
			ch = fgetc(infile);
		}
	}
	return false;
	//遇到 Right_Square_Bracket跳出循环；
	//检测 term 结束；
}
void scanner()
{
	infile = fopen("data.txt", "r");
	while (!infile)
	{
		printf("error!\n");
		return;
	}
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
				printf("error!\n");
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
						printf("error!\n");
						return;
					}
				}
			}
			if (ch != Colon)
			{
				printf("error!\n");
				return;
			}
		}
		else
		{
			printf("error!\n");
			return;
		}//检测 id 结束；

		//

		ch = fgetc(infile);
		if (ch != Back_Slash)  //开始检测term;
		{
			printf("error!\n");
			return;
		}
		if (check_term())
			return;
		//检测 term 结束；

		ch = fgetc(infile);
		if (ch != Is_Interpreted_As)
		{
			printf("error!\n");
			return;
		}
		
		ch = fgetc(infile); //开始检测 interpretation；
		if (!((ch == Back_Slash) || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')||ch==Left_Brace))
		{
			printf("error!\n");
			return;
		}
		while ((ch != '\n')&&ch!=EOF)
		{
			while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')|| (ch == Back_Slash)  )
			{
				 //检测lexical_item；
				if (ch == Back_Slash)
				{
					if (check_term())
						return;
					ch = fgetc(infile);
					if ((ch != '\n') && (ch != Blank_Space)&&(ch!=EOF))
					{
						printf("error!\n");
						return;
					}
					if (ch == Blank_Space)
					{
						ch = fgetc(infile);
						if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)))
						{
							printf("error!\n");
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
						printf("error!\n");
						return;
					}
					if (ch == Blank_Space)
					{
						ch = fgetc(infile);
						if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)))
						{
							printf("error!\n");
							return;
						}
					}
				}
			}

			if (ch == Left_Brace)
			{
				ch = fgetc(infile);
				if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
				{
					printf("error!\n");
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
									printf("error!\n");
									return;
								}
								if (ch == Blank_Space)
								{
									ch = fgetc(infile);
									if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
									{
										printf("error!\n");
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
								printf("error!\n");
								return;
							}
							if (ch == Blank_Space)
							{
								ch = fgetc(infile);
								if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
								{
									printf("error!\n");
									return;
								}
							}
						} while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')||(ch==Comma));

					if (ch != Right_Brace)
					{
						printf("error!\n");
						return;
					}
				}
				ch = fgetc(infile);
				if ((ch != EOF) && (ch != '\n'))
				{
					printf("error!\n");
					return;
				}
			}
		}
	}
	printf("true\n"); 
}
int _tmain(int argc, _TCHAR* argv[])
{
	scanner();
	printf("%d\n", line);
	return 0;
}

