#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
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
	public:

		struct EDITOR_DATA
		{
			bool ShowAllObects = false;
			bool ShowAllLevels = false;

		};
		static EDITOR_DATA editor_data;

		MainEditor() {}
		MainEditor(const MainEditor&) {}

		void TopBar();
		void ShowAllObject();
		void ShowAllLevel();
		void SelectedObjectWindow();
		void ShowMenuWindow();

		void MainEditorInit(GLFWwindow* mainWindow);
		void MainEditorUpdate();
		void MainEditorExit();
	};
}
