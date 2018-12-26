#include "stdafx.h"
#include "Instrument.h"
#include "2A03Address.h"
#include "EXTRACT_LIB.h"
#include "FILE_INPUT.h"
#include "FILE_OUTPUT.h"

char FILE_NAME[Max_Length];

/*void ReadFileString(FILE *fp)
{
	long file_size;
	if(fseek(fp , 0 , SEEK_END) == 0)
		file_size = ftell(fp);
	fread(FILE_STRING , 1 , file_size , fp);
}*/

Instrument2A03::Instrument2A03()
{
	InitializeInstrument();
}
void Instrument2A03::InitializeInstrument()
{
	memset(Trigger , 0 , sizeof(Trigger));
	memset(ENABLE_FLAG , 0 , sizeof(ENABLE_FLAG));
	memset(NAME_NUM , 0 , sizeof(NAME_NUM));
	memset(SEQ_LOOP , 0xFF , sizeof(SEQ_LOOP));
	memset(SEQ_LIST , 0 , sizeof(SEQ_LIST));
	memset(SEQ_NUM , 0 , sizeof(SEQ_NUM));
	memset(SEQ_RELEASE , 0xFF , sizeof(SEQ_RELEASE));
	memset(SEQ_SETTING , 0 , sizeof(SEQ_SETTING));
}
bool Instrument2A03::Get_EnableFlag(int Type)
{
	return ENABLE_FLAG[Type];
}
void Instrument2A03::Read_SeqCount(FILE *fp , int Address)
{
	SEQ_COUNT = Read_INTBlock(fp , Address);
	//printf("Seq Count:%d\n",SEQ_COUNT);
}
void Instrument2A03::Read_EnableFlag(FILE *fp , int Address)
{
	int i;
	for(i = 0 ; i < SEQ_COUNT ; i++)
	{
		ENABLE_FLAG[i] = WORDBlock_DecodeLow(Read_WORDBlock(fp , Address + i*2));
		//printf("Enable Flag:%d\n",ENABLE_FLAG[i]);
	}
}
void Instrument2A03::Read_SeqIndex(FILE *fp , int Address)
{
	int i;
	for(i = 0 ; i < SEQ_COUNT ; i++)
	{
		SEQ_INDEX[i] = WORDBlock_DecodeHigh(Read_WORDBlock(fp , Address + i*2));
		//printf("Sequence Index:%d\n",SEQ_INDEX[i]);
	}
}
void Instrument2A03::Read_InstrumentNameLength(FILE *fp , int Address)
{
	NAME_LENGTH = Read_INTBlock(fp , Address);
	Read_STRINGBlock(fp , NAME_NUM , sizeof(int) , Address);
	//printf("Name Length:%d\n" , NAME_LENGTH);
}
void Instrument2A03::Read_InstrumentName(FILE *fp , int Address)
{
	if(JumptoAddress(fp , Address))
		Read_STRINGBlock(fp , NAME_STRING , NAME_LENGTH);
}
int Instrument2A03::Read_SequenceIndex(FILE *fp , int Address)
{
	return Read_INTBlock(fp , Address);
}
int Instrument2A03::Read_SequenceType(FILE *fp , int Address)
{
	return Read_INTBlock(fp , Address);
}
void Instrument2A03::Read_SequenceLength(FILE *fp , int Address , int Type)
{
	SEQ_LENGTH[Type] = Read_CHARBlock(fp , Address);
	Read_STRINGBlock(fp , SEQ_NUM[Type] , 1 , Address);
	//printf("SEQ_LENGTH %d\n",SEQ_LENGTH[Type]);
}
void Instrument2A03::Read_SequenceLoop(FILE *fp , int Address , int Type)
{
	Read_STRINGBlock(fp , SEQ_LOOP[Type] , sizeof(int) , Address);
}
void Instrument2A03::Read_SequenceList(FILE *fp , int Address , int Type)
{
	Read_STRINGBlock(fp , SEQ_LIST[Type] , SEQ_LENGTH[Type] , Address);
}
void Instrument2A03::Read_SequenceRelease(FILE *fp , int Address , int Type)
{
	Read_STRINGBlock(fp , SEQ_RELEASE[Type] , sizeof(int) , Address);
}
void Instrument2A03::Read_SequenceSetting(FILE *fp , int Address , int Type)
{
	Read_STRINGBlock(fp , SEQ_SETTING[Type] , sizeof(int) , Address);
}
int Instrument2A03::Get_NameLength()
{
	return NAME_LENGTH;
}
char *Instrument2A03::Get_NameString()
{
	return NAME_STRING;
}
int Instrument2A03::Get_SequenceIndex(int Type)
{
	return SEQ_INDEX[Type];
}
int Instrument2A03::Get_SequenceLength(int Type)
{
	return SEQ_LENGTH[Type];
}

