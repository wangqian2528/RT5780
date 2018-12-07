#include "STM8S103k.h" 
#include "WalkMotor.h"
#include "MotorCtrl.h"
#include "Input.h"

//static _Bool bFlag; 
volatile unsigned char nWalkLoss; 

void WalkMotor_10ms_Int(void)
{
    //bFlag = TRUE; 
    nWalkLoss++;
    if(nWalkLoss > 2)
    {
        //TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, 0);
        bWalkEnable = 0;
    }
}

/*
unsigned int WalkMotor_VoltageAdj(unsigned int setDuty)
{
    unsigned short adc24;      //此处的电压值已经扩大了100倍
    ADC_Get_Voltage(ADC_V24,&adc24);     
    if(adc24 <= WALK_SET_VOLTAGE/100) 
    {
        return setDuty;        //电压值偏低，返回预设值
    }
    unsigned int scale = WALK_SET_VOLTAGE / adc24; //计算与设定电压的比例值
    setDuty *= scale;
    unsigned int yushu = setDuty  % 100;
    setDuty /= 100;
    if(yushu > 50) setDuty++;
    return setDuty; 
}

void WalkMotor_Set_Pwm_Data(unsigned long ulDuty)
{
    unsigned int duty ;
    if(ulDuty == 0)
    {
        TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, ulDuty);
        return;
    }
    duty = TIMER_CompareBufGet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL);
    if(ulDuty == duty)
    {
        if(WalkMotor_Get_Fault() == WALK_MOTOR_NORMAL) return;
        WalkMotor_Reset();
        __no_operation();
        __no_operation();
        WalkMotor_Reset_Cancel();
        return; 
    }
    if(!bFlag) return;
    bFlag = false;
    if(duty < ulDuty)
    {
        if(duty < WALK_MOTOR_DEFAULT_TOP/2)
            duty = WALK_MOTOR_DEFAULT_TOP/2;
        else duty++;
    }
    TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, duty);
}
*/
static void WalkPower_On(void)
{
    //Power_On();
    // GPIO_PinOutSet(WALK_MOTOR_ENBL_PORT, WALK_MOTOR_ENBL_BIT);
    //WalkMotor_Set_Pwm_Data(WALK_MOTOR_DEFAULT_TOP);
		bWalkEnable = 1;
}
static void WalkPower_Off(void)
{
    //GPIO_PinOutClear(WALK_MOTOR_ENBL_PORT, WALK_MOTOR_ENBL_BIT);
    //WalkMotor_Set_Pwm_Data(0);
		bWalkEnable = 0;
}
//unsigned int WalkRelay_Get(void)
//{
    //return(GPIO_PinOutGet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT));
//}

unsigned int WalkMotor_GetDirection(void)
{
    if(bWalkPhase == 0)
    {
        return WALK_MOTOR_GO_UP;
    }
    return WALK_MOTOR_GO_DOWN;
}

unsigned int WalkPower_Get(void)
{
    //unsigned long  ulDuty;
    //ulDuty = TIMER_CompareBufGet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL);
    if(bWalkEnable == 1) return WALK_MOTOR_POWER_ON;
    else return WALK_MOTOR_POWER_OFF;
}

static void WalkMotor_Up(void)
{
    //Power_On();
    //GPIO_PinOutSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
    //GPIO_PinOutClear(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT);
    //GPIO_PinOutClear(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);
		bWalkReset = 1;
		bWalkPhase = 0;
		bWalkDecay = 0;
}
static void WalkMotor_Down(void)
{
    // Power_On();
    //GPIO_PinOutSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
    //GPIO_PinOutSet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT);
    //GPIO_PinOutClear(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);
		bWalkReset = 1;
		bWalkPhase = 1;
		bWalkDecay = 0;
}
static void WalkMotor_Break(void)
{
    //GPIO_PinOutClear(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);
    // GPIO_PinOutClear(WALK_MOTOR_ENBL_PORT, WALK_MOTOR_ENBL_BIT);
    //WalkMotor_Set_Pwm_Data(0);
		bWalkDecay = 0;
		bWalkEnable = 0;
}
/*
static void WalkMotor_Reset(void)
{
    //GPIO_PinOutClear(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
		bWalkReset = 0;
}
static void WalkMotor_Reset_Cancel(void)
{
    //GPIO_PinOutSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
		bWalkReset = 1;
}
*/

int WalkMotor_Get_Fault(void)
{
    if(bWalkFault == 1)
        return WALK_MOTOR_NORMAL;
    return WALK_MOTOR_FAIL;
}

unsigned char WalkMotor_Control(unsigned char nFinalWalkMotorState,unsigned short stopPosition)
{
    unsigned char nRetVal;
    _Bool bPowerFlag;
		unsigned short curPosition;
		
    nRetVal = FALSE;
    curPosition = Input_GetWalkMotorPosition();
    nWalkLoss = 0;
    //if(!LEUART0_isOK())
    //{
        //WalkMotor_Break();
        //WalkPower_Off();
        //return(unsigned char)(TRUE);
    //}
    switch(nFinalWalkMotorState)
    {
    case STATE_RUN_WALK_POSITION:  
        if(stopPosition > (curPosition + 3))
        {
            if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(TOP_POSITION);//2
                bPowerFlag = FALSE;
                nRetVal = TRUE ;
                //w_Position = 0;
                WalkMotor_Break();
                break;
            }
            WalkMotor_Up();
            bPowerFlag = TRUE;
            break;
        }
        if((stopPosition + 3) < curPosition)
        {
            if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(0);
                bPowerFlag = FALSE;
                nRetVal = TRUE ;
                //w_Position = BACK_MOTOR_MAX_POSITION;
                WalkMotor_Break();
                break;
            }
            WalkMotor_Down();
            bPowerFlag = TRUE;
            break;
        }
        bPowerFlag = FALSE;
        nRetVal = TRUE ;
        WalkMotor_Break();
        break;
    case STATE_RUN_WALK_DOWN:  //back motor go down
        if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
        {
            Input_SetWalkMotorPosition(0);
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            //w_Position = BACK_MOTOR_MAX_POSITION;
            WalkMotor_Break();
            break;
        }
        WalkMotor_Down();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_WALK_UP:  //back motor go up
        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
        {
            Input_SetWalkMotorPosition(TOP_POSITION);//3
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            //w_Position = 0;
            WalkMotor_Break();
            break;
        }
        WalkMotor_Up();
        bPowerFlag = TRUE;
        break ;
    case STATE_WALK_IDLE:
        nRetVal = TRUE ;
        WalkMotor_Break();
        bPowerFlag = FALSE;
        break ;
    default://异常处理
        break ;
    }
    //电源部分的处理
    if(bPowerFlag == TRUE)
    {
        WalkPower_On();
    }
    else
    {
        WalkPower_Off();
    }
    return nRetVal ;
}