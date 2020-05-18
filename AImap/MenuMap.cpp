#include "MenuMap.h"
//#include "Map.h"
#include "Tree.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	AImap::MenuMap menuMap;
	//AImap::Tree arbol;
	Application::Run(%menuMap);
	return 0;
}