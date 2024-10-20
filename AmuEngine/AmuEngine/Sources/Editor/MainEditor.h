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

			// Show State Variable
			bool showAllObjects = false;

			// Show Popup
			bool showNewObjectPopup = false;
			bool showAddObjectPopup = false;
			bool showObjectListRightClickPopup = false;
			bool showCompListRightClickPopup = false;
			bool showAlreadyHaveSameNameLevelPopup = false;
			bool showAddLevelPopup = false;

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
