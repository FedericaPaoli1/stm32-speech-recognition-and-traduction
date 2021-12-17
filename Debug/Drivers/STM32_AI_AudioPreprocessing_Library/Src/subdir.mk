################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.c \
../Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.c 

OBJS += \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.o \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.o 

C_DEPS += \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/common_tables.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/dct.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.d \
./Drivers/STM32_AI_AudioPreprocessing_Library/Src/window.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32_AI_AudioPreprocessing_Library/Src/%.o: ../Drivers/STM32_AI_AudioPreprocessing_Library/Src/%.c Drivers/STM32_AI_AudioPreprocessing_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I"/home/federica/Scrivania/Uni/PROS/Progetto/SpeechRecognitionAndTraduction/Drivers/CMSIS/DSP/Include" -I"/home/federica/Scrivania/Uni/PROS/Progetto/SpeechRecognitionAndTraduction/Drivers/STM32_AI_AudioPreprocessing_Library/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

