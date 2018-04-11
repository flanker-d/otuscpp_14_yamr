cmake_minimum_required(VERSION 3.2)

project(yamr VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(${PROJECT_SOURCE_DIR})

configure_file(version.h.in version.h)

add_library(yamr_file_splitter
        file_splitter/file_splitter.cpp
        )

add_library(yamr_mapper
        mapper/mapper.cpp
        )
target_link_libraries(yamr_mapper -lpthread)

add_library(yamr_reducer
        reducer/reducer.cpp
        )
target_link_libraries(yamr_reducer -lpthread)

add_executable(yamr
        main.cpp
        )
target_link_libraries(yamr yamr_file_splitter yamr_mapper yamr_reducer)

set_target_properties(yamr yamr_file_splitter yamr_mapper yamr_reducer PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS yamr
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
