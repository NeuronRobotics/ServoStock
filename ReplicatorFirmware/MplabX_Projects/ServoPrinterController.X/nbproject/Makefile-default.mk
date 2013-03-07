#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/711791526/SPIClient.o ${OBJECTDIR}/_ext/711791526/main.o ${OBJECTDIR}/_ext/711791526/Callbacks.o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ${OBJECTDIR}/_ext/711791526/AS5055.o ${OBJECTDIR}/_ext/711791526/PID.o ${OBJECTDIR}/_ext/711791526/Servo.o ${OBJECTDIR}/_ext/711791526/StepperSim.o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ${OBJECTDIR}/_ext/711791526/CartesianController.o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ${OBJECTDIR}/_ext/711791526/delta.o ${OBJECTDIR}/_ext/711791526/Calibration.o ${OBJECTDIR}/_ext/711791526/MotionTest.o ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ${OBJECTDIR}/_ext/1487882678/usb_device.o ${OBJECTDIR}/_ext/2118813141/Delay.o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ${OBJECTDIR}/_ext/2118813141/LED.o ${OBJECTDIR}/_ext/2118813141/Tick.o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ${OBJECTDIR}/_ext/2118813141/UART.o ${OBJECTDIR}/_ext/2118813141/ADC.o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ${OBJECTDIR}/_ext/1080174469/FIFO.o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ${OBJECTDIR}/_ext/1080174469/Debug.o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/711791526/SPIClient.o.d ${OBJECTDIR}/_ext/711791526/main.o.d ${OBJECTDIR}/_ext/711791526/Callbacks.o.d ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d ${OBJECTDIR}/_ext/711791526/AS5055.o.d ${OBJECTDIR}/_ext/711791526/PID.o.d ${OBJECTDIR}/_ext/711791526/Servo.o.d ${OBJECTDIR}/_ext/711791526/StepperSim.o.d ${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d ${OBJECTDIR}/_ext/711791526/CartesianController.o.d ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d ${OBJECTDIR}/_ext/711791526/delta.o.d ${OBJECTDIR}/_ext/711791526/Calibration.o.d ${OBJECTDIR}/_ext/711791526/MotionTest.o.d ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d ${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d ${OBJECTDIR}/_ext/1487882678/usb_callback.o.d ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d ${OBJECTDIR}/_ext/1487882678/usb_device.o.d ${OBJECTDIR}/_ext/2118813141/Delay.o.d ${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d ${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d ${OBJECTDIR}/_ext/2118813141/LED.o.d ${OBJECTDIR}/_ext/2118813141/Tick.o.d ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d ${OBJECTDIR}/_ext/2118813141/UART.o.d ${OBJECTDIR}/_ext/2118813141/ADC.o.d ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d ${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d ${OBJECTDIR}/_ext/1080174469/FIFO.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d ${OBJECTDIR}/_ext/1080174469/Debug.o.d ${OBJECTDIR}/_ext/1080174469/Scheduler.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/711791526/SPIClient.o ${OBJECTDIR}/_ext/711791526/main.o ${OBJECTDIR}/_ext/711791526/Callbacks.o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ${OBJECTDIR}/_ext/711791526/AS5055.o ${OBJECTDIR}/_ext/711791526/PID.o ${OBJECTDIR}/_ext/711791526/Servo.o ${OBJECTDIR}/_ext/711791526/StepperSim.o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ${OBJECTDIR}/_ext/711791526/CartesianController.o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ${OBJECTDIR}/_ext/711791526/delta.o ${OBJECTDIR}/_ext/711791526/Calibration.o ${OBJECTDIR}/_ext/711791526/MotionTest.o ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ${OBJECTDIR}/_ext/1487882678/usb_device.o ${OBJECTDIR}/_ext/2118813141/Delay.o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ${OBJECTDIR}/_ext/2118813141/LED.o ${OBJECTDIR}/_ext/2118813141/Tick.o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ${OBJECTDIR}/_ext/2118813141/UART.o ${OBJECTDIR}/_ext/2118813141/ADC.o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ${OBJECTDIR}/_ext/1080174469/FIFO.o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ${OBJECTDIR}/_ext/1080174469/Debug.o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/711791526/SPIClient.o: ../../src/Bowler/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/SPIClient.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" -o ${OBJECTDIR}/_ext/711791526/SPIClient.o ../../src/Bowler/SPIClient.c   
	
${OBJECTDIR}/_ext/711791526/main.o: ../../src/Bowler/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/main.o.d" -o ${OBJECTDIR}/_ext/711791526/main.o ../../src/Bowler/main.c   
	
