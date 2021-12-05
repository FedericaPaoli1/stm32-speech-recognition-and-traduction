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
#include "commands.h"

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

enum leds_status {
	Off, Green, Blue, Red, Orange
};

//float pcm_buf[WIN_LENGTH];
uint16_t pdmRxBuf[128];
uint16_t MidBuffer[16];
uint8_t rxstate = 0;

uint16_t fifobuf[4096];
uint16_t fifo_w_ptr = 0;
uint16_t fifo_r_ptr = 0;
uint8_t fifo_read_enabled = 0;
uint8_t display_words_enabled = 0;
enum leds_status led_status = Off;
char b[50];

fft_complex_t pcm_data[4096];
double spectrum[WIN_LENGTH];
int bits = 8; // log2(HOP_LENGTH)

void FifoWrite(uint16_t data) {
	fifobuf[fifo_w_ptr] = data;
	fifo_w_ptr++;
	/*if (fifo_w_ptr >= 256) {
	 fifo_read_enabled = 1;
	 fifo_w_ptr = 0;
	 }*/
}

uint16_t FifoRead() {
	uint16_t val = fifobuf[fifo_r_ptr];
	fifo_r_ptr++;
	/*if (fifo_r_ptr >= 256) {
	 fifo_r_ptr = 0;
	 // slide buffer
	 for (int i = HOP_LENGTH; i < 256; i++) {
	 fifobuf[i - HOP_LENGTH] = fifobuf[i];
	 }
	 fifo_read_enabled = 0;
	 fifo_w_ptr = HOP_LENGTH;
	 }*/
	return val;
}

void debug(const char *c) {
	HAL_UART_Transmit(&huart2, (uint8_t*) c, strlen(c),
	HAL_MAX_DELAY);
}

