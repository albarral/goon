#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/goon/look/LookManager.o \
	${OBJECTDIR}/src/goon/look/bus/LookBus.o \
	${OBJECTDIR}/src/goon/look/main.o \
	${OBJECTDIR}/src/goon/look/modules/Grab.o \
	${OBJECTDIR}/src/goon/look/modules/LookMonitor.o \
	${OBJECTDIR}/src/goon/look/modules/See.o \
	${OBJECTDIR}/src/goon/look/test/TestBodies.o \
	${OBJECTDIR}/src/goon/look/test/TestRegions.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/look/LookManager.o: src/goon/look/LookManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/LookManager.o src/goon/look/LookManager.cpp

${OBJECTDIR}/src/goon/look/bus/LookBus.o: src/goon/look/bus/LookBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/bus/LookBus.o src/goon/look/bus/LookBus.cpp

${OBJECTDIR}/src/goon/look/main.o: src/goon/look/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/main.o src/goon/look/main.cpp

${OBJECTDIR}/src/goon/look/modules/Grab.o: src/goon/look/modules/Grab.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/modules/Grab.o src/goon/look/modules/Grab.cpp

${OBJECTDIR}/src/goon/look/modules/LookMonitor.o: src/goon/look/modules/LookMonitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/modules/LookMonitor.o src/goon/look/modules/LookMonitor.cpp

${OBJECTDIR}/src/goon/look/modules/See.o: src/goon/look/modules/See.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/modules/See.o src/goon/look/modules/See.cpp

${OBJECTDIR}/src/goon/look/test/TestBodies.o: src/goon/look/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/test/TestBodies.o src/goon/look/test/TestBodies.cpp

${OBJECTDIR}/src/goon/look/test/TestRegions.o: src/goon/look/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/test/TestRegions.o src/goon/look/test/TestRegions.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
