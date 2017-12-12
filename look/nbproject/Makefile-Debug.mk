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
	${OBJECTDIR}/src/goon/look/GoonControl.o \
	${OBJECTDIR}/src/goon/look/GoonShow.o \
	${OBJECTDIR}/src/goon/look/main.o \
	${OBJECTDIR}/src/goon/look/test/TestBodies.o \
	${OBJECTDIR}/src/goon/look/test/TestRegions.o


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
LDLIBSOPTIONS=-Wl,-rpath,../goon_core/dist/Debug/GNU-Linux -L../goon_core/dist/Debug/GNU-Linux -lgoon_core -Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../goon_data/dist/Debug/GNU-Linux -L../goon_data/dist/Debug/GNU-Linux -lgoon_data -Wl,-rpath,../goon_camera/dist/Debug/GNU-Linux -L../goon_camera/dist/Debug/GNU-Linux -lgoon_camera -Wl,-rpath,../goon_retinal/dist/Debug/GNU-Linux -L../goon_retinal/dist/Debug/GNU-Linux -lgoon_retinal -Wl,-rpath,../goon_peripheral/dist/Debug/GNU-Linux -L../goon_peripheral/dist/Debug/GNU-Linux -lgoon_peripheral -Wl,-rpath,../goon_vision/dist/Debug/GNU-Linux -L../goon_vision/dist/Debug/GNU-Linux -lgoon_vision -Wl,-rpath,../monitor/dist/Debug/GNU-Linux -L../monitor/dist/Debug/GNU-Linux -lgoon_monitor -Wl,-rpath,../show/dist/Debug/GNU-Linux -L../show/dist/Debug/GNU-Linux -lgoon_show -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty -llog4cxx -lopencv_core -lopencv_highgui -lopencv_imgproc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_core/dist/Debug/GNU-Linux/libgoon_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_data/dist/Debug/GNU-Linux/libgoon_data.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_camera/dist/Debug/GNU-Linux/libgoon_camera.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_retinal/dist/Debug/GNU-Linux/libgoon_retinal.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_peripheral/dist/Debug/GNU-Linux/libgoon_peripheral.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../goon_vision/dist/Debug/GNU-Linux/libgoon_vision.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../monitor/dist/Debug/GNU-Linux/libgoon_monitor.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../show/dist/Debug/GNU-Linux/libgoon_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/look/GoonControl.o: src/goon/look/GoonControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_core/src -I../goon_features/src -I../goon_data/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_vision/src -I../monitor/src -I../show/src -I/usr/include -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/GoonControl.o src/goon/look/GoonControl.cpp

${OBJECTDIR}/src/goon/look/GoonShow.o: src/goon/look/GoonShow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_core/src -I../goon_features/src -I../goon_data/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_vision/src -I../monitor/src -I../show/src -I/usr/include -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/GoonShow.o src/goon/look/GoonShow.cpp

${OBJECTDIR}/src/goon/look/main.o: src/goon/look/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_core/src -I../goon_features/src -I../goon_data/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_vision/src -I../monitor/src -I../show/src -I/usr/include -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/main.o src/goon/look/main.cpp

${OBJECTDIR}/src/goon/look/test/TestBodies.o: src/goon/look/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_core/src -I../goon_features/src -I../goon_data/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_vision/src -I../monitor/src -I../show/src -I/usr/include -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/test/TestBodies.o src/goon/look/test/TestBodies.cpp

${OBJECTDIR}/src/goon/look/test/TestRegions.o: src/goon/look/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/look/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../goon_core/src -I../goon_features/src -I../goon_data/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_vision/src -I../monitor/src -I../show/src -I/usr/include -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/look/test/TestRegions.o src/goon/look/test/TestRegions.cpp

# Subprojects
.build-subprojects:
	cd ../goon_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_camera && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_retinal && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_peripheral && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_vision && ${MAKE}  -f Makefile CONF=Debug
	cd ../monitor && ${MAKE}  -f Makefile CONF=Debug
	cd ../show && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/look

# Subprojects
.clean-subprojects:
	cd ../goon_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_camera && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_retinal && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_peripheral && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_vision && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../monitor && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../show && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
