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
	${OBJECTDIR}/src/goon/data/base/Body.o \
	${OBJECTDIR}/src/goon/data/base/BodyUtils.o \
	${OBJECTDIR}/src/goon/data/base/blob.o \
	${OBJECTDIR}/src/goon/data/base/region.o \
	${OBJECTDIR}/src/goon/data/base/roi.o \
	${OBJECTDIR}/src/goon/data/motion/Motion.o \
	${OBJECTDIR}/src/goon/data/motion/Move.o \
	${OBJECTDIR}/src/goon/data/motion/Move2D.o \
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
LDLIBSOPTIONS=-Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -lopencv_core

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}: ../goon_features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/data/base/Body.o: src/goon/data/base/Body.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/Body.o src/goon/data/base/Body.cpp

${OBJECTDIR}/src/goon/data/base/BodyUtils.o: src/goon/data/base/BodyUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/BodyUtils.o src/goon/data/base/BodyUtils.cpp

${OBJECTDIR}/src/goon/data/base/blob.o: src/goon/data/base/blob.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/blob.o src/goon/data/base/blob.cpp

${OBJECTDIR}/src/goon/data/base/region.o: src/goon/data/base/region.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/region.o src/goon/data/base/region.cpp

${OBJECTDIR}/src/goon/data/base/roi.o: src/goon/data/base/roi.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/roi.o src/goon/data/base/roi.cpp

${OBJECTDIR}/src/goon/data/motion/Motion.o: src/goon/data/motion/Motion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/motion
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/motion/Motion.o src/goon/data/motion/Motion.cpp

${OBJECTDIR}/src/goon/data/motion/Move.o: src/goon/data/motion/Move.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/motion
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/motion/Move.o src/goon/data/motion/Move.cpp

${OBJECTDIR}/src/goon/data/motion/Move2D.o: src/goon/data/motion/Move2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/motion
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/motion/Move2D.o src/goon/data/motion/Move2D.cpp

${OBJECTDIR}/src/goon/data/retina.o: src/goon/data/retina.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/retina.o src/goon/data/retina.cpp

${OBJECTDIR}/src/goon/data/rois.o: src/goon/data/rois.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_features/src -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/rois.o src/goon/data/rois.cpp

# Subprojects
.build-subprojects:
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_data.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
