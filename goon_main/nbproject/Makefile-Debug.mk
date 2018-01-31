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
LDLIBSOPTIONS=-Wl,-rpath,../goon_core/dist/Debug/GNU-Linux -L../goon_core/dist/Debug/GNU-Linux -lgoon_core -Wl,-rpath,../goon_data/dist/Debug/GNU-Linux -L../goon_data/dist/Debug/GNU-Linux -lgoon_data -Wl,-rpath,../goon_features/dist/Debug/GNU-Linux -L../goon_features/dist/Debug/GNU-Linux -lgoon_features -Wl,-rpath,../goon_camera/dist/Debug/GNU-Linux -L../goon_camera/dist/Debug/GNU-Linux -lgoon_camera -Wl,-rpath,../goon_retinal/dist/Debug/GNU-Linux -L../goon_retinal/dist/Debug/GNU-Linux -lgoon_retinal -Wl,-rpath,../goon_peripheral/dist/Debug/GNU-Linux -L../goon_peripheral/dist/Debug/GNU-Linux -lgoon_peripheral -Wl,-rpath,../goon_cortex/dist/Debug/GNU-Linux -L../goon_cortex/dist/Debug/GNU-Linux -lgoon_cortex -Wl,-rpath,../goon_vision/dist/Debug/GNU-Linux -L../goon_vision/dist/Debug/GNU-Linux -lgoon_vision -Wl,-rpath,../goon_coms/dist/Debug/GNU-Linux -L../goon_coms/dist/Debug/GNU-Linux -lgoon_coms -Wl,-rpath,../goon_show/dist/Debug/GNU-Linux -L../goon_show/dist/Debug/GNU-Linux -lgoon_show -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty -Wl,-rpath,../../tron/nety/dist/Debug/GNU-Linux -L../../tron/nety/dist/Debug/GNU-Linux -ltron_nety -Wl,-rpath,../../tron/talky/dist/Debug/GNU-Linux -L../../tron/talky/dist/Debug/GNU-Linux -ltron_talky -Wl,-rpath,../../tron/comy/dist/Debug/GNU-Linux -L../../tron/comy/dist/Debug/GNU-Linux -ltron_comy -Wl,-rpath,../../tron/tivy/dist/Debug/GNU-Linux -L../../tron/tivy/dist/Debug/GNU-Linux -ltron_tivy -llog4cxx -lopencv_core -lopencv_highgui -lopencv_imgproc

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

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_coms/dist/Debug/GNU-Linux/libgoon_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../goon_show/dist/Debug/GNU-Linux/libgoon_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/nety/dist/Debug/GNU-Linux/libtron_nety.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/talky/dist/Debug/GNU-Linux/libtron_talky.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/comy/dist/Debug/GNU-Linux/libtron_comy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ../../tron/tivy/dist/Debug/GNU-Linux/libtron_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/goon ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/goon/main/GoonControl.o: src/goon/main/GoonControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/GoonControl.o src/goon/main/GoonControl.cpp

${OBJECTDIR}/src/goon/main/GoonVersion.o: src/goon/main/GoonVersion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/GoonVersion.o src/goon/main/GoonVersion.cpp

${OBJECTDIR}/src/goon/main/main.o: src/goon/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/main.o src/goon/main/main.cpp

${OBJECTDIR}/src/goon/main/test/Test.o: src/goon/main/test/Test.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/Test.o src/goon/main/test/Test.cpp

${OBJECTDIR}/src/goon/main/test/TestBodies.o: src/goon/main/test/TestBodies.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestBodies.o src/goon/main/test/TestBodies.cpp

${OBJECTDIR}/src/goon/main/test/TestImage.o: src/goon/main/test/TestImage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestImage.o src/goon/main/test/TestImage.cpp

${OBJECTDIR}/src/goon/main/test/TestObjects.o: src/goon/main/test/TestObjects.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestObjects.o src/goon/main/test/TestObjects.cpp

${OBJECTDIR}/src/goon/main/test/TestRegions.o: src/goon/main/test/TestRegions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/main/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -I../goon_core/src -I../goon_data/src -I../goon_features/src -I../goon_camera/src -I../goon_retinal/src -I../goon_peripheral/src -I../goon_cortex/src -I../goon_vision/src -I../goon_coms/src -I../goon_show/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/tivy/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/comy/src -I/usr/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/main/test/TestRegions.o src/goon/main/test/TestRegions.cpp

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
	cd ../goon_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../goon_show && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug

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
	cd ../goon_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../goon_show && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
