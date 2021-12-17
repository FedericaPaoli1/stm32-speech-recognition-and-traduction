################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/TransformFunctions.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/TransformFunctionsF16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal2.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix8_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix8_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f64.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_f32.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_q31.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_q15.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_q31.c 

S_UPPER_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal2.S 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/TransformFunctions.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/TransformFunctionsF16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal2.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix8_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix8_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f64.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_f32.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_q31.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_q15.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_q31.o 

S_UPPER_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal2.d 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/TransformFunctions.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/TransformFunctionsF16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal2.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_bitreversal_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix2_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix4_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix8_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_cfft_radix8_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_dct4_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_mfcc_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_fast_init_f64.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_f32.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_init_q31.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_q15.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/arm_rfft_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/%.o: ../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/%.o: ../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/%.S Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/TransformFunctions/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

