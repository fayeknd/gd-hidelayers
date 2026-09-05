#include "LevelEditorLayer.hpp"
#include "EditorUI.hpp"
#include <regex>

void LevelEditorLayerHook::updateVisibility(float dt) {
    LevelEditorLayer::updateVisibility(dt);
    if (!static_cast<EditorUIHook*>(m_editorUI)->m_fields->m_toggleOn) return;

    // https://gd-src.undefined0.dev/libcocos2dcpp-32.so/LevelEditorLayer__updateVisibility#$pseudocode=163,19,163,19
    bool isPlaying = (m_playbackMode == PlaybackMode::Playing);
    bool weirdGameVariable = GameManager::sharedState()->getGameVariable("0121"); // i dont know what this is

    for (size_t i = 0; i < m_activeObjectsCount; i++) {
        GameObject* obj = m_activeObjects[i];
        int layer = m_currentLayer;
        if (!((isPlaying || validGroup(obj, 0)) || (obj->m_editorLayer == layer || layer == -1))) {
            obj->setOpacity(0);
        }
        //geode::log::info("Object alpha: {}, isPlaying state: {}, layer: {}", obj->getOpacity(), isPlaying, layer);
    }