void Instrument2A03::Write_InstrumentType(FILE *fp , int Address)
{
	Write_CHARBlock(fp , INST_TYPE , Address);
}
void Instrument2A03::Write_InstrumentNameLength(FILE *fp , int Address)
{
	Write_INTBlock(fp , NAME_NUM , Address);
}
void Instrument2A03::Write_InstrumentName(FILE *fp , int Address)
{
	Write_STRINGBlock(fp , NAME_STRING , NAME_LENGTH , Address);
}
void Instrument2A03::Write_SeqCount(FILE *fp , int Address)
{
	Write_CHARBlock(fp , SEQ_COUNT , Address);
}
void Instrument2A03::Write_EnableFlag(FILE *fp , int Address , int Type)
{
	Write_CHARBlock(fp , ENABLE_FLAG[Type] , Address);
}
void Instrument2A03::Write_SequenceLength(FILE *fp , int Address , int Type)
{
	Write_INTBlock(fp , SEQ_NUM[Type] , Address);
}
void Instrument2A03::Write_SequenceLoop(FILE *fp , int Address , int Type)
{
	Write_INTBlock(fp , SEQ_LOOP[Type] , Address);
}
void Instrument2A03::Write_SequenceRelease(FILE *fp , int Address , int Type)
{
	Write_INTBlock(fp , SEQ_RELEASE[Type] , Address);
}
void Instrument2A03::Write_SequenceSetting(FILE *fp , int Address , int Type)
{
	Write_INTBlock(fp , SEQ_SETTING[Type] , Address);
}
void Instrument2A03::Write_SequenceList(FILE *fp , int Count , int Address , int Type)
{
	Write_STRINGBlock(fp , SEQ_LIST[Type] , Count , Address);
}


char FTM_HEADER[] = "FamiTracker Module";
char FTI_HEADER[] = "FTI2.4";
char FTI_NODPCM_END[] = {
0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00
};

