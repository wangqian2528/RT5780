/* STM8S103K.h */

/* Copyright (c) 2003-2013 STMicroelectronics */

#ifndef __STM8S103K__
#define __STM8S103K__


typedef struct
{
	unsigned BIT0:1;
	unsigned BIT1:1;
	unsigned BIT2:1;
	unsigned BIT3:1;
	unsigned BIT4:1;
	unsigned BIT5:1;
	unsigned BIT6:1;
	unsigned BIT7:1;
}ST_BITS;

typedef struct
{
	ST_BITS ODR;
	ST_BITS IDR;
	ST_BITS DDR;
	ST_BITS CR1;
	ST_BITS CR2;
}GPIO;

#define PA      (*(volatile GPIO*)0x5000)
#define PB      (*(volatile GPIO*)0x5005)
#define PC      (*(volatile GPIO*)0x500a)
#define PD      (*(volatile GPIO*)0x500f)
#define PE      (*(volatile GPIO*)0x5014)
#define PF      (*(volatile GPIO*)0x5019)


#define TRUE      1
#define FALSE     0

#define EOI_AB  0XF1
#define EOI_AA  0XF2

#define SOI		0x55	

#define MAX_SEND_COUNT			14
#define MAX_RECEIVE_COUNT		25

#define bMax485De	      PD.ODR.BIT7

#define bWalkEnable     PA.ODR.BIT3
#define bWalkReset      PE.ODR.BIT5
#define bWalkPhase      PF.ODR.BIT4
#define bWalkDecay			PB.ODR.BIT7	
#define bWalkFault  		PB.IDR.BIT6

#define bKneadReset     PD.ODR.BIT0
#define bKneadPhase     PC.ODR.BIT5
#define bKneadDecay			PC.ODR.BIT6	
#define bKneadFault  		PC.IDR.BIT7

#define bKnockReset     PD.ODR.BIT2
#define bKnockFault     PD.IDR.BIT3

#define bKneadMaxBit    PC.IDR.BIT3
#define bKneadMedBit    PC.IDR.BIT2
#define bKneadMinBit    PC.IDR.BIT1
#define bWalkUpSW       PA.IDR.BIT2
#define bWalkDownSW     PA.IDR.BIT1



/* Port A */
/*****************************************************************/

#define         PA_ODR                    (*(volatile unsigned char*)0x5000)
#define         PA_IDR                    (*(volatile unsigned char*)0x5001)
#define         PA_DDR                    (*(volatile unsigned char*)0x5002)
#define         PA_CR1                    (*(volatile unsigned char*)0x5003)
#define         PA_CR2                    (*(volatile unsigned char*)0x5004)


/* Port B */
/*****************************************************************/

#define         PB_ODR                    (*(volatile unsigned char*)0x5005)
#define         PB_IDR                    (*(volatile unsigned char*)0x5006)
#define         PB_DDR                    (*(volatile unsigned char*)0x5007)
#define         PB_CR1                    (*(volatile unsigned char*)0x5008)
#define         PB_CR2                    (*(volatile unsigned char*)0x5009)


/* Port C */
/*****************************************************************/

#define         PC_ODR                    (*(volatile unsigned char*)0x500a)
#define         PC_IDR                    (*(volatile unsigned char*)0x500b)
#define         PC_DDR                    (*(volatile unsigned char*)0x500c)
#define         PC_CR1                    (*(volatile unsigned char*)0x500d)
#define         PC_CR2                    (*(volatile unsigned char*)0x500e)


/* Port D */
/*****************************************************************/

#define         PD_ODR                    (*(volatile unsigned char*)0x500f)
#define         PD_IDR                    (*(volatile unsigned char*)0x5010)
#define         PD_DDR                    (*(volatile unsigned char*)0x5011)
#define         PD_CR1                    (*(volatile unsigned char*)0x5012)
#define         PD_CR2                    (*(volatile unsigned char*)0x5013)


/* Port E */
/*****************************************************************/

