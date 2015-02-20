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
ifeq "$(wildcard nbproject/Makefile-local-debugRev4.mk)" "nbproject/Makefile-local-debugRev4.mk"
include nbproject/Makefile-local-debugRev4.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=debugRev4
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/driver/AS5055.c src/driver/ForgeHeater.c src/driver/SPIClient.c src/driver/FlashStorageLocal.c src/driver/Servo.c src/kinematics/KosselKinematics.c src/kinematics/delta.c src/kinematics/FrogLegs.c src/kinematics/CartesianController.c src/kinematics/CartesianBoxKinematics.c src/motion/Calibration.c src/motion/StepperSim.c src/motion/PID.c src/namespace/Namespace_bcs_cartesian.c src/namespace/Namespace_bcs_rtd.c src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/driver/AS5055.o ${OBJECTDIR}/src/driver/ForgeHeater.o ${OBJECTDIR}/src/driver/SPIClient.o ${OBJECTDIR}/src/driver/FlashStorageLocal.o ${OBJECTDIR}/src/driver/Servo.o ${OBJECTDIR}/src/kinematics/KosselKinematics.o ${OBJECTDIR}/src/kinematics/delta.o ${OBJECTDIR}/src/kinematics/FrogLegs.o ${OBJECTDIR}/src/kinematics/CartesianController.o ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o ${OBJECTDIR}/src/motion/Calibration.o ${OBJECTDIR}/src/motion/StepperSim.o ${OBJECTDIR}/src/motion/PID.o ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o ${OBJECTDIR}/src/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/driver/AS5055.o.d ${OBJECTDIR}/src/driver/ForgeHeater.o.d ${OBJECTDIR}/src/driver/SPIClient.o.d ${OBJECTDIR}/src/driver/FlashStorageLocal.o.d ${OBJECTDIR}/src/driver/Servo.o.d ${OBJECTDIR}/src/kinematics/KosselKinematics.o.d ${OBJECTDIR}/src/kinematics/delta.o.d ${OBJECTDIR}/src/kinematics/FrogLegs.o.d ${OBJECTDIR}/src/kinematics/CartesianController.o.d ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d ${OBJECTDIR}/src/motion/Calibration.o.d ${OBJECTDIR}/src/motion/StepperSim.o.d ${OBJECTDIR}/src/motion/PID.o.d ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d ${OBJECTDIR}/src/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/driver/AS5055.o ${OBJECTDIR}/src/driver/ForgeHeater.o ${OBJECTDIR}/src/driver/SPIClient.o ${OBJECTDIR}/src/driver/FlashStorageLocal.o ${OBJECTDIR}/src/driver/Servo.o ${OBJECTDIR}/src/kinematics/KosselKinematics.o ${OBJECTDIR}/src/kinematics/delta.o ${OBJECTDIR}/src/kinematics/FrogLegs.o ${OBJECTDIR}/src/kinematics/CartesianController.o ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o ${OBJECTDIR}/src/motion/Calibration.o ${OBJECTDIR}/src/motion/StepperSim.o ${OBJECTDIR}/src/motion/PID.o ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o ${OBJECTDIR}/src/main.o

# Source Files
SOURCEFILES=src/driver/AS5055.c src/driver/ForgeHeater.c src/driver/SPIClient.c src/driver/FlashStorageLocal.c src/driver/Servo.c src/kinematics/KosselKinematics.c src/kinematics/delta.c src/kinematics/FrogLegs.c src/kinematics/CartesianController.c src/kinematics/CartesianBoxKinematics.c src/motion/Calibration.c src/motion/StepperSim.c src/motion/PID.c src/namespace/Namespace_bcs_cartesian.c src/namespace/Namespace_bcs_rtd.c src/main.c


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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-debugRev4.mk dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/driver/AS5055.o: src/driver/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/AS5055.o.d 
	@${RM} ${OBJECTDIR}/src/driver/AS5055.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/AS5055.o.d" -o ${OBJECTDIR}/src/driver/AS5055.o src/driver/AS5055.c    -DRev4
	
${OBJECTDIR}/src/driver/ForgeHeater.o: src/driver/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/ForgeHeater.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ForgeHeater.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/ForgeHeater.o.d" -o ${OBJECTDIR}/src/driver/ForgeHeater.o src/driver/ForgeHeater.c    -DRev4
	
${OBJECTDIR}/src/driver/SPIClient.o: src/driver/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/SPIClient.o.d 
	@${RM} ${OBJECTDIR}/src/driver/SPIClient.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/SPIClient.o.d" -o ${OBJECTDIR}/src/driver/SPIClient.o src/driver/SPIClient.c    -DRev4
	
