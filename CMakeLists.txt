cmake_minimum_required(VERSION 3.19) 

project(db48x LANGUAGES C CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2 QuickWidgets Widgets Multimedia)

# Set the target and platform
# TODO: control other flags depending on target
set(TARGET db50x)
set(COLOR color)
set(VARIANT dm32)
set(SDK dmcp5/dmcp)
set(PGM pgm5)
set(PGM_TARGET ${TARGET}.${PGM})
set(HELPFILE_NAME help/${TARGET}.md)
set(HELPINDEX_NAME help/${TARGET}.idx)

execute_process(COMMAND tools/build_id OUTPUT_VARIABLE BUILD_ID OUTPUT_STRIP_TRAILING_WHITESPACE)

qt_standard_project_setup()

# Add the sim subdirectory
add_subdirectory(recorder)
add_subdirectory(sim)
