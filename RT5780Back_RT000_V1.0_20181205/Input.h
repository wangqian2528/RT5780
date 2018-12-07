#ifndef __INPUT_H__
#define __INPUT_H__

void Input_5ms_Int(void);

void Input_SetWalkMotorPosition(unsigned int locate);
unsigned int Input_GetWalkMotorPosition(void);

unsigned int Input_GetKneadMax(void);
unsigned int Input_GetKneadMid(void);
unsigned int Input_GetKneadMin(void);
unsigned int Input_GetKneadPosition(void);

unsigned int Input_GetWalkUpSwitch(void);
unsigned int Input_GetWalkDownSwitch(void);

void Input_Proce(void);

#endif