cmake_minimum_required(VERSION 3.18)

project(Mega_calcApp)
#set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.3/mingw_64")
MATH(EXPR stack_size "1024 * 1024 * 1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/app")

find_package(Qt6 COMPONENTS Gui Qml Quick)
qt_add_executable(Mega_calcApp icon.rc "src/main.cpp"
        "src/ui files/Ui/ui.cpp" "src/ui files/Ui/ui.h"
        "src/ui files/Core/Core.cpp" "src/ui files/Core/Core.h"
        "src/classes/Solver/Solver.cpp" "src/classes/Solver/Solver.h"
        "src/classes/Parser/Parser.cpp" "src/classes/Parser/Parser.h"
        "src/classes/LongComplex/LongComplex.cpp" "src/classes/LongComplex/LongComplex.h"
        "src/classes/Mat2D/Mat2D_LN.cpp" "src/classes/Mat2D/Mat2D_LN.h"
        "src/classes/Mat2D/Mat2D_LC.cpp" "src/classes/Mat2D/Mat2D_LC.h"
        "src/classes/VecND/VecND_LC.cpp" "src/classes/VecND/VecND_LC.h"
        "src/classes/VecND/VecND_LN.cpp" "src/classes/VecND/VecND_LN.h"
        "src/classes/LongNumber/LongNumber.cpp" "src/classes/LongNumber/LongNumber.h"
        "src/classes/LongNumber/cringe class/cringe.h")

qt_add_resources(Mega_calcApp "configuration"
        PREFIX "/"
        FILES
        qtquickcontrols2.conf
        )

target_link_libraries(Mega_calcApp PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Qml
        )

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)