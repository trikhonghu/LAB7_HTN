/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
#include "ds3231.h"
#include "sensor.h"
#include "buzzer.h"
#include "touch.h"
#include "fsm.h"
#include "snake.h"
#include "screen.h"
#include "touch_screen.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define INIT 0
#define DRAW 1
#define CLEAR 2

int draw_Status = INIT;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void test_LedDebug();
void touchProcess();
void test_button();
uint8_t isButtonClear();
void test_Adc();
void sendSensor();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_FSMC_Init();
  MX_I2C1_Init();
  MX_TIM13_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
// touch_Adjust();
 setTimer3(100);
 setTimer5(10);
 setTimer7(10);
 while (1)
  {
	  //scan touch screen
	  //check if touch screen is touched
	  /*if(touch_IsTouched() && draw_Status == DRAW){
            //draw a point at the touch position
		  lcd_DrawPoint(touch_GetX(), touch_GetY(), RED);
	  }*/
	  // 50ms task
	  while(!flag_timer2);
	  flag_timer2 = 0;
	  touch_Scan();
	  button_Scan();
	  if(flag_timer5 == 1){
		  sendSensor();
		  setTimer5(5000);
	  }
	  if(isHumidity()){
		  buzzer_check = 1;
	  }else{
		  buzzer_check = 0;
	  }
	  if (isLight()){
		HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, SET);
	  }else{
		  HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, RESET);
	  }
//	  if(status == INIT || status == GAME_OVER)
//		  test_Adc();
	  //touchProcess();
	  fsm_machine();
	  test_LedDebug();
	  fsm_send_buzzer();
	  //test_button();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init(){
	  timer_init();
	  button_init();
	  buzzer_init();
	  lcd_init();
	  touch_init();
	  setTimer2(50);
	  uart_init_esp();

	  lcd_Clear(BLACK);
	  lcd_Fill(50, 200, 190, 300, GREEN);
	  lcd_ShowStr(90,235,"START",BLACK,BLACK,24,1);
}

uint8_t count_adc = 0;

void test_Adc(){
	count_adc = (count_adc + 1)%20;
	if(count_adc == 0){
		sensor_Read();
		lcd_ShowStr(10, 0, "Wattage:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(130, 0,getWattage(), 4, RED, BLACK, 16);
		if(!isLight()){
			lcd_ShowStr(10, 20, "Light:", RED, BLACK, 16, 0);
			lcd_ShowStr(130, 20,"Strong", RED, BLACK, 16, 0);
		}else{
			lcd_ShowStr(10, 20, "Light:", RED, BLACK, 16, 0);
			lcd_ShowStr(130, 20,"Weak  ", RED, BLACK, 16, 0);
		}
		//lcd_ShowStr(10, 140, "Light:", RED, BLACK, 16, 0);
		//lcd_ShowIntNum(130, 140, sensor_GetLight(), 4, RED, BLACK, 16);
		lcd_ShowStr(10, 40, "Potentiometer:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(130, 40, ((float)sensor_GetPotentiometer()/4095)*100, 4, RED, BLACK, 16);
		//lcd_ShowIntNum(130, 40, sensor_GetPotentiometer(), 4, RED, BLACK, 16);
		lcd_ShowStr(10, 60, "Temperature:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(130, 60,sensor_GetTemperature(), 4, RED, BLACK, 16);
	}
}

uint8_t count_led_debug = 0;

void test_LedDebug(){
	count_led_debug = (count_led_debug + 1)%20;
	if(count_led_debug == 0){
		HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
	}
}

uint8_t isButtonClear(){
	if(!touch_IsTouched()) return 0;
	return touch_GetX() > 60 && touch_GetX() < 180 && touch_GetY() > 10 && touch_GetY() < 60;
}

void touchProcess(){
	switch (draw_Status) {
		case INIT:
                // display blue button
			lcd_Fill(60, 10, 180, 60, GBLUE);
			lcd_ShowStr(90, 20, "CLEAR", RED, BLACK, 24, 1);
			draw_Status = DRAW;
			break;
		case DRAW:
			if(isButtonClear()){
				draw_Status = CLEAR;
                    // clear board
				lcd_Fill(0, 60, 240, 320, BLACK);
                    // display green button
				lcd_Fill(60, 10, 180, 60, GREEN);
				lcd_ShowStr(90, 20, "CLEAR", RED, BLACK, 24, 1);
			}
			break;
		case CLEAR:
			if(!touch_IsTouched()) draw_Status = INIT;
			break;
		default:
			break;
	}
}

void test_button(){
	for(int i = 0; i < 16; i++){
		if(button_count[i] == 1){
			led7_SetDigit(i/10, 2, 0);
			led7_SetDigit(i%10, 3, 0);
		}
	}
}

void sendSensor(){
	if(send_flag == 0){
		char res[100];
		char light[10];
		if(!isLight()){
			sprintf(light, "Strong");
		}else{
			sprintf(light, "Weak");
		}
		//int light = sensor_GetLight();
		int po1 = sensor_GetPotentiometer();
		int temp1 = sensor_GetTemperature();
		if(status != PLAY){
			sprintf(res, "Light : %s\nPotentiometer : %d \nTemperature : %d\nNo one is playing\n%c",light, po1, temp1, sec);// khong co ai choi
			uart_EspSendString(res);
		}
		if(status == PLAY){
			sprintf(res, "Light : %s\nPotentiometer : %d \nTemperature : %d\n%d is playing\nTime : %d sec\nScore : %d\n%c",light, po1, temp1, ID, count, score, sec);//dang co nguoi choi
			uart_EspSendString(res);
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
