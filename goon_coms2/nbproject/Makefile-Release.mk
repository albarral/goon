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
	${OBJECTDIR}/src/goon/coms/VisionComs.o \
	${OBJECTDIR}/src/goon/coms/VisionConnector.o \
	${OBJECTDIR}/src/goon/coms/modules/VisionServer.o \
	${OBJECTDIR}/src/goon/coms/server/ExtraChannelServer.o \
	${OBJECTDIR}/src/goon/coms/server/FocusChannelServer.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_coms2.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_coms2.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_coms2.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/coms/VisionComs.o: src/goon/coms/VisionComs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/coms/VisionComs.o src/goon/coms/VisionComs.cpp

${OBJECTDIR}/src/goon/coms/VisionConnector.o: src/goon/coms/VisionConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/coms/VisionConnector.o src/goon/coms/VisionConnector.cpp

${OBJECTDIR}/src/goon/coms/modules/VisionServer.o: src/goon/coms/modules/VisionServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/coms/modules/VisionServer.o src/goon/coms/modules/VisionServer.cpp

${OBJECTDIR}/src/goon/coms/server/ExtraChannelServer.o: src/goon/coms/server/ExtraChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/coms/server/ExtraChannelServer.o src/goon/coms/server/ExtraChannelServer.cpp

${OBJECTDIR}/src/goon/coms/server/FocusChannelServer.o: src/goon/coms/server/FocusChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/coms/server/FocusChannelServer.o src/goon/coms/server/FocusChannelServer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_coms2.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
