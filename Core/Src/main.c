/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "pdm2pcm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "mic_handler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "small_words_model.h"
#include "small_words_model_data.h"

#include "fft.h"
#include "libmfcc.h"

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
CRC_HandleTypeDef hcrc;

I2S_HandleTypeDef hi2s2;
DMA_HandleTypeDef hdma_spi2_rx;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2S2_Init(void);
static void MX_CRC_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define WIN_LENGTH 1024
#define HOP_LENGTH WIN_LENGTH/2 // 512

//float pcm_buf[WIN_LENGTH];
uint16_t pdmRxBuf[WIN_LENGTH];
uint16_t MidBuffer[16];
uint8_t rxstate = 0;

uint16_t fifobuf[WIN_LENGTH];
uint16_t fifo_w_ptr = 0;
uint16_t fifo_r_ptr = 0;
uint8_t fifo_read_enabled = 0;
char b[50];

fft_complex_t pcm_data[WIN_LENGTH];
double spectrum[WIN_LENGTH];
int bits = 8; // log2(HOP_LENGTH)

void FifoWrite(uint16_t data) {
	// TODO set to 0 the counter
	fifobuf[fifo_w_ptr] = data;
	fifo_w_ptr++;
	if (fifo_w_ptr >= WIN_LENGTH) {
		fifo_read_enabled = 1;
		fifo_w_ptr = 0;
	}
}

uint16_t FifoRead() {
	// TODO set to 0 the counter
	uint16_t val = fifobuf[fifo_r_ptr];
	fifo_r_ptr++;
	if (fifo_r_ptr >= WIN_LENGTH)
		fifo_r_ptr = 0;
	return val;
}

