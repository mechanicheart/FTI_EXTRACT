//No DPCM
#ifndef _INSTRUMENT
#define _INSTRUMENT

#include "EXTRACT_LIB.h"

#define NOTE_RANGE 12
#define OCTAVE_RANGE 8
#define INTERVAL_CODE_OFFSET NOTE_RANGE * OCTAVE_RANGE * 3

enum{
INST_NONE = 0 ,
INST_2A03 = 1 ,
INST_VRC6 , 
INST_VRC7
};

int INTERVAL_CODE[] = {
0x00 , 0x00 , 0xFF																		//Sample, Sample Pitch, Sample Delta Value
};
static int INSTRUMENT_COUNT = 0;

class Instrument2A03{
	public:
		Instrument2A03();
		void InitializeInstrument();
		bool Get_EnableFlag(int Type);
		void Read_SeqCount(FILE *fp , int Address);
		void Read_EnableFlag(FILE *fp , int Address);
		void Read_SeqIndex(FILE *fp , int Address);
		void Read_InstrumentNameLength(FILE *fp , int Address);
		void Read_InstrumentName(FILE *fp , int Address);
		
		int Read_SequenceIndex(FILE *fp , int Address);			//Unused
		int Read_SequenceType(FILE *fp , int Address);
		void Read_SequenceLength(FILE *fp , int Address , int Type);
		void Read_SequenceLoop(FILE *fp , int Address , int Type);
		void Read_SequenceList(FILE *fp , int Address , int Type);
		
		void Read_SequenceRelease(FILE *fp , int Address , int Type);
		void Read_SequenceSetting(FILE *fp , int Address , int Type);
		
		int Get_NameLength();
		char *Get_NameString();
		int Get_SequenceIndex(int Type);
		int Get_SequenceLength(int Type);
		
		void Write_InstrumentType(FILE *fp , int Address);
		void Write_InstrumentNameLength(FILE *fp , int Address);
		void Write_InstrumentName(FILE *fp , int Address);
		void Write_SeqCount(FILE *fp , int Address);
		void Write_EnableFlag(FILE *fp , int Address , int Type);
		void Write_SequenceLength(FILE *fp , int Address , int Type);
		void Write_SequenceLoop(FILE *fp , int Address , int Type);
		void Write_SequenceRelease(FILE *fp , int Address , int Type);
		void Write_SequenceSetting(FILE *fp , int Address , int Type);
		void Write_SequenceList(FILE *fp , int Count , int Address , int Type);
		
		int Trigger[5];
	private:
		bool ENABLE_FLAG[5];
		int SEQ_INDEX[5];
		
		int INST_TYPE = INST_2A03;
		int SEQ_COUNT;
		
		int NAME_LENGTH;
		char NAME_NUM[4];
		
		char NAME_STRING[Max_Name];
		
		int SEQ_LENGTH[5];
		char SEQ_NUM[5][4];
		
		char SEQ_LOOP[5][4];
		char SEQ_LIST[5][Max_SEQ];
		
		char SEQ_RELEASE[5][4];
		char SEQ_SETTING[5][4];
		
};

#endif