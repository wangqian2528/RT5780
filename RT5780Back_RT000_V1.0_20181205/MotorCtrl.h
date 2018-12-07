#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__

#define TOP_BY_LIMIT

#define KNOCK_STOP		    0 //停止
#define KNOCK_RUN_WIDTH		1 //宽中窄定位完成后启动
#define KNOCK_RUN		      2 //无需宽中窄定位，无条件立即启动
#define KNOCK_RUN_STOP		3 //宽中窄定位完成后启动短时间后马上停止
#define KNOCK_RUN_MUSIC		4 //音乐互动模式（与宽中窄定位无关）

#define KNOCK_SPEED0_PWM 	0       //0%
#define KNOCK_SPEED1_PWM 	50//300
#define KNOCK_SPEED2_PWM 	60//350
#define KNOCK_SPEED3_PWM 	70//400
#define KNOCK_SPEED4_PWM 	80//450
#define KNOCK_SPEED5_PWM 	90//500
#define KNOCK_SPEED6_PWM 	101//550

//继电器+Mosfet+Brake电路电机状态定义(无继电器只取前面5种状态)
#define STATE_IDLE				                0
#define STATE_RUN_CLOCK				            1
#define STATE_STOP_CLOCK_HV			          2
#define STATE_STOP_CLOCK_BRAKE		        3
#define STATE_STOP_CLOCK_ZV			          4
#define STATE_RUN_ANTICLOCK			          5
#define STATE_STOP_ANTICLOCK_HV		        6
#define STATE_STOP_ANTICLOCK_BRAKE	      7
#define STATE_STOP_ANTICLOCK_ZV		        8
#define STATE_RUN_UNCLOCK			            9

#define KNEAD_SPEED0_PWM  0 //0% 100%:560
#define KNEAD_SPEED1_PWM 	50//85//105//85//70//300
#define KNEAD_SPEED2_PWM 	60//95//111//95//82//60//350
#define KNEAD_SPEED3_PWM 	70//105//117//105//94//45//400
#define KNEAD_SPEED4_PWM 	80//115//122//115//106//30//450
#define KNEAD_SPEED5_PWM 	90//125//127//125//118//15//500
#define KNEAD_SPEED6_PWM 	101//131//132//0//560

#define KNEAD_WIDTH_UNKNOWN		0
#define KNEAD_WIDTH_MIN			1
#define KNEAD_WIDTH_MED			2
#define KNEAD_WIDTH_MAX			3

#define STATE_KNEAD_CLOCK_RUN     1
#define STATE_KNEAD_UNCLOCK_RUN   2
#define STATE_KNEAD_IDLE          0

#define STATE_KNEAD_STOP_AT_MIN   3
#define STATE_KNEAD_STOP_AT_MED   4  
#define STATE_KNEAD_STOP_AT_MAX   5  
//揉捏电机描述常数
#define KNEAD_STOP			    0 //按摩臂停留在随机位置
#define KNEAD_STOP_AT_MIN		1 //按摩臂停留在窄的位置
#define KNEAD_STOP_AT_MED		2 //按摩臂停留在中的位置
#define KNEAD_STOP_AT_MAX		3 //按摩臂停留在宽的位置
#define KNEAD_RUN		       	4 //按摩臂顺时钟方向揉捏
#define KNEAD_RUN_STOP		 	5 //按摩臂CLOCK方向n圈后停留在随机位置
#define KNEAD_RUN_STOP_AT_MIN 	        6 //按摩臂CLOCK方向n圈后停留在窄的位置
#define KNEAD_RUN_STOP_AT_MED 	        7 //按摩臂CLOCK方向n圈后停留在中的位置
#define KNEAD_RUN_STOP_AT_MAX 	        8 //按摩臂CLOCK方向n圈后停留在宽的位置
#define KNEAD_RUN_RUBBING 	            9 //

#define STATE_RUN_WALK_DOWN     0
#define STATE_RUN_WALK_UP       1
#define STATE_WALK_IDLE         2
#define STATE_RUN_WALK_POSITION 3

