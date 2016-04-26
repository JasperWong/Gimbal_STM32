#ifndef PARSER_H
#define PARSER_H

#include "stm32f10x.h"

typedef struct
{
	enum state{
		STATE_WAIT_X, 								
		STATE_WAIT_COLON,									
		STATE_WAIT_REG_DATA_1,
		STATE_WAIT_Y, 
		STATE_WAIT_COLON2,
		STATE_WAIT_REG_DATA_2,			
//		STATE_WAIT_CHECKSUM, 				
		STATE_WAIT_NEWLINE,						
		STATE_PARSE_FINISH_PENDING,
	};
	
	int32_t status;
	int32_t data_roll;
	int32_t data_yaw;
	uint8_t checksum;
	uint8_t isMinus_Roll;
	uint8_t isMinus_Yaw;
	
}COMMAND_PARSER;

uint8_t PARSER_IsParseFinish(COMMAND_PARSER *parser);
void PARSER_Reset(COMMAND_PARSER *parser);
void PARSER_RunPaser(COMMAND_PARSER *parser,int32_t data);
#endif
