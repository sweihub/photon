#include "candlestick.h"
#include "json.hpp"
#include "app.h"
#include "ctp.h"
#include "inireader.h"
#include "imgui/imgui_combo_autoselect.h"

// Our state
bool show_demo_window = false;
bool show_demo_implot = false;
bool show_test_window = false;
bool show_candlestick_window = false;

int menu_clicked_id = 0;

struct UI {
	bool open = false;
	std::string name;
	void (*show)(UI *) = nullptr;
};

enum MenuId
{
	UI_ADD_ACCOUNT = 0,
};


namespace photon {
	template <typename... T>
	std::string format(const char * fmt, T ...args) {
		char buf[256] = {};
		snprintf(buf, sizeof(buf), fmt, args...);
		return std::string(buf);
	}
}


using ShowWindowHandler = void (*)(UI *);
struct GlobalAppData {
	std::vector<UI> windows;

	void add(int id, const char * name, ShowWindowHandler handler);
	void open(int id);
};

GlobalAppData app;

void GlobalAppData::add(int id, const char * name, ShowWindowHandler show) {
	app.windows.resize(id + 1);
	app.windows[id].show = show;
	app.windows[id].name = photon::format("%s###%d", name, id);
}

void GlobalAppData::open(int id) {
	UI & ui = app.windows[id];
	ui.open = true;
	ImGui::SetWindowFocus(ui.name.c_str());
}

void ShowAddAccountWindow(UI *ui)
{
	static char account[64] = {};
	static char password[64] = {};
	static char authcode[128] = {};
	static char appid[128] = {};
	static char broker[64] = {};

	if (ImGui::Begin(ui->name.c_str(), &ui->open)) {
		float offset = ImGui::GetFontSize() * 4.5f;
		ImGui::Text("期货公司");
		ImGui::SameLine(offset);	

		static ImGui::ComboAutoSelectData data = { {
				"AnimGraphNode_CopyBone",
				"ce skipaa",
				"ce skipscreen",
				"ce skipsplash",
				"ce skipsplashscreen",
				"client_unit.cpp",
				"letrograd",
				"level",
				"leveler",
				"MacroCallback.cpp",
				"Miskatonic university",
				"MockAI.h",
				"MockGameplayTasks.h",
				"MovieSceneColorTrack.cpp",
				"r.maxfps",
				"r.maxsteadyfps",
				"reboot",
				"rescale",
				"reset",
				"resource",
				"restart",
				"retrocomputer",
				"retrograd",
				"return",
				"slomo 10",
				"SVisualLoggerLogsList.h",
				"上海中期",
				"上海中华",
				"宏源期货",
				"The Black Knight",
				"",
				"  ",
				"empty string above"
			} };
		
		if (ImGui::ComboAutoSelect("my combofilter", data)) {		
			//...picking has occurred
		}
		ImGui::Text("Selection: %s, index = %d", data.input, data.index);
				
		ImGui::Text("帐号");
		ImGui::SameLine(offset);
		ImGui::InputText("##account", account, sizeof(account));

		ImGui::Text("密码");
		ImGui::SameLine(offset);
		ImGui::InputText("##password", password, sizeof(password), ImGuiInputTextFlags_Password);

		ImGui::Text("AppID");
		ImGui::SameLine(offset);
		ImGui::InputText("##appid", appid, sizeof(appid));

		ImGui::Text("授权码");
		ImGui::SameLine(offset);
		ImGui::InputText("##authcode", authcode, sizeof(authcode));
	}

	ImGui::End();
}

void AddWindows()
{
	app.add(UI_ADD_ACCOUNT, "新增账户", ShowAddAccountWindow);
}

void ShowWindows()
{
	for (UI & ui : app.windows) {
		if (ui.open)
			ui.show(&ui);
	}
}

void ProcessMenuClickedEvents()
{

	//menu_clicked_id = 0;
}

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
			if (ImGui::MenuItem("添加账户")) {
				app.open(UI_ADD_ACCOUNT);
			}
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

	ProcessMenuClickedEvents();
	
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

void on_start()
{
	AddWindows();
}

void on_frame() 
{		
	ShowAppMainMenuBar();
	ShowWindows();
}

void on_stop()
{

}
