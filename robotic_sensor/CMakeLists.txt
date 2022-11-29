cmake_minimum_required(VERSION 3.8)
project(robotic_sensor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SensorData.msg"
  "msg/SensorDataPoints.msg"
  "srv/RoboticSensor.srv"
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(server src/sensor_service.cpp)
ament_target_dependencies(server
  rclcpp )

#add_executable(server1 src/sensor_service1.cpp)
#ament_target_dependencies(server
#  rclcpp )
   
add_executable(client src/sensor_client.cpp)
ament_target_dependencies(client
  rclcpp )

install(TARGETS
  server
#  server1
  client
  DESTINATION lib/${PROJECT_NAME})

rosidl_target_interfaces(client
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(server
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