#define         PE_ODR                    (*(volatile unsigned char*)0x5014)
#define         PE_IDR                    (*(volatile unsigned char*)0x5015)
#define         PE_DDR                    (*(volatile unsigned char*)0x5016)
#define         PE_CR1                    (*(volatile unsigned char*)0x5017)
#define         PE_CR2                    (*(volatile unsigned char*)0x5018)


/* Port F */
/*****************************************************************/

#define         PF_ODR                    (*(volatile unsigned char*)0x5019)
#define         PF_IDR                    (*(volatile unsigned char*)0x501a)
#define         PF_DDR                    (*(volatile unsigned char*)0x501b)
#define         PF_CR1                    (*(volatile unsigned char*)0x501c)
#define         PF_CR2                    (*(volatile unsigned char*)0x501d)


/* Flash */
/*****************************************************************/

#define         FLASH_CR1                (*(volatile unsigned char*)0x505A)
#define         FLASH_CR2                (*(volatile unsigned char*)0x505B)
#define         FLASH_NCR2                (*(volatile unsigned char*)0x505C)
#define         FLASH_FPR                (*(volatile unsigned char*)0x505D)
#define         FLASH_NFPR                (*(volatile unsigned char*)0x505E)
#define         FLASH_IAPSR                (*(volatile unsigned char*)0x505F)
#define         FLASH_PUKR                (*(volatile unsigned char*)0x5062)
#define         FLASH_DUKR                (*(volatile unsigned char*)0x5064)


/* External Interrupt Control Register (ITC) */
/*****************************************************************/

#define         EXTI_CR1                (*(volatile unsigned char*)0x50A0)
#define         EXTI_CR2                (*(volatile unsigned char*)0x50A1)


/* Reset (RST) */
/*****************************************************************/

/* Reset status register 1 */
#define         RST_SR                    (*(volatile unsigned char*)0x50B3)


/* Clock Control (CLK) */
/*****************************************************************/

#define         CLK_ICKR                (*(volatile unsigned char*)0x50C0)
#define         CLK_ECKR                (*(volatile unsigned char*)0x50C1)
#define         CLK_CMSR                (*(volatile unsigned char*)0x50C3)
#define         CLK_SWR                    (*(volatile unsigned char*)0x50C4)
#define         CLK_SWCR                (*(volatile unsigned char*)0x50C5)
#define         CLK_CKDIVR                (*(volatile unsigned char*)0x50C6)
#define         CLK_PCKENR1                (*(volatile unsigned char*)0x50C7)
#define         CLK_CSSR                (*(volatile unsigned char*)0x50C8)
#define         CLK_CCOR                (*(volatile unsigned char*)0x50C9)
#define         CLK_PCKENR2                (*(volatile unsigned char*)0x50CA)
#define         CLK_CANCCR                (*(volatile unsigned char*)0x50CB)
#define         CLK_HSITRIMR            (*(volatile unsigned char*)0x50CC)
#define         CLK_SWIMCCR                (*(volatile unsigned char*)0x50CD)


/* Window Watchdog (WWDG) */
/*****************************************************************/

#define         WWDG_CR                    (*(volatile unsigned char*)0x50D1)
#define         WWDG_WR                    (*(volatile unsigned char*)0x50D2)


/* Independent Watchdog (IWDG) */
/*****************************************************************/

#define         IWDG_KR                    (*(volatile unsigned char*)0x50E0)
#define         IWDG_PR                    (*(volatile unsigned char*)0x50E1)
#define         IWDG_RLR                (*(volatile unsigned char*)0x50E2)


/* Auto Wake-Up (AWU) */
/*****************************************************************/

#define         AWU_CSR                    (*(volatile unsigned char*)0x50F0)
#define         AWU_APR                    (*(volatile unsigned char*)0x50F1)
#define         AWU_TBR                    (*(volatile unsigned char*)0x50F2)


/* Beeper (BEEP) */
/*****************************************************************/

/* BEEP Control/Status Register */
#define         BEEP_CSR                (*(volatile unsigned char*)0x50F3)


