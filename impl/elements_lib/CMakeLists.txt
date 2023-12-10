file(GLOB GAMEFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(elements_lib ${GAMEFILES})

target_include_directories(elements_lib PUBLIC ..)
target_link_libraries(elements_lib PUBLIC JamTemplateLib)

if (MSVC)
    target_compile_options(elements_lib PRIVATE "/W3")
    target_compile_options(elements_lib PRIVATE "/EHsc")
else ()
    target_compile_options(elements_lib PRIVATE "-Wall")
    target_compile_options(elements_lib PRIVATE "-Wextra")
endif ()

