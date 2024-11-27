# Define the executable
set(SOURCES
    sim-main.cpp
    sim-window.cpp
    sim-screen.cpp
    sim-rpl.cpp
    dmcp.cpp
    ../fonts/EditorFont.cc
    ../fonts/HelpFont.cc
    ../fonts/ReducedFont.cc
    ../fonts/StackFont.cc
    ../src/algebraic.cc
    ../src/arithmetic.cc
    ../src/array.cc
    ../src/bignum.cc
    ../src/catalog.cc
    ../src/characters.cc
    ../src/command.cc
    ../src/comment.cc
    ../src/compare.cc
    ../src/complex.cc
    ../src/conditionals.cc
    ../src/constants.cc
    ../src/custom.cc
    ../src/datetime.cc
    ../src/decimal.cc
    ../src/dmcp/main.cc
    ../src/dmcp/sysmenu.cc
    ../src/dmcp/target.cc
    ../src/equations.cc
    ../src/expression.cc
    ../src/file.cc
    ../src/files.cc
    ../src/font.cc
    ../src/fraction.cc
    ../src/functions.cc
    ../src/graphics.cc
    ../src/grob.cc
    ../src/hwfp.cc
    ../src/integer.cc
    ../src/integrate.cc
    ../src/library.cc
    ../src/list.cc
    ../src/locals.cc
    ../src/logical.cc
    ../src/loops.cc
    ../src/menu.cc
    ../src/object.cc
    ../src/plot.cc
    ../src/polynomial.cc
    ../src/program.cc
    ../src/renderer.cc
    ../src/runtime.cc
    ../src/settings.cc
    ../src/solve.cc
    ../src/stack.cc
    ../src/stats.cc
    ../src/symbol.cc
    ../src/tag.cc
    ../src/tests.cc
    ../src/text.cc
    ../src/unit.cc
    ../src/user_interface.cc
    ../src/util.cc
    ../src/variables.cc
    sim-window.h
    sim-screen.h
    sim-rpl.h
    android/AndroidManifest.xml
)

qt6_add_executable(${TARGET} ${SOURCES})

qt6_add_ui(${TARGET} SOURCES sim-window.ui)

set_property(TARGET ${TARGET} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
             ${CMAKE_CURRENT_SOURCE_DIR}/android)

target_include_directories(${TARGET} PRIVATE ../src/${VARIANT} ../src/dmcp ../src ${SDK} ./)

target_link_libraries(${TARGET} PRIVATE recorder)

string(TOUPPER ${VARIANT} VARIANT_UPPER)
target_compile_definitions(${TARGET} PRIVATE DEFINES_${VARIANT} ${VARIANT_UPPER} CONFIG_FIXED_BASED_OBJECTS DEOPTIMIZE_CATALOG SIMULATOR)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET} PRIVATE DEBUG)
endif()
target_compile_definitions(${TARGET} PRIVATE __packed= USE_QT)
if(APPLE)
    target_compile_definitions(${TARGET} PRIVATE _WCHAR_T_DEFINED)
endif()
target_compile_definitions(${TARGET} PRIVATE HELPFILE_NAME=\"${HELPFILE_NAME}\")
target_compile_definitions(${TARGET} PRIVATE HELPINDEX_NAME=\"${HELPINDEX_NAME}\")
if(COLOR)
    target_compile_definitions(${TARGET} PRIVATE CONFIG_COLOR)
endif()

# Platform-specific libraries and flags
if(WIN32)
    target_link_libraries(${TARGET} PRIVATE setupapi)
elseif(ANDROID)
    # No additional libraries for Android
elseif(FREEBSD)
    target_link_libraries(${TARGET} PRIVATE thr iconv)
elseif(APPLE)
    target_link_libraries(${TARGET} PRIVATE "-framework CoreFoundation" "-framework IOKit")
    target_compile_options(${TARGET} PRIVATE -fsanitize=address)
    target_link_libraries(${TARGET} PRIVATE -fsanitize=address)
endif()

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TARGET} PRIVATE -Wno-unknown-pragmas)
endif()

target_link_libraries(${TARGET} PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::QuickControls2 Qt6::QuickWidgets Qt6::Widgets Qt6::Multimedia)

# Add UI forms and resources
qt6_add_resources(RESOURCE_FILES sim.qrc)

file(GLOB_RECURSE HELP_FILES ${PROJECT_SOURCE_DIR}/help/*)
file(GLOB_RECURSE CONFIG_FILES ${PROJECT_SOURCE_DIR}/config/*)

qt_add_resources(${TARGET} "help" PREFIX "/help" BASE ${PROJECT_SOURCE_DIR}/help FILES ${HELP_FILES})
qt_add_resources(${TARGET} "config" PREFIX "/config" BASE ${PROJECT_SOURCE_DIR}/config FILES ${CONFIG_FILES})

target_sources(${TARGET} PRIVATE ${RESOURCE_FILES})

install(TARGETS ${TARGET}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${TARGET}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})