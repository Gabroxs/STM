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


#define RCC ((RCC_type*) 0x40021000)
#define GPIOE ((Gpio_type*) 0x48001000)
#define TIMER2 ((Timer_type*) 0x40000000)
#define TIMER3 ((Timer_type*) 0x40000400)


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