void debug(const char *c) {
	HAL_UART_Transmit(&huart2, (uint8_t*) c, strlen(c),
	HAL_MAX_DELAY);
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	/*
	 char buf[50];
	 int buf_len = 0;
	 ai_error ai_err;
	 ai_i32 nbatch;
	 uint32_t timestamp;
	 float y_val;

	 // Chunk of memory used to hold intermediate values for neural network
	 AI_ALIGNED(4) ai_u8 activations[AI_SMALL_WORDS_MODEL_DATA_ACTIVATIONS_SIZE];
	 //AI_ALIGNED(4): specify a minimum alignment measured in bytes

	 // Buffers used to store input and output tensors
	 AI_ALIGNED(4) ai_i8 in_data[AI_SMALL_WORDS_MODEL_IN_1_SIZE_BYTES];
	 AI_ALIGNED(4) ai_i8 out_data[AI_SMALL_WORDS_MODEL_OUT_1_SIZE_BYTES];

	 // Pointer to our model
	 ai_handle small_words_model = AI_HANDLE_NULL;

	 // Initialize wrapper structs that hold pointers to data and info about the
	 // data (tensor height, width, channels)
	 ai_buffer ai_input[AI_SMALL_WORDS_MODEL_IN_NUM] = AI_SMALL_WORDS_MODEL_IN;
	 ai_buffer ai_output[AI_SMALL_WORDS_MODEL_OUT_NUM] = AI_SMALL_WORDS_MODEL_OUT;

	 // Set working memory and get weights/biases from model
	 ai_network_params ai_params = { AI_SMALL_WORDS_MODEL_DATA_WEIGHTS(
	 ai_small_words_model_data_weights_get()), AI_SMALL_WORDS_MODEL_DATA_ACTIVATIONS(
	 activations) };

	 // Set pointers wrapper structs to our data buffers
	 ai_input[0].n_batches = 1;
	 ai_input[0].data = AI_HANDLE_PTR(in_data);
	 ai_output[0].n_batches = 1;
	 ai_output[0].data = AI_HANDLE_PTR(out_data);
	 */
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
	MX_DMA_Init();
	MX_I2S2_Init();
	MX_CRC_Init();
	MX_PDM2PCM_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	//__HAL_RCC_CRC_CLK_ENABLE();
	//CRC->CR = CRC_CR_RESET;
	//mic_init(&hi2s2);
	HAL_I2S_Receive_DMA(&hi2s2, &pdmRxBuf[0], HOP_LENGTH / 2);
	//init_mfcc();
	/*
	 // Create instance of neural network
	 ai_err = ai_small_words_model_create(&small_words_model, AI_SMALL_WORDS_MODEL_DATA_CONFIG);
	 if (ai_err.type != AI_ERROR_NONE) {
	 buf_len = sprintf(buf, "Error: could not create NN instance\r\n");
	 HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	 while (1)
	 ;
	 }

	 // Initialize neural network
	 if (!ai_small_words_model_init(small_words_model, &ai_params)) {
	 buf_len = sprintf(buf, "Error: could not initialize NN\r\n");
	 HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
	 while (1)
	 ;
	 }
	 */
	/* USER CODE END 2 */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
		/*
		 // Perform inference
		 nbatch = ai_small_words_model_run(small_words_model, &ai_input[0], &ai_output[0]);
		 if (nbatch != 1) {
		 buf_len = sprintf(buf, "Error: could not run inference\r\n");
		 HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
		 }

		 // Read output (predicted y) of neural network
		 y_val = ((float*) out_data)[0];
		 */
		if (rxstate == 1) {
			// Filter the input values and store the results in an intermediate buffer
			PDM_Filter(&pdmRxBuf[0], &MidBuffer[0], &PDM1_filter_handler);

			// The mid buffer has length 16 because the PDM is configured to produce 16 samples
			// of PCM each time it is called
			for (int i = 0; i < 16; i++) {
				FifoWrite(MidBuffer[i]);
			}

			// Reset rx state
			rxstate = 0;

		}

		if (rxstate == 2) {
			// Filter the input values and store the results in an intermediate buffer
			PDM_Filter(&pdmRxBuf[HOP_LENGTH / 2], &MidBuffer[0],
					&PDM1_filter_handler);
			for (int i = 0; i < 16; i++) {
				FifoWrite(MidBuffer[i]);
			}

			/*sprintf(b, "%d\r\n", fifo_w_ptr - fifo_r_ptr);
			 debug(b);

			 // Check if there are all values of the window to start processing the audio signal
			 if (fifo_w_ptr - fifo_r_ptr > WIN_LENGTH) {
			 fifo_read_enabled = 1;
			 debug("fifo_read_enabled\r\n");
			 }*/

			// Reset rx state
			rxstate = 0;
		}

		if (fifo_read_enabled == 1) {
			// Read 1024 samples from the PCM buffer
			for (int i = 0; i < WIN_LENGTH; i++) {
				// Cast the value to float
				int32_t data = FifoRead();
				//pcm_buf[i] = data;
				pcm_data[i].r = data;
			}

			/*
			 POST PROCESSING non serve dal momento che otteniamo alla fine degli interi

			 PCM_post_processing(pcm_buf);

			 for (int i = 0; i < 128; i++) {
			 pcm_data[i].r = pcm_buf[i];
			 }*/

			fft_permutate(pcm_data, bits);
			fft_forward(pcm_data, bits);

			// make FFT results purely real
			for (int i = 0; i < WIN_LENGTH; i++) {
				spectrum[i] = pcm_data[i].r;
			}

			//PCM_post_processing(spectrum, WIN_LENGTH);

			/*for (int i = 0; i < WIN_LENGTH; i++) {
			 int l = sprintf(b, "%f\r\n", spectrum[i]);
			 HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
			 HAL_MAX_DELAY);
			 }
			 int l = sprintf(b, "-------------------------END\r\n");
			 HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
			 HAL_MAX_DELAY);*/

			// compute the first coefficient
			int numbins = 2;
			for (int coeff = 0; coeff < numbins; coeff++) {
				float mfcc_result = GetCoefficient(spectrum, 8000, numbins,
				WIN_LENGTH, coeff);
				int l = sprintf(b, "%f\r\n", mfcc_result);
				HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
				HAL_MAX_DELAY);
			}
			int l = sprintf(b, "-------------------------END\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
			HAL_MAX_DELAY);
		}
	}
	/*	if (mic_start_recording() == 0) {
	 int result = mic_monitor();
	 for (int i = 0; i < 1000000; i++) {
	 ;
	 }
	 if (result == 0) {
	 // no input: BLUE LED
	 HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
	 } else if (result == -1) {
	 // Error in PDM->PCM conversion: RED LED
	 HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
	 } else {
	 // PDM->PCM conversion done: GREEN LED
	 HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
	 int16_t *pcm = get_pcm();
	 char b[32];
	 for (int i = 0; i < PCM_BUF_SIZE; i++) {
	 sprintf(b, "%" PRIi16 "\r\n", *(pcm + i));
	 HAL_UART_Transmit(&huart2, (uint8_t*) b, 32,
	 HAL_MAX_DELAY);
	 memset(b, 0, 32);
	 }
	 HAL_UART_Transmit(&huart2, (uint8_t*) "END\r\n",
	 strlen("END\r\n"),
	 HAL_MAX_DELAY);
	 }
	 mic_stop_recording();

	 } else {
	 // Failed to start I2S transmission: ORANGE LED
	 HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
	 }*/
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
//}
/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Macro to configure the PLL multiplication factor
	 */
	__HAL_RCC_PLL_PLLM_CONFIG(8);
	/** Macro to configure the PLL clock source
	 */
	__HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
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
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void) {

	/* USER CODE BEGIN CRC_Init 0 */

	/* USER CODE END CRC_Init 0 */

	/* USER CODE BEGIN CRC_Init 1 */

	/* USER CODE END CRC_Init 1 */
	hcrc.Instance = CRC;
	if (HAL_CRC_Init(&hcrc) != HAL_OK) {
		Error_Handler();
	}
	__HAL_CRC_DR_RESET(&hcrc);
	/* USER CODE BEGIN CRC_Init 2 */

	/* USER CODE END CRC_Init 2 */

}

/**
 * @brief I2S2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2S2_Init(void) {

	/* USER CODE BEGIN I2S2_Init 0 */

	/* USER CODE END I2S2_Init 0 */

	/* USER CODE BEGIN I2S2_Init 1 */

	/* USER CODE END I2S2_Init 1 */
	hi2s2.Instance = SPI2;
	hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
	hi2s2.Init.Standard = I2S_STANDARD_MSB;
	hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
	hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
	hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_192K;
	hi2s2.Init.CPOL = I2S_CPOL_LOW;
	hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
	hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
	if (HAL_I2S_Init(&hi2s2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2S2_Init 2 */

	/* USER CODE END I2S2_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin */
	GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
	rxstate = 1;
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
	rxstate = 2;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
