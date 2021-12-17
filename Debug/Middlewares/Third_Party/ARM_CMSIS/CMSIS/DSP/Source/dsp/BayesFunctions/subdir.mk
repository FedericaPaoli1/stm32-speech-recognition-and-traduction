################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/BayesFunctions.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/BayesFunctionsF16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.c \
../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/BayesFunctions.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/BayesFunctionsF16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/BayesFunctions.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/BayesFunctionsF16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.d \
./Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/%.o: ../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Source/dsp/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

