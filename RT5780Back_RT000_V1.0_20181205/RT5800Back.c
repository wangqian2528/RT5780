/* Includes -----------------------------------------------------------------*/
#include "STM8S103k.h"          /* Registers and memory mapping file */
#include "WalkMotor.h"
#include "KneadMotor.h"
#include "KnockMotor.h"
#include "MotorCtrl.h"
#include "Input.h"
#include "timer.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
_Bool bReceivePacketOk, bMasterSendPacket;
//_Bool bReceiveBusy = FALSE;
//-----------------------------------------------------------------------------
unsigned char nWalkMotorControlParam1;
unsigned short nWalkMotorControlParam2;
unsigned char nKneadMotorControlParam1,nKneadMotorControlParam2;
unsigned char nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3;

unsigned short nVoltage;

unsigned char nKneadMotorReturn,nWalkMotorReturn;

unsigned char nKnockMotor_ControlParam1,nKneadMotor_ControlParam1,nKneadMotor_ControlParam2,nWalkMotor_ControlParam1;
unsigned short nWalkMotor_ControlParam2;

extern unsigned char nBackMainRunMode;
extern unsigned char nCurKneadKnockSpeed,nCurKnockRunStopCounter,nCurActionStepCounter;
extern unsigned char bKnockMotorInProcess,bKneadMotorInProcess,bWalkMotorInProcess;
extern unsigned char nCurKneadMotorCycles;
extern unsigned char bUpdateLocate;
extern unsigned short nShoulderPosition;

extern unsigned int RX_Index;
extern unsigned int nSendCounter;

extern volatile unsigned int nCurWalkLocate;

_Bool b485SendFlag;//modify by dyl  20170424
unsigned char upload_auto_step;//dyl 20170426
/*---------------------------------------------------------------------------*/
/* ROUTINE NAME: CLK_Init                                                    */
/* INPUT/OUTPUT: None.                                                       */
/* DESCRIPTION:  Initialize the clock source                                 */
/*---------------------------------------------------------------------------*/
void CLK_Init(void)
{
    while(!(CLK_ICKR&0x02));
    /* Configure HSI prescaler*/
    CLK_CKDIVR = 0x00;	/* 0: fHSI= fHSI RC output    = 16MHz*/
}

//portA
#define WALK_DOWN_SW_BIT      1
#define WALK_UP_SW_BIT        2
#define WALK_ENABLE_BIT       3
//portB
#define WALK_PULSE_BIT        3
#define WALK_FAULT_BIT        6
#define WALK_DECAY_BIT        7
//portC
#define KNEAD_MAX_BIT         1
#define KNEAD_MED_BIT         2
#define KNEAD_MIN_BIT         3
#define KNEAD_ENABLE_BIT      4
#define KNEAD_PHASE_BIT       5
#define KNEAD_DECAY_BIT       6
#define KNEAD_FAULT_BIT       7
//portD
#define KNEAD_RESET_BIT       0
#define KNOCK_RESET_BIT       2
#define KNOCK_FAULT_BIT       3
#define KNOCK_ENABLE_BIT      4

#define UART_TXD_BIT          5
#define UART_RXD_BIT          6
#define MAX485_DE_BIT         7
//portE
#define WALK_RESET_BIT        5
//portF
#define WALK_PHASE_BIT        4