/* Serial Peripheral Interface (SPI) */
/*****************************************************************/

#define         SPI_CR1                    (*(volatile unsigned char*)0x5200)
#define         SPI_CR2                    (*(volatile unsigned char*)0x5201)
#define         SPI_ICR                    (*(volatile unsigned char*)0x5202)
#define         SPI_SR                    (*(volatile unsigned char*)0x5203)
#define         SPI_DR                    (*(volatile unsigned char*)0x5204)
#define         SPI_CRCPR                (*(volatile unsigned char*)0x5205)
#define         SPI_RXCRCR                (*(volatile unsigned char*)0x5206)
#define         SPI_TXCRCR                (*(volatile unsigned char*)0x5207)


/* I2C Bus Interface (I2C) */
/*****************************************************************/

#define         I2C_CR1                    (*(volatile unsigned char*)0x5210)
#define         I2C_CR2                    (*(volatile unsigned char*)0x5211)
#define         I2C_FREQR                (*(volatile unsigned char*)0x5212)
#define         I2C_OARL                (*(volatile unsigned char*)0x5213)
#define         I2C_OARH                (*(volatile unsigned char*)0x5214)
#define         I2C_DR                    (*(volatile unsigned char*)0x5216)
#define         I2C_SR1                    (*(volatile unsigned char*)0x5217)
#define         I2C_SR2                    (*(volatile unsigned char*)0x5218)
#define         I2C_SR3                    (*(volatile unsigned char*)0x5219)
#define         I2C_ITR                    (*(volatile unsigned char*)0x521A)
#define         I2C_CCRL                (*(volatile unsigned char*)0x521B)
#define         I2C_CCRH                (*(volatile unsigned char*)0x521C)
#define         I2C_TRISER                (*(volatile unsigned char*)0x521D)
#define         I2C_PECR                (*(volatile unsigned char*)0x521E)


/* Universal synch/asynch receiver transmitter (UART1) */
/*****************************************************************/

#define         UART1_SR                (*(volatile unsigned char*)0x5230)
#define         UART1_DR                (*(volatile unsigned char*)0x5231)
#define         UART1_BRR1                (*(volatile unsigned char*)0x5232)
#define         UART1_BRR2                (*(volatile unsigned char*)0x5233)
#define         UART1_CR1                (*(volatile unsigned char*)0x5234)
#define         UART1_CR2                (*(volatile unsigned char*)0x5235)
#define         UART1_CR3                (*(volatile unsigned char*)0x5236)
#define         UART1_CR4                (*(volatile unsigned char*)0x5237)
#define         UART1_CR5                (*(volatile unsigned char*)0x5238)
#define         UART1_GTR                (*(volatile unsigned char*)0x5239)
#define         UART1_PSCR                (*(volatile unsigned char*)0x523a)


