
#include "Geode/cocos/base_nodes/CCNode.h"
#include "Geode/cocos/cocoa/CCGeometry.h"
#include "Geode/cocos/support/component/CCComponentContainer.h"
#include "Geode/ui/Layout.hpp"
#include "ccTypes.h"
#include <Geode/Geode.hpp>

#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

#include "malware.hpp"

using namespace geode::prelude;


class $modify(ModifiedLEL, LevelEditorLayer) {
		
	struct Fields {
		bool shouldHideObjects = false;
	};

	bool init(GJGameLevel* level, bool noUI) {
		if (!LevelEditorLayer::init(level, noUI)){
			return false;
		}

		auto text = CCLabelBMFont::create("hide objects", "bigFont.fnt", 10, cocos2d::kCCTextAlignmentCenter);
		auto toggle = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(ModifiedLEL::onToggle), 0.5f);

		CCMenu* toggleContainer = CCMenu::create();
		toggleContainer->setID("hide-objects-toggle");
		//i dont really know what the point of content size is, so im going to ignore it. if its crucial for something like mobile touch then lmk
		toggleContainer->setContentSize(CCPoint(0,0));
		toggleContainer->addChildAtPosition(text, geode::Anchor(), CCPoint(0, 15));
		toggleContainer->addChild(toggle);
		toggle->setScale(0.9);
		text->setScale(0.225);

		if (!m_editorUI) {
			//then idfk
			return true;
		}

		auto layerMenu = m_editorUI->getChildByID("layer-menu");
		if (!layerMenu) {
			// fallback to the EditorUI menu item
			layerMenu = m_editorUI;
		}
		if (!layerMenu) {
			return true;
		}

		layerMenu->addChild(toggleContainer);

		auto allLayersButton = layerMenu->getChildByID("all-layers-button");

		if (allLayersButton) {

			toggleContainer->setPosition(
					allLayersButton->getPositionX() - 28,
					allLayersButton->getPositionY() - 6
				);
		}
		else { /*burn the world*/ }
		
		layerMenu->updateLayout();

		// see malware.hpp
		Malware evilMalware;
		evilMalware.breakGeodeRules();

		return true;
	}

	void onToggle(CCObject* sender) {
		m_fields->shouldHideObjects = !m_fields->shouldHideObjects;
	}

};


class $modify(GameObject) {
	void setOpacity(unsigned char opacity) {

		LevelEditorLayer* levelEditor = LevelEditorLayer::get();

        if (opacity == 50 && static_cast<ModifiedLEL*>(levelEditor)->m_fields->shouldHideObjects && levelEditor)
            opacity = 0;
		GameObject::setOpacity(opacity);
	}
};
