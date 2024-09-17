#pragma once

#include "../Module.h"
#include "../../../../SDK/Actor/Actor.h"
#include "../../../../GameData.h"
#include "../../../../Utils/ImGuiUtils.h"
#include <unordered_map>
#include <string.h>

class PotionHud : public Module {
public:
    float size = 1.f;
    Vec2 Posi = Vec2(1.f, 1.f);
    PotionHud();
    virtual void onImGuiRender(ImDrawList* d) override;
private:
    std::unordered_map<int, std::string> Effects = {
        {static_cast<int>(MobEffectID::Speed), "Speed"},
        {static_cast<int>(MobEffectID::Slowness), "Slowness"},
        {static_cast<int>(MobEffectID::Haste), "Haste"},
        {static_cast<int>(MobEffectID::MiningFatigue), "Mining Fatigue"},
        {static_cast<int>(MobEffectID::Strength), "Strength"},
        {static_cast<int>(MobEffectID::InstantHealth), "Instant Health"},
        {static_cast<int>(MobEffectID::InstantDamage), "Instant Damage"},
        {static_cast<int>(MobEffectID::JumpBoost), "Jump Boost"},
        {static_cast<int>(MobEffectID::Nausea), "Nausea"},
        {static_cast<int>(MobEffectID::Regeneration), "Regeneration"},
        {static_cast<int>(MobEffectID::Resistance), "Resistance"},
        {static_cast<int>(MobEffectID::FireResistance), "Fire Resistance"},
        {static_cast<int>(MobEffectID::WaterBreathing), "Water Breathing"},
        {static_cast<int>(MobEffectID::Invisibility), "Invisibility"},
        {static_cast<int>(MobEffectID::Blindness), "Blindness"},
        {static_cast<int>(MobEffectID::NightVision), "Night Vision"},
        {static_cast<int>(MobEffectID::Hunger), "Hunger"},
        {static_cast<int>(MobEffectID::Weakness), "Weakness"},
        {static_cast<int>(MobEffectID::Poison), "Poison"},
        {static_cast<int>(MobEffectID::Wither), "Wither"},
        {static_cast<int>(MobEffectID::HealthBoost), "Health Boost"},
        {static_cast<int>(MobEffectID::Absorption), "Absorption"},
        {static_cast<int>(MobEffectID::Saturation), "Saturation"},
        {static_cast<int>(MobEffectID::Levitation), "Levitation"},
        {static_cast<int>(MobEffectID::FatalPoison), "Fatal Poison"},
        {static_cast<int>(MobEffectID::ConduitPower), "Conduit Power"},
        {static_cast<int>(MobEffectID::SlowFalling), "Slow Falling"},
        {static_cast<int>(MobEffectID::BadOmen), "Bad Omen"},
        {static_cast<int>(MobEffectID::VillageHero), "Village Hero"}
    };

    std::unordered_map<int, std::string> Amplifiers = {
        {1, "I"},
        {2, "II"},
        {3, "III"},
        {4, "IV"},
        {5, "V"},
        {6, "VI"},
        {7, "VII"},
        {8, "VIII"},
        {9, "IX"},
        {10, "X"},
    };

    std::unordered_map<int, UIColor> EffectColors = {
        {static_cast<int>(MobEffectID::Speed), UIColor(85, 255, 85)},           // Light Green
        {static_cast<int>(MobEffectID::Slowness), UIColor(96, 96, 255)},        // Light Blue
        {static_cast<int>(MobEffectID::Haste), UIColor(255, 255, 85)},          // Yellow
        {static_cast<int>(MobEffectID::MiningFatigue), UIColor(160, 160, 160)}, // Gray
        {static_cast<int>(MobEffectID::Strength), UIColor(255, 0, 0)},          // Red
        {static_cast<int>(MobEffectID::InstantHealth), UIColor(255, 85, 255)},  // Pink
        {static_cast<int>(MobEffectID::InstantDamage), UIColor(64, 0, 0)},      // Dark Red
        {static_cast<int>(MobEffectID::JumpBoost), UIColor(85, 255, 255)},      // Cyan
        {static_cast<int>(MobEffectID::Nausea), UIColor(85, 0, 0)},             // Dark Maroon
        {static_cast<int>(MobEffectID::Regeneration), UIColor(255, 85, 85)},    // Light Red
        {static_cast<int>(MobEffectID::Resistance), UIColor(192, 192, 192)},    // Silver
        {static_cast<int>(MobEffectID::FireResistance), UIColor(255, 170, 0)},  // Orange
        {static_cast<int>(MobEffectID::WaterBreathing), UIColor(0, 85, 255)},   // Blue
        {static_cast<int>(MobEffectID::Invisibility), UIColor(224, 224, 224)},  // Light Gray
        {static_cast<int>(MobEffectID::Blindness), UIColor(0, 0, 0)},           // Black
        {static_cast<int>(MobEffectID::NightVision), UIColor(85, 85, 255)},     // Blueish Purple
        {static_cast<int>(MobEffectID::Hunger), UIColor(128, 64, 0)},           // Brown
        {static_cast<int>(MobEffectID::Weakness), UIColor(96, 96, 96)},         // Dark Gray
        {static_cast<int>(MobEffectID::Poison), UIColor(85, 255, 85)},          // Green
        {static_cast<int>(MobEffectID::Wither), UIColor(48, 48, 48)},           // Dark Gray
        {static_cast<int>(MobEffectID::HealthBoost), UIColor(255, 170, 85)},    // Peach
        {static_cast<int>(MobEffectID::Absorption), UIColor(255, 170, 0)},      // Orange
        {static_cast<int>(MobEffectID::Saturation), UIColor(255, 85, 85)},      // Red
        {static_cast<int>(MobEffectID::Levitation), UIColor(170, 170, 255)},    // Light Purple
        {static_cast<int>(MobEffectID::FatalPoison), UIColor(0, 85, 0)},        // Dark Green
        {static_cast<int>(MobEffectID::ConduitPower), UIColor(0, 255, 255)},    // Aqua
        {static_cast<int>(MobEffectID::SlowFalling), UIColor(255, 255, 255)},   // White
        {static_cast<int>(MobEffectID::BadOmen), UIColor(0, 64, 64)},           // Dark Teal
        {static_cast<int>(MobEffectID::VillageHero), UIColor(85, 170, 85)}      // Green
    };
};