void GPIO_Init(void)
{
    PA_DDR |= (1 << WALK_ENABLE_BIT);
    PA_DDR &= ~((1 << WALK_DOWN_SW_BIT) | (1 << WALK_UP_SW_BIT));
    PA_ODR &= ~(1 << WALK_ENABLE_BIT);
    PA_CR1 |= (1 << WALK_ENABLE_BIT);

    PB_DDR |=  (1 << WALK_DECAY_BIT);
    PB_DDR &= ~((1 << WALK_PULSE_BIT) | (1 << WALK_FAULT_BIT));
    PB_ODR &= ~((1 << WALK_DECAY_BIT));
    PB_CR1 |= (1 << WALK_FAULT_BIT) | (1 << WALK_DECAY_BIT);
    EXTI_CR1 = 0x08;
    PB_CR2 |= (1 << WALK_PULSE_BIT);

    PC_DDR |= ((1 << KNEAD_ENABLE_BIT) | (1 << KNEAD_PHASE_BIT) | (1 << KNEAD_DECAY_BIT));
    PC_DDR &= ~((1 << KNEAD_MAX_BIT) | (1 << KNEAD_MED_BIT) | (1 << KNEAD_MIN_BIT) | (1 << KNEAD_FAULT_BIT));
    PC_ODR &= ~((1 << KNEAD_ENABLE_BIT) | (1 << KNEAD_PHASE_BIT) | (1 << KNEAD_DECAY_BIT));		  
    PC_CR1 |= ((1 << KNEAD_ENABLE_BIT) | (1 << KNEAD_PHASE_BIT) | (1 << KNEAD_DECAY_BIT) 
          | (1 << KNEAD_FAULT_BIT));

    PD_DDR |= (/*(1 << UART_TXD_BIT) | */(1 << MAX485_DE_BIT) | (1 << KNEAD_RESET_BIT) | (1 << KNOCK_RESET_BIT) 
          | (1 << KNOCK_ENABLE_BIT));
    PD_DDR &= ~((1 << KNOCK_FAULT_BIT) /*| (1 << UART_RXD_BIT)*/);
    PD_ODR &= ~(/*(1 << UART_TXD_BIT) | */(1 << MAX485_DE_BIT) | (1 << KNEAD_RESET_BIT) | (1 << KNOCK_RESET_BIT) 
          | (1 << KNOCK_ENABLE_BIT));
    PD_CR1 |= (/*(1 << UART_TXD_BIT) |*/ (1 << MAX485_DE_BIT) | (1 << KNEAD_RESET_BIT) | (1 << KNOCK_RESET_BIT)
          | (1 << KNOCK_ENABLE_BIT) | (1 << KNOCK_FAULT_BIT));		

    PE_DDR |= (1 << WALK_RESET_BIT) ;
    PE_ODR &= ~(1 << WALK_RESET_BIT);
    PE_CR1 |= (1 << WALK_RESET_BIT) ;

    PF_DDR |= (1 << WALK_PHASE_BIT);
    PF_ODR &= ~(1 << WALK_PHASE_BIT);
    PF_CR1 |= (1 << WALK_PHASE_BIT);
}

//-----------------------------------------------------------------------------
void TIM_Init(void)  //1ms
{
    TIM4_PSCR = 0x06;       // Configure TIM4 prescaler = 64
    TIM4_ARR  = 250;        // Configure TIM4 period

    // TIM4 counter enable
    TIM4_CR1 |= 0x05;       // Enable TIM4
    TIM4_IER |= 0x01;       // Enable TIM4 OVR interrupt
}
//-----------------------------------------------------------------------------
void Time1Pwm_Init(void)
{
    TIM1_CCMR4 |= 0x68;
    TIM1_CCER2 |= 0x10;	    // "OC3N" enabled, CCnP=0为高电平有效
    TIM1_ARRH = 0;	
    TIM1_ARRL = 100;	//以高字节，低字节这种方式写时必须先写高字节。再写低字节。
    TIM1_CCR4H = 0x00;	// CC3 Dutycycle
    TIM1_CCR4L = 0x00;
    TIM1_BKR |= 0x80;	// Output enable
    TIM1_EGR &= ~0x01;
    TIM1_PSCRH = 0x00;	// Configuration prescaler (Fck_cnt=Fck_psc/PSCR+1)
    TIM1_PSCRL = 0x07;	// 预分频为799+1，fCK_CNT = 20k
    TIM1_CR1 |= 0x81;	// Counter enable
}
void Time2Pwm_Init(void)
{
    TIM2_CCMR1 |= 0x68;	
    TIM2_CCER1 |= 0x01;
    TIM2_ARRH    = 0;         /* Freq control register: ARR             */
    TIM2_ARRL    = 100;
    TIM2_CCR1H  = 0x00;    /* CC3 Dutycycle */
    TIM2_CCR1L  = 0x00;
    TIM2_PSCR  = 0x03;      /* fCK_CNT is equal to fCK_PSC.           */
    TIM2_CR1  |= 0x81;      /* Enable TIM2.                           */ 
}
//-----------------------------------------------------------------------------

void UART_Init(void)
{
    UART1_CR1 = 0x00;
    UART1_CR3 = 0x00;
    UART1_BRR2 = 0x0b;//0x03; zwg	//UART_DIV:15-12, ,3:0
    UART1_BRR1 = 0x08;//0x68;zwg 	//UART_DIV:11-4, 波特率约为 0683 115200
    UART1_CR2 = 0x26;//the 2 indicate:An UART interrupt is generated whenever OR=1 or RXNE=1 in the UART_SR register.And the 6 indicate the ten disable ren enable
}
//-----------------------------------------------------------------------------
#define  ADC_CHANNEL      0x01
#define  ADC_CR1_ADON     0x01
#define  ADC_CR1_CONT     0x02
#define  ADC_CSR_EOC      0x80
void ADC_Init(void)
{
    ADC_CSR |= ADC_CHANNEL;		//选择通道 AIN0，AIN1
    //ADC_CR2 |= 0x00;	//左对齐
    //ADC_TDRH = ADC2_TDRH_RESET_VALUE;
    ADC_TDRL |= 0x03;	//禁止AIN0,AIN1施密特触发输入
    //ADC_CR1 &= ~ADC_CR1_CONT;
    ADC_CR2  |= 0x0a;  //使能扫描模式，数据右对齐
    //ADC_CR3  |= 0x80;  //数据缓存使能
    ADC_CR1 |= 0x70;
    //ADC_CR1 &= ~ADC_CR1_ADON;
    ADC_CR1 |= ADC_CR1_ADON;
}
//-----------------------------------------------------------------------------
void Delay(unsigned int nClock)
{
    while(nClock--);  //800;  100us
                    //4000; 500us
}
//-----------------------------------------------------------------------------
unsigned char nTxBuf[MAX_SEND_COUNT],nRxBuf[MAX_RECEIVE_COUNT];
unsigned char nSendCount,nSendTotalCount;
unsigned int nCommandID;
_Bool btest;

