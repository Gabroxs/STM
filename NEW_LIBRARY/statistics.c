#include "statistics.h"
#include "struttura.h"
#include <math.h>

float mean(const float *const values, unsigned int N){
  
  float media = 0;
      
  for(size_t i = 0; i < N; i++){
    
    media += values[i];   
  }
 
  return (media / N);
  
}

float std_dev(const float *const values, float mean, unsigned int N){
  
  float std_dev = 0;
  float partial = 0;
  
  for(size_t i = 0; i < N; i++){
    
    partial = pow((values[i] - mean), 2);
    std_dev += partial;
  
  }

  return (sqrt(std_dev * 1/N));
  
}