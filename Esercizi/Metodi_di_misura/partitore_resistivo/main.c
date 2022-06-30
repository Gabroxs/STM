/*
*   Programma per la misura di resistenza incognita mediante partitore resistivo.
*   Valori di resistenze note: 100k, 10k, 1k, 100 [ohm]
*   
*   Periferiche in uso: AC3_IN1, GPIOA, GPIOB, GPIOD, RCC, TIM3       
*
*   
*/

#include "struttura.h"

void main(void){
  
  //Configurazione periferiche
  
  //1. Abilitare le periferiche tramite RCC
  RCC -> AHBENR |= (1 << 17) | (1 << 18) | (1 << 20) | (1 << 29);
  RCC -> APB1ENR |= 1 << 1;
  
  //2. Configurare le varie porte di GPIO
  GPIOA -> MODER0 = 0;
  GPIOB -> MODER1 = 3;  //canale ADC3_IN1
  GPIOB -> MODER0 = 1;
  GPIOB -> MODER2 = 1;
  GPIOB -> MODER10 = 1;
  GPIOB -> MODER12 = 1;
  GPIOB -> OTYPER |= 1 | (1 << 2) | (1 << 10) | (1 << 12);      //Configurazione PB0,PB2,PB10,PB12 come open drain
  GPIOD -> MODER9 |= 1;
  
  //3. Configurare TIM3 per avere DeltaT = 10us
    TIMER3 -> ARR = 80; 
  
  //4. Configurazione ADC3
  TIMER3 -> CR1 |= 1;
  ADC3 -> CR &= ~(1 << 29);
  ADC3 -> CR |= 1 << 28;
  ADC3_4 -> CCR |= 1 << 16;
  
  while(!(TIMER3 -> SR & 1));
  TIMER3 -> SR &= ~1;
  TIMER3 -> CR1 &= ~1;
  
  if(!(ADC3 -> CR & 1)){        //Calibratiion procedure...Assicurarsi che ADEN = 0 prima di iniziare la calibrazione
    
    ADC3 -> DIFSEL &= ~(1 << 1);
    ADC3 -> CR |= (unsigned int) 1 << 31;
    while((ADC3 -> CR & (unsigned int)(1 << 31)) == (unsigned int)(1 << 31));                //Calibration is running
  
  }//End of calibration procedure

  ADC3 -> SQR1 |= 1 << 6;
  ADC3 -> SMPR1 |= 7 << 3;
  
  ADC3 -> CR |= 1;              //ADEN = 1
  while(!(ADC3 -> ISR & 1));     //Attendo che ADRDY vada ad 1
  
  while(1);
  
}