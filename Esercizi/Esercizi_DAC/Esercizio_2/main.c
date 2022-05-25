/*
*
*       Per la traccia dell'esercizio vedi cartella
*
*/

#include "struttura.h"
#include "prototypes.h"
#include <stdio.h>

unsigned int voltage = 0;
float volt = 0.0;
unsigned int signal[13] = {0};
void ramp(unsigned int *const vector);

int main(void){
  
  // Abilitiamo prima tutte le periferiche da RCC
  
  RCC -> AHBENR |= GPIOAEN | ADC12EN;
  RCC -> APB1ENR |= TIMER2EN | TIMER3EN | DACEN;

  //Settiamo PA1 e PA4 come analogici dal registro MODER
  
  GPIOA -> MODER1 = 3;
  GPIOA -> MODER4 = 3;
  
  //Configurazione ADC1 channel 2
  
  ADC12_clk_domain(1);
  ADC1_vreg_en();
  wait_us(10);
  ADC_difsel(0, 2);
  ADC1_calibration(0);
  ADC1_enable(1);
  ADC1_conversion_length(1);
  ADC1 -> SQR1 |= 2 << 6;
  ADC1 -> SMPR1 |= 7 << 6;
    
  DAC1_set(1, 0, 0, 0);
  DAC1_en(1);
  ADC1_enable(1);
  ramp(signal);
  
  while(1){
    
   for(unsigned int i = 0; i < 13; i++){
      
       DAC1 -> DHR12R1 = signal[i];
       ADC1 -> CR |= 1 << 2;               //setto ad 1 il bit ADSTART
    
       while(!(ADC1 -> ISR & (1 << 2)));   //attendo che EOC si alzi (mi segnala la fine della conversione)      
    
       voltage = (unsigned int) ADC1 -> DR;
    
       volt = (float)(voltage * (3.0/4095));
    
       printf("%.3f V\n", volt);
       
       wait_ms(1500);
  
  }
  
}
}

void ramp(unsigned int *const vector){
  
  for(unsigned int i = 0; i < 7; i++){
    
    vector[i] = 682 * i;
    
  }
  
  for(unsigned int i = 6; i > 0; i--){
    
    vector[i + 6] = vector[6] - 682 * i;
    
  }
  
}