${OBJECTDIR}/_ext/711791526/Callbacks.o: ../../src/Bowler/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Callbacks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" -o ${OBJECTDIR}/_ext/711791526/Callbacks.o ../../src/Bowler/Callbacks.c   
	
${OBJECTDIR}/_ext/711791526/UpstreamPackets.o: ../../src/Bowler/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ../../src/Bowler/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/711791526/AS5055.o: ../../src/Bowler/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/AS5055.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/AS5055.o.d" -o ${OBJECTDIR}/_ext/711791526/AS5055.o ../../src/Bowler/AS5055.c   
	
${OBJECTDIR}/_ext/711791526/PID.o: ../../src/Bowler/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/PID.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/PID.o.d" -o ${OBJECTDIR}/_ext/711791526/PID.o ../../src/Bowler/PID.c   
	
${OBJECTDIR}/_ext/711791526/Servo.o: ../../src/Bowler/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Servo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/Servo.o.d" -o ${OBJECTDIR}/_ext/711791526/Servo.o ../../src/Bowler/Servo.c   
	
${OBJECTDIR}/_ext/711791526/StepperSim.o: ../../src/Bowler/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/StepperSim.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" -o ${OBJECTDIR}/_ext/711791526/StepperSim.o ../../src/Bowler/StepperSim.c   
	
${OBJECTDIR}/_ext/711791526/ForgeHeater.o: ../../src/Bowler/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ../../src/Bowler/ForgeHeater.c   
	
${OBJECTDIR}/_ext/711791526/CartesianController.o: ../../src/Bowler/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/CartesianController.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" -o ${OBJECTDIR}/_ext/711791526/CartesianController.o ../../src/Bowler/CartesianController.c   
	
${OBJECTDIR}/_ext/711791526/DeltaKinematics.o: ../../src/Bowler/DeltaKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" -o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ../../src/Bowler/DeltaKinematics.c   
	
${OBJECTDIR}/_ext/711791526/delta.o: ../../src/Bowler/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/delta.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/delta.o.d" -o ${OBJECTDIR}/_ext/711791526/delta.o ../../src/Bowler/delta.c   
	
${OBJECTDIR}/_ext/711791526/Calibration.o: ../../src/Bowler/Calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Calibration.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/Calibration.o.d" -o ${OBJECTDIR}/_ext/711791526/Calibration.o ../../src/Bowler/Calibration.c   
	
${OBJECTDIR}/_ext/711791526/MotionTest.o: ../../src/Bowler/MotionTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/MotionTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" -o ${OBJECTDIR}/_ext/711791526/MotionTest.o ../../src/Bowler/MotionTest.c   
	
${OBJECTDIR}/_ext/1487882678/usb_descriptors.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/1487882678/usb_fifo.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c   
	
${OBJECTDIR}/_ext/1487882678/usb_callback.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_callback.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c   
	
${OBJECTDIR}/_ext/1487882678/usb_interrupt.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c   
	
${OBJECTDIR}/_ext/1487882678/usb_device.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_device.o ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c   
	
${OBJECTDIR}/_ext/2118813141/Delay.o: ../../../NR-Clib/Platform/src/pic32/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Delay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Delay.o.d" -o ${OBJECTDIR}/_ext/2118813141/Delay.o ../../../NR-Clib/Platform/src/pic32/Delay.c   
	
${OBJECTDIR}/_ext/2118813141/FlashStorage.o: ../../../NR-Clib/Platform/src/pic32/FlashStorage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" -o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ../../../NR-Clib/Platform/src/pic32/FlashStorage.c   
	
${OBJECTDIR}/_ext/2118813141/HAL_P32.o: ../../../NR-Clib/Platform/src/pic32/HAL_P32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" -o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ../../../NR-Clib/Platform/src/pic32/HAL_P32.c   
	
${OBJECTDIR}/_ext/2118813141/LED.o: ../../../NR-Clib/Platform/src/pic32/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/LED.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/LED.o.d" -o ${OBJECTDIR}/_ext/2118813141/LED.o ../../../NR-Clib/Platform/src/pic32/LED.c   
	
${OBJECTDIR}/_ext/2118813141/Tick.o: ../../../NR-Clib/Platform/src/pic32/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Tick.o.d" -o ${OBJECTDIR}/_ext/2118813141/Tick.o ../../../NR-Clib/Platform/src/pic32/Tick.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c   
	
