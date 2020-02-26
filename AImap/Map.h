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
#include "colorclass.h"
#include "player.h"

#define MAX_SIZE 15
#define CELL_MAX_SIZE 40

// Para crear botones dinámicos
#define BUTTON_NAME_COLOR "btn_color"

#define FILENAME_LISTCOLOR "Grounds.txt"
#define FILENAME_LISTPLAYER "Player.txt"

namespace AImap {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Reflection;
	using namespace std;
	
	
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
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::TabPage^  tabPage2;

	
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_Value;
	private: System::Windows::Forms::Button^  button_SetColor;
	private: System::Windows::Forms::Button^  button_AddColor;
	private: System::Windows::Forms::TextBox^  textBox_GroundName;
	private: System::Windows::Forms::Button^  button_EstadoFinal;
	private: System::Windows::Forms::Button^  button_EstadoInicial;
	private: System::Windows::Forms::Button^  button_ResetGrounds;
	private: System::Windows::Forms::Button^  button_SaveGrounds;

	Collection<Cell> *listCell;
	Collection<ColorClass> *listColor;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

			 Collection<Player> *listPlayer;
	//Collection<Button> *listButton;
			 
	
	public:
			
		Map(void)
		{
			InitializeComponent();
			
		}

		Map(String ^fileNameMap) {
			InitializeComponent();
			listCell = new Collection<Cell>;
			listColor = new Collection<ColorClass>;
			listPlayer = new Collection<Player>;

			//listButton = new Collection<Button>;

			//arrayData = new ArrayClass<int>;
			chargeMap(fileNameMap);
			chargeColor();
			chargePlayerFile();
			chargePlayer();
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Map::typeid));
			this->panelMap = (gcnew System::Windows::Forms::Panel());
			this->btn_play = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_FileNameMap = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->button_EstadoFinal = (gcnew System::Windows::Forms::Button());
			this->button_EstadoInicial = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button_ResetGrounds = (gcnew System::Windows::Forms::Button());
			this->button_SaveGrounds = (gcnew System::Windows::Forms::Button());
			this->numericUpDown_Value = (gcnew System::Windows::Forms::NumericUpDown());
			this->button_SetColor = (gcnew System::Windows::Forms::Button());
			this->button_AddColor = (gcnew System::Windows::Forms::Button());
			this->textBox_GroundName = (gcnew System::Windows::Forms::TextBox());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_Value))->BeginInit();
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
			this->textBox1->Size = System::Drawing::Size(75, 92);
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
			this->tabControl1->Location = System::Drawing::Point(-1, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(630, 585);
			this->tabControl1->TabIndex = 6;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button_EstadoFinal);
			this->tabPage1->Controls->Add(this->button_EstadoInicial);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->textBox_FileNameMap);
			this->tabPage1->Controls->Add(this->panelMap);
			this->tabPage1->Controls->Add(this->btn_play);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(622, 559);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// button_EstadoFinal
			// 
			this->button_EstadoFinal->Location = System::Drawing::Point(143, 52);
			this->button_EstadoFinal->Name = L"button_EstadoFinal";
			this->button_EstadoFinal->Size = System::Drawing::Size(81, 23);
			this->button_EstadoFinal->TabIndex = 7;
			this->button_EstadoFinal->Text = L"Estado Final";
			this->button_EstadoFinal->UseVisualStyleBackColor = true;
			// 
			// button_EstadoInicial
			// 
			this->button_EstadoInicial->Location = System::Drawing::Point(143, 23);
			this->button_EstadoInicial->Name = L"button_EstadoInicial";
			this->button_EstadoInicial->Size = System::Drawing::Size(81, 23);
			this->button_EstadoInicial->TabIndex = 6;
			this->button_EstadoInicial->Text = L"Estado Inicial";
			this->button_EstadoInicial->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->pictureBox1);
			this->tabPage2->Controls->Add(this->button_ResetGrounds);
			this->tabPage2->Controls->Add(this->button_SaveGrounds);
			this->tabPage2->Controls->Add(this->numericUpDown_Value);
			this->tabPage2->Controls->Add(this->button_SetColor);
			this->tabPage2->Controls->Add(this->button_AddColor);
			this->tabPage2->Controls->Add(this->textBox_GroundName);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(622, 559);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(68, 9);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(492, 335);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// button_ResetGrounds
			// 
			this->button_ResetGrounds->Location = System::Drawing::Point(385, 250);
			this->button_ResetGrounds->Name = L"button_ResetGrounds";
			this->button_ResetGrounds->Size = System::Drawing::Size(84, 23);
			this->button_ResetGrounds->TabIndex = 5;
			this->button_ResetGrounds->Text = L"Reestablecer";
			this->button_ResetGrounds->UseVisualStyleBackColor = true;
			// 
			// button_SaveGrounds
			// 
			this->button_SaveGrounds->Location = System::Drawing::Point(385, 221);
			this->button_SaveGrounds->Name = L"button_SaveGrounds";
			this->button_SaveGrounds->Size = System::Drawing::Size(84, 23);
			this->button_SaveGrounds->TabIndex = 4;
			this->button_SaveGrounds->Text = L"Guardar";
			this->button_SaveGrounds->UseVisualStyleBackColor = true;
			// 
			// numericUpDown_Value
			// 
			this->numericUpDown_Value->Location = System::Drawing::Point(385, 324);
			this->numericUpDown_Value->Name = L"numericUpDown_Value";
			this->numericUpDown_Value->Size = System::Drawing::Size(39, 20);
			this->numericUpDown_Value->TabIndex = 3;
			// 
			// button_SetColor
			// 
			this->button_SetColor->Location = System::Drawing::Point(385, 350);
			this->button_SetColor->Name = L"button_SetColor";
			this->button_SetColor->Size = System::Drawing::Size(75, 23);
			this->button_SetColor->TabIndex = 2;
			this->button_SetColor->Text = L"Color";
			this->button_SetColor->UseVisualStyleBackColor = true;
			this->button_SetColor->Click += gcnew System::EventHandler(this, &Map::button_SetColor_Click);
			// 
			// button_AddColor
			// 
			this->button_AddColor->Location = System::Drawing::Point(385, 379);
			this->button_AddColor->Name = L"button_AddColor";
			this->button_AddColor->Size = System::Drawing::Size(75, 23);
			this->button_AddColor->TabIndex = 1;
			this->button_AddColor->Text = L"Añadir";
			this->button_AddColor->UseVisualStyleBackColor = true;
			this->button_AddColor->Click += gcnew System::EventHandler(this, &Map::button_AddColor_Click);
			// 
			// textBox_GroundName
			// 
			this->textBox_GroundName->Location = System::Drawing::Point(385, 298);
			this->textBox_GroundName->Name = L"textBox_GroundName";
			this->textBox_GroundName->Size = System::Drawing::Size(100, 20);
			this->textBox_GroundName->TabIndex = 0;
			// 
			// Map
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(630, 597);
			this->Controls->Add(this->tabControl1);
			this->Location = System::Drawing::Point(30, 30);
			this->Name = L"Map";
			this->Text = L"Map";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_Value))->EndInit();
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
			//MessageBox::Show(gcnew String(str.c_str()));
			
			cell.setVisitCounter(0);

			if (!readerFile.is_open()) {
				messageError("Error, archivo'" + str + "'de lectura no disponible");
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
									panelMap->Size.Height = CELL_MAX_SIZE * (sizeMax + 1);
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
				panelMap->Size.Width = CELL_MAX_SIZE * (sizeMax + 1);
			}
			readerFile.close();
		}

		void chargeColor() {
			Button ^btn;
			ComboBox ^comboBox;
			TextBox ^textBox;
			NumericUpDown^ numericUpDown;
			String ^systemStr, ^idStr;
			ColorClass color = ColorClass();
			int size = listColor->getItemCounter(), id;
			Collection<ColorClass>* listColor2 = new Collection<ColorClass>;

			for (int i = 0; i < size; i++) {
				btn = gcnew Button;
				comboBox = gcnew ComboBox;
				//textBox = gcnew TextBox;
				numericUpDown = gcnew NumericUpDown;
				idStr = listColor->getDataByPosition(i).getId().ToString();
				//Estableciendo propiedades de botones dinámicos de colores
				systemStr = "btn_color" + idStr;
				btn->Name = systemStr;
				btn->Text = "Seleccionar color";
				btn->Location = Point(10,i * 25);
				btn->Size = System::Drawing::Size(115, 23);
				btn->BackColor = Color::Green;
				//Creando los eventos del botón dinámico
				btn->Click += gcnew System::EventHandler(this, &Map::btn_color_click);

				systemStr = "comboBox_Color" + idStr;
				comboBox->Name = systemStr;
				comboBox->Text = "Escoga un terreno";
				comboBox->Location = Point(135, i * 25);
				comboBox->Size = System::Drawing::Size(115, 23);
				comboBox->DropDownStyle = ComboBoxStyle::DropDownList;
				//comboBox->Leave += gcnew System::EventHandler(this, &Map::comboBox_Color_Name);
				
				
				/*systemStr = "textBox_Color" + i.ToString();
				textBox->Name = systemStr;
				textBox->Location = Point(260, i * 25);
				textBox->Size = System::Drawing::Size(115, 23);
				textBox->Visible = true;*/

				systemStr = "numericUpDown_Color" + idStr;
				numericUpDown->Name = systemStr;
				numericUpDown->Location = Point(260, i * 25);
				numericUpDown->Size = System::Drawing::Size(39, 20);
				

				tabPage2->Controls->Add(comboBox);
				tabPage2->Controls->Add(btn);
				tabPage2->Controls->Add(numericUpDown);
				//tabPage2->Controls->Add(textBox);
			}
			
		}	

		void chargeColorFile() {
			Cell cell;
			ColorClass color = ColorClass();;
			std::string str, str2, str3;
			fstream readerFile;

			readerFile.open(FILENAME_LISTCOLOR, ios::in);

			cell.setVisitCounter(0);

			if (!readerFile.is_open()) {
				messageError("Error, archivo de lectura no disponible");
			}
			else {
				while (!readerFile.eof()) {
					getline(readerFile, str, '°');
					color.setGroundName(str);
					getline(readerFile, str, '°');
					getline(readerFile, str2, '°');
					getline(readerFile, str3, '°');
					color.setColor(atoi(str.c_str()), atoi(str2.c_str()), atoi(str3.c_str()));

					if (!readerFile.eof())
						listColor->insertData(color);
				}
			}
			readerFile.close();
		}

		void chargePlayerFile() {
			Assembly ^assembly = Assembly::GetExecutingAssembly();
			StreamReader ^reader;
			Player player;
			std::string str, str2, str3, file;
			String ^systemStr;
			fstream readerFile;
			
			systemStr = "AImap.Player.txt";
			reader = gcnew StreamReader(assembly->GetManifestResourceStream(systemStr));
			systemStr = reader->ReadToEnd();
			marshalString(systemStr, file);

			MessageBox::Show(systemStr);

			/*C:\\Users\\Juan Balderrama\\source\\repos\\AImap\\AImap\\*/
			readerFile.open("algo123.txt", ios::app);
			readerFile.close();
			readerFile.open(FILENAME_LISTPLAYER, ios::in);

			if (!readerFile.is_open()) {
				messageError("Error, archivo '" + str +  "' de lectura no disponible");
			}
			else {
				while (!readerFile.eof()) {
					getline(readerFile, str, '°');
					player.setId(atoi(str.c_str()));
					getline(readerFile, str, '°');
					player.setName(str);

					if (!readerFile.eof()) {
						listPlayer->insertData(player);
					}
				}
			}

			readerFile.close();
			//MessageBox::Show("Added " + listPlayer->getItemCounter().ToString());
		}

		void chargePlayer() {
			ComboBox ^comboBox;
			PictureBox ^pictureBox;
			String ^systemStr;
			Player player;
			int items;
			AImap::Resources::ResourceManager ^manager;
			comboBox = gcnew ComboBox;
			pictureBox = gcnew PictureBox;
			//pictureBox->Image = AImap::Resources::

			comboBox->Name = "comboBox_Player";
			comboBox->Text = "Escoga un personaje";
			comboBox->Location = Point(370, 10);
			comboBox->Size = System::Drawing::Size(115, 23);
			comboBox->DropDownStyle = ComboBoxStyle::DropDownList;
			items = listPlayer->getItemCounter();
			
			pictureBox->Name = "pictureBox_Player";
			pictureBox->Location = Point(370, 40);
			pictureBox->Size = System::Drawing::Size(115, 115);
			


			for (int i = 0; i < items; i++) {
				player = listPlayer->getDataByPosition(i);
				systemStr = gcnew String(player.getName().c_str());
				systemStr = player.getId().ToString() + " - " + systemStr;
				comboBox->Items->Add(systemStr);
			}
			tabPage2->Controls->Add(comboBox);
			tabPage2->Controls->Add(pictureBox);
			
		}

		void drawMap() {
			Graphics ^g = panelMap->CreateGraphics();
			SolidBrush ^sb = gcnew SolidBrush(Color::Red);
			Pen ^p = gcnew Pen(Color::Blue);
			ColorClass color, colorTwo;
			Cell cell;
			string str;
			
			for (int i = 0; i < MAX_SIZE; i++) {
				for (int j = 0; j < MAX_SIZE; j++) {
					cell.setPositionX(j);
					cell.setPositionY(i);

					if (listCell->findPositionXY(cell) != nullptr) {
						cell = listCell->findPositionXY(cell)->getData();
						
						colorTwo.setId(cell.getIdGround());
						//color = listColor->getDataByPosition(cell.getIdGround());
						color = listColor->findData(colorTwo)->getData();
						//color = listColor[123];
						
						g->DrawRectangle(p, i * CELL_MAX_SIZE, j * CELL_MAX_SIZE, CELL_MAX_SIZE, CELL_MAX_SIZE);
						g->DrawString(cell.getIdGround().ToString(), this->Font, sb, PointF(i * CELL_MAX_SIZE + 10, j * CELL_MAX_SIZE + 10));
						//MessageBox::Show(color.getColor(0).ToString() + "-" + color.getColor(1).ToString() + "-" + color.getColor(2).ToString());
						sb = gcnew SolidBrush(Color::FromArgb(color.getColor(0), color.getColor(1), color.getColor(2)));
						g->FillRectangle(sb, i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 1, CELL_MAX_SIZE-1, CELL_MAX_SIZE-1);
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

		ColorClass *colorAux = new ColorClass();

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
			ColorClass *color = new ColorClass();
			int id, r, g, b;

			btn = safe_cast<Button^>(sender);
			id = Int32::Parse(btn->Name->Substring(9));
			
			MessageBox::Show(id.ToString());
			
			if (listColor->getPointerDataByPosition(id) != nullptr) {
				if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					r = colorDialog1->Color.R;
					g= colorDialog1->Color.G;
					b = colorDialog1->Color.B;
					listColor->getDataByPosition(id).setColor(r, g, b);
					//listColor->findId(id)->getData().setColor(r,g,b);
					
					MessageBox::Show("color establecido como: " + listColor->getDataByPosition(id).getColor(0) + " - ");
				}
			}

		}

		void comboBox_Color_Name(Object^ sender, EventArgs^ e) {
			ComboBox ^comboBox;
			ColorClass color, colorTwo;
			string str, str2;
			String ^systemStr;
			String ^systemStr2;
			int id;

			comboBox = safe_cast<ComboBox^>(sender);

			if (comboBox->Text == "") {
				MessageBox::Show("Error, no puede haber campos vacíos en los nombres");
			}
			if (comboBox->Text == "Escoga un terreno") {
				MessageBox::Show("Error, debe de escoger un nombre válido");
				}
			else {
				id = Int32::Parse(comboBox->Name->Substring(14));
				marshalString(comboBox->Text, str);
				color.setGroundName(str);
				//colorTwo = listColor->findData()->getData();

				if (listColor->findData(color) == nullptr) {
					listColor->findData(color)->getData().setGroundName(str);
				}
				else if (listColor->getDataByPosition(id).getId()) {

				}
				else {
					str = listColor->findData(color)->getData().getGroundName();
					systemStr = gcnew String(str.c_str());
					systemStr2 = gcnew String(color.getGroundName().c_str());
					MessageBox::Show("Error, el nombre para este terreno ya existe, ingrese uno nuevo - " + systemStr + "-" + 
					systemStr2);
				}
			}
			
			}

	private: System::Void panelMap_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Graphics ^g = panelMap->CreateGraphics();
		Pen ^p = gcnew Pen(Color::Black);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				g->DrawRectangle(p, 2 * CELL_MAX_SIZE, i * CELL_MAX_SIZE, CELL_MAX_SIZE, CELL_MAX_SIZE);
			}
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		drawMap();
	
}
	private: System::Void Map_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		Application::Exit();
	}
	private: System::Void button_SetColor_Click(System::Object^  sender, System::EventArgs^  e) {
		Button ^btn;
		int id, r, g, b;
	
		if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			r = colorDialog1->Color.R;
			g = colorDialog1->Color.G;
			b = colorDialog1->Color.B;

			colorAux->setColor(r, g, b);

			MessageBox::Show("color establecido como: " + colorAux->getColor(0).ToString() + " - ");
		}
	}
	private: System::Void button_AddColor_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^systemStr = "";
		string str;

		if (numericUpDown_Value->Value < 0 || 100 < numericUpDown_Value->Value) {
			systemStr = "El valor del terreno no puede ser inferior a 0 o superior a 100\n";
		}
		if (textBox_GroundName->Text == "") {
			systemStr += "Ingrese un nombre para el terreno\n";
		}
		if (colorAux->getColor(0) == -1) {
			systemStr += "Debe establecer un color primero";
		}
		if (systemStr != "") {
			MessageBox::Show("Error, se presentaron los siguientes errores al ingresar el terreno: \n" + systemStr);
		}
		else {
			
			marshalString(textBox_GroundName->Text, str);
			colorAux->setGroundName(str);
			colorAux->setValue(int(numericUpDown_Value->Value));
			colorAux->setId(listColor->getLast()->getData().getId() + 1);

			listColor->insertData(*colorAux);
			if (listColor->findData(*colorAux)) {
				MessageBox::Show("Terreno ingresado correctamente");
			}
			else {
				MessageBox::Show("Error, no se ha podido ingresar el terreno correctamente, vuelva a intentarlo.");
			}
			
		}
	}
};
}
