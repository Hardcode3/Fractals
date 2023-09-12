add_executable (main "main.cpp")
target_link_libraries (main PUBLIC fractals)

add_executable(gui "gui.cpp")
target_link_libraries(gui PUBLIC GuiLib)