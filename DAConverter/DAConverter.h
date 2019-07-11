
/* MINIMANUAL

DACout= Vref*(DOR/4096)=>   DOR =DACout/Vref*4096
Default trigger is TIM6_TRGO  (TSEL==0)
				soft =7
*/

#include "headers.h"  

void initialize_DAC_CH1(DAC_TypeDef* _DAC);
void test_remap_CH1();
int DAC_setlvl_asy_CH1(float voltage);
int DAC_setlvl_CH1(float voltage);
void DAC_CH1_out(uint16_t value);

void initialize_DAC_CH2(DAC_TypeDef* _DAC);
void test_remap_CH2();
int DAC_setlvl_asy_CH2(float voltage);
int DAC_setlvl_CH2(float voltage);
void DAC_CH2_out(uint16_t value);

