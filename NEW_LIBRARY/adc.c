#include "adc.h"
#include "struttura.h"

void ADC1_start(void){
  
  ADC1 -> CR |= 1 << 2;
  
}

void ADC1_conversion_length(unsigned int length){
  
  ADC1 -> SQR1 |= length;
  
  //length[3:0] indica quante conversioni l'adc dovra' effettuare!
  
}

void ADC12_clk_domain(unsigned int ckmode){
  
  ADC1_2 -> CCR |= ckmode << 16;
  //ckmode = 1 --> ck dal bus AHB (no divisore inserito)  
}

void ADC_difsel(unsigned int difsel, unsigned int channel){
  
  ADC1 -> DIFSEL |= difsel << channel;
  
  //difsel = 0 --> canale single ended
  //difsel = 1 --> canale differenziale
  
  //channel[15:1] //0 e' riservato!
}


void ADC1_calibration(unsigned int adcaldif){
  
  if(!(ADC1 -> CR & 1)){ //se ADEN = 0
    
    ADC1 -> CR |= adcaldif; //0 per single ended, 1 per differenziale
    ADC1 -> CR |= ADC_CAL;  //ADCAL = 1
    
    while(ADC1 -> CR & ADC_CAL); //aspetto che ADCAL vada a 0
    
    // calibrazione terminata
       
  }
  
}

void ADC1_enable(unsigned int aden){
  
  ADC1 -> CR |= 1; //ADEN = 1
  while(!(ADC1 -> ISR & 1)); //attesa finche' ADRDY = 1
  
  //ADC1 pronto per la conversione
  
}

void ADC1_vreg_en(void){
  
  ADC1 -> CR &= ~(1 << 29);             //abilitazione regotalore di tensione ADC1
  ADC1 -> CR |= 1 << 28;
    
}