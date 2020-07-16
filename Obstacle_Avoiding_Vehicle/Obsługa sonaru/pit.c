#include "pit.h"
#include "sonar.h"
#include "slcd.h"
#include "extra.h"

#define Output 0
const uint32_t MaskENGINE[] = {1UL << 3};

void PIT_IRQHandler(void) 
{
	
	slcdDisplay(Distance_from_probes(),10);
	
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;										
	PIT->CHANNEL[1].TCTRL |=  (PIT_TCTRL_TEN_MASK |	PIT_TCTRL_TIE_MASK);
	
	if(Distance_from_probes() < 50)
	{
		PTB -> PSOR = MaskENGINE[Output];
		delay_mc(50);
		PTB -> PCOR = MaskENGINE[Output];
	}

}

void PIT_initialize(void) 
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;	
	slcdInitialize();				
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
	PIT->CHANNEL[1].LDVAL = 0x249F00;
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;									
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;
	PIT->MCR = 0x00;
	
	PORTB->PCR[3] = PORT_PCR_MUX(1); 
	PTB->PDDR |= MaskENGINE[Output];
}

