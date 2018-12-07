#include "STM8S103k.h"
#include "Input.h"
#include "WalkMotor.h"
#include "KneadMotor.h"
#include "MotorCtrl.h"
#include "Timer.h"
#define MAX_INBUFFER_COUNT 25
unsigned int RX_Index = 0;
unsigned int nSendCounter = 0;		
unsigned char nInChar;		
extern _Bool bReceivePacketOk, bMasterSendPacket;
//extern _Bool bReceiveBusy;

extern unsigned char nTxBuf[MAX_SEND_COUNT],nRxBuf[MAX_RECEIVE_COUNT];
extern unsigned char nSendCount,nSendTotalCount;

extern volatile unsigned int nCurWalkLocate;

extern _Bool b485SendFlag;//modify by dyl  20170424
_Bool bSendFinishFlag = 0;//modify for new 485send  dyl 20170426

#pragma vector=0x04
__interrupt void EXTI1_PORTB_Interrupt(void)
{
	  if(WalkMotor_GetDirection() != WALK_MOTOR_GO_UP)
	  {
			  if(nCurWalkLocate > 0 )
			  {
					  nCurWalkLocate-- ;
			  }
			  if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
			  {
					  Input_SetWalkMotorPosition(0);
			  }
	  }
	  else
	  {
			  if(nCurWalkLocate < 1000)
			  {
					  nCurWalkLocate++ ;
			  }
			  if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
			  {
					  Input_SetWalkMotorPosition(TOP_POSITION);
			  }
	  }
	return;

}

#pragma vector=0x11
__interrupt void UART_TX_Interrupt(void)
{
    //unsigned int i;
		
		if(nSendCount < nSendTotalCount)
    {
			  bSendFinishFlag = FALSE;//modify for new 485send  dyl 20170426
				
        while(!(UART1_SR&0x40));//trasmission is not complete;
        UART1_DR = nTxBuf[nSendCount];
        nSendCount++;
    }
    else
    {   					
        while(!(UART1_SR&0x40));//shouled bit 7(txe) have a test either?
        nSendCount = 0;
        UART1_CR2 &= 0xB7;//should bit 2(ren)disable?
				
				//i = 200;
				//while(i--);			
				
        //bMax485De = FALSE;//modify for new 485send  dyl 20170426		
				bSendFinishFlag = TRUE;//modify for new 485send  dyl 20170426
    }
	  return;

}

#pragma vector=0x12
__interrupt void UART_RX_Interrupt(void)
{
	//RXNE, 读数据寄存器非空
	//unsigned char checksum;
        //unsigned char i;
	UART1_SR &= 0xDF;		//RXNE可由软件清0
	 nInChar = UART1_DR;		//读取UART_DR寄存器也可清除RXNE位
	 
	if(bReceivePacketOk == FALSE)
	{
		if((RX_Index == 0) && (nInChar != 0X55)) return ; 
		if((RX_Index == 0) && (nInChar == 0X55))
		{
				RX_Index = 0 ;
				nRxBuf[RX_Index] = nInChar ;
				RX_Index++ ;

		}
		else
		{
				nRxBuf[RX_Index] = nInChar ;
				RX_Index++ ;
				
				RX_Index %= MAX_INBUFFER_COUNT;
				//if(nInBufferCount==(5+InBuffer[2]))
			 if( nRxBuf[1]==0xAB)
				 {
				 
						 if(nInChar==EOI_AB)
						{							  
								bReceivePacketOk = TRUE ;
							  RX_Index=0;
						//	bTime10ms=0;
							//counter_10ms=0;
			        	
						}
		      }
					if( nRxBuf[1]==0xAA)
				 {
				 
						 if(nInChar==EOI_AA)
						{
								bReceivePacketOk = TRUE ;
							  RX_Index=0;
						//	bTime10ms=0;
							//counter_10ms=0;
			       	
						}
		      }
	  }
				 
				
	
	}
	return;

}

#pragma vector=0x17
__interrupt void TIM4_Interrupt(void)
{
	  static unsigned char by_Time5ms = 0;
    static unsigned char by_Time10ms = 0;
    //static unsigned char by_Time50ms = 0;
    static unsigned char by_Time100ms = 0;
		
		static unsigned char b485SendCounter = 0;
		static unsigned char bSendFinishCounter = 0;
		
		if((bSendFinishFlag == TRUE)&&(bSendFinishCounter < 2))//modify for new 485send  dyl 20170426
		{
		    bSendFinishCounter++;
	  }
		else if((bSendFinishFlag == TRUE)&&(bSendFinishCounter >= 2))
	  {
			  bSendFinishFlag = FALSE;
				bSendFinishCounter = 0;
				bMax485De = FALSE;
		}
		if((bMasterSendPacket == TRUE)&&(b485SendCounter < 5))//modify by dyl  20170424
		{
		    b485SendCounter++;
	  }
		else if((bMasterSendPacket == TRUE)&&(b485SendCounter >= 5))
	  {
			  b485SendFlag = TRUE;
				b485SendCounter = 0;
		}
		if(by_Time5ms >= 4)
		{
		    by_Time5ms = 0; 
				Input_5ms_Int();
	  }
		else
		{
		    ++by_Time5ms;
	  }
		if(by_Time10ms >= 9)
		{
		    by_Time10ms = 0; 
				WalkMotor_10ms_Int();
		    KneadMotor_10ms_Int();
	  }
		else
	  {
		    ++by_Time10ms;
		}
		if(by_Time100ms >= 100)
		{
		    by_Time100ms = 0;
				Timer_Flag_100ms_Int();
	  }
		else
	  {
		    ++by_Time100ms;
		}
		if(nSendCounter >= 100)
	  {
				//bMasterSendPacket = TRUE;//modify by dyl  20170317
				nSendCounter = 0;
		}
		else
	  {
		    ++nSendCounter;
		}
	  TIM4_SR &= ~(0x01);
	  return;

}




