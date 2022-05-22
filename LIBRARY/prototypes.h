#ifndef PROTOTYPES_H
  
  #define PROTOTYPES_H

   void wait_us(unsigned int us);
   void wait_ms(unsigned int ms);
   void wait_TIMER3(void);
   void ADC1_vreg_en(void);
   void timer3_set(unsigned int arr, unsigned int psc);
   void timer3Enable(unsigned int enable);
   void timer2_set(unsigned int arr, unsigned int psc);
   void timer2Enable(unsigned int enable);
   void timer1_set(unsigned int arr, unsigned int psc);
   void timer1Enable(unsigned int enable);
   void DAC1_set(unsigned int boff1, unsigned int ten1, unsigned int tsel1, unsigned int dmaen1);
   void DAC1_en(unsigned int en1);
   void DAC2_set(unsigned int boff2, unsigned int ten2, unsigned int tsel2, unsigned int dmaen2);
   void DAC2_en(unsigned int en2);   
   float mean(const float values[], unsigned int N);
   float std_dev(const float values[], float mean, unsigned int N);
   unsigned int TIMER3_PSC_wait_ms(float delta_t);
   void fSineWave(unsigned int *const vector, unsigned int freq, unsigned int size);
   void sineWave(unsigned int *const vector, unsigned int size);
   void sine3Wave(unsigned int *const vector, unsigned int size);
   void squareWave(unsigned int *const vector, unsigned int size);
   void triangularWave(unsigned int *const vector, unsigned int size);

#endif