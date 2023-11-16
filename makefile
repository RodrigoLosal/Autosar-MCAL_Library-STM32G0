#---Set project name
TARGET = mcal

#---Files to compile
SRCS = main.c startup.c Nvic.c Port.c Port_Cfg.c Crc.c Dio.c Gpt.c Gpt_Cfg.c
SRCS += Can.c Can_Lcfg.c Can_Arch.c Pwm.c Pwm_Lcfg.c Pwm_Arch.c Spi.c Spi_Lcfg.c Spi_Arch.c Det.c Det_Lcfg.c
SRCS += Mcu.c Mcu_Lcfg.c Mcu_Arch.c Fls.c Fls_Lcfg.c Adc.c

#---Linker script
LINKER = linker.ld

#List of subdirectories for MCAL modules
MCAL_MODULES = Can Dio Fls Gpt Mcu Nvic Port Spi Pwm Adc

#directorios con archivos a compilar (.c y .s)
SRC_PATHS  = .
SRC_PATHS += $(addprefix autosar/mcal/,$(MCAL_MODULES))
SRC_PATHS += autosar/libs
SRC_PATHS += cfg
SRC_PATHS += autosar/Sys
#direcotrios con archivos .h
INC_PATHS  = .
INC_PATHS += autosar
INC_PATHS += autosar/libs
INC_PATHS += autosar/mcal
INC_PATHS += $(addprefix autosar/mcal/,$(MCAL_MODULES))
INC_PATHS += autosar/mcal/regs
INC_PATHS += cfg
INC_PATHS += autosar/Sys

#---Set toolchain
TOOLCHAIN = arm-none-eabi

#---Compilation options
CPU = -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft
CFLAGS  = -O0                        # Compile with Size Optimizations (O0, O1, O2, O3, Os)
CFLAGS += -g3                        # Debugging information level (g1, g2, g3)
CFLAGS += -ffunction-sections        # Create a separate function section
CFLAGS += -fdata-sections            # Create a separate data section
CFLAGS += -fno-builtin               # Don't recognize built-in functions that do not begin with ‘__builtin_’ as prefix
CFLAGS += -std=c99                   # Comply with C11
CFLAGS += -Wall                      # Be anal Enable All Warnings
CFLAGS += -pedantic                  # Be extra anal More ANSI Checks
CFLAGS += -Werror                    # Threat all warnings as errors
CFLAGS += -Wstrict-prototypes        # Warn if a function is declared or defined without specifying the argument types
CFLAGS += -fsigned-char              # char is treated as signed
CFLAGS += -fdiagnostics-color=always # color the output
CFLAGS += -fomit-frame-pointer       # Don't keep the frame pointer in a register for functions that don't need one
CFLAGS += -fverbose-asm              # Put extra commentary information in the generated assembly code
CFLAGS += -MMD -MP

#---Linker options
LFLAGS  = $(CPU)
#LFLAGS += -Wl,--gc-sections
LFLAGS += -nostdlib
LFLAGS += -Wl,-Map=Build/$(TARGET).map	# Generate map file

#Linter ccpcheck flags
LNFLAGS  = --inline-suppr       # comments to suppress lint warnings
LNFLAGS += --enable=warning,style # enable only warnings
LNFLAGS += --error-exitcode=1	# return error if any warnings
LNFLAGS += --quiet              # spit only useful information
LNFLAGS += --std=c11            # check against C11
LNFLAGS += --template=gcc       # display warning gcc style
LNFLAGS += --force              # evaluate all the #if sentences
LNFLAGS += --platform=unix32    # lint againt a unix32 platform, but we are using arm32
LNFLAGS += --cppcheck-build-dir=Build/checks

#---Build target
OBJS = $(SRCS:%.c=Build/obj/%.o)
DEPS = $(OBJS:%.o=%.d)
RSLST = $(SRCT:Test_%.c=Build/unity/results/test_%.txt)
FILES  = $(shell find ./ -type f ! -path '*/test/unity*' -name "*.[ch]")
VPATH = $(SRC_PATHS)
INCLS = $(addprefix -I ,$(INC_PATHS))

all : format lint build $(TARGET)

$(TARGET) : $(addprefix Build/, $(TARGET).elf)
	$(TOOLCHAIN)-objcopy -Oihex $< Build/$(TARGET).hex
	$(TOOLCHAIN)-objdump -S $< > Build/$(TARGET).lst
	$(TOOLCHAIN)-size --format=berkeley $<

Build/$(TARGET).elf : $(OBJS)
	$(TOOLCHAIN)-gcc $(LFLAGS) -T $(LINKER) -o $@ $^

Build/obj/%.o : %.c
	$(TOOLCHAIN)-gcc $(CPU) $(CFLAGS) $(INCLS) -c $< -o $@

.PHONY : build clean lint docs format test
#---remove binary files
clean :
	rm -r Build
#---Create output directory
build :
	@mkdir -p Build/obj
	@mkdir -p Build/unity
	@mkdir -p Build/unity/results
	@mkdir -p Build/unity/obj

flash :
	openocd -f board/st_nucleo_g0.cfg -c "program Build/$(TARGET).hex verify reset" -c shutdown

#---open a debug server conection------------------------------------------------------------------
open :
	openocd -f board/st_nucleo_g0.cfg
#	JLinkGDBServer -if SWD -device stm32g0b1re -nogui

#---launch a debug session, NOTE: is mandatory to previously open a debug server session-----------
debug :
	arm-none-eabi-gdb Build/$(TARGET).elf -iex "set auto-load safe-path /"

format :
	@clang-format -style=file -i --Werror $(FILES)

lint : format
	mkdir -p Build/checks
	cppcheck --addon=misra.json --suppressions-list=.msupress $(LNFLAGS) autosar

test : format build 
	ceedling clobber
	ceedling gcov:all utils:gcov
	firefox Build/ceedling/artifacts/gcov/GcovCoverageResults.html

docs : format
	mkdir -p Build/doxygen 
	mkdir -p Build/sphinx 
	mkdir -p Build/sphinx/_template 
	mkdir -p Build/sphinx/_static 
	mkdir -p Build/sphinx/_build
	doxygen .doxyfile
	firefox Build/doxygen/html/index.html
#	sphinx-build -b html Docs Build/sphinx/_build -c ./ -W
#	firefox Build/sphinx/_build/index.html
