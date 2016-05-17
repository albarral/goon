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
	${OBJECTDIR}/src/goon/test/Module.o \
	${OBJECTDIR}/src/goon/test/TestBodies.o \
	${OBJECTDIR}/src/goon/test/TestRegions.o \
	${OBJECTDIR}/src/goon/test/main.o \
	${OBJECTDIR}/src/goon/test/modules/Grab.o \
	${OBJECTDIR}/src/goon/test/modules/See.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/test/Module.o: src/goon/test/Module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/Module.o src/goon/test/Module.cpp

${OBJECTDIR}/src/goon/test/TestBodies.o: src/goon/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/TestBodies.o src/goon/test/TestBodies.cpp

${OBJECTDIR}/src/goon/test/TestRegions.o: src/goon/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/TestRegions.o src/goon/test/TestRegions.cpp

${OBJECTDIR}/src/goon/test/main.o: src/goon/test/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/main.o src/goon/test/main.cpp

${OBJECTDIR}/src/goon/test/modules/Grab.o: src/goon/test/modules/Grab.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/modules/Grab.o src/goon/test/modules/Grab.cpp

${OBJECTDIR}/src/goon/test/modules/See.o: src/goon/test/modules/See.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/modules/See.o src/goon/test/modules/See.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
