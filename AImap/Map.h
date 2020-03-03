#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>
#include <array>

#include "collection.h"
#include "cell.h"
#include "colorclass.h"
#include "player.h"

#define MAX_SIZE 15
#define CELL_MAX_SIZE 40

// Para crear botones din�micos
#define BUTTON_NAME_COLOR "btn_color"


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
	private: System::ComponentModel::IContainer^  components;
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
	private: System::Windows::Forms::ImageList^  imageList_Player;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox_Player;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox_Player;

	Collection<Cell> *listCell;
	Collection<ColorClass> *listColor;
	Collection<Player> *listPlayer;
	Collection<ColorClass> *listColorInUse;
	Collection<ColorClass> *listGround;
	cli::array<ComboBox^>^ arrayComboBox;
	//Collection<Button> *listButton;
	int publicSizeMax;
			 
	
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
			listGround = new Collection<ColorClass>;

			//listButton = new Collection<Button>;

			//arrayData = new ArrayClass<int>;
			chargeMap(fileNameMap);
			chargeColorFile();
			chargeColor();
			chargePlayerFile();
		}
	
	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
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
		/// Variable del dise�ador necesaria.
		/// </summary>
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necesario para admitir el Dise�ador. No se puede modificar
		/// el contenido de este m�todo con el editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Map::typeid));
			this->panelMap = (gcnew System::Windows::Forms::Panel());
			this->btn_play = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox_FileNameMap = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->imageList_Player = (gcnew System::Windows::Forms::ImageList(this->components));
			this->button_EstadoFinal = (gcnew System::Windows::Forms::Button());
			this->button_EstadoInicial = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox_Player = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox_Player = (gcnew System::Windows::Forms::ComboBox());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Player))->BeginInit();
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
			this->tabPage1->Controls->Add(this->comboBox1);
			this->tabPage1->Controls->Add(this->label1);
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
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(340, 57);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 10;
			// 
			// label1
			// 
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->ImageIndex = 0;
			this->label1->ImageList = this->imageList_Player;
			this->label1->Location = System::Drawing::Point(210, 38);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(52, 50);
			this->label1->TabIndex = 8;
			this->label1->Text = L"label1";
			// 
			// imageList_Player
			// 
			this->imageList_Player->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList_Player.ImageStream")));
			this->imageList_Player->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList_Player->Images->SetKeyName(0, L"Fish.gif");
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
			this->tabPage2->Controls->Add(this->pictureBox_Player);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->comboBox_Player);
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
			// pictureBox_Player
			// 
			this->pictureBox_Player->Location = System::Drawing::Point(385, 87);
			this->pictureBox_Player->Name = L"pictureBox_Player";
			this->pictureBox_Player->Size = System::Drawing::Size(200, 200);
			this->pictureBox_Player->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_Player->TabIndex = 8;
			this->pictureBox_Player->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(385, 27);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Personaje";
			// 
			// comboBox_Player
			// 
			this->comboBox_Player->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_Player->FormattingEnabled = true;
			this->comboBox_Player->Location = System::Drawing::Point(385, 46);
			this->comboBox_Player->Name = L"comboBox_Player";
			this->comboBox_Player->Size = System::Drawing::Size(121, 21);
			this->comboBox_Player->TabIndex = 6;
			this->comboBox_Player->SelectedIndexChanged += gcnew System::EventHandler(this, &Map::comboBox_Player_SelectedIndexChanged);
			// 
			// button_ResetGrounds
			// 
			this->button_ResetGrounds->Location = System::Drawing::Point(385, 337);
			this->button_ResetGrounds->Name = L"button_ResetGrounds";
			this->button_ResetGrounds->Size = System::Drawing::Size(84, 23);
			this->button_ResetGrounds->TabIndex = 5;
			this->button_ResetGrounds->Text = L"Reestablecer";
			this->button_ResetGrounds->UseVisualStyleBackColor = true;
			// 
			// button_SaveGrounds
			// 
			this->button_SaveGrounds->Location = System::Drawing::Point(385, 308);
			this->button_SaveGrounds->Name = L"button_SaveGrounds";
			this->button_SaveGrounds->Size = System::Drawing::Size(84, 23);
			this->button_SaveGrounds->TabIndex = 4;
			this->button_SaveGrounds->Text = L"Guardar";
			this->button_SaveGrounds->UseVisualStyleBackColor = true;
			// 
			// numericUpDown_Value
			// 
			this->numericUpDown_Value->Location = System::Drawing::Point(385, 411);
			this->numericUpDown_Value->Name = L"numericUpDown_Value";
			this->numericUpDown_Value->Size = System::Drawing::Size(39, 20);
			this->numericUpDown_Value->TabIndex = 3;
			// 
			// button_SetColor
			// 
			this->button_SetColor->Location = System::Drawing::Point(385, 437);
			this->button_SetColor->Name = L"button_SetColor";
			this->button_SetColor->Size = System::Drawing::Size(75, 23);
			this->button_SetColor->TabIndex = 2;
			this->button_SetColor->Text = L"Color";
			this->button_SetColor->UseVisualStyleBackColor = true;
			this->button_SetColor->Click += gcnew System::EventHandler(this, &Map::button_SetColor_Click);
			// 
			// button_AddColor
			// 
			this->button_AddColor->Location = System::Drawing::Point(385, 466);
			this->button_AddColor->Name = L"button_AddColor";
			this->button_AddColor->Size = System::Drawing::Size(75, 23);
			this->button_AddColor->TabIndex = 1;
			this->button_AddColor->Text = L"A�adir";
			this->button_AddColor->UseVisualStyleBackColor = true;
			this->button_AddColor->Click += gcnew System::EventHandler(this, &Map::button_AddColor_Click);
			// 
			// textBox_GroundName
			// 
			this->textBox_GroundName->Location = System::Drawing::Point(385, 385);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Player))->EndInit();
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
									publicSizeMax = sizeMax = column;
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
							// Valida caracter inv�lido
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
			String ^systemStr, ^idStr;
			ColorClass color;
			int size = listColor->getItemCounter(), id, sizeListGround = listGround->getItemCounter();
			cli::array <String^>^ nameColor = gcnew cli::array<String^>(sizeListGround);
			arrayComboBox = gcnew cli::array<ComboBox^>(size);

			for (int i = 0; i < sizeListGround; i++) {
				//nameColor[i] = listColor->getDataByPosition(i).getGroundName();
				//listColorInUse[i] = listColor[i];
				
				nameColor[i] = gcnew String(listGround->getDataByPosition(i).getGroundName().c_str());
				//MessageBox::Show(nameColor[i]);
			}

			for (int i = 0; i < size; i++) {
				btn = gcnew Button;
				comboBox = gcnew ComboBox;
				textBox = gcnew TextBox;
				color = listColor->getDataByPosition(i);
				idStr = color.getId().ToString();

				//Estableciendo propiedades de botones din�micos de colores
				systemStr = "btn_color" + idStr;
				btn->Name = systemStr;
				btn->Text = "Seleccionar color";
				btn->Location = Point(10,i * 25);
				btn->Size = System::Drawing::Size(115, 23);
				btn->BackColor = Color::Gray;
				//Creando los eventos del bot�n din�mico
				btn->Click += gcnew System::EventHandler(this, &Map::btn_color_click);

				systemStr = "comboBox_Color" + idStr;
				comboBox->Name = systemStr;
				comboBox->Location = Point(135, i * 25);
				comboBox->Size = System::Drawing::Size(115, 23);
				comboBox->DropDownStyle = ComboBoxStyle::DropDownList;
				comboBox->Items->AddRange(nameColor);
				comboBox->Text = "Escoga un terreno";
				comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Map::comboBox_Color_Name);
				arrayComboBox[i] = comboBox;
				
				
				/*systemStr = "textBox_Color" + i.ToString();
				textBox->Name = systemStr;
				textBox->Location = Point(260, i * 25);
				textBox->Size = System::Drawing::Size(115, 23);
				textBox->Visible = true;*/

				
				textBox->Name = "textBox_Color" + idStr;
				//systemStr = "numericUpDown_Color" + idStr;
				textBox->Location = Point(260, i * 25);
				textBox->Size = System::Drawing::Size(60, 23);
				textBox->Leave += gcnew System::EventHandler(this, &Map::textBox_Color_Float);
				

				tabPage2->Controls->Add(comboBox);
				tabPage2->Controls->Add(btn);
				tabPage2->Controls->Add(textBox);
				//tabPage2->Controls->Add(textBox);
			}
			
		}	

		void chargeColorFile() {
			Cell cell;
			ColorClass color;
			std::string str, str2, str3;
			fstream readerFile;
			cli::array <String^>^ nameColor = gcnew cli::array<String^>(200);
			String^ algo;
			int i = 0;

			auto execAssem = System::Reflection::Assembly::GetExecutingAssembly();
			auto resourceName = execAssem->GetName()->Name + ".Custom";
			auto resourceManager = gcnew Resources::ResourceManager(resourceName, execAssem);
			auto reader = cli::safe_cast<String^>(resourceManager->GetObject("Default_Ground"));
			
			//algo = reader->ReadToEnd();
			nameColor = reader->Split('|');
			for(int i=0;i<nameColor->Length-1; i+=4)
			{
				marshalString(nameColor[i], str);
				color.setGroundName(str);
				//color.setId(Int32::Parse(nameColor[i + 1]));
				int uno, dos, tres;
				uno = Int32::Parse(nameColor[i + 1]);
				dos = Int32::Parse(nameColor[i + 2]);
				tres = Int32::Parse(nameColor[i + 3]);
				color.setColor(uno, dos, tres);
				//MessageBox::Show(nameColor->Length.ToString() + " - " + i.ToString() + " - " + color.getColor(2).ToString());

				//listColor->operator[](i).setGroundName(str);
				listGround->insertData(color);
			}
		}

		void chargePlayerFile() {
			Player player;
			String ^systemStr;
			int i = 0, fileLength;
			int items;
			

			player.setId(0);
			player.setName("Fish");
			listPlayer->insertData(player);

			player.setId(1);
			player.setName("NyanCat");
			listPlayer->insertData(player);

			player.setId(2);
			player.setName("Virus");
			listPlayer->insertData(player);

			items = listPlayer->getItemCounter();

			for (int i = 0; i < items; i++) {
				player = listPlayer->getDataByPosition(i);
				systemStr = gcnew String(player.getName().c_str());
				comboBox_Player->Items->Add(systemStr);
			}

		}

		void drawMap() {
			Graphics ^g = panelMap->CreateGraphics();
			SolidBrush ^sb = gcnew SolidBrush(Color::Red);
			Pen ^p = gcnew Pen(Color::Blue);
			ColorClass color, colorTwo;
			Cell cell;
			string str;
			
			panelMap->Size.Width = publicSizeMax * CELL_MAX_SIZE;
			panelMap->Size.Height = publicSizeMax * CELL_MAX_SIZE;

			for (int i = 0; i < publicSizeMax; i++) {
				for (int j = 0; j < publicSizeMax; j++) {
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

		void validateBeforePlay() {
			
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
			id = Int32::Parse(comboBox->Name->Substring(14));
			
			//MessageBox::Show("CHANGED");
			
			for each (ComboBox^ var in arrayComboBox)
			{
				if (comboBox->SelectedIndex > 0) {
					var->Items->RemoveAt(comboBox->SelectedIndex);
				}
				
			}

			/*if (comboBox->Text == "Escoga un terreno") {
				MessageBox::Show("Error, debe de escoger un nombre v�lido");
				}
			else {
				
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
			}*/
			
			}

		void textBox_Color_Float(Object^ sender, EventArgs^ e) {
			TextBox ^txt = safe_cast<TextBox^>(sender);
			
			if (txt->Text == "") {

			}
			else if (System::Text::RegularExpressions::Regex::IsMatch(txt->Text, "^[-]?[0-9]*[.]?[0-9]+$") || 
				System::Text::RegularExpressions::Regex::IsMatch(txt->Text, "^[-]?[0-9]+[.]$")) {
				// ((.[0-9]+)|[0-9]+)  
				
			}
			else {
				MessageBox::Show("Ingrese un valor num�rico correcto");
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
	private: System::Void comboBox_Player_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		StreamReader ^reader;
		String ^systemStr;

		systemStr = comboBox_Player->SelectedItem->ToString();

		auto execAssem = System::Reflection::Assembly::GetExecutingAssembly();
		auto resourceName = execAssem->GetName()->Name + ".Custom";
		auto resourceManager = gcnew Resources::ResourceManager(resourceName, execAssem);
		auto bitMap = cli::safe_cast<Bitmap^>(resourceManager->GetObject(systemStr));
		pictureBox_Player->Image = bitMap;
		
		//MessageBox::Show("Function");
	}
};
}
