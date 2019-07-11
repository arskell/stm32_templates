//  HSI/2*k + HSI 
int upclock(char k){
	if((k>-1)||(k<15)){
		if(k>=7)
				FLASH->ACR|=(1<<0);
		if(k>10)
				FLASH->ACR|=(2<<0);
		RCC->CR&=~(1UL<<24);
		while(((RCC->CR)&(1UL<<25))){}
		RCC->CFGR|=((uint16_t)k<<18);
		RCC->CR|=(1UL<<24);
		while(!((RCC->CR)&(1UL<<25))){}
		RCC->CFGR|=2;
		while(!((RCC->CFGR)&(1UL<<3))){}
		return 0;
	}
		return -1;
}
