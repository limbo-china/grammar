

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


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
#define Syntax 1
#define Vocabulary_tag 2
#define Vocabulary_rule 3
#define TagSize 15
#define IdSize  100
#define IdNumSize 1000

char *tag=(char*)malloc(TagSize*sizeof(char));
char ch;
char id_c[IdNumSize][IdSize];
FILE *infile;
int id_num = 0;
int line = 1;
int status = Syntax;
	

void scanner();
bool grammertag();	//grammer tag¼ì²â
bool syntaxtag();	//syntax tag¼ì²â
bool vocabutag();	//vocabulary tag¼ì²â
bool term();		//term¼ì²â
bool id();			//id¼ì²â
bool interpret();	//¡®¡ú¡¯¼ì²â
bool syn_inter();	//syntax interpretation¼ì²â
bool voc_inter();	//vocabulary interpretation¼ì²â

bool grammertag()
{
	char *t=tag;
	if (ch != 'g')
	{
		printf("error:tag \'grammer\'expected\n");
		return false;
	}
	while (ch >= 97 && ch <= 122)
	{
		*t++ = ch;
		ch = fgetc(infile);
	}
	if (ch != '\n')
	{
		printf("error: a eol expected behind a tag\n");
		return false;
	}
	line++;
	*t = '\0';
	if (strcmp(tag, "grammer"))
	{
		printf("error: tag \'grammer\'expected\n");
		return false;
	}
	ch = fgetc(infile);
	return true;
}
bool syntaxtag()
{
	char *t = tag;
	if (ch != 's')
	{
		printf("error:tag \'syntax\'expected\n");
		return false;
	}
	while (ch >= 97 && ch <= 122)
	{
		*t++ = ch;
		ch = fgetc(infile);
	}
	if (ch != '\n')
	{
		printf("error: a eol expected behind a tag\n");
		return false;
	}
	line++;
	*t = '\0';
	if (strcmp(tag, "syntax"))
	{
		printf("error: tag \'syntax\'expected\n");
		return false;
	}
	ch = fgetc(infile);
	return true;
}
bool vocabutag()
{
	char *t = tag;
	if (ch != 'v')
	{
		printf("error:tag \'vocabulary\'expected\n");
		return false;
	}
	while (ch >= 97 && ch <= 122)
	{
		*t++ = ch;
		ch = fgetc(infile);
	}
	if (ch != '\n')
	{
		printf("error: a eol expected behind a tag\n");
		return false;
	}
	line++;
	*t = '\0';
	if (strcmp(tag, "vocabulary"))
	{
		printf("error: tag \'vocabulary\'expected\n");
		return false;
	}
	status = Vocabulary_tag;
	ch = fgetc(infile);
	return true;
}
bool term() //term¼ì²âº¯Êý¶¨Òå
{
	ch = fgetc(infile);
	if (ch != Back_Slash)
	{
		printf("error£º missing a '\\' behind '\\' \n");
		return false;
	}
	ch = fgetc(infile);
	if (ch < 'A' || ch> 'Z') //¼ì²âupper_case£»
	{
		printf("error£º upper_case expected behind '\\' \n");
		return false;
	}

	do //¼ì²âid_character£»
	{
		ch = fgetc(infile);
	} while ((ch >= '0'&&ch <= '9') || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'));

	if (ch == Left_Square_Bracket) //¼ì²âleft_square_bracket£»
	{
		ch = fgetc(infile);
		if (ch != ExplicationN && ch != ExplicationP)
		{
			printf("error: missing a '-'or'+' behind '[' \n");
			return false;
		}
		ch = fgetc(infile);
		if (ch != 'P'&&ch != 'F')
		{
			printf("error: 'FIN' or 'PL' expected \n");
			return false;
		}
		if (ch == 'P')
		{
			ch = fgetc(infile);
			if (ch != 'L')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return false;
			}
		}
		else if (ch == 'F')
		{
			ch = fgetc(infile);
			if (ch != 'I')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return false;
			}
			ch = fgetc(infile);
			if (ch != 'N')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return false;
			}
		}
		ch = fgetc(infile);
		while (ch != Right_Square_Bracket) //µ±»¹Ã»Óöµ½ Right_Square_BracketÊ±£»
		{
			if (ch != Comma)
			{
				printf("error: missing a ',' or a ']'\n");
				return false;
			}
			ch = fgetc(infile);
			if (ch != ExplicationN&&ch != ExplicationP)
			{
				if (ch != Blank_Space)
				{
					printf("error: a blankspace or '-'or'+' expected behind ','\n");
					return false;
				}
				else
				{
					ch = fgetc(infile);
					if (ch != ExplicationN&&ch != ExplicationP)
					{
						printf("error: missing a '-'or'+' behind blankspace\n");
						return false;
					}
				}
			}
			ch = fgetc(infile);
			if (ch != 'P'&&ch != 'F')
			{
				printf("error: 'FIN' or 'PL' expected \n");
				return false;
			}
			if (ch == 'P')
			{
				ch = fgetc(infile);
				if (ch != 'L')
				{
					printf("error: 'FIN' or 'PL' expected \n");
					return false;
				}
			}
			else if (ch == 'F')
			{
				ch = fgetc(infile);
				if (ch != 'I')
				{
					printf("error: 'FIN' or 'PL' expected \n");
					return false;
				}
				ch = fgetc(infile);
				if (ch != 'N')
				{
					printf("error: 'FIN' or 'PL' expected \n");
					return false;
				}
			}
			ch = fgetc(infile);
		}
		ch = fgetc(infile);
	}
	return true;
	//Óöµ½ Right_Square_BracketÌø³öÑ­»·£»
	//¼ì²â term ½áÊø£»
}
bool id()
{
	char *c = id_c[id_num];
	int i;
	if (ch >= '0'&&ch <= '9')
	{
		*c++ = ch;
		ch = fgetc(infile);
		while ((ch >= '0'&&ch <= '9') || ch == Hyphen)
		{
			*c++ = ch;
			ch = fgetc(infile);
			if (ch == Hyphen)
			{
				*c++ = ch;
				ch = fgetc(infile);
				if (ch < '0' || ch > '9')
				{
					printf("error: digit expected behind '-'\n");
					return false;
				}
			}
		}
		if (ch != Colon)
		{
			printf("error: missing a ':' \n");
			return false;
		}
		*c = '\0';
		for (i = 0; i < id_num; i++)
		{
			if (!strcmp(id_c[i], id_c[id_num]))
			{
				printf("error: the id is not unique\n");
				return false;
			}
		}
		id_num++;
	}
	else
	{
		printf("error: digit expected at the beginning of a rule\n");
		return false;
	}//¼ì²â id ½áÊø£»
	ch = fgetc(infile);
	return true;
	
}
bool interpret()
{
	if (ch != Is_Interpreted_As_First)
	{
		printf("error: '¡ú' expected behind a term \n");
		return false;
	}
	ch = fgetc(infile);
	if (ch != Is_Interpreted_As_Second)
	{
		printf("error: '¡ú' expected behind a term \n");
		return false;
	}
	ch = fgetc(infile);
	return true;
}
bool syn_inter()
{
	
	if (!((ch == Back_Slash) || (ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
	{
		printf("error: at the beginnning of syntax interpretation\n");
		return false;
	}
	while (ch != '\n')
	{
		while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)) //syntax_interpretation;
		{
			//¼ì²âlexical_item£»
			if (ch == Back_Slash)
			{
				if (!term())
					return false;
				if ((ch != '\n') && (ch != Blank_Space))
				{
					printf("error: behind a term in syntax interpretation\n");
					return false;
				}
				if (ch == Blank_Space)
				{
					ch = fgetc(infile);
					if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)))
					{
						printf("error: lexical_item expected behind a blankspace\n");
						return false;
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
					printf("error: eol or blankspace expected behind a vocabulary_item\n");
					return false;
				}
				if (ch == Blank_Space)
				{
					ch = fgetc(infile);
					if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch == Back_Slash)))
					{
						printf("error: vocabulary_item or term expected behind a blankspace\n");
						return false;
					}
				}
			}
		}
	}
	line++;
	ch = fgetc(infile);
	return true;
}
bool voc_inter()
{
	if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
	{
		printf("error: at the beginnning of vocabulary interpretation\n");
		return false;
	}
	while (ch != '\n')
	{
		do
		{
			ch = fgetc(infile);
		} while ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'));
		if ((ch != '\n') && (ch != Blank_Space))
		{
			printf("error: eol or blankspace expected behind a vocabulary_item\n");
			return false;
		}
		if (ch == Blank_Space)
		{
			ch = fgetc(infile);
			if (!((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
			{
				printf("error: vocabulary_item expected behind a blankspace\n");
				return false;
			}
		}
	}
	line++;
	ch = fgetc(infile);
	return true;
}

void scanner(FILE *infile)
{
	
	ch = fgetc(infile);
	if (!grammertag())	//¼ì²âgrammertag
		return;
	if (!syntaxtag())	//¼ì²âsyntaxtag
		return;
	while (ch != EOF)
	{
		
		if (!id())
			return ;	//¼ì²â id;

		if (ch != Back_Slash)  //¿ªÊ¼¼ì²âterm;
		{
			printf("error: '\\' expected behind ':'\n");
			return;
		}

		if (!term())
			return;		//¼ì²âterm;
		
		if (!interpret())
			return;		 //¼ì²â¡®¡ú¡¯;
		
							//¿ªÊ¼¼ì²â interpretation£»
		if (status == Syntax)
		{
			if (!syn_inter())	//¼ì²â syntax interpretation;
				return;
			if (ch == 'v')
			{
				printf("error: a eol expected between syntax and vocabulary\n");
				return;
			}
			if (ch == '\n')
			{
				line++;
				ch = fgetc(infile);
				if (ch == 'v')
				if (!vocabutag())
					return;
			}
		}
		else if (status == Vocabulary_tag)
		{
			if (!voc_inter())	//¼ì²â vocabulary interpretation;
				return;
			status = Vocabulary_rule;
			if (ch == '\n')
			{
				line++;
				ch = fgetc(infile);
				if (ch == EOF)
				{
					printf("error: eol occured at the end of grammer\n");
					return;
				}
			}
		}
	}
	if (status == Vocabulary_rule)
		printf("true\n");
	else
		printf("error: missing vocabulary\n");
}
int main(int argc, char *argv[])
{
		
		char *fname = "1.txt";
		infile = fopen(fname, "r");
		while (!infile)
		{
			printf("error: can not open file:%s\n",fname);
			return 0;
		}
		scanner(infile);
		printf("line:%d\n", line);
		fclose(infile);
		
	return 0;
}

