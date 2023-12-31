cmake_minimum_required(VERSION 3.21)
message("Using toolchain file ${CMAKE_TOOLCHAIN_FILE}.")

########################################################################################################################
## Define project
########################################################################################################################
project(
        DynamicCharacterAppearance
        VERSION 1.0.0
        DESCRIPTION ""
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

include(GNUInstallDirs)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.rc
        @ONLY)

set(sources
        src/GameAPI/GameActor.cpp
        src/GameAPI/GameColor.cpp
        src/GameAPI/GameSex.cpp
        src/GameAPI/RGBColor.cpp
	    src/Papyrus/Papyrus.cpp
	    src/Papyrus/Script.h
        src/Serialization/Manager.cpp
        src/Threading/Components/Component.cpp
        src/Threading/Components/FallbackColorComponent.cpp
        src/Threading/Components/HealthIndicatorColorComponent.cpp
        src/Threading/Components/MagickaIndicatorColorComponent.cpp
        src/Threading/Components/RainbowColorComponent.cpp
        src/Threading/Components/StaminaIndicatorColorComponent.cpp
        src/Threading/Components/StatIndicatorColorComponent.cpp
        src/Threading/ActorThread.cpp
        src/Threading/ColorRecordThread.cpp
        src/Threading/ColorThread.cpp
        src/Threading/HairColorThread.cpp
        src/Threading/OverlayType.cpp
        src/Threading/OverlayColorThread.cpp
        src/Threading/SubThread.cpp
        src/Threading/SubThreadType.cpp
        src/Threading/ThreadManager.cpp
        src/Util/FormTable.cpp
        src/Main.cpp

        ${CMAKE_CURRENT_BINARY_DIR}/version.rc)

source_group(
        TREE ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        ${sources})

########################################################################################################################
## Configure target DLL
########################################################################################################################
find_package(nlohmann_json REQUIRED)
find_package(CommonLibSSE CONFIG REQUIRED)
find_package(ryml CONFIG REQUIRED)
find_path(ARTICUNO_INCLUDE_DIRS "articuno/articuno.h")

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${sources})
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_include_directories(${PROJECT_NAME}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
        $<INSTALL_INTERFACE:src>
        ${ARTICUNO_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ryml::ryml
        nlohmann_json::nlohmann_json)

target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        src/PCH.h)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/Sample"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(TARGETS ${PROJECT_NAME}
        DESTINATION "${CMAKE_INSTALL_LIBDIR}")