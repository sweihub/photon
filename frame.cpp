#include "candlestick.h"
#include "json.hpp"
#include "frame.h"
#include "ctp.h"
#include "inireader.h"

// Our state
bool show_demo_window = false;
bool show_demo_implot = false;
bool show_test_window = false;
bool show_candlestick_window = false;

static void ShowAppMainMenuBar()
{
	static bool openpopuptemp = false;
	static char * focus_window = nullptr;

	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("策略"))
	{
		if (ImGui::MenuItem(u8"策略")) {
			openpopuptemp = true;
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu(u8"系统"))
	{
		if (ImGui::MenuItem(u8"设置", "CTRL+Z")) {
		}

		if (ImGui::MenuItem(u8"日志", "CTRL+Y", false, false)) {
		}  // Disabled item

		ImGui::Separator();

		if (ImGui::MenuItem("Cut", "CTRL+X")) {}
		if (ImGui::MenuItem("Copy", "CTRL+C")) {}
		if (ImGui::MenuItem("Paste", "CTRL+V")) {}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("交易")) {
		ImGui::MenuItem("账户");
		ImGui::MenuItem("行情");
		if (ImGui::BeginMenu("交易")) {
			ImGui::MenuItem("账户");
			ImGui::MenuItem("账户");
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}

	// Demo
	if (ImGui::BeginMenu("窗口")) {
		if (ImGui::MenuItem("Demo Window")) {
			show_demo_window = true;
			focus_window = "Dear ImGui Demo";
		}
		if (ImGui::MenuItem("Demo Implot")) {
			show_demo_implot = true;	
			focus_window = "ImPlot Demo";
		}
		if (ImGui::MenuItem("Demo Candlestick")) {
			show_candlestick_window = true;
			focus_window = "Candlestick";
		}
		if (ImGui::MenuItem("Test")) {
			show_test_window = true;
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

	if (show_demo_window) 
		ImGui::ShowDemoWindow(&show_demo_window);

	if (show_demo_implot)
		ImPlot::ShowDemoWindow(&show_demo_implot);
	
	if (show_candlestick_window) {
		ImGui::Begin("Candlestick", &show_candlestick_window);
		ShowCandlestick();
		ImGui::End();
	}

	if (show_test_window) {
		ImGui::Begin("test###1");
		ImGui::Text("text 1");
		ImGui::End();

		ImGui::Begin("test####2");
		ImGui::Text("text 2");
		ImGui::End();
	}

	// Mark to show the modal dialog
	if (openpopuptemp) {
		ImGui::OpenPopup("Exit this?");
		openpopuptemp = false;
	}
	
	// Show the modal dialog if marked as show
	if (ImGui::BeginPopupModal("Exit this?")) {
		ImGui::Text("Hello from Stacked The Second!");
		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}

	if (focus_window) {
		ImGui::SetWindowFocus(focus_window);
		focus_window = nullptr;
	}
}

int on_frame() {
		
	ShowAppMainMenuBar();

	return (0);
}