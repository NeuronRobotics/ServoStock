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
SOURCEFILES_QUOTED_IF_SPACED=../../src/driver/Servo.c ../../src/driver/SPIClient.c ../../src/driver/ForgeHeater.c ../../src/driver/AS5055.c ../../src/driver/FlashStorageLocal.c ../../src/kinematics/KosselKinematics.c ../../src/kinematics/CartesianController.c ../../src/kinematics/delta.c ../../src/kinematics/FrogLegs.c ../../src/motion/StepperSim.c ../../src/motion/PID.c ../../src/namespace/UpstreamPackets.c ../../src/namespace/Namespace_bcs_cartesian.c ../../src/namespace/Callbacks.c ../../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/263962707/Servo.o ${OBJECTDIR}/_ext/263962707/SPIClient.o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ${OBJECTDIR}/_ext/263962707/AS5055.o ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ${OBJECTDIR}/_ext/1494288313/delta.o ${OBJECTDIR}/_ext/1494288313/FrogLegs.o ${OBJECTDIR}/_ext/519170017/StepperSim.o ${OBJECTDIR}/_ext/519170017/PID.o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ${OBJECTDIR}/_ext/1445274692/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/263962707/Servo.o.d ${OBJECTDIR}/_ext/263962707/SPIClient.o.d ${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d ${OBJECTDIR}/_ext/263962707/AS5055.o.d ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d ${OBJECTDIR}/_ext/1494288313/CartesianController.o.d ${OBJECTDIR}/_ext/1494288313/delta.o.d ${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d ${OBJECTDIR}/_ext/519170017/StepperSim.o.d ${OBJECTDIR}/_ext/519170017/PID.o.d ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d ${OBJECTDIR}/_ext/2048476848/Callbacks.o.d ${OBJECTDIR}/_ext/1445274692/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/263962707/Servo.o ${OBJECTDIR}/_ext/263962707/SPIClient.o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ${OBJECTDIR}/_ext/263962707/AS5055.o ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ${OBJECTDIR}/_ext/1494288313/delta.o ${OBJECTDIR}/_ext/1494288313/FrogLegs.o ${OBJECTDIR}/_ext/519170017/StepperSim.o ${OBJECTDIR}/_ext/519170017/PID.o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ${OBJECTDIR}/_ext/1445274692/main.o

# Source Files
SOURCEFILES=../../src/driver/Servo.c ../../src/driver/SPIClient.c ../../src/driver/ForgeHeater.c ../../src/driver/AS5055.c ../../src/driver/FlashStorageLocal.c ../../src/kinematics/KosselKinematics.c ../../src/kinematics/CartesianController.c ../../src/kinematics/delta.c ../../src/kinematics/FrogLegs.c ../../src/motion/StepperSim.c ../../src/motion/PID.c ../../src/namespace/UpstreamPackets.c ../../src/namespace/Namespace_bcs_cartesian.c ../../src/namespace/Callbacks.c ../../src/main.c


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
${OBJECTDIR}/_ext/263962707/Servo.o: ../../src/driver/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/Servo.o.d" -o ${OBJECTDIR}/_ext/263962707/Servo.o ../../src/driver/Servo.c   
	
${OBJECTDIR}/_ext/263962707/SPIClient.o: ../../src/driver/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" -o ${OBJECTDIR}/_ext/263962707/SPIClient.o ../../src/driver/SPIClient.c   
	
${OBJECTDIR}/_ext/263962707/ForgeHeater.o: ../../src/driver/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ../../src/driver/ForgeHeater.c   
	
${OBJECTDIR}/_ext/263962707/AS5055.o: ../../src/driver/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/AS5055.o.d" -o ${OBJECTDIR}/_ext/263962707/AS5055.o ../../src/driver/AS5055.c   
	
${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o: ../../src/driver/FlashStorageLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d" -o ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o ../../src/driver/FlashStorageLocal.c   
	
${OBJECTDIR}/_ext/1494288313/KosselKinematics.o: ../../src/kinematics/KosselKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" -o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ../../src/kinematics/KosselKinematics.c   
	
${OBJECTDIR}/_ext/1494288313/CartesianController.o: ../../src/kinematics/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" -o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ../../src/kinematics/CartesianController.c   
	
${OBJECTDIR}/_ext/1494288313/delta.o: ../../src/kinematics/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/delta.o.d" -o ${OBJECTDIR}/_ext/1494288313/delta.o ../../src/kinematics/delta.c   
	
${OBJECTDIR}/_ext/1494288313/FrogLegs.o: ../../src/kinematics/FrogLegs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/FrogLegs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d" -o ${OBJECTDIR}/_ext/1494288313/FrogLegs.o ../../src/kinematics/FrogLegs.c   
	
${OBJECTDIR}/_ext/519170017/StepperSim.o: ../../src/motion/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" -o ${OBJECTDIR}/_ext/519170017/StepperSim.o ../../src/motion/StepperSim.c   
	
${OBJECTDIR}/_ext/519170017/PID.o: ../../src/motion/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/519170017/PID.o.d" -o ${OBJECTDIR}/_ext/519170017/PID.o ../../src/motion/PID.c   
	
${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o: ../../src/namespace/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ../../src/namespace/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o: ../../src/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ../../src/namespace/Namespace_bcs_cartesian.c   
	
${OBJECTDIR}/_ext/2048476848/Callbacks.o: ../../src/namespace/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" -o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ../../src/namespace/Callbacks.c   
	
${OBJECTDIR}/_ext/1445274692/main.o: ../../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445274692 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445274692/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1445274692/main.o.d" -o ${OBJECTDIR}/_ext/1445274692/main.o ../../src/main.c   
	
else
${OBJECTDIR}/_ext/263962707/Servo.o: ../../src/driver/Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/Servo.o.d" -o ${OBJECTDIR}/_ext/263962707/Servo.o ../../src/driver/Servo.c   
	
${OBJECTDIR}/_ext/263962707/SPIClient.o: ../../src/driver/SPIClient.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/SPIClient.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/SPIClient.o.d" -o ${OBJECTDIR}/_ext/263962707/SPIClient.o ../../src/driver/SPIClient.c   
	
${OBJECTDIR}/_ext/263962707/ForgeHeater.o: ../../src/driver/ForgeHeater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/ForgeHeater.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/ForgeHeater.o.d" -o ${OBJECTDIR}/_ext/263962707/ForgeHeater.o ../../src/driver/ForgeHeater.c   
	
${OBJECTDIR}/_ext/263962707/AS5055.o: ../../src/driver/AS5055.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/AS5055.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/AS5055.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/AS5055.o.d" -o ${OBJECTDIR}/_ext/263962707/AS5055.o ../../src/driver/AS5055.c   
	
${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o: ../../src/driver/FlashStorageLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/263962707 
	@${RM} ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d 
	@${RM} ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o.d" -o ${OBJECTDIR}/_ext/263962707/FlashStorageLocal.o ../../src/driver/FlashStorageLocal.c   
	
${OBJECTDIR}/_ext/1494288313/KosselKinematics.o: ../../src/kinematics/KosselKinematics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/KosselKinematics.o.d" -o ${OBJECTDIR}/_ext/1494288313/KosselKinematics.o ../../src/kinematics/KosselKinematics.c   
	
${OBJECTDIR}/_ext/1494288313/CartesianController.o: ../../src/kinematics/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/CartesianController.o.d" -o ${OBJECTDIR}/_ext/1494288313/CartesianController.o ../../src/kinematics/CartesianController.c   
	
${OBJECTDIR}/_ext/1494288313/delta.o: ../../src/kinematics/delta.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/delta.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/delta.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/delta.o.d" -o ${OBJECTDIR}/_ext/1494288313/delta.o ../../src/kinematics/delta.c   
	
${OBJECTDIR}/_ext/1494288313/FrogLegs.o: ../../src/kinematics/FrogLegs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1494288313 
	@${RM} ${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494288313/FrogLegs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1494288313/FrogLegs.o.d" -o ${OBJECTDIR}/_ext/1494288313/FrogLegs.o ../../src/kinematics/FrogLegs.c   
	
${OBJECTDIR}/_ext/519170017/StepperSim.o: ../../src/motion/StepperSim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/StepperSim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/519170017/StepperSim.o.d" -o ${OBJECTDIR}/_ext/519170017/StepperSim.o ../../src/motion/StepperSim.c   
	
${OBJECTDIR}/_ext/519170017/PID.o: ../../src/motion/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/519170017 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o.d 
	@${RM} ${OBJECTDIR}/_ext/519170017/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/519170017/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/519170017/PID.o.d" -o ${OBJECTDIR}/_ext/519170017/PID.o ../../src/motion/PID.c   
	
${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o: ../../src/namespace/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/2048476848/UpstreamPackets.o ../../src/namespace/UpstreamPackets.c   
	
${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o: ../../src/namespace/Namespace_bcs_cartesian.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o.d" -o ${OBJECTDIR}/_ext/2048476848/Namespace_bcs_cartesian.o ../../src/namespace/Namespace_bcs_cartesian.c   
	
${OBJECTDIR}/_ext/2048476848/Callbacks.o: ../../src/namespace/Callbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048476848 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2048476848/Callbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2048476848/Callbacks.o.d" -o ${OBJECTDIR}/_ext/2048476848/Callbacks.o ../../src/namespace/Callbacks.c   
	
${OBJECTDIR}/_ext/1445274692/main.o: ../../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445274692 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445274692/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -O1 -I"../../../../c-bowler/firmware/library/NR-Clib/development/BowlerStack/include" -I"../../../../c-bowler/firmware/library/NR-Clib/development/Platform/include" -I"../../include/replicator" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1445274692/main.o.d" -o ${OBJECTDIR}/_ext/1445274692/main.o ../../src/main.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../c-bowler/firmware/library/NR-Clib/development/c-bowler.X/dist/default/debug/c-bowler.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../../../c-bowler/firmware/library/NR-Clib/development/c-bowler.X/dist/default/debug/c-bowler.X.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=1024,--defsym=_min_stack_size=1024,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../c-bowler/firmware/library/NR-Clib/development/c-bowler.X/dist/default/production/c-bowler.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../../../c-bowler/firmware/library/NR-Clib/development/c-bowler.X/dist/default/production/c-bowler.X.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--defsym=_min_stack_size=1024,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ServoPrinterController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:
	cd ../../../../c-bowler/firmware/library/NR-Clib/development/c-bowler.X && ${MAKE}  -f Makefile CONF=default


# Subprojects
.clean-subprojects:
	cd ../../../../c-bowler/firmware/library/NR-Clib/development/c-bowler.X && rm -rf "build/default" "dist/default"

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
