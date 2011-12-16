INCLUDES	    = -I../NR-Clib/include/ -I./include/ -I ../common/include -I ../NR-Clib/include/arch/pic32

-include ../NR-Clib/toolchain/pic32/toolchain.mk

DEVICEP 		= 32MX440F128H
DEFINES			= -DUSE_VELOCITY
CCP     		= $(GCCP) -mprocessor=$(DEVICEP) $(INCLUDES) $(DEFINES)
LINK 			= $(GCCP) -mprocessor=$(DEVICEP) -L ../../../NR-Clib/lib/PIC32/$(DEVICEP)/ -L ../../../common/Release/pic   -Wl,--script="elf32pic32mx.ld" 
OBJ				= Main.o DyIOMain.o CartesianController.o UartDMARx.o Debug_DyIO.o PinFunctions.o ChannelConfig.o ChannelMode.o ChannelValues.o SPI.o PID.o PacketEventCallbackss.o InitializationCallbacks.o UpstreamPackets.o DownStreamPackets.o CoOpCallbacks.o AsyncManager.o Switches.o Pin_State.o SerialPassThrough.o PPMReader.o ADC.o  AVRInterface.o CoProcCom.o Counter.o EEPROMMannager.o
DIRS:
	rm -rf output
	mkdir -p output/release
	mkdir -p output/debug

all:DIRS release
	echo ok
release:	

	$(CCP) -c src/Drivers/dma/UartDMARx.c 				-o output/release/UartDMARx.o
	$(CCP) -c ../common/src/dyio/PinFunctions.c -o output/release/PinFunctions.o
	$(CCP) -c ../common/src/main/Debug_DyIO.c 	-o output/release/Debug_DyIO.o

	$(CCP) -c src/Application/PID.c 		-o output/release/PID.o	
	$(CCP) -c src/Main.c 					-o output/release/Main.o
	$(CCP) -c src/DyIOMain.c 				-o output/release/DyIOMain.o
	
	$(CCP) -c src/DyIO/ChannelConfig.c 		-o output/release/ChannelConfig.o
	$(CCP) -c src/DyIO/ChannelMode.c 		-o output/release/ChannelMode.o
	$(CCP) -c src/DyIO/ChannelValues.c 		-o output/release/ChannelValues.o
	$(CCP) -c src/DyIO/Pin_State.c 			-o output/release/Pin_State.o
	
	
	$(CCP) -c src/Drivers/ADC.c 				-o output/release/ADC.o
	$(CCP) -c src/Drivers/AVRInterface.c 		-o output/release/AVRInterface.o
	$(CCP) -c src/Drivers/CoProcCom.c 			-o output/release/CoProcCom.o
	$(CCP) -c src/Drivers/Counter.c 			-o output/release/Counter.o
	$(CCP) -c src/Drivers/EEPROMMannager.c		-o output/release/EEPROMMannager.o
	$(CCP) -c src/Drivers/PPMReader.c 			-o output/release/PPMReader.o
	$(CCP) -c src/Drivers/SerialPassThrough.c 	-o output/release/SerialPassThrough.o
	$(CCP) -c src/Drivers/SPI.c 				-o output/release/SPI.o
	$(CCP) -c src/Drivers/Switches.c 			-o output/release/Switches.o
	
	$(CCP) -c src/BowlerCallbacks/AsyncManager.c 			-o output/release/AsyncManager.o
	$(CCP) -c src/BowlerCallbacks/CoOpCallbacks.c 			-o output/release/CoOpCallbacks.o
	$(CCP) -c src/BowlerCallbacks/DownStreamPackets.c 		-o output/release/DownStreamPackets.o
	$(CCP) -c src/BowlerCallbacks/UpstreamPackets.c 		-o output/release/UpstreamPackets.o
	$(CCP) -c src/BowlerCallbacks/InitializationCallbacks.c -o output/release/InitializationCallbacks.o
	$(CCP) -c src/BowlerCallbacks/PacketEventCallbacks.c 	-o output/release/PacketEventCallbackss.o
	
	
	$(CCP) -c src/Application/CartesianController.c 	-o output/release/CartesianController.o
	
	
	cp *.ld output/release/
	cd output/release/; $(LINK) $(OBJ) -lNRLIB  -o output.elf
	cd output/release/; $(BIN2HEX) -v -a  output.elf
	
	cp output/release/* output/debug/
	
	cd output/debug/; $(LINK)   $(OBJ) -lNRLIB_debug  -o output.elf
	cd output/debug/; $(BIN2HEX) -v -a  output.elf
	
	
	