#pragma once

#include <vector>
#include <string>
#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui
{
	bool ComboAutoSelect(const char* label, char* output, int outlen, int* current_item, const std::vector<std::string> & items, ImGuiComboFlags flags = 0);

} 