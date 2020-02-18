#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cctype>
#include <string>

#include "collection.h"
#include "cell.h"
#include "arrayclass.h"
#include "MenuMap.h"

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
	MenuMap ^menuM;
	private:
		Collection<Cell> *listCell;
		Collection<ArrayClass<int>> *listArrayClass;
		ArrayClass<int> *arrayData;

	private: System::Windows::Forms::Button^  button1;
			 
	
	public:
		Map(void)
		{
			InitializeComponent();
			drawMap();
		}

		Map(MenuMap ^menuMapX ,String ^fileNameMap) {
			InitializeComponent();
			listCell = new Collection<Cell>;
			listArrayClass = new Collection<ArrayClass<int>>;
			arrayData = new ArrayClass<int>;
			menuM = menuMapX;
			drawMap();
			//chargeMap(fileNameMap);

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
			menuM->Close();
		}
	private: System::Windows::Forms::Panel^  panelMap;
	private: System::Windows::Forms::TextBox^  txtPrueba;
	private: System::Windows::Forms::TextBox^  txtPrueba2;
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
			this->txtPrueba = (gcnew System::Windows::Forms::TextBox());
			this->txtPrueba2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// panelMap
			// 
			this->panelMap->Location = System::Drawing::Point(12, 208);
			this->panelMap->Name = L"panelMap";
			this->panelMap->Size = System::Drawing::Size(606, 377);
			this->panelMap->TabIndex = 1;
			this->panelMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Map::panelMap_Paint);
			// 
			// txtPrueba
			// 
			this->txtPrueba->Location = System::Drawing::Point(117, 3);
			this->txtPrueba->Multiline = true;
			this->txtPrueba->Name = L"txtPrueba";
			this->txtPrueba->Size = System::Drawing::Size(266, 84);
			this->txtPrueba->TabIndex = 1;
			// 
			// txtPrueba2
			// 
			this->txtPrueba2->Location = System::Drawing::Point(117, 118);
			this->txtPrueba2->Multiline = true;
			this->txtPrueba2->Name = L"txtPrueba2";
			this->txtPrueba2->Size = System::Drawing::Size(266, 84);
			this->txtPrueba2->TabIndex = 2;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(514, 104);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Map::button1_Click);
			// 
			// Map
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(630, 597);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->txtPrueba2);
			this->Controls->Add(this->txtPrueba);
			this->Controls->Add(this->panelMap);
			this->Name = L"Map";
			this->Text = L"Map";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		void chargeMap(String ^fileNameMap) {
			Cell cell;
			std::string str;
			char character;
			int column = 0, row = 0, counter = 0, value;
			fstream readerFile;
			marshalString(fileNameMap, str);
			readerFile.open(str, ios::in);

			cell.setVisitCounter(0);

			if (!readerFile.is_open()) {
				messageError("Error, archivo de lectura no disponible");
			}
			else {
				while (!readerFile.eof()) {
					if (readerFile.beg == -1 || readerFile.beg == readerFile.end) {
						messageError("Error, archivo de lectura no disponible 2");
						break;
					}
					else if (!readerFile.eof()) {
						readerFile.get(character);
						//txtPrueba2->Text += character;
						if (!readerFile.eof()) {
							if (isdigit(character)) {
								str += character;
							}
							else if (character == ',') {
								cell.setId(counter);
								cell.setIdGround(atoi(str.c_str()));
								listCell->insertData(cell);
								if (row <= 14) {
									value = cell.getId();
									arrayData->setRow(row);
									arrayData->setColumn(column);
									arrayData->setValue(cell.getId());
									column++;
								}
								counter++;
								//txtPrueba->Text += cell.getId().ToString();
								str = "";
							}
							// Retorno de carro
							else if (character == 10) {
								cell.setId(counter);
								cell.setIdGround(atoi(str.c_str()));
								listCell->insertData(cell);
								if (row <= 14) {
									arrayData->setRow(row);
									arrayData->setColumn(column);
									arrayData->setValue(cell.getId());
									row++;
								}
								counter++;
								//txtPrueba->Text += cell.getId().ToString() + "\r\n";
								str = "";
							}
							// Nueva línea
							else {
								marshalString(fileNameMap, str);
								messageError("No se puede leer el archivo '" + str + "', archivo corrupto.");
								readerFile.close();
								break;
							}
						}
					}
				}
				arrayData->setSize(row);
			}
			readerFile.close();
		}

		

		void drawMap() {
			Graphics ^g = panelMap->CreateGraphics();
			Pen ^p = gcnew Pen(Color::Blue);
			for (int i = 0; i < arrayData->getSize(); i++) {
				for (int j = 0; j < arrayData->getSize(); j++) {
					
					g->DrawRectangle(p,  * 30, i * 30, 30, 30);
					//txtPrueba2->Text = arrayData->getSize().ToString();
				}
			}
		}
		// //////////////////////////////////////////////////////// HERRAMIENTAS ////////////////////////////////////////////////////////////// //

		void marshalString(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void messageError(string str) {
			String ^systemStr = gcnew String(str.c_str());
			MessageBox::Show("Error: " + systemStr);
		}
		
	private: System::Void panelMap_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics ^g = panelMap->CreateGraphics();
		Pen ^p = gcnew Pen(Color::Black);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				g->DrawRectangle(p, 2 * 30, i * 30, 30, 30);
			}
		}
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	drawMap();
}
};
}
