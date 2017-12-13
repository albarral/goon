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
	${OBJECTDIR}/src/goon/main/GoonControl.o \
	${OBJECTDIR}/src/goon/main/main.o \
	${OBJECTDIR}/src/goon/main/test/TestBodies.o \
	${OBJECTDIR}/src/goon/main/test/TestRegions.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon_main

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon_main: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon_main ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/main/GoonControl.o: src/goon/main/GoonControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/GoonControl.o src/goon/main/GoonControl.cpp

${OBJECTDIR}/src/goon/main/main.o: src/goon/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/main.o src/goon/main/main.cpp

${OBJECTDIR}/src/goon/main/test/TestBodies.o: src/goon/main/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestBodies.o src/goon/main/test/TestBodies.cpp

${OBJECTDIR}/src/goon/main/test/TestRegions.o: src/goon/main/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestRegions.o src/goon/main/test/TestRegions.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon_main

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
