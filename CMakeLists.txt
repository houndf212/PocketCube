cmake_minimum_required(VERSION 3.16)

project(PocketCube LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (CMAKE_BUILD_TYPE STREQUAL "ASAN") 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g -DNDEBUG -Og")

endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -fno-exceptions -fno-rtti -fvisibility=hidden ")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto=auto")

set (APP_SOURCE
    hash_size_t_array.h
    rcDefine.h
    rcRotate.h
    rcRotate.cpp
    rcStatus.h
    rcStatus.cpp
    rcStatus_print.cpp
    rcGenStatus.h
    rcGenStatus.cpp
    rcStatusTree.h
    rcStatusTree.cpp
    rcMeetInMiddleSolver.h
    rcMeetInMiddleSolver.cpp
    pcDefine.h
    pcRotate.h
    pcRotate.cpp
    pcStatus.h
    pcStatus.cpp
    pcStatus_print.cpp
    pcStatusGen.h
    pcStatusGen.cpp
    pcStatusTree.h
    pcStatusTree.cpp
    pcIsoSolver.h
    pcIsoSolver.cpp
    pcMeetInMiddleSolver.h
    pcMeetInMiddleSolver.cpp
    pcIsoSolver_check.cpp
    main.cpp
    )

add_executable(pocket_cube ${APP_SOURCE})

include(GNUInstallDirs)
install(TARGETS pocket_cube 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
