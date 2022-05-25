#include "timer.h"
#include "struttura.h"

void timer3_set(unsigned int arr, unsigned int psc){
  
  TIMER3 -> ARR = arr;                
  TIMER3 -> PSC = psc;       
   
}

void timer3Enable(unsigned int enable){
  
    TIMER3 -> CR1 |= enable;

}  

void timer2_set(unsigned int arr, unsigned int psc){
  
  TIMER2 -> ARR = arr;                
  TIMER2 -> PSC = psc;       
   
}

void timer2Enable(unsigned int enable){
  
    TIMER2 -> CR1 |= enable;

}

void timer1_set(unsigned int arr, unsigned int psc){
  
  TIMER1 -> ARR = arr;                
  TIMER1 -> PSC = psc;       
   
}

void timer1Enable(unsigned int enable){
  
    TIMER1 -> CR1 |= enable;

}  
