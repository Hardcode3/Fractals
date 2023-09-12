#include <app/app.hpp>


App::App(std::size_t width, std::size_t height, std::string windowTitle) : width_(width), height_(height), window_title_(windowTitle)
{
    if (init() == 1)
        throw std::runtime_error("Initialization of the app failed");
}

App::~App()
{
    destroy();
    for (const auto& window : windows_)
        delete window;
}

void App::set_style()
{
    style_->WindowRounding = 8.0f;
    style_->GrabRounding = 8.0f;
    style_->FrameRounding = 7.0f;
    style_->ScrollbarRounding = 12.0f;
    style_->WindowPadding = ImVec2(9.0f, 9.0f);
    style_->PopupRounding = 8.0f;
    style_->PopupBorderSize = 2.0f;
    style_->FrameBorderSize = 1.0f;
}

void App::set_dark_style()
{
    if (is_light_style_)
    {
        set_background_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f));
        ImGui::StyleColorsDark();
    }
}

void App::set_light_style()
{
    if (is_light_style_)
    {
        set_background_color(ImVec4(.9f, .9f, .9f, 1.0f));
        ImGui::StyleColorsLight();
    }
}

void App::main_menu_bar()
{
    static bool show_imgui_demo = false;
    static bool show_implot_demo = false;
    if (show_imgui_demo)
        ImGui::ShowDemoWindow();
    if (show_implot_demo)
        ImPlot::ShowDemoWindow();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::MenuItem("Fractal"))
        {
            WindowBase* win = get_window("Fractal Processing");
            if (win == nullptr)
            {
                windows_.push_back(new WinFractalProcessing("Fractal Processing", true));
            }
            else
            {
                win->is_active_ = true;
            }
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::Checkbox("Show ImGui demo", &show_imgui_demo);
            ImGui::Checkbox("Show ImPlot demo", &show_implot_demo);
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("About"))
        {
            ;
        }
        ImGui::EndMainMenuBar();
    }
}

void App::glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int App::init()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    glsl_version_ = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glsl_version_ = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glsl_version_ = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    window_ = glfwCreateWindow(width_, height_, window_title_.c_str(), nullptr, nullptr);
    if (window_ == nullptr)
        return 1;
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImNodes::CreateContext();

    io_ = &ImGui::GetIO();
    assert(io_ != nullptr);

    io_->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    if (is_light_style_)
        ImGui::StyleColorsLight();
    else
        ImGui::StyleColorsDark();

    style_ = &ImGui::GetStyle();
    set_style();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(glsl_version_.c_str());

    setup_fonts();
    
    glfwSetWindowSizeLimits(window_, App::MIN_WINDOW_SIZE.x, App::MIN_WINDOW_SIZE.y, App::MAX_WINDOW_SIZE.x, App::MAX_WINDOW_SIZE.y);

    return 0;
}

void App::setup_fonts()
{
    ;
}

bool App::add_font(const char* relative_font_path)
{
    return true;
}


void App::update()
{
    Utils::notification_sys.update();
    main_menu_bar();
    for (auto& window : windows_)
        window->update();
}

void App::loop()
{
    while (!glfwWindowShouldClose(window_))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        update();

        ImGui::Render();
        glfwGetFramebufferSize(window_, &width_, &height_);
        glViewport(0, 0, width_, height_);
        glClearColor(background_color_.x * background_color_.w, background_color_.y * background_color_.w, background_color_.z * background_color_.w, background_color_.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window_);
    }
}

void App::close()
{
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

void App::destroy()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImNodes::DestroyContext();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window_);
    glfwTerminate();
}

void App::font_editor(const char *label)
{
    ImGuiIO &io = ImGui::GetIO();
    ImFont *font_current = ImGui::GetFont();
    if (ImGui::BeginCombo("Font", font_current->GetDebugName()))
    {
        for (int n = 0; n < io.Fonts->Fonts.Size; n++)
        {
            ImFont *font = io.Fonts->Fonts[n];
            ImGui::PushID((void *)font);
            if (ImGui::Selectable(font->GetDebugName(), font == font_current))
                io.FontDefault = font;
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    Utils::help_marker(
        "- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
        "- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
        "- Read FAQ and documentation in misc/fonts/ for more details.\n"
        "- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}

bool App::style_selector()
{
    static int style_idx = 1;
    if (ImGui::Combo("Color scheme", &style_idx, "Classic\0Dark\0Light\0"))
    {
        switch (style_idx)
        {
        case 0:
            ImGui::StyleColorsClassic();
            break;
        case 1:
            ImGui::StyleColorsDark();
            break;
        case 2:
            ImGui::StyleColorsLight();
            break;
        }
        return true;
    }
    return false;
}

void App::set_vsync(int swap_interval)
{
    // must be called after the creation of the opengl context
    if (swap_interval == 0 || swap_interval == 1)
        glfwSwapInterval(swap_interval);
}

bool App::window_exists(const std::string window_title) const
{
    for (const auto& win : windows_)
    {
        if (win->get_title() == window_title)
        {
            return true;
        }
    }
    return false;
}

WindowBase* App::get_window(const std::string window_title)
{
    for (const auto& win : windows_)
    {
        if (win->get_title() == window_title)
        {
            return win;
        }
    }
    return nullptr;
}