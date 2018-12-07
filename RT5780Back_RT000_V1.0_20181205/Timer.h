#ifndef __TIMER_H__
#define __TIMER_H__

#define T_LOOP 0x80

#define C_TIMER_RUN     1
#define C_TIME_RUBBING  6

void Timer_Initial(void);
void Timer_Flag_100ms_Int(void);
void Timer_Counter_Clear(char by_Index);
char Timer_Counter(char by_Mode,unsigned int w_Dat);

#endif
