set(target_name GuiLib)

set(IMGUI_APP_SOURCE
    "${PROJECT_SOURCE_DIR}/src/gui/app/app.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/app/notifications.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/app/window_base.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/app/win_fractal_processing.cpp"
    
    "${PROJECT_SOURCE_DIR}/src/gui/utils/help_marker.cpp"
    "${PROJECT_SOURCE_DIR}/src/gui/utils/padding.cpp"
)
set(IMGUI_APP_HEADER
    "${PROJECT_SOURCE_DIR}/include/gui/app/app.hpp"
    "${PROJECT_SOURCE_DIR}/include/gui/app/notifications.hpp"
    "${PROJECT_SOURCE_DIR}/include/gui/app/window_base.hpp"
    "${PROJECT_SOURCE_DIR}/include/gui/app/win_fractal_processing.hpp"

    "${PROJECT_SOURCE_DIR}/include/gui/utils/help_marker.hpp"
    "${PROJECT_SOURCE_DIR}/include/gui/utils/padding.hpp"
)
source_group("App/HEADERS" FILES ${FILE_LOADER_HEADER})
source_group("App/SOURCES" FILES ${FILE_LOADER_SOURCE})

add_library(${target_name} STATIC "")

target_sources(${target_name}
    PRIVATE
        ${IMGUI_APP_SOURCE}
        ${IMGUI_APP_HEADER}
)

target_link_libraries(${target_name} PUBLIC custom_imgui fractals)

target_include_directories(${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/gui"
        "${PROJECT_SOURCE_DIR}/build"
        "${PROJECT_SOURCE_DIR}/assets"
)

set_property(TARGET ${target_name} PROPERTY FOLDER "App")