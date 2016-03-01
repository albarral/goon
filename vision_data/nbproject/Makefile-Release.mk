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
	${OBJECTDIR}/src/goon/data/aux/Body.o \
	${OBJECTDIR}/src/goon/data/aux/Identity.o \
	${OBJECTDIR}/src/goon/data/aux/Record.o \
	${OBJECTDIR}/src/goon/data/aux/VisualElement.o \
	${OBJECTDIR}/src/goon/data/aux/vMotion.o \
	${OBJECTDIR}/src/goon/data/base/blob.o \
	${OBJECTDIR}/src/goon/data/base/motion.o \
	${OBJECTDIR}/src/goon/data/base/region.o \
	${OBJECTDIR}/src/goon/data/base/roi.o \
	${OBJECTDIR}/src/goon/data/capture.o \
	${OBJECTDIR}/src/goon/data/elements/Model.o \
	${OBJECTDIR}/src/goon/data/elements/ModelView.o \
	${OBJECTDIR}/src/goon/data/elements/Object.o \
	${OBJECTDIR}/src/goon/data/elements/Scene.o \
	${OBJECTDIR}/src/goon/data/retina.o \
	${OBJECTDIR}/src/goon/data/rois.o \
	${OBJECTDIR}/src/goon/data/visual_data.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_data.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_data.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_data.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/data/aux/Body.o: src/goon/data/aux/Body.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/aux
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/aux/Body.o src/goon/data/aux/Body.cpp

${OBJECTDIR}/src/goon/data/aux/Identity.o: src/goon/data/aux/Identity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/aux
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/aux/Identity.o src/goon/data/aux/Identity.cpp

${OBJECTDIR}/src/goon/data/aux/Record.o: src/goon/data/aux/Record.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/aux
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/aux/Record.o src/goon/data/aux/Record.cpp

${OBJECTDIR}/src/goon/data/aux/VisualElement.o: src/goon/data/aux/VisualElement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/aux
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/aux/VisualElement.o src/goon/data/aux/VisualElement.cpp

${OBJECTDIR}/src/goon/data/aux/vMotion.o: src/goon/data/aux/vMotion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/aux
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/aux/vMotion.o src/goon/data/aux/vMotion.cpp

${OBJECTDIR}/src/goon/data/base/blob.o: src/goon/data/base/blob.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/blob.o src/goon/data/base/blob.cpp

${OBJECTDIR}/src/goon/data/base/motion.o: src/goon/data/base/motion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/motion.o src/goon/data/base/motion.cpp

${OBJECTDIR}/src/goon/data/base/region.o: src/goon/data/base/region.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/region.o src/goon/data/base/region.cpp

${OBJECTDIR}/src/goon/data/base/roi.o: src/goon/data/base/roi.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/base/roi.o src/goon/data/base/roi.cpp

${OBJECTDIR}/src/goon/data/capture.o: src/goon/data/capture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/capture.o src/goon/data/capture.cpp

${OBJECTDIR}/src/goon/data/elements/Model.o: src/goon/data/elements/Model.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/elements
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/elements/Model.o src/goon/data/elements/Model.cpp

${OBJECTDIR}/src/goon/data/elements/ModelView.o: src/goon/data/elements/ModelView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/elements
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/elements/ModelView.o src/goon/data/elements/ModelView.cpp

${OBJECTDIR}/src/goon/data/elements/Object.o: src/goon/data/elements/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/elements
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/elements/Object.o src/goon/data/elements/Object.cpp

${OBJECTDIR}/src/goon/data/elements/Scene.o: src/goon/data/elements/Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data/elements
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/elements/Scene.o src/goon/data/elements/Scene.cpp

${OBJECTDIR}/src/goon/data/retina.o: src/goon/data/retina.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/retina.o src/goon/data/retina.cpp

${OBJECTDIR}/src/goon/data/rois.o: src/goon/data/rois.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/rois.o src/goon/data/rois.cpp

${OBJECTDIR}/src/goon/data/visual_data.o: src/goon/data/visual_data.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/data/visual_data.o src/goon/data/visual_data.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvision_data.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
