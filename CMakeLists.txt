cmake_minimum_required(VERSION 3.25)
project(todo VERSION 2.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_executable(todo ./src/ui/cli/cli.cc)
target_compile_options(todo PRIVATE -O3 -DNDEBUG -Os -Ofast -Og -s -march=native -masm=intel -flto=auto -funroll-all-loops)

add_executable(todo-gui ./src/ui/gui/gui.cc)
if(WIN32)
target_compile_options(todo-gui PRIVATE -O3 -DNDEBUG -Os -Ofast -Og -s -march=native -masm=intel -flto=auto -funroll-all-loops -mwindows)
else()
target_compile_options(todo-gui PRIVATE -O3 -DNDEBUG -Os -Ofast -Og -s -march=native -masm=intel -flto=auto -funroll-all-loops)
endif()
target_link_libraries(todo-gui PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(todo-gui PRIVATE ${GTKMM_INCLUDE_DIRS})

if(UNIX)
install(TARGETS todo todo-gui DESTINATION /usr/bin/)
install(FILES todo_gui.desktop DESTINATION /usr/share/applications/)
endif()
