#ifndef WINDOW_BASE_H
#define WINDOW_BASE_H

#include <string>
#include <iostream>
#include <imgui.h>

#include <utils/help_marker.hpp>
#include <imfilebrowser.h>
#include <app/notifications.hpp>

class WindowBase
{
public:
	WindowBase() = delete;
	WindowBase(std::string title, bool is_active, enum ImGuiWindowFlags_ flags = ImGuiWindowFlags_MenuBar);
	virtual ~WindowBase();

	virtual void draw() = 0;
	void update();

	std::string get_title() const { return title_; }
	void set_title(const char* title) { title_ = title; }

	ImVec2 get_min_size() const { return min_size_; }
	void set_min_size(ImVec2 min_size) { (min_size.x < io_->DisplaySize.x && min_size_.y < io_->DisplaySize.y) ? min_size_ = min_size : min_size_; }

	bool is_active_ = true;

	static std::size_t WIN_ANY_TYPE_NB;

protected:
	std::string title_;
	enum ImGuiWindowFlags_ flags_;

	ImVec2 min_size_ = { 800, 800 };

	ImGuiIO* io_ = &ImGui::GetIO();
};

#endif // !WINDOW_BASE_H