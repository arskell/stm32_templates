#include "DAConverter.h"

int pin=4UL;
int pin2=5UL;
float Vref;
char _init_DAC_VH1_ISTRUE;
char _init_DAC_VH2_ISTRUE;
DAC_TypeDef* __DAC;

void initialize_DAC_CH1(DAC_TypeDef* _DAC){
		
		Vref=5.0;
		__DAC=_DAC;
		RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
		GPIOA->MODER|=(3UL<<pin*2);
		GPIOA->PUPDR&=~(3UL<<pin*2);
		GPIOA->BSRRL&=~(1UL<<pin);
		GPIOA->OSPEEDR|=(3UL<<pin*2);
		RCC->APB1ENR|=RCC_APB1ENR_DAC1EN;
		__DAC->CR|=(1UL<<2);
		__DAC->CR|=(7UL<<3);
		__DAC->CR|=(1UL<<0);
		_init_DAC_VH1_ISTRUE=1;
	
		
}
	
void initialize_DAC_CH2(DAC_TypeDef* _DAC){

	Vref=5.0;
		__DAC=_DAC;
		RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
		GPIOA->MODER|=(3UL<<pin2*2);
		GPIOA->PUPDR&=~(3UL<<pin2*2);
		GPIOA->BSRRL&=~(1UL<<pin2);
		GPIOA->OSPEEDR|=(3UL<<pin2*2);
		RCC->APB1ENR|=RCC_APB1ENR_DAC1EN;
		__DAC->CR|=(1UL<<18);
		__DAC->CR|=(7UL<<19);
		__DAC->CR|=(1UL<<16);
		_init_DAC_VH2_ISTRUE=1;

}

int DAC_setlvl_asy_CH2(float voltage){
	if(_init_DAC_VH2_ISTRUE!=1)
		return -1;
	
	__DAC->DHR12R2=voltage/Vref*(4096-1);
	__DAC->SWTRIGR|=(1UL<<1);
	return 0;
}

int DAC_setlvl_CH2(float voltage){
	
	int err=DAC_setlvl_asy_CH2(voltage);
	while((__DAC->SWTRIGR)&(1UL<<1));
	return err;

}

void DAC_CH2_out(uint16_t value){
	
	__DAC->DHR12R2=value;
	__DAC->SWTRIGR|=(1UL<<1);
	while((__DAC->SWTRIGR)&(1UL<<1));
}

int DAC_setlvl_asy_CH1(float voltage){
	
	if(_init_DAC_VH1_ISTRUE!=1)
		return -1;
	
	__DAC->DHR12R1=voltage/Vref*(4096-1);
	__DAC->SWTRIGR|=(1UL<<0);
	return 0;
}

int  DAC_setlvl_CH1(float voltage){

	int err=DAC_setlvl_asy_CH1(voltage);
	while((__DAC->SWTRIGR)&(1UL<<0));
	return err;
}


void DAC_CH1_out(uint16_t value){
	
	__DAC->DHR12R1=value;
	__DAC->SWTRIGR|=(1UL<<0);
	while((__DAC->SWTRIGR)&(1UL<<0));
}

void test_remap_CH1(){
	
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
	GPIOA->MODER|=(1UL<<pin*2);
	//GPIOA->PUPDR|=(1UL<<pin*2);
	GPIOA->BSRRL|=(1UL<<pin);
}

void test_remap_CH2(){
	RCC->AHBENR|=RCC_AHBENR_GPIOAEN;
	GPIOA->MODER|=(1UL<<pin2*2);
	//GPIOA->PUPDR|=(1UL<<pin2*2);
	GPIOA->BSRRL|=(1UL<<pin2);
}
