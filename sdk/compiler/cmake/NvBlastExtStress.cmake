#
# Build NvBlastExtStress Common
#

SET(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/common)

SET(STRESS_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extensions/stress/include)
SET(STRESS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/extensions/stress/source)

SET(EXT_COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/extensions/common/source)
SET(EXT_COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extensions/common/include)

FIND_PACKAGE(PxSharedSDK ${PM_physxsdk_VERSION} REQUIRED)
FIND_PACKAGE(PhysXSDK ${PM_pxshared_VERSION} REQUIRED)

# Include here after the directories are defined so that the platform specific file can use the variables.
include(${PROJECT_CMAKE_FILES_DIR}/${TARGET_BUILD_PLATFORM}/NvBlastExtStress.cmake OPTIONAL)


SET(COMMON_FILES
	${BLASTEXTSTRESS_PLATFORM_COMMON_FILES}
	
	${COMMON_SOURCE_DIR}/NvBlastAssert.cpp
	${COMMON_SOURCE_DIR}/NvBlastAssert.h
)

SET(STRESS_SOURCE_FILES
	${STRESS_SOURCE_DIR}/NvBlastExtStressSolver.cpp
)

SET(STRESS_PUBLIC_FILES
	${STRESS_INCLUDE_DIR}/NvBlastExtStressSolver.h
)

ADD_LIBRARY(NvBlastExtStress SHARED 
	${COMMON_FILES}
	${STRESS_SOURCE_FILES}
	${STRESS_PUBLIC_FILES}
)

SOURCE_GROUP("common" FILES ${COMMON_FILES})
SOURCE_GROUP("public" FILES ${STRESS_PUBLIC_FILES}) 
SOURCE_GROUP("src" FILES ${STRESS_SOURCE_FILES})

# Target specific compile options

TARGET_INCLUDE_DIRECTORIES(NvBlastExtStress 
	PUBLIC ${STRESS_INCLUDE_DIR}

	PRIVATE ${BLASTEXTSTRESS_PLATFORM_INCLUDES}

	PRIVATE ${PROJECT_SOURCE_DIR}/common
	PRIVATE ${PROJECT_SOURCE_DIR}/lowlevel/include
	PRIVATE ${PROJECT_SOURCE_DIR}/lowlevel/source

	PRIVATE ${COMMON_SOURCE_DIR}

	PRIVATE ${PXSHAREDSDK_INCLUDE_DIRS}
	PRIVATE ${PHYSXSDK_INCLUDE_DIRS}
)

SET(BLASTEXTSTRESS_COMPILE_DEFS
	# Common to all configurations
	${BLAST_SLN_COMPILE_DEFS};_CONSOLE;
	
	$<$<CONFIG:debug>:${BLAST_SLN_DEBUG_COMPILE_DEFS}>
	$<$<CONFIG:checked>:${BLAST_SLN_CHECKED_COMPILE_DEFS}>
	$<$<CONFIG:profile>:${BLAST_SLN_PROFILE_COMPILE_DEFS}>
	$<$<CONFIG:release>:${BLAST_SLN_RELEASE_COMPILE_DEFS}>
)

TARGET_COMPILE_DEFINITIONS(NvBlastExtStress
	PUBLIC CAPNP_LITE=1
	PRIVATE ${BLASTEXTSTRESS_COMPILE_DEFS}
)

# Warning disables for Capn Proto
TARGET_COMPILE_OPTIONS(NvBlastExtStress
	PRIVATE ${BLASTEXTSTRESS_PLATFORM_COMPILE_OPTIONS}
)

SET_TARGET_PROPERTIES(NvBlastExtStress PROPERTIES 
	PDB_NAME_DEBUG "NvBlastExtStress${CMAKE_DEBUG_POSTFIX}"
	PDB_NAME_CHECKED "NvBlastExtStress${CMAKE_CHECKED_POSTFIX}"
	PDB_NAME_PROFILE "NvBlastExtStress${CMAKE_PROFILE_POSTFIX}"
	PDB_NAME_RELEASE "NvBlastExtStress${CMAKE_RELEASE_POSTFIX}"
)

# Do final direct sets after the target has been defined
TARGET_LINK_LIBRARIES(NvBlastExtStress 
	PUBLIC NvBlast NvBlastGlobals
	PUBLIC ${BLASTEXT_PLATFORM_LINKED_LIBS}
)
