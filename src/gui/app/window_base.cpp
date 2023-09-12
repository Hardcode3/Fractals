#include <imgui.h>

#include <app/window_base.hpp>

std::size_t WindowBase::WIN_ANY_TYPE_NB = 0;

WindowBase::WindowBase(std::string title, bool is_active, enum ImGuiWindowFlags_ flags):title_(title), is_active_(is_active), flags_(flags)
{
	WIN_ANY_TYPE_NB++;
}

WindowBase::~WindowBase()
{
	WIN_ANY_TYPE_NB--;
}

void WindowBase::update()
{
	if (is_active_)
	{
		ImGui::SetNextWindowSizeConstraints(min_size_, io_->DisplaySize);
		ImGui::Begin(title_.c_str(), &is_active_, flags_);
		draw();
		ImGui::End();
	}
}
