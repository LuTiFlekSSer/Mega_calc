cmake_minimum_required(VERSION 3.18)

project(Mega_calcApp)
#set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.4.1/mingw_64")

#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/app")

find_package(Qt6 COMPONENTS Gui Qml Quick)
qt_add_executable(Mega_calcApp "src/main.cpp"
        "src/ui files/ui.cpp" "src/ui files/ui.h"
        "src/classes/LongComplex/LongComplex.cpp" "src/classes/LongComplex/LongComplex.h"
        "src/classes/Mat2D/Mat2D.cpp" "src/classes/Mat2D/Mat2D.h"
        "src/classes/VecND/VecND.cpp" "src/classes/VecND/VecND.h"
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