/*! \file */
/* USER CODE BEGIN Header */
/**
  ****************************************************************************
  * @file           : main.c
  * @brief          : Projekt AMK\n Autorzy: Monika Lis, Wojciech Przybylo
  ****************************************************************************


/*! \mainpage Temat: Optymalizacja temperatury na elemencie przy pomocy regulacji obrotow wentylatora
 *
 * \section intro_sec Opis
 *
 * Zalozeniem projektu bylo uzyskanie optymalizacji temperatury na elemencie przy pomocy regulacji obrotow wiatraka.
 * Przy realizacji posluzono sie mikrokontorlerem STM32L072CZY oraz sterowaniem przy pomocy PWM.
 * Ponadto projekt zawiera tryb kontroli obrotow wiatraka przy pomocy komparatora LM393 wykrywajacego poziom natezenia dzwieku
 *
 * \subsection install_sec Wykorzystane elementy:
 * \n - STM32L072CZY
 * \n - wentylator karty graficznej PLA08015S12HH
 * \n - DHT11 \- czujnik temperatury i wilgotnosci
 * \n - uklad L293D (mostek typu H sluzacy do oddzielenia logiki sterujacej od zewnetrznego zasilania wiatraka)
 * \n - LM393 \- komparator reagujacy na natezenie dzwieku
 * \n - Bateria 9V (zewnetrzne zasilanie wiatraka)
 * \n - Przelacznik \- fizyczne przelaczenie pomiedzy trybami
 * \n - Dioda
 * \n - Kondensator 1000 uF
 */


#include "main.h"
#include "stm32l0xx_hal.h"
#include "lcd_i2cModule.h"
#include "stm32l0xx_hal_tim.h"
#include "stdio.h"

 /// zmienna konfigurujaca I2C
I2C_HandleTypeDef hi2c1;
/// zmienna konfigurujaca timer 3 
TIM_HandleTypeDef htim3;
/// zmienna konfigurujaca timer 21
TIM_HandleTypeDef htim21;
/// port, do ktorego podlaczony jest czujnik temperatury DHT11
#define DHT11_PORT GPIOA
/// pin, do ktorego podlaczony jest czujnik temperatury DHT11 
#define DHT11_PIN GPIO_PIN_11
/// maksymalna predkosc obrotow wiatraka
#define MAX_ROTATION 49999
/// mininalna predkosc obrotow wiatraka
#define NO_ROTATION 0
/// srednia predkosc obrotow wiatraka
#define MEDIUM_ROTATION 30000
/// funkcja konfigurujaca zegar systemowy
void SystemClock_Config(void);
/// funkcja inicjalizujaca GPIO
static void MX_GPIO_Init(void);
/// funkcja inicjalizujaca protokol I2C \- sluzacy do przesylu danych na wyslietlacz LCD
static void MX_I2C1_Init(void);
/// funkcja inicjalizujaca timer 3 \-sluzacy do generacji sygnalu PWM 
static void MX_TIM3_Init(void);
/// funkcja inicjalizujaca timer 21 \-sluzacy do pomiaru czasu w mikrosekundach
static void MX_TIM21_Init(void);

/// czesc calkowita danych czujnika wilgotnosci
uint8_t Rh_byte1;
/// czesc dziesietna danych czujnika wilgotnosci
uint8_t Rh_byte2;
/// czesc calkowita danych czujnika tempertury
uint8_t Temp_byte1;
/// czesc dziesietna danych czujnika wilgotnosci
uint8_t Temp_byte2;
/// zmienna pomocnicza
uint16_t RH;
/// zmienna pomocnicza
uint16_t TEMP;
/// zmienna pomocnicza
float Temperature = 0;
/// zmienna pomocnicza
float Humidity = 0;
/// flaga ustawiana w momencie gotowosci czujnika do wysylania danych
uint8_t Presence = 0;