${OBJECTDIR}/_ext/2118813141/UART.o: ../../../NR-Clib/Platform/src/pic32/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/UART.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/UART.o.d" -o ${OBJECTDIR}/_ext/2118813141/UART.o ../../../NR-Clib/Platform/src/pic32/UART.c   
	
${OBJECTDIR}/_ext/2118813141/ADC.o: ../../../NR-Clib/Platform/src/pic32/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/ADC.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/ADC.o.d" -o ${OBJECTDIR}/_ext/2118813141/ADC.o ../../../NR-Clib/Platform/src/pic32/ADC.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o: ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c   
	
${OBJECTDIR}/_ext/1080174469/AbstractPID.o: ../../../NR-Clib/BowlerStack/src/AbstractPID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" -o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ../../../NR-Clib/BowlerStack/src/AbstractPID.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o: ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c   
	
${OBJECTDIR}/_ext/1080174469/FIFO.o: ../../../NR-Clib/BowlerStack/src/FIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/FIFO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" -o ${OBJECTDIR}/_ext/1080174469/FIFO.o ../../../NR-Clib/BowlerStack/src/FIFO.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o: ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o: ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c   
	
${OBJECTDIR}/_ext/1080174469/Debug.o: ../../../NR-Clib/BowlerStack/src/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Debug.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Debug.o.d" -o ${OBJECTDIR}/_ext/1080174469/Debug.o ../../../NR-Clib/BowlerStack/src/Debug.c   
	
${OBJECTDIR}/_ext/1080174469/Scheduler.o: ../../../NR-Clib/BowlerStack/src/Scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Scheduler.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" -o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ../../../NR-Clib/BowlerStack/src/Scheduler.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Server.o: ../../../NR-Clib/BowlerStack/src/Bowler_Server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ../../../NR-Clib/BowlerStack/src/Bowler_Server.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c   
	
