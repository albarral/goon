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
	${OBJECTDIR}/src/goon/utils/Click.o \
	${OBJECTDIR}/src/goon/utils/Module.o \
	${OBJECTDIR}/src/goon/utils/angle.o \
	${OBJECTDIR}/src/goon/utils/area.o \
	${OBJECTDIR}/src/goon/utils/average.o \
	${OBJECTDIR}/src/goon/utils/distance.o \
	${OBJECTDIR}/src/goon/utils/hsv_color.o \
	${OBJECTDIR}/src/goon/utils/rgb_color.o \
	${OBJECTDIR}/src/goon/utils/shape.o \
	${OBJECTDIR}/src/goon/utils/trigger.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_utils.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_utils.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_utils.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/utils/Click.o: src/goon/utils/Click.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/Click.o src/goon/utils/Click.cpp

${OBJECTDIR}/src/goon/utils/Module.o: src/goon/utils/Module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/Module.o src/goon/utils/Module.cpp

${OBJECTDIR}/src/goon/utils/angle.o: src/goon/utils/angle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/angle.o src/goon/utils/angle.cpp

${OBJECTDIR}/src/goon/utils/area.o: src/goon/utils/area.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/area.o src/goon/utils/area.cpp

${OBJECTDIR}/src/goon/utils/average.o: src/goon/utils/average.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/average.o src/goon/utils/average.cpp

${OBJECTDIR}/src/goon/utils/distance.o: src/goon/utils/distance.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/distance.o src/goon/utils/distance.cpp

${OBJECTDIR}/src/goon/utils/hsv_color.o: src/goon/utils/hsv_color.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/hsv_color.o src/goon/utils/hsv_color.cpp

${OBJECTDIR}/src/goon/utils/rgb_color.o: src/goon/utils/rgb_color.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/rgb_color.o src/goon/utils/rgb_color.cpp

${OBJECTDIR}/src/goon/utils/shape.o: src/goon/utils/shape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/shape.o src/goon/utils/shape.cpp

${OBJECTDIR}/src/goon/utils/trigger.o: src/goon/utils/trigger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/utils/trigger.o src/goon/utils/trigger.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_utils.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
