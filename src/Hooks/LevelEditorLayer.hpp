#pragma once
#include <Geode/modify/LevelEditorLayer.hpp>

class $modify(LevelEditorLayerHook, LevelEditorLayer) {
    void updateVisibility(float dt);
};