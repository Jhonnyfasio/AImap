#include "MenuMap.h"
#include "Map.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	AImap::MenuMap menuMap;
	Application::Run(%menuMap);
	return 0;
}