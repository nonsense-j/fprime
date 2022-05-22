set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ResCapPorts.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapController.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapController.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapExecutor.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ResCapExecutor.fpp"
)

find_library(LIBAUTPARSER libautparser "/home/nonsense/Projects/FinalTask/fprime/Ref/AutParser/build")
add_library(libautparser SHARED IMPORTED GLOBAL)
set_target_properties(libautparser PROPERTIES IMPORTED_LOCATION /home/nonsense/Projects/FinalTask/fprime/Ref/AutParser/build/libautparser.so)

set(MOD_DEPS
    libautparser
)

register_fprime_module()