/// Funkcja generujaca opoznienie w mikrosekundach.\n
/// Wejscie:
/// \arg \c time \- czas opoznienia podany w us
void delay(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim21, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim21)) < time);
}

/// Funkcja wyswietlajaca temperature na ekranie LCD.\n
/// Wejscie:
/// \arg \c Temp \- temperatura do wyswietlenia 
void Display_Temp(float Temp)
{
	char str[20] = { 0 };
	LCD_SetCursor(1, 1);

	sprintf(str, "TEMP: %.1f ", Temp);
	LCD_Send_String(str, STR_NOSLIDE);
	LCD_Send_String("C     ", STR_NOSLIDE);
}


/// Funkcja wyswietlajaca wilgotnosc powietrza na ekranie LCD.\n
/// Wejscie:
/// \arg \c Rh  \- wilgotnosc do wyswietlenia 
void Display_Rh(float Rh)
{
	char str[20] = { 0 };
	LCD_SetCursor(2, 1);

	sprintf(str, "WILG: %.1f ", Rh);
	LCD_Send_String(str, STR_NOSLIDE);
	LCD_Send_String("%     ", STR_NOSLIDE);
}


/// Funkcja zmieniajaca stan podanego pinu na OUTPUT.\n
/// Wejscie:
/// \arg \c GPIOx \- PORT\n
/// \arg \c GPIO_Pin \- PIN
void Set_Pin_Output(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/// Funkcja zmieniajaca stan podanego pinu na INPUT.\n
/// Wejscie:
/// \arg \c GPIOx \- PORT\n
/// \arg \c GPIO_Pin  \- PIN
void Set_Pin_Input(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/// Funkcja inicjalizujaca czujnik DHT11.\n
/// Aby zainicjalizowac DHT11 nalezy ustawic pin odpowiadajacy za wymiane danych
/// na warosc LOW przez minimum 18ms, nastepnie nalezy ustawic pin w stan HIGH.\n
/// Po wywolaniu tej funkcji czujnik powinien zareagowac na wybudzenie.
void DHT11_Start(void)
{
	Set_Pin_Output(DHT11_PORT, DHT11_PIN);	//Ustawienie pinu w stan OUTPUT
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 0);
	delay(18000);
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);
	delay(20);
	Set_Pin_Input(DHT11_PORT, DHT11_PIN);
}

/// Funkcja odczytujaca i weryfikujaca odpowiedz czujnika na uprzednia inicjalizacje.\n
/// Poprawne wybudzenie czujnika powinno skutkowac ustawieniem pinu danych
/// na wartosc LOW przez 80us, a nastepnie HIGH przez 80us.
/// Wyjscie:
/// \arg \c Response  \- Flaga swiadczaca o gotowosci lub niegotowosci do przesylu danych
uint8_t DHT11_Check_Response(void)
{
	uint8_t Response = 0;
	delay(35);
	if (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))
	{
		delay(80);
		if ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))) { Response = 1; }
		else { Response = -1; }
	}
	while ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)));

	return Response;
}

/// Funkcja odczytujaca bajt danych z czujnika.\n
/// Wyslanie kazdego bitu danych poprzedzone jest trwajacym 50us stanem niskim.\n
/// Nastepnie pin ustawiany jest w stan wysoki a czas trwania stanu HIGH rozroznia wartosc bitu (0 lub 1).
/// - 26\-28us \- logiczne "0"\n
/// - 70us \- logiczne "1"\n\n
/// Wyjscie:
/// \arg \c i \- bajt danych
uint8_t DHT11_Read(void)
{
	uint8_t i = 0, j;
	for (j = 0; j < 8; j++)
	{
		while (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)));
		delay(40);
		if (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))   // jezeli po 40us jest w stanie niskim...
		{
			i &= ~(1 << (7 - j));   // ...wpisz zero...
		}
		else i |= (1 << (7 - j));  // ...jezeli w wysokim to wpisz jedynke
		while ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)));  // czekaj az bedzie w stanie niskim
	}
	return i;
}

