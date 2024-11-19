#pragma 
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_stdlib.h"
#ifdef APIENTRY
#undef APIENTRY
#endif
#include "../imgui/imgui_internal.h"
#include "../imgui/implot.h"
#include <vector>
#include <string>

void MultiSelectCombo(const char* label, const std::vector<std::string>& items, std::vector<bool>& selected);