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
            gl_widget.hpp
            gl_widget.cpp
            layer.hpp)
endif()
