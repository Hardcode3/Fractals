// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include <iostream>
#include <cstring>
#include <assert.h>
#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <implot.h>
#include <imnodes.h>

#include <fractalsConfigure.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <imfilebrowser.h>
#include <app/notifications.hpp>
#include <app/win_fractal_processing.hpp>
#include <utils/help_marker.hpp>


#ifndef APP_H
#define APP_H

class App
{
public:
    App(std::size_t width, std::size_t height, std::string windowTitle);
    ~App();

    void update();

    void setup_fonts();
    bool add_font(const char* path);
    void set_style();
    void loop();
    void close();
    void font_editor(const char* label);
    bool style_selector();
    void main_menu_bar();

    int get_width() const { return width_; }
    int get_height() const { return height_; }
    std::string get_window_title() const { return window_title_; }
    GLFWwindow* get_GLFW_window() const { return window_; }
    std::string get_GLSL_version() const { return glsl_version_; }
    bool is_color_style_light() const { return is_light_style_; }
    bool window_exists(const std::string window_title) const;
    WindowBase* get_window(const std::string window_title);

    void set_width(int width) { width_ = width; }
    void set_height(int height) { height_ = height; }
    void set_window_title(char* windowTitle) { window_title_ = windowTitle; }
    void set_color_style_light(bool lightColorStyle) { is_light_style_ = lightColorStyle; }
    void set_background_color(ImVec4 color) { background_color_ = color; }
    void set_dark_style();
    void set_light_style();
    void set_vsync(int swap_interval);

public:
    static Utils::NotificationSystem notif_sys;

    static constexpr ImVec2 MIN_WINDOW_SIZE = { 640, 480 };
    static constexpr ImVec2 MAX_WINDOW_SIZE = { 3480, 2160 };

private:
    int width_ = 1920;
    int height_ = 1080;
    GLFWwindow* window_ = nullptr;
    std::string window_title_ = "default window title";
    std::string glsl_version_ = "uninitialized";
    bool is_vsync_ = true;

    ImGui::FileBrowser file_browser_;

    ImGuiStyle* style_ = nullptr;
    ImGuiIO* io_ = nullptr;
    
    int font_size_ = 16;
    bool is_light_style_ = true;
    bool is_minimized_ = false;

    ImVec4 background_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    size_t font_size_range_[4] = { 12, 14, 16, 18 };

    std::vector<WindowBase*> windows_; 

private:
    static void glfw_error_callback(int error, const char* description);
    int init();
    void destroy();

};

#endif // !APP_H