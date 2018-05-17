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
	${OBJECTDIR}/src/goon/main/GoonControl.o \
	${OBJECTDIR}/src/goon/main/GoonVersion.o \
	${OBJECTDIR}/src/goon/main/main.o \
	${OBJECTDIR}/src/goon/main/test/Test.o \
	${OBJECTDIR}/src/goon/main/test/TestBodies.o \
	${OBJECTDIR}/src/goon/main/test/TestImage.o \
	${OBJECTDIR}/src/goon/main/test/TestObjects.o \
	${OBJECTDIR}/src/goon/main/test/TestRegions.o


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
LDLIBSOPTIONS=-Wl,-rpath,../goon_core/dist/Debug/GNU-Linux -L../goon_core/dist/Debug/GNU-Linux -lgoon_core -Wl,-rpath,../goon_data/dist/Debug/GNU-Linux -L../goon_data/dist/Debug/GNU-Linux -lgoon_data -Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../goon_camera/dist/Debug/GNU-Linux -L../goon_camera/dist/Debug/GNU-Linux -lgoon_camera -Wl,-rpath,../goon_retinal/dist/Debug/GNU-Linux -L../goon_retinal/dist/Debug/GNU-Linux -lgoon_retinal -Wl,-rpath,../goon_peripheral/dist/Debug/GNU-Linux -L../goon_peripheral/dist/Debug/GNU-Linux -lgoon_peripheral -Wl,-rpath,../goon_cortex/dist/Debug/GNU-Linux -L../goon_cortex/dist/Debug/GNU-Linux -lgoon_cortex -Wl,-rpath,../goon_vision/dist/Debug/GNU-Linux -L../goon_vision/dist/Debug/GNU-Linux -lgoon_vision -Wl,-rpath,../goon_coms2/dist/Debug/GNU-Linux -L../goon_coms2/dist/Debug/GNU-Linux -lgoon_coms2 -Wl,-rpath,../goon_show/dist/Debug/GNU-Linux -L../goon_show/dist/Debug/GNU-Linux -lgoon_show -Wl,-rpath,../../tron2/tron2_coms/dist/Debug/GNU-Linux -L../../tron2/tron2_coms/dist/Debug/GNU-Linux -ltron2_coms -Wl,-rpath,../../tron2/tron2_robot/dist/Debug/GNU-Linux -L../../tron2/tron2_robot/dist/Debug/GNU-Linux -ltron2_robot -Wl,-rpath,../../tron2/tron2_tivy/dist/Debug/GNU-Linux -L../../tron2/tron2_tivy/dist/Debug/GNU-Linux -ltron2_tivy -Wl,-rpath,../../tron/tron_control/dist/Debug/GNU-Linux -L../../tron/tron_control/dist/Debug/GNU-Linux -ltron_control -Wl,-rpath,../../tron/tron_cv/dist/Debug/GNU-Linux -L../../tron/tron_cv/dist/Debug/GNU-Linux -ltron_cv -Wl,-rpath,../../tron/tron_display/dist/Debug/GNU-Linux -L../../tron/tron_display/dist/Debug/GNU-Linux -ltron_display -Wl,-rpath,../../tron/tron_math/dist/Debug/GNU-Linux -L../../tron/tron_math/dist/Debug/GNU-Linux -ltron_math -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util -Wl,-rpath,../../tron/tron_wire/dist/Debug/GNU-Linux -L../../tron/tron_wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/tron_wire2/dist/Debug/GNU-Linux -L../../tron/tron_wire2/dist/Debug/GNU-Linux -ltron_wire2 -Wl,-rpath,../../tron/tron_tools/dist/Debug/GNU-Linux -L../../tron/tron_tools/dist/Debug/GNU-Linux -ltron_tools -llog4cxx -lopencv_core -lopencv_highgui -lopencv_imgproc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_core/dist/Debug/GNU-Linux/libgoon_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_data/dist/Debug/GNU-Linux/libgoon_data.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_features/dist/Debug/GNU-Linux/libgoon_features.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_camera/dist/Debug/GNU-Linux/libgoon_camera.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_retinal/dist/Debug/GNU-Linux/libgoon_retinal.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_peripheral/dist/Debug/GNU-Linux/libgoon_peripheral.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_cortex/dist/Debug/GNU-Linux/libgoon_cortex.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_vision/dist/Debug/GNU-Linux/libgoon_vision.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_coms2/dist/Debug/GNU-Linux/libgoon_coms2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_show/dist/Debug/GNU-Linux/libgoon_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron2/tron2_coms/dist/Debug/GNU-Linux/libtron2_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron2/tron2_robot/dist/Debug/GNU-Linux/libtron2_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron2/tron2_tivy/dist/Debug/GNU-Linux/libtron2_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_control/dist/Debug/GNU-Linux/libtron_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_cv/dist/Debug/GNU-Linux/libtron_cv.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_display/dist/Debug/GNU-Linux/libtron_display.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_math/dist/Debug/GNU-Linux/libtron_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tron_tools/dist/Debug/GNU-Linux/libtron_tools.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/main/GoonControl.o: src/goon/main/GoonControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/GoonControl.o src/goon/main/GoonControl.cpp

${OBJECTDIR}/src/goon/main/GoonVersion.o: src/goon/main/GoonVersion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/GoonVersion.o src/goon/main/GoonVersion.cpp

${OBJECTDIR}/src/goon/main/main.o: src/goon/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/main.o src/goon/main/main.cpp

${OBJECTDIR}/src/goon/main/test/Test.o: src/goon/main/test/Test.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/Test.o src/goon/main/test/Test.cpp

${OBJECTDIR}/src/goon/main/test/TestBodies.o: src/goon/main/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestBodies.o src/goon/main/test/TestBodies.cpp

${OBJECTDIR}/src/goon/main/test/TestImage.o: src/goon/main/test/TestImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestImage.o src/goon/main/test/TestImage.cpp

${OBJECTDIR}/src/goon/main/test/TestObjects.o: src/goon/main/test/TestObjects.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestObjects.o src/goon/main/test/TestObjects.cpp

${OBJECTDIR}/src/goon/main/test/TestRegions.o: src/goon/main/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms2/src -I../goon_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_cv/src -I../../tron/tron_display/src -I../../tron/tron_math/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestRegions.o src/goon/main/test/TestRegions.cpp

# Subprojects
.build-subprojects:
	cd ../goon_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_camera && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_retinal && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_peripheral && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_cortex && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_vision && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_coms2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_show && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_tivy && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_cv && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_display && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_wire2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_tools && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon

# Subprojects
.clean-subprojects:
	cd ../goon_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_data && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_features && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_camera && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_retinal && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_peripheral && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_cortex && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_vision && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_coms2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_show && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_tivy && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_cv && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_display && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_wire2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_tools && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