// TODO cambiare puntatori a parole ONE, TWO, THREE, FOUR
void recognize_commands(const char *word) {
	// ONE
	if (strcmp(word, UP) == 0) {
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
	}
	// TWO
	else if (strcmp(word, RIGHT) == 0) {
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
	}
	// THREE
	else if (strcmp(word, LEFT) == 0) {
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
	}
	// FOUR
	else if (strcmp(word, DOWN) == 0) {
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
			// enable the display of the words
			display_words_enabled = 1;
		} else if (strcmp(word, OFF) == 0) {
			// disable the display of the words
			if (display_words_enabled)
				display_words_enabled = 0;
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

	char buf[50];
	int buf_len = 0;
	ai_error ai_err;
	ai_i32 nbatch;

	// Chunk of memory used to hold intermediate values for neural network
	AI_ALIGNED(4) ai_u8 activations[AI_SMALL_WORDS_MODEL_DATA_ACTIVATIONS_SIZE];
	//AI_ALIGNED(4): specify a minimum alignment measured in bytes

	// Buffers used to store input and output tensors
	AI_ALIGNED(4) ai_float in_data[AI_SMALL_WORDS_MODEL_IN_1_SIZE_BYTES];
	AI_ALIGNED(4) ai_float out_data[AI_SMALL_WORDS_MODEL_OUT_1_SIZE_BYTES];

	// Pointer to our model
	ai_handle small_words_model = AI_HANDLE_NULL;

	// Initialize wrapper structs that hold pointers to data and info about the
	// data (tensor height, width, channels)
	ai_buffer ai_input[AI_SMALL_WORDS_MODEL_IN_NUM] = AI_SMALL_WORDS_MODEL_IN;
	ai_buffer ai_output[AI_SMALL_WORDS_MODEL_OUT_NUM] = AI_SMALL_WORDS_MODEL_OUT;

	// Set working memory and get weights/biases from model
	ai_network_params ai_params =
					AI_NETWORK_PARAMS_INIT(AI_SMALL_WORDS_MODEL_DATA_WEIGHTS(ai_small_words_model_data_weights_get()), AI_SMALL_WORDS_MODEL_DATA_ACTIVATIONS(activations));

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

	HAL_I2S_Receive_DMA(&hi2s2, &pdmRxBuf[0], 64);

	// Create instance of neural network
	ai_err = ai_small_words_model_create(&small_words_model,
	AI_SMALL_WORDS_MODEL_DATA_CONFIG);
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

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {

		float in_array[512] = { -462.5489807128906, -460.6819152832031,
				-335.66546630859375, -52.03413009643555, 42.36781692504883,
				37.663734436035156, -56.254520416259766, -145.94793701171875,
				-179.08938598632812, -200.5740509033203, -237.589111328125,
				-286.0892028808594, -326.72296142578125, -361.7548522949219,
				-383.8531494140625, -402.59613037109375, -414.57366943359375,
				-421.791259765625, -423.08502197265625, -412.6073303222656,
				-405.4219055175781, -409.1328125, -409.6954345703125,
				-411.6041564941406, -410.2247619628906, -416.58990478515625,
				-429.2041015625, -435.84271240234375, -437.8703308105469,
				-442.71246337890625, -441.8224792480469, -448.0345764160156,
				82.91480255126953, 82.21368408203125, 108.05314636230469,
				96.94743347167969, 97.26155090332031, 109.45526123046875,
				138.27711486816406, 166.1852569580078, 160.50558471679688,
				148.44912719726562, 137.7445068359375, 132.2306671142578,
				129.04910278320312, 118.98014831542969, 108.73556518554688,
				95.19557189941406, 88.06059265136719, 86.40806579589844,
				86.45936584472656, 95.56078338623047, 97.29298400878906,
				93.53260803222656, 92.76338958740234, 96.28926849365234,
				93.344482421875, 90.36163330078125, 87.16122436523438,
				85.33695983886719, 89.93179321289062, 89.18970489501953,
				89.3155746459961, 85.55142211914062, 30.046829223632812,
				26.3184814453125, -7.346662998199463, -45.74298858642578,
				-47.26594543457031, -46.71194839477539, -48.39898681640625,
				-60.257511138916016, -59.05059051513672, -53.9133415222168,
				-46.839542388916016, -27.13712501525879, -19.176342010498047,
				-18.218536376953125, -3.764845132827759, 7.901210308074951,
				7.353961944580078, 11.354618072509766, 13.134448051452637,
				20.55592918395996, 27.0792236328125, 31.78763198852539,
				33.7177734375, 35.570465087890625, 26.258438110351562,
				27.526966094970703, 26.300458908081055, 22.089542388916016,
				26.644136428833008, 32.46015930175781, 30.47498893737793,
				28.417091369628906, 9.614219665527344, 10.547652244567871,
				-18.823379516601562, -16.654281616210938, -16.442699432373047,
				-14.249542236328125, -8.728095054626465, -7.9880170822143555,
				-13.367971420288086, -14.82347583770752, -17.782161712646484,
				-19.205509185791016, -19.19045639038086, -22.104137420654297,
				-15.100624084472656, -6.221297264099121, 0.7040461897850037,
				9.542312622070312, 13.057371139526367, 8.50900650024414,
				8.793787956237793, 20.142677307128906, 26.394874572753906,
				24.382884979248047, 22.03366470336914, 25.051755905151367,
				19.17455291748047, 10.838985443115234, 12.889331817626953,
				11.988645553588867, 6.991077899932861, 9.415761947631836,
				18.507221221923828, 19.643592834472656, -38.577392578125,
				-52.982364654541016, -49.07319259643555, -45.276065826416016,
				-41.46149444580078, -37.94609069824219, -31.618980407714844,
				-29.70258331298828, -33.266239166259766, -35.24976348876953,
				-29.583635330200195, -16.418216705322266, -10.782724380493164,
				-1.7867164611816406, 10.988938331604004, 15.728893280029297,
				12.322757720947266, 9.129117965698242, 17.16074562072754,
				24.965618133544922, 27.92776870727539, 26.977882385253906,
				26.455425262451172, 26.0874080657959, 24.019569396972656,
				23.890399932861328, 23.383968353271484, 15.880614280700684,
				6.909854412078857, 11.539682388305664, 21.055652618408203,
				20.607433319091797, 2.23683500289917, 3.9207191467285156,
				-0.1609582006931305, -1.864985466003418, -1.7765960693359375,
				-4.2371344566345215, -1.0565688610076904, 0.1589498519897461,
				-9.351451873779297, -10.989921569824219, -5.327041149139404,
				6.043673515319824, 10.904842376708984, 21.9311466217041,
				25.476430892944336, 23.06573486328125, 19.541099548339844,
				25.929908752441406, 34.39350891113281, 39.044822692871094,
				33.91709899902344, 32.009185791015625, 33.35890197753906,
				32.06470489501953, 29.77276611328125, 34.560272216796875,
				29.60491943359375, 20.838645935058594, 23.023056030273438,
				34.502525329589844, 14.102472305297852, 12.090479850769043,
				36.4473876953125, 17.722476959228516, 10.196125984191895,
				4.419459342956543, 0.9029611349105835, 6.439078330993652,
				10.260845184326172, 8.577982902526855, 5.314340114593506,
				7.914997100830078, 6.986629486083984, 17.646953582763672,
				18.118122100830078, 19.80841827392578, 17.413902282714844,
				16.17621612548828, 15.59427261352539, 21.348968505859375,
				24.324031829833984, 24.139328002929688, 21.525100708007812,
				18.87215805053711, 22.100528717041016, 27.42927360534668,
				26.317081451416016, 20.247392654418945, 16.159908294677734,
				16.971416473388672, 18.746692657470703, 22.975452423095703,
				13.18320083618164, 12.601115226745605, 23.045654296875,
				15.892494201660156, 9.871513366699219, 2.017137289047241,
				-13.80759048461914, -19.568458557128906, -2.9037647247314453,
				-2.404064416885376, -1.4750094413757324, -0.4474823474884033,
				-2.2611353397369385, 5.410343647003174, 13.958454132080078,
				14.446758270263672, 10.881028175354004, 9.675851821899414,
				10.636332511901855, 11.72123908996582, 18.57193374633789,
				19.627517700195312, 19.11156463623047, 14.913145065307617,
				15.30527114868164, 13.954046249389648, 13.605215072631836,
				15.628097534179688, 13.629060745239258, 12.023391723632812,
				9.557926177978516, 8.680302619934082, 6.741803169250488,
				6.960604667663574, -5.628655433654785, -4.56618595123291,
				-6.20931339263916, -10.53839111328125, -15.168704986572266,
				-13.350996017456055, -5.313011169433594, -2.6690635681152344,
				-3.7586264610290527, -4.833095550537109, -8.104005813598633,
				-1.4196674823760986, 5.889117240905762, 8.872520446777344,
				5.349480628967285, 2.219979763031006, 4.772538185119629,
				0.6638578772544861, 0.4753528833389282, 4.80576753616333,
				3.859083652496338, 3.1909573078155518, 6.687399864196777,
				6.80944299697876, 5.650842666625977, 1.8245378732681274,
				-1.2384891510009766, 0.5372681021690369, 6.487669467926025,
				14.118612289428711, 4.927896499633789, 4.271984100341797,
				16.823741912841797, 11.711752891540527, 5.703359603881836,
				1.2544755935668945, -2.2822043895721436, -2.821866035461426,
				0.8284096717834473, -0.29201191663742065, -6.020557403564453,
				-10.39376449584961, -1.4388065338134766, 14.497523307800293,
				14.296854019165039, 10.089155197143555, 5.502203941345215,
				-0.732353925704956, 4.24931001663208, 6.342814922332764,
				7.129881381988525, 8.068368911743164, 12.270769119262695,
				9.389347076416016, 10.780929565429688, 6.948720932006836,
				3.4742672443389893, 3.8298704624176025, -0.759306788444519,
				1.9553661346435547, 12.331071853637695, 15.628568649291992,
				-3.7395999431610107, -3.1441898345947266, 0.22182631492614746,
				-8.557567596435547, -4.930193901062012, -0.947598934173584,
				6.2991228103637695, 7.109719753265381, 7.951298236846924,
				13.672903060913086, 12.516149520874023, 13.588525772094727,
				24.787429809570312, 29.45211410522461, 16.776817321777344,
				6.442817687988281, -1.1699646711349487, -2.7234621047973633,
				1.7530804872512817, 4.831542015075684, 0.6394906044006348,
				0.944627583026886, 5.648475646972656, -2.093780517578125,
				0.1592138409614563, 0.37179040908813477, -1.6915427446365356,
				-0.13104242086410522, 1.8831532001495361, 0.6233612298965454,
				1.8601351976394653, 2.4538917541503906, -7.053937911987305,
				-2.3930678367614746, -7.734020233154297, -8.369866371154785,
				-3.835352897644043, 1.6765135526657104, 15.019407272338867,
				31.66347312927246, 24.998878479003906, 18.619281768798828,
				9.105267524719238, 12.746309280395508, 23.91605567932129,
				23.141590118408203, 8.437118530273438, 4.704058647155762,
				9.391912460327148, 10.25253677368164, 7.815424919128418,
				9.629841804504395, 4.97843074798584, 1.5823383331298828,
				7.008219242095947, 10.844949722290039, 9.97147274017334,
				3.805095672607422, 7.046128749847412, 12.398605346679688,
				14.007491111755371, 13.889738082885742, 6.709373474121094,
				6.704802989959717, -3.4873571395874023, -3.125687837600708,
				-4.002378940582275, -17.2246150970459, -17.982934951782227,
				-19.03095245361328, -26.707489013671875, -35.91849136352539,
				-32.46690368652344, -29.592281341552734, -28.088428497314453,
				-27.788158416748047, -25.764404296875, -22.518415451049805,
				-15.309818267822266, -8.436908721923828, -3.289728879928589,
				1.337883710861206, -7.038370609283447, -12.452327728271484,
				-9.19017219543457, 0.8398922681808472, 3.253390312194824,
				4.549759864807129, 7.41970157623291, -0.7802560329437256,
				-5.590977191925049, -2.8022043704986572, 0.5788699984550476,
				5.21683406829834, 6.092034339904785, 1.0689810514450073,
				-2.122600555419922, -0.9182325601577759, -9.828079223632812,
				-13.219587326049805, -8.709213256835938, -6.677727699279785,
				-5.584166049957275, 3.199131727218628, -2.53658127784729,
				-5.553032875061035, -4.166958332061768, -3.5777699947357178,
				-9.429121017456055, -11.844480514526367, -3.6022403240203857,
				-0.08143922686576843, -1.251651406288147, -2.7030551433563232,
				-5.86240291595459, -9.299139022827148, -5.934937477111816,
				1.8310539722442627, 3.86841082572937, 0.5112693309783936,
				1.0151480436325073, 3.2822177410125732, 2.262596368789673,
				-5.37516975402832, -5.2385969161987305, -1.2456104755401611,
				0.5974754095077515, -3.228104591369629, 3.763141632080078,
				3.8391311168670654, -2.7556400299072266, -10.184757232666016,
				-9.532434463500977, -6.51884651184082, 4.006880760192871,
				14.660428047180176, 14.222269058227539, 9.672141075134277,
				7.440553665161133, 1.5014839172363281, 3.9082579612731934,
				0.7342394590377808, -1.6894469261169434, -7.501882553100586,
				-4.960712909698486, -4.618200778961182, -4.809879302978516,
				-1.4047398567199707, -0.7735379338264465, -5.0705084800720215,
				-6.238825798034668, -6.7629594802856445, -1.0999090671539307,
				5.0094146728515625, 8.884366035461426, 6.724293231964111,
				4.80702018737793, -0.44190073013305664, 2.4547674655914307,
				2.7916300296783447, 2.5629465579986572, 1.0499112606048584,
				4.451821804046631, -2.1450791358947754, -2.9035959243774414,
				-5.014453887939453, -12.873045921325684, -26.312274932861328,
				-24.148212432861328, -18.844989776611328, -8.825775146484375,
				-3.21583890914917, -0.5966141223907471, -4.873621940612793,
				-3.7183475494384766, -8.860721588134766, -8.512951850891113,
				-5.416776180267334, -4.745195388793945, 2.0160439014434814,
				6.304471015930176, 7.45665168762207, 4.826930046081543,
				4.869168281555176, 10.858297348022461, 8.825749397277832,
				7.653464317321777, 8.393640518188477, 9.717666625976562,
				4.587841033935547, -1.5723075866699219, -2.0356557369232178 };

// Fill input buffer (use test value)
		for (uint32_t i = 0; i < AI_SMALL_WORDS_MODEL_IN_1_SIZE; i++) {
			((ai_float*) in_data)[i] = (ai_float) in_array[i];
		}

// Perform inference
		nbatch = ai_small_words_model_run(small_words_model, &ai_input[0],
				&ai_output[0]);
		if (nbatch != 1) {
			buf_len = sprintf(buf, "Error: could not run inference\r\n");
			HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);
		}

		uint8_t idx = argmax(out_data, AI_SMALL_WORDS_MODEL_OUT_1_SIZE);

		char *word = get_word(idx);

		recognize_commands(word);

		if (display_words_enabled) {

			// Print output of neural network along with inference time (microseconds)
			buf_len = sprintf(buf, "%d %s\r\n", idx, word);
			HAL_UART_Transmit(&huart2, (uint8_t*) buf, buf_len, 100);

			// Wait before doing it again
			HAL_Delay(500);
		}

		if (rxstate == 1) {
			// Filter the input values and store the results in an intermediate buffer
			PDM_Filter(&pdmRxBuf[0], &MidBuffer[0], &PDM1_filter_handler);

			// The mid buffer has length 16 because the PDM is configured to produce 16 samples
			// of PCM each time it is called
			for (int i = 0; i < 16; i++) {
				fifobuf[fifo_w_ptr] = MidBuffer[i];
				fifo_w_ptr++;
			}

			// Reset rx state
			rxstate = 0;

		}

		if (rxstate == 2) {
			// Filter the input values and store the results in an intermediate buffer
			PDM_Filter(&pdmRxBuf[64], &MidBuffer[0], &PDM1_filter_handler);
			for (int i = 0; i < 16; i++) {
				fifobuf[fifo_w_ptr] = MidBuffer[i];
				fifo_w_ptr++;
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

		if (fifo_w_ptr == 4096) {
			//Stop the DMA
			//HAL_I2S_DMAPause(&hi2s2);

			// Send to UART or Store Data
			fifo_w_ptr = 0;

			/*// Read 1024 samples from the PCM buffer
			 for (int i = 0; i < 128; i++) {
			 // Cast the value to float
			 int32_t data = FifoRead();
			 //pcm_buf[i] = data;
			 pcm_data[i].r = data;
			 }*/

			/*for (int i = 0; i < 4096; i++) {
			 int l = sprintf(b, "%" PRIu16 "\r\n", fifobuf[i]);
			 HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
			 HAL_MAX_DELAY);
			 }*/

			/*
			 POST PROCESSING non serve dal momento che otteniamo alla fine degli interi

			 PCM_post_processing(pcm_buf);

			 for (int i = 0; i < 128; i++) {
			 pcm_data[i].r = pcm_buf[i];
			 }*/

			// make FFT results purely real
			/*for (int i = 0; i < WIN_LENGTH; i++) {
			 spectrum[i] = pcm_data[i].r;
			 }*/

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
			/*int numbins = 2;
			 for (int coeff = 0; coeff < numbins; coeff++) {
			 float mfcc_result = GetCoefficient(spectrum, 8000, numbins,
			 WIN_LENGTH, coeff);
			 int l = sprintf(b, "%f\r\n", mfcc_result);
			 HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
			 HAL_MAX_DELAY);
			 }
			 int l = sprintf(b, "-------------------------END\r\n");
			 HAL_UART_Transmit(&huart2, (uint8_t*) b, l,
			 HAL_MAX_DELAY);*/
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
	hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_32K;
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