//行走电机定位方式
#define WALK_LOCATE_ABSULATE			        0
#define WALK_LOCATE_SHOULDER			        3  //肩膀位置
#define WALK_LOCATE_TOP				            2
#define WALK_LOCATE_SHOULDER_OR_ABSULATE	1
#define WALK_LOCATE_PARK			            4
//#define WALK_LOCATE_NeckSwitch			     5
#define WALK_LOCATE_NeckMed			          6  //脖子中间位置
#define WALK_LOCATE_PressNeck			        7  //脖子靠近肩膀 位置

#define WALK_LOCATE_WAIST             8
#define WALK_SHOULDER_WAIST_1_10      9  //肩膀向腰的位置移动1/10的距离
#define WALK_SHOULDER_WAIST_2_10      10 //肩膀向腰的位置移动2/10的距离
#define WALK_SHOULDER_WAIST_3_10      11 //肩膀向腰的位置移动3/10的距离
#define WALK_SHOULDER_WAIST_4_10      12 //肩膀向腰的位置移动4/10的距离
#define WALK_SHOULDER_WAIST_5_10      13 //肩膀向腰的位置移动5/10的距离
#define WALK_SHOULDER_WAIST_6_10      14 //肩膀向腰的位置移动6/10的距离
#define WALK_SHOULDER_WAIST_7_10      15 //肩膀向腰的位置移动7/10的距离
#define WALK_SHOULDER_WAIST_8_10      16 //肩膀向腰的位置移动8/10的距离
#define WALK_SHOULDER_WAIST_9_10      17 //肩膀向腰的位置移动9/10的距离

//背背运行主模式
#define BACK_MAIN_MODE_IDLE			                0 //与CHAIR_STATE_IDLE对应
#define BACK_MAIN_MODE_SETTLE		                1 //与CHAIR_STATE_SETTLE对应 
#define BACK_MAIN_MODE_AUTO			                2	
#define BACK_MAIN_MODE_MANUAL		                3
#define BACK_MAIN_MODE_3D                       4
#define BACK_MAIN_MODE_DEMO                     5

//行程参数
#define BODY_TOUCHED                            1//8600s修改为通讯方式，改为逻辑1，后背光耦开关碰到时的值
#define BODY_NO_TOUCHED                         0//8600s修改为通讯方式，改为逻辑1，后背光耦开关碰到时的值
#define LIMIT_POSITION				                  112//280//8600 100  //肩膀位置的最低点
#define TOP_POSITION 				                    160//399//397//8600 215  //肩膀位置的最高点
#define RESET_POSITION				                  (TOP_POSITION - 12)//(TOP_POSITION - 30)
#define WAIST_POSITION 				                  52//130
#define BUTTOCKS_POSITION 			                20//50
#define LIMIT_PRECISION                         4//10

//达到极限位置的信号电平
#define REACH_WALK_LIMIT    0   //hull
#define REACH_BACK_LIMIT    1   //limit switch
#define REACH_LEG_LIMIT     1   //limit switch
#define REACH_SLIDE_LIMIT   1   //limit switch
#define REACH_AXIS_LIMIT    1   //limit switch
#define REACH_FLEX_LIMIT    0   //hull

//与肩部定位相关的常数
#define DEFAULT_SHOULDER_POSITION	                  148//370//330
#define DEFAULT_SHOULDER_POSITION_RELAX	            122//305
#define DEFAULT_NECK_LENGTH		                      12//30  
#define Med_NECK_LENGTH			                        6//15  
#define MAX_SHOULDER_ADJUST_TIME	                  100 //肩部微调时间，单位：100ms
#define SHOULDER_ADJUST_STEP		                    12//30
#define MAX_SHOULDER_ADJUST_DIFF	                  20//52 //肩部最大微调距离：5*SHOULDER_ADJUST_STEP + 2(考虑显示和惯性)

//行走电机时间描述常数
#define MAX_PARK_TIME			0xff //定点方式时，WalkMotorControl()函数不返回值，确保SOFT_KNOCK正常

void main_GetKneadPosition(void);
void KnockMotorControl(unsigned char nKnockMotorState,unsigned char nKnockingMotorRunTime,unsigned char nKnockingMotorStopTime);
void KneadMotorControl(unsigned char nKneadMotorState,unsigned char nKneadMotorCycles);
unsigned char WalkMotorControl(unsigned char nWalkMotorLocateMethod,unsigned short nWalkMotorLocateParam);

#endif