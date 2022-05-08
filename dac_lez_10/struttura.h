#ifndef STRUTTURA_H
#define STRUTTURA_H

typedef struct{
	

  union{

      unsigned int MODER;    
      struct{

            unsigned  MODER0:2;
            unsigned  MODER1:2;
            unsigned  MODER2:2;
            unsigned  MODER3:2;
            unsigned  MODER4:2;
            unsigned  MODER5:2;
            unsigned  MODER6:2;
            unsigned  MODER7:2;
            unsigned  MODER8:2;
            unsigned  MODER9:2;
            unsigned  MODER10:2;
            unsigned  MODER11:2;
            unsigned  MODER12:2;
            unsigned  MODER13:2;
            unsigned  MODER14:2;
            unsigned  MODER15:2;
      
      };


  };


	unsigned int OTYPER;
	unsigned int OSPEEDR;
	unsigned int PUPDR;
        union{
        
          unsigned int IDR;
          struct{
            
            unsigned  IDR0:1;
            unsigned  IDR1:1;
            unsigned  IDR2:1;
            unsigned  IDR3:1;
            unsigned  IDR4:1;
            unsigned  IDR5:1;
            unsigned  IDR6:1;
            unsigned  IDR7:1;
            unsigned  IDR8:1;
            unsigned  IDR9:1;
            unsigned  IDR10:1;
            unsigned  IDR11:1;
            unsigned  IDR12:1;
            unsigned  IDR13:1;
            unsigned  IDR14:1;
            unsigned  IDR15:1;
            unsigned  IDRX :16;       //parte alta del registro -- don't care
          };
        
        };
        
        union{
          unsigned int ODR;
          struct{
            
            unsigned  ODR0:1;
            unsigned  ODR1:1;
            unsigned  ODR2:1;
            unsigned  ODR3:1;
            unsigned  ODR4:1;
            unsigned  ODR5:1;
            unsigned  ODR6:1;
            unsigned  ODR7:1;
            unsigned  ODR8:1;
            unsigned  ODR9:1;
            unsigned  ODR10:1;
            unsigned  ODR11:1;
            unsigned  ODR12:1;
            unsigned  ODR13:1;
            unsigned  ODR14:1;
            unsigned  ODR15:1;
            unsigned  ODRX :16;         //parte alta del registro -- don't care
                   
          };
          
        };
	
	unsigned int BSRR;	
	unsigned int LCKR;
	unsigned int AFRL;
	unsigned int AFRH;
	unsigned int BRR;
	
}Gpio_type;


typedef struct{ 

	unsigned int CR;   
	unsigned int CFGR;  
	unsigned int CIR;
	unsigned int APD2RSTR;
	unsigned int APB1RSTR;
	unsigned int AHBENR;
	unsigned int APB2ENR;
	unsigned int APB1ENR;
	unsigned int BDCR;
	unsigned int CSR;
	unsigned int AHBRSTR;
	unsigned int CFGR2;
	unsigned int CFGR3;
	
}RCC_type;     

typedef struct{ 

	unsigned int CR1;   
	unsigned int CR2;  
	unsigned int SMCR;
	unsigned int DIER;
	unsigned int SR;
	unsigned int EGR;
	unsigned int CCMR1;
	unsigned int CCMR2;
	unsigned int CCER;
  unsigned int CNT;
	unsigned int PSC;
	unsigned int ARR;
	unsigned int CCR1;
	unsigned int CCR2;
	unsigned int CCR3;
	unsigned int CCR4;
	unsigned int RESERVED;
	unsigned int DCR;
	unsigned int DMAR;
		
}Timer_type; 



typedef struct{
  
  unsigned int CSR;
  unsigned int RESERVED;
  unsigned int CCR;
  unsigned int CDR;
  
}ADC_CR_type;


typedef struct{
  
  unsigned int ISR;
  unsigned int IER;
  unsigned int CR;
  unsigned int CFGR;
  unsigned int RESERVED0;
  unsigned int SMPR1;
  unsigned int SMPR2;
  unsigned int RESERVED1;
  unsigned int TR1;
  unsigned int TR2;
  unsigned int TR3;
  unsigned int RESERVED2;
  unsigned int SQR1;
  unsigned int SQR2;
  unsigned int SQR3;
  unsigned int SQR4;
  unsigned int DR;
  unsigned int RESERVED3;
  unsigned int RESERVED4;
  unsigned int JSQR;
  unsigned int RESERVED5;
  unsigned int RESERVED6;
  unsigned int RESERVED7;
  unsigned int RESERVED8;
  unsigned int OFR1;
  unsigned int OFR2;
  unsigned int OFR3;
  unsigned int OFR4;
  unsigned int RESERVED9;
  unsigned int RESERVED10;
  unsigned int RESERVED11;
  unsigned int RESERVED12; 
  unsigned int JDR1;
  unsigned int JDR2;
  unsigned int JDR3;
  unsigned int JDR4;
  unsigned int RESERVED13;
  unsigned int RESERVED14;
  unsigned int RESERVED15;
  unsigned int RESERVED16;
  unsigned int AWD2CR;
  unsigned int AWD3CR;
  unsigned int RESERVER17;
  unsigned int RESERVED18;
  unsigned int DIFSEL;
  unsigned int CALFACT;
  
  
}ADC_type;

typedef struct{

  unsigned int CR;
  unsigned int SWTRIGR;
  unsigned int DHR12R1;
  unsigned int DHR12L1;
  unsigned int DHR8R1;
  unsigned int DHR12R2;
  unsigned int DHR12L2;
  unsigned int DHR8R2;
  unsigned int DHR12RD;
  unsigned int DHR12LD;
  unsigned int DHR8RD;
  unsigned int DOR1;
  unsigned int DOR2;
  unsigned int SR;

}DAC_type;




#define RCC ((RCC_type*) 0x40021000)
#define GPIOE ((Gpio_type*) 0x48001000)
#define GPIOA ((Gpio_type*) 0x48000000)
#define TIMER2 ((Timer_type*) 0x40000000)
#define TIMER3 ((Timer_type*) 0x40000400)
#define DAC1 ((DAC_type*) 0x40007400)


#define GPIOAEN  (1 << 17)
#define TIMER2EN (1 << 0)
#define TIMER3EN (1 << 1)
#define UIF (1 << 0)


#define ADC1 ((ADC_type*) 0x50000000)
#define ADC2 ((ADC_type*) 0x50000100)
#define ADC3 ((ADC_type*) 0x50000400)
#define ADC4 ((ADC_type*) 0x50000500)

#define ADC1_2 ((ADC_CR_type*) 0x50000300)
#define ADC3_4 ((ADC_CR_type*) 0x50000700)

#define ADC12EN (1 << 28)
#define ADC34EN (1 << 29)
#define ADC_CAL ((unsigned int) (1 << 31))
#define ADC_CAL_DIFF ((unsigned int) (1 << 30))

#define EN1 1
#define BOFF1 (1 << 1)
#define DACEN (1 << 29)

typedef struct{
  
  unsigned int AHBENR;
  unsigned int APB1RSTR;
  
}RCC_cfg;


typedef struct{
  
  unsigned int MODER;
    
}GpioA_cfg;

typedef struct{
  
  unsigned int MODER;
  
}GpioE_cfg;


typedef struct{
  
  unsigned int ARR;
  unsigned int CR1;
  
}Timer_cfg;


#endif