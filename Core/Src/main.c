/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 * @author		   : Federica Paoli'
 * @author		   : Stefano Taverni
 * @date	       : 2022-1
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
#include <execution_time.h>
#include "main.h"
#include "pdm2pcm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

/* BSP drivers */
#include "../../Drivers/BSP/STM32F4-Discovery/stm32f4_discovery.h"
#include "../../Drivers/BSP/STM32F4-Discovery/stm32f4_discovery_audio.h"

/* Audio processing */
#include "arm_math.h"
#include "feature_extraction.h"

#include "commands.h"
#include "audio_record.h"

/* AI model */
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "speech_commands_model.h"
#include "speech_commands_model_data.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

enum leds_status {
	Off, Green, Blue, Red, Orange
};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* Input signal sampling rate */
#define SAMPLE_RATE  16000U

/* Number of FFT points. It must be greater or equal to FRAME_LEN */
#define FFT_LEN       2048U

/* Window length and then padded with zeros to match FFT_LEN */
#define FRAME_LEN   FFT_LEN

/* Number of overlapping samples between successive frames */
#define HOP_LEN        512U

/* Number of Mel bands */
#define NUM_MELS       128U

/* Number of Mel filter weights. Returned by MelFilterbank_Init */
#define NUM_MEL_COEFS 2020U

/* Number of MFCCs to return */
#define NUM_MFCC        16U

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

/* Instance for floating-point RFFT/RIFFT */
arm_rfft_fast_instance_f32 rfft;

/* Instance for the floating-point MelFilterbank function */
MelFilterTypeDef mel_filter;

/* Instance for the floating-point DCT functions */
DCT_InstanceTypeDef dct;

/* Instance for the floating-point Spectrogram function */
SpectrogramTypeDef spectrogram;

/* Instance for the floating-point MelSpectrogram function */
MelSpectrogramTypeDef mel_spectrogram;

/* Instance for the floating-point Log-MelSpectrogram function */
LogMelSpectrogramTypeDef log_mel_spectrogram;

/* Instance for the floating-point Mfcc function */
MfccTypeDef mfcc;

/* Intermediate buffer that contains a signal frame */
float32_t frame_buffer[FRAME_LEN];

/* Intermediate buffer that contains Mel-Frequency Cepstral Coefficients (MFCCs) column  */
float32_t mfcc_col_buffer[NUM_MFCC];

/* Intermediate buffer that contains the window function  */
float32_t window_func_buffer[FRAME_LEN];

/* Temporary calculation buffer of length `FFT_LEN` */
float32_t spectrogram_scratch_buffer[FFT_LEN];

/* Intermediate buffer that contains the Discrete Cosine Transform coefficients */
float32_t dct_coefs_buffer[NUM_MELS * NUM_MFCC];

/* Temporary calculation buffer of length `NUM_MELS` */
float32_t mfcc_scratch_buffer[NUM_MELS];

/*Intermediate buffer that contains the Mel filter weights of length `NUM_MEL_COEFS` */
float32_t mel_filter_coefs[NUM_MEL_COEFS];

/* Intermediate buffer that contains the Mel filter coefficients start indices */
uint32_t mel_filter_start_indices[NUM_MELS];

/* Intermediate buffer that contains the Mel filter coefficients stop indices */
uint32_t mel_filter_stop_indices[NUM_MELS];

/* Number of frames of the input signal */
uint32_t num_frames = 1 + (PCM_BUFFER_SIZE - FRAME_LEN) / HOP_LEN;

/* Buffer used to print through the USART interface */
char usart_buffer[50];
int usart_buffer_length = 0;

/* Control words display */
uint8_t display_words_enabled = 0;

/* Check if the words can be printed */
uint8_t print_words = 1;

/* Board led status  */
enum leds_status led_status = Off;

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

/* Initialize audio processing structures */
void preprocessing_init(void);

