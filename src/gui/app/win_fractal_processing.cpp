#include <app/win_fractal_processing.hpp>

void WinFractalProcessing::draw()
{
	ImGui::Text("Tweak the parameters of your fractal");
	ImGui::Spacing();

	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Choose the zoom (span of the displayed real axis):");
	if (ImGui::SliderFloat("Real span", &real_span_, 1e-20, 4, "%10f units"))
	{
		redraw_request_ = true;
	}

	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Choose the starting complex number for the set:");
	if (ImGui::SliderFloat("Real part:", &z0_real_, -2.0, 2.0, "%10f units"))
	{
		redraw_request_ = true;
	}
	if (ImGui::SliderFloat("Imaginary part:", &z0_imaginary_, -2.0, 2.0, "%.10f units"))
	{
		redraw_request_ = true;
	}

	ImGui::Separator();
	ImGui::Spacing();

	ImGui::SliderInt("Number of CPU threads", &thread_count_, THREAD_LIMITS.x, THREAD_LIMITS.y, "%i CPU's");

	ImGui::Separator();
	ImGui::Spacing();

	if (ImGui::SliderInt("Symmetry", &symmetry_, SYMMETRY_LIMITS.x, SYMMETRY_LIMITS.y, "symmerty order %i"))
	{
		redraw_request_ = true;
	}
	
	bool has_fractal_thread_finished = true;
	static std::thread fractal_thread;

	auto compute_fractal = [this, &has_fractal_thread_finished]()
		{
			has_fractal_thread_finished = false;
			fractal_->reset();
			fractal_->init(io_->DisplaySize.x, io_->DisplaySize.y, std::complex<long double>(0, 0), static_cast<long double>(real_span_));
			fractal_->compute_mandelbrot_async(5000, std::complex<long double>(static_cast<long double>(z0_real_), static_cast<long double>(z0_imaginary_)), (std::size_t)(thread_count_), RGBAPixel::BLACKNWHITE_CIRCULAR, symmetry_);
			has_fractal_thread_finished = true;
			redraw_request_ = false;
		};

	if ((ImGui::Button("Compute set", ImVec2(ImGui::GetContentRegionAvail().x, 30)) 
		|| redraw_request_)
		&& has_fractal_thread_finished 
		&& fractal_->is_computing() == false)
	{
		fractal_thread = std::thread(compute_fractal);
		fractal_thread.detach();
	}

	if (has_fractal_thread_finished && fractal_thread.joinable())
	{
		fractal_thread.join();
	}

	draw_image();
}

void WinFractalProcessing::draw_image()
{
	std::vector<unsigned char>* image = fractal_->get_image();
	if (image->size() == 0)
	{
		return;
	}

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	ImVec2 start_pos = ImVec2(0, 0);
	float pixel_size = 1.0f; // Adjust this to control the size of each pixel
	ImVec2 pixel_spacing = ImVec2(0.0f, 0.0f); // Adjust this to add spacing between pixels
	RGBAPixel pixel;

	for (int y = 0; y < fractal_->get_height(); y++)
	{
		for (int x = 0; x < fractal_->get_width(); x++)
		{
			int pixel_index = y * fractal_->get_width() + x;
			ImVec2 rect_min = ImVec2(start_pos.x + x * (pixel_size + pixel_spacing.x),
				start_pos.y + y * (pixel_size + pixel_spacing.y));
			ImVec2 rect_max = ImVec2(rect_min.x + pixel_size, rect_min.y + pixel_size);
			pixel = fractal_->get_pixel(x, y);
			draw_list->AddRectFilled(rect_min, rect_max, IM_COL32((ImU32)pixel.red_, (ImU32)pixel.green_, (ImU32)pixel.blue_, (ImU32)pixel.alpha_));
		}
	}
}