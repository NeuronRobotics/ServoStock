INCLUDES	    = -I../NR-Clib/include/ -I./include/ -I ../common/include -I ../NR-Clib/include/arch/avr -I/usr/lib/avr/include/ 

DEVICEA         = atmega644p
CPU_SPD       	= 18432000UL
LOW_FUSE     	= 0xce
HIGH_FUSE    	= 0xd9
EXT_FUSE      	= 0xff
GCCA            = avr-gcc
CCA             = $(GCCA) -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=$(DEVICEA) -DF_CPU=$(CPU_SPD) $(INCLUDES) -c
CCA324          = $(GCCA) -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=atmega324p -DF_CPU=$(CPU_SPD) $(INCLUDES) -c

LINK324p 		= $(GCCA)  -L ../../../NR-Clib/lib/AVR/atmega324p/ 

LINK 			= $(GCCA)  -L ../../../NR-Clib/lib/AVR/$(DEVICEA)/ 
OBJ				= Main.o DyIOMain.o ChannelConfig.o PinFunctions.o Debug_DyIO.o ChannelMode.o ChannelValues.o Pin_State.o ADC.o DCMotorDriver.o EEPROM.o IO.o PWM.o Servo.o UARTPassThrough.o CoOpCallbacks.o Push.o InitilizationCallbacks.o PacketEventCallbackss.o
DIRS:
	mkdir -p output/644p
	mkdir -p output/324p
	mkdir -p output/wpi
	mkdir -p output/dyiolib
	mkdir -p output/debug
	cp scripts/BuildLib.sh output

all:DIRS release legacy
	echo ok
extra:DIRS release legacy wpi dyiolib
	echo ok
