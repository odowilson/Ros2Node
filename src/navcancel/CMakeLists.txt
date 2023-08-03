cmake_minimum_required(VERSION 3.8)
project(navcancel)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav2_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp_action REQUIRED)



add_executable(navcancel src/navcancel.cpp)

target_include_directories(navcancel PUBLIC ...)
target_link_libraries(navcancel ${rclcpp_LIBRARIES})
target_link_libraries(navcancel ${rclcpp_action_LIBRARIES})

target_include_directories(navcancel PUBLIC
        ${rclcpp_INCLUDE_DIRS}
        ${nav2_msgs_INCLUDE_DIRS}
        ${rclcpp_action_INCLUDE_DIRS}
)

ament_target_dependencies(navcancel rclcpp nav2_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
        navcancel
        DESTINATION lib/navcancel
)

ament_package()
