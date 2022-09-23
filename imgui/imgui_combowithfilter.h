#pragma once

#include <vector>
#include <string>

namespace ImGui {
	bool ComboWithFilter(const char* label, int* current_item, const std::vector<std::string>& items, int popup_max_height_in_items = -1);
}