cmake_minimum_required(VERSION 3.20)

project(Protocol VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FetchContent)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

set(OPENSSL_USE_STATIC_LIBS ON)
find_package(OpenSSL REQUIRED)

FetchContent_Declare(
    reflection
    GIT_REPOSITORY https://github.com/SculkCatalystMC/Reflection.git
    GIT_TAG main
)
FetchContent_MakeAvailable(reflection)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PROTOCOL_ENABLE_DETAIL_ERROR "Enable detailed error information" OFF)
option(PROTOCOL_DISABLE_CODEC "Disable codec features" OFF)
option(PROTOCOL_DISABLE_AUTHENTICATION "Disable authentication features" OFF)
option(PROTOCOL_DISABLE_CONNECTION "Disable connection features" OFF)

if(NOT PROTOCOL_DISABLE_CONNECTION AND PROTOCOL_DISABLE_CODEC)
    message(FATAL_ERROR
        "Invalid configuration: CONNECTION requires CODEC. "
        "Set PROTOCOL_DISABLE_CODEC=OFF or PROTOCOL_DISABLE_CONNECTION=ON."
    )
endif()

set(PROTOCOL_SOURCES)
set(PROTOCOL_INSTALL_INCLUDE_DIRS)

if(NOT PROTOCOL_DISABLE_CODEC)
    file(GLOB_RECURSE PROTOCOL_SOURCES_CODEC CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/sculk/protocol/codec/*.cpp"
    )
    list(APPEND PROTOCOL_SOURCES ${PROTOCOL_SOURCES_CODEC})
    list(APPEND PROTOCOL_INSTALL_INCLUDE_DIRS "sculk/protocol/codec")
endif()

if(NOT PROTOCOL_DISABLE_AUTHENTICATION)
    file(GLOB_RECURSE PROTOCOL_SOURCES_AUTH CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/sculk/protocol/auth/*.cpp"
    )
    list(APPEND PROTOCOL_SOURCES ${PROTOCOL_SOURCES_AUTH})
    list(APPEND PROTOCOL_INSTALL_INCLUDE_DIRS "sculk/protocol/auth")
endif()

if(NOT PROTOCOL_DISABLE_CONNECTION)
    file(GLOB_RECURSE PROTOCOL_SOURCES_CONNECTION CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/sculk/protocol/connection/*.cpp"
    )
    list(APPEND PROTOCOL_SOURCES ${PROTOCOL_SOURCES_CONNECTION})
    list(APPEND PROTOCOL_INSTALL_INCLUDE_DIRS "sculk/protocol/connection")
endif()

add_library(Protocol STATIC)

if(PROTOCOL_SOURCES)
    target_sources(Protocol PRIVATE ${PROTOCOL_SOURCES})
endif()

add_library(Protocol::Protocol ALIAS Protocol)

set_target_properties(Protocol PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    LINKER_LANGUAGE CXX
)

target_compile_features(Protocol PUBLIC cxx_std_23)
target_link_libraries(Protocol PRIVATE reflection::reflection OpenSSL::Crypto)

target_include_directories(Protocol PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(PROTOCOL_ENABLE_DETAIL_ERROR)
    target_compile_definitions(Protocol PRIVATE SCULK_PROTOCOL_DETAIL_ERROR)
endif()

if(MSVC)
    target_compile_options(Protocol PRIVATE
        /W4
        /utf-8
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:RelWithDebInfo>:/O2>
    )
    target_compile_definitions(Protocol PRIVATE
        UNICODE
        NOMINMAX
    )
else()
    target_compile_options(Protocol PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:RelWithDebInfo>:-O3>
    )
endif()

install(TARGETS Protocol
    EXPORT ProtocolTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

foreach(PROTOCOL_INCLUDE_DIR ${PROTOCOL_INSTALL_INCLUDE_DIRS})
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROTOCOL_INCLUDE_DIR}/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROTOCOL_INCLUDE_DIR}
        OPTIONAL
    )
endforeach()

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/ProtocolConfig.cmake.in
    ${PROJECT_BINARY_DIR}/ProtocolConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Protocol
)

write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/ProtocolConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT ProtocolTargets
    FILE ProtocolTargets.cmake
    NAMESPACE Protocol::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Protocol
)

install(FILES
    ${PROJECT_BINARY_DIR}/ProtocolConfig.cmake
    ${PROJECT_BINARY_DIR}/ProtocolConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Protocol
)