message(STATUS "> Found external/imgui directory")


if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
    execute_process(
        COMMAND git clone https://github.com/glfw/glfw.git glfw
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    message("> Cloning lodepng from remote")
else()
    message("> Lodepng already cloned, proceeding")
endif()

# OpenGL configuration
# search for OpenGL on the system
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
# add glfw subdirectory after having found OpenGL
add_subdirectory(glfw)
if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
endif()
set_property(TARGET glfw update_mappings  PROPERTY FOLDER "External/GLFW3")


set(target_name custom_imgui)

add_library(${target_name} STATIC "")

target_link_libraries(${target_name} ${OPENGL_LIBRARIES} glfw)

target_sources(${target_name}
    PRIVATE
        "imfilebrowser/imfilebrowser.h"

        "imgui_docking/imconfig.h"
        "imgui_docking/imgui.cpp"
        "imgui_docking/imgui.h"
        "imgui_docking/imgui_demo.cpp"
        "imgui_docking/imgui_draw.cpp"
        "imgui_docking/imgui_impl_glfw.cpp"
        "imgui_docking/imgui_impl_glfw.h"
        "imgui_docking/imgui_impl_opengl3.cpp"
        "imgui_docking/imgui_impl_opengl3.h"
        "imgui_docking/imgui_impl_opengl3_loader.h"
        "imgui_docking/imgui_internal.h"
        "imgui_docking/imgui_tables.cpp"
        "imgui_docking/imgui_widgets.cpp"
        "imgui_docking/imstb_rectpack.h"
        "imgui_docking/imstb_textedit.h"
        "imgui_docking/imstb_truetype.h"

        "imnodes/imnodes.cpp"
        "imnodes/imnodes.h"
        "imnodes/imnodes_internal.h"

        "implot/implot.cpp"
        "implot/implot.h"
        "implot/implot_demo.cpp"
        "implot/implot_items.cpp"
        "implot/implot_internal.h"
)

target_include_directories(${target_name}
    PUBLIC
        "imfilebrowser"
        "imgui_docking"
        "imnodes"
        "implot"
)

set_property(TARGET ${target_name} PROPERTY FOLDER "External/Custom_ImGUI")