#include "Instrument.h"
#include "FILE_INPUT.h"

#define HEADER_BLOCK 							          0x000000C3
#define HEADER_BLOCK_LENGTH 				        0x000000D7
#define INSTRUMENT_BLOCK						        Read_INTBlock(fp , HEADER_BLOCK_LENGTH) + 0x000000DB
#define INSTRUMENT_BLOCK_LENGTH		          Read_INTBlock(fp , HEADER_BLOCK_LENGTH) + 0x000000EF
#define INSTRUMENT_NUM						          Read_INTBlock(fp , HEADER_BLOCK_LENGTH) + 0x000000F3

#define INSTRUMENT_INDEX						        0x00000000
#define INSTRUMENT_TYPE						          0x00000004
#define INSTRUMENT_SEQ_COUNT				        0x00000005
#define INSTRUMENT_SEQ_ENABLEINDEX	        0x00000009
#define INSTRUMENT_SAMPLE				          	Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_COUNT) * 2 + 0x00000009
#define INSTRUMENT_NAME_LENGTH		        	Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_COUNT) * 2 + INTERVAL_CODE_OFFSET + 0x00000009
#define INSTRUMENT_NAME					           	Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_COUNT) * 2 + INTERVAL_CODE_OFFSET + 0x0000000D
#define NEXT_INSTRUMENT						          Read_INTBlock(fp , BASE_INSTRUMENT_OFFSET + INSTRUMENT_SEQ_COUNT) * 2 + INTERVAL_CODE_OFFSET + Read_INTBlock(fp ,BASE_INSTRUMENT_OFFSET +  INSTRUMENT_NAME_LENGTH) + 0x0000000D

#define SEQUENCE_COUNT					          	0x00000018
#define SEQUENCE_BLOCK_INTERVAL		          0x0000001C					//28 Bytes Interval

#define SEQUENCE_INDEX							        0x00000000
#define SEQUENCE_TYPE							          0x00000004
#define SEQUENCE_LENGTH						          0x00000008
#define SEQUENCE_LOOP							          0x00000009
#define SEQUENCE_LIST							          0x0000000D
#define NEXT_SEQUENCE							          Read_CHARBlock(fp , BASE_INSTRUMENT_OFFSET + SEQUENCE_LENGTH) + 0x0000000D

#define SEQUENCE_RELEASE						        0x00000000
#define SEQUENCE_SETTING						        0x00000004
#define NEXT_SEQUENCE_N						          0x00000008

#define FTI_HEADER_BLOCK						        0x00000000
#define FTI_INSTRUMENT_TYPE					        0x00000006
#define FTI_NAME_LENGTH						          0x00000007
#define FTI_NAME_STRING						          0x0000000B
#define FTI_INSTRUMENT_SEQ_COUNT		        Instr_2A03[i].Get_NameLength()+ 0x0000000B

#define FTI_ENABLE_FLAG							        0x00000000
#define FTI_SEQUENCE_LENGTH				          0x00000001
#define FTI_SEQUENCE_LOOP					          0x00000005
#define FTI_SEQUENCE_RELEASE				        0x00000009
#define FTI_SEQUENCE_SETTING				        0x0000000D
#define FTI_SEQUENCE_LIST						        0x00000011
#define FTI_NEXT_SEQUENCE					          Instr_2A03[i].Get_SequenceLength(j) + 0x00000011