${OBJECTDIR}/src/driver/FlashStorageLocal.o: src/driver/FlashStorageLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/FlashStorageLocal.o.d 
	@${RM} ${OBJECTDIR}/src/driver/FlashStorageLocal.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/FlashStorageLocal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/FlashStorageLocal.o.d" -o ${OBJECTDIR}/src/driver/FlashStorageLocal.o src/driver/FlashStorageLocal.c    -DRev4
	
${OBJECTDIR}/src/driver/Servo.o: src/driver/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/Servo.o.d 
	@${RM} ${OBJECTDIR}/src/driver/Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/Servo.o.d" -o ${OBJECTDIR}/src/driver/Servo.o src/driver/Servo.c    -DRev4
	
${OBJECTDIR}/src/kinematics/KosselKinematics.o: src/kinematics/KosselKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/KosselKinematics.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/KosselKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/KosselKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/KosselKinematics.o.d" -o ${OBJECTDIR}/src/kinematics/KosselKinematics.o src/kinematics/KosselKinematics.c    -DRev4
	
${OBJECTDIR}/src/kinematics/delta.o: src/kinematics/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/delta.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/delta.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/delta.o.d" -o ${OBJECTDIR}/src/kinematics/delta.o src/kinematics/delta.c    -DRev4
	
${OBJECTDIR}/src/kinematics/FrogLegs.o: src/kinematics/FrogLegs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/FrogLegs.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/FrogLegs.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/FrogLegs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/FrogLegs.o.d" -o ${OBJECTDIR}/src/kinematics/FrogLegs.o src/kinematics/FrogLegs.c    -DRev4
	
${OBJECTDIR}/src/kinematics/CartesianController.o: src/kinematics/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/CartesianController.o.d" -o ${OBJECTDIR}/src/kinematics/CartesianController.o src/kinematics/CartesianController.c    -DRev4
	
