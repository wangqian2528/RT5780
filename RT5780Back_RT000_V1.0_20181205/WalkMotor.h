#ifndef __WALK_MOTOR_H__
#define __WALK_MOTOR_H__

#define STATE_RUN_WALK_DOWN     0
#define STATE_RUN_WALK_UP       1
#define STATE_WALK_IDLE         2
#define STATE_RUN_WALK_POSITION 3

enum
{
    WALK_MOTOR_POWER_ON, 
    WALK_MOTOR_POWER_OFF 
};

enum
{
    WALK_MOTOR_GO_UP, 
    WALK_MOTOR_GO_DOWN 
};

enum
{
    WALK_MOTOR_NORMAL,
    WALK_MOTOR_FAIL
};

void WalkMotor_10ms_Int(void);
unsigned char WalkMotor_Control(unsigned char nFinalWalkMotorState,unsigned short stopPosition);
unsigned int WalkMotor_GetDirection(void);

#endif

