cmake_minimum_required(VERSION 3.2)

project(yamr VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(${PROJECT_SOURCE_DIR})

configure_file(version.h.in version.h)

add_library(yamr_concurrent
        concurrent/queue.cpp
        )

add_library(yamr_file_ops
        file_ops/file_splitter.cpp
        file_ops/file_saver.cpp
        include/data_types.h
        )

add_library(yamr_mapper
        mapper/mapper.cpp
        mapper/imapper_alg.cpp
        mapper/alg/min_prefix_len.cpp
        )
target_link_libraries(yamr_mapper -lpthread)

add_library(yamr_reducer
        reducer/reducer.cpp
        reducer/ireducer_alg.cpp
        reducer/alg/min_prefix_len.cpp
        )
target_link_libraries(yamr_reducer yamr_concurrent yamr_file_ops -lpthread)

add_library(yamr_shuffler
        shuffler/shuffler.cpp
        shuffler/ishuffler.h
        )
target_link_libraries(yamr_shuffler yamr_mapper yamr_reducer -lpthread)

add_executable(yamr
        main.cpp
        )
target_link_libraries(yamr yamr_concurrent yamr_file_ops yamr_mapper yamr_reducer yamr_shuffler)

set_target_properties(yamr yamr_concurrent yamr_file_ops yamr_mapper yamr_reducer yamr_shuffler PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS yamr yamr_concurrent yamr_file_ops yamr_mapper yamr_reducer yamr_shuffler
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
