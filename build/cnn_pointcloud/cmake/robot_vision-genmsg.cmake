# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "robot_vision: 8 messages, 0 services")

set(MSG_I_FLAGS "-Irobot_vision:/home/robo/ros/src/cnn_pointcloud/msg;-Irobot_vision:/home/robo/ros/devel/share/robot_vision/msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/noetic/share/actionlib_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(robot_vision_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" "sensor_msgs/PointCloud2:std_msgs/Header:sensor_msgs/PointField"
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" "robot_vision/SVMclassifierActionFeedback:robot_vision/SVMclassifierGoal:robot_vision/SVMclassifierResult:actionlib_msgs/GoalStatus:robot_vision/SVMclassifierActionGoal:robot_vision/SVMclassifierActionResult:actionlib_msgs/GoalID:robot_vision/SVMclassifierFeedback:std_msgs/Header"
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" "actionlib_msgs/GoalID:std_msgs/Header:robot_vision/SVMclassifierGoal"
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" "actionlib_msgs/GoalID:robot_vision/SVMclassifierResult:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" "actionlib_msgs/GoalID:robot_vision/SVMclassifierFeedback:std_msgs/Header:actionlib_msgs/GoalStatus"
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" ""
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" ""
)

get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" NAME_WE)
add_custom_target(_robot_vision_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "robot_vision" "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(robot_vision
  "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg"
  "${MSG_I_FLAGS}"
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)
_generate_msg_cpp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
)

### Generating Services

### Generating Module File
_generate_module_cpp(robot_vision
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(robot_vision_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(robot_vision_generate_messages robot_vision_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_cpp _robot_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_vision_gencpp)
add_dependencies(robot_vision_gencpp robot_vision_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_vision_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(robot_vision
  "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg"
  "${MSG_I_FLAGS}"
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)
_generate_msg_eus(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
)

### Generating Services

### Generating Module File
_generate_module_eus(robot_vision
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(robot_vision_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(robot_vision_generate_messages robot_vision_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_eus _robot_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_vision_geneus)
add_dependencies(robot_vision_geneus robot_vision_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_vision_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(robot_vision
  "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg"
  "${MSG_I_FLAGS}"
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)
_generate_msg_lisp(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
)

### Generating Services

### Generating Module File
_generate_module_lisp(robot_vision
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(robot_vision_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(robot_vision_generate_messages robot_vision_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_lisp _robot_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_vision_genlisp)
add_dependencies(robot_vision_genlisp robot_vision_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_vision_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg"
  "${MSG_I_FLAGS}"
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)
_generate_msg_nodejs(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
)

### Generating Services

### Generating Module File
_generate_module_nodejs(robot_vision
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(robot_vision_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(robot_vision_generate_messages robot_vision_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_nodejs _robot_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_vision_gennodejs)
add_dependencies(robot_vision_gennodejs robot_vision_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_vision_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(robot_vision
  "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointCloud2.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/sensor_msgs/cmake/../msg/PointField.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg"
  "${MSG_I_FLAGS}"
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalID.msg;/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/actionlib_msgs/cmake/../msg/GoalStatus.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)
_generate_msg_py(robot_vision
  "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
)

### Generating Services

### Generating Module File
_generate_module_py(robot_vision
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(robot_vision_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(robot_vision_generate_messages robot_vision_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robo/ros/src/cnn_pointcloud/msg/pointcloudVector.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierAction.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierActionFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierGoal.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierResult.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/robo/ros/devel/share/robot_vision/msg/SVMclassifierFeedback.msg" NAME_WE)
add_dependencies(robot_vision_generate_messages_py _robot_vision_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(robot_vision_genpy)
add_dependencies(robot_vision_genpy robot_vision_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS robot_vision_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/robot_vision
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(robot_vision_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET actionlib_msgs_generate_messages_cpp)
  add_dependencies(robot_vision_generate_messages_cpp actionlib_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/robot_vision
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(robot_vision_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET actionlib_msgs_generate_messages_eus)
  add_dependencies(robot_vision_generate_messages_eus actionlib_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/robot_vision
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(robot_vision_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET actionlib_msgs_generate_messages_lisp)
  add_dependencies(robot_vision_generate_messages_lisp actionlib_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/robot_vision
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(robot_vision_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET actionlib_msgs_generate_messages_nodejs)
  add_dependencies(robot_vision_generate_messages_nodejs actionlib_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/robot_vision
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(robot_vision_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET actionlib_msgs_generate_messages_py)
  add_dependencies(robot_vision_generate_messages_py actionlib_msgs_generate_messages_py)
endif()
