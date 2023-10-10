
add_library(arduino-esp32 INTERFACE)

target_include_directories(arduino-esp32
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/arduino-esp32/cores/esp32
)

set(ESP_LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/arduino-esp32/libraries)

file(GLOB libs RELATIVE ${ESP_LIBDIR} ${ESP_LIBDIR}/*)
foreach (lib ${libs})
    if (IS_DIRECTORY ${ESP_LIBDIR}/${lib})
        target_include_directories(arduino-esp32
                INTERFACE ${ESP_LIBDIR}/${lib}/src)
    endif ()
endforeach ()

set(ESP_COREDIR ${CMAKE_CURRENT_SOURCE_DIR}/arduino-esp32/tools/sdk/esp32s3/include)

file(GLOB libs RELATIVE ${ESP_COREDIR} ${ESP_COREDIR}/*)
foreach (lib ${libs})
    if (IS_DIRECTORY ${ESP_COREDIR}/${lib})
        target_include_directories(arduino-esp32
                INTERFACE ${ESP_COREDIR}/${lib}/include)
    endif ()
endforeach ()
