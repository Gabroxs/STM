typedef struct{ //con la struct definisco una struttura dati che non fa altro che replicare la struttura dati della memoria del micro

  unsigned int MODER;   //sto allocando 32 bit come per il registro moder presente fisicamente in memoria
  unsigned int OTYPER;  //i registri rappresentati sono tutti consecutivi in memoria
  unsigned int OSPEEDR;
  unsigned int PUPDR;
  
  union{ //poichè abbiamo dichiarato un'union unsigned int ODR e la struct condividono lo stesso spazio di memoria
    
    unsigned int IDR;   //reg a 32 bit
    struct{
            
      unsigned  USER_BUTTON:1;         //unsigned label:spazio_da_riservare
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
  
  
  
  
  union{ //poichè abbiamo dichiarato un'union unsigned int ODR e la struct condividono lo stesso spazio di memoria
    
    unsigned int ODR;   //reg a 32 bit
    struct{
            
      unsigned  ODR0:1;         //unsigned label:spazio_da_riservare
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
      unsigned  ODRX :16;       //parte alta del registro -- don't care
            };
  };
  
  //mediante la union ho la possibilità di poter accedere ai singoli bit del registro

}Gpio_type;     //è un tipo strutturato 

typedef struct{ //con la struct definisco una struttura dati che non fa altro che replicare la struttura dati della memoria del micro

  unsigned int CR;   //sto allocando 32 bit come per il registro moder presente fisicamente in memoria
  unsigned int CFGR;  //i registri rappresentati sono tutti consecutivi in memoria
  unsigned int CIR;
  unsigned int APD2RSTR;
  unsigned int APB1RSTR;
  unsigned int AHBENR;

}RCC_type;     //è un tipo strutturato 



#define RCC_AHBENR  (unsigned int*) 0x40021014
#define GPIOE_MODER (unsigned int*) 0x48001000
#define GPIOE_ODR   (unsigned int*) 0x48001014
#define GPIOA_MODER (unsigned int*) 0x48000000
#define GPIOA_IDR   (unsigned int*) 0x48000010 

#define GPIOA ((Gpio_type*) 0x48000000)   //puntatore di tipo Gpio_type (la dimensione del puntatore è determinata dalla struct) --> 0x48000000
#define GPIOE ((Gpio_type*) 0x48001000)
#define RCC ((RCC_type*) 0x40021000)

#define GPIOAEN (1 << 17)
#define GPIOEEN (1 << 21)

unsigned int* punt;


void main (){
  //punt = RCC_AHBENR; //Punta a RCC_AHBENR
  
  RCC -> AHBENR |= GPIOEEN | GPIOAEN;
  
  //GPIOA -> MODER = 1;
  
    
  //*punt |= GPIOEEN | GPIOAEN; //Con define Attivo PORT_E + PORT_A con shift register
  //*punt &= ~(GPIOAEN); //Con define Disattivo PORT_A con shift register
  
 /* punt = GPIOE_MODER; //Punta a GPIOE_MODER
  *punt = 0x00010000; //PE8 Digital Output
 */
  
  GPIOE -> MODER |= 1 << 16;
/*  
  punt = GPIOA_MODER; //Punta a GPIOA_MODER
  *punt = 0xA8000000; //PA0 Digital Input
*/

  GPIOA -> MODER &= ~(3 << 0);
  
  while(1){
  
  /*
  punt = GPIOA_IDR;
  while( ((*punt)&(1<<0)) != (1<<0));
  */
    
  //while( ((GPIOA -> IDR)&(1<<0)) != (1<<0));  
  
  while(GPIOA -> USER_BUTTON == 0);  
    
  for(int i = 0; i < 800000; i++); //Perdiamo un po' di tempo in modo da vedere il cambio di stato del led
  
  /*
  punt = GPIOE_ODR; //Punta a GPIOE_ODR
  *punt |= 1 << 8; //Attivo PE8
  */
  
  //GPIOE -> ODR |= (1 << 8);
  
  GPIOE -> ODR8 = 1;
  
 /* punt = GPIOA_IDR;
  while( ((*punt)&(1<<0)) != (1<<0));
 */
  
  while( ((GPIOA -> IDR)&(1<<0)) != (1<<0));
  
  for(int i = 0; i < 800000; i++);
  /*
  punt = GPIOE_ODR; //Punta a GPIOE_ODR
  *punt &= ~(1 << 8); //Metto a 0 PE8
  */
  
  //GPIOE -> ODR &= ~(1 << 8);
  
  GPIOE -> ODR8 = 0;
  
  for(int i = 0; i < 800000; i++);
  
  }
  
}