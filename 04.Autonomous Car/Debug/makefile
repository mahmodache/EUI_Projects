################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./APP/tasks.obj" \
"./GeneralFunctions/Delay.obj" \
"./HAL/Button/Button.obj" \
"./HAL/LCD/LCD.obj" \
"./HAL/LDR/LDR.obj" \
"./HAL/Motors/Motor.obj" \
"./HAL/Temperature/Temperature.obj" \
"./HAL/Ultrasonic/Ultrasonic.obj" \
"./MCAL/ADC/ADC.obj" \
"./MCAL/GPIO/GPIO.obj" \
"./MCAL/GPTM/GPTM.obj" \
"./MCAL/PWM/PWM.obj" \
"./MCAL/SysTick/SysTick.obj" \
"./OS/scheduler.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include APP/subdir_vars.mk
-include GeneralFunctions/subdir_vars.mk
-include HAL/Button/subdir_vars.mk
-include HAL/LCD/subdir_vars.mk
-include HAL/LDR/subdir_vars.mk
-include HAL/Motors/subdir_vars.mk
-include HAL/Temperature/subdir_vars.mk
-include HAL/Ultrasonic/subdir_vars.mk
-include MCAL/ADC/subdir_vars.mk
-include MCAL/GPIO/subdir_vars.mk
-include MCAL/GPTM/subdir_vars.mk
-include MCAL/PWM/subdir_vars.mk
-include MCAL/SysTick/subdir_vars.mk
-include OS/subdir_vars.mk
-include subdir_rules.mk
-include APP/subdir_rules.mk
-include GeneralFunctions/subdir_rules.mk
-include HAL/Button/subdir_rules.mk
-include HAL/LCD/subdir_rules.mk
-include HAL/LDR/subdir_rules.mk
-include HAL/Motors/subdir_rules.mk
-include HAL/Temperature/subdir_rules.mk
-include HAL/Ultrasonic/subdir_rules.mk
-include MCAL/ADC/subdir_rules.mk
-include MCAL/GPIO/subdir_rules.mk
-include MCAL/GPTM/subdir_rules.mk
-include MCAL/PWM/subdir_rules.mk
-include MCAL/SysTick/subdir_rules.mk
-include OS/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Mega_Project.out \

EXE_OUTPUTS__QUOTED += \
"Mega_Project.out" \

BIN_OUTPUTS += \
Mega_Project.hex \

BIN_OUTPUTS__QUOTED += \
"Mega_Project.hex" \


# All Target
all: Mega_Project.out

# Tool invocations
Mega_Project.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --define=ccs="ccs" --define=PART_TM4C123GH6PM --c99 --gcc --abi=eabi --check_misra="all,-19.4" -z -m"app_TM4C123GH6PM_ccs.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --reread_libs --warn_sections --rom_model -o "Mega_Project.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Mega_Project.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armhex"  -o "Mega_Project.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "APP\tasks.obj" "GeneralFunctions\Delay.obj" "HAL\Button\Button.obj" "HAL\LCD\LCD.obj" "HAL\LDR\LDR.obj" "HAL\Motors\Motor.obj" "HAL\Temperature\Temperature.obj" "HAL\Ultrasonic\Ultrasonic.obj" "MCAL\ADC\ADC.obj" "MCAL\GPIO\GPIO.obj" "MCAL\GPTM\GPTM.obj" "MCAL\PWM\PWM.obj" "MCAL\SysTick\SysTick.obj" "OS\scheduler.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "APP\tasks.d" "GeneralFunctions\Delay.d" "HAL\Button\Button.d" "HAL\LCD\LCD.d" "HAL\LDR\LDR.d" "HAL\Motors\Motor.d" "HAL\Temperature\Temperature.d" "HAL\Ultrasonic\Ultrasonic.d" "MCAL\ADC\ADC.d" "MCAL\GPIO\GPIO.d" "MCAL\GPTM\GPTM.d" "MCAL\PWM\PWM.d" "MCAL\SysTick\SysTick.d" "OS\scheduler.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

