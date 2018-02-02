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
	${OBJECTDIR}/src/goon/features/Blob.o \
	${OBJECTDIR}/src/goon/features/Body.o \
	${OBJECTDIR}/src/goon/features/BodyOverlap.o \
	${OBJECTDIR}/src/goon/features/BodyOverlapFraction.o \
	${OBJECTDIR}/src/goon/features/ColorBlob.o \
	${OBJECTDIR}/src/goon/features/color/ColorSimilarity.o \
	${OBJECTDIR}/src/goon/features/color/HSVEssence.o \
	${OBJECTDIR}/src/goon/features/color/hsv_color.o \
	${OBJECTDIR}/src/goon/features/color/rgb_color.o \
	${OBJECTDIR}/src/goon/features/motion/TransMotion.o \
	${OBJECTDIR}/src/goon/features/nature/Nature.o \
	${OBJECTDIR}/src/goon/features/shape/shape.o \
	${OBJECTDIR}/src/goon/features/structure/Structure.o \
	${OBJECTDIR}/src/goon/features/structure/Structure2.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_features.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_features.${CND_DLIB_EXT}: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_features.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_features.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/goon/features/Blob.o: src/goon/features/Blob.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/Blob.o src/goon/features/Blob.cpp

${OBJECTDIR}/src/goon/features/Body.o: src/goon/features/Body.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/Body.o src/goon/features/Body.cpp

${OBJECTDIR}/src/goon/features/BodyOverlap.o: src/goon/features/BodyOverlap.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/BodyOverlap.o src/goon/features/BodyOverlap.cpp

${OBJECTDIR}/src/goon/features/BodyOverlapFraction.o: src/goon/features/BodyOverlapFraction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/BodyOverlapFraction.o src/goon/features/BodyOverlapFraction.cpp

${OBJECTDIR}/src/goon/features/ColorBlob.o: src/goon/features/ColorBlob.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/ColorBlob.o src/goon/features/ColorBlob.cpp

${OBJECTDIR}/src/goon/features/color/ColorSimilarity.o: src/goon/features/color/ColorSimilarity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/color
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/color/ColorSimilarity.o src/goon/features/color/ColorSimilarity.cpp

${OBJECTDIR}/src/goon/features/color/HSVEssence.o: src/goon/features/color/HSVEssence.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/color
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/color/HSVEssence.o src/goon/features/color/HSVEssence.cpp

${OBJECTDIR}/src/goon/features/color/hsv_color.o: src/goon/features/color/hsv_color.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/color
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/color/hsv_color.o src/goon/features/color/hsv_color.cpp

${OBJECTDIR}/src/goon/features/color/rgb_color.o: src/goon/features/color/rgb_color.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/color
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/color/rgb_color.o src/goon/features/color/rgb_color.cpp

${OBJECTDIR}/src/goon/features/motion/TransMotion.o: src/goon/features/motion/TransMotion.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/motion
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/motion/TransMotion.o src/goon/features/motion/TransMotion.cpp

${OBJECTDIR}/src/goon/features/nature/Nature.o: src/goon/features/nature/Nature.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/nature
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/nature/Nature.o src/goon/features/nature/Nature.cpp

${OBJECTDIR}/src/goon/features/shape/shape.o: src/goon/features/shape/shape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/shape
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/shape/shape.o src/goon/features/shape/shape.cpp

${OBJECTDIR}/src/goon/features/structure/Structure.o: src/goon/features/structure/Structure.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/structure
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/structure/Structure.o src/goon/features/structure/Structure.cpp

${OBJECTDIR}/src/goon/features/structure/Structure2.o: src/goon/features/structure/Structure2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/goon/features/structure
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/goon/features/structure/Structure2.o src/goon/features/structure/Structure2.cpp

# Subprojects
.build-subprojects:
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoon_features.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
