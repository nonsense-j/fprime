set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ResCapStart.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapStart.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapMove.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapMove.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCap_attack.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCap_attack.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCap_attack_over.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCap_attack_over.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCap_take_photo.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCap_take_photo.fpp"
)

find_library(LIBROSCPP libroscpp "/opt/ros/noetic/lib")
add_library(libroscpp SHARED IMPORTED GLOBAL)
set_target_properties(libroscpp PROPERTIES IMPORTED_LOCATION /opt/ros/noetic/lib/libroscpp.so)

set(MOD_DEPS
    libroscpp
)

include_directories(include
    /opt/ros/noetic/include
)

link_directories(
    /opt/ros/noetic/lib
)

register_fprime_module()