#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__

#define TOP_BY_LIMIT

#define KNOCK_STOP		    0 //ֹͣ
#define KNOCK_RUN_WIDTH		1 //����խ��λ��ɺ�����
#define KNOCK_RUN		      2 //�������խ��λ����������������
#define KNOCK_RUN_STOP		3 //����խ��λ��ɺ�������ʱ�������ֹͣ
#define KNOCK_RUN_MUSIC		4 //���ֻ���ģʽ�������խ��λ�޹أ�

#define KNOCK_SPEED0_PWM 	0       //0%
#define KNOCK_SPEED1_PWM 	50//300
#define KNOCK_SPEED2_PWM 	60//350
#define KNOCK_SPEED3_PWM 	70//400
#define KNOCK_SPEED4_PWM 	80//450
#define KNOCK_SPEED5_PWM 	90//500
#define KNOCK_SPEED6_PWM 	101//550

//�̵���+Mosfet+Brake��·���״̬����(�޼̵���ֻȡǰ��5��״̬)
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
//��������������
#define KNEAD_STOP			    0 //��Ħ��ͣ�������λ��
#define KNEAD_STOP_AT_MIN		1 //��Ħ��ͣ����խ��λ��
#define KNEAD_STOP_AT_MED		2 //��Ħ��ͣ�����е�λ��
#define KNEAD_STOP_AT_MAX		3 //��Ħ��ͣ���ڿ��λ��
#define KNEAD_RUN		       	4 //��Ħ��˳ʱ�ӷ�������
#define KNEAD_RUN_STOP		 	5 //��Ħ��CLOCK����nȦ��ͣ�������λ��
#define KNEAD_RUN_STOP_AT_MIN 	        6 //��Ħ��CLOCK����nȦ��ͣ����խ��λ��
#define KNEAD_RUN_STOP_AT_MED 	        7 //��Ħ��CLOCK����nȦ��ͣ�����е�λ��
#define KNEAD_RUN_STOP_AT_MAX 	        8 //��Ħ��CLOCK����nȦ��ͣ���ڿ��λ��
#define KNEAD_RUN_RUBBING 	            9 //

#define STATE_RUN_WALK_DOWN     0
#define STATE_RUN_WALK_UP       1
#define STATE_WALK_IDLE         2
#define STATE_RUN_WALK_POSITION 3

//���ߵ����λ��ʽ
#define WALK_LOCATE_ABSULATE			        0
#define WALK_LOCATE_SHOULDER			        3  //���λ��
#define WALK_LOCATE_TOP				            2
#define WALK_LOCATE_SHOULDER_OR_ABSULATE	1
#define WALK_LOCATE_PARK			            4
//#define WALK_LOCATE_NeckSwitch			     5
#define WALK_LOCATE_NeckMed			          6  //�����м�λ��
#define WALK_LOCATE_PressNeck			        7  //���ӿ������ λ��

#define WALK_LOCATE_WAIST             8
#define WALK_SHOULDER_WAIST_1_10      9  //���������λ���ƶ�1/10�ľ���
#define WALK_SHOULDER_WAIST_2_10      10 //���������λ���ƶ�2/10�ľ���
#define WALK_SHOULDER_WAIST_3_10      11 //���������λ���ƶ�3/10�ľ���
#define WALK_SHOULDER_WAIST_4_10      12 //���������λ���ƶ�4/10�ľ���
#define WALK_SHOULDER_WAIST_5_10      13 //���������λ���ƶ�5/10�ľ���
#define WALK_SHOULDER_WAIST_6_10      14 //���������λ���ƶ�6/10�ľ���
#define WALK_SHOULDER_WAIST_7_10      15 //���������λ���ƶ�7/10�ľ���
#define WALK_SHOULDER_WAIST_8_10      16 //���������λ���ƶ�8/10�ľ���
#define WALK_SHOULDER_WAIST_9_10      17 //���������λ���ƶ�9/10�ľ���

//����������ģʽ
#define BACK_MAIN_MODE_IDLE			                0 //��CHAIR_STATE_IDLE��Ӧ
#define BACK_MAIN_MODE_SETTLE		                1 //��CHAIR_STATE_SETTLE��Ӧ 
#define BACK_MAIN_MODE_AUTO			                2	
#define BACK_MAIN_MODE_MANUAL		                3
#define BACK_MAIN_MODE_3D                       4
#define BACK_MAIN_MODE_DEMO                     5

//�г̲���
#define BODY_TOUCHED                            1//8600s�޸�ΪͨѶ��ʽ����Ϊ�߼�1���󱳹��������ʱ��ֵ
#define BODY_NO_TOUCHED                         0//8600s�޸�ΪͨѶ��ʽ����Ϊ�߼�1���󱳹��������ʱ��ֵ
#define LIMIT_POSITION				                  112//280//8600 100  //���λ�õ���͵�
#define TOP_POSITION 				                    160//399//397//8600 215  //���λ�õ���ߵ�
#define RESET_POSITION				                  (TOP_POSITION - 12)//(TOP_POSITION - 30)
#define WAIST_POSITION 				                  52//130
#define BUTTOCKS_POSITION 			                20//50
#define LIMIT_PRECISION                         4//10

//�ﵽ����λ�õ��źŵ�ƽ
#define REACH_WALK_LIMIT    0   //hull
#define REACH_BACK_LIMIT    1   //limit switch
#define REACH_LEG_LIMIT     1   //limit switch
#define REACH_SLIDE_LIMIT   1   //limit switch
#define REACH_AXIS_LIMIT    1   //limit switch
#define REACH_FLEX_LIMIT    0   //hull

//��粿��λ��صĳ���
#define DEFAULT_SHOULDER_POSITION	                  148//370//330
#define DEFAULT_SHOULDER_POSITION_RELAX	            122//305
#define DEFAULT_NECK_LENGTH		                      12//30  
#define Med_NECK_LENGTH			                        6//15  
#define MAX_SHOULDER_ADJUST_TIME	                  100 //�粿΢��ʱ�䣬��λ��100ms
#define SHOULDER_ADJUST_STEP		                    12//30
#define MAX_SHOULDER_ADJUST_DIFF	                  20//52 //�粿���΢�����룺5*SHOULDER_ADJUST_STEP + 2(������ʾ�͹���)

//���ߵ��ʱ����������
#define MAX_PARK_TIME			0xff //���㷽ʽʱ��WalkMotorControl()����������ֵ��ȷ��SOFT_KNOCK����

void main_GetKneadPosition(void);
void KnockMotorControl(unsigned char nKnockMotorState,unsigned char nKnockingMotorRunTime,unsigned char nKnockingMotorStopTime);
void KneadMotorControl(unsigned char nKneadMotorState,unsigned char nKneadMotorCycles);
unsigned char WalkMotorControl(unsigned char nWalkMotorLocateMethod,unsigned short nWalkMotorLocateParam);

#endif