#ifndef _FILE_OUTPUT
#define _FILE_OUTPUT

#include "stdafx.h"
#include "EXTRACT_LIB.h"

FILE *wp;

char FTI_PREFIX[64][128] = {
"00 - " , "01 - " , "02 - " , "03 - " , "04 - " , "05 - " , "06 - " , "07 - " , "08 - " , "09 - " , "0A - " , "0B - " , "0C - " , "0D - " , "0E - " ,  "0F - " , 
"10 - " , "11 - " , "12 - " , "13 - " , "14 - " , "15 - " , "16 - " , "17 - " , "18 - " , "19 - " , "1A - " , "1B - " , "1C - " , "1D - " , "1E - " ,  "1F - " , 
"20 - " , "21 - " , "22 - " , "23 - " , "24 - " , "25 - " , "26 - " , "27 - " , "28 - " , "29 - " , "2A - " , "2B - " , "2C - " , "2D - " , "2E - " ,  "2F - " , 
"30 - " , "31 - " , "32 - " , "33 - " , "34 - " , "35 - " , "36 - " , "37 - " , "38 - " , "39 - " , "3A - " , "3B - " , "3C - " , "3D - " , "3E - " ,  "3F - "
};
const char *FTI_AFFIX = ".fti";
char FOLDER_NAME[Max_Length];
char RELATIVE_ROUTE[Max_Length] = ".\\";

void Write_CHARBlock(FILE *fp , char c)
{
	char s[Max_Length];
	s[0] = c;
	fwrite(s , sizeof(char) , 1 , fp);
}
void Write_CHARBlock(FILE *fp , char c , int Address)
{
	if(JumptoAddress(fp , Address))
		Write_CHARBlock(fp , c);
}
void Write_INTBlock(FILE *fp , char s[])
{
	fwrite(s , sizeof(int) , 1 , fp);
}
void Write_INTBlock(FILE *fp , char s[] , int Address)
{
	if(JumptoAddress(fp , Address))
		Write_INTBlock(fp , s);
}
void Write_STRINGBlock(FILE *fp , char s[] , int Count)
{
	fwrite(s , 1 , Count , fp);
}
void Write_STRINGBlock(FILE *fp , char s[] , int Count , int Address)
{
	if(JumptoAddress(fp , Address))
		Write_STRINGBlock(fp , s , Count);
}

void Make_RelativeRoute(int num)
{
	if(!num)
		RELATIVE_ROUTE[3] = '\0';
	else
		RELATIVE_ROUTE[0] = '\0';
	strcat(FOLDER_NAME , "\\");
	strcat(RELATIVE_ROUTE , FOLDER_NAME);
}

char *Output_NameGen(char *s , int num)
{
	char p[Max_Length];
	Make_RelativeRoute(num);
	strcpy(p , s);
	strcat(p , FTI_AFFIX);
	strcat(FTI_PREFIX[num] , p);
	return strcat(RELATIVE_ROUTE , FTI_PREFIX[num]);
}

#endif