${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o: ../../src/Bowler/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/664674842 
	@${RM} ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o ../../src/Bowler/namespace/Namespace_bcs_cartesian.c   
	
else
${OBJECTDIR}/_ext/711791526/SPIClient.o: ../../src/Bowler/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/SPIClient.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" -o ${OBJECTDIR}/_ext/711791526/SPIClient.o ../../src/Bowler/SPIClient.c   
	
${OBJECTDIR}/_ext/711791526/main.o: ../../src/Bowler/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/main.o.d" -o ${OBJECTDIR}/_ext/711791526/main.o ../../src/Bowler/main.c   
	
${OBJECTDIR}/_ext/711791526/Callbacks.o: ../../src/Bowler/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Callbacks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" -o ${OBJECTDIR}/_ext/711791526/Callbacks.o ../../src/Bowler/Callbacks.c   
	
${OBJECTDIR}/_ext/711791526/UpstreamPackets.o: ../../src/Bowler/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ../../src/Bowler/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/711791526/AS5055.o: ../../src/Bowler/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/AS5055.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/AS5055.o.d" -o ${OBJECTDIR}/_ext/711791526/AS5055.o ../../src/Bowler/AS5055.c   
	
${OBJECTDIR}/_ext/711791526/PID.o: ../../src/Bowler/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/PID.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/PID.o.d" -o ${OBJECTDIR}/_ext/711791526/PID.o ../../src/Bowler/PID.c   
	
${OBJECTDIR}/_ext/711791526/Servo.o: ../../src/Bowler/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Servo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/Servo.o.d" -o ${OBJECTDIR}/_ext/711791526/Servo.o ../../src/Bowler/Servo.c   
	
${OBJECTDIR}/_ext/711791526/StepperSim.o: ../../src/Bowler/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/StepperSim.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" -o ${OBJECTDIR}/_ext/711791526/StepperSim.o ../../src/Bowler/StepperSim.c   
	
${OBJECTDIR}/_ext/711791526/ForgeHeater.o: ../../src/Bowler/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ../../src/Bowler/ForgeHeater.c   
	
${OBJECTDIR}/_ext/711791526/CartesianController.o: ../../src/Bowler/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/CartesianController.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" -o ${OBJECTDIR}/_ext/711791526/CartesianController.o ../../src/Bowler/CartesianController.c   
	
${OBJECTDIR}/_ext/711791526/DeltaKinematics.o: ../../src/Bowler/DeltaKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" -o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ../../src/Bowler/DeltaKinematics.c   
	
${OBJECTDIR}/_ext/711791526/delta.o: ../../src/Bowler/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/delta.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/delta.o.d" -o ${OBJECTDIR}/_ext/711791526/delta.o ../../src/Bowler/delta.c   
	
${OBJECTDIR}/_ext/711791526/Calibration.o: ../../src/Bowler/Calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Calibration.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/Calibration.o.d" -o ${OBJECTDIR}/_ext/711791526/Calibration.o ../../src/Bowler/Calibration.c   
	
${OBJECTDIR}/_ext/711791526/MotionTest.o: ../../src/Bowler/MotionTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/MotionTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" -o ${OBJECTDIR}/_ext/711791526/MotionTest.o ../../src/Bowler/MotionTest.c   
	
${OBJECTDIR}/_ext/1487882678/usb_descriptors.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/1487882678/usb_fifo.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c   
	
${OBJECTDIR}/_ext/1487882678/usb_callback.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_callback.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c   
	
${OBJECTDIR}/_ext/1487882678/usb_interrupt.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c   
	
${OBJECTDIR}/_ext/1487882678/usb_device.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_device.o ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c   
	
${OBJECTDIR}/_ext/2118813141/Delay.o: ../../../NR-Clib/Platform/src/pic32/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Delay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Delay.o.d" -o ${OBJECTDIR}/_ext/2118813141/Delay.o ../../../NR-Clib/Platform/src/pic32/Delay.c   
	
${OBJECTDIR}/_ext/2118813141/FlashStorage.o: ../../../NR-Clib/Platform/src/pic32/FlashStorage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" -o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ../../../NR-Clib/Platform/src/pic32/FlashStorage.c   
	
${OBJECTDIR}/_ext/2118813141/HAL_P32.o: ../../../NR-Clib/Platform/src/pic32/HAL_P32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" -o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ../../../NR-Clib/Platform/src/pic32/HAL_P32.c   
	
${OBJECTDIR}/_ext/2118813141/LED.o: ../../../NR-Clib/Platform/src/pic32/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/LED.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/LED.o.d" -o ${OBJECTDIR}/_ext/2118813141/LED.o ../../../NR-Clib/Platform/src/pic32/LED.c   
	
${OBJECTDIR}/_ext/2118813141/Tick.o: ../../../NR-Clib/Platform/src/pic32/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Tick.o.d" -o ${OBJECTDIR}/_ext/2118813141/Tick.o ../../../NR-Clib/Platform/src/pic32/Tick.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c   
	
${OBJECTDIR}/_ext/2118813141/UART.o: ../../../NR-Clib/Platform/src/pic32/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/UART.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/UART.o.d" -o ${OBJECTDIR}/_ext/2118813141/UART.o ../../../NR-Clib/Platform/src/pic32/UART.c   
	
${OBJECTDIR}/_ext/2118813141/ADC.o: ../../../NR-Clib/Platform/src/pic32/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/ADC.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/ADC.o.d" -o ${OBJECTDIR}/_ext/2118813141/ADC.o ../../../NR-Clib/Platform/src/pic32/ADC.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o: ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c   
	
${OBJECTDIR}/_ext/1080174469/AbstractPID.o: ../../../NR-Clib/BowlerStack/src/AbstractPID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" -o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ../../../NR-Clib/BowlerStack/src/AbstractPID.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o: ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c   
	
${OBJECTDIR}/_ext/1080174469/FIFO.o: ../../../NR-Clib/BowlerStack/src/FIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/FIFO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" -o ${OBJECTDIR}/_ext/1080174469/FIFO.o ../../../NR-Clib/BowlerStack/src/FIFO.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o: ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o: ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c   
	
${OBJECTDIR}/_ext/1080174469/Debug.o: ../../../NR-Clib/BowlerStack/src/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Debug.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Debug.o.d" -o ${OBJECTDIR}/_ext/1080174469/Debug.o ../../../NR-Clib/BowlerStack/src/Debug.c   
	
${OBJECTDIR}/_ext/1080174469/Scheduler.o: ../../../NR-Clib/BowlerStack/src/Scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Scheduler.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" -o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ../../../NR-Clib/BowlerStack/src/Scheduler.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Server.o: ../../../NR-Clib/BowlerStack/src/Bowler_Server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ../../../NR-Clib/BowlerStack/src/Bowler_Server.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c   
	
${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o: ../../src/Bowler/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/664674842 
	@${RM} ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/_ext/664674842/Namespace_bcs_cartesian.o ../../src/Bowler/namespace/Namespace_bcs_cartesian.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
