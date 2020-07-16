#include "sonar.h"
#include "extra.h"


uint32_t probes[10];
uint8_t i = 0;

void TPM2_IRQHandler(void) 
{
	
	uint32_t Logic_state_on_pin	= (FPTB->PDIR & (1UL << 2));	
	if (Logic_state_on_pin != 0) 
	{
		result = TPM2->CNT;												
		TPM2->SC |= TPM_SC_TOF_MASK;								
		TPM1->SC |= TPM_SC_CMOD(0);												
	} 
	else if (Logic_state_on_pin == 0)  
	{		
		if ((TPM2->SC & TPM_SC_TOF_MASK)==0) 
		{
			probes[i] = TPM2->CNT - result;
			
			if (i == 9) 
			{	
			i = 0;
			}
			
		}
	TPM1->CNT = 0;																	
	TPM1->SC |= TPM_SC_CMOD(1);											
	}
	TPM2->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}

void SONAR_initialize(void) 
{
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;							
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;							
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;		
	
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);							
	MCG->C2 |= MCG_C2_IRCS_MASK;										
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;									

	PORTB->PCR[1] = PORT_PCR_MUX(3);  							
	TPM1->SC |= TPM_SC_PS(5);												

	TPM1->CNT = 0;																	
	TPM2->CNT = 0;																  
	TPM1->CONTROLS[1].CnV = 625;										
	TPM1->MOD = 12500;																
	TPM1->SC &= ~TPM_SC_CPWMS_MASK;
	TPM1->CONTROLS[1].CnSC |= (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);
	TPM1->CONTROLS[1].CnSC &= ~TPM_CnSC_ELSB_MASK;	
	PORTB->PCR[2] = PORT_PCR_MUX(3);  							
	TPM2->SC |= TPM_SC_PS(1);											 
	TPM2->SC &= ~TPM_SC_CPWMS_MASK;	
	TPM2->CONTROLS[0].CnSC &=  ~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK);
	TPM2->CONTROLS[0].CnSC |=  (TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK);

	NVIC_ClearPendingIRQ(TPM2_IRQn);
	NVIC_EnableIRQ(TPM2_IRQn);
	TPM2->CONTROLS[0].CnSC |= TPM_CnSC_CHIE_MASK; 
	TPM1->SC |= TPM_SC_CMOD(1);											
	TPM2->SC |= TPM_SC_CMOD(1);											

}

uint32_t Distance_from_probes(void) 
{	
	
	uint8_t j = 0;
	uint32_t sum = 0;
	
	for (j=0;j<10;j++) 
	{
		sum += probes[i];
	}
	
	return 34000*0.5*(sum/10)*0.000001;	
}
