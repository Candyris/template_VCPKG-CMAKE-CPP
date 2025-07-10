cmake_minimum_required(VERSION 3.10)
project(main LANGUAGES CXX)

find_package(fmt CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# nlohmann-json is header-only, no find_package needed


add_executable(main helloworld.cpp)

target_link_libraries(main PRIVATE
    fmt::fmt
    imgui::imgui
    glfw
    glad::glad
)