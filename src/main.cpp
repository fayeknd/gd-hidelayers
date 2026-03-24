#include "Geode/cocos/base_nodes/CCNode.h"
#include "Geode/cocos/support/component/CCComponentContainer.h"
#include "Geode/ui/TextRenderer.hpp"
#include "Geode/utils/cocos.hpp"
#include <Geode/Geode.hpp>

#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

float timeSinceStartup = 0;

bool shouldSetZero = false;

class $modify(GameObject) {
	void setOpacity(unsigned char opacity) {
        if (opacity == 50 && shouldSetZero)
            opacity = 0;
		GameObject::setOpacity(opacity);
	}
};


class $modify(NewToggleClass, LevelEditorLayer) {
		
	bool init(GJGameLevel* level, bool noUI) {
		if (!LevelEditorLayer::init(level, noUI)){
			return false;
		}

		// could probably have this in some sort of object container but i dont know how to do that
		// so lol

		auto text = CCLabelBMFont::create("  hide\nobjects", "bigFont.fnt");
		auto toggle = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(NewToggleClass::onToggle), 0.5f);

		auto parent = this->getChildByID("EditorUI")->getChildByID("layer-menu");
		parent->addChild(text);
		parent->addChild(toggle);

		text->setPosition(CCPoint(-4, 25));
		text->setScale(0.225);

		toggle->setPosition(CCPoint(-4, 8));

		return true;
	}

	void onToggle(CCObject* sender) {
		shouldSetZero = !shouldSetZero;
	}

};