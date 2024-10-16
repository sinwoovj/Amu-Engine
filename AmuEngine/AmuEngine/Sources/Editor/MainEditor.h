#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <EasyImgui.h>
#include <opengl.h>

namespace editor
{
	class GameObject;

	class MainEditor
	{
		enum EditorMode
		{
			Play,
			Pause,
			Edit
		};

		~MainEditor();
	public:

		struct EDITOR_DATA
		{
			// Data Variable
			std::string currLevelName = "";
			std::string selectLevelName = "";
			std::string selectObjectName = "";
			std::string addLvlName = "";
			std::string addObjName = "";

			// Show State Variable
			bool showAllObjects = false;
			bool showNewObjectPopup = false;
			bool showAddObjectPopup = false;
			bool showObjectListRightClickPopup = false;

			// Normal State Variable
			bool DeleteObject = false;
		};
		static EDITOR_DATA editor_data;

		MainEditor() {}
		MainEditor(const MainEditor&) {}

		void PopUp();
		void TopBar();
		void ShowLevelObject(bool* p_open);
		void SelectedObjectWindow();
		void ShowMenuWindow();

		void MainEditorInit(GLFWwindow* mainWindow);
		void MainEditorUpdate();
		void MainEditorExit();
	};
}
