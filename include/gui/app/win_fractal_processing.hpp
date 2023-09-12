#include <thread>
#include <complex>

#include <imgui.h>

#include <app/window_base.hpp>
#include <fractals.hpp>


#ifndef WIN_FRACTAL_PROCESSING_HPP
#define WIN_FRACTAL_PROCESSING_HPP

class WinFractalProcessing : public WindowBase
{
public:
	WinFractalProcessing() = delete;
	WinFractalProcessing(std::string title, bool is_active, enum ImGuiWindowFlags_ flags = ImGuiWindowFlags_None) : WindowBase(title, is_active, flags) { ; }
	~WinFractalProcessing() { ; }

	void draw() override;

private:
	std::unique_ptr<Fractals> fractal_ = std::make_unique<Fractals>();
	int width_ = 800, height_ = 800;
	float z0_real_ = 0;
	float z0_imaginary_ = 0;
	float real_span_ = 4.0;
	int thread_count_ = 10;
	int symmetry_ = 2;

	static constexpr ImVec2 THREAD_LIMITS = ImVec2(1, 200);
	static constexpr ImVec2 SYMMETRY_LIMITS = ImVec2(-1, 10);
	static constexpr ImVec2 WIDTH_LIMITS = ImVec2(100, 3480);
	static constexpr ImVec2 HEIGHT_LIMITS = ImVec2(100, 3480);

	bool redraw_request_ = false;
	bool show_image_ = true;
	void draw_image();
};

#endif