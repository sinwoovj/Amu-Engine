#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <EasyImgui.h>
#include <opengl.h>

namespace editor
{
	class MainEditor
	{

		~MainEditor();
	public:
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
			std::string modifySpritePath = "";
			std::string addLvlName = "";
			std::string addObjName = "";
			std::string addLayerName = "";
			std::string addTagName = "";

			int remove_layer_item_selected_idx = 0;
			int layer_item_selected_idx = 0;
			int remove_tag_item_selected_idx = 0;
			int tag_item_selected_idx = 0;

			// Show State Variable
			bool showAllObjects = false;

			// Show Popup
			bool showNewObjectPopup = false;
			bool showAddObjectPopup = false;
			bool showObjectListRightClickPopup = false;
			bool showCompListRightClickPopup = false;
			bool showAlreadyHaveSameNameLevelPopup = false;
			bool showAlreadyHaveSameNameObjectPopup = false;
			bool showAddLevelPopup = false;

			bool showAddLayerPopup = false;
			bool showAddTagPopup = false;
			bool showRemoveLayerPopup = false;
			bool showRemoveTagPopup = false;

			// Normal State Variable
			bool DeleteObject = false;
		};
		static EDITOR_DATA editor_data;

		MainEditor() {}
		MainEditor(const MainEditor&) {}

		void PopUp();
		void TopBar();
		void ShowLevelObject(bool* p_open);

		void MainEditorInit(GLFWwindow* mainWindow);
		void MainEditorUpdate();
		void MainEditorExit();
	};
}