/* 16-Bit Timer 1 (TIM1) */
/*****************************************************************/
#define         TIM1_CR1                (*(volatile unsigned char*)0x5250)
#define         TIM1_CR2                (*(volatile unsigned char*)0x5251)
#define         TIM1_SMCR                (*(volatile unsigned char*)0x5252)
#define         TIM1_ETR                (*(volatile unsigned char*)0x5253)
#define         TIM1_IER                (*(volatile unsigned char*)0x5254)
#define         TIM1_SR1                (*(volatile unsigned char*)0x5255)
#define         TIM1_SR2                (*(volatile unsigned char*)0x5256)
#define         TIM1_EGR                (*(volatile unsigned char*)0x5257)
#define         TIM1_CCMR1                (*(volatile unsigned char*)0x5258)
#define         TIM1_CCMR2                (*(volatile unsigned char*)0x5259)
#define         TIM1_CCMR3                (*(volatile unsigned char*)0x525A)
#define         TIM1_CCMR4                (*(volatile unsigned char*)0x525B)
#define         TIM1_CCER1                (*(volatile unsigned char*)0x525C)
#define         TIM1_CCER2                (*(volatile unsigned char*)0x525D)
#define         TIM1_CNTR                (*(volatile unsigned char*)0x525E)
#define         TIM1_CNTRH                (*(volatile unsigned char*)0x525E)
#define         TIM1_CNTRL                (*(volatile unsigned char*)0x525F)
#define         TIM1_PSCR                (*(volatile unsigned char*)0x5260)
#define         TIM1_PSCRH                (*(volatile unsigned char*)0x5260)
#define         TIM1_PSCRL                (*(volatile unsigned char*)0x5261)
#define         TIM1_ARR                (*(volatile unsigned char*)0x5262)
#define         TIM1_ARRH                (*(volatile unsigned char*)0x5262)
#define         TIM1_ARRL                (*(volatile unsigned char*)0x5263)
#define         TIM1_RCR                (*(volatile unsigned char*)0x5264)
#define         TIM1_CCR1                (*(volatile unsigned char*)0x5265)
#define         TIM1_CCR1H                (*(volatile unsigned char*)0x5265)
#define         TIM1_CCR1L                (*(volatile unsigned char*)0x5266)
#define         TIM1_CCR2                (*(volatile unsigned char*)0x5267)
#define         TIM1_CCR2H                (*(volatile unsigned char*)0x5267)
#define         TIM1_CCR2L                (*(volatile unsigned char*)0x5268)
#define         TIM1_CCR3                (*(volatile unsigned char*)0x5269)
#define         TIM1_CCR3H                (*(volatile unsigned char*)0x5269)
#define         TIM1_CCR3L                (*(volatile unsigned char*)0x526A)
#define         TIM1_CCR4                (*(volatile unsigned char*)0x526B)
#define         TIM1_CCR4H                (*(volatile unsigned char*)0x526B)
#define         TIM1_CCR4L                (*(volatile unsigned char*)0x526C)
#define         TIM1_BKR                (*(volatile unsigned char*)0x526D)
#define         TIM1_DTR                (*(volatile unsigned char*)0x526E)
#define         TIM1_OISR                (*(volatile unsigned char*)0x526F)



#define         TIM2_CR1                (*(volatile unsigned char*)0x5300)
#define         TIM2_IER                (*(volatile unsigned char*)0x5303)
#define         TIM2_SR1                (*(volatile unsigned char*)0x5304)
#define         TIM2_SR2                (*(volatile unsigned char*)0x5305)
#define         TIM2_EGR                (*(volatile unsigned char*)0x5306)
#define         TIM2_CCMR1                (*(volatile unsigned char*)0x5307)
#define         TIM2_CCMR2                (*(volatile unsigned char*)0x5308)
#define         TIM2_CCMR3                (*(volatile unsigned char*)0x5309)
#define         TIM2_CCER1                (*(volatile unsigned char*)0x530A)
#define         TIM2_CCER2                (*(volatile unsigned char*)0x530B)
#define         TIM2_CNTR                (*(volatile unsigned char*)0x530c)
#define         TIM2_CNTRH                (*(volatile unsigned char*)0x530C)
#define         TIM2_CNTRL                (*(volatile unsigned char*)0x530D)
#define         TIM2_PSCR                (*(volatile unsigned char*)0x530E)
#define         TIM2_ARR                (*(volatile unsigned char*)0x530f)
#define         TIM2_ARRH                (*(volatile unsigned char*)0x530F)
#define         TIM2_ARRL                (*(volatile unsigned char*)0x5310)
#define         TIM2_CCR1                (*(volatile unsigned char*)0x5311)
#define         TIM2_CCR1H                (*(volatile unsigned char*)0x5311)
#define         TIM2_CCR1L                (*(volatile unsigned char*)0x5312)
#define         TIM2_CCR2                (*(volatile unsigned char*)0x5313)
#define         TIM2_CCR2H                (*(volatile unsigned char*)0x5313)
#define         TIM2_CCR2L                (*(volatile unsigned char*)0x5314)
#define         TIM2_CCR3                (*(volatile unsigned char*)0x5315)
#define         TIM2_CCR3H                (*(volatile unsigned char*)0x5315)
#define         TIM2_CCR3L                (*(volatile unsigned char*)0x5316)


