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
LDLIBSOPTIONS=-Wl,-rpath,../utils/dist/Debug/GNU-Linux -L../utils/dist/Debug/GNU-Linux -lgoon_utils -Wl,-rpath,../features/dist/Debug/GNU-Linux -L../features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../vision_data/dist/Debug/GNU-Linux -L../vision_data/dist/Debug/GNU-Linux -lgoon_data -Wl,-rpath,../camera/dist/Debug/GNU-Linux -L../camera/dist/Debug/GNU-Linux -lgoon_camera -Wl,-rpath,../retinal_vision/dist/Debug/GNU-Linux -L../retinal_vision/dist/Debug/GNU-Linux -lgoon_retinal -Wl,-rpath,../peripheral_vision/dist/Debug/GNU-Linux -L../peripheral_vision/dist/Debug/GNU-Linux -lgoon_peripheral -Wl,-rpath,../monitor/dist/Debug/GNU-Linux -L../monitor/dist/Debug/GNU-Linux -lgoon_monitor -Wl,-rpath,../show/dist/Debug/GNU-Linux -L../show/dist/Debug/GNU-Linux -lgoon_show -llog4cxx -lopencv_core -lopencv_highgui -lopencv_imgproc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../utils/dist/Debug/GNU-Linux/libgoon_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../vision_data/dist/Debug/GNU-Linux/libgoon_data.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../camera/dist/Debug/GNU-Linux/libgoon_camera.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../retinal_vision/dist/Debug/GNU-Linux/libgoon_retinal.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../peripheral_vision/dist/Debug/GNU-Linux/libgoon_peripheral.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../monitor/dist/Debug/GNU-Linux/libgoon_monitor.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ../show/dist/Debug/GNU-Linux/libgoon_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/test/TestBodies.o: src/goon/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -I../features/src -I../vision_data/src -I../camera/src -I../retinal_vision/src -I../peripheral_vision/src -I../monitor/src -I../show/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/TestBodies.o src/goon/test/TestBodies.cpp

${OBJECTDIR}/src/goon/test/TestRegions.o: src/goon/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -I../features/src -I../vision_data/src -I../camera/src -I../retinal_vision/src -I../peripheral_vision/src -I../monitor/src -I../show/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/TestRegions.o src/goon/test/TestRegions.cpp

${OBJECTDIR}/src/goon/test/main.o: src/goon/test/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -I../features/src -I../vision_data/src -I../camera/src -I../retinal_vision/src -I../peripheral_vision/src -I../monitor/src -I../show/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/main.o src/goon/test/main.cpp

${OBJECTDIR}/src/goon/test/modules/Grab.o: src/goon/test/modules/Grab.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -I../features/src -I../vision_data/src -I../camera/src -I../retinal_vision/src -I../peripheral_vision/src -I../monitor/src -I../show/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/modules/Grab.o src/goon/test/modules/Grab.cpp

${OBJECTDIR}/src/goon/test/modules/See.o: src/goon/test/modules/See.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/test/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utils/src -I../features/src -I../vision_data/src -I../camera/src -I../retinal_vision/src -I../peripheral_vision/src -I../monitor/src -I../show/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/test/modules/See.o src/goon/test/modules/See.cpp

# Subprojects
.build-subprojects:
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug
	cd ../features && ${MAKE}  -f Makefile CONF=Debug
	cd ../vision_data && ${MAKE}  -f Makefile CONF=Debug
	cd ../camera && ${MAKE}  -f Makefile CONF=Debug
	cd ../retinal_vision && ${MAKE}  -f Makefile CONF=Debug
	cd ../peripheral_vision && ${MAKE}  -f Makefile CONF=Debug
	cd ../monitor && ${MAKE}  -f Makefile CONF=Debug
	cd ../show && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testGoon

# Subprojects
.clean-subprojects:
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../features && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../vision_data && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../camera && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../retinal_vision && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../peripheral_vision && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../monitor && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../show && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
