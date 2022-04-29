#ifndef PROTOTYPES_H
  
  #define PROTOTYPES_H

   void wait_us(unsigned int us);
   void wait_ms(unsigned int ms);
   void wait_next_acquisition(void);
   void ADC1_vreg_en(void);
   void TIMER3_set(unsigned int arr, unsigned int psc, _Bool enable);
   float mean(float values[], unsigned int N);
   float std_dev(float values[], float mean, unsigned int N);

#endif