/* 8-Bit  Timer 4 (TIM4) */
/*****************************************************************/

#define         TIM4_CR1                (*(volatile unsigned char*)0x5340)
#define         TIM4_IER                (*(volatile unsigned char*)0x5343)
#define         TIM4_SR                    (*(volatile unsigned char*)0x5344)
#define         TIM4_EGR                (*(volatile unsigned char*)0x5345)
#define         TIM4_CNTR                (*(volatile unsigned char*)0x5346)
#define         TIM4_PSCR                (*(volatile unsigned char*)0x5347)
#define         TIM4_ARR                (*(volatile unsigned char*)0x5348)


/* 10-Bit A/D Converter (ADC1) */
/*****************************************************************/

/* ADC Data buffer Register 0 */
#define         ADC_DB0R                (*(volatile unsigned char*)0x53e0)

/* Data Buffer register 0 High */
#define         ADC_DB0RH                (*(volatile unsigned char*)0x53e0)

/* Data Buffer register 0 Low */
#define         ADC_DB0RL                (*(volatile unsigned char*)0x53e1)

/* ADC Data buffer Register 1 */
#define         ADC_DB1R                (*(volatile unsigned char*)0x53e2)

/* Data Buffer register 1 High */
#define         ADC_DB1RH                (*(volatile unsigned char*)0x53e2)

/* Data Buffer register 1 Low */
#define         ADC_DB1RL                (*(volatile unsigned char*)0x53e3)

/* ADC Data buffer Register 2 */
#define         ADC_DB2R                (*(volatile unsigned char*)0x53e4)

/* Data Buffer register 2 High */
#define         ADC_DB2RH                (*(volatile unsigned char*)0x53e4)

/* Data Buffer register 2 Low */
#define         ADC_DB2RL                (*(volatile unsigned char*)0x53e5)

/* ADC Data buffer Register 3 */
#define         ADC_DB3R                (*(volatile unsigned char*)0x53e6)

/* Data Buffer register 3 High */
#define         ADC_DB3RH                (*(volatile unsigned char*)0x53e6)

/* Data Buffer register 3 Low */
#define         ADC_DB3RL                (*(volatile unsigned char*)0x53e7)


/* ADC Data buffer Register 4 */
#define         ADC_DB4R                (*(volatile unsigned char*)0x53e8)

/* Data Buffer register 4 High */
#define         ADC_DB4RH                (*(volatile unsigned char*)0x53e8)

/* Data Buffer register 4 Low */
#define         ADC_DB4RL                (*(volatile unsigned char*)0x53e9)


/* ADC Data buffer Register 5 */
#define         ADC_DB5R                (*(volatile unsigned char*)0x53ea)


/* Data Buffer register 5 High */
#define         ADC_DB5RH                (*(volatile unsigned char*)0x53ea)

/* Data Buffer register 5 Low */
#define         ADC_DB5RL                (*(volatile unsigned char*)0x53eb)


/* ADC Data buffer Register 6 */
#define         ADC_DB6R                (*(volatile unsigned char*)0x53ec)

/* Data Buffer register 6 High */
#define         ADC_DB6RH                (*(volatile unsigned char*)0x53ec)

/* Data Buffer register 6 Low */
#define         ADC_DB6RL                (*(volatile unsigned char*)0x53ed)


/* ADC Data buffer Register 7 */
#define         ADC_DB7R                (*(volatile unsigned char*)0x53ee)

/* Data Buffer register 7 High */
#define         ADC_DB7RH                (*(volatile unsigned char*)0x53ee)

/* Data Buffer register 7 Low */
#define         ADC_DB7RL                (*(volatile unsigned char*)0x53ef)


/* ADC Data buffer Register 8 */
#define         ADC_DB8R                (*(volatile unsigned char*)0x53f0)

