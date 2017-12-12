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
	${OBJECTDIR}/src/goon/camera/Grabber.o \
	${OBJECTDIR}/src/goon/camera/camera.o \
	${OBJECTDIR}/src/goon/camera/models/image_flow.o \
	${OBJECTDIR}/src/goon/camera/models/ip_camera.o \
	${OBJECTDIR}/src/goon/camera/models/video_flow.o \
	${OBJECTDIR}/src/goon/camera/models/web_camera.o


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
LDLIBSOPTIONS=-lopencv_core -lopencv_highgui -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_camera.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_camera.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_camera.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/camera/Grabber.o: src/goon/camera/Grabber.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/camera
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/camera/Grabber.o src/goon/camera/Grabber.cpp

${OBJECTDIR}/src/goon/camera/camera.o: src/goon/camera/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/camera
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/camera/camera.o src/goon/camera/camera.cpp

${OBJECTDIR}/src/goon/camera/models/image_flow.o: src/goon/camera/models/image_flow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/camera/models
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/camera/models/image_flow.o src/goon/camera/models/image_flow.cpp

${OBJECTDIR}/src/goon/camera/models/ip_camera.o: src/goon/camera/models/ip_camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/camera/models
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/camera/models/ip_camera.o src/goon/camera/models/ip_camera.cpp

${OBJECTDIR}/src/goon/camera/models/video_flow.o: src/goon/camera/models/video_flow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/camera/models
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/camera/models/video_flow.o src/goon/camera/models/video_flow.cpp

${OBJECTDIR}/src/goon/camera/models/web_camera.o: src/goon/camera/models/web_camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/camera/models
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/camera/models/web_camera.o src/goon/camera/models/web_camera.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_camera.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
