################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
wordclock_arduino.lss \

FLASH_IMAGE += \
wordclock_arduino.hex \

EEPROM_IMAGE += \
wordclock_arduino.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: wordclock_arduino.elf secondary-outputs

# Tool invocations
wordclock_arduino.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,wordclock_arduino.map -mmcu=atmega328p -o "wordclock_arduino.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

wordclock_arduino.lss: wordclock_arduino.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S wordclock_arduino.elf  >"wordclock_arduino.lss"
	@echo 'Finished building: $@'
	@echo ' '

wordclock_arduino.hex: wordclock_arduino.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex wordclock_arduino.elf  "wordclock_arduino.hex"
	@echo 'Finished building: $@'
	@echo ' '

wordclock_arduino.eep: wordclock_arduino.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex wordclock_arduino.elf  "wordclock_arduino.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: wordclock_arduino.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p wordclock_arduino.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: wordclock_arduino.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm328p -carduino -P/dev/ttyACM0 -V -Uflash:w:wordclock_arduino.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) wordclock_arduino.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
