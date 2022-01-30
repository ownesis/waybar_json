cmake_minimum_required(VERSION 3.0)

project(libwaybar_json VERSION 0.1.0 DESCRIPTION "C library for generate a json value for the custom-module of waybar")

set(SRCS
    waybar_json.c
    )

set(HDRS
    waybar_json.h
    )

add_library(waybar_json SHARED ${SRCS} ${HRDS})
set_target_properties(waybar_json PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(waybar_json PROPERTIES SOVERSION ${PROJECT_VERSION})

add_library(waybar_json_static STATIC ${SRCS} ${HRDS})
set_target_properties(waybar_json_static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(waybar_json_static PROPERTIES SOVERSION ${PROJECT_VERSION})

include(GNUInstallDirs)

install(TARGETS waybar_json
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS waybar_json_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES "waybar_json.h" DESTINATION "include/")

find_package(JSON-C CONFIG REQUIRED)

if(JSON-C_FOUND)
    target_link_libraries(waybar_json PRIVATE json-c::json-c)
    target_link_libraries(waybar_json_static PRIVATE json-c::json-c)
else()
    message(FATAL_ERROR "json-c not found")
endif()


