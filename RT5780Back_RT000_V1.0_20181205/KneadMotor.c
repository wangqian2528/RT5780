#include "STM8S103k.h" 
#include "Input.h"
#include "KneadMotor.h"

//unsigned int w_KneadCurrent = 8;
static unsigned int motorStatus = MOTOR_STOP_BREAK;
static volatile unsigned int motorBreakTime;
static volatile unsigned int kneadCounter;
//static unsigned int kneadSpeed;
volatile unsigned char nKneadLoss;

extern unsigned short nVoltage;

static void KneadMotor_Set_Pwm_Data(unsigned int ulDuty);

void KneadMotor_Reset(void)
{
    //GPIO_PinOutClear(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
		bKneadReset = 0;
}

void KneadMotor_Reset_Cancel(void)
{
    //GPIO_PinOutSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
		bKneadReset = 1;
}
void KneadMotorBrake_On(void)
{
    KneadMotor_Set_Pwm_Data(0);
    //GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
		bKneadDecay = 0;
}
void KneadMotorBrake_Off(void)
{
    KneadMotor_Set_Pwm_Data(0);
    //GPIO_PinOutSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
		bKneadDecay = 1;
}
void KneadMotor_10ms_Int(void)
{
    kneadCounter++;
    nKneadLoss++;
    if(nKneadLoss > 2)
    {
        //TIMER_CompareBufSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, 0);
				TIM1_CCR4H = 0;
				TIM1_CCR4L = 0;
    }
}
//当电机电源电压大于预设值时，设定占空比按比例缩小，否则设定占空比不变
unsigned int KneadMotor_VoltageAdj(unsigned int setDuty)
{
    unsigned short adc24;      //此处的电压值已经扩大了100倍
		unsigned int scale,yushu;
    //ADC_Get_Voltage(ADC_V24,&adc24);   
    adc24 = nVoltage;		
    if(adc24 <= KNEAD_SET_VOLTAGE) 
    {
        return setDuty;        //电压值偏低，返回预设值
    }
    scale = KNEAD_SET_VOLTAGE *100 / adc24; //计算与设定电压的比例值,百分之scale
    setDuty *= scale;
    yushu = setDuty  % 100;
    setDuty /= 100;   //setDuty乘以百分之scale
    if(yushu > 50) setDuty++;
    return setDuty; 
}

void KneadMotor_Set_Pwm_Data(unsigned int ulDuty)
{
    if(ulDuty == 0)
    {
        //TIMER_CompareBufSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, ulDuty);
				TIM1_CCR4H = 0;
				TIM1_CCR4L = ulDuty;
        return;
    }
    if(KneadMotor_Get_Fault() == KNEAD_MOTOR_FAIL) 
    {
        KneadMotor_Reset();
			  asm("nop");
			  asm("nop");
        KneadMotor_Reset_Cancel();
    } 
    //ulDuty = KneadMotor_VoltageAdj(ulDuty);
    //TIMER_CompareBufSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, ulDuty);
		TIM1_CCR4H = 0;
		TIM1_CCR4L = ulDuty;
    motorStatus = MOTOR_RUN;
}
_Bool KneadMotor_IsRun(void)
{
    unsigned int ulDuty;
    //ulDuty = TIMER_CompareBufGet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL);
    ulDuty = TIM1_CCR4L;
		if(ulDuty > 0) return 1;
    else return 0;
}

void KneadMotor_ClockRun(void)
{
    //GPIO_PinOutSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
    //GPIO_PinOutSet(KNEAD_MOTOR_PHASE_PORT, KNEAD_MOTOR_PHASE_BIT);
    //GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
		bKneadReset = 1;
		bKneadPhase = 1;
		bKneadDecay = 0;
}
void KneadMotor_UnClockRun(void)
{
    //GPIO_PinOutSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
    //GPIO_PinOutClear(KNEAD_MOTOR_PHASE_PORT, KNEAD_MOTOR_PHASE_BIT);
    //GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
		bKneadReset = 1;
		bKneadPhase = 0;
		bKneadDecay = 0;
}
void KneadMotor_Break(void)
{
    KneadMotor_Set_Pwm_Data(0);    //关闭马达电源
    if(motorStatus == MOTOR_RUN)
    {
        //GPIO_PinOutSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT); //使马达端口处于高阻，此时马达属于惯性滑行
				bKneadDecay = 1;
        motorStatus = MOTOR_STOP_HZ;
        motorBreakTime = 0;
    }
    if(motorStatus == MOTOR_STOP_HZ)
    {
        if(motorBreakTime < MOTOR_STOP_HZ_TIME) return;
    }
    //GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);  //短路马达，保持马达在刹车状态
		bKneadDecay = 0;
    motorStatus = MOTOR_STOP_BREAK;
}

