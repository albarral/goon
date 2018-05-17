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
	${OBJECTDIR}/src/goon/data/VisualMemory.o \
	${OBJECTDIR}/src/goon/data/base/ColorBody.o \
	${OBJECTDIR}/src/goon/data/base/RealBody.o \
	${OBJECTDIR}/src/goon/data/base/region.o \
	${OBJECTDIR}/src/goon/data/base/roi.o \
	${OBJECTDIR}/src/goon/data/config/CortexConfig.o \
	${OBJECTDIR}/src/goon/data/config/RetinalConfig.o \
	${OBJECTDIR}/src/goon/data/cortex/Model.o \
	${OBJECTDIR}/src/goon/data/cortex/Object.o \
	${OBJECTDIR}/src/goon/data/cortex/ObjectModel.o \
	${OBJECTDIR}/src/goon/data/cortex/Scene.o \
	${OBJECTDIR}/src/goon/data/retina.o \
	${OBJECTDIR}/src/goon/data/rois.o


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
LDLIBSOPTIONS=-Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util -lopencv_core

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}: ../goon_features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/data/VisualMemory.o: src/goon/data/VisualMemory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/VisualMemory.o src/goon/data/VisualMemory.cpp

${OBJECTDIR}/src/goon/data/base/ColorBody.o: src/goon/data/base/ColorBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/ColorBody.o src/goon/data/base/ColorBody.cpp

${OBJECTDIR}/src/goon/data/base/RealBody.o: src/goon/data/base/RealBody.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/RealBody.o src/goon/data/base/RealBody.cpp

${OBJECTDIR}/src/goon/data/base/region.o: src/goon/data/base/region.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/region.o src/goon/data/base/region.cpp

${OBJECTDIR}/src/goon/data/base/roi.o: src/goon/data/base/roi.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/roi.o src/goon/data/base/roi.cpp

${OBJECTDIR}/src/goon/data/config/CortexConfig.o: src/goon/data/config/CortexConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/config/CortexConfig.o src/goon/data/config/CortexConfig.cpp

${OBJECTDIR}/src/goon/data/config/RetinalConfig.o: src/goon/data/config/RetinalConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/config/RetinalConfig.o src/goon/data/config/RetinalConfig.cpp

${OBJECTDIR}/src/goon/data/cortex/Model.o: src/goon/data/cortex/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/cortex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/cortex/Model.o src/goon/data/cortex/Model.cpp

${OBJECTDIR}/src/goon/data/cortex/Object.o: src/goon/data/cortex/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/cortex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/cortex/Object.o src/goon/data/cortex/Object.cpp

${OBJECTDIR}/src/goon/data/cortex/ObjectModel.o: src/goon/data/cortex/ObjectModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/cortex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/cortex/ObjectModel.o src/goon/data/cortex/ObjectModel.cpp

${OBJECTDIR}/src/goon/data/cortex/Scene.o: src/goon/data/cortex/Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/cortex
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/cortex/Scene.o src/goon/data/cortex/Scene.cpp

${OBJECTDIR}/src/goon/data/retina.o: src/goon/data/retina.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/retina.o src/goon/data/retina.cpp

${OBJECTDIR}/src/goon/data/rois.o: src/goon/data/rois.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/rois.o src/goon/data/rois.cpp

# Subprojects
.build-subprojects:
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