int main(int argc , char *FILE_NAME_IN[])
{
	assert(argc == 2);
	strcpy(FOLDER_NAME , FILE_NAME_IN[1]);
	FOLDER_NAME[GetStringLength(FOLDER_NAME) - 4] = '\0';
	_mkdir(FOLDER_NAME);
	opendir(FOLDER_NAME);
	int i , j;
	memset(RELATIVE_ROUTE , 0 ,sizeof(RELATIVE_ROUTE));
	
    fp = fopen(FILE_NAME_IN[1] , "rb+");
	if(fseek(fp , 0 , SEEK_SET) == 0)
		fread(FILE_NAME , 1 , 18 , fp);
	if(memcmp(FILE_NAME , FTM_HEADER , GetStringLength(FTM_HEADER)) != 0)
		return -1;
	INSTRUMENT_COUNT = Read_INTBlock(fp , INSTRUMENT_NUM);
	//printf("COUNT : %d\n" , INSTRUMENT_COUNT);
	Instrument2A03 Instr_2A03[INSTRUMENT_COUNT];
	int BASE_INSTRUMENT_OFFSET = INSTRUMENT_NUM + 0x00000004;
	//printf("%d",BASE_INSTRUMENT_OFFSET);
	
	//printf("%d %d\n",BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_COUNT , Read_INTBlock(fp , INSTRUMENT_SEQ_COUNT));
	for(i = 0 ; i < INSTRUMENT_COUNT ; i++)
	{
		switch(Read_CHARBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_TYPE))
		{
			case INST_2A03:
			{
				Instr_2A03[i].Read_SeqCount(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_COUNT);
				Instr_2A03[i].Read_EnableFlag(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_ENABLEINDEX);
				Instr_2A03[i].Read_SeqIndex(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_ENABLEINDEX);
				Instr_2A03[i].Read_InstrumentNameLength(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_NAME_LENGTH);
				Instr_2A03[i].Read_InstrumentName(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_NAME);
				BASE_INSTRUMENT_OFFSET += NEXT_INSTRUMENT; 
				break;
			}
			default:
					break;
		}
	}
	int SEQ_AMOUNT = Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_COUNT);
	BASE_INSTRUMENT_OFFSET += SEQUENCE_BLOCK_INTERVAL;
	
	int AMOUNT = SEQ_AMOUNT;
	while(AMOUNT > 0)
	{
		for(i = 0 ; i < INSTRUMENT_COUNT ; i++)
		{
			int Index = Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_INDEX);
			int Type = Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_TYPE);
			if(!Instr_2A03[i].Get_EnableFlag(Type))	continue;
			else if(Instr_2A03[i].Get_SequenceIndex(Type) == Index)
			{
				//printf("%d\n",BASE_INSTRUMENT_OFFSET + SEQUENCE_LENGTH);
				Instr_2A03[i].Read_SequenceLength(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_LENGTH , Type);
				Instr_2A03[i].Read_SequenceLoop(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_LOOP , Type);
				Instr_2A03[i].Read_SequenceList(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_LIST , Type);
				Instr_2A03[i].Trigger[Type] = AMOUNT;
				//printf("BASE_INSTRUMENT_OFFSET %d\n" , BASE_INSTRUMENT_OFFSET);
			}
		}
		BASE_INSTRUMENT_OFFSET += NEXT_SEQUENCE;
		AMOUNT --;	
	}
	for(AMOUNT = SEQ_AMOUNT ; AMOUNT > 0 ; AMOUNT --)
	{
		for(j = 0 ; j < 5 ; j++)
			for(i = 0 ; i < INSTRUMENT_COUNT ; i++)
				if(Instr_2A03[i].Trigger[j] == AMOUNT)
				{
					Instr_2A03[i].Read_SequenceRelease(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_RELEASE , j);
					//printf("SEQUENCE_RELEASE : %d\n",BASE_INSTRUMENT_OFFSET + SEQUENCE_RELEASE);
					Instr_2A03[i].Read_SequenceSetting(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_SETTING , j);
				}
		BASE_INSTRUMENT_OFFSET += NEXT_SEQUENCE_N;
	}
	fclose(fp);
		
	for(i = 0 ; i < INSTRUMENT_COUNT ; i++)
	{
		wp = fopen(Output_NameGen(Instr_2A03[i].Get_NameString() , i) , "wb+");
		fwrite(FTI_HEADER , 1 , GetStringLength(FTI_HEADER) , wp);
		Instr_2A03[i].Write_InstrumentType(wp , FTI_INSTRUMENT_TYPE);
		Instr_2A03[i].Write_InstrumentNameLength(wp , FTI_NAME_LENGTH);
		Instr_2A03[i].Write_InstrumentName(wp , FTI_NAME_STRING);
		Instr_2A03[i].Write_SeqCount(wp , FTI_INSTRUMENT_SEQ_COUNT);
		BASE_INSTRUMENT_OFFSET = FTI_INSTRUMENT_SEQ_COUNT + 0x00000001;
		for(j = 0; j < 5 ; j++)
		{
			Instr_2A03[i].Write_EnableFlag(wp , BASE_INSTRUMENT_OFFSET + FTI_ENABLE_FLAG , j);
			if(!Instr_2A03[i].Get_EnableFlag(j))
			{
				BASE_INSTRUMENT_OFFSET += 0x00000001;
				continue;
			}
			else
			{
				Instr_2A03[i].Write_SequenceLength(wp , BASE_INSTRUMENT_OFFSET + FTI_SEQUENCE_LENGTH , j);
				Instr_2A03[i].Write_SequenceLoop(wp , BASE_INSTRUMENT_OFFSET + FTI_SEQUENCE_LOOP , j);
				Instr_2A03[i].Write_SequenceRelease(wp , BASE_INSTRUMENT_OFFSET + FTI_SEQUENCE_RELEASE , j);
				//printf("FTI_SEQUENCE_RELEASE : %d\n",BASE_INSTRUMENT_OFFSET + FTI_SEQUENCE_RELEASE);
				Instr_2A03[i].Write_SequenceSetting(wp , BASE_INSTRUMENT_OFFSET + FTI_SEQUENCE_SETTING , j);
				Instr_2A03[i].Write_SequenceList(wp , Instr_2A03[i].Get_SequenceLength(j) , BASE_INSTRUMENT_OFFSET + FTI_SEQUENCE_LIST , j);
				BASE_INSTRUMENT_OFFSET += FTI_NEXT_SEQUENCE;
			}
		}
		fwrite(FTI_NODPCM_END , 8 , 1 , wp);
	}
	fclose(wp);
	return 0;
}
