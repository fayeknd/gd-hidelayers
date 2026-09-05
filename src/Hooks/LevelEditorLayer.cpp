#include "LevelEditorLayer.hpp"
#include "EditorUI.hpp"

// https://gd-src.undefined0.dev/libcocos2dcpp-32.so/LevelEditorLayer__updateVisibility#$pseudocode=163,19,163,19

void LevelEditorLayerHook::updateVisibility(float dt) {
    LevelEditorLayer::updateVisibility(dt);

    if (!static_cast<EditorUIHook*>(m_editorUI)->m_fields->m_toggleOn) return;

    for (size_t i = 0; i < m_activeObjectsCount; i++) {

        GameObject* obj = m_activeObjects[i];
        int layer = m_currentLayer;

        if (!((m_playbackMode == PlaybackMode::Playing || validGroup(obj, 0)) || (obj->m_editorLayer == layer || layer == -1)) && obj->getOpacity() != 0) {
            obj->setOpacity(0);
        }
    }
}
