#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>

#include "collection.h"
#include "cell.h"
#include "arrayclass.h"
#include "colorclass.h"

#define MAX_SIZE 15
// Para crear botones dinámicos
#define BUTTON_NAME_COLOR "btn_color"

//ArrayClass<int, Cell> arrayData[110][110];

namespace AImap {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	//ArrayClass<int, Cell> arrayData[MAX_SIZE][MAX_SIZE];
	
	
	/// <summary>
	/// Resumen de Map
	/// </summary>
	public ref class Map : public System::Windows::Forms::Form
	{
	private:;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox_FileNameMap;
	private: System::Windows::Forms::Panel^  panelMap;
	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  btn_play;


	Collection<ArrayClass<int, Cell>> *listArrayClass;
	Collection<Cell> *listCell;
	Collection<ColorClass> *listColor;
	//Collection<Button> *listButton;


	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::TabPage^  tabPage2;

			 
				 
	
	public:
			
		Map(void)
		{
			InitializeComponent();
			
		}

		Map(String ^fileNameMap) {
			InitializeComponent();
			listCell = new Collection<Cell>;
			listArrayClass = new Collection<ArrayClass<int, Cell>>;
			listColor = new Collection<ColorClass>;
			//listButton = new Collection<Button>;

			//arrayData = new ArrayClass<int>;
			chargeMap(fileNameMap);
			chargeColor();
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
			Application::Exit();
		}
		
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panelMap = (gcnew System::Windows::Forms::Panel());
			this->btn_play = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_FileNameMap = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panelMap
			// 
			this->panelMap->AutoSize = true;
			this->panelMap->Location = System::Drawing::Point(44, 104);
			this->panelMap->Name = L"panelMap";
			this->panelMap->Size = System::Drawing::Size(511, 392);
			this->panelMap->TabIndex = 1;
			this->panelMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Map::panelMap_Paint);
			// 
			// btn_play
			// 
			this->btn_play->Location = System::Drawing::Point(44, 502);
			this->btn_play->Name = L"btn_play";
			this->btn_play->Size = System::Drawing::Size(75, 23);
			this->btn_play->TabIndex = 3;
			this->btn_play->Text = L"Jugar";
			this->btn_play->UseVisualStyleBackColor = true;
			this->btn_play->Click += gcnew System::EventHandler(this, &Map::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(44, 6);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(216, 92);
			this->textBox1->TabIndex = 4;
			// 
			// textBox_FileNameMap
			// 
			this->textBox_FileNameMap->Location = System::Drawing::Point(288, 23);
			this->textBox_FileNameMap->Name = L"textBox_FileNameMap";
			this->textBox_FileNameMap->Size = System::Drawing::Size(183, 20);
			this->textBox_FileNameMap->TabIndex = 5;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 25);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(603, 560);
			this->tabControl1->TabIndex = 6;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->textBox_FileNameMap);
			this->tabPage1->Controls->Add(this->panelMap);
			this->tabPage1->Controls->Add(this->btn_play);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(595, 534);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(595, 534);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// Map
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(630, 597);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Map";
			this->Text = L"Map";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		void chargeMap(String ^fileNameMap) {
			Cell cell;
			ColorClass color;
			std::string str, str2;
			std::stringstream toStr;
			char character;
			int column = 0, row = 0, counter = 0, value = 0, sizeMax = 15;
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
							// Valida cada columna
							else if (character == ',') {
								if (row <= 14 && column <= 14) {
									cell.setId(counter++);
									cell.setIdGround(atoi(str.c_str()));
									cell.setPositionX(row);
									cell.setPositionY(column);
									listCell->insertData(cell);
									if (!listColor->findId(cell.getIdGround())) {
										color.setId(cell.getIdGround());
										listColor->insertData(color);
									}
									textBox1->Text += listCell->getLast()->getData().getPositionX().ToString() + ",";
									textBox1->Text += listCell->getLast()->getData().getPositionY().ToString() + "//";
									column++;
								}
								else if(column >= 15){
									cell.setId(-1);
									cell.setIdGround(-1);
									cell.setPositionX(row);
									cell.setPositionY(column);
									listCell->insertData(cell);
								}
								//txtPrueba->Text += cell.getId().ToString();
								str = "";
							}
							// Retorno de carro (agrega la fila)
							else if (character == 10 || character == 13) {
								if (row == 0) {
									sizeMax = column;
									panelMap->Size.Height = 30 * (sizeMax + 1);
								}
								//MessageBox::Show("Column: " + sizeMax.ToString());
								if (counter < sizeMax) {
									marshalString(row.ToString(), str);
									marshalString(counter.ToString(), str2);
									messageError("Error, el mapa tiene lados irregulares (Linea: " + str + ", Columna: " + str2 );
									readerFile.close();
									break;
								}
								if (row <= 14 && column <= 14) {
									cell.setId(counter++);
									cell.setIdGround(atoi(str.c_str()));
									cell.setPositionX(row);
									cell.setPositionY(column);
									listCell->insertData(cell);
									if (!listColor->findId(cell.getIdGround())) {
										color.setId(cell.getIdGround());
										listColor->insertData(color);
									}

									row++;
									column = 0;
								}
								else if(row >= 15){
									cell.setId(-1);
									cell.setIdGround(-1);
									cell.setPositionX(row);
									cell.setPositionY(column);

									listCell->insertData(cell);
									
									}
								//txtPrueba->Text += cell.getId().ToString() + "\r\n";
								str = "";
							}
							// Valida caracter inválido
							else {
								marshalString(fileNameMap, str);
								messageError("No se puede leer el archivo '" + str + "', archivo corrupto.");
								readerFile.close();
								break;
							}
						}
					}
				}
				panelMap->Size.Width = 30 * (sizeMax + 1);
			}
			readerFile.close();
		}

		void chargeColor() {
			Button ^btn;
			String ^systemStr;
			ColorClass color = ColorClass();
			int size = listColor->getItemCounter();
			Collection<ColorClass>* listColor2 = new Collection<ColorClass>;

			for (int i = 0; i < size; i++) {
				btn = gcnew Button;

				//Estableciendo propiedades de botones dinámicos de colores
				systemStr = "btn_color" + i.ToString();
				btn->Name = systemStr;
				listColor[i]; 

				btn->Text = "Seleccionar color";
				btn->Location = Point(10,i * 25);
				btn->Size = System::Drawing::Size(115, 23);
				btn->BackColor = Color::Green;
				//Creando los eventos del botón dinámico
				btn->Click += gcnew System::EventHandler(this, &Map::btn_color_click);
				tabPage2->Controls->Add(btn);
			}
			
		}
		

		void drawMap() {
			Graphics ^g = panelMap->CreateGraphics();
			SolidBrush ^sb = gcnew SolidBrush(Color::Red);
			Pen ^p = gcnew Pen(Color::Blue);
			Cell cell;
			string str;
			
			for (int i = 0; i < MAX_SIZE; i++) {
				for (int j = 0; j < MAX_SIZE; j++) {
					cell.setPositionX(j);
					cell.setPositionY(i);

					if (listCell->findPositionXY(cell) != nullptr) {
						cell = listCell->findPositionXY(cell)->getData();
						g->DrawRectangle(p, i * 30, j * 30, 30, 30);
						g->DrawString(cell.getIdGround().ToString(), this->Font, sb, PointF(i * 30 + 10, j * 30 + 10));
						if (cell.getIdGround() == 0) {
							g->FillRectangle(sb, i * 30 + 1, j * 30 + 1, 29, 29);
						}
					}
					else {
						str += "- 1";
					}
					//txtPrueba2->Text = arrayData->getSize().ToString();
				}
			}
			//MessageBox::Show();
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
	
		void btn_color_click(Object^ sender, EventArgs^ e) {
			Button ^btn;
			ColorClass color;
			int id, r, g, b;

			btn = safe_cast<Button^>(sender);
			//id = Int32::Parse(btn->Name->Substring(9));
			
			MessageBox::Show(id.ToString());

			if (listColor->findId(id)) {
				color = listColor->findId(id)->getData();
				
				if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					r = colorDialog1->Color.R;
					g= colorDialog1->Color.G;
					b = colorDialog1->Color.B;
					color.setColor(r,g,b);
					/*MessageBox::Show("color establecido como: " + color.getColor(0).ToString() + " - " +
						color.getColor(1).ToString() + " - " +
						color.getColor(2).ToString() + " - " );*/
				}
			}

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
private: System::Void Map_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	Application::Exit();
}
};
}
