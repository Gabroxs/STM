#ifndef PROTOTYPES_H
  
  #define PROTOTYPES_H

   void wait_us(unsigned int us);
   void wait_ms(unsigned int ms);
   void wait_TIMER3(void);
   void ADC1_vreg_en(void);
   void TIMER3_set(unsigned int arr, unsigned int psc, _Bool enable);
   float mean(const float values[], unsigned int N);
   float std_dev(const float values[], float mean, unsigned int N);
   unsigned int TIMER3_PSC_wait_ms(float delta_t);

#endif