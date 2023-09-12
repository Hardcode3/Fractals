#include <utils/padding.hpp>

void Utils::center_cursor(const char* content, const bool center_x, const bool center_y)
{
    ImVec2 text_size = ImGui::CalcTextSize(content);
    if (center_x)
    {
        float text_height = text_size.x;
        float center = ImGui::GetWindowWidth() / 2.0f;
        ImGui::SetCursorPosX(center - (text_height / 2.0f));
    }
    if (center_y)
    {
        float text_height = text_size.y;
        float center = ImGui::GetWindowHeight() / 2.0f;
        ImGui::SetCursorPosX(center - (text_height / 2.0f));
    }
}