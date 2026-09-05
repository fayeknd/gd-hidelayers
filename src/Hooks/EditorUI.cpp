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

    geode::EditorButtonSprite* onSpr = geode::EditorButtonSprite::create(
        CCSprite::create("showObjs.png"_spr),
        geode::EditorBaseColor::Cyan
    );
    onSpr->setID("on"_spr);

    geode::EditorButtonSprite* offSpr = geode::EditorButtonSprite::create(
        CCSprite::create("hideObjs.png"_spr),
        geode::EditorBaseColor::Green
    );
    offSpr->setID("off"_spr);

    CCMenuItemSpriteExtra* button = CCMenuItemSpriteExtra::create(offSpr, this, menu_selector(EditorUIHook::onToggle));
    button->setContentSize(CCSize(40.f,40.f));
    button->setID("hide-obj-toggle"_spr);

    button->addChild(onSpr);
    onSpr->setPosition(offSpr->getPosition());
    
    onSpr->setVisible(m_fields->m_toggleOn);
    offSpr->setVisible(!m_fields->m_toggleOn);

    geode::log::info("Created toggle '{}'.", button->getID());
    m_uiItems->addObject(button);
    menu->addChild(button);
    menu->updateLayout();
    
    m_fields->m_button = button;
    m_fields->m_offSpr = offSpr;
    m_fields->m_onSpr  = onSpr;

    return true;
}

void EditorUIHook::onToggle(CCObject*) {

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