${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o: src/kinematics/CartesianBoxKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d" -o ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o src/kinematics/CartesianBoxKinematics.c    -DRev4
	
${OBJECTDIR}/src/motion/Calibration.o: src/motion/Calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/motion 
	@${RM} ${OBJECTDIR}/src/motion/Calibration.o.d 
	@${RM} ${OBJECTDIR}/src/motion/Calibration.o 
	@${FIXDEPS} "${OBJECTDIR}/src/motion/Calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/motion/Calibration.o.d" -o ${OBJECTDIR}/src/motion/Calibration.o src/motion/Calibration.c    -DRev4
	
${OBJECTDIR}/src/motion/StepperSim.o: src/motion/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/motion 
	@${RM} ${OBJECTDIR}/src/motion/StepperSim.o.d 
	@${RM} ${OBJECTDIR}/src/motion/StepperSim.o 
	@${FIXDEPS} "${OBJECTDIR}/src/motion/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/motion/StepperSim.o.d" -o ${OBJECTDIR}/src/motion/StepperSim.o src/motion/StepperSim.c    -DRev4
	
${OBJECTDIR}/src/motion/PID.o: src/motion/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/motion 
	@${RM} ${OBJECTDIR}/src/motion/PID.o.d 
	@${RM} ${OBJECTDIR}/src/motion/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/src/motion/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/motion/PID.o.d" -o ${OBJECTDIR}/src/motion/PID.o src/motion/PID.c    -DRev4
	
${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o: src/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/namespace 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o 
	@${FIXDEPS} "${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o src/namespace/Namespace_bcs_cartesian.c    -DRev4
	
${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o: src/namespace/Namespace_bcs_rtd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/namespace 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o 
	@${FIXDEPS} "${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d" -o ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o src/namespace/Namespace_bcs_rtd.c    -DRev4
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DRev4
	
else
${OBJECTDIR}/src/driver/AS5055.o: src/driver/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/AS5055.o.d 
	@${RM} ${OBJECTDIR}/src/driver/AS5055.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/AS5055.o.d" -o ${OBJECTDIR}/src/driver/AS5055.o src/driver/AS5055.c    -DRev4
	
${OBJECTDIR}/src/driver/ForgeHeater.o: src/driver/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/ForgeHeater.o.d 
	@${RM} ${OBJECTDIR}/src/driver/ForgeHeater.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/ForgeHeater.o.d" -o ${OBJECTDIR}/src/driver/ForgeHeater.o src/driver/ForgeHeater.c    -DRev4
	
${OBJECTDIR}/src/driver/SPIClient.o: src/driver/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/SPIClient.o.d 
	@${RM} ${OBJECTDIR}/src/driver/SPIClient.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/SPIClient.o.d" -o ${OBJECTDIR}/src/driver/SPIClient.o src/driver/SPIClient.c    -DRev4
	
${OBJECTDIR}/src/driver/FlashStorageLocal.o: src/driver/FlashStorageLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/FlashStorageLocal.o.d 
	@${RM} ${OBJECTDIR}/src/driver/FlashStorageLocal.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/FlashStorageLocal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/FlashStorageLocal.o.d" -o ${OBJECTDIR}/src/driver/FlashStorageLocal.o src/driver/FlashStorageLocal.c    -DRev4
	
${OBJECTDIR}/src/driver/Servo.o: src/driver/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/driver 
	@${RM} ${OBJECTDIR}/src/driver/Servo.o.d 
	@${RM} ${OBJECTDIR}/src/driver/Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/driver/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/driver/Servo.o.d" -o ${OBJECTDIR}/src/driver/Servo.o src/driver/Servo.c    -DRev4
	
${OBJECTDIR}/src/kinematics/KosselKinematics.o: src/kinematics/KosselKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/KosselKinematics.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/KosselKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/KosselKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/KosselKinematics.o.d" -o ${OBJECTDIR}/src/kinematics/KosselKinematics.o src/kinematics/KosselKinematics.c    -DRev4
	
${OBJECTDIR}/src/kinematics/delta.o: src/kinematics/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/delta.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/delta.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/delta.o.d" -o ${OBJECTDIR}/src/kinematics/delta.o src/kinematics/delta.c    -DRev4
	
${OBJECTDIR}/src/kinematics/FrogLegs.o: src/kinematics/FrogLegs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/FrogLegs.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/FrogLegs.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/FrogLegs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/FrogLegs.o.d" -o ${OBJECTDIR}/src/kinematics/FrogLegs.o src/kinematics/FrogLegs.c    -DRev4
	
${OBJECTDIR}/src/kinematics/CartesianController.o: src/kinematics/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/CartesianController.o.d" -o ${OBJECTDIR}/src/kinematics/CartesianController.o src/kinematics/CartesianController.c    -DRev4
	
${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o: src/kinematics/CartesianBoxKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/kinematics 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d 
	@${RM} ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o.d" -o ${OBJECTDIR}/src/kinematics/CartesianBoxKinematics.o src/kinematics/CartesianBoxKinematics.c    -DRev4
	
${OBJECTDIR}/src/motion/Calibration.o: src/motion/Calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/motion 
	@${RM} ${OBJECTDIR}/src/motion/Calibration.o.d 
	@${RM} ${OBJECTDIR}/src/motion/Calibration.o 
	@${FIXDEPS} "${OBJECTDIR}/src/motion/Calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/motion/Calibration.o.d" -o ${OBJECTDIR}/src/motion/Calibration.o src/motion/Calibration.c    -DRev4
	
${OBJECTDIR}/src/motion/StepperSim.o: src/motion/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/motion 
	@${RM} ${OBJECTDIR}/src/motion/StepperSim.o.d 
	@${RM} ${OBJECTDIR}/src/motion/StepperSim.o 
	@${FIXDEPS} "${OBJECTDIR}/src/motion/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/motion/StepperSim.o.d" -o ${OBJECTDIR}/src/motion/StepperSim.o src/motion/StepperSim.c    -DRev4
	
${OBJECTDIR}/src/motion/PID.o: src/motion/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/motion 
	@${RM} ${OBJECTDIR}/src/motion/PID.o.d 
	@${RM} ${OBJECTDIR}/src/motion/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/src/motion/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/motion/PID.o.d" -o ${OBJECTDIR}/src/motion/PID.o src/motion/PID.c    -DRev4
	
${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o: src/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/namespace 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o 
	@${FIXDEPS} "${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/src/namespace/Namespace_bcs_cartesian.o src/namespace/Namespace_bcs_cartesian.c    -DRev4
	
${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o: src/namespace/Namespace_bcs_rtd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/namespace 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d 
	@${RM} ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o 
	@${FIXDEPS} "${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o.d" -o ${OBJECTDIR}/src/namespace/Namespace_bcs_rtd.o src/namespace/Namespace_bcs_rtd.c    -DRev4
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"include/replicator" -I"../../c-bowler/Platform/include" -I"../../c-bowler/BowlerStack/include" -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DRev4
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../c-bowler/c-bowler.X/dist/default/debug/c-bowler.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../c-bowler/c-bowler.X/dist/default/debug/c-bowler.X.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../c-bowler/c-bowler.X/dist/default/production/c-bowler.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../c-bowler/c-bowler.X/dist/default/production/c-bowler.X.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:
	cd ../../c-bowler/c-bowler.X && ${MAKE}  -f Makefile CONF=default


# Subprojects
.clean-subprojects:
	cd ../../c-bowler/c-bowler.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/debugRev4
	${RM} -r dist/debugRev4

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
