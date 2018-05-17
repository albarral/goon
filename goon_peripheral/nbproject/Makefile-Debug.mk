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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/goon/peripheral/PeripheralVision.o \
	${OBJECTDIR}/src/goon/peripheral/RoisDetection.o \
	${OBJECTDIR}/src/goon/peripheral/Saliency.o


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
LDLIBSOPTIONS=-Wl,-rpath,../goon_data/dist/Debug/GNU-Linux -L../goon_data/dist/Debug/GNU-Linux -lgoon_data -Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../../tron/tron_cv/dist/Debug/GNU-Linux -L../../tron/tron_cv/dist/Debug/GNU-Linux -ltron_cv -Wl,-rpath,../../tron/tron_math/dist/Debug/GNU-Linux -L../../tron/tron_math/dist/Debug/GNU-Linux -ltron_math -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util -lopencv_core

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}: ../goon_data/dist/Debug/GNU-Linux/libgoon_data.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}: ../goon_features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}: ../../tron/tron_cv/dist/Debug/GNU-Linux/libtron_cv.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}: ../../tron/tron_math/dist/Debug/GNU-Linux/libtron_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/peripheral/PeripheralVision.o: src/goon/peripheral/PeripheralVision.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../goon_data/src -I../../tron/tron_cv/src -I../../tron/tron_math/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/PeripheralVision.o src/goon/peripheral/PeripheralVision.cpp

${OBJECTDIR}/src/goon/peripheral/RoisDetection.o: src/goon/peripheral/RoisDetection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../goon_data/src -I../../tron/tron_cv/src -I../../tron/tron_math/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/RoisDetection.o src/goon/peripheral/RoisDetection.cpp

${OBJECTDIR}/src/goon/peripheral/Saliency.o: src/goon/peripheral/Saliency.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/peripheral
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../goon_data/src -I../../tron/tron_cv/src -I../../tron/tron_math/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/peripheral/Saliency.o src/goon/peripheral/Saliency.cpp

# Subprojects
.build-subprojects:
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_cv && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_peripheral.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_cv && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
