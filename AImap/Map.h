#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cctype>
#include <string>

#include "cell.h"
#include "collection.h"

namespace AImap {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace std;

	/// <summary>
	/// Resumen de Map
	/// </summary>
	public ref class Map : public System::Windows::Forms::Form
	{
	public:
		Map(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//


		}

		Map(String ^fileNameMap) {
			InitializeComponent();
			chargeMap(fileNameMap);

			Collection<Cell> *listData = new Collection<Cell>;
			
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Map()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panelMap;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panelMap = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panelMap
			// 
			this->panelMap->Location = System::Drawing::Point(12, 208);
			this->panelMap->Name = L"panelMap";
			this->panelMap->Size = System::Drawing::Size(606, 377);
			this->panelMap->TabIndex = 0;
			// 
			// Map
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(630, 597);
			this->Controls->Add(this->panelMap);
			this->Name = L"Map";
			this->Text = L"Map";
			this->ResumeLayout(false);

		}
#pragma endregion

		void chargeMap(String ^fileNameMap) {
			Cell cell;
			std::string str;
			std::stringstream toInt;
			char character;
			fstream readerFile;
			marshalString(fileNameMap, str);
			readerFile.open(str, ios::in);

			if (!readerFile.is_open()) {
				cout << "Error, archivo de lectura no disponible" << endl;
			}
			else {
				while (!readerFile.eof()) {
					if (readerFile.beg == -1 || readerFile.beg == readerFile.end) {
						cout << "Error, archivo de lectura no disponible 2" << endl;
						break;
					}
					else if (!readerFile.eof()) {
						readerFile >> character;
						if(isdigit(character)){
							str += character;	
						}
						else if (character == ',') {
							cell.setId(character);
							str = "";
						}
						else if (character == 13) {
							cell.setId(character);
							str = "";
						}
						else if (character == 10) {
							// Nada
						}
						else {
							// Imprimir error por caracter no válido
						}
						if (!readerFile.eof()) {
							listData->insertData(packet);
						}
					}
				}
			}
			readerFile.close();
		}

		// //////////////////////////////////////////////////////// HERRAMIENTAS ////////////////////////////////////////////////////////////// //

		void marshalString(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

	};
}
