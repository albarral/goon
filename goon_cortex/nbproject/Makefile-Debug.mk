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
	${OBJECTDIR}/src/goon/cortex/CortexVision.o \
	${OBJECTDIR}/src/goon/cortex/bind/binding.o \
	${OBJECTDIR}/src/goon/cortex/model/Modeling.o \
	${OBJECTDIR}/src/goon/cortex/model/characterization.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Compare.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Evidence.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Matching2.o \
	${OBJECTDIR}/src/goon/cortex/recognition/Recall.o \
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
LDLIBSOPTIONS=-Wl,-rpath,../goon_data/dist/Debug/GNU-Linux -L../goon_data/dist/Debug/GNU-Linux -lgoon_data -Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}: ../goon_data/dist/Debug/GNU-Linux/libgoon_data.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}: ../goon_features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/cortex/CortexVision.o: src/goon/cortex/CortexVision.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/CortexVision.o src/goon/cortex/CortexVision.cpp

${OBJECTDIR}/src/goon/cortex/bind/binding.o: src/goon/cortex/bind/binding.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/bind
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/bind/binding.o src/goon/cortex/bind/binding.cpp

${OBJECTDIR}/src/goon/cortex/model/Modeling.o: src/goon/cortex/model/Modeling.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/model/Modeling.o src/goon/cortex/model/Modeling.cpp

${OBJECTDIR}/src/goon/cortex/model/characterization.o: src/goon/cortex/model/characterization.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/model
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/model/characterization.o src/goon/cortex/model/characterization.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Compare.o: src/goon/cortex/recognition/Compare.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Compare.o src/goon/cortex/recognition/Compare.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Evidence.o: src/goon/cortex/recognition/Evidence.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Evidence.o src/goon/cortex/recognition/Evidence.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Matching2.o: src/goon/cortex/recognition/Matching2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Matching2.o src/goon/cortex/recognition/Matching2.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Recall.o: src/goon/cortex/recognition/Recall.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Recall.o src/goon/cortex/recognition/Recall.cpp

${OBJECTDIR}/src/goon/cortex/recognition/Recognition2.o: src/goon/cortex/recognition/Recognition2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/cortex/recognition
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_data/src -I../goon_features/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/cortex/recognition/Recognition2.o src/goon/cortex/recognition/Recognition2.cpp

# Subprojects
.build-subprojects:
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_cortex.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
