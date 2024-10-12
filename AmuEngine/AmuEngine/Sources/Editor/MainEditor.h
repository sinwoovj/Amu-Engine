#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../imgui/imgui.h"
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
		struct ExampleTreeNode
		{
			// Tree structure
			char                        Name[28] = "";
			int                         UID = 0;
			ExampleTreeNode* Parent = NULL;
			ImVector<ExampleTreeNode*>  Childs;
			unsigned short              IndexInParent = 0;  // Maintaining this allows us to implement linear traversal more easily

			// Leaf Data
			bool                        HasData = false;    // All leaves have data
			bool                        DataMyBool = true;
			int                         DataMyInt = 128;
			glm::vec2                   DataMyVec2 = glm::vec2(0.0f, 3.141592f);
		};

		struct ImGuiWindowData
		{
			// Examples Apps (accessible from the "Examples" menu)
			bool ShowMainMenuBar = false;
			bool ShowAppAssetsBrowser = false;
			bool ShowAppConsole = false;
			bool ShowAppCustomRendering = false;
			bool ShowAppDocuments = false;
			bool ShowAppDockSpace = false;
			bool ShowAppLog = false;
			bool ShowAppLayout = false;
			bool ShowAppPropertyEditor = false;
			bool ShowAppSimpleOverlay = false;
			bool ShowAppAutoResize = false;
			bool ShowAppConstrainedResize = false;
			bool ShowAppFullscreen = false;
			bool ShowAppLongText = false;
			bool ShowAppWindowTitles = false;

			// Dear ImGui Tools (accessible from the "Tools" menu)
			bool ShowMetrics = false;
			bool ShowDebugLog = false;
			bool ShowIDStackTool = false;
			bool ShowStyleEditor = false;
			bool ShowAbout = false;

			// Other data
			ExampleTreeNode* DemoTree = NULL;
		};


		struct EDITOR_DATA
		{
			bool ShowAllObects = false;
			bool ShowAllLevels = false;
		};
		static EDITOR_DATA editor_data;

		MainEditor() {}
		MainEditor(const MainEditor&) {}

		void TopBar();
		void ShowAllObject(bool* p_open);
		void ShowAllLevel(bool* p_open);
		void SelectedObjectWindow();
		void ShowMenuWindow();

		void MainEditorInit(GLFWwindow* mainWindow);
		void MainEditorUpdate();
		void MainEditorExit();
	};
}
