#include "dac.h"
#include "struttura.h"

void DAC1_set(unsigned int boff1, unsigned int ten1, unsigned int tsel1, unsigned int dmaen1){
  
  DAC1 -> CR |= boff1 << 1;
  DAC1 -> CR |= ten1 << 2;
  DAC1 -> CR |= tsel1 << 3;
  DAC1 -> CR |= dmaen1 << 12; 
  
}

void DAC1_en(unsigned int en1){
  
  DAC1 -> CR |= en1;
  
}

void DAC2_set(unsigned int boff2, unsigned int ten2, unsigned int tsel2, unsigned int dmaen2){
  
  DAC1 -> CR |= boff2 << 1;
  DAC1 -> CR |= ten2 << 2;
  DAC1 -> CR |= tsel2 << 3;
  DAC1 -> CR |= dmaen2 << 12; 
  
}

void DAC2_en(unsigned int en2){
  
  DAC1 -> CR |= en2;
  
}