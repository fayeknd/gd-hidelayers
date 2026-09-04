#include "EditorUI.hpp"
using namespace geode::prelude;

bool EditorUIHook::init(LevelEditorLayer *editorLayer) {
    if (!EditorUI::init(editorLayer)) return false;
    m_fields->m_toggleOn = geode::Mod::get()->getSavedValue<bool>("hide-layers", true);
    
    CCNode* menu = this->getChildByID("editor-buttons-menu");
    if (!menu){
        // gulp!!
        geode::log::error("Menu item '{}' was not found, please send me this issue @ fayeknd on discord thx!!", "editor-buttons-menu");
        return true;
    }

    m_fields->m_onSpr = geode::EditorButtonSprite::create(
        CCSprite::create("showObjs.png"_spr),
        geode::EditorBaseColor::Cyan
    );
    m_fields->m_onSpr->setID("on"_spr);

    m_fields->m_offSpr = geode::EditorButtonSprite::create(
        CCSprite::create("hideObjs.png"_spr),
        geode::EditorBaseColor::Green
    );
    m_fields->m_offSpr->setID("off"_spr);

    m_fields->m_button = CCMenuItemSpriteExtra::create(m_fields->m_offSpr, this, menu_selector(EditorUIHook::onToggle));
    m_fields->m_button->setContentSize(menu->getChildByIndex(0)->getContentSize());
    m_fields->m_button->setID("hide-obj-toggle"_spr);

    m_fields->m_button->addChild(m_fields->m_onSpr);
    m_fields->m_onSpr->setPosition(m_fields->m_offSpr->getPosition());
    
    m_fields->m_onSpr->setVisible(m_fields->m_toggleOn);
    m_fields->m_offSpr->setVisible(!m_fields->m_toggleOn);

    geode::log::info("Created toggle '{}'.", m_fields->m_button->getID());
    menu->addChild(m_fields->m_button);
    menu->updateLayout();
    
    return true;
}

void EditorUIHook::onToggle(CCObject*) { /*
    m_fields->shouldHideObjects = !m_fields->shouldHideObjects;
    m_fields->m_layerChanged = true; */

    m_fields->m_toggleOn = !m_fields->m_toggleOn;
    if (m_fields->m_toggleOn) {
        m_fields->m_offSpr->setVisible(false);
        m_fields->m_onSpr->setVisible(true);
    }
    else {
        m_fields->m_offSpr->setVisible(true);
        m_fields->m_onSpr->setVisible(false);
    }

    geode::Mod::get()->setSavedValue<bool>("hide-layers", m_fields->m_toggleOn); 
}

void EditorUIHook::showUI(bool show) {
    m_fields->m_button->setVisible(show);
    return EditorUI::showUI(show);
}

void EditorUIHook::onPlaytest(CCObject* sender) {
    m_fields->m_button->setVisible(false);
    EditorUI::onPlaytest(sender);
}

void EditorUIHook::onStopPlaytest(CCObject* sender) {
    m_fields->m_button->setVisible(true);
    EditorUI::onStopPlaytest(sender);
}

