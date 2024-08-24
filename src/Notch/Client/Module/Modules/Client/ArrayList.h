#pragma once
#include "../Module.h"
#include "../../ModuleManager.h"
#include "../../../../Libraries/Libs/ImFX/imfx.h"
#include "../../../../Utils/ImGuiUtils.h"
#include "../../../../GameData.h"

struct modules {
	Module* mod;
	bool enable;
	float persent;
	modules(Module* mod, bool enable, float persent) : mod(mod), enable(enable), persent(persent) {};
};

class ArrayList : public Module {
private:
	std::vector<modules> modInfo;

	int position = 1;
	int keymode = 0;

	bool top = true;
	Vec2 spos; // start pos
	float textsize = 1.f;
	float height = 1.f;
	float width = 1.2f;
	int backgroundEnum = 1;
	int textEnum = 1;
	UIColor backgroundCol;
	UIColor textCol;
	bool drawKeybind = false;

public:
	ArrayList();
	~ArrayList();


	void onImGuiRender(ImDrawList* drawlist);
	virtual void onEnable() override;
	virtual void onDisable() override;
};