int KneadMotor_Get_Fault(void)
{
    if(bKneadFault == 1)
        return KNEAD_MOTOR_NORMAL;
    return KNEAD_MOTOR_FAIL;
}

void KneadMotorUpdateSpeed(unsigned int speed)
{
    switch(speed)
    {
    default:  
    case 0: KneadMotor_Set_Pwm_Data(KNEAD_SPEED0_PWM); break;
    case 1: KneadMotor_Set_Pwm_Data(KNEAD_SPEED1_PWM); break;
    case 2: KneadMotor_Set_Pwm_Data(KNEAD_SPEED2_PWM); break;
    case 3: KneadMotor_Set_Pwm_Data(KNEAD_SPEED3_PWM); break;
    case 4: KneadMotor_Set_Pwm_Data(KNEAD_SPEED4_PWM); break;
    case 5: KneadMotor_Set_Pwm_Data(KNEAD_SPEED5_PWM); break;
    case 6: KneadMotor_Set_Pwm_Data(KNEAD_SPEED6_PWM); break;
    }
}
//Knead motor control function
unsigned int KneadMotor_Control(unsigned int nMotorState,unsigned int PWM)
{
    //  static unsigned int kneadPosition =  KNEAD_WIDTH_UNKNOWN; 
    unsigned int nRetVal;
    _Bool bPowerFlag;
    nRetVal = FALSE;
    nKneadLoss =0;
    switch(nMotorState)
    {
    case STATE_KNEAD_STOP_AT_MIN:
        //if(KNEAD_WIDTH_MIN == Input_GetKneadPosition())
        if(Input_GetKneadMin() == 0)
        {
            //kneadPosition = KNEAD_WIDTH_MIN;
            nRetVal = TRUE ;
            KneadMotor_Break();
            bPowerFlag = FALSE;
            break ;  
        }
        PWM = KNEAD_SPEED2_PWM;
        KneadMotor_ClockRun();
        bPowerFlag = TRUE;
        break;
    case STATE_KNEAD_STOP_AT_MED:
        //if(KNEAD_WIDTH_MED == Input_GetKneadPosition())
        if(Input_GetKneadMid() == 0)
        {
            //kneadPosition = KNEAD_WIDTH_MED;
            nRetVal = TRUE ;
            KneadMotor_Break();
            bPowerFlag = FALSE;
            break ;  
        }
        PWM = KNEAD_SPEED2_PWM;
        KneadMotor_ClockRun();
        bPowerFlag = TRUE;
        break;
    case STATE_KNEAD_STOP_AT_MAX:  
        //if(KNEAD_WIDTH_MAX == Input_GetKneadPosition())
        if(Input_GetKneadMax() == 0)
        {
            //kneadPosition = KNEAD_WIDTH_MAX;
            nRetVal = TRUE ;
            KneadMotor_Break();
            bPowerFlag = FALSE;
            break ;  
        }
        PWM = KNEAD_SPEED2_PWM;
        KneadMotor_ClockRun();
        bPowerFlag = TRUE;
        break;
    case STATE_KNEAD_CLOCK_RUN:    //顺时针旋转
        nRetVal = FALSE ;
        KneadMotor_ClockRun();
        bPowerFlag = TRUE;
        break;
    case STATE_KNEAD_UNCLOCK_RUN:  //逆时针旋转
        nRetVal = FALSE ;
        KneadMotor_UnClockRun();
        bPowerFlag = TRUE;
        break;
    default:
    case STATE_KNEAD_IDLE:
        nRetVal = TRUE ;
        KneadMotor_Break();
        bPowerFlag = FALSE;
        break;  
    } 
    //电源部分的处理
    if(bPowerFlag == TRUE)
    {
        KneadMotor_Set_Pwm_Data(PWM);
    }
    else
    {
        KneadMotor_Set_Pwm_Data(0);
    }
    return nRetVal ;
}