#include "STM8S103k.h" 
#include "KnockMotor.h"

extern unsigned short nVoltage;

void KnockMotor_Enbl(void)
{
    //GPIO_PinOutClear(KNOCK_MOTOR_ENBL_PORT, KNOCK_MOTOR_ENBL_BIT);
    bKnockReset = 0;
}
void KnockMotor_DisEnbl(void)
{
    //GPIO_PinOutSet(KNOCK_MOTOR_ENBL_PORT, KNOCK_MOTOR_ENBL_BIT);
    bKnockReset = 1;
}

unsigned int KnockMotor_VoltageAdj(unsigned int setDuty)
{
    unsigned short adc24;      //此处的电压值已经扩大了100倍
    unsigned int scale,yushu;
    //ADC_Get_Voltage(ADC_V24,&adc24);
    adc24 = nVoltage;		
    if(adc24 <= KNOCK_SET_VOLTAGE/100) 
    {
        return setDuty;        //电压值偏低，返回预设值
    }
    scale = KNOCK_SET_VOLTAGE / adc24; //计算与设定电压的比例值
    setDuty *= scale;
    
    yushu = setDuty  % 100;
    setDuty /= 100;
    if(yushu > 50) setDuty++;
    return setDuty; 
}

void KnockMotor_Set_Pwm_Data(unsigned int ulDuty)
{
    if(ulDuty == 0)
    {
        //TIMER_CompareBufSet(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_TIMER_CHANNEL, ulDuty);
        TIM2_CCR1H = 0;
        TIM2_CCR1L = ulDuty;
        return;
    }
    
    //ulDuty = KnockMotor_VoltageAdj(ulDuty);
    
    if(KnockMotor_Get_Fault() == KNOCK_MOTOR_FAIL) 
    {
        KnockMotor_DisEnbl();
        //__no_operation();
        //__no_operation();
        asm("nop");
        asm("nop");
        KnockMotor_Enbl();
    }
    //TIMER_CompareBufSet(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_TIMER_CHANNEL, ulDuty);
    TIM2_CCR1H = 0;
    TIM2_CCR1L = ulDuty;
}

void KnockMotor_ClockRun(void)
{
    //GPIO_PinOutSet(KNOCK_MOTOR_ENBL_PORT, KNOCK_MOTOR_RESET_BIT);
    //GPIO_PinOutClear(KNOCK_MOTOR_PHASE_PORT, KNOCK_MOTOR_PHASE_BIT);
    //GPIO_PinOutClear(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT);
}
void KnockMotor_UnClockRun(void)
{
    //GPIO_PinOutSet(KNOCK_MOTOR_ENBL_PORT, KNOCK_MOTOR_RESET_BIT);
    //GPIO_PinOutClear(KNOCK_MOTOR_PHASE_PORT, KNOCK_MOTOR_PHASE_BIT);
    //GPIO_PinOutClear(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT);
}
void KnockMotor_Break(void)
{
    KnockMotor_Set_Pwm_Data(0);
    //GPIO_PinOutClear(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT);
}

int KnockMotor_Get_Fault(void)
{
    if(bKnockFault == 1)
    return KNOCK_MOTOR_NORMAL;
    return KNOCK_MOTOR_FAIL;
}