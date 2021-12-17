################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include X-CUBE-AI/App/subdir.mk
-include PDM2PCM/App/subdir.mk
-include Drivers/STM32_AI_AudioPreprocessing_Library/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/DSP/Source/TransformFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/SupportFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/StatisticsFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/SVMFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/QuaternionMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/MatrixFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/InterpolationFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/FilteringFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/FastMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/DistanceFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/ControllerFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/ComplexMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/CommonTables/subdir.mk
-include Drivers/CMSIS/DSP/Source/BayesFunctions/subdir.mk
-include Drivers/CMSIS/DSP/Source/BasicMathFunctions/subdir.mk
-include Drivers/BSP/STM32F4-Discovery/subdir.mk
-include Drivers/BSP/Components/lis3dsh/subdir.mk
-include Drivers/BSP/Components/lis302dl/subdir.mk
-include Drivers/BSP/Components/cs43l22/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := stm32-speech-recognition-and-traduction
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
stm32-speech-recognition-and-traduction.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
stm32-speech-recognition-and-traduction.list \

OBJCOPY_BIN += \
stm32-speech-recognition-and-traduction.bin \


# All Target
all: main-build

# Main-build Target
main-build: stm32-speech-recognition-and-traduction.elf secondary-outputs

# Tool invocations
stm32-speech-recognition-and-traduction.elf: $(OBJS) $(USER_OBJS) /home/federica/Scrivania/Uni/PROS/Progetto/SpeechRecognitionAndTraduction/STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "stm32-speech-recognition-and-traduction.elf" @"objects.list" $(USER_OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group -mcpu=cortex-m4 -T"/home/federica/Scrivania/Uni/PROS/Progetto/SpeechRecognitionAndTraduction/STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="stm32-speech-recognition-and-traduction.map" -Wl,--gc-sections -static -L../Middlewares/ST/STM32_Audio/Addons/PDM/Lib -L../Middlewares/ST/AI/Lib --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

stm32-speech-recognition-and-traduction.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "stm32-speech-recognition-and-traduction.list"
	@echo 'Finished building: $@'
	@echo ' '

stm32-speech-recognition-and-traduction.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "stm32-speech-recognition-and-traduction.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SIZE_OUTPUT)$(OBJDUMP_LIST)$(EXECUTABLES)$(OBJS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(OBJCOPY_BIN) stm32-speech-recognition-and-traduction.elf
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
