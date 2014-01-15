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

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c ../../../NR-Clib/Platform/src/pic32/Delay.c ../../../NR-Clib/Platform/src/pic32/FlashStorage.c ../../../NR-Clib/Platform/src/pic32/HAL_P32.c ../../../NR-Clib/Platform/src/pic32/LED.c ../../../NR-Clib/Platform/src/pic32/Tick.c ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c ../../../NR-Clib/Platform/src/pic32/UART.c ../../../NR-Clib/Platform/src/pic32/ADC.c ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c ../../../NR-Clib/BowlerStack/src/AbstractPID.c ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c ../../../NR-Clib/BowlerStack/src/FIFO.c ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c ../../../NR-Clib/BowlerStack/src/Debug.c ../../../NR-Clib/BowlerStack/src/Scheduler.c ../../../NR-Clib/BowlerStack/src/Bowler_Server.c ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c ../../../NR-Clib/BowlerStack/src/Namespace_bcs_rpc.c ../../src/driver/Servo.c ../../src/driver/SPIClient.c ../../src/driver/ForgeHeater.c ../../src/driver/AS5055.c ../../src/kinematics/KosselKinematics.c ../../src/kinematics/CartesianController.c ../../src/kinematics/DeltaKinematics.c ../../src/kinematics/delta.c ../../src/motion/MotionTest.c ../../src/motion/StepperSim.c ../../src/motion/servoCalibration.c ../../src/motion/PID.c ../../src/namespace/UpstreamPackets.c ../../src/namespace/Namespace_bcs_cartesian.c ../../src/namespace/Callbacks.c ../../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ${OBJECTDIR}/_ext/1487882678/usb_device.o ${OBJECTDIR}/_ext/2118813141/Delay.o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ${OBJECTDIR}/_ext/2118813141/LED.o ${OBJECTDIR}/_ext/2118813141/Tick.o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ${OBJECTDIR}/_ext/2118813141/UART.o ${OBJECTDIR}/_ext/2118813141/ADC.o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ${OBJECTDIR}/_ext/1080174469/FIFO.o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ${OBJECTDIR}/_ext/1080174469/Debug.o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o ${OBJECTDIR}/_ext/263962707/Servo.o ${OBJECTDIR}/_ext/263962707/SPIClient.o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ${OBJECTDIR}/_ext/263962707/AS5055.o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o ${OBJECTDIR}/_ext/1494288313/delta.o ${OBJECTDIR}/_ext/519170017/MotionTest.o ${OBJECTDIR}/_ext/519170017/StepperSim.o ${OBJECTDIR}/_ext/519170017/servoCalibration.o ${OBJECTDIR}/_ext/519170017/PID.o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ${OBJECTDIR}/_ext/1445274692/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d ${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d ${OBJECTDIR}/_ext/1487882678/usb_callback.o.d ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d ${OBJECTDIR}/_ext/1487882678/usb_device.o.d ${OBJECTDIR}/_ext/2118813141/Delay.o.d ${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d ${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d ${OBJECTDIR}/_ext/2118813141/LED.o.d ${OBJECTDIR}/_ext/2118813141/Tick.o.d ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d ${OBJECTDIR}/_ext/2118813141/UART.o.d ${OBJECTDIR}/_ext/2118813141/ADC.o.d ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d ${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d ${OBJECTDIR}/_ext/1080174469/FIFO.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d ${OBJECTDIR}/_ext/1080174469/Debug.o.d ${OBJECTDIR}/_ext/1080174469/Scheduler.o.d ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d ${OBJECTDIR}/_ext/263962707/Servo.o.d ${OBJECTDIR}/_ext/263962707/SPIClient.o.d ${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d ${OBJECTDIR}/_ext/263962707/AS5055.o.d ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d ${OBJECTDIR}/_ext/1494288313/CartesianController.o.d ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d ${OBJECTDIR}/_ext/1494288313/delta.o.d ${OBJECTDIR}/_ext/519170017/MotionTest.o.d ${OBJECTDIR}/_ext/519170017/StepperSim.o.d ${OBJECTDIR}/_ext/519170017/servoCalibration.o.d ${OBJECTDIR}/_ext/519170017/PID.o.d ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d ${OBJECTDIR}/_ext/2048476848/Callbacks.o.d ${OBJECTDIR}/_ext/1445274692/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ${OBJECTDIR}/_ext/1487882678/usb_device.o ${OBJECTDIR}/_ext/2118813141/Delay.o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ${OBJECTDIR}/_ext/2118813141/LED.o ${OBJECTDIR}/_ext/2118813141/Tick.o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ${OBJECTDIR}/_ext/2118813141/UART.o ${OBJECTDIR}/_ext/2118813141/ADC.o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ${OBJECTDIR}/_ext/1080174469/FIFO.o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ${OBJECTDIR}/_ext/1080174469/Debug.o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o ${OBJECTDIR}/_ext/263962707/Servo.o ${OBJECTDIR}/_ext/263962707/SPIClient.o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ${OBJECTDIR}/_ext/263962707/AS5055.o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o ${OBJECTDIR}/_ext/1494288313/delta.o ${OBJECTDIR}/_ext/519170017/MotionTest.o ${OBJECTDIR}/_ext/519170017/StepperSim.o ${OBJECTDIR}/_ext/519170017/servoCalibration.o ${OBJECTDIR}/_ext/519170017/PID.o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ${OBJECTDIR}/_ext/1445274692/main.o

# Source Files
SOURCEFILES=../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c ../../../NR-Clib/Platform/src/pic32/Delay.c ../../../NR-Clib/Platform/src/pic32/FlashStorage.c ../../../NR-Clib/Platform/src/pic32/HAL_P32.c ../../../NR-Clib/Platform/src/pic32/LED.c ../../../NR-Clib/Platform/src/pic32/Tick.c ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c ../../../NR-Clib/Platform/src/pic32/UART.c ../../../NR-Clib/Platform/src/pic32/ADC.c ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c ../../../NR-Clib/BowlerStack/src/AbstractPID.c ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c ../../../NR-Clib/BowlerStack/src/FIFO.c ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c ../../../NR-Clib/BowlerStack/src/Debug.c ../../../NR-Clib/BowlerStack/src/Scheduler.c ../../../NR-Clib/BowlerStack/src/Bowler_Server.c ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c ../../../NR-Clib/BowlerStack/src/Namespace_bcs_rpc.c ../../src/driver/Servo.c ../../src/driver/SPIClient.c ../../src/driver/ForgeHeater.c ../../src/driver/AS5055.c ../../src/kinematics/KosselKinematics.c ../../src/kinematics/CartesianController.c ../../src/kinematics/DeltaKinematics.c ../../src/kinematics/delta.c ../../src/motion/MotionTest.c ../../src/motion/StepperSim.c ../../src/motion/servoCalibration.c ../../src/motion/PID.c ../../src/namespace/UpstreamPackets.c ../../src/namespace/Namespace_bcs_cartesian.c ../../src/namespace/Callbacks.c ../../src/main.c


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

MP_PROCESSOR_OPTION=32MX440F128H
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
${OBJECTDIR}/_ext/1487882678/usb_descriptors.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/1487882678/usb_fifo.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_fifo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c   
	
${OBJECTDIR}/_ext/1487882678/usb_callback.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c   
	
${OBJECTDIR}/_ext/1487882678/usb_interrupt.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c   
	
${OBJECTDIR}/_ext/1487882678/usb_device.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_device.o ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c   
	
${OBJECTDIR}/_ext/2118813141/Delay.o: ../../../NR-Clib/Platform/src/pic32/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Delay.o.d" -o ${OBJECTDIR}/_ext/2118813141/Delay.o ../../../NR-Clib/Platform/src/pic32/Delay.c   
	
${OBJECTDIR}/_ext/2118813141/FlashStorage.o: ../../../NR-Clib/Platform/src/pic32/FlashStorage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/FlashStorage.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" -o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ../../../NR-Clib/Platform/src/pic32/FlashStorage.c   
	
${OBJECTDIR}/_ext/2118813141/HAL_P32.o: ../../../NR-Clib/Platform/src/pic32/HAL_P32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/HAL_P32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" -o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ../../../NR-Clib/Platform/src/pic32/HAL_P32.c   
	
${OBJECTDIR}/_ext/2118813141/LED.o: ../../../NR-Clib/Platform/src/pic32/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/LED.o.d" -o ${OBJECTDIR}/_ext/2118813141/LED.o ../../../NR-Clib/Platform/src/pic32/LED.c   
	
${OBJECTDIR}/_ext/2118813141/Tick.o: ../../../NR-Clib/Platform/src/pic32/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Tick.o.d" -o ${OBJECTDIR}/_ext/2118813141/Tick.o ../../../NR-Clib/Platform/src/pic32/Tick.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c   
	
${OBJECTDIR}/_ext/2118813141/UART.o: ../../../NR-Clib/Platform/src/pic32/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/UART.o.d" -o ${OBJECTDIR}/_ext/2118813141/UART.o ../../../NR-Clib/Platform/src/pic32/UART.c   
	
${OBJECTDIR}/_ext/2118813141/ADC.o: ../../../NR-Clib/Platform/src/pic32/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/ADC.o.d" -o ${OBJECTDIR}/_ext/2118813141/ADC.o ../../../NR-Clib/Platform/src/pic32/ADC.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o: ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c   
	
${OBJECTDIR}/_ext/1080174469/AbstractPID.o: ../../../NR-Clib/BowlerStack/src/AbstractPID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/AbstractPID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" -o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ../../../NR-Clib/BowlerStack/src/AbstractPID.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o: ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c   
	
${OBJECTDIR}/_ext/1080174469/FIFO.o: ../../../NR-Clib/BowlerStack/src/FIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/FIFO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/FIFO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" -o ${OBJECTDIR}/_ext/1080174469/FIFO.o ../../../NR-Clib/BowlerStack/src/FIFO.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o: ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o: ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c   
	
${OBJECTDIR}/_ext/1080174469/Debug.o: ../../../NR-Clib/BowlerStack/src/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Debug.o.d" -o ${OBJECTDIR}/_ext/1080174469/Debug.o ../../../NR-Clib/BowlerStack/src/Debug.c   
	
${OBJECTDIR}/_ext/1080174469/Scheduler.o: ../../../NR-Clib/BowlerStack/src/Scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Scheduler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" -o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ../../../NR-Clib/BowlerStack/src/Scheduler.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Server.o: ../../../NR-Clib/BowlerStack/src/Bowler_Server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ../../../NR-Clib/BowlerStack/src/Bowler_Server.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_rpc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_rpc.c   
	
${OBJECTDIR}/_ext/263962707/Servo.o: ../../src/driver/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/Servo.o.d" -o ${OBJECTDIR}/_ext/263962707/Servo.o ../../src/driver/Servo.c   
	
${OBJECTDIR}/_ext/263962707/SPIClient.o: ../../src/driver/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" -o ${OBJECTDIR}/_ext/263962707/SPIClient.o ../../src/driver/SPIClient.c   
	
${OBJECTDIR}/_ext/263962707/ForgeHeater.o: ../../src/driver/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ../../src/driver/ForgeHeater.c   
	
${OBJECTDIR}/_ext/263962707/AS5055.o: ../../src/driver/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/AS5055.o.d" -o ${OBJECTDIR}/_ext/263962707/AS5055.o ../../src/driver/AS5055.c   
	
${OBJECTDIR}/_ext/1494288313/KosselKinematics.o: ../../src/kinematics/KosselKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" -o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ../../src/kinematics/KosselKinematics.c   
	
${OBJECTDIR}/_ext/1494288313/CartesianController.o: ../../src/kinematics/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" -o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ../../src/kinematics/CartesianController.c   
	
${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o: ../../src/kinematics/DeltaKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d" -o ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o ../../src/kinematics/DeltaKinematics.c   
	
${OBJECTDIR}/_ext/1494288313/delta.o: ../../src/kinematics/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/delta.o.d" -o ${OBJECTDIR}/_ext/1494288313/delta.o ../../src/kinematics/delta.c   
	
${OBJECTDIR}/_ext/519170017/MotionTest.o: ../../src/motion/MotionTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/MotionTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/MotionTest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/MotionTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/MotionTest.o.d" -o ${OBJECTDIR}/_ext/519170017/MotionTest.o ../../src/motion/MotionTest.c   
	
${OBJECTDIR}/_ext/519170017/StepperSim.o: ../../src/motion/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" -o ${OBJECTDIR}/_ext/519170017/StepperSim.o ../../src/motion/StepperSim.c   
	
${OBJECTDIR}/_ext/519170017/servoCalibration.o: ../../src/motion/servoCalibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/servoCalibration.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/servoCalibration.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/servoCalibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/servoCalibration.o.d" -o ${OBJECTDIR}/_ext/519170017/servoCalibration.o ../../src/motion/servoCalibration.c   
	
${OBJECTDIR}/_ext/519170017/PID.o: ../../src/motion/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/PID.o.d" -o ${OBJECTDIR}/_ext/519170017/PID.o ../../src/motion/PID.c   
	
${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o: ../../src/namespace/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ../../src/namespace/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o: ../../src/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ../../src/namespace/Namespace_bcs_cartesian.c   
	
${OBJECTDIR}/_ext/2048476848/Callbacks.o: ../../src/namespace/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" -o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ../../src/namespace/Callbacks.c   
	
${OBJECTDIR}/_ext/1445274692/main.o: ../../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445274692 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445274692/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1445274692/main.o.d" -o ${OBJECTDIR}/_ext/1445274692/main.o ../../src/main.c   
	
else
${OBJECTDIR}/_ext/1487882678/usb_descriptors.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_descriptors.o ../../../NR-Clib/Platform/src/pic32/usb/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_function_cdc.o ../../../NR-Clib/Platform/src/pic32/usb/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/1487882678/usb_fifo.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_fifo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_fifo.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_fifo.o ../../../NR-Clib/Platform/src/pic32/usb/usb_fifo.c   
	
${OBJECTDIR}/_ext/1487882678/usb_callback.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_callback.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_callback.o ../../../NR-Clib/Platform/src/pic32/usb/usb_callback.c   
	
${OBJECTDIR}/_ext/1487882678/usb_interrupt.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_interrupt.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_interrupt.o ../../../NR-Clib/Platform/src/pic32/usb/usb_interrupt.c   
	
${OBJECTDIR}/_ext/1487882678/usb_device.o: ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1487882678 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1487882678/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1487882678/usb_device.o.d" -o ${OBJECTDIR}/_ext/1487882678/usb_device.o ../../../NR-Clib/Platform/src/pic32/usb/usb_device.c   
	
${OBJECTDIR}/_ext/2118813141/Delay.o: ../../../NR-Clib/Platform/src/pic32/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Delay.o.d" -o ${OBJECTDIR}/_ext/2118813141/Delay.o ../../../NR-Clib/Platform/src/pic32/Delay.c   
	
${OBJECTDIR}/_ext/2118813141/FlashStorage.o: ../../../NR-Clib/Platform/src/pic32/FlashStorage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/FlashStorage.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/FlashStorage.o.d" -o ${OBJECTDIR}/_ext/2118813141/FlashStorage.o ../../../NR-Clib/Platform/src/pic32/FlashStorage.c   
	
${OBJECTDIR}/_ext/2118813141/HAL_P32.o: ../../../NR-Clib/Platform/src/pic32/HAL_P32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/HAL_P32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/HAL_P32.o.d" -o ${OBJECTDIR}/_ext/2118813141/HAL_P32.o ../../../NR-Clib/Platform/src/pic32/HAL_P32.c   
	
${OBJECTDIR}/_ext/2118813141/LED.o: ../../../NR-Clib/Platform/src/pic32/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/LED.o.d" -o ${OBJECTDIR}/_ext/2118813141/LED.o ../../../NR-Clib/Platform/src/pic32/LED.c   
	
${OBJECTDIR}/_ext/2118813141/Tick.o: ../../../NR-Clib/Platform/src/pic32/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Tick.o.d" -o ${OBJECTDIR}/_ext/2118813141/Tick.o ../../../NR-Clib/Platform/src/pic32/Tick.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_UART_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_UART_HAL.c   
	
${OBJECTDIR}/_ext/2118813141/UART.o: ../../../NR-Clib/Platform/src/pic32/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/UART.o.d" -o ${OBJECTDIR}/_ext/2118813141/UART.o ../../../NR-Clib/Platform/src/pic32/UART.c   
	
${OBJECTDIR}/_ext/2118813141/ADC.o: ../../../NR-Clib/Platform/src/pic32/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/ADC.o.d" -o ${OBJECTDIR}/_ext/2118813141/ADC.o ../../../NR-Clib/Platform/src/pic32/ADC.c   
	
${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o: ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2118813141 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o.d" -o ${OBJECTDIR}/_ext/2118813141/Bowler_USB_HAL.o ../../../NR-Clib/Platform/src/pic32/Bowler_USB_HAL.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o: ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Helper.o ../../../NR-Clib/BowlerStack/src/Bowler_Helper.c   
	
${OBJECTDIR}/_ext/1080174469/AbstractPID.o: ../../../NR-Clib/BowlerStack/src/AbstractPID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/AbstractPID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/AbstractPID.o.d" -o ${OBJECTDIR}/_ext/1080174469/AbstractPID.o ../../../NR-Clib/BowlerStack/src/AbstractPID.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o: ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Stack_Callback.o ../../../NR-Clib/BowlerStack/src/Bowler_Stack_Callback.c   
	
${OBJECTDIR}/_ext/1080174469/FIFO.o: ../../../NR-Clib/BowlerStack/src/FIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/FIFO.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/FIFO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/FIFO.o.d" -o ${OBJECTDIR}/_ext/1080174469/FIFO.o ../../../NR-Clib/BowlerStack/src/FIFO.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o: ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_RPC_Process.o ../../../NR-Clib/BowlerStack/src/Bowler_RPC_Process.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o: ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Transport.o ../../../NR-Clib/BowlerStack/src/Bowler_Transport.c   
	
${OBJECTDIR}/_ext/1080174469/Debug.o: ../../../NR-Clib/BowlerStack/src/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Debug.o.d" -o ${OBJECTDIR}/_ext/1080174469/Debug.o ../../../NR-Clib/BowlerStack/src/Debug.c   
	
${OBJECTDIR}/_ext/1080174469/Scheduler.o: ../../../NR-Clib/BowlerStack/src/Scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Scheduler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Scheduler.o.d" -o ${OBJECTDIR}/_ext/1080174469/Scheduler.o ../../../NR-Clib/BowlerStack/src/Scheduler.c   
	
${OBJECTDIR}/_ext/1080174469/Bowler_Server.o: ../../../NR-Clib/BowlerStack/src/Bowler_Server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Bowler_Server.o.d" -o ${OBJECTDIR}/_ext/1080174469/Bowler_Server.o ../../../NR-Clib/BowlerStack/src/Bowler_Server.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_core.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_core.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_pid.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_pid.c   
	
${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o: ../../../NR-Clib/BowlerStack/src/Namespace_bcs_rpc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1080174469 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o.d" -o ${OBJECTDIR}/_ext/1080174469/Namespace_bcs_rpc.o ../../../NR-Clib/BowlerStack/src/Namespace_bcs_rpc.c   
	
${OBJECTDIR}/_ext/263962707/Servo.o: ../../src/driver/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/Servo.o.d" -o ${OBJECTDIR}/_ext/263962707/Servo.o ../../src/driver/Servo.c   
	
${OBJECTDIR}/_ext/263962707/SPIClient.o: ../../src/driver/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" -o ${OBJECTDIR}/_ext/263962707/SPIClient.o ../../src/driver/SPIClient.c   
	
${OBJECTDIR}/_ext/263962707/ForgeHeater.o: ../../src/driver/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ../../src/driver/ForgeHeater.c   
	
${OBJECTDIR}/_ext/263962707/AS5055.o: ../../src/driver/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/263962707/AS5055.o.d" -o ${OBJECTDIR}/_ext/263962707/AS5055.o ../../src/driver/AS5055.c   
	
${OBJECTDIR}/_ext/1494288313/KosselKinematics.o: ../../src/kinematics/KosselKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" -o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ../../src/kinematics/KosselKinematics.c   
	
${OBJECTDIR}/_ext/1494288313/CartesianController.o: ../../src/kinematics/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" -o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ../../src/kinematics/CartesianController.c   
	
${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o: ../../src/kinematics/DeltaKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o.d" -o ${OBJECTDIR}/_ext/1494288313/DeltaKinematics.o ../../src/kinematics/DeltaKinematics.c   
	
${OBJECTDIR}/_ext/1494288313/delta.o: ../../src/kinematics/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1494288313/delta.o.d" -o ${OBJECTDIR}/_ext/1494288313/delta.o ../../src/kinematics/delta.c   
	
${OBJECTDIR}/_ext/519170017/MotionTest.o: ../../src/motion/MotionTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/MotionTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/MotionTest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/MotionTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/MotionTest.o.d" -o ${OBJECTDIR}/_ext/519170017/MotionTest.o ../../src/motion/MotionTest.c   
	
${OBJECTDIR}/_ext/519170017/StepperSim.o: ../../src/motion/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" -o ${OBJECTDIR}/_ext/519170017/StepperSim.o ../../src/motion/StepperSim.c   
	
${OBJECTDIR}/_ext/519170017/servoCalibration.o: ../../src/motion/servoCalibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/servoCalibration.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/servoCalibration.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/servoCalibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/servoCalibration.o.d" -o ${OBJECTDIR}/_ext/519170017/servoCalibration.o ../../src/motion/servoCalibration.c   
	
${OBJECTDIR}/_ext/519170017/PID.o: ../../src/motion/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/519170017/PID.o.d" -o ${OBJECTDIR}/_ext/519170017/PID.o ../../src/motion/PID.c   
	
${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o: ../../src/namespace/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ../../src/namespace/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o: ../../src/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ../../src/namespace/Namespace_bcs_cartesian.c   
	
${OBJECTDIR}/_ext/2048476848/Callbacks.o: ../../src/namespace/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" -o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ../../src/namespace/Callbacks.c   
	
${OBJECTDIR}/_ext/1445274692/main.o: ../../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445274692 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445274692/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/BowlerStack/include" -I"../../../NR-Clib/Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1445274692/main.o.d" -o ${OBJECTDIR}/_ext/1445274692/main.o ../../src/main.c   
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
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
