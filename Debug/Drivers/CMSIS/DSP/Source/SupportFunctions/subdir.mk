################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/SupportFunctions/SupportFunctions.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/SupportFunctionsF16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_barycenter_f16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_barycenter_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_f16_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_f16_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_f16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_f16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_sort_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_sort_init_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/SupportFunctions/SupportFunctions.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/SupportFunctionsF16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_barycenter_f16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_barycenter_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_f16_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_f16_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_f16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_f16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_sort_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_sort_init_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/SupportFunctions/SupportFunctions.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/SupportFunctionsF16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_barycenter_f16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_barycenter_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_bitonic_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_bubble_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_f16_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_f16_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_f16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_heap_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_insertion_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_merge_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_merge_sort_init_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_f16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_quick_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_selection_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_sort_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_sort_init_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_weighted_sum_f16.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_weighted_sum_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/SupportFunctions/%.o: ../Drivers/CMSIS/DSP/Source/SupportFunctions/%.c Drivers/CMSIS/DSP/Source/SupportFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I"/home/federica/Scrivania/Uni/PROS/Progetto/SpeechRecognitionAndTraduction/Drivers/CMSIS/DSP/Include" -I"/home/federica/Scrivania/Uni/PROS/Progetto/SpeechRecognitionAndTraduction/Drivers/STM32_AI_AudioPreprocessing_Library/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

