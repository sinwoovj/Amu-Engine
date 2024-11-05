#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../FrameCounter/FrameCounter.h"
#include "../Components/SpriteComp.h"
#include <EasyImgui.h>
#include <opengl.h>

namespace editor
{
	class MainEditor
	{

	public:
		~MainEditor();
		enum EditorMode
		{
			Play,
			Pause,
			Edit
		};
		static EditorMode editorMode;

		struct EDITOR_DATA
		{
			// Data Variable
			std::string currLevelName = "";

			std::string selectLevelName = "";
			std::string selectObjectName = "";
			std::string selectCompName = "";
			std::string selectLayerName = "";
			std::string selectTagName = "";

			std::string modifySpritePath = "";

			std::string addLvlName = "";
			std::string addObjName = "";
			std::string addLayerName = "";
			std::string addTagName = "";

			std::string changeLvlName = "";
			std::string changeObjName = "";
			std::string changeLayerName = "";
			std::string changeTagName = "";

			int remove_layer_item_selected_idx = 0;
			int layer_item_selected_idx = 0;
			int remove_tag_item_selected_idx = 0;
			int tag_item_selected_idx = 0;

			// Show State Variable
			bool showAllObjects = true; // Default
			bool showProfiler = false;
			bool showMapEditor = false;
			bool showGameDataEditor = false;

			// Show Popup
			bool showNewObjectPopup = false;
			bool showAddObjectPopup = false;
			bool showObjectListRightClickPopup = false;
			bool showCompListRightClickPopup = false;
			bool showLayerComboRightClickPopup = false;
			bool showTagComboRightClickPopup = false;
			bool showAlreadyHaveSameNameLevelPopup = false;
			bool showAlreadyHaveSameNameObjectPopup = false;
			bool showAlreadyHaveSameNameLayerPopup = false;
			bool showAlreadyHaveSameNameTagPopup = false;
			bool showAddLevelPopup = false;

			bool showAddLayerPopup = false;
			bool showAddTagPopup = false;

			bool showChangeLevelPopup = false;
			bool showChangeObjectPopup = false;
			bool showChangeLayerPopup = false;
			bool showChangeTagPopup = false;

			// Normal State Variable
			bool DeleteObject = false;
			bool ShowCollider = false;
			bool IsTraceObject = true; //Defualt
			bool ShowFps = false;
			bool ShowGrid = false;

			// Constant Variable
			const std::string editorFileName = "./Sources/Editor/editor.json";
		};
		static EDITOR_DATA editor_data;

		//check state var
		SpriteComp* psc = nullptr;
		SpriteComp* sc = nullptr;

		MainEditor() {}
		MainEditor(const MainEditor&) {}

		void renderFPSOverlay();
		void TraceObject();
		void PopUp();
		void TopBar();
		void ShowLevelObject(bool* p_open);
		void ShowProfiler(bool* p_open);
		void ShowMapEditor(bool* p_open);
		void ShowGameDataEditor(bool* p_open);

		void MainEditorInit();
		void MainEditorUpdate();
		void MainEditorExit();
	};
}

#define DEBUG_EDITOR_MODE_IN if(editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Edit) {

#define DEBUG_EDITOR_MODE_OUT }