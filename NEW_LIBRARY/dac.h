#ifndef DAC_H
#define DAC_H

void DAC1_set(unsigned int boff1, unsigned int ten1, unsigned int tsel1, unsigned int dmaen1);
void DAC1_en(unsigned int en1);
void DAC2_set(unsigned int boff2, unsigned int ten2, unsigned int tsel2, unsigned int dmaen2);
void DAC2_en(unsigned int en2); 

#endif

