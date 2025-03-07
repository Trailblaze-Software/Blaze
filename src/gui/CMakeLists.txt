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

target_sources(
  ${GUI_3D_EXE_NAME} PRIVATE main_3d.cpp main_3d_window.hpp main_3d_window.cpp
                             main_3d_window.ui gl_widget.hpp gl_widget.cpp)
