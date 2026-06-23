target_sources(
  ${GUI_EXE_NAME}
  PRIVATE main_window.ui
          main.cpp
          main_window.cpp
          progress_box.hpp
          main_window.hpp
          progress_box.cpp
          progress_box.ui
          config_editor.hpp
          config_editor.cpp
          config_editor.ui)

if(BLAZE_BUILD_3D_GUI)
  target_sources(
    ${GUI_3D_EXE_NAME}
    PRIVATE main_3d.cpp
            main_3d_window.hpp
            main_3d_window.cpp
            layer_renderer.hpp
            layer_renderer.cpp
            main_3d_window.ui
            point_cloud_framebuffer.hpp
            point_cloud_framebuffer.cpp
            point_cloud_gl.hpp
            point_cloud_gl.cpp
            gl_check.hpp
            gl_check.cpp
            gl_widget.hpp
            gl_widget.cpp
            layer.hpp)

  target_sources(${UNIT_TESTS_NAME} PRIVATE tests/test_camera.cpp)
  target_link_libraries(${UNIT_TESTS_NAME} PRIVATE Qt6::Gui)

  if(APPLE)
    # Plain executables need an explicit rpath to Qt's frameworks directory so
    # ctest can launch unit_tests (Library not loaded: @rpath/QtGui.framework).
    get_filename_component(_blaze_qt_prefix "${Qt6_DIR}/../../.." ABSOLUTE)
    set_target_properties(
      ${UNIT_TESTS_NAME} PROPERTIES INSTALL_RPATH "${_blaze_qt_prefix}/lib"
                                    MACOSX_RPATH ON)
  endif()
endif()