/// Funkcja main\n
/// Funkcja zawiera implementacje dwoch trybow:
/// 1. automatyczna regulacja temperatury\n
/// 2. sterowanie wiatrakiem za pomoca klaskania\n
int main(void)
{
	// Poczatkowa inicjalizacja 
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_TIM3_Init();
	MX_TIM21_Init();

	LCD_i2cDeviceCheck();
	LCD_Init();
	LCD_BackLight(LCD_BL_ON);

	HAL_TIM_Base_Start(&htim21);
	HAL_TIM_Base_Start(&htim3);

	// zmienne lokalne
	float out_T = 0;
	float out_H = 0;
	int i = 0;
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, NO_ROTATION);

	LCD_Send_String("INICJALIZACJA...", STR_NOSLIDE);

	while (1)
	{
		/*******************TRYB 1************************/
		if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))) {

			out_T = 0;
			out_H = 0;

			for (i = 0; i < 10; i++) {

				DHT11_Start();								//Wybudzenie DHT11
				Presence = DHT11_Check_Response();			//Sprawdzenie odpowiedzi DHT11
				Rh_byte1 = DHT11_Read();					//Odczyt 4 bajtow danych
				Rh_byte2 = DHT11_Read();
				Temp_byte1 = DHT11_Read();
				Temp_byte2 = DHT11_Read();

				TEMP = Temp_byte1;
				RH = Rh_byte1;

				/*Rzutowanie otrzymanych wartosci na typ float*/
				Temperature = (float)TEMP;
				Humidity = (float)RH;

				/*Sygnalizacja za pomoca diody jednego pelnego pomiaru*/
				HAL_Delay(1000);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

				/*Sumowanie wynikow z kazdego pomiaru w celu zmniejszenia ryzyka bledu*/
				out_T += Temperature;
				out_H += Humidity;
			}
			/*Wyswietlenie sredniej arytmetycznej otrzymanych 10-ciu pomiarow*/
			Display_Temp((out_T / 10));
			Display_Rh(out_H / 10);

			/*Dostosowanie predkosci obrotow wiatraka do panujacej temeratury*/
			if ((out_T / 10) > 22) {
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, NO_ROTATION);
			}
			else {
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, MEDIUM_ROTATION);
			}

		}

		/*******************TRYB 2************************/
		/*Tryb pozwalajacy sterowac wiatrakiem za pomoca np. klaskania*/
		else {
			/*Wstepna inicjalizacja obrotow wiatraka*/
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, NO_ROTATION);
			/*Oczekiwanie na wysoki poziom sygnalu z komparatora --> wykrycie dzwieku */
			while (((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)))) {}
			/*Oczekiwanie na niski poziom sygnalu z komparatora */
			/*Klasniecie powoduje szybki skok napiecia LOW-->HIGH, HIGH-->LOW */
			while (!((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)))) {
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, MAX_ROTATION);
			}
			/*Ponowne wykrycie dzwieku dezaktywujace obroty wiatraka */
			while (((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)))) {}
			while (!((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)))) {
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, NO_ROTATION);
			}
		}
	}
}


void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

static void MX_I2C1_Init(void)
{

	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x40000A0B;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		Error_Handler();
	}
}

static void MX_TIM3_Init(void)
{

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 4;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 49999;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIMEx_RemapConfig(&htim3, TIM3_TI2_GPIOB5_AF4) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_MspPostInit(&htim3);

}


static void MX_TIM21_Init(void)
{

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	htim21.Instance = TIM21;
	htim21.Init.Prescaler = 12 - 1;				//Zegar 12MHz z prescalerem 12 generuje "tick" co 1us
	htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim21.Init.Period = 0xffff - 1;
	htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim21.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim21, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	/*Configure GPIOA pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);

	/*Configure GPIOB pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA11 */
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : PB14 | PB13 */
	GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//*Configure GPIO pin : PB7 */
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//*Configure GPIO pin : PB2 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

}
#endif
