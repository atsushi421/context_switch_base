cmake_minimum_required(VERSION 3.8)
project(sample_app)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
add_executable(timer_node src/timer_node.cpp)
ament_target_dependencies(timer_node rclcpp)

# --- pmu_analyzer ---
# Please change the path to the pmu_analyzer.
include_directories(/home/atsushi/pmu_analyzer/include)
target_link_libraries(timer_node /home/atsushi/pmu_analyzer/lib/libpmuanalyzer.so)
set_target_properties(timer_node PROPERTIES
  INSTALL_RPATH "$ORIGIN/../lib:/home/atsushi/pmu_analyzer/lib"
)

install(TARGETS
  timer_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
