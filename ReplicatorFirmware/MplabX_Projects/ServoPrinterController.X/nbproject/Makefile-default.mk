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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/711791526/SPIClient.o ${OBJECTDIR}/_ext/711791526/main.o ${OBJECTDIR}/_ext/711791526/Callbacks.o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ${OBJECTDIR}/_ext/711791526/AS5055.o ${OBJECTDIR}/_ext/711791526/PID.o ${OBJECTDIR}/_ext/711791526/Servo.o ${OBJECTDIR}/_ext/711791526/StepperSim.o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ${OBJECTDIR}/_ext/711791526/CartesianController.o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ${OBJECTDIR}/_ext/711791526/delta.o ${OBJECTDIR}/_ext/711791526/Calibration.o ${OBJECTDIR}/_ext/711791526/MotionTest.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/711791526/SPIClient.o.d ${OBJECTDIR}/_ext/711791526/main.o.d ${OBJECTDIR}/_ext/711791526/Callbacks.o.d ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d ${OBJECTDIR}/_ext/711791526/AS5055.o.d ${OBJECTDIR}/_ext/711791526/PID.o.d ${OBJECTDIR}/_ext/711791526/Servo.o.d ${OBJECTDIR}/_ext/711791526/StepperSim.o.d ${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d ${OBJECTDIR}/_ext/711791526/CartesianController.o.d ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d ${OBJECTDIR}/_ext/711791526/delta.o.d ${OBJECTDIR}/_ext/711791526/Calibration.o.d ${OBJECTDIR}/_ext/711791526/MotionTest.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/711791526/SPIClient.o ${OBJECTDIR}/_ext/711791526/main.o ${OBJECTDIR}/_ext/711791526/Callbacks.o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ${OBJECTDIR}/_ext/711791526/AS5055.o ${OBJECTDIR}/_ext/711791526/PID.o ${OBJECTDIR}/_ext/711791526/Servo.o ${OBJECTDIR}/_ext/711791526/StepperSim.o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ${OBJECTDIR}/_ext/711791526/CartesianController.o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ${OBJECTDIR}/_ext/711791526/delta.o ${OBJECTDIR}/_ext/711791526/Calibration.o ${OBJECTDIR}/_ext/711791526/MotionTest.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" -o ${OBJECTDIR}/_ext/711791526/SPIClient.o ../../src/Bowler/SPIClient.c   
	
${OBJECTDIR}/_ext/711791526/main.o: ../../src/Bowler/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/main.o.d" -o ${OBJECTDIR}/_ext/711791526/main.o ../../src/Bowler/main.c   
	
${OBJECTDIR}/_ext/711791526/Callbacks.o: ../../src/Bowler/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Callbacks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" -o ${OBJECTDIR}/_ext/711791526/Callbacks.o ../../src/Bowler/Callbacks.c   
	
${OBJECTDIR}/_ext/711791526/UpstreamPackets.o: ../../src/Bowler/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ../../src/Bowler/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/711791526/AS5055.o: ../../src/Bowler/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/AS5055.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/AS5055.o.d" -o ${OBJECTDIR}/_ext/711791526/AS5055.o ../../src/Bowler/AS5055.c   
	
${OBJECTDIR}/_ext/711791526/PID.o: ../../src/Bowler/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/PID.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/PID.o.d" -o ${OBJECTDIR}/_ext/711791526/PID.o ../../src/Bowler/PID.c   
	
${OBJECTDIR}/_ext/711791526/Servo.o: ../../src/Bowler/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Servo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/Servo.o.d" -o ${OBJECTDIR}/_ext/711791526/Servo.o ../../src/Bowler/Servo.c   
	
${OBJECTDIR}/_ext/711791526/StepperSim.o: ../../src/Bowler/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/StepperSim.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" -o ${OBJECTDIR}/_ext/711791526/StepperSim.o ../../src/Bowler/StepperSim.c   
	
${OBJECTDIR}/_ext/711791526/ForgeHeater.o: ../../src/Bowler/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ../../src/Bowler/ForgeHeater.c   
	
${OBJECTDIR}/_ext/711791526/CartesianController.o: ../../src/Bowler/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/CartesianController.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" -o ${OBJECTDIR}/_ext/711791526/CartesianController.o ../../src/Bowler/CartesianController.c   
	
${OBJECTDIR}/_ext/711791526/DeltaKinematics.o: ../../src/Bowler/DeltaKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" -o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ../../src/Bowler/DeltaKinematics.c   
	
${OBJECTDIR}/_ext/711791526/delta.o: ../../src/Bowler/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/delta.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/delta.o.d" -o ${OBJECTDIR}/_ext/711791526/delta.o ../../src/Bowler/delta.c   
	
${OBJECTDIR}/_ext/711791526/Calibration.o: ../../src/Bowler/Calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Calibration.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/Calibration.o.d" -o ${OBJECTDIR}/_ext/711791526/Calibration.o ../../src/Bowler/Calibration.c   
	
${OBJECTDIR}/_ext/711791526/MotionTest.o: ../../src/Bowler/MotionTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/MotionTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" -o ${OBJECTDIR}/_ext/711791526/MotionTest.o ../../src/Bowler/MotionTest.c   
	
else
${OBJECTDIR}/_ext/711791526/SPIClient.o: ../../src/Bowler/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/SPIClient.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/SPIClient.o.d" -o ${OBJECTDIR}/_ext/711791526/SPIClient.o ../../src/Bowler/SPIClient.c   
	
${OBJECTDIR}/_ext/711791526/main.o: ../../src/Bowler/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/main.o.d" -o ${OBJECTDIR}/_ext/711791526/main.o ../../src/Bowler/main.c   
	
${OBJECTDIR}/_ext/711791526/Callbacks.o: ../../src/Bowler/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Callbacks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/Callbacks.o.d" -o ${OBJECTDIR}/_ext/711791526/Callbacks.o ../../src/Bowler/Callbacks.c   
	
${OBJECTDIR}/_ext/711791526/UpstreamPackets.o: ../../src/Bowler/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/711791526/UpstreamPackets.o ../../src/Bowler/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/711791526/AS5055.o: ../../src/Bowler/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/AS5055.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/AS5055.o.d" -o ${OBJECTDIR}/_ext/711791526/AS5055.o ../../src/Bowler/AS5055.c   
	
${OBJECTDIR}/_ext/711791526/PID.o: ../../src/Bowler/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/PID.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/PID.o.d" -o ${OBJECTDIR}/_ext/711791526/PID.o ../../src/Bowler/PID.c   
	
${OBJECTDIR}/_ext/711791526/Servo.o: ../../src/Bowler/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Servo.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/Servo.o.d" -o ${OBJECTDIR}/_ext/711791526/Servo.o ../../src/Bowler/Servo.c   
	
${OBJECTDIR}/_ext/711791526/StepperSim.o: ../../src/Bowler/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/StepperSim.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/StepperSim.o.d" -o ${OBJECTDIR}/_ext/711791526/StepperSim.o ../../src/Bowler/StepperSim.c   
	
${OBJECTDIR}/_ext/711791526/ForgeHeater.o: ../../src/Bowler/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/711791526/ForgeHeater.o ../../src/Bowler/ForgeHeater.c   
	
${OBJECTDIR}/_ext/711791526/CartesianController.o: ../../src/Bowler/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/CartesianController.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/CartesianController.o.d" -o ${OBJECTDIR}/_ext/711791526/CartesianController.o ../../src/Bowler/CartesianController.c   
	
${OBJECTDIR}/_ext/711791526/DeltaKinematics.o: ../../src/Bowler/DeltaKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/DeltaKinematics.o.d" -o ${OBJECTDIR}/_ext/711791526/DeltaKinematics.o ../../src/Bowler/DeltaKinematics.c   
	
${OBJECTDIR}/_ext/711791526/delta.o: ../../src/Bowler/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/delta.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/delta.o.d" -o ${OBJECTDIR}/_ext/711791526/delta.o ../../src/Bowler/delta.c   
	
${OBJECTDIR}/_ext/711791526/Calibration.o: ../../src/Bowler/Calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/Calibration.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/Calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/Calibration.o.d" -o ${OBJECTDIR}/_ext/711791526/Calibration.o ../../src/Bowler/Calibration.c   
	
${OBJECTDIR}/_ext/711791526/MotionTest.o: ../../src/Bowler/MotionTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/711791526 
	@${RM} ${OBJECTDIR}/_ext/711791526/MotionTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../include/replicator" -I"../../../NR-Clib/include" -I"../../../NR-Clib/include/arch/pic32" -MMD -MF "${OBJECTDIR}/_ext/711791526/MotionTest.o.d" -o ${OBJECTDIR}/_ext/711791526/MotionTest.o ../../src/Bowler/MotionTest.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ExampleEthernet.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
