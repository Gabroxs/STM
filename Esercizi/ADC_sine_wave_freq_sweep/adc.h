#ifndef ADC_H
#define ADC_H

void ADC1_start(void);
void ADC1_conversion_length(unsigned int length);
void ADC12_clk_domain(unsigned int ckmode);
void ADC_difsel(unsigned int difsel, unsigned int channel);
void ADC1_calibration(unsigned int adcaldif);
void ADC1_enable(unsigned int aden);
void ADC1_vreg_en(void);

#endif