/* Data Buffer register 8 High */
#define         ADC_DB8RH                (*(volatile unsigned char*)0x53F0)

/* Data Buffer register 8 Low */
#define         ADC_DB8RL                (*(volatile unsigned char*)0x53F1)


/* ADC Data buffer Register 9 */
#define         ADC_DB9R                (*(volatile unsigned char*)0x53F2)

/* Data Buffer register 9 High */
#define         ADC_DB9RH                (*(volatile unsigned char*)0x53F2)

/* Data Buffer register 9 Low */
#define         ADC_DB9RL                (*(volatile unsigned char*)0x53F3)


/* ADC Control/Status Register */
#define         ADC_CSR                    (*(volatile unsigned char*)0x5400)


/* ADC Configuration Register 1 */
#define         ADC_CR1                    (*(volatile unsigned char*)0x5401)


/* ADC Configuration Register 2 */
#define         ADC_CR2                    (*(volatile unsigned char*)0x5402)


/* ADC Configuration Register 3 */
#define         ADC_CR3                    (*(volatile unsigned char*)0x5403)


/* ADC Data Register */
#define         ADC_DR                    (*(volatile unsigned char*)0x5404)

/* Data bits High */
#define         ADC_DRH                    (*(volatile unsigned char*)0x5404)

/* Data bits Low */
#define         ADC_DRL                    (*(volatile unsigned char*)0x5405)


/* ADC Schmitt Trigger Disable Register */
#define         ADC_TDR                (*(volatile unsigned char*)0x5406)

/* Schmitt trigger disable High */
#define         ADC_TDRH                (*(volatile unsigned char*)0x5406)

/* Schmitt trigger disable Low */
#define         ADC_TDRL                (*(volatile unsigned char*)0x5407)


/* ADC High Threshold Register */
#define         ADC_HTR                (*(volatile unsigned char*)0x5408)

/* High Threshold Register High */
#define         ADC_HTRH                (*(volatile unsigned char*)0x5408)

/* High Threshold Register Low */
#define         ADC_HTRL                (*(volatile unsigned char*)0x5409)


/* ADC Low Threshold Register */
#define         ADC_LTR                (*(volatile unsigned char*)0x540A)

/* Low Threshold Register High */
#define         ADC_LTRH                (*(volatile unsigned char*)0x540A)

/* Low Threshold Register Low */
#define         ADC_LTRL                (*(volatile unsigned char*)0x540B)


/* ADC Analog Watchdog Status Register */
#define         ADC_AWSR                (*(volatile unsigned char*)0x540C)

/* Analog Watchdog Status register High */
#define         ADC_AWSRH                (*(volatile unsigned char*)0x540C)

/* Analog Watchdog Status register Low */
#define         ADC_AWSRL                (*(volatile unsigned char*)0x540D)


/* ADC Analog Watchdog Control Register */
#define         ADC_AWCR                (*(volatile unsigned char*)0x540E)

/* Analog Watchdog Control register High */
#define         ADC_AWCRH                (*(volatile unsigned char*)0x540E)

/* Analog Watchdog Control register Low */
#define         ADC_AWCRL                (*(volatile unsigned char*)0x540F)


/*  Global configuration register (CFG) */
/*****************************************************************/

/* CFG Global configuration register */
#define         CFG_GCR                    (*(volatile unsigned char*)0x7F60)


/* Interrupt Software Priority Register (ITC) */
/*****************************************************************/

#define         ITC_SPR1                (*(volatile unsigned char*)0x7f70)
#define         ITC_SPR2                (*(volatile unsigned char*)0x7f71)
#define         ITC_SPR3                (*(volatile unsigned char*)0x7f72)
#define         ITC_SPR4                (*(volatile unsigned char*)0x7f73)
#define         ITC_SPR5                (*(volatile unsigned char*)0x7f74)
#define         ITC_SPR6                (*(volatile unsigned char*)0x7f75)
#define         ITC_SPR7                (*(volatile unsigned char*)0x7f76)



#endif /* __STM8S103K__ */