unsigned char nReceiveClass = 0xAB;
//-----------------------------------------------------------------------------
void CommProcess(void)
{
    unsigned char chk_sum;
    //unsigned char j;

    unsigned int i = 0;
    if(bReceivePacketOk == TRUE)
    {
    //bMasterSendPacket = FALSE;  //syx 20160516				
        bReceivePacketOk = FALSE;	
        //_asm("sim");
        nReceiveClass = nRxBuf[1];
        if(nReceiveClass == 0xAB)
        {
            chk_sum=0;
            for ( i=1;i<3+nRxBuf[2];i++)
            {
                chk_sum+=nRxBuf[i];
            }
            chk_sum=~chk_sum;
            chk_sum&=0x7f;
            if(chk_sum==nRxBuf[3+nRxBuf[2]])
            {
                bMasterSendPacket = TRUE;//modify by dyl  20170426
                if(nRxBuf[22]==1)//收到主板发送的标志位
                {
                    nKnockMotorControlParam1 = nRxBuf[3];
                    nKnockMotorControlParam2 = nRxBuf[4];
                    nKnockMotorControlParam3 = nRxBuf[5];
                    nKneadMotorControlParam1 = nRxBuf[6];
                    nKneadMotorControlParam2 = nRxBuf[7];
                    nWalkMotorControlParam1 = nRxBuf[8];
                    nWalkMotorControlParam2 = ((unsigned short)nRxBuf[9] << 8) | (unsigned short)nRxBuf[10];
                    //nVoltage = ((unsigned short)nRxBuf[11] << 8) | (unsigned short)nRxBuf[12];
                    bKnockMotorInProcess = nRxBuf[11];
                    bKneadMotorInProcess = nRxBuf[12];
                    bWalkMotorInProcess = nRxBuf[13];
                    bUpdateLocate = nRxBuf[14];
                    nShoulderPosition = ((unsigned short)nRxBuf[15] << 8) | (unsigned short)nRxBuf[16];
                    nBackMainRunMode = nRxBuf[17];
                    nCurActionStepCounter = nRxBuf[18];
                    nCurKneadKnockSpeed = nRxBuf[19];
                    nCurKnockRunStopCounter = nRxBuf[20];
                    nCurKneadMotorCycles = nRxBuf[21];
                    upload_auto_step=2;//回传给主板，表示收到动作
                }
                else 
                {
                    upload_auto_step=1;//无需更新动作				
                }
            }
        }
        else if(nReceiveClass == 0xAA)
        {
            chk_sum=0;
            for ( i=1;i<3+nRxBuf[2];i++)
            {
                chk_sum+=nRxBuf[i];
            }
            chk_sum=~chk_sum;
            chk_sum&=0x7f;
            if(chk_sum==nRxBuf[3+nRxBuf[2]])
            {
                bMasterSendPacket = TRUE;//modify by dyl  20170426
                nKnockMotor_ControlParam1 = nRxBuf[3];
                nKneadMotor_ControlParam1 = nRxBuf[4];
                nKneadMotor_ControlParam2 = nRxBuf[5];
                nWalkMotor_ControlParam1 = nRxBuf[6];
                nWalkMotor_ControlParam2 = ((unsigned short)nRxBuf[7] << 8) | (unsigned short)nRxBuf[8];
                //nVoltage = ((unsigned short)nRxBuf[9] << 8) | (unsigned short)nRxBuf[10];
            }
        }
        //RX_Index = 0;
        //nSendCounter = 0;
        //_asm("rim");
    }
    if(nReceiveClass == 0xAB)
    {
        main_GetKneadPosition();
        WalkMotorControl(nWalkMotorControlParam1,nWalkMotorControlParam2);
        KneadMotorControl(nKneadMotorControlParam1,nKneadMotorControlParam2);
        KnockMotorControl(nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3);
    }
    else if(nReceiveClass == 0xAA)
    {
        nWalkMotorReturn = WalkMotor_Control(nWalkMotor_ControlParam1,nWalkMotor_ControlParam2);
        nKneadMotorReturn = KneadMotor_Control(nKneadMotor_ControlParam1,nKneadMotor_ControlParam2);
        KnockMotor_Set_Pwm_Data(nKnockMotor_ControlParam1);
    }
    if((bMasterSendPacket == TRUE)&&(b485SendFlag == TRUE))//modify by dyl  20170424
    {
        if(nReceiveClass == 0xAB)
        {
            nSendCount = 0;
            nSendTotalCount = 14;//dyl 20170426 //13;//11;
            for(i = 0;i < nSendTotalCount;i++)
            {
                nTxBuf[i] = 0;
            }
            nTxBuf[0] = 0x55;
            nTxBuf[1] = 0xAB;
            nTxBuf[2] = 9;//dyl 20170426 //8; //数据包长度
            nTxBuf[3] = bKnockMotorInProcess;
            nTxBuf[4] = bKneadMotorInProcess;
            nTxBuf[5] = bWalkMotorInProcess;
            nTxBuf[6] = (nShoulderPosition >> 8);
            nTxBuf[7] = nShoulderPosition;
            //nTxBuf[8] = nCurActionStepCounter;
            //nTxBuf[9] = nCurKnockRunStopCounter;
            nTxBuf[8] = (nCurWalkLocate >> 8);
            nTxBuf[9] = nCurWalkLocate;
            nTxBuf[10] = Input_GetKneadPosition();
            nTxBuf[11] = upload_auto_step;//dyl 20170426 
            chk_sum=0;
            chk_sum +=	nTxBuf[1];
            chk_sum +=	nTxBuf[2];
            chk_sum +=	nTxBuf[3];
            chk_sum +=	nTxBuf[4];
            chk_sum +=	nTxBuf[5];
            chk_sum +=	nTxBuf[6];
            chk_sum +=	nTxBuf[7];
            chk_sum +=	nTxBuf[8];
            chk_sum +=	nTxBuf[9];
            chk_sum +=	nTxBuf[10];
            chk_sum +=	nTxBuf[11];
            chk_sum =   ~chk_sum;
            chk_sum &=   0x7f;
            nTxBuf[12] = chk_sum;
            nTxBuf[13] = EOI_AB;
            bMax485De = TRUE;
            //i = 200;
            //while(i--);
            while(!(UART1_SR&0x40));//trasmission is not complete;
            UART1_DR = nTxBuf[nSendCount];
            nSendCount++;
            UART1_CR2 |= 0x48;
        }
        else if(nReceiveClass == 0xAA)
        {
            nSendCount = 0;
            nSendTotalCount = 7;
            for(i = 0;i < nSendTotalCount;i++)
            {
                nTxBuf[i] = 0;
            }
            nTxBuf[0] = 0x55;
            nTxBuf[1] = 0xAA;
            nTxBuf[2] = 2; //数据包长度
            nTxBuf[3] = nWalkMotorReturn;
            nTxBuf[4] = nKneadMotorReturn;
            chk_sum=0;
            chk_sum +=	nTxBuf[1];
            chk_sum +=	nTxBuf[2];
            chk_sum +=	nTxBuf[3];
            chk_sum +=	nTxBuf[4];
            chk_sum =   ~chk_sum;
            chk_sum &=   0x7f;
            nTxBuf[5] = chk_sum;
            nTxBuf[6] = EOI_AA;
            bMax485De = TRUE;
            //i = 200;
            //while(i--);
            while(!(UART1_SR&0x40));//trasmission is not complete;
            UART1_DR = nTxBuf[nSendCount];
            nSendCount++;
            UART1_CR2 |= 0x48;
        }
        bMasterSendPacket = FALSE;
        b485SendFlag = FALSE;//modify by dyl  20170424
    }
}
//-----------------------------------------------------------------------------
void main()
{
    asm("sim");		/* Disable interrupts */

    CLK_Init();
    GPIO_Init();
    TIM_Init();
    Time1Pwm_Init();
    Time2Pwm_Init();
    UART_Init();
    asm("rim");

    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");

    bMax485De = FALSE;
    bMasterSendPacket = FALSE;
    bWalkMotorInProcess = FALSE ;
    nWalkMotorControlParam1 = WALK_LOCATE_PARK ;
    nWalkMotorControlParam2 = 0 ;
    bUpdateLocate = TRUE ;     //行走电机坐标更新标志，置位时更新一次坐标
    nKneadMotorControlParam1 = KNEAD_STOP ;

    while(1)
    {
        Input_Proce();
        CommProcess();
        if(Timer_Counter(C_TIMER_RUN + T_LOOP,1))//work
        {
            nCurActionStepCounter++ ;  //syx 20160519
            nCurKnockRunStopCounter++ ;  //syx 20160519
        }
    }
}
