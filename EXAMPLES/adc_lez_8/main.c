/*
*       Programma per effettuare lettura analogica su PA0 (user button discovery)
*       12/04/2022 LEZ.8-9
*
*/


/*
*       Gli step da seguire sono:
*       
*       1. Abilitare PORTA da RCC
*       2. Configurare PA0 come analog da MODER
*       3. Abilitare ADC1 da RCC
*       4. Impostare clock per conversione ADC1, ADC CLOKC AHB / 1, CKMODE[1:0] 
*       5. Abilitazione regolatore di tensione
*       6. Configuro il canale in modalita' single o differential
*       7. Calibrazione ADC
*       8. Abilitazione ADC    
*       9. Impostare sequenza di acquisizione (da quanti e quali canali acquisire)
*       10. Impostiamo il sampling time per ciascun canale da acquisire
*       11. Avviare la conversione con ADSTART (software trigger)
*       12. Attendo il flag EOC
*       13. Leggo dal DATAREGISTER il dato acquisito
*
*
*       OSS: Gli step da 1 a 10 li eseguiamo nel main --> fase di configurazione periferiche mentre gli step da 
*       11 a 13 li possiamo eseguire in loop 
*/

#include "struttura.h"
#include <stdio.h>  

unsigned int voltage = 0;
float volt = 0.0;

static void wait_us(unsigned int us);
static void wait_us(unsigned int ms);


void main(void){
  
  RCC -> AHBENR |= GPIOAEN;
  GPIOA -> MODER0 = 3;
  
  RCC -> AHBENR |= ADC12EN; 
  ADC1_2 -> CCR |= 1 << 16;     //imposto il clokc dell'ADC1_2 pari a quello del bus AHB
  
  ADC1 -> CR &= ~(1 << 29);     // abilitazione regolatore di tensione
  ADC1 -> CR |= (1 << 28);
  
  for(unsigned int i = 0; i < 8000; i++);       //attesa per abilitazione regolatore di tensione

  ADC1 -> DIFSEL &= ~(1 << 1);                  //imposto il canale PA0 come single ended
  ADC1 -> CR &= ~(1 << 30);                     //specifico che la calibrazione deve avvenire per un canale single ended (ADCALDIFF = 0)
  ADC1 -> CR |= (unsigned int) 1 << 31;                        // avvio la fase di calibrazione
  
  
  while((ADC1 -> CR & (unsigned int)(1 << 31)) == (unsigned int)(1 << 31));         // attendo che il bit ADCAL passi da 1 a 0 (indica la fine della calibrazione del canale)
  
  ADC1 -> CR |= 1;                                       //mettiamo ad 1 il bit ADEN...abilito l'adc
  
   
  while(!(ADC1 -> ISR & 1));                            //attendo che il bit ADRDY vada ad 1...l'adc e' pronto all'uso
  
  ADC1 -> SQR1 |= 1 << 6;                       //effettuo una sola conversione sul canale 1 di ADC1
  
  ADC1 -> SMPR1 |= 7 << 3;                      // assegno il tempo di sampling del canale 1 di ADC1
  
  while(1){
    
    
    ADC1 -> CR |= 1 << 2;               //setto ad 1 il bit ADSTART
    
    while(!(ADC1 -> ISR & (1 << 2)));   //attendo che EOC si alzi (mi segnala la fine della conversione)      
    
    voltage = (unsigned int) ADC1 -> DR;
    
    volt = (float)(voltage * (3.0/4095));
    
    printf("%.3f V\n", volt);
  }
  
  
}


void wait_us(unsigned int us){
  
  TIM2 -> ARR = (unsigned int) (us * 8);
  TIM2 -> CR1 |= 
  
  
}


void wait_ms(unsigned int ms){
  
  
  
  
}
             

