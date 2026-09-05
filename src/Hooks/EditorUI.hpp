#pragma once
#include <Geode/modify/EditorUI.hpp>


class $modify(EditorUIHook, EditorUI) {
public:

	struct Fields {
		CCMenuItemSpriteExtra* m_button = nullptr;
		geode::EditorButtonSprite* m_onSpr = nullptr;
		geode::EditorButtonSprite* m_offSpr = nullptr;

		bool m_toggleOn;
	};

	bool init(LevelEditorLayer *editorLayer);
	void onToggle(CCObject* sender);

};