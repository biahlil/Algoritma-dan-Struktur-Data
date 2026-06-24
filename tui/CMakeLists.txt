cmake_minimum_required(VERSION 3.10)
project(AlgoData)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ftxui REQUIRED)

# Example: New FTXUI TUI app
add_executable(tui_app tui_main.cpp 
../struct_pointer/line.cpp ../struct_pointer/circle.cpp line_module.cpp circle_module.cpp
stack_module.cpp queue_module.cpp 
../module-2-stack-and-queue-biahlil/stack.cpp 
../module-2-stack-and-queue-biahlil/queue.cpp
module_registry.cpp)
target_link_libraries(tui_app PRIVATE ftxui::screen ftxui::dom ftxui::component)
target_include_directories(tui_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../struct_pointer
    ${CMAKE_CURRENT_SOURCE_DIR}/../module-2-stack-and-queue-biahlil
)

