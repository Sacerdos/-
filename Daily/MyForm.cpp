#include "MyForm.h"
#include <Windows.h>
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void main(array<String^>^ args) 
{
	FreeConsole();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Daily::MyForm form;
	Application::Run(%form);
}
