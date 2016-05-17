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
	${OBJECTDIR}/src/goon/peripheral/IDPool.o \
	${OBJECTDIR}/src/goon/peripheral/Unit.o \
	${OBJECTDIR}/src/goon/peripheral/peripheral_vision.o \
	${OBJECTDIR}/src/goon/peripheral/units_detection.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperipheral_vision.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperipheral_vision.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperipheral_vision.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/peripheral/IDPool.o: src/goon/peripheral/IDPool.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/IDPool.o src/goon/peripheral/IDPool.cpp

${OBJECTDIR}/src/goon/peripheral/Unit.o: src/goon/peripheral/Unit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/Unit.o src/goon/peripheral/Unit.cpp

${OBJECTDIR}/src/goon/peripheral/peripheral_vision.o: src/goon/peripheral/peripheral_vision.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/peripheral_vision.o src/goon/peripheral/peripheral_vision.cpp

${OBJECTDIR}/src/goon/peripheral/units_detection.o: src/goon/peripheral/units_detection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/units_detection.o src/goon/peripheral/units_detection.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libperipheral_vision.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
