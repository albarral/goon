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
	${OBJECTDIR}/src/goon/cortex/CortexVision.o \
	${OBJECTDIR}/src/goon/cortex/analysis/binding.o \
	${OBJECTDIR}/src/goon/cortex/analysis/characterization.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Compare.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Matching2.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Modeling.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Recognition2.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/cortex/CortexVision.o: src/goon/cortex/CortexVision.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/CortexVision.o src/goon/cortex/CortexVision.cpp

${OBJECTDIR}/src/goon/cortex/analysis/binding.o: src/goon/cortex/analysis/binding.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/analysis
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/analysis/binding.o src/goon/cortex/analysis/binding.cpp

${OBJECTDIR}/src/goon/cortex/analysis/characterization.o: src/goon/cortex/analysis/characterization.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/analysis
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/analysis/characterization.o src/goon/cortex/analysis/characterization.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Compare.o: src/goon/cortex/recognition/Compare.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Compare.o src/goon/cortex/recognition/Compare.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Matching2.o: src/goon/cortex/recognition/Matching2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Matching2.o src/goon/cortex/recognition/Matching2.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Modeling.o: src/goon/cortex/recognition/Modeling.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Modeling.o src/goon/cortex/recognition/Modeling.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Recognition2.o: src/goon/cortex/recognition/Recognition2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Recognition2.o src/goon/cortex/recognition/Recognition2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
