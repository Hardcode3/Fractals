#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>

#include <imgui.h>

#include <utils/padding.hpp>

namespace Utils
{
	class Notification
	{
	public:
		// the construcor makes a copy of the input arguments to avoid variable scope issues
		Notification(const char* content, const ImVec4 color, const float duration);
		~Notification() {}

		void update();

		// the content has to be initialized, therefore non const
		char content_[200];
		const ImVec4 color_;
		const float total_duration_ms_;
		std::chrono::high_resolution_clock::time_point creation_time_;
	};

	class NotificationSystem
	{
	public:
		NotificationSystem() { ; }
		~NotificationSystem() { ; }

		void update();
		void insert_notification(const char* content,const ImVec4& color, const float& duration);

	private:
		std::vector<Notification*> notifications_; // the container for the notifications
			
		// depend on the size of the current main window
		int win_width_ = 99; // width of the notification pannel
		int win_height_ = 99; // height of the notification pannel

		unsigned int win_bottom_padding_ = 10; // offset of the notification window / bottom of the window
		float win_padding_ = 0.5f; // window padding in pourcents
		float notif_padding_ = 1.0f; // notification padding inside the notification window
		unsigned int notification_no_ = 0; // the number of notifications currently in the notification pannel
		const float alpha_ = 0.6;

		int flags_ = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | 
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
	
		ImGuiIO* io_ = &ImGui::GetIO();
	};

	static Utils::NotificationSystem notification_sys = Utils::NotificationSystem();
}

#endif