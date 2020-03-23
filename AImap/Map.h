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
#include "ground.h"
#include "player.h"

#define MAX_SIZE 15
#define CELL_MAX_SIZE 50

// Para crear botones dinámicos
#define BUTTON_NAME_COLOR "btn_Color"
#define TEXTBOX_NAME_COLOR "textBox_Color"
#define CHECKBOX_NAME_COLOR "checkBox_Color"
#define COMBOBOX_NAME_COLOR "comboBox_Color"

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
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::ImageList^  imageList_Player;
	private: System::Windows::Forms::PictureBox^  pictureBox_PlayerIcon;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox_Player;
	private: System::Windows::Forms::Button^  button_ResetGrounds;
	private: System::Windows::Forms::Button^  button_SaveGrounds;
	private: System::Windows::Forms::PictureBox^  pictureBox_Start;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  txtPrueba2;
	private: System::Windows::Forms::Panel^  panelMap;
	private: System::Windows::Forms::Button^  btn_play;
	private: System::Windows::Forms::PictureBox^  pictureBox_Goal;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::PictureBox^  pictureBox_Player;
	private: BufferedGraphics ^graphicsBuffer;

	Collection<Cell> *listCell;
	Collection<Ground> *listGround;
	Collection<Player> *listPlayer;
	Collection<Ground> *listColorInUse;
	Collection<ColorClass> *listColor;
	cli::array<ComboBox^>^ arrayComboBox;
	cli::array<TextBox^>^ arrayTextBox;
	cli::array<Button^>^ arrayButton;
	cli::array<CheckBox^>^ arrayCheckBox;
	String ^fileNameMapGlobal;
	Point pictureBoxStarPoint, pictureBoxGoalPoint;

	int pointGoal = -1;
	int pointStart = -1;
	
	
	int publicSizeHeightMax;
	int publicSizeWidthMax;

	int visit = 0;
	private: System::Windows::Forms::Label^  label4;

			 bool isPlaying = false;
			 bool isCorruptFile = false;
	
	public:
			
		Map(void)
		{
			InitializeComponent();
			
		}

		Map(String ^fileNameMap) {
			InitializeComponent();
			//mainMenu = menuMap;
			listCell = new Collection<Cell>;
			listGround = new Collection<Ground>;
			listPlayer = new Collection<Player>;
			listColor = new Collection<ColorClass>;
			//chargeMap(fileNameMap);
			fileNameMapGlobal = fileNameMap;
			//listButton = new Collection<Button>;
			pictureBoxStarPoint = pictureBox_Start->Location;
			pictureBoxGoalPoint = pictureBox_Goal->Location;
			//arrayData = new ArrayClass<int>;
			//this->DoubleBuffered = true;


			
			UpdateGraphicsBuffer();
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
			//Application::Exit();
			//this->Close();
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
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Map::typeid));
			this->imageList_Player = (gcnew System::Windows::Forms::ImageList(this->components));
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->pictureBox_PlayerIcon = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox_Player = (gcnew System::Windows::Forms::ComboBox());
			this->button_ResetGrounds = (gcnew System::Windows::Forms::Button());
			this->button_SaveGrounds = (gcnew System::Windows::Forms::Button());
			this->pictureBox_Start = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->txtPrueba2 = (gcnew System::Windows::Forms::TextBox());
			this->panelMap = (gcnew System::Windows::Forms::Panel());
			this->btn_play = (gcnew System::Windows::Forms::Button());
			this->pictureBox_Goal = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox_Player = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_PlayerIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Start))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Goal))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Player))->BeginInit();
			this->SuspendLayout();
			// 
			// imageList_Player
			// 
			this->imageList_Player->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList_Player.ImageStream")));
			this->imageList_Player->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList_Player->Images->SetKeyName(0, L"Fish.gif");
			// 
			// pictureBox_PlayerIcon
			// 
			this->pictureBox_PlayerIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_PlayerIcon.Image")));
			this->pictureBox_PlayerIcon->Location = System::Drawing::Point(799, 126);
			this->pictureBox_PlayerIcon->Name = L"pictureBox_PlayerIcon";
			this->pictureBox_PlayerIcon->Size = System::Drawing::Size(200, 200);
			this->pictureBox_PlayerIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_PlayerIcon->TabIndex = 13;
			this->pictureBox_PlayerIcon->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(799, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Personaje";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// comboBox_Player
			// 
			this->comboBox_Player->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_Player->FormattingEnabled = true;
			this->comboBox_Player->Location = System::Drawing::Point(799, 85);
			this->comboBox_Player->Name = L"comboBox_Player";
			this->comboBox_Player->Size = System::Drawing::Size(121, 21);
			this->comboBox_Player->TabIndex = 11;
			this->comboBox_Player->SelectedIndexChanged += gcnew System::EventHandler(this, &Map::comboBox_Player_SelectedIndexChanged);
			// 
			// button_ResetGrounds
			// 
			this->button_ResetGrounds->Location = System::Drawing::Point(799, 376);
			this->button_ResetGrounds->Name = L"button_ResetGrounds";
			this->button_ResetGrounds->Size = System::Drawing::Size(84, 23);
			this->button_ResetGrounds->TabIndex = 10;
			this->button_ResetGrounds->Text = L"Reestablecer";
			this->button_ResetGrounds->UseVisualStyleBackColor = true;
			// 
			// button_SaveGrounds
			// 
			this->button_SaveGrounds->Location = System::Drawing::Point(799, 347);
			this->button_SaveGrounds->Name = L"button_SaveGrounds";
			this->button_SaveGrounds->Size = System::Drawing::Size(84, 23);
			this->button_SaveGrounds->TabIndex = 9;
			this->button_SaveGrounds->Text = L"Guardar";
			this->button_SaveGrounds->UseVisualStyleBackColor = true;
			// 
			// pictureBox_Start
			// 
			this->pictureBox_Start->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->pictureBox_Start->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_Start.Image")));
			this->pictureBox_Start->Location = System::Drawing::Point(25, 29);
			this->pictureBox_Start->Name = L"pictureBox_Start";
			this->pictureBox_Start->Size = System::Drawing::Size(50, 50);
			this->pictureBox_Start->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_Start->TabIndex = 21;
			this->pictureBox_Start->TabStop = false;
			this->pictureBox_Start->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Start_MouseDown);
			this->pictureBox_Start->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Start_MouseMove);
			this->pictureBox_Start->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Start_MouseUp);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(553, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(75, 67);
			this->textBox1->TabIndex = 16;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);
			// 
			// txtPrueba2
			// 
			this->txtPrueba2->Location = System::Drawing::Point(195, 45);
			this->txtPrueba2->Name = L"txtPrueba2";
			this->txtPrueba2->Size = System::Drawing::Size(183, 20);
			this->txtPrueba2->TabIndex = 17;
			// 
			// panelMap
			// 
			this->panelMap->AllowDrop = true;
			this->panelMap->AutoSize = true;
			this->panelMap->BackColor = System::Drawing::Color::Transparent;
			this->panelMap->Location = System::Drawing::Point(26, 110);
			this->panelMap->Name = L"panelMap";
			this->panelMap->Size = System::Drawing::Size(750, 750);
			this->panelMap->TabIndex = 14;
			this->panelMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Map::panelMap_Paint_1);
			this->panelMap->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::panelMap_MouseDown);
			// 
			// btn_play
			// 
			this->btn_play->BackColor = System::Drawing::Color::LimeGreen;
			this->btn_play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_play->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btn_play->Location = System::Drawing::Point(406, 29);
			this->btn_play->Name = L"btn_play";
			this->btn_play->Size = System::Drawing::Size(120, 50);
			this->btn_play->TabIndex = 15;
			this->btn_play->Text = L"Jugar";
			this->btn_play->UseVisualStyleBackColor = false;
			this->btn_play->Click += gcnew System::EventHandler(this, &Map::btn_play_Click);
			// 
			// pictureBox_Goal
			// 
			this->pictureBox_Goal->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->pictureBox_Goal->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_Goal.Image")));
			this->pictureBox_Goal->Location = System::Drawing::Point(100, 29);
			this->pictureBox_Goal->Name = L"pictureBox_Goal";
			this->pictureBox_Goal->Size = System::Drawing::Size(50, 50);
			this->pictureBox_Goal->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_Goal->TabIndex = 22;
			this->pictureBox_Goal->TabStop = false;
			this->pictureBox_Goal->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Start_MouseDown);
			this->pictureBox_Goal->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Start_MouseMove);
			this->pictureBox_Goal->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Start_MouseUp);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(22, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 23;
			this->label1->Text = L"Inicio";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(97, 13);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 13);
			this->label3->TabIndex = 24;
			this->label3->Text = L"Meta";
			// 
			// pictureBox_Player
			// 
			this->pictureBox_Player->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_Player.Image")));
			this->pictureBox_Player->Location = System::Drawing::Point(799, 12);
			this->pictureBox_Player->Name = L"pictureBox_Player";
			this->pictureBox_Player->Size = System::Drawing::Size(45, 45);
			this->pictureBox_Player->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_Player->TabIndex = 25;
			this->pictureBox_Player->TabStop = false;
			this->pictureBox_Player->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::pictureBox_Player_MouseDown);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(802, 406);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(218, 13);
			this->label4->TabIndex = 26;
			this->label4->Text = L"Color           Terreno            Alcance     Coste";
			// 
			// Map
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1042, 909);
			this->Controls->Add(this->btn_play);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->pictureBox_Player);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox_Goal);
			this->Controls->Add(this->pictureBox_Start);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->txtPrueba2);
			this->Controls->Add(this->panelMap);
			this->Controls->Add(this->pictureBox_PlayerIcon);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBox_Player);
			this->Controls->Add(this->button_ResetGrounds);
			this->Controls->Add(this->button_SaveGrounds);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->HelpButton = true;
			this->Location = System::Drawing::Point(30, 30);
			this->Name = L"Map";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Map";
			this->Shown += gcnew System::EventHandler(this, &Map::Map_Shown);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_PlayerIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Start))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Goal))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Player))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void UpdateGraphicsBuffer() {
			BufferedGraphicsContext ^bufferContext = BufferedGraphicsManager::Current;
			//graphicsBuffer = bufferContext->Allocate(panelMap->CreateGraphics(), this->DisplayRectangle);
		}

		// Carga el mapa al sistema
		/*void chargeMap(String ^fileNameMap) {
			Cell cell;
			Ground ground;
			std::string str, str2;
			std::stringstream toStr;
			char character;
			int column = 0, row = 0, counter = 0, value = 0, sizeMax = 15;
			fstream readerFile;
			marshalString(fileNameMap, str);
			readerFile.open(str, ios::in);
			char letra = 'A';
			//MessageBox::Show(gcnew String(str.c_str()));

			//cell.setVisitCounter(0);

			if (!readerFile.is_open()) {
				messageError("Error, archivo'" + str + "'de lectura no disponible");
			}
			else {
				str = "";
				if (readerFile.beg == -1 || readerFile.beg == readerFile.end) {
					messageError("Error, archivo de lectura no disponible 2");
					this->Close();
				}
				while (!readerFile.eof()) {
					
					if (!readerFile.eof()) {
						readerFile.get(character);
						txtPrueba2->Text += character;
						//if (!readerFile.eof()) {
							if (!readerFile.eof() && isdigit(character)) {
								str += character;
							}
							// Valida cada columna
							else if (!readerFile.eof() && character == ',') {
								if (str == "") {
									marshalString((row + 1).ToString(), str);
									marshalString((column + 1).ToString(), str2);
									messageError("Error, no puede haber dos ',' juntas (Linea: " + str + ", Columna: " + str2);
									//Application::Exit();
									this->Close();
								}
								if (row <= 15 && column <= 15) {
									//MessageBox::Show("Insertado con id: " + counter.ToString());
									cell.setId(counter++);
									cell.setIdGround(atoi(str.c_str()));
									cell.setPositionX(column);
									cell.setPositionY(row);
									listCell->insertData(cell);
									if (!listGround->findId(cell.getIdGround())) {
										ground.setId(cell.getIdGround());
										ground.setIsValid(true);
										listGround->insertData(ground);
									}
									textBox1->Text += listCell->getLast()->getData().getPositionX().ToString() + ",";
									textBox1->Text += listCell->getLast()->getData().getPositionY().ToString() + "//";
									column++;
								}
								//txtPrueba->Text += cell.getId().ToString();
								str = "";
							}
							// Retorno de carro (agrega la fila)
							else if (character == 10 || character == 13 || character == 3 || readerFile.eof()) {
								++column;
								if (row == 0) {
									sizeMax = column;
									publicSizeWidthMax = column;
									MessageBox::Show(publicSizeWidthMax.ToString());

								}
								MessageBox::Show("SizeMax: " + sizeMax.ToString() + " - " + column.ToString());
								if (column != sizeMax && str != "") {
									marshalString((row+1).ToString(), str);
									marshalString((column+1).ToString(), str2);
									messageError("Error, el mapa tiene lados irregulares (Linea: " + str + ", Columna: " + str2);
									//Application::Exit();
									this->Close(),
									readerFile.close();
									break;
								}
								if (row <= 15 && column <= 15 && str != "") {
									MessageBox::Show("Insertado con id: " + counter.ToString());
									cell.setId(counter++);
									cell.setIdGround(atoi(str.c_str()));
									cell.setPositionX(column);
									cell.setPositionY(row);
									listCell->insertData(cell);
									if (!listGround->findId(cell.getIdGround())) {
										ground.setId(cell.getIdGround());
										ground.setIsValid(true);
										listGround->insertData(ground);
									}

									textBox1->Text += listCell->getLast()->getData().getPositionX().ToString() + ",";
									textBox1->Text += listCell->getLast()->getData().getPositionY().ToString() + "//";

									publicSizeHeightMax = ++row;
									column = 0;
								}
								else if (str == "" && !readerFile.eof()) {
									marshalString((row + 1).ToString(), str);
									marshalString((column + 1).ToString(), str2);
									messageError("Error, el mapa no tiene la codificación correcta 'NUMERO,NUMERO' (Linea: " + str + ", Columna: " + str2 + ")");
									this->Close();
								}
								//txtPrueba->Text += cell.getId().ToString() + "\r\n";
								str = "";
							}
							// Valida caracter inválido
							else {
								marshalString(fileNameMap, str);
								MessageBox::Show("No se puede leer el archivo '" + fileNameMap + "', archivo corrupto en:\n"+
									"Fila: " +(row + 1).ToString() + "\nColumna: " + (column + 1).ToString() + ".\n"+
								"Favor de elegir un nuevo archivo");
								readerFile.close();
								//Application::Exit();
								this->Close();
								break;
							}
						//}
					}
				}
				//panelMap->Size.Width = CELL_MAX_SIZE * (sizeMax + 1);
			}
			readerFile.close();
			panelMap->Size = System::Drawing::Size((publicSizeWidthMax+1) * CELL_MAX_SIZE + 1,
				publicSizeHeightMax * CELL_MAX_SIZE + 1);

			MessageBox::Show("Width: " + publicSizeWidthMax.ToString() + " Height: " + publicSizeHeightMax.ToString());
			Label ^label;
			for (int i = 0; i < publicSizeWidthMax; i++) {
				label = gcnew Label;
				label->Size = System::Drawing::Size(20, 20);
				
				label->Text = System::Char::ToString(letra++);
				label->Location = Point(43 + (i * CELL_MAX_SIZE), 86);
				this->Controls->Add(label);
			}
			for (int j = 0; j < publicSizeHeightMax; j++) {
				label = gcnew Label;
				label->Size = System::Drawing::Size(20, 20);
				label->TextAlign = System::Drawing::ContentAlignment::TopRight;
				label->Text = (j+1).ToString();
				label->Location = Point(3 , 125 + (j * CELL_MAX_SIZE));
				this->Controls->Add(label);
			}

		}*/

		void chargeMap(String ^fileNameMap) {
			Cell cell;
			Ground ground;
			std::string str, str2;
			std::stringstream toStr;
			char character;
			int column = 0, row = 0, counter = 0, value = 0, sizeMax = 15;
			fstream readerFile;
			marshalString(fileNameMap, str);
			readerFile.open(str, ios::in);
			char letra = 'A';
			//MessageBox::Show(gcnew String(str.c_str()));

			//cell.setVisitCounter(0);

			if (!readerFile.is_open()) {
				messageError("Error, archivo'" + str + "'de lectura no disponible");
			}
			else {
				str = "";
				if (readerFile.beg == -1 || readerFile.beg == readerFile.end) {
					messageError("Error, archivo de lectura no disponible 2");
					//this->Close();
					isCorruptFile = true;
				}
				while (!readerFile.eof()) {
					
					if (!readerFile.eof()) {
						readerFile.get(character);
						txtPrueba2->Text += character;
						//if (!readerFile.eof()) {
							if (!readerFile.eof() && isdigit(character)) {
								str += character;
							}
							// Valida cada columna
							else if (!readerFile.eof() && character == ',') {
								if (row <= 14 && column <= 14 && str != "") {
									cell.setId(counter++);
									cell.setIdGround(atoi(str.c_str()));
									cell.setPositionX(column);
									cell.setPositionY(row);
									listCell->insertData(cell);
									if (!listGround->findId(cell.getIdGround())) {
										ground.setId(cell.getIdGround());
										ground.setIsValid(true);
										listGround->insertData(ground);
									}
									textBox1->Text += listCell->getLast()->getData().getPositionX().ToString() + ",";
									textBox1->Text += listCell->getLast()->getData().getPositionY().ToString() + "//";
									column++;
								}
								if (str == "") {
									messageError("No se amdmiten valores nulos (dobles comas)");
									isCorruptFile = true;
								}
								//txtPrueba->Text += cell.getId().ToString();
								str = "";
							}
							// Retorno de carro (agrega la fila)
							else if (character == 10 || character == 13 || character == 3 || readerFile.eof()) {
								if (row == 0) {
									sizeMax = column;
									publicSizeWidthMax = column + 1;
									//panelMap->Size.Height = CELL_MAX_SIZE * (sizeMax + 1);
									//MessageBox::Show(publicSizeMax.ToString());

								}
								//MessageBox::Show("Column: " + column.ToString() + " - " + sizeMax.ToString());
								if (column != sizeMax && !readerFile.eof()) {
									marshalString((row+1).ToString(), str);
									marshalString((counter+1).ToString(), str2);
									messageError("Error, el mapa tiene lados irregulares (Linea: " + str + ", Columna: " + str2);
									//this->Close();
									isCorruptFile = true;
									readerFile.close();
									break;
								}
								if (row <= 14 && column <= 14 && str != "") {
									cell.setId(counter++);
									cell.setIdGround(atoi(str.c_str()));
									cell.setPositionX(column);
									cell.setPositionY(row);
									listCell->insertData(cell);
									if (!listGround->findId(cell.getIdGround())) {
										ground.setId(cell.getIdGround());
										ground.setIsValid(true);
										listGround->insertData(ground);
									}

									publicSizeHeightMax = ++row;
									column = 0;
								}
								if (str == "") {
									messageError("No se amdmiten valores nulos (dobles comas)");
									isCorruptFile = true;
								}
								//txtPrueba->Text += cell.getId().ToString() + "\r\n";
								str = "";
							}
							// Valida caracter inválido
							else {
								marshalString(fileNameMap, str);
								MessageBox::Show("No se puede leer el archivo '" + fileNameMap + "', archivo corrupto en:\n"+
									"Fila: " +(row + 1).ToString() + "\nColumna: " + (column + 1).ToString() + ".\n"+
								"Favor de elegir un nuevo archivo");
								readerFile.close();
								//Application::Exit();
								//this->Close();
								isCorruptFile = true;
								break;
							}
						//}
					}
				}
				//panelMap->Size.Width = CELL_MAX_SIZE * (sizeMax + 1);
			}
			readerFile.close();
			panelMap->Size = System::Drawing::Size(publicSizeWidthMax * CELL_MAX_SIZE + 1,
				publicSizeHeightMax * CELL_MAX_SIZE + 1);

			/*MessageBox::Show("Width: " + publicSizeWidthMax.ToString() + " Height: " + publicSizeHeightMax.ToString() +
			panelMap->Size.Width.ToString() + " - "+panelMap->Size.Height);*/
			Label ^label;
			for (int i = 0; i < publicSizeWidthMax; i++) {
				label = gcnew Label;
				label->Size = System::Drawing::Size(20, 20);
				
				label->Text = System::Char::ToString(letra++);
				label->Location = Point(43 + (i * CELL_MAX_SIZE), 86);
				this->Controls->Add(label);
			}
			for (int j = 0; j < publicSizeHeightMax; j++) {
				label = gcnew Label;
				label->Size = System::Drawing::Size(20, 20);
				label->TextAlign = System::Drawing::ContentAlignment::TopRight;
				label->Text = (j+1).ToString();
				label->Location = Point(3 , 125 + (j * CELL_MAX_SIZE));
				this->Controls->Add(label);
			}

		}


		// Crea botones, textbos y combobox dinámicos para los colores
		void chargeColor() {
			Button ^btn;
			ComboBox ^comboBox;
			CheckBox ^checkBox;
			TextBox ^textBox;
			//Label ^label;
			String ^systemStr, ^idStr;
			Ground ground;
			int size = listGround->getItemCounter(), id, sizeListGround = listColor->getItemCounter();
			cli::array <String^>^ nameGround = gcnew cli::array<String^>(sizeListGround);
			arrayComboBox = gcnew cli::array<ComboBox^>(size);
			arrayButton = gcnew cli::array<Button^>(size);
			arrayTextBox = gcnew cli::array<TextBox^>(size);
			arrayCheckBox = gcnew cli::array<CheckBox^>(size);

			for (int i = 0; i < sizeListGround; i++) {
				//nameColor[i] = listColor->getDataByPosition(i).getGroundName();
				//listColorInUse[i] = listColor[i];
				
				nameGround[i] = gcnew String(listColor->getDataByPosition(i).getName().c_str());
				//MessageBox::Show(nameColor[i]);
			}

			for (int i = 0; i < size; i++) {
				btn = gcnew Button;
				comboBox = gcnew ComboBox;
				textBox = gcnew TextBox;
				checkBox = gcnew CheckBox;
				//label = gcnew Label;
				ground = listGround->getDataByPosition(i);
				idStr = ground.getId().ToString();

				//Estableciendo las etiquetas con los ID
				//label->Location = Point(790, i * 25 + 420);
				//label->Text = gcnew String(idStr);

				//Estableciendo propiedades de botones dinámicos de colores
				systemStr = BUTTON_NAME_COLOR + idStr;
				btn->Name = systemStr;
				btn->Text = idStr + " - Color";
				//btn->Location = Point(10,i * 25);
				btn->Location = Point(800, i * 25 + 420);
				btn->Size = System::Drawing::Size(55, 23);
				btn->BackColor = Color::Gray;
				//Creando los eventos del botón dinámico
				btn->Click += gcnew System::EventHandler(this, &Map::btn_color_click);
				arrayButton[i] = btn;

				systemStr = COMBOBOX_NAME_COLOR + idStr;
				comboBox->Name = systemStr;
				//comboBox->Location = Point(135, i * 25);
				comboBox->Location = Point(800+ 60, i * 25 + 420);
				comboBox->Size = System::Drawing::Size(70, 23);
				comboBox->DropDownStyle = ComboBoxStyle::DropDownList;
				comboBox->Items->AddRange(nameGround);
				comboBox->Text = "Escoga un terreno";
				comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Map::comboBox_Color_Name);
				arrayComboBox[i] = comboBox;
				
				 
				/*systemStr = "textBox_Color" + i.ToString();
				textBox->Name = systemStr;
				textBox->Location = Point(260, i * 25);
				textBox->Size = System::Drawing::Size(115, 23);
				textBox->Visible = true;*/

				checkBox->Name = CHECKBOX_NAME_COLOR + idStr;
				checkBox->Location = Point(800 + 135, i * 25 + 420);
				checkBox->Size = System::Drawing::Size(46, 17);
				checkBox->Text = "N/A";
				checkBox->CheckedChanged += gcnew System::EventHandler(this, &Map::checkBox_Color_IsValid);
				arrayCheckBox[i] = checkBox;
				
				textBox->Name = TEXTBOX_NAME_COLOR + idStr;
				//systemStr = "numericUpDown_Color" + idStr;
				//textBox->Location = Point(260, i * 25);
				textBox->Location = Point(800 + 185, i * 25 + 420);
				textBox->Size = System::Drawing::Size(60, 23);
				textBox->Text = "0";
				textBox->Leave += gcnew System::EventHandler(this, &Map::textBox_Color_Float);
				arrayTextBox[i] = textBox;
				
				//this->Controls->Add(label);
				this->Controls->Add(comboBox);
				this->Controls->Add(btn);
				this->Controls->Add(checkBox);
				this->Controls->Add(textBox);
				//tabPage2->Controls->Add(textBox);
			}
			
		}	

		// Carga los colores
		void chargeColorFile() {
			Cell cell;
			ColorClass color;
			std::string str, str2, str3;
			fstream readerFile;
			cli::array <String^>^ nameColor = gcnew cli::array<String^>(200);
			String^ algo;
			int i = 0;

			//System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Map::typeid));
			auto execAssem = System::Reflection::Assembly::GetExecutingAssembly();
			auto resourceName = execAssem->GetName()->Name + ".Custom";
			auto resourceManager = gcnew Resources::ResourceManager(resourceName, execAssem);
			auto reader = cli::safe_cast<String^>(resourceManager->GetObject("Default_Ground"));
			
			//algo = reader->ReadToEnd();
			nameColor = reader->Split('|');
			for(int i=0;i<nameColor->Length-1; i+=4)
			{
				marshalString(nameColor[i], str);
				color.setId(i);
				color.setName(str);
				//color.setId(Int32::Parse(nameColor[i + 1]));
				int uno, dos, tres;
				uno = Int32::Parse(nameColor[i + 1]);
				dos = Int32::Parse(nameColor[i + 2]);
				tres = Int32::Parse(nameColor[i + 3]);
				color.setColor(uno, dos, tres);
				//MessageBox::Show(nameColor->Length.ToString() + " - " + i.ToString() + " - " + color.getColor(2).ToString());

				//listColor->operator[](i).setGroundName(str);
				listColor->insertData(color);
			}
		}

		// Carga los jugadores predeterminados
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

		// Dibuja el mapa
		void drawMap(const bool drawId) {
			Graphics ^g = panelMap->CreateGraphics();
			SolidBrush ^sb = gcnew SolidBrush(Color::Red);
			Pen ^p = gcnew Pen(Color::Blue);
			System::String ^string = "";
			System::Drawing::Font ^myFont;
			Ground ground, groundTwo;
			Cell cell;
			std::string str;

			myFont = gcnew System::Drawing::Font("Arial", 7);

			for (int i = 0; i <= publicSizeHeightMax; i++) {
				for (int j = 0; j <= publicSizeWidthMax; j++) {
					cell.setPositionX(i);
					cell.setPositionY(j);

					if (listCell->findPositionXY(cell) != nullptr) {
						cell = listCell->findPositionXY(cell)->getData();
						
						groundTwo.setId(cell.getIdGround());
						//color = listColor->getDataByPosition(cell.getIdGround());
						ground = listGround->findData(groundTwo)->getData();
						//color = listColor[123];
						
						g->DrawRectangle(p, i * CELL_MAX_SIZE, j * CELL_MAX_SIZE, CELL_MAX_SIZE, CELL_MAX_SIZE);
						
						//MessageBox::Show(color.getColor(0).ToString() + "-" + color.getColor(1).ToString() + "-" + color.getColor(2).ToString());
						if (ground.getColor(0) == -1 || ground.getColor(1) == -1 || ground.getColor(2) == -1) {
							sb = gcnew SolidBrush(Color::LightGray);
						}
						else{
							string = "";
							//
							
							sb = gcnew SolidBrush(Color::FromArgb(ground.getColor(0), ground.getColor(1), ground.getColor(2)));
							g->FillRectangle(sb, i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 1, CELL_MAX_SIZE - 1, CELL_MAX_SIZE - 1);
							
							/*for (int i = 0; i < cell.getLastVisitPosition(); i++) {
								string += cell.getVisitCounter(i).ToString() + ", ";
								MessageBox::Show(cell.getId().ToString() + " - "+ cell.getLastVisitPosition().ToString() + " - Pos:"+i.ToString() + cell.getVisitCounter(i).ToString());
							}*/
							string = gcnew String(cell.getVisitCounter().c_str());
							if (string != "") {
								//MessageBox::Show(cell.getLastVisitPosition().ToString() + "-"+string);
								g->DrawString(string, myFont, gcnew SolidBrush(Color::Black), PointF(i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 41));
							}
							
						}
						if (drawId) {
							g->DrawString(cell.getIdGround().ToString(), this->Font, gcnew SolidBrush(Color::DarkBlue), PointF(i * CELL_MAX_SIZE + 10, j * CELL_MAX_SIZE + 10));
						}
						}
					else {
						//MessageBox::Show("not found at " + i.ToString() + "-" + j.ToString());
					}
					//txtPrueba2->Text = arrayData->getSize().ToString();
				}
			}
			//MessageBox::Show();
		}

		//Valida si todo está listo para jugar
		bool isReadyToPlay() {
			Point pointStart = panelMap->PointToClient(PointToScreen(pictureBox_Start->Location));
			Point pointGoal = panelMap->PointToClient(PointToScreen(pictureBox_Goal->Location));
			System::Windows::Forms::DialogResult ^confirm;
			String ^messageError;
			int errorCounter = 0;
			int counterArray = 0;

			

			if (pictureBox_Start->Location == pictureBoxStarPoint) {
				messageError += ++errorCounter + ".- Seleccione un punto de inicio\n";
			}
			if (pictureBox_Goal->Location == pictureBoxGoalPoint) {
				messageError += ++errorCounter + ".- Seleccione un punto de llegada\n";
			}
			if (comboBox_Player->Text == "") {
				messageError += ++errorCounter + ".- Seleccione un personaje a jugar\n";
			}

			if (!isValidGround(pointStart)) {
				messageError += ++errorCounter + ".- Seleccione un celda de inicio válida\n";
			}
			if (!isValidGround(pointGoal)) {
				messageError += ++errorCounter + ".- Seleccione un celda de llegada válida\n";
			}

			for each (ComboBox^ var in arrayComboBox)
			{
				if (var->Text == "") {
					messageError += ++errorCounter + ".- Elija un terreno para el ID: " +
						Int32::Parse(var->Name->Substring(14)) + "'\n";
				}
				counterArray++;
			}
			counterArray = 0;
			for each (TextBox^ var in arrayTextBox)
			{
				if (var->Text == "") {
					messageError += ++errorCounter + ".- Elija un coste para el terreno '" +
						arrayComboBox[counterArray]->Text + "'\n";
				}
				counterArray++;
			}
			
			if (errorCounter) {
				messageError = "Errores encontrados: " + errorCounter + "\n" +
					"Resuelva los siguientes errores antes de comenzar a jugar\n" + messageError;
				MessageBox::Show(messageError);
				return false;
			}
			else {
				//comboBox_Player->Enabled = false;
				return true;
			}
		}

		void disableObject() {
			for each (Button^ var in arrayButton)
			{
				var->Enabled = false;
			}
			for each (CheckBox^ var in arrayCheckBox)
			{
				var->Enabled = false;
			}
			for each (ComboBox^ var in arrayComboBox)
			{
				var->Enabled = false;
			}
			for each (TextBox^ var in arrayTextBox)
			{
				var->Enabled = false;
			}
			
			comboBox_Player->Enabled = false;
			pictureBox_Start->Enabled = false;
			pictureBox_Goal->Enabled = false;
			btn_play->Enabled = false;
		}

		void enableObject() {
			for each (Button^ var in arrayButton)
			{
				var->Enabled = true;
			}
			for each (CheckBox^ var in arrayCheckBox)
			{
				var->Enabled = true;
			}
			for each (ComboBox^ var in arrayComboBox)
			{
				var->Enabled = true;
			}
			for each (TextBox^ var in arrayTextBox)
			{
				var->Enabled = true;
			}

			comboBox_Player->Enabled = true;
			pictureBox_Start->Enabled = true;
			pictureBox_Goal->Enabled = true;
			btn_play->Enabled = true;
		}

		// //////////////////////////////////////////////////////// HERRAMIENTAS ////////////////////////////////////////////////////////////// //

		Ground *colorAux = new Ground();

		//Convierte de System::String a std::string
		void marshalString(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		//  Manda mensajes de error con un std::str
		void messageError(string str) {
			String ^systemStr = gcnew String(str.c_str());
			MessageBox::Show("Error: " + systemStr);
		}
	
		// Valida el click en el botón dinámico del color
		void btn_color_click(Object^ sender, EventArgs^ e) {
			Button ^btn;
			ColorClass *color = new ColorClass();
			Ground ground;
			int id, r, g, b;

			btn = safe_cast<Button^>(sender);
			id = Int32::Parse(btn->Name->Substring(9));
			
			MessageBox::Show(id.ToString());
			ground.setId(id);
			if (listGround->findData(ground) != nullptr) {
				if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					r = colorDialog1->Color.R;
					g= colorDialog1->Color.G;
					b = colorDialog1->Color.B;
					listGround->findData(ground)->getData().setColor(r, g, b);
					//listColor->findId(id)->getData().setColor(r,g,b);
					btn->BackColor = Color::FromArgb(r, g, b);
					//MessageBox::Show("color establecido como: " + listGround->findData(ground)->getData().getColor(0) + " - ");
					drawMap(true);
				}
			}

		}

		// Valida el cambio de nombre en el combobox dinámico del color
		void comboBox_Color_Name(Object^ sender, EventArgs^ e) {
			ComboBox ^comboBox;
			Button ^button = gcnew Button;
			Button ^buttonAux = gcnew Button;
			Ground ground;
			ColorClass color;
			Color newColor;
			string str;
			String ^systemStr;
			String ^systemStr2;
			int id;
			bool repeated = false;

			comboBox = safe_cast<ComboBox^>(sender);
			id = Int32::Parse(comboBox->Name->Substring(14));
			
			//MessageBox::Show("CHANGED");
			for each (ComboBox^ var in arrayComboBox)
			{
				//tabPage2->Controls->Find("btn_color1");
				if (comboBox->SelectedIndex == var->SelectedIndex && comboBox->Name != var->Name) {
					comboBox->SelectedIndex = -1;
					repeated = true;
					newColor = Color::Gray;
					if (listGround->findData(ground) != nullptr) {
						//MessageBox::Show("asdf: " + button->Name);
						listGround->findData(ground)->getData().setColor(newColor.Gray.R, newColor.Gray.G, newColor.Gray.B);
						drawMap(true);
					}
				}
			}
			if (!repeated) {
				for each(Object^ var in this->Controls) {
					if (var->GetType() == button->GetType()) {
						button = cli::safe_cast<Button^>(var);
						//MessageBox::Show("Changing1: " + button->Name);
						if (button->Name == BUTTON_NAME_COLOR + id.ToString()) {
							
							marshalString(comboBox->Text, str);
							color.setName(str);
							
							if (listColor->findData(color) != nullptr) {
								color = listColor->findData(color)->getData();
								buttonAux = button;
								newColor = Color::FromArgb(color.getColor(0), color.getColor(1), color.getColor(2));
								ground.setId(id);
								if (listGround->findData(ground) != nullptr) {
									//MessageBox::Show("asdf: " + button->Name);
									listGround->findData(ground)->getData().setColor(color.getColor(0), color.getColor(1), color.getColor(2));
									marshalString(comboBox->Text, str);
									listGround->findData(ground)->getData().setName(str);
									
									drawMap(true);
								}
								
								
							}
							
						}
					}
				}
			}
			buttonAux->BackColor = newColor;

			/*if (comboBox->Text == "Escoga un terreno") {
				MessageBox::Show("Error, debe de escoger un nombre válido");
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

		//Valida el cambio de si es válido el terreno para el juego
		void checkBox_Color_IsValid(Object^ sender, EventArgs^ e) {
			
			CheckBox ^checkBox;
			String ^string;
			Ground ground;
			int id;
			checkBox = safe_cast<CheckBox^>(sender);
			id = Int32::Parse(checkBox->Name->Substring(14));
			
			

			if (checkBox->Checked) {
				string = TEXTBOX_NAME_COLOR + id.ToString();
				for each (TextBox^ var in arrayTextBox) {
					if (var->Name == string) {
						var->Enabled = false;
						ground.setId(id);
						if (listGround->findData(ground) != nullptr) {
							listGround->findData(ground)->getData().setIsValid(false);
						}
					}
				}
			}
			if (!checkBox->Checked) {
				string = TEXTBOX_NAME_COLOR + id.ToString();
				for each (TextBox^ var in arrayTextBox) {
					if (var->Name == string) {
						var->Enabled = true;
						ground.setId(id);
						if (listGround->findData(ground) != nullptr) {
							listGround->findData(ground)->getData().setIsValid(true);
						}
					}
				}
			}
		}

		// Valida el cambio de valor en el combobox dinámico del color
		void textBox_Color_Float(Object^ sender, EventArgs^ e) {
			TextBox ^txt = safe_cast<TextBox^>(sender);
			Ground ground;
			int id;

			if (txt->Text == "") {
				txt->Text == "0";
			}
			else if (System::Text::RegularExpressions::Regex::IsMatch(txt->Text, "^[0-9]*[.]?[0-9]+$") ||
				System::Text::RegularExpressions::Regex::IsMatch(txt->Text, "^[0-9]+[.]$")) {
				// ((.[0-9]+)|[0-9]+)  
				id = Int32::Parse(txt->Name->Substring(13));
				ground.setId(id);
				if (listGround->findData(ground) != nullptr) {
					listGround->findData(ground)->getData().setValue(System::Math::Truncate((Convert::ToDouble(txt->Text) * 100)) / 100);
					txt->Text = (System::Math::Truncate((Convert::ToDouble(txt->Text) * 100)) / 100).ToString();
				}
			}
			else {
				MessageBox::Show("Ingrese un valor numérico correcto");
				txt->Text = "";
			}
		}

	// Cerrar completamente el programa
	private: System::Void Map_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		//Application::Exit();
	}
	private: System::Void button_SetColor_Click(System::Object^  sender, System::EventArgs^  e) {
		Button ^btn;
		int id, r, g, b;
	
		if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			r = colorDialog1->Color.R;
			g = colorDialog1->Color.G;
			b = colorDialog1->Color.B;

			colorAux->setColor(r, g, b);

			//MessageBox::Show("color establecido como: " + colorAux->getColor(0).ToString() + " - ");
		}
	}
	private: System::Void button_AddColor_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^systemStr = "";
		string str;

		/*if (textBox_GroundName->Text == "") {
			systemStr += "Ingrese un nombre para el terreno\n";
		}*/
		if (colorAux->getColor(0) == -1) {
			systemStr += "Debe establecer un color primero";
		}
		if (systemStr != "") {
			MessageBox::Show("Error, se presentaron los siguientes errores al ingresar el terreno: \n" + systemStr);
		}
		else {
			
			//marshalString(textBox_GroundName->Text, str);
			colorAux->setName(str);
			colorAux->setId(listGround->getLast()->getData().getId() + 1);

			listGround->insertData(*colorAux);
			if (listGround->findData(*colorAux)) {
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
		pictureBox_PlayerIcon->Image = bitMap;
		
		//MessageBox::Show("Function");
	}
	private: System::Void Map_Shown(System::Object^  sender, System::EventArgs^  e) {
		this->Hide();
		chargeMap(fileNameMapGlobal);
		chargeColorFile();
		chargeColor();
		chargePlayerFile();
		panelMap->SendToBack();
		panelMap->Invalidate();
		auto execAssem = System::Reflection::Assembly::GetExecutingAssembly();
		auto resourceName = execAssem->GetName()->Name + ".Custom";
		auto resourceManager = gcnew Resources::ResourceManager(resourceName, execAssem);
		auto reader = cli::safe_cast<Bitmap^>(resourceManager->GetObject("Start"));

		pictureBox_Start->Image = reader;
		if (!isCorruptFile) {
			this->Show();
		}
		}
	
			 
			 /////////////////////// Eventos para Drag & drop de estado inicial y final //////////////////////////////77
	Point ^coordenadas = gcnew Point;
	private: System::Void pictureBox_Start_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		PictureBox ^pictureBox;
		//pictureBox_Start->DoDragDrop(pictureBox_Start, DragDropEffects::Move);
		pictureBox = safe_cast<PictureBox^>(sender);

		pictureBox->Height = 40;
		pictureBox->Width = 40;

		coordenadas->Y = MousePosition.Y - pictureBox->Top;
		coordenadas->X = MousePosition.X - pictureBox->Left;
		
		//pictureBox_Start->Location = Point(coordenadas->X, coordenadas->Y);
	}
	private: System::Void pictureBox_Start_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		PictureBox ^pictureBox;

		if (e->Button == Windows::Forms::MouseButtons::Left) {
			pictureBox = safe_cast<PictureBox^>(sender);
			pictureBox->Top = MousePosition.Y - coordenadas->Y;
			pictureBox->Left = MousePosition.X - coordenadas->X;
			panelMap->SendToBack();
			//

		}
	}
	private: System::Void pictureBox_Start_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		Cell cell;
		PictureBox ^pictureBox;
		pictureBox = safe_cast<PictureBox^>(sender);
		int locationX;
		int locationY;
		pictureBox->Height = 40;
		pictureBox->Width = 40;

		Point point = panelMap->PointToClient(Cursor->Position);
		Point auxPoint;
		locationX = (int)(point.X / CELL_MAX_SIZE);
		locationY = (int)(point.Y / CELL_MAX_SIZE);

		cell.setPositionX(locationX);
		cell.setPositionY(locationY);
		
		/*MessageBox::Show(point.ToString() + " location: " + locationX.ToString() + ", "+locationY.ToString() + "\n" +
		Cursor->Position.X + ", " + Cursor->Position.Y);*/
		//if (point.X < 0 || point.Y < 0 || point.X > 750 || point.Y > 750) {
		if (!isValidPositionPanelMap(point)) {
			if (pictureBox_Start->Name == pictureBox->Name) {
				pictureBox->Location = pictureBoxStarPoint;
				pictureBox->Height = 50;
				pictureBox->Width = 50;
				}
			else {
				pictureBox->Location = pictureBoxGoalPoint;
				pictureBox->Height = 50;
				pictureBox->Width = 50;
				}
			}
		else if (!isValidGround(point)) {
			MessageBox::Show("Error, no puede poner el punto de inicio o final en un terreno con la casilla marcada N/A");
		}
		else {
			if (listCell->findPositionXY(cell) != nullptr) {
				if (pictureBox->Name == pictureBox_Start->Name) {
					pointStart = listCell->findPositionXY(cell)->getData().getId();
					auxPoint = pictureBoxStarPoint;
				}
				else {
					pointGoal = listCell->findPositionXY(cell)->getData().getId();
					auxPoint = pictureBoxGoalPoint;
				}
				//MessageBox::Show(start);
				if (pointStart == pointGoal) {
					pictureBox->Location = auxPoint;
					pictureBox->Height = 50;
					pictureBox->Width = 50;
					
				}
				else {
					pictureBox->Location = Point(panelMap->Location.X + (locationX * CELL_MAX_SIZE) +
						5, panelMap->Location.Y + (locationY * CELL_MAX_SIZE) + 5);
					pictureBox->Height = 30;
					pictureBox->Width = 30;
				}
			}
			else {
				pictureBox->Location = pictureBoxStarPoint;
			}
		}
	}
	
	// Permitir un Drag&Drop en el panel con movimiento
	private: System::Void panelMap_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		e->Effect = DragDropEffects::Move;
	}
	
	// Permitir un Drag&Drop en el panel
	private: System::Void panelMap_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		panelMap->Controls->Add(pictureBox_Start);
		Button ^btn;
		ColorClass *color = new ColorClass();
		int id, r, g, b;

		btn = safe_cast<Button^>(sender);
		MessageBox::Show("Entry");
	}
	
	// Pinta el panel
	private: System::Void panelMap_Paint_1(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		UpdateGraphicsBuffer();
		if (isPlaying) {
			drawMap(false);
		}
		else {
			drawMap(true);
		}
		
	}
	
	// Evento click para iniciar el juego
	private: System::Void btn_play_Click(System::Object^  sender, System::EventArgs^  e) {
		
		//pictureBox_Start->SendToBack();
		panelMap->SendToBack();
		
		if (isReadyToPlay()) {
			isPlaying = true;
			disableObject();
			drawMap(false);
			pictureBox_Player->Location = pictureBox_Start->Location;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);
			Map::Focus();
		}
		//panelMap->Focus();
		
	}
	
	// Detectar el click de las teclas para mover el jugador
	private: System::Void Map_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		Point point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
		Point auxPoint = point;
		Point auxAuxPoint = auxPoint;
		Cell cell;
		stringstream toStr;
		int locationX, locationY, intAux;
		bool moved = false;
		if (pictureBox_Player->Location != pictureBox_Goal->Location) {
			//FLECHA IZQUIERDA
			if (e->KeyValue.ToString() == "37") {
				point.X = point.X - CELL_MAX_SIZE;
				auxPoint= Point(point.X, auxPoint.Y);
				if (isValidGround(auxPoint) && isValidPositionPanelMap(point)) {
					pictureBox_Player->Location = Point(pictureBox_Player->Location.X - CELL_MAX_SIZE,
						pictureBox_Player->Location.Y);
					moved = true;
				}
			}
			//FLECHA ARRIBA
			else if (e->KeyValue.ToString() == "38") {
				point.Y = point.Y - CELL_MAX_SIZE;
				auxPoint = Point(auxPoint.X, point.Y);
				if (isValidGround(auxPoint) && isValidPositionPanelMap(point)) {
					pictureBox_Player->Location = Point(pictureBox_Player->Location.X,
						pictureBox_Player->Location.Y - CELL_MAX_SIZE);
					moved = true;
				}
			}
			//FLECHA ABAJO
			else if (e->KeyValue.ToString() == "40") {
				/*MessageBox::Show("LocX: " + locationX.ToString() + " LocY: " + locationY.ToString() + " - " +
					pictureBox_Player->Location.Y + " - " + panelMap->MousePosition.Y);*/
				point.Y = point.Y + CELL_MAX_SIZE;
				auxPoint = Point(auxPoint.X, point.Y);
				if (isValidGround(auxPoint) && isValidPositionPanelMap(point)) {
					pictureBox_Player->Location = Point(pictureBox_Player->Location.X,
						pictureBox_Player->Location.Y + CELL_MAX_SIZE);
					moved = true;
				}
			}

			//FLECHA DERECHA
			else if (e->KeyValue.ToString() == "39") {
				point.X = point.X + CELL_MAX_SIZE;
				auxPoint = Point(point.X, auxPoint.Y);
				if (isValidGround(auxPoint) && isValidPositionPanelMap(point)) {
					pictureBox_Player->Location = Point(pictureBox_Player->Location.X + CELL_MAX_SIZE,
						pictureBox_Player->Location.Y);
					moved = true;
				}
			}
			else {
				// Nothing
			}
			if (moved) {
				locationX = (int)(auxAuxPoint.X / CELL_MAX_SIZE);
				locationY = (int)(auxAuxPoint.Y / CELL_MAX_SIZE);

				cell.setPositionX(locationX);
				cell.setPositionY(locationY);

				if (listCell->findPositionXY(cell) != nullptr) {
					intAux = ++visit;
					toStr.str("");
					toStr << intAux;
					listCell->findPositionXY(cell)->getData().setVisitCounter(toStr.str());
					cell = listCell->findPositionXY(cell)->getData();
					//MessageBox::Show("Here " + cell.getLastVisitPosition().ToString());
					//MessageBox::Show(intAux.ToString()+", "+listCell->findPositionXY(cell)->getData().getVisitCounter(cell.getLastVisitPosition()-1).ToString());
					drawMap(false);
				}
			}
		}
		if (pictureBox_Player->Location == pictureBox_Goal->Location) {
			MessageBox::Show("Has llegado a la meta \n");
			pictureBox_Player->Location = pictureBox_Start->Location;
			enableObject();
		}
	}
	
	// Valida que el jugador no se salga del mapa de juego
	bool isValidPositionPanelMap(Point ^point) {
		Cell cell;
		//if (point->X < 0 || point->Y < 0 || point->X > 750 || point->Y > 750) {
		if (point->X < 0 || point->Y < 0 || point->X > panelMap->Size.Width || point->Y > panelMap->Size.Height) {
			//pictureBox_Player->Location = pictureBox_Player->Location;
			return false;
		}
		else {
			return true;
		}

	}
	bool isValidGround(Point auxPoint) {
		Cell cell;
		Ground ground;
		int locationX, locationY, intAux;

		locationX = (int)(auxPoint.X / CELL_MAX_SIZE);
		locationY = (int)(auxPoint.Y / CELL_MAX_SIZE);

		cell.setPositionX(locationX);
		cell.setPositionY(locationY);

		if (listCell->findPositionXY(cell) != nullptr) {
			ground.setId(listCell->findPositionXY(cell)->getData().getIdGround());
			if (listGround->findData(ground) != nullptr) {
				if (listGround->findData(ground)->getData().getIsValid()) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		return false;
	}


	private: System::Void panelMap_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == Windows::Forms::MouseButtons::Left) {
			ToolTip ^tt = gcnew ToolTip();
			IWin32Window ^win = this;
			Point point = panelMap->PointToClient(MousePosition);

			System::String^ informacion = toolTipMensaje(point);

			tt->Show(informacion, win, PointToClient(MousePosition).X + 10, PointToClient(MousePosition).Y+30, 2000);
			//tt->Show(informacion, win, PointToClient(MousePosition), 2000);
		}
	}

	System::String^ toolTipMensaje(Point point) {
		System::String^ informacion;
		System::String^ coordenadaX;
		int coordenadaY;
		Cell cell;
		Cell cellAux;
		char letra = 'A';


		//Coordenada
		int locationX;
		int locationY;

		locationX = (int)(point.X / CELL_MAX_SIZE);
		locationY = (int)(point.Y / CELL_MAX_SIZE);

		cell.setPositionX(locationX);
		cell.setPositionY(locationY);

		if (listCell->findPositionXY(cell) != nullptr) {
			cellAux = listCell->getData(listCell->findPositionXY(cell));

			for (int i = 0; i < cellAux.getPositionX(); i++) {
				letra += 1;
			}
			coordenadaX = System::Char::ToString(letra);
			coordenadaY = cellAux.getPositionY() + 1;

			informacion = "Coordenada: " + coordenadaX + "-" + coordenadaY.ToString() + "\n";

			Ground groundAux;
			groundAux.setId(cellAux.getIdGround());

			//DESCOMENTAR NOMBRE (Sig 2 lineas)
			if (listGround->findData(groundAux) != nullptr) {
				groundAux = listGround->findData(groundAux)->getData();
			}
			else {
				MessageBox::Show("Not found " + groundAux.getId().ToString());
			}
			informacion = informacion + "Terreno: " + gcnew String(groundAux.getName().c_str()) + "\n";

			//Costo
			if (groundAux.getIsValid()) {
				informacion = informacion + "Costo: " + groundAux.getValue().ToString() + "\n";
			}
			else {
				informacion = informacion + "Costo: N/A\n";
			}
			//Inicial
			if (pointStart == cellAux.getId()) {
				informacion = informacion + "Inicial: Sí \n";
			}
			else {
				informacion = informacion + "Inicial: No \n";
			}

			//Final
			if (pointGoal == cellAux.getId()) {
				informacion = informacion + "Final: Sí \n";
			}
			else {
				informacion = informacion + "Final: No \n";
			}
		}
		return informacion;
	}
	
	private: System::Void pictureBox_Player_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == Windows::Forms::MouseButtons::Left) {
		ToolTip ^tt = gcnew ToolTip();
		IWin32Window ^win = this;
		Point point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));

		System::String^ informacion = toolTipMensaje(point);

		tt->Show(informacion, win, PointToClient(MousePosition).X + 10, PointToClient(MousePosition).Y + 30, 2000);
		//tt->Show(informacion, win, PointToClient(MousePosition), 2000);
	}
}
};
}
