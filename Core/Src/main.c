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
#include "speech_commands_model.h"
#include "speech_commands_model_data.h"
#include "commands.h"

#include "arm_math.h"

#include "feature_extraction.h"

// BSP drivers
#include "../../Drivers/BSP/STM32F4-Discovery/stm32f4_discovery.h"
#include "../../Drivers/BSP/STM32F4-Discovery/stm32f4_discovery_audio.h"
#include "audio_record.h"

#include "elapsed_time.h"
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

I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s2;
DMA_HandleTypeDef hdma_spi2_rx;

SPI_HandleTypeDef hspi1;

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
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

// Initialize filtering structures
void Preprocessing_Init(void);
void SleepMode(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* For MFCCs computation -------------------------------------------- */
#define SAMPLE_RATE  16000U /* Input signal sampling rate */
#define FFT_LEN       2048U /* Number of FFT points. Must be greater or equal to FRAME_LEN */
#define FRAME_LEN   FFT_LEN /* Window length and then padded with zeros to match FFT_LEN */
#define HOP_LEN        512U /* Number of overlapping samples between successive frames */
#define NUM_MELS       128U /* Number of mel bands */
#define NUM_MEL_COEFS 2020U /* Number of mel filter weights. Returned by MelFilterbank_Init */
#define NUM_MFCC        16U /* Number of MFCCs to return */

arm_rfft_fast_instance_f32 S_Rfft;
MelFilterTypeDef S_MelFilter;
DCT_InstanceTypeDef S_DCT;
SpectrogramTypeDef S_Spectr;
MelSpectrogramTypeDef S_MelSpectr;
LogMelSpectrogramTypeDef S_LogMelSpectr;
MfccTypeDef S_Mfcc;

float32_t pInFrame[FRAME_LEN];
float32_t pOutColBuffer[NUM_MFCC];
float32_t pWindowFuncBuffer[FRAME_LEN];
float32_t pSpectrScratchBuffer[FFT_LEN];
float32_t pDCTCoefsBuffer[NUM_MELS * NUM_MFCC];
float32_t pMfccScratchBuffer[NUM_MELS];
float32_t pMelFilterCoefs[NUM_MEL_COEFS];
uint32_t pMelFilterStartIndices[NUM_MELS];
uint32_t pMelFilterStopIndices[NUM_MELS];
uint32_t num_frames = 1 + (WR_BUFFER_SIZE - FRAME_LEN) / HOP_LEN;
//uint32_t num_frames = 1 + (16000 - FRAME_LEN) / HOP_LEN;

/* -------------------------------------------- */

// Check if button is pressed
static uint8_t button_pressed = 0;

// Macros to print an uint16 as raw bytes
#define PRI_BYTES_2 "%c%c"
#define ARG_BYTES_BE_2(var) \
	((const char *)&(var))[1], \
	((const char *)&(var))[0]

#define ARG_BYTES_LE_2(var) \
	((const char *)&(var))[0], \
	((const char *)&(var))[1]

enum leds_status {
	Off, Green, Blue, Red, Orange
};

char b[50];
int buf_len = 0;

uint8_t display_words_enabled = 0;
uint8_t print_words = 1;
enum leds_status led_status = Off;

/* For MFCCs computation -------------------------------------------- */
void AudioPreprocessing_Run(int16_t *pInSignal, float32_t *pOutMfcc,
		uint32_t signal_len) {
	const uint32_t num_frames = 1 + (signal_len - FRAME_LEN) / HOP_LEN;

	for (uint32_t frame_index = 0; frame_index < num_frames; frame_index++) {
		buf_to_float_normed(&pInSignal[HOP_LEN * frame_index], pInFrame,
		FRAME_LEN);

		MfccColumn(&S_Mfcc, pInFrame, pOutColBuffer);
		/* Reshape column into pOutMfcc */
		for (uint32_t i = 0; i < NUM_MFCC; i++) {
			pOutMfcc[i * num_frames + frame_index] = pOutColBuffer[i];
		}
	}
}
/* -------------------------------------------- */

void debug(const char *c) {
	HAL_UART_Transmit(&huart2, (uint8_t*) c, strlen(c),
	HAL_MAX_DELAY);
}

void toggle_leds() {
	BSP_LED_Toggle(LED3);
	HAL_Delay(100);
	BSP_LED_Toggle(LED4);
	HAL_Delay(100);
	BSP_LED_Toggle(LED5);
	HAL_Delay(100);
	BSP_LED_Toggle(LED6);
	HAL_Delay(100);
}

// TODO: document me!
void recognize_commands(const char *word) {
	if (strcmp(word, ONE) == 0) {
		if (led_status != Green) {
			if (led_status == Blue) {
				HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			} else if (led_status == Red) {
				HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			} else if (led_status == Orange) {
				HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			}
			// GREEN LED
			HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			led_status = Green;
		}
	} else if (strcmp(word, TWO) == 0) {
		if (led_status != Blue) {
			if (led_status == Green) {
				HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			} else if (led_status == Red) {
				HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			} else if (led_status == Orange) {
				HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			}
			// BLUE LED
			HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			led_status = Blue;
		}
	} else if (strcmp(word, THREE) == 0) {
		if (led_status != Red) {
			if (led_status == Green) {
				HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			} else if (led_status == Blue) {
				HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			} else if (led_status == Orange) {
				HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			}
			// RED LED
			HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			led_status = Red;
		}
	} else if (strcmp(word, FOUR) == 0) {
		if (led_status != Orange) {
			if (led_status == Green) {
				HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			} else if (led_status == Blue) {
				HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			} else if (led_status == Red) {
				HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			}
			// ORANGE LED
			HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			led_status = Orange;
		}
	}

	// case in which the word spoken is different from the four colors
	else {
		// if there is a led on, turn it off
		if (led_status == Green) {
			HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
		} else if (led_status == Blue) {
			HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
		} else if (led_status == Red) {
			HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
		} else if (led_status == Orange) {
			HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
		}

		led_status = Off;

		if (strcmp(word, ON) == 0) {
			print_words = 0;
			if (!display_words_enabled) {	// We need to enable words display
				buf_len = sprintf(b, "Now the words will be displayed\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
			} else {		// Words display is already enabled
				buf_len = sprintf(b, "Words display is already enabled\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
			}

			// enable words display
			display_words_enabled = 1;
		} else if (strcmp(word, OFF) == 0) {
			// disable the display of the words
			if (display_words_enabled) {
				display_words_enabled = 0;

				buf_len = sprintf(b,
						"Now the words will not be displayed anymore\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
			}
		} else if (strcmp(word, VISUAL) == 0) {
			print_words = 0;

			for (uint8_t i = 0; i < ELAPSED_TIME_MAX_SECTIONS; i++) {
				switch (i) {
				case 0:
					buf_len = sprintf(b,
							"Audio acquisition execution time:\r\n");
					break;
				case 1:
					buf_len = sprintf(b,
							"MFCCs extraction execution time:\r\n");
					break;
				case 2:
					buf_len = sprintf(b, "Inference execution time:\r\n");
					break;
				default:
					break;
					// unreachable
				}
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);

				buf_len = sprintf(b, "\telapsed=%lu\r\n",
						elapsed_time_tbl[i].current);
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);

				buf_len = sprintf(b, "\tmax=%lu\r\n", elapsed_time_tbl[i].max);
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);

				buf_len = sprintf(b, "\tmin=%lu\r\n", elapsed_time_tbl[i].min);
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
			}
		} else if (strcmp(word, STOP) == 0) {

			print_words = 0;

			buf_len = sprintf(b, "Execution times are now reset\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);

			for (uint8_t i = 0; i < ELAPSED_TIME_MAX_SECTIONS; i++) {
				elapsed_time_clr(i);
			}
		}
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	ai_error ai_err;
	ai_i32 nbatch;

	// Chunk of memory used to hold intermediate values for neural network
	AI_ALIGNED(4) ai_u8 activations[AI_SPEECH_COMMANDS_MODEL_DATA_ACTIVATIONS_SIZE];
	//AI_ALIGNED(4): specify a minimum alignment measured in bytes

	// Buffers used to store input and output tensors
	AI_ALIGNED(4) ai_float in_data[AI_SPEECH_COMMANDS_MODEL_IN_1_SIZE_BYTES];
	AI_ALIGNED(4) ai_float out_data[AI_SPEECH_COMMANDS_MODEL_OUT_1_SIZE_BYTES];

	// Pointer to our model
	ai_handle speech_commands_model = AI_HANDLE_NULL;

	// Initialize wrapper structs that hold pointers to data and info about the
	// data (tensor height, width, channels)
	ai_buffer ai_input[AI_SPEECH_COMMANDS_MODEL_IN_NUM] =
	AI_SPEECH_COMMANDS_MODEL_IN;
	ai_buffer ai_output[AI_SPEECH_COMMANDS_MODEL_OUT_NUM] =
	AI_SPEECH_COMMANDS_MODEL_OUT;

	// Set working memory and get weights/biases from model
	ai_network_params ai_params =
					AI_NETWORK_PARAMS_INIT(
							AI_SPEECH_COMMANDS_MODEL_DATA_WEIGHTS(ai_speech_commands_model_data_weights_get()),
							AI_SPEECH_COMMANDS_MODEL_DATA_ACTIVATIONS(activations)
					);

	// Set pointers wrapper structs to our data buffers
	ai_input[0].n_batches = 1;
	ai_input[0].data = AI_HANDLE_PTR(in_data);
	ai_output[0].n_batches = 1;
	ai_output[0].data = AI_HANDLE_PTR(out_data);

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	// Initialize leds
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	Preprocessing_Init();

	elapsed_time_init();

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	// Initialize button
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_I2S2_Init();
	MX_CRC_Init();
	MX_PDM2PCM_Init();
	MX_USART2_UART_Init();
	MX_I2C1_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */

	// Create instance of neural network
	ai_err = ai_speech_commands_model_create(&speech_commands_model,
	AI_SPEECH_COMMANDS_MODEL_DATA_CONFIG);
	if (ai_err.type != AI_ERROR_NONE) {
		buf_len = sprintf(b, "Error: could not create NN instance\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
		while (1)
			;
	}

	// Initialize neural network
	if (!ai_speech_commands_model_init(speech_commands_model, &ai_params)) {
		buf_len = sprintf(b, "Error: could not initialize NN\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
		while (1)
			;
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		SleepMode();

		elapsed_time_start(0);
		AudioRecord_Test();
		elapsed_time_stop(0);

		elapsed_time_start(1);
		AudioPreprocessing_Run((int16_t*) &WrBuffer[0], (ai_float*) &in_data[0],
		WR_BUFFER_SIZE);
		elapsed_time_stop(1);

		// Perform inference
		elapsed_time_start(2);
		nbatch = ai_speech_commands_model_run(speech_commands_model,
				&ai_input[0], &ai_output[0]);
		elapsed_time_stop(2);

		if (nbatch != 1) {
			buf_len = sprintf(b, "Error: could not run inference\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
		}

		uint8_t idx = argmax(out_data, AI_SPEECH_COMMANDS_MODEL_OUT_1_SIZE);

		char *word = get_word(idx);

		print_words = 1;

		recognize_commands(word);
		//display_words_enabled = 1; // only for debug -> to remove

		if (display_words_enabled) {
			// Do not print ON and VISUAL, since `recognize_commands` prints special messages for them
			if (print_words) {
				// Print output of neural network
				buf_len = sprintf(b, "%d %s\r\n", idx, word);
				HAL_UART_Transmit(&huart2, (uint8_t*) b, buf_len, 100);
			}
		}
	}

	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Macro to configure the PLL multiplication factor
	 */
	__HAL_RCC_PLL_PLLM_CONFIG(10);
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
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

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
	hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
	hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
	hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
	hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_8K;
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
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

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

	/*Configure GPIO pin : PA0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin */
	GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

void Preprocessing_Init(void) {
	/* Init window function */
	if (Window_Init(pWindowFuncBuffer, FRAME_LEN, WINDOW_HANN) != 0) {
		debug("ERROR: window init failed\r\n");
		while (1)
			;
	}

	/* Init RFFT */
	arm_rfft_fast_init_f32(&S_Rfft, FFT_LEN);

	/* Init mel filterbank */
	S_MelFilter.pStartIndices = pMelFilterStartIndices;
	S_MelFilter.pStopIndices = pMelFilterStopIndices;
	S_MelFilter.pCoefficients = pMelFilterCoefs;
	S_MelFilter.NumMels = NUM_MELS;
	S_MelFilter.FFTLen = FFT_LEN;
	S_MelFilter.SampRate = SAMPLE_RATE;
	S_MelFilter.FMin = 0.0;
	S_MelFilter.FMax = S_MelFilter.SampRate / 2.0;
	S_MelFilter.Formula = MEL_SLANEY;
	S_MelFilter.Normalize = 1;
	S_MelFilter.Mel2F = 1;
	MelFilterbank_Init(&S_MelFilter);
	if (S_MelFilter.CoefficientsLength != NUM_MEL_COEFS) {
		debug("ERROR: MelFilterbank init failed\r\n");
		while (1)
			; /* Adjust NUM_MEL_COEFS to match S_MelFilter.CoefficientsLength */
	}

	/* Init DCT operation */
	S_DCT.NumFilters = NUM_MFCC;
	S_DCT.NumInputs = NUM_MELS;
	S_DCT.Type = DCT_TYPE_II_ORTHO;
	S_DCT.RemoveDCTZero = 0;
	S_DCT.pDCTCoefs = pDCTCoefsBuffer;
	if (DCT_Init(&S_DCT) != 0) {
		debug("ERROR: DCT init failed\r\n");
		while (1)
			;
	}

	/* Init Spectrogram */
	S_Spectr.pRfft = &S_Rfft;
	S_Spectr.Type = SPECTRUM_TYPE_POWER;
	S_Spectr.pWindow = pWindowFuncBuffer;
	S_Spectr.SampRate = SAMPLE_RATE;
	S_Spectr.FrameLen = FRAME_LEN;
	S_Spectr.FFTLen = FFT_LEN;
	S_Spectr.pScratch = pSpectrScratchBuffer;

	/* Init MelSpectrogram */
	S_MelSpectr.SpectrogramConf = &S_Spectr;
	S_MelSpectr.MelFilter = &S_MelFilter;

	/* Init LogMelSpectrogram */
	S_LogMelSpectr.MelSpectrogramConf = &S_MelSpectr;
	S_LogMelSpectr.LogFormula = LOGMELSPECTROGRAM_SCALE_DB;
	S_LogMelSpectr.Ref = 1.0;
	S_LogMelSpectr.TopdB = HUGE_VALF;

	/* Init MFCC */
	S_Mfcc.LogMelConf = &S_LogMelSpectr;
	S_Mfcc.pDCT = &S_DCT;
	S_Mfcc.NumMfccCoefs = NUM_MFCC; //20
	S_Mfcc.pScratch = pMfccScratchBuffer;
}

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
 if (GPIO_Pin == GPIO_PIN_0) {
 button_pressed = 1;
 }
 }*/

void SleepMode(void) {

	HAL_UART_DeInit(&huart2);
	HAL_I2S_DeInit(&hi2s2);

	/* Suspend Tick increment to prevent wakeup by Systick interrupt.
	 Otherwise the Systick interrupt will wake up the device within 1ms (HAL time base) */
	HAL_SuspendTick();

	/* Request to enter SLEEP mode */
	HAL_PWR_EnterSLEEPMode(0, PWR_SLEEPENTRY_WFI);

	/* Resume Tick interrupt if disabled prior to sleep mode entry*/
	HAL_ResumeTick();

	/* Reinitialize UART2 */
	MX_USART2_UART_Init();

	/* Reinitialize I2S2 */
	MX_I2S2_Init();
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
