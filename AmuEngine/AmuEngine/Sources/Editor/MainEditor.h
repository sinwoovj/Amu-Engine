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

		MainEditor() {}
		MainEditor(const MainEditor&) {}

		void TopBar();
		void ShowAllObject();
		void SelectedObjectWindow();

		void MainEditorInit(GLFWwindow* mainWindow);
		void MainEditorUpdate();
		void MainEditorExit();
	};
}
