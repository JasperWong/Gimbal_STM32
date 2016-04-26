#include "parser.h"
#include "usart.h"


void PARSER_Reset(COMMAND_PARSER *parser)
{
	parser->status = STATE_WAIT_X;
}

void PARSER_RunPaser(COMMAND_PARSER *parser,int32_t data)
{

	switch(parser->status)
	{
		case STATE_WAIT_X:
		{
//			printf("1");
			if(data=='X') 
			{	
				parser->isMinus_Roll=0;
				parser->isMinus_Yaw=0;
				parser->data_roll=0;
				parser->data_yaw=0;
				parser->status =STATE_WAIT_COLON;
			}
			else
			{
				parser->status=STATE_WAIT_X;
			}
			break;
		}
		
		case STATE_WAIT_COLON:
		{
//			printf("2");
			if(data==':')
			{
				parser->status =STATE_WAIT_REG_DATA_1;
			}
			else
			{
				parser->status=STATE_WAIT_X;
			}
			break;
		}
		
		case STATE_WAIT_REG_DATA_1:
		{
			
			if(data=='-') 
			{
				parser->isMinus_Roll=1;
				break;
			}
			if(data==' ')
			{
				parser->status=STATE_WAIT_Y;
				break;
			}
//			printf("3");
			parser->data_roll = parser->data_roll*10+(data-'0');
			break;
		}
		
		case STATE_WAIT_Y:
		{
//			printf("4");
			if(data=='Y')
			{
				parser->status=STATE_WAIT_COLON2;
			}
			break;
		}
		
		case STATE_WAIT_COLON2:
		{
//			printf("5");
			if(data==':')
			{
				parser->status=STATE_WAIT_REG_DATA_2;
			}
			break;
		}		
		
		case STATE_WAIT_REG_DATA_2:
		{
			if(data=='-')
			{
				parser->isMinus_Yaw=1;
				break;
			}
			if(data==' ')
			{
				parser->status=STATE_WAIT_NEWLINE;
				break;
			}
			parser->data_yaw=parser->data_yaw*10+(data-'0');
//			printf("6");
			break;
		}

		
		case STATE_WAIT_NEWLINE:
		{
//			printf("7");
			if(data=='\n')
			{
//				printf("8");
				parser->status=STATE_PARSE_FINISH_PENDING;
			}
//			else 
//			{
//				parser->status=STATE_WAIT_X;
//			}
			break;
		}
		
		case STATE_PARSE_FINISH_PENDING:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}
	