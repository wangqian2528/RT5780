#include "STM8S103k.h"
#include "MotorCtrl.h"
#include "Input.h"

typedef  struct
{
    unsigned char timer_H;
    unsigned char timer_L;
    unsigned char flag;
}INPUT_ST;

INPUT_ST st_WalkUp,st_WalkDown;

static _Bool b5msFlag;
static _Bool bKneadMin,bKneadMid,bKneadMax;
static unsigned char by_KneadPosition = KNEAD_WIDTH_UNKNOWN;

volatile unsigned int nCurWalkLocate;

void Input_SetWalkMotorPosition(unsigned int locate)
{
    //nCurWalkLocate = (unsigned int)(locate*2);
		nCurWalkLocate = locate;
}

unsigned int Input_GetWalkMotorPosition(void)
{
    //return(nCurWalkLocate/2);
		return nCurWalkLocate;
}

void Input_5ms_Int(void)
{
    b5msFlag = 1;
}

void Input_High(INPUT_ST* p)
{
    p->timer_L = 0;
    p->timer_H ++; 
    if((p->timer_H) >= 2)
    {
        p->timer_H = 2;
        p->flag = 1;
    }
}
void Input_Low(INPUT_ST* p)
{
    p->timer_H = 0;
    p->timer_L ++; 
    if((p->timer_L) >= 2)
    {
        p->timer_L = 2;
        p->flag = 0;
    }
}

void Input_Proce(void)
{
		if(!b5msFlag) return;		
    b5msFlag = 0;
	
    if(bKneadMinBit == 0)
    {
        by_KneadPosition = KNEAD_WIDTH_MIN;    
        bKneadMin = 0;
        bKneadMid = 1; 
        bKneadMax = 1;
    }
    if(bKneadMedBit == 0)
    {
        by_KneadPosition = KNEAD_WIDTH_MED;    
        bKneadMin = 1;
        bKneadMid = 0; 
        bKneadMax = 1;
    }
    if(bKneadMaxBit == 0)
    {
        by_KneadPosition = KNEAD_WIDTH_MAX;  
        bKneadMin = 1;
        bKneadMid = 1; 
        bKneadMax = 0;
    }

    bWalkUpSW ? Input_High(&st_WalkUp):Input_Low(&st_WalkUp);
    bWalkDownSW ? Input_High(&st_WalkDown):Input_Low(&st_WalkDown);
}

//return 0 or 1
unsigned int Input_GetKneadMax(void)
{
    return(bKneadMax);
}
//return 0 or 1
unsigned int Input_GetKneadMid(void)
{
    return(bKneadMid);
}
//return 0 or 1
unsigned int Input_GetKneadMin(void)
{
    return(bKneadMin);
}

unsigned int Input_GetKneadPosition(void)
{
    return (unsigned int)by_KneadPosition;
}

unsigned int Input_GetWalkUpSwitch(void)
{
    return(st_WalkUp.flag);
}

unsigned int Input_GetWalkDownSwitch(void)
{
    return(st_WalkDown.flag);
}