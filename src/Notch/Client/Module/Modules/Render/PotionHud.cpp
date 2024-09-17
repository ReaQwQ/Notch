#include "PotionHud.h"
#include <iomanip>

PotionHud::PotionHud() : Module("Potion HUD", "Shows Your Effect Hudb", Category::RENDER, 0x0) {
    addSlider<float>("Size", "Size of Text", ValueType::FLOAT_T, &size, 0.f, 2.f);
    addSlider<float>("PosX", "Position X of Text", ValueType::FLOAT_T, &Posi.x, 0.f, 1.f);
    addSlider<float>("PosY", "Position Y of Text", ValueType::FLOAT_T, &Posi.y, 0.f, 1.f);
}

void PotionHud::onImGuiRender(ImDrawList* d) {
    if (!Game.getLocalPlayer() || !Game.canUseMoveKeys()) return;
    Vec2 winsize = Game.getGuiData()->realSize;
    float heightIncrement = 0;

    for (MobEffectInstance effect : Game.getLocalPlayer()->getMobEffectsComponent()->effects) {
        if ((int)effect.mId <= 0) continue;
        const int& totalSeconds = effect.mDuration / 20;
        const int& Hours = totalSeconds / 60 / 60;
        const int& Minutes = totalSeconds / 60;
        const int& Seconds = totalSeconds % 60;

        Vec2 RenderPos = Vec2(winsize.x * Posi.x, winsize.y * Posi.y);
        RenderPos.y += heightIncrement;
        UIColor col = EffectColors[(int)effect.mId];
        std::ostringstream oss;
        oss << Effects[(int)effect.mId] << " " << Amplifiers[effect.mAmplifier + 1] << ": "
            << std::setw(2) << std::setfill('0') << Minutes << ":"
            << std::setw(2) << std::setfill('0') << Seconds;

        std::string EffectText = oss.str();
        ImGuiUtils::drawText(RenderPos, EffectText, col, size);

        heightIncrement += 25 * size;
    }
}