/* MCU sleep mode */
void stop_mode(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief Compute MFCCs from the input signal audio.
 *   This function normalizes the input audio data in PCM form and extracts the
 *   MFCCs from them.
 *
 * @param  input_signal*   PCM input signal
 * @param  out_mfcc*       MFCCs output buffer
 * @param  signal_len      length of the input signal
 *
 * @retval None
 */
void preprocess_audio(int16_t *input_signal, float32_t *out_mfcc,
		uint32_t signal_len) {

	for (uint32_t frame_index = 0; frame_index < num_frames; frame_index++) {

		/* Convert 16-bit PCM into normalized floating point values */
		buf_to_float_normed(&input_signal[HOP_LEN * frame_index], frame_buffer,
		FRAME_LEN);

		MfccColumn(&mfcc, frame_buffer, mfcc_col_buffer);

		/* Reshape column into `out_mfcc` */
		for (uint32_t i = 0; i < NUM_MFCC; i++) {
			out_mfcc[i * num_frames + frame_index] = mfcc_col_buffer[i];
		}
	}
}

/**
 * @brief Recognize specific vocal commands.
 *   This function performs the following actions depending on the predicted 
 *   word:
 *      - `ON` -> enable words display
 *      - `OFF` -> disable words display
 *      - `VISUAL` -> show execution time statistics
 *      - `STOP` -> reset execution time statistics
 *      - `ONE` -> turn the green led on
 *      - `TWO` -> turn the blue led on
 *      - `THREE` -> turn the red led on
 *      - `FOUR` -> turn the orange led on
 *
 *   The following rules apply to the above commands:
 *      - `ON` command has no effect when `display_words_enabled` is true
 *      - `OFF` command has no effect when `display_words_enabled` is false
 *      - `VISUAL` and `STOP` commands will always have effect
 *      - the LEDs will always turn off unless their commands are pronounced
 *
 * @param  word*   a constant string to be recognized
 *
 * @retval None
 */
void recognize_commands(const char *word) {
	/* Turn on green led and turn off the others */
	if (strcmp(word, ONE) == 0) {
		if (led_status != Green) {
			if (led_status == Blue) {
				HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			} else if (led_status == Red) {
				HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			} else if (led_status == Orange) {
				HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			}
			HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			led_status = Green;
		}
		/* Turn on blue led and turn off the others */
	} else if (strcmp(word, TWO) == 0) {
		if (led_status != Blue) {
			if (led_status == Green) {
				HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			} else if (led_status == Red) {
				HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			} else if (led_status == Orange) {
				HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			}
			HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			led_status = Blue;
		}
		/* Turn on red led and turn off the others */
	} else if (strcmp(word, THREE) == 0) {
		if (led_status != Red) {
			if (led_status == Green) {
				HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			} else if (led_status == Blue) {
				HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			} else if (led_status == Orange) {
				HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			}
			HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			led_status = Red;
		}
		/* Turn on orange led and turn off the others */
	} else if (strcmp(word, FOUR) == 0) {
		if (led_status != Orange) {
			if (led_status == Green) {
				HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
			} else if (led_status == Blue) {
				HAL_GPIO_TogglePin(GPIOD, LD6_Pin);
			} else if (led_status == Red) {
				HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
			}
			HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			led_status = Orange;
		}
	}
	/* The input word is different from the four colors */
	else {
		/* If there is a led on, turn it off */
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

		/* Enable `display_words_enabled` */
		if (strcmp(word, ON) == 0) {
			print_words = 0;
			if (!display_words_enabled) {
				usart_buffer_length = sprintf(usart_buffer,
						"Now the words will be displayed\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);
				/* `display_words_enabled` is already enabled */
			} else {
				usart_buffer_length = sprintf(usart_buffer,
						"Words display is already enabled\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);
			}

			display_words_enabled = 1;
			/* Disable `display_words_enabled` */
		} else if (strcmp(word, OFF) == 0) {
			if (display_words_enabled) {
				display_words_enabled = 0;

				usart_buffer_length = sprintf(usart_buffer,
						"Now the words will not be displayed anymore\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);
			}
			/* Show execution time statistics */
		} else if (strcmp(word, VISUAL) == 0) {
			print_words = 0;

			for (uint8_t i = 0; i < EXECUTION_TIME_MAX_SECTIONS; i++) {
				switch (i) {
				case 0:
					usart_buffer_length = sprintf(usart_buffer,
							"Audio acquisition execution time:\r\n");
					break;
				case 1:
					usart_buffer_length = sprintf(usart_buffer,
							"MFCCs extraction execution time:\r\n");
					break;
				case 2:
					usart_buffer_length = sprintf(usart_buffer,
							"Inference execution time:\r\n");
					break;
				default:
					break;
					// unreachable
				}
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);

				usart_buffer_length = sprintf(usart_buffer, "\telapsed=%lu\r\n",
						time_statistics_blocks[i].elapsed);
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);

				usart_buffer_length = sprintf(usart_buffer, "\tmax=%lu\r\n",
						time_statistics_blocks[i].max);
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);

				usart_buffer_length = sprintf(usart_buffer, "\tmin=%lu\r\n",
						time_statistics_blocks[i].min);
				HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
						usart_buffer_length, 100);
			}
			/* Reset execution time statistics */
		} else if (strcmp(word, STOP) == 0) {

			print_words = 0;

			usart_buffer_length = sprintf(usart_buffer,
					"Execution times are now reset\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
					usart_buffer_length, 100);

			for (uint8_t i = 0; i < EXECUTION_TIME_MAX_SECTIONS; i++) {
				execution_time_clear(i);
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

	/* Chunk of memory used to hold intermediate values for the neural network */
	AI_ALIGNED(4) ai_u8 activations[AI_SPEECH_COMMANDS_MODEL_DATA_ACTIVATIONS_SIZE];

	/* Buffers used to store input and output tensors */
	AI_ALIGNED(4) ai_float in_data[AI_SPEECH_COMMANDS_MODEL_IN_1_SIZE_BYTES];
	AI_ALIGNED(4) ai_float out_data[AI_SPEECH_COMMANDS_MODEL_OUT_1_SIZE_BYTES];

	/* Pointer to the neural network model */
	ai_handle speech_commands_model = AI_HANDLE_NULL;

	/* Initialize wrapper structs that hold info about the data (tensor height, width, channels) */
	ai_buffer ai_input[AI_SPEECH_COMMANDS_MODEL_IN_NUM] =
	AI_SPEECH_COMMANDS_MODEL_IN;
	ai_buffer ai_output[AI_SPEECH_COMMANDS_MODEL_OUT_NUM] =
	AI_SPEECH_COMMANDS_MODEL_OUT;

	/* Allocate memory and get weights from the neural network model */
	ai_network_params ai_params =
					AI_NETWORK_PARAMS_INIT(
							AI_SPEECH_COMMANDS_MODEL_DATA_WEIGHTS(ai_speech_commands_model_data_weights_get()),
							AI_SPEECH_COMMANDS_MODEL_DATA_ACTIVATIONS(activations)
					);

	/* Set wrapper structs pointers to the data buffers */
	ai_input[0].n_batches = 1;
	ai_input[0].data = AI_HANDLE_PTR(in_data);
	ai_output[0].n_batches = 1;
	ai_output[0].data = AI_HANDLE_PTR(out_data);

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* Initialize LEDs */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	preprocessing_init();

	execution_time_init();

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* Initialize button */
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

	/* Create an instance of the neural network */
	ai_err = ai_speech_commands_model_create(&speech_commands_model,
	AI_SPEECH_COMMANDS_MODEL_DATA_CONFIG);
	if (ai_err.type != AI_ERROR_NONE) {
		usart_buffer_length = sprintf(usart_buffer,
				"Error: could not create NN instance\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer, usart_buffer_length,
				100);
		while (1)
			;
	}

	/* Initialize the neural network */
	if (!ai_speech_commands_model_init(speech_commands_model, &ai_params)) {
		usart_buffer_length = sprintf(usart_buffer,
				"Error: could not initialize NN\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer, usart_buffer_length,
				100);
		while (1)
			;
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		stop_mode();

		execution_time_start(0);
		/* Acquire audio signal and transform it to PCM data */
		audio_record();
		execution_time_stop(0);

		execution_time_start(1);
		/* Preprocess audio signal to get the MFCCs */
		preprocess_audio((int16_t*) &pcm_buffer[0], (ai_float*) &in_data[0],
		PCM_BUFFER_SIZE);
		execution_time_stop(1);

		execution_time_start(2);
		/* Perform inference */
		nbatch = ai_speech_commands_model_run(speech_commands_model,
				&ai_input[0], &ai_output[0]);
		execution_time_stop(2);


		if (nbatch != 1) {
			usart_buffer_length = sprintf(usart_buffer,
					"Error: could not run inference\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
					usart_buffer_length, 100);
		} else {
			/* Get the predicted word */
			uint8_t idx = argmax(out_data, AI_SPEECH_COMMANDS_MODEL_OUT_1_SIZE);
			char *word = get_word(idx);

			print_words = 1;

			recognize_commands(word);

			if (display_words_enabled) {
				/* Print words for commands different from `ON`, `VISUAL` and `STOP` */
				if (print_words) {
					/* Print the neural network output */
					usart_buffer_length = sprintf(usart_buffer, "%s\r\n", word);
					HAL_UART_Transmit(&huart2, (uint8_t*) usart_buffer,
							usart_buffer_length, 100);
				}
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

/**
 * @brief Initialize the data structures to preprocess the audio signal.
 *
 * @param  None
 *
 * @retval None
 */
void preprocessing_init(void) {
	/* Init window function */
	if (Window_Init(window_func_buffer, FRAME_LEN, WINDOW_HANN) != 0) {
		while (1)
			;
	}

	/* Init RFFT */
	arm_rfft_fast_init_f32(&rfft, FFT_LEN);

	/* Init mel filterbank */
	mel_filter.pStartIndices = mel_filter_start_indices;
	mel_filter.pStopIndices = mel_filter_stop_indices;
	mel_filter.pCoefficients = mel_filter_coefs;
	mel_filter.NumMels = NUM_MELS;
	mel_filter.FFTLen = FFT_LEN;
	mel_filter.SampRate = SAMPLE_RATE;
	mel_filter.FMin = 0.0;
	mel_filter.FMax = mel_filter.SampRate / 2.0;
	mel_filter.Formula = MEL_SLANEY;
	mel_filter.Normalize = 1;
	mel_filter.Mel2F = 1;
	MelFilterbank_Init(&mel_filter);
	if (mel_filter.CoefficientsLength != NUM_MEL_COEFS) {
		while (1)
			;
	}

	/* Init DCT operation */
	dct.NumFilters = NUM_MFCC;
	dct.NumInputs = NUM_MELS;
	dct.Type = DCT_TYPE_II_ORTHO;
	dct.RemoveDCTZero = 0;
	dct.pDCTCoefs = dct_coefs_buffer;
	if (DCT_Init(&dct) != 0) {
		while (1)
			;
	}

	/* Init Spectrogram */
	spectrogram.pRfft = &rfft;
	spectrogram.Type = SPECTRUM_TYPE_POWER;
	spectrogram.pWindow = window_func_buffer;
	spectrogram.SampRate = SAMPLE_RATE;
	spectrogram.FrameLen = FRAME_LEN;
	spectrogram.FFTLen = FFT_LEN;
	spectrogram.pScratch = spectrogram_scratch_buffer;

	/* Init MelSpectrogram */
	mel_spectrogram.SpectrogramConf = &spectrogram;
	mel_spectrogram.MelFilter = &mel_filter;

	/* Init LogMelSpectrogram */
	log_mel_spectrogram.MelSpectrogramConf = &mel_spectrogram;
	log_mel_spectrogram.LogFormula = LOGMELSPECTROGRAM_SCALE_DB;
	log_mel_spectrogram.Ref = 1.0;
	log_mel_spectrogram.TopdB = HUGE_VALF;

	/* Init MFCC */
	mfcc.LogMelConf = &log_mel_spectrogram;
	mfcc.pDCT = &dct;
	mfcc.NumMfccCoefs = NUM_MFCC;
	mfcc.pScratch = mfcc_scratch_buffer;
}

/**
 * @brief Put the MCU into WFI STOP MODE.
 *   This function suspends all the peripherals and the USART, except the GPIO 
 *   ones.
 *
 * @param  None
 *
 * @retval None
 */
void stop_mode(void) {
	HAL_UART_DeInit(&huart2);

	/* Suspend Tick increment to prevent wakeup by Systick interrupt, 
	 * otherwise the Systick interrupt will wake up the device within 
	 * 1ms (HAL time base)
	 */
	HAL_SuspendTick();

	/* Request to enter STOP mode */
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

	/* Resume Tick interrupt if disabled prior to sleep mode entry*/
	HAL_ResumeTick();

	/* Reinitialize UART2 */
	MX_USART2_UART_Init();
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