release:	

	$(CCA) -c ../common/src/dyio/PinFunctions.c 	-o output/644p/PinFunctions.o
	$(CCA) -c ../common/src/main/Debug_DyIO.c 		-o output/644p/Debug_DyIO.o
	$(CCA) -c src/Main.c 					-o output/644p/Main.o
	$(CCA) -c src/DyIOMain.c 				-o output/644p/DyIOMain.o
	
	$(CCA) -c src/DyIO/ChannelConfig.c 		-o output/644p/ChannelConfig.o
	$(CCA) -c src/DyIO/ChannelMode.c 		-o output/644p/ChannelMode.o
	$(CCA) -c src/DyIO/ChannelValues.c 		-o output/644p/ChannelValues.o
	$(CCA) -c src/DyIO/Pin_State.c 			-o output/644p/Pin_State.o
	
	
	$(CCA) -c src/Driver/ADC.c 				-o output/644p/ADC.o
	$(CCA) -c src/Driver/DCMotorDriver.c 			-o output/644p/DCMotorDriver.o
	$(CCA) -c src/Driver/EEPROM.c			-o output/644p/EEPROM.o
	$(CCA) -c src/Driver/IO.c 			-o output/644p/IO.o
	$(CCA) -c src/Driver/PWM.c 			-o output/644p/PWM.o
	$(CCA) -c src/Driver/Servo.c 			-o output/644p/Servo.o
	$(CCA) -c src/Driver/UARTPassThrough.c 	-o output/644p/UARTPassThrough.o
	
	
	$(CCA) -c src/BowlerCallbacks/CoOpCallbacks.c 			-o output/644p/CoOpCallbacks.o
	$(CCA) -c src/BowlerCallbacks/Push.c 					-o output/644p/Push.o
	$(CCA) -c src/BowlerCallbacks/InitilizationCallbacks.c -o output/644p/InitilizationCallbacks.o
	$(CCA) -c src/BowlerCallbacks/PacketEventCallbacks.c 	-o output/644p/PacketEventCallbackss.o
	
	cd output/644p/; $(LINK)  -mmcu=$(DEVICEA) $(OBJ) -lNRLIB -o output.elf
	cd output/644p/; avr-objcopy -R .eeprom -O ihex output.elf  "output.hex"
	#cd output/644p/; avr-size --format=avr --mcu=$(DEVICEA) output.elf
	cp output/644p/* output/debug/
	cd output/644p/; rm *.o
	
	cd output/debug/; $(LINK) -mmcu=$(DEVICEA)  $(OBJ) -lNRLIB_debug  -o output.elf
	cd output/debug/; avr-objcopy -R .eeprom -O ihex output.elf  "output.hex"
	#cd output/debug/;  avr-size --format=avr --mcu=$(DEVICEA) output.elf
	cd output/debug/; rm *.o
legacy:	
	$(CCA324) -c ../common/src/dyio/PinFunctions.c 		-o output/324p/PinFunctions.o
	$(CCA324) -c ../common/src/main/Debug_DyIO.c 		-o output/324p/Debug_DyIO.o
	$(CCA324) -c src/Main.c 					-o output/324p/Main.o
	$(CCA324) -c src/DyIOMain.c 				-o output/324p/DyIOMain.o
	
	$(CCA324) -c src/DyIO/ChannelConfig.c 		-o output/324p/ChannelConfig.o
	$(CCA324) -c src/DyIO/ChannelMode.c 		-o output/324p/ChannelMode.o
	$(CCA324) -c src/DyIO/ChannelValues.c 		-o output/324p/ChannelValues.o
	$(CCA324) -c src/DyIO/Pin_State.c 			-o output/324p/Pin_State.o
	
	
	$(CCA324) -c src/Driver/ADC.c 				-o output/324p/ADC.o
	$(CCA324) -c src/Driver/DCMotorDriver.c 			-o output/324p/DCMotorDriver.o
	$(CCA324) -c src/Driver/EEPROM.c			-o output/324p/EEPROM.o
	$(CCA324) -c src/Driver/IO.c 			-o output/324p/IO.o
	$(CCA324) -c src/Driver/PWM.c 			-o output/324p/PWM.o
	$(CCA324) -c src/Driver/Servo.c 			-o output/324p/Servo.o
	$(CCA324) -c src/Driver/UARTPassThrough.c 	-o output/324p/UARTPassThrough.o
	
	
	$(CCA324) -c src/BowlerCallbacks/CoOpCallbacks.c 			-o output/324p/CoOpCallbacks.o
	$(CCA324) -c src/BowlerCallbacks/Push.c 					-o output/324p/Push.o
	$(CCA324) -c src/BowlerCallbacks/InitilizationCallbacks.c -o output/324p/InitilizationCallbacks.o
	$(CCA324) -c src/BowlerCallbacks/PacketEventCallbacks.c 	-o output/324p/PacketEventCallbackss.o
	
	cd output/324p/; $(LINK324p)  -mmcu=atmega324p $(OBJ) -lNRLIB  -o output.elf
	cd output/324p/; avr-objcopy -R .eeprom -O ihex output.elf  "output.hex"
	#cd output/324p/; avr-size --format=avr --mcu=atmega324p output.elf
	cd output/324p/; rm *.o
wpi:
	$(CCA) -DWPIRBE -c ../common/src/dyio/PinFunctions.c 	-o output/wpi/PinFunctions.o
	$(CCA) -DWPIRBE -c ../common/src/main/Debug_DyIO.c 		-o output/wpi/Debug_DyIO.o	
	$(CCA) -DWPIRBE -c src/Main.c 					-o output/wpi/Main.o
	$(CCA) -DWPIRBE -c src/DyIOMain.c 				-o output/wpi/DyIOMain.o
	
	$(CCA) -DWPIRBE -c src/DyIO/ChannelConfig.c 		-o output/wpi/ChannelConfig.o
	$(CCA) -DWPIRBE -c src/DyIO/ChannelMode.c 		-o output/wpi/ChannelMode.o
	$(CCA) -DWPIRBE -c src/DyIO/ChannelValues.c 		-o output/wpi/ChannelValues.o
	$(CCA) -DWPIRBE -c src/DyIO/Pin_State.c 			-o output/wpi/Pin_State.o
	
	
	$(CCA) -DWPIRBE -c src/Driver/ADC.c 				-o output/wpi/ADC.o
	$(CCA) -DWPIRBE -c src/Driver/DCMotorDriver.c 			-o output/wpi/DCMotorDriver.o
	$(CCA) -DWPIRBE -c src/Driver/EEPROM.c			-o output/wpi/EEPROM.o
	$(CCA) -DWPIRBE -c src/Driver/IO.c 			-o output/wpi/IO.o
	$(CCA) -DWPIRBE -c src/Driver/PWM.c 			-o output/wpi/PWM.o
	$(CCA) -DWPIRBE -c src/Driver/Servo.c 			-o output/wpi/Servo.o
	$(CCA) -DWPIRBE -c src/Driver/UARTPassThrough.c 	-o output/wpi/UARTPassThrough.o
	
	
	$(CCA) -DWPIRBE -c src/BowlerCallbacks/CoOpCallbacks.c 			-o output/wpi/CoOpCallbacks.o
	$(CCA) -DWPIRBE -c src/BowlerCallbacks/Push.c 					-o output/wpi/Push.o
	$(CCA) -DWPIRBE -c src/BowlerCallbacks/InitilizationCallbacks.c -o output/wpi/InitilizationCallbacks.o
	$(CCA) -DWPIRBE -c src/BowlerCallbacks/PacketEventCallbacks.c 	-o output/wpi/PacketEventCallbackss.o
	
	$(CCA) -DWPIRBE -c src/Driver/SPISlave.c 	-o output/wpi/SPISlave.o
	
	cd output/wpi/; $(LINK)  -mmcu=$(DEVICEA) $(OBJ) SPISlave.o -lNRLIB  -o output.elf
	cd output/wpi/; avr-objcopy -R .eeprom -O ihex output.elf  "output.hex"
	#cd output/wpi/; avr-size --format=avr --mcu=$(DEVICEA) output.elf	
	cd output/wpi/; rm *.o
dyiolib:	
	$(CCA) -DUSE_AS_LIBRARY -c ../common/src/dyio/PinFunctions.c 	-o output/dyiolib/PinFunctions.o
	$(CCA) -DUSE_AS_LIBRARY -c ../common/src/main/Debug_DyIO.c 		-o output/dyiolib/Debug_DyIO.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Main.c 					-o output/dyiolib/Main.o
	$(CCA) -DUSE_AS_LIBRARY -c src/DyIOMain.c 				-o output/dyiolib/DyIOMain.o
	
	$(CCA) -DUSE_AS_LIBRARY -c src/DyIO/ChannelConfig.c 		-o output/dyiolib/ChannelConfig.o
	$(CCA) -DUSE_AS_LIBRARY -c src/DyIO/ChannelMode.c 		-o output/dyiolib/ChannelMode.o
	$(CCA) -DUSE_AS_LIBRARY -c src/DyIO/ChannelValues.c 		-o output/dyiolib/ChannelValues.o
	$(CCA) -DUSE_AS_LIBRARY -c src/DyIO/Pin_State.c 			-o output/dyiolib/Pin_State.o
	
	
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/ADC.c 				-o output/dyiolib/ADC.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/DCMotorDriver.c 			-o output/dyiolib/DCMotorDriver.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/EEPROM.c			-o output/dyiolib/EEPROM.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/IO.c 			-o output/dyiolib/IO.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/PWM.c 			-o output/dyiolib/PWM.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/Servo.c 			-o output/dyiolib/Servo.o
	$(CCA) -DUSE_AS_LIBRARY -c src/Driver/UARTPassThrough.c 	-o output/dyiolib/UARTPassThrough.o
	
	
	$(CCA) -DUSE_AS_LIBRARY -c src/BowlerCallbacks/CoOpCallbacks.c 			-o output/dyiolib/CoOpCallbacks.o
	$(CCA) -DUSE_AS_LIBRARY -c src/BowlerCallbacks/Push.c 					-o output/dyiolib/Push.o
	$(CCA) -DUSE_AS_LIBRARY -c src/BowlerCallbacks/InitilizationCallbacks.c -o output/dyiolib/InitilizationCallbacks.o
	$(CCA) -DUSE_AS_LIBRARY -c src/BowlerCallbacks/PacketEventCallbacks.c 	-o output/dyiolib/PacketEventCallbackss.o
	
	cd output/; sh BuildLib.sh
	cp output/*.tar scripts/