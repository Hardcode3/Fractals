#include <app/notifications.hpp>


Utils::Notification::Notification(const char* content, const ImVec4 color, const float total_duration_ms)
	:color_(color), total_duration_ms_(total_duration_ms)
{
	assert(strlen(content_) > strlen(content));
	strcpy(content_, content);
	creation_time_ = std::chrono::high_resolution_clock::now();
}

void Utils::Notification::update()
{
	Utils::center_cursor(content_, true, false);
	ImGui::PushStyleColor(ImGuiCol_Text, color_);
	ImGui::BulletText(content_);
	ImGui::PopStyleColor();
}

void Utils::NotificationSystem::update()
{
	if (notification_no_ > 0)
	{
		io_ = &ImGui::GetIO();
		std::cout << "update notif\n";
		auto current_time = std::chrono::high_resolution_clock::now();
		
		static float inter_line_height = ImGui::GetStyle().ItemSpacing.y;
		static float notif_line_height = ImGui::GetTextLineHeight();
		win_width_ = io_->DisplaySize.x * (1 - win_padding_);
		win_height_ = notif_line_height + notification_no_ * (notif_line_height + inter_line_height);

		ImGui::SetNextWindowFocus();
		ImGui::SetNextWindowPos(ImVec2(win_padding_ * io_->DisplaySize.x / 2, io_->DisplaySize.y - win_height_));
		ImGui::SetNextWindowPos(ImVec2(20, 20));
		ImGui::SetNextWindowBgAlpha(alpha_);
		ImGui::Begin("Notifications", nullptr, flags_);
		

		for (Notification* notif : notifications_)
		{
			assert(notif != nullptr);
			auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - notif->creation_time_);
			
			if (duration_ms.count() > notif->total_duration_ms_)
			{
				// find the notification entity in the vector
				auto it = std::find(notifications_.begin(), notifications_.end(), notif);

				if (it != notifications_.end())
				{
					// delete the object pointed by the element
					delete* it;
					// delete the pointer from the vector
					notifications_.erase(it);
					// decrement the number of notifications
					notification_no_--;
				}
			}
			notif->update();
		}
		ImGui::End();
	}
}

void Utils::NotificationSystem::insert_notification(const char* content, const ImVec4& color, const float& total_duration)
{
	Notification* notif = new Notification(content, color, total_duration);
	notifications_.insert(notifications_.begin(), notif);
	std::cout << notifications_.size() << "\n";
	notification_no_++;
}