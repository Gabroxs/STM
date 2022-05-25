#include "signal.h"
#include "struttura.h"
#include <math.h>


void sineWave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size; i++){
    
    vector[i] = (unsigned int) (2047 * sin((2 * 3.14159 / size) * i) + 2048);
    
  }
  
}


void fSineWave(unsigned int *const vector, unsigned int freq, unsigned int size){

   for(unsigned int i = 0; i < size; i++){
    
      vector[i] = (unsigned int) (2047 * sin((2 * freq * 3.14159 / size) * i) + 2048);
    
  }


}


void sine3Wave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size; i++){
    
    vector[i] = (unsigned int) (2047 * sin((6 * 3.14159 / size) * i) + 2048);
    
  }
  
}

void squareWave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size; i++){
      
    if(i < size/2){
    
       vector[i] = 4095;
      
    }
    
    else{
      
       vector[i] = 0;
      
    }
  }      
       
}


void triangularWave(unsigned int *const vector, unsigned int size){
  
  for(unsigned int i = 0; i < size/4; i++){
    
    vector[i] = 2048 + 81 * i;
    
  }
  
  for(unsigned int i = 0; i < size/2; i++){
    
    vector[i + size/4] = 4095 - 81 * i;
    
  }
  
  for(unsigned int i = 0; i < size/4; i++){
    
    vector[i + 3*size/4] = 81 * i;
    
  }
    
}