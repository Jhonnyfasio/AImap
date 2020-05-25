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
#include "costoJugador.h"
#include "arbol.h"
#include "Tree.h"

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
	private: System::Windows::Forms::PictureBox^  pictureBox_Start;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  txtPrueba2;
	private: System::Windows::Forms::Panel^  panelMap;
	private: System::Windows::Forms::Button^  button_Play;
	private: System::Windows::Forms::PictureBox^  pictureBox_Goal;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::PictureBox^  pictureBox_Player;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  button_Reset;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  comboBox_Priority;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ComboBox^  comboBox_Algoritmos;
	private: System::Windows::Forms::Timer^ timer1;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox2;

	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::ComboBox^  comboBox_Distance;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  btn_ShowMap;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Panel^  picTree;

	private: BufferedGraphics ^graphicsBuffer;

	Collection<Cell> *listCell;
	Collection<Ground> *listGround;
	Collection<Player> *listPlayer;
	Collection<Ground> *listColorInUse;
	Collection<ColorClass> *listColor;
	Collection<CostoJugador> *listCostoJugador;

	Collection<Vertice*> *listaVertices;
	Collection<Vertice*> *pilaVertices;
	Collection<Vertice*> *listVisitados;
	Collection<Vertice*> *path;
	Collection<Vertice*> *listVerticesAuxGlobal;
	Arbol *arbol;
	cli::array<ComboBox^>^ arrayComboBox;
	cli::array<TextBox^>^ arrayTextBox;
	cli::array<Button^>^ arrayButton;
	cli::array<CheckBox^>^ arrayCheckBox;
	cli::array<String^>^ arrayPriority;
	cli::array <String^>^ priority;
	String ^fileNameMapGlobal;
	Point pictureBoxStarPoint, pictureBoxGoalPoint, pictureBoxPlayerPoint;
	Graphics ^g;


	int pointGoal = -1;
	int pointStart = -1;
	int publicSizeHeightMax;
	int publicSizeWidthMax;
	int visit = 0;
	bool isPlaying = false;
	bool won = false;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox3;
			 bool isCorruptFile = false;

	public:

		Map(void)
		{
			InitializeComponent();

		}

		Map(String ^fileNameMap) {
			InitializeComponent();
			//mainMenu = menuMap;
			g = panelMap->CreateGraphics();
			listCell = new Collection<Cell>;
			listGround = new Collection<Ground>;
			listPlayer = new Collection<Player>;
			listColor = new Collection<ColorClass>;
			listCostoJugador = new Collection<CostoJugador>;
			listVerticesAuxGlobal = new Collection<Vertice*>;

			/*Howtoo::TreeNode *root = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("root"));
			Howtoo::TreeNode *a_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("A"));
			Howtoo::TreeNode *b_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("B"));
			Howtoo::TreeNode *c_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("C"));
			Howtoo::TreeNode *d_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("D"));
			Howtoo::TreeNode *e_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("E"));
			Howtoo::TreeNode *f_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("F"));
			Howtoo::TreeNode *g_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("G"));
			Howtoo::TreeNode *h_node = new Howtoo::TreeNode(Howtoo::TreeNode::CircleNode("H"));

			root->AddChild(a_node);
			root->AddChild(b_node);
			a_node->AddChild(c_node);
			a_node->AddChild(d_node);
			b_node->AddChild(e_node);
			b_node->AddChild(f_node);
			b_node->AddChild(g_node);
			e_node->AddChild(h_node);*/

			fileNameMapGlobal = fileNameMap;

			pictureBoxStarPoint = pictureBox_Start->Location;
			pictureBoxGoalPoint = pictureBox_Goal->Location;
			pictureBoxPlayerPoint = pictureBox_Player->Location;

			createArrayPriority();
			comboBox_Priority->SelectedIndex = 0;
			comboBox_Algoritmos->SelectedIndex = 1;
			comboBox_Distance->SelectedIndex = 0;
			//UpdateGraphicsBuffer();
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
			this->pictureBox_Start = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->txtPrueba2 = (gcnew System::Windows::Forms::TextBox());
			this->panelMap = (gcnew System::Windows::Forms::Panel());
			this->button_Play = (gcnew System::Windows::Forms::Button());
			this->pictureBox_Goal = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox_Player = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button_Reset = (gcnew System::Windows::Forms::Button());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->comboBox_Priority = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->comboBox_Algoritmos = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->comboBox_Distance = (gcnew System::Windows::Forms::ComboBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->btn_ShowMap = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->picTree = (gcnew System::Windows::Forms::Panel());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_PlayerIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Start))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Goal))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Player))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->flowLayoutPanel2->SuspendLayout();
			this->picTree->SuspendLayout();
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
			this->pictureBox_PlayerIcon->Location = System::Drawing::Point(800, 99);
			this->pictureBox_PlayerIcon->Name = L"pictureBox_PlayerIcon";
			this->pictureBox_PlayerIcon->Size = System::Drawing::Size(220, 220);
			this->pictureBox_PlayerIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_PlayerIcon->TabIndex = 13;
			this->pictureBox_PlayerIcon->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(796, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(80, 20);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Personaje";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// comboBox_Player
			// 
			this->comboBox_Player->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_Player->FormattingEnabled = true;
			this->comboBox_Player->Location = System::Drawing::Point(799, 64);
			this->comboBox_Player->Name = L"comboBox_Player";
			this->comboBox_Player->Size = System::Drawing::Size(121, 21);
			this->comboBox_Player->TabIndex = 11;
			this->comboBox_Player->SelectedIndexChanged += gcnew System::EventHandler(this, &Map::comboBox_Player_SelectedIndexChanged);
			// 
			// pictureBox_Start
			// 
			this->pictureBox_Start->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->pictureBox_Start->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_Start.Image")));
			this->pictureBox_Start->Location = System::Drawing::Point(26, 29);
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
			this->textBox1->Location = System::Drawing::Point(523, 19);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(87, 20);
			this->textBox1->TabIndex = 16;
			// 
			// txtPrueba2
			// 
			this->txtPrueba2->Enabled = false;
			this->txtPrueba2->Location = System::Drawing::Point(27, 85);
			this->txtPrueba2->Name = L"txtPrueba2";
			this->txtPrueba2->ReadOnly = true;
			this->txtPrueba2->Size = System::Drawing::Size(129, 20);
			this->txtPrueba2->TabIndex = 17;
			this->txtPrueba2->Visible = false;
			// 
			// panelMap
			// 
			this->panelMap->AllowDrop = true;
			this->panelMap->AutoScroll = true;
			this->panelMap->AutoSize = true;
			this->panelMap->BackColor = System::Drawing::Color::Silver;
			this->panelMap->ForeColor = System::Drawing::Color::Black;
			this->panelMap->Location = System::Drawing::Point(26, 130);
			this->panelMap->Name = L"panelMap";
			this->panelMap->Size = System::Drawing::Size(763, 750);
			this->panelMap->TabIndex = 14;
			this->panelMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Map::panelMap_Paint_1);
			this->panelMap->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Map::panelMap_MouseDown);
			// 
			// button_Play
			// 
			this->button_Play->BackColor = System::Drawing::Color::LimeGreen;
			this->button_Play->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Play->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button_Play->Location = System::Drawing::Point(546, 14);
			this->button_Play->Name = L"button_Play";
			this->button_Play->Size = System::Drawing::Size(120, 66);
			this->button_Play->TabIndex = 15;
			this->button_Play->Text = L"Jugar";
			this->button_Play->UseVisualStyleBackColor = false;
			this->button_Play->Click += gcnew System::EventHandler(this, &Map::btn_play_Click);
			// 
			// pictureBox_Goal
			// 
			this->pictureBox_Goal->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->pictureBox_Goal->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_Goal.Image")));
			this->pictureBox_Goal->Location = System::Drawing::Point(101, 29);
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
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(23, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 20);
			this->label1->TabIndex = 23;
			this->label1->Text = L"Inicio";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(97, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(45, 20);
			this->label3->TabIndex = 24;
			this->label3->Text = L"Meta";
			// 
			// pictureBox_Player
			// 
			this->pictureBox_Player->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox_Player.Image")));
			this->pictureBox_Player->Location = System::Drawing::Point(957, 40);
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
			this->label4->Location = System::Drawing::Point(1056, 45);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(218, 13);
			this->label4->TabIndex = 26;
			this->label4->Text = L"Color           Terreno            Alcance     Coste";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::DarkRed;
			this->label6->Location = System::Drawing::Point(1044, 12);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(248, 25);
			this->label6->TabIndex = 30;
			this->label6->Text = L"   Establecer Terrenos    ";
			// 
			// button_Reset
			// 
			this->button_Reset->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_Reset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Reset->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button_Reset->Location = System::Drawing::Point(672, 15);
			this->button_Reset->Name = L"button_Reset";
			this->button_Reset->Size = System::Drawing::Size(120, 66);
			this->button_Reset->TabIndex = 34;
			this->button_Reset->Text = L"Volver a Jugar";
			this->button_Reset->UseVisualStyleBackColor = false;
			this->button_Reset->Click += gcnew System::EventHandler(this, &Map::button_Reset_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::DarkRed;
			this->label8->Location = System::Drawing::Point(790, 13);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(239, 24);
			this->label8->TabIndex = 35;
			this->label8->Text = L"         Elegir Personaje         ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::DarkRed;
			this->label5->Location = System::Drawing::Point(795, 336);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(536, 25);
			this->label5->TabIndex = 37;
			this->label5->Text = L"                                       Árbol                                     "
				L"   ";
			// 
			// comboBox_Priority
			// 
			this->comboBox_Priority->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox_Priority->FormattingEnabled = true;
			this->comboBox_Priority->Items->AddRange(gcnew cli::array< System::Object^  >(24) {
				L"01.- Abajo, Izquierda, Arriba, Derecha (🢃, 🢀, 🢁, 🢂)",
					L"02.- Abajo, Izquierda, Derecha, Arriba (🢃, 🢀, 🢂, 🢁)", L"03.- Abajo, Arriba, Derecha, Izquierda (🢃, 🢁, 🢂, 🢀)", L"04.- Abajo, Arriba, Izquierda, Derecha (🢃, 🢁, 🢀, 🢂)",
					L"05.- Abajo, Derecha, Izquierda, Arriba (🢃, 🢂, 🢀, 🢁)", L"06.- Abajo, Derecha, Arriba, Izquierda (🢃, 🢂, 🢁, 🢀)", L"07.- Izquierda, Arriba, Derecha, Abajo (🢀, 🢁, 🢂, 🢃)",
					L"08.- Izquierda, Arriba, Abajo, Derecha (🢀, 🢁, 🢃, 🢂)", L"09.- Izquierda, Derecha, Abajo, Arriba (🢀, 🢂, 🢃, 🢁)", L"10.- Izquierda, Derecha, Arriba, Abajo (🢀, 🢂, 🢁, 🢃)",
					L"11.- Izquierda, Abajo, Arriba, Derecha (🢀, 🢃, 🢁, 🢂)", L"12.- Izquierda, Abajo, Derecha, Arriba (🢀, 🢃, 🢂, 🢁)", L"13.- Arriba, Derecha, Abajo, Izquierda (🢁, 🢂, 🢃, 🢀)",
					L"14.- Arriba, Derecha, Izquierda, Abajo (🢁, 🢂, 🢀, 🢃)", L"15.- Arriba, Abajo, Derecha, Izquierda (🢁, 🢃, 🢂, 🢀)", L"16.- Arriba, Abajo, Izquierda, Derecha (🢁, 🢃, 🢀, 🢂)",
					L"17.- Arriba, Izquierda, Derecha, Abajo (🢁, 🢀, 🢂, 🢃)", L"18.- Arriba, Izquierda, Abajo, Derecha (🢁, 🢀, 🢃, 🢂)", L"19.- Derecha, Abajo, Izquierda, Arriba (🢂, 🢃, 🢀, 🢁)",
					L"20.- Derecha, Abajo, Arriba, Izquierda (🢂, 🢃, 🢁, 🢀)", L"21.- Derecha, Izquierda, Arriba, Abajo (🢂, 🢀, 🢁, 🢃)", L"22.- Derecha, Izquierda, Abajo, Arriba (🢂, 🢀, 🢃, 🢁)",
					L"23.- Derecha, Arriba, Abajo, Izquierda (🢂, 🢁, 🢃, 🢀)", L"24.- Derecha, Arriba, Izquierda, Abajo (🢂, 🢁, 🢀, 🢃)"
			});
			this->comboBox_Priority->Location = System::Drawing::Point(165, 80);
			this->comboBox_Priority->Name = L"comboBox_Priority";
			this->comboBox_Priority->Size = System::Drawing::Size(316, 24);
			this->comboBox_Priority->TabIndex = 38;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(161, 60);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(71, 20);
			this->label7->TabIndex = 39;
			this->label7->Text = L"Prioridad";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(163, 9);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(76, 20);
			this->label9->TabIndex = 41;
			this->label9->Text = L"Algoritmo";
			// 
			// comboBox_Algoritmos
			// 
			this->comboBox_Algoritmos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->comboBox_Algoritmos->FormattingEnabled = true;
			this->comboBox_Algoritmos->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Manual", L"Algoritmo de Profundidad",
					L"Algoritmo de Coste uniforme", L"Algoritmo Voraz primero el mejor", L"Algoritmo A*"
			});
			this->comboBox_Algoritmos->Location = System::Drawing::Point(165, 29);
			this->comboBox_Algoritmos->Name = L"comboBox_Algoritmos";
			this->comboBox_Algoritmos->Size = System::Drawing::Size(212, 24);
			this->comboBox_Algoritmos->TabIndex = 40;
			this->comboBox_Algoritmos->SelectedIndexChanged += gcnew System::EventHandler(this, &Map::comboBox_Algoritmos_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(489, 85);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 42;
			this->button1->Text = L"Aristas";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Map::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Map::timer1_Tick);
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(587, 80);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(206, 20);
			this->textBox2->TabIndex = 43;
			this->textBox2->Visible = false;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->InterceptArrowKeys = false;
			this->numericUpDown1->Location = System::Drawing::Point(656, 88);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			this->numericUpDown1->TabIndex = 46;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Map::numericUpDown1_ValueChanged);
			// 
			// comboBox_Distance
			// 
			this->comboBox_Distance->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox_Distance->FormattingEnabled = true;
			this->comboBox_Distance->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Manhattan", L"Euclideana" });
			this->comboBox_Distance->Location = System::Drawing::Point(398, 29);
			this->comboBox_Distance->Name = L"comboBox_Distance";
			this->comboBox_Distance->Size = System::Drawing::Size(142, 24);
			this->comboBox_Distance->TabIndex = 47;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(394, 9);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(75, 20);
			this->label10->TabIndex = 48;
			this->label10->Text = L"Distancia";
			// 
			// btn_ShowMap
			// 
			this->btn_ShowMap->BackColor = System::Drawing::Color::LimeGreen;
			this->btn_ShowMap->Enabled = false;
			this->btn_ShowMap->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_ShowMap->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btn_ShowMap->Location = System::Drawing::Point(805, 325);
			this->btn_ShowMap->Name = L"btn_ShowMap";
			this->btn_ShowMap->Size = System::Drawing::Size(94, 32);
			this->btn_ShowMap->TabIndex = 49;
			this->btn_ShowMap->Text = L"Árbol";
			this->btn_ShowMap->UseVisualStyleBackColor = false;
			this->btn_ShowMap->Click += gcnew System::EventHandler(this, &Map::btn_ShowMap_Click);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->AutoScroll = true;
			this->flowLayoutPanel2->Controls->Add(this->picTree);
			this->flowLayoutPanel2->Location = System::Drawing::Point(802, 374);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(514, 503);
			this->flowLayoutPanel2->TabIndex = 52;
			// 
			// picTree
			// 
			this->picTree->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->picTree->Controls->Add(this->textBox3);
			this->picTree->Location = System::Drawing::Point(3, 3);
			this->picTree->Name = L"picTree";
			this->picTree->Size = System::Drawing::Size(499, 479);
			this->picTree->TabIndex = 53;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(244, 3);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(205, 428);
			this->textBox3->TabIndex = 54;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(596, 91);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(54, 13);
			this->label11->TabIndex = 53;
			this->label11->Text = L"Velocidad";
			// 
			// Map
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1334, 889);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->flowLayoutPanel2);
			this->Controls->Add(this->btn_ShowMap);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->comboBox_Distance);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->comboBox_Algoritmos);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->comboBox_Priority);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button_Reset);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button_Play);
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
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->HelpButton = true;
			this->Location = System::Drawing::Point(30, 30);
			this->Name = L"Map";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Map";
			this->Shown += gcnew System::EventHandler(this, &Map::Map_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_PlayerIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Start))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Goal))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Player))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->picTree->ResumeLayout(false);
			this->picTree->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

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
							if (str == "" && !readerFile.eof()) {
								messageError("No se admiten valores nulos (dobles comas)");
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
								marshalString((row + 1).ToString(), str);
								marshalString((column).ToString(), str2);
								messageError("Error, el mapa tiene lados irregulares (Linea: " + str + ", Columna: " + str2 + ")");
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
							if (str == "" && !readerFile.eof()) {
								messageError("No se admiten valores nulos.");
								isCorruptFile = true;
							}
							//txtPrueba->Text += cell.getId().ToString() + "\r\n";
							str = "";
						}
						// Valida caracter inválido
						else {
							marshalString(fileNameMap, str);
							MessageBox::Show("No se puede leer el archivo '" + fileNameMap + "', archivo corrupto en:\n" +
								"Fila: " + (row + 1).ToString() + "\nColumna: " + (column + 1).ToString() + ".\n" +
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
				label->Location = Point(43 + (i * CELL_MAX_SIZE), 110);
				this->Controls->Add(label);
			}
			for (int j = 0; j < publicSizeHeightMax; j++) {
				label = gcnew Label;
				label->Size = System::Drawing::Size(20, 20);
				label->TextAlign = System::Drawing::ContentAlignment::TopRight;
				label->Text = (j + 1).ToString();
				label->Location = Point(3, 145 + (j * CELL_MAX_SIZE));
				this->Controls->Add(label);
			}
		}

		// Crea botones, textbos y combobox dinámicos para los colores
		void chargeColor() {
			ArrayList ^myArray = gcnew ArrayList();
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
				int posX = 1042;
				int posY = 60;
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
				btn->Location = Point(posX, i * 25 + posY);
				btn->Size = System::Drawing::Size(65, 23);
				btn->BackColor = Color::Gray;
				//Creando los eventos del botón dinámico
				btn->Click += gcnew System::EventHandler(this, &Map::btn_color_click);
				arrayButton[i] = btn;

				systemStr = COMBOBOX_NAME_COLOR + idStr;
				comboBox->Name = systemStr;
				//comboBox->Location = Point(135, i * 25);
				comboBox->Location = Point(posX + 70, i * 25 + posY);
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
				checkBox->Location = Point(posX + 145, i * 25 + posY);
				checkBox->Size = System::Drawing::Size(46, 17);
				checkBox->Text = "N/A";
				checkBox->CheckedChanged += gcnew System::EventHandler(this, &Map::checkBox_Color_IsValid);
				arrayCheckBox[i] = checkBox;

				textBox->Name = TEXTBOX_NAME_COLOR + idStr;
				//systemStr = "numericUpDown_Color" + idStr;
				//textBox->Location = Point(260, i * 25);
				textBox->Location = Point(posX + 195, i * 25 + posY);
				textBox->Size = System::Drawing::Size(50, 23);
				textBox->Text = "0";
				//textBox->Leave += gcnew System::EventHandler(this, &Map::textBox_Color_Float);
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
			//MessageBox::Show("Encontre: " + nameColor[0], " - Lenght: "+ nameColor->Length.ToString() );
			for (int i = 0; i < nameColor->Length - 1; i += 4)
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

		// Carga los costos para cada terreno dependiendo el jugador
		void chargeCostoJugadorFile() {
			CostoJugador costoJugador;
			Ground ground;
			std::string str, str2, str3;
			cli::array <String^>^ generalString = gcnew cli::array<String^>(200);
			cli::array <String^>^ costosPorJugador = gcnew cli::array<String^>(5);
			String^ algo;
			int i = 0;

			//System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Map::typeid));
			auto execAssem = System::Reflection::Assembly::GetExecutingAssembly();
			auto resourceName = execAssem->GetName()->Name + ".Custom";
			auto resourceManager = gcnew Resources::ResourceManager(resourceName, execAssem);
			auto reader = cli::safe_cast<String^>(resourceManager->GetObject("Costos"));

			//algo = reader->ReadToEnd();
			generalString = reader->Split('|');

			//MessageBox::Show(reader + " - "+ generalString + " - " + generalString->Length);
			for (int i = 0; i < generalString->Length - 1; i++)
			{
				costosPorJugador = generalString[i]->Split(',');

				marshalString(costosPorJugador[0], str);
				costoJugador.setName(str);

				marshalString(costosPorJugador[1], str);
				costoJugador.setGroundName(str);

				costoJugador.setCosto(Int32::Parse(costosPorJugador[2]));

				listCostoJugador->insertData(costoJugador);
				//MessageBox::Show("Cargando jugadore costo: " + costosPorJugador[0] + " - " + costosPorJugador[1] +
				//costosPorJugador[2]);
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

			player.setId(3);
			player.setName("Ralph");
			listPlayer->insertData(player);

			player.setId(4);
			player.setName("Robot");
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
			//this->panelMap->SetStyle(ControlStyles::DoubleBuffer, true);

			BufferedGraphicsContext ^bufferContext = BufferedGraphicsManager::Current;
			BufferedGraphics ^myBuffer;
			//graphicsBuffer = bufferContext->Allocate(this->CreateGraphics(), this->DisplayRectangle);
			myBuffer = bufferContext->Allocate(panelMap->CreateGraphics(), panelMap->DisplayRectangle);



			SolidBrush ^sb = gcnew SolidBrush(Color::Red);
			Pen ^p = gcnew Pen(Color::Blue);
			System::String ^string = "";
			System::Drawing::Font ^myFont;
			Ground ground, groundTwo;
			Cell cell, cellAux;
			Vertice *vertice;
			std::string str;
			myFont = gcnew System::Drawing::Font("Arial", 7);

			for (int i = 0; i <= publicSizeHeightMax; i++) {
				for (int j = 0; j <= publicSizeWidthMax; j++) {
					cell.setPositionX(i);
					cell.setPositionY(j);

					if (listCell->findPositionXY(cell) != nullptr) {
						cell = listCell->findPositionXY(cell)->getData();
						groundTwo.setId(cell.getIdGround());
						ground = listGround->findData(groundTwo)->getData();

						if (won) {
							Collection<Vertice*>* listAux = new Collection<Vertice*>;
							Pen ^pAux = gcnew Pen(Color::Yellow);
							pAux->Width = 2.0;
							while (!path->isEmpty()) {
								vertice = path->dequeue();
								cellAux = vertice->elemento;
								//string += gcnew String(cell2.getName().c_str()) + ",";
								myBuffer->Graphics->DrawRectangle(pAux, cellAux.getPositionX() * CELL_MAX_SIZE + 10, cellAux.getPositionY() * CELL_MAX_SIZE + 10, CELL_MAX_SIZE - 20, CELL_MAX_SIZE - 20);
								listAux->insertData(vertice);
							}
							path = listAux;
						}

						//g->DrawRectangle(p, i * CELL_MAX_SIZE, j * CELL_MAX_SIZE, CELL_MAX_SIZE, CELL_MAX_SIZE);

						//MessageBox::Show(color.getColor(0).ToString() + "-" + color.getColor(1).ToString() + "-" + color.getColor(2).ToString());

						if (ground.getColor(0) == -1 || ground.getColor(1) == -1 || ground.getColor(2) == -1) {
							sb = gcnew SolidBrush(Color::LightGray);
						}
						else if ((isPlaying && !cell.getIsKnown())) {
							sb = gcnew SolidBrush(panelMap->ForeColor);
						}
						else {
							string = "";
							//

							sb = gcnew SolidBrush(Color::FromArgb(ground.getColor(0), ground.getColor(1), ground.getColor(2)));

							//g->FillRectangle(sb, i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 1, CELL_MAX_SIZE - 1, CELL_MAX_SIZE - 1);


							/*for (int i = 0; i < cell.getLastVisitPosition(); i++) {
								string += cell.getVisitCounter(i).ToString() + ", ";
								MessageBox::Show(cell.getId().ToString() + " - "+ cell.getLastVisitPosition().ToString() + " - Pos:"+i.ToString() + cell.getVisitCounter(i).ToString());
							}*/


						}
						myBuffer->Graphics->FillRectangle(sb, i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 1, CELL_MAX_SIZE - 1, CELL_MAX_SIZE - 1);
						if (isPlaying && cell.getIsKnown()) {
							string = gcnew String(cell.getVisitCounter().c_str());
							if (string != "") {
								//MessageBox::Show(cell.getLastVisitPosition().ToString() + "-"+string);

								//g->DrawString(string, myFont, gcnew SolidBrush(Color::Black), PointF(i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 41));
								myBuffer->Graphics->DrawString(string, myFont, gcnew SolidBrush(Color::Black), PointF(i * CELL_MAX_SIZE + 1, j * CELL_MAX_SIZE + 41));
							}
						}
						if (drawId) {
							//g->DrawString(cell.getIdGround().ToString(), this->Font, gcnew SolidBrush(Color::DarkBlue), PointF(i * CELL_MAX_SIZE + 10, j * CELL_MAX_SIZE + 10));
							myBuffer->Graphics->DrawString(cell.getIdGround().ToString(), this->Font, gcnew SolidBrush(Color::DarkBlue), PointF(i * CELL_MAX_SIZE + 10, j * CELL_MAX_SIZE + 10));
						}
					}
					else {
						//MessageBox::Show("not found at " + i.ToString() + "-" + j.ToString());
					}
					//txtPrueba2->Text = arrayData->getSize().ToString();
				}
			}
			//MessageBox::Show();
			myBuffer->Render(panelMap->CreateGraphics());
		}

		// Buscar Nivel
		int buscarNivel(Vertice* vertice) {
			Collection<Vertice*> *listAux = new Collection<Vertice*>;
			Vertice* actual;
			int counter = -1;
			bool found = false;
			while (!listVerticesAuxGlobal->isEmpty()) {
				actual = listVerticesAuxGlobal->dequeue();
				//MessageBox::Show("Comparando: " + actual->nivel.ToString() + ", " + vertice->nivel.ToString());
				if (actual->nivel == vertice->nivel && !found) {
					counter++;
					if (actual == vertice) {
						found = true;
					}
				}
				listAux->insertData(actual);
			}
			listVerticesAuxGlobal = listAux;
			return counter;
		}
		
		Collection<Vertice*> *recorrerAnchura() {
			Vertice* actual = arbol->first();
			Arista* arista;
			Collection<Vertice*> *listVerticesAux = new Collection<Vertice*>;
			Collection<Vertice*> *colaVerticesAux = new Collection<Vertice*>;
			String ^string;

			colaVerticesAux->insertData(actual);
			//textBox3->Text += "what,";
			while (!colaVerticesAux->isEmpty()) {
				actual = colaVerticesAux->dequeue();
				listVerticesAux->insertData(actual);
				listVerticesAuxGlobal->insertData(actual);
				string += gcnew String(actual->elemento.getName().c_str()) + "," + actual->nivel.ToString() + ",";
				arista = actual->listaAdy;
				while (arista != nullptr) {
					if (listVerticesAux->findData(arista->verticePertenece) == nullptr && colaVerticesAux->findData(arista->verticePertenece) == nullptr) {
						//listVerticesAux->insertData(arista->verticePertenece);
						//string += gcnew String(arista->verticePertenece->elemento.getName().c_str()) + "," + arista->verticePertenece->nivel.ToString() + ",";
						colaVerticesAux->insertData(arista->verticePertenece);
						//textBox3->Text += "w,";
						arista = arista->sigArista;
					}


				}
				//textBox3->Text += "what,";
			}
			//MessageBox::Show(string);
			return listVerticesAux;
		}

		//Valida si todo está listo para jugar
		void setCostosFromGround(ComboBox ^comboBox, Ground ground) {
			CostoJugador costoJugador;
			String ^string;
			std::string str;
			int id;

			if (comboBox_Player->Text != "") {
				marshalString(comboBox->Text, str);
				costoJugador.setGroundName(str);

				marshalString(comboBox_Player->Text, str);
				costoJugador.setName(str);
				//MessageBox::Show("Buscando: "+comboBox->Text + " - "+ comboBox_Player->Text);
				//MessageBox::Show(gcnew String(listCostoJugador->getFirst()->getData().getName().c_str()));
				if (listCostoJugador->findData(costoJugador) != nullptr) {
					costoJugador = listCostoJugador->findData(costoJugador)->getData();
					id = Int32::Parse(comboBox->Name->Substring(14));

					ground.setId(id);
					if (listGround->findData(ground) != nullptr) {
						listGround->findData(ground)->getData().setValue(costoJugador.getCosto());
					}

					string = CHECKBOX_NAME_COLOR + id.ToString();
					//MessageBox::Show("Finding: " + string +" Changing");
					if (costoJugador.getCosto() < 0) {
						for each(CheckBox ^var in arrayCheckBox) {
							if (var->Name == string) {
								var->Checked = true;
							}
						}
					}
					else {
						for each(CheckBox ^var in arrayCheckBox) {
							if (var->Name == string) {
								var->Checked = false;
							}
						}
						string = TEXTBOX_NAME_COLOR + id.ToString();
						for each (TextBox ^var in arrayTextBox)
						{
							if (var->Name == string) {
								var->Text = costoJugador.getCosto().ToString();
								//MessageBox::Show("Changing");
							}
						}
					}
				}
			}
		}

		void setCostosFromPlayer() {
			CostoJugador costoJugador;
			Ground ground;
			String ^string;
			std::string str;
			int id;
			System::String ^specifier;

			if (comboBox_Player->Text != "") {

				for each (ComboBox ^var in arrayComboBox)
				{
					if (var->Text != "") {
						marshalString(var->Text, str);
						costoJugador.setGroundName(str);

						marshalString(comboBox_Player->Text, str);
						costoJugador.setName(str);
						//MessageBox::Show(gcnew String(str.c_str()));

						if (listCostoJugador->findData(costoJugador) != nullptr) {
							id = Int32::Parse(var->Name->Substring(14));
							costoJugador = listCostoJugador->findData(costoJugador)->getData();

							ground.setId(id);
							if (listGround->findData(ground) != nullptr) {
								listGround->findData(ground)->getData().setValue(costoJugador.getCosto());
							}

							string = CHECKBOX_NAME_COLOR + id.ToString();
							//MessageBox::Show("Finding: " + string +" Changing");
							if (costoJugador.getCosto() < 0) {
								for each(CheckBox ^var in arrayCheckBox) {
									if (var->Name == string) {
										var->Checked = true;
									}
								}
							}
							else {
								for each(CheckBox ^var in arrayCheckBox) {
									if (var->Name == string) {
										var->Checked = false;
									}
								}
								string = TEXTBOX_NAME_COLOR + id.ToString();
								for each (TextBox ^var in arrayTextBox)
								{
									if (var->Name == string) {
										specifier = "G";
										costoJugador.getCosto().ToString();
										var->Text = costoJugador.getCosto().ToString();
										//MessageBox::Show(costoJugador.getCosto().ToString(gcnew System::Globalization::CultureInfo("en-US")));
										//MessageBox::Show("Changing");
									}
								}
							}
						}
					}
				}
				//MessageBox::Show("Buscando: "+comboBox->Text + " - "+ comboBox_Player->Text);
				//MessageBox::Show(gcnew String(listCostoJugador->getFirst()->getData().getName().c_str()));

			}
		}

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
			button_Play->Enabled = false;

			comboBox_Algoritmos->Enabled = false;
			comboBox_Distance->Enabled = false;
			comboBox_Priority->Enabled = false;

			btn_ShowMap->Enabled = true;
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
			button_Play->Enabled = true;

			comboBox_Algoritmos->Enabled = true;
			comboBox_Distance->Enabled = true;
			comboBox_Priority->Enabled = true;

			btn_ShowMap->Enabled = false;
		}

		void setVisit(Point point) {
			Cell *cell = new Cell();
			int intAux;
			stringstream toStr;

			cell->setPositionX((int)(point.X / CELL_MAX_SIZE));
			cell->setPositionY((int)(point.Y / CELL_MAX_SIZE));

			if (listCell->findPositionXY(*cell) != nullptr) {
				intAux = ++visit;
				toStr.str("");
				toStr << intAux;
				cell = listCell->findPositionXY(*cell)->getDataPtr();
				cell->setVisitCounter(toStr.str());
				arbol->existeVertice(*cell)->elemento.setVisitCounter(toStr.str());
				//listCell->findPositionXY(*cell)->getData().setVisitCounter(toStr.str());

				//MessageBox::Show("Here: " + gcnew String(cell->getVisitCounter().c_str()));
				//MessageBox::Show(intAux.ToString()+", "+listCell->findPositionXY(cell)->getData().getVisitCounter(cell.getLastVisitPosition()-1).ToString());
				//panelMap_Paint_1(panelMap,panelMap->InvokePaint);
				panelMap->Refresh();
			}
		}

		void unlockCell(Point point) {
			//Point point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
			Cell cell, cellOrigen, cellArriba, cellAbajo, cellIzquierda, cellDerecha;
			Vertice *origen, *destinoArriba, *destinoAbajo, *destinoIzquierda, *destinoDerecha, *destino;
			Ground ground, groundArriba, groundAbajo, groundIzquierda, groundDerecha;
			String ^string;

			origen = destinoArriba = destinoAbajo = destinoIzquierda = destinoDerecha = nullptr;
			point = Point(point.X / CELL_MAX_SIZE, point.Y / CELL_MAX_SIZE);

			cell.setPositionX(point.X);
			cell.setPositionY(point.Y);
			if (listCell->findPositionXY(cell) != nullptr) {
				cellOrigen = cell = listCell->findPositionXY(cell)->getData();
				origen = arbol->existeVertice(cell);
				// textBox3->Text = "Unlocking: " + point.ToString();
				//moveTo(cell);
			}

			// Valida la casilla hacia abajo
			Point newPoint = Point(point.X, point.Y + 1);
			//MessageBox::Show("Finding in: " + newPoint);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr && !listCell->findPositionXY(cell)->getData().getIsKnown()) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundAbajo.setId(cell.getIdGround());
					groundAbajo = listGround->findData(groundAbajo)->getData();
					cell.setPrice(groundAbajo.getValue());
					arbol->insertaVertice(cell);
					if (groundAbajo.getIsValid()) {
						destinoAbajo = arbol->existeVertice(cell);
					}
					//arbol->insertaVertice(listCell-);
				}
			}

			// Valida la casilla hacia arriba
			newPoint = Point(point.X, point.Y - 1);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr && !listCell->findPositionXY(cell)->getData().getIsKnown()) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundArriba.setId(cell.getIdGround());
					groundArriba = listGround->findData(groundArriba)->getData();
					cell.setPrice(groundArriba.getValue());
					arbol->insertaVertice(cell);
					if (groundArriba.getIsValid()) {
						destinoArriba = arbol->existeVertice(cell);
					}
				}
			}

			// Valida la casilla hacia la derecha
			newPoint = Point(point.X + 1, point.Y);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr && !listCell->findPositionXY(cell)->getData().getIsKnown()) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundDerecha.setId(cell.getIdGround());
					groundDerecha = listGround->findData(groundDerecha)->getData();
					cell.setPrice(groundDerecha.getValue());
					arbol->insertaVertice(cell);
					if (groundDerecha.getIsValid()) {
						destinoDerecha = arbol->existeVertice(cell);
					}

				}
			}

			//Valida la casilla hacia la izquierda
			newPoint = Point(point.X - 1, point.Y);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr && !listCell->findPositionXY(cell)->getData().getIsKnown()) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundIzquierda.setId(cell.getIdGround());
					groundIzquierda = listGround->findData(groundIzquierda)->getData();
					cell.setPrice(groundIzquierda.getValue());
					arbol->insertaVertice(cell);
					if (groundIzquierda.getIsValid()) {
						destinoIzquierda = arbol->existeVertice(cell);
					}

				}
			}
			// textBox3->Text = priority[0];
			origen->isArista = true;
			for (int i = 0; i < 4; i++) {
				if (priority[i] == "Arriba") {
					destino = destinoArriba;
					ground = groundArriba;
					//MessageBox::Show("Arriba");
				}
				else if (priority[i] == "Abajo") {
					destino = destinoAbajo;
					ground = groundAbajo;
					//MessageBox::Show("Abajo");
				}
				else if (priority[i] == "Derecha") {
					destino = destinoDerecha;
					ground = groundDerecha;
					//MessageBox::Show("Derecha");
				}
				else if (priority[i] == "Izquierda") {
					destino = destinoIzquierda;
					ground = groundIzquierda;
					//MessageBox::Show("izquierda");
				}
				else {
					//MessageBox::Show("No obteniendo destino prioridad");
				}
				//origen->elemento.getName();
				//MessageBox::Show("Insertando Origen: " + "hi");

				if (destino != nullptr && !arbol->existeArista(origen, destino)) {
					//MessageBox::Show("Añandiendo Origen: " + gcnew String(origen->elemento.getName().c_str()) + ", Destino: "+ 
						//gcnew String(destino->elemento.getName().c_str()));
					arbol->insertaArista(origen, destino, listGround->findData(ground)->getData().getValue());
					destino->isArista = true;
				}

			}
			ArrangeTree();
			picTree->Refresh();

		}

		void unlockCellDos(Point point) {
			//Point point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
			Cell cell, cellOrigen, cellArriba, cellAbajo, cellIzquierda, cellDerecha, cellAux;
			Vertice *origen, *destinoArriba, *destinoAbajo, *destinoIzquierda, *destinoDerecha, *destino;
			Ground ground, groundArriba, groundAbajo, groundIzquierda, groundDerecha;
			String ^string;
			float priceDestino;
			float priceOrigen;

			origen = destinoArriba = destinoAbajo = destinoIzquierda = destinoDerecha = nullptr;
			point = Point(point.X / CELL_MAX_SIZE, point.Y / CELL_MAX_SIZE);

			cell.setPositionX(point.X);
			cell.setPositionY(point.Y);
			if (listCell->findPositionXY(cell) != nullptr) {
				cellOrigen = cell = listCell->findPositionXY(cell)->getData();
				origen = arbol->existeVertice(cell);
				// textBox3->Text = "Unlocking: " + point.ToString();
				//moveTo(cell);
			}

			// Valida la casilla hacia abajo
			Point newPoint = Point(point.X, point.Y + 1);
			//MessageBox::Show("Finding in: " + newPoint);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundAbajo.setId(cell.getIdGround());
					groundAbajo = listGround->findData(groundAbajo)->getData();
					cell.setPrice(groundAbajo.getValue());
					arbol->insertaVertice(cell);
					if (groundAbajo.getIsValid()) {
						destinoAbajo = arbol->existeVertice(cell);
					}
					//arbol->insertaVertice(listCell-);
				}
			}

			// Valida la casilla hacia arriba
			newPoint = Point(point.X, point.Y - 1);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundArriba.setId(cell.getIdGround());
					groundArriba = listGround->findData(groundArriba)->getData();
					cell.setPrice(groundArriba.getValue());
					arbol->insertaVertice(cell);
					if (groundArriba.getIsValid()) {
						destinoArriba = arbol->existeVertice(cell);
					}
				}
			}

			// Valida la casilla hacia la derecha
			newPoint = Point(point.X + 1, point.Y);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundDerecha.setId(cell.getIdGround());
					groundDerecha = listGround->findData(groundDerecha)->getData();
					cell.setPrice(groundDerecha.getValue());
					arbol->insertaVertice(cell);
					if (groundDerecha.getIsValid()) {
						destinoDerecha = arbol->existeVertice(cell);
					}

				}
			}

			//Valida la casilla hacia la izquierda
			newPoint = Point(point.X - 1, point.Y);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr) {
					cell = listCell->findPositionXY(cell)->getData();
					listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundIzquierda.setId(cell.getIdGround());
					groundIzquierda = listGround->findData(groundIzquierda)->getData();
					cell.setPrice(groundIzquierda.getValue());
					arbol->insertaVertice(cell);
					if (groundIzquierda.getIsValid()) {
						destinoIzquierda = arbol->existeVertice(cell);
					}

				}
			}
			//textBox3->Text = "";
			float distanceUno;
			float distanceDos;
			for (int i = 0; i < 4; i++) {
				if (priority[i] == "Arriba") {
					destino = destinoArriba;
					ground = groundArriba;
					//priceDestino = destino->elemento.getPrice();
					//MessageBox::Show("Arriba");
				}
				else if (priority[i] == "Abajo") {
					destino = destinoAbajo;
					ground = groundAbajo;
					//MessageBox::Show("Abajo");
				}
				else if (priority[i] == "Derecha") {
					destino = destinoDerecha;
					ground = groundDerecha;
					//MessageBox::Show("Derecha");
				}
				else if (priority[i] == "Izquierda") {
					destino = destinoIzquierda;
					ground = groundIzquierda;
					//MessageBox::Show("izquierda");
				}
				else {
					//MessageBox::Show("No obteniendo destino prioridad");
				}

				if (destino != nullptr && !arbol->existeArista(origen, destino) && listVisitados->findData(destino) == nullptr) {
					//MessageBox::Show("Añandiendo Origen: " + gcnew String(origen->elemento.getName().c_str()) + ", Destino: "+ 
						//gcnew String(destino->elemento.getName().c_str()));
					if (destino->isArista) {
						distanceUno = destino->elemento.getDistanciaHN() + (float)destino->elemento.getPrice() + origen->elemento.getDistanciaGN();
						distanceDos = destino->elemento.getDistanciaHN() + destino->elemento.getDistanciaGN();
						if (distanceUno < distanceDos) {
							//textBox3->Text += "\nEliminando; " + gcnew String(destino->elemento.getName().c_str()) +
							//	"\n\t" + distanceUno + " - " + distanceDos;
							cellAux = destino->elemento;
							arbol->eliminarVertice(destino);
							//MessageBox::Show("Deleting");
							arbol->insertaVertice(cellAux);
							destino = arbol->existeVertice(cellAux);
							//if (destino->padre != nullptr) {
							if(destino != nullptr){
							///arbol->eliminarArista(destino->padre, destino);
								//destino = arbol->existeVertice(cellAux);
								arbol->insertaArista(origen, destino, listGround->findData(ground)->getData().getValue());
								destino->isArista = true;
							}
							
							if (destino != nullptr) {
								arbol->insertaArista(origen, destino, listGround->findData(ground)->getData().getValue());
								destino->isArista = true;
								//destino->elemento.setDistanciaGN(origen->elemento.getDistanciaGN() + destino->elemento.getPrice());
							}
							
							
						}

					}
					else {
							arbol->insertaArista(origen, destino, listGround->findData(ground)->getData().getValue());
							destino->isArista = true;
						
						
					}
				}

			}
			//ArrangeTree();
			//picTree->Refresh();

		}

		/*void unlockCell(Point point) {
			//Point point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
			Cell *cell = new Cell();
			Cell cellOrigen;
			Cell cellArriba, cellAbajo, cellIzquierda, cellDerecha;
			Vertice *origen, *destinoArriba, *destinoAbajo, *destinoIzquierda, *destinoDerecha, *destino;
			Ground ground, groundArriba, groundAbajo, groundIzquierda, groundDerecha;
			String ^string;

			origen = destinoArriba = destinoAbajo = destinoIzquierda = destinoDerecha = nullptr;
			point = Point(point.X / CELL_MAX_SIZE, point.Y / CELL_MAX_SIZE);

			cell->setPositionX(point.X);
			cell->setPositionY(point.Y);
			cell = listCell->findPositionXY(*cell)->getDataPtr();
			if (cell != nullptr) {
				cellOrigen = *cell;
				origen = arbol->existeVertice(*cell);
				textBox3->Text = "Unlocking: " + point.ToString();
				//moveTo(cell);
			}

			// Valida la casilla hacia abajo
			Point newPoint = Point(point.X, point.Y + 1);
			//MessageBox::Show("Finding in: " + newPoint);
			if (isValidPositionPanelMap(newPoint)) {
				cell->setPositionX(newPoint.X);
				cell->setPositionY(newPoint.Y);
				cell = listCell->findPositionXY(*cell)->getDataPtr();
				if (cell != nullptr && !cell->getIsKnown()) {
					//cell = listCell->findPositionXY(*cell)->getData();
					cell->setIsKnown(true);
					//listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundAbajo.setId(cell->getIdGround());
					groundAbajo = listGround->findData(groundAbajo)->getData();
					cell->setPrice(groundAbajo.getValue());
					arbol->insertaVertice(*cell);
					if (groundAbajo.getIsValid()) {
						destinoAbajo = arbol->existeVertice(*cell);
					}
					//arbol->insertaVertice(listCell-);
				}
			}

			// Valida la casilla hacia arriba
			newPoint = Point(point.X, point.Y - 1);
			if (isValidPositionPanelMap(newPoint)) {
				cell->setPositionX(newPoint.X);
				cell->setPositionY(newPoint.Y);
				cell = listCell->findPositionXY(*cell)->getDataPtr();
				if (cell != nullptr && !cell->getIsKnown()) {
					//cell = listCell->findPositionXY(cell)->getData();
					cell->setIsKnown(true);
					//listCell->findPositionXY(*cell)->getData().setIsKnown(true);

					groundArriba.setId(cell->getIdGround());
					groundArriba = listGround->findData(groundArriba)->getData();
					cell->setPrice(groundArriba.getValue());
					arbol->insertaVertice(*cell);
					if (groundArriba.getIsValid()) {
						destinoArriba = arbol->existeVertice(*cell);
					}
				}
			}

			// Valida la casilla hacia la derecha
			newPoint = Point(point.X + 1, point.Y);
			if (isValidPositionPanelMap(newPoint)) {
				cell->setPositionX(newPoint.X);
				cell->setPositionY(newPoint.Y);
				cell = listCell->findPositionXY(*cell)->getDataPtr();
				if (cell != nullptr && !cell->getIsKnown()) {
					//cell = listCell->findPositionXY(cell)->getData();
					cell->setIsKnown(true);
					//listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundDerecha.setId(cell->getIdGround());
					groundDerecha = listGround->findData(groundDerecha)->getData();
					cell->setPrice(groundDerecha.getValue());
					arbol->insertaVertice(*cell);
					if (groundDerecha.getIsValid()) {
						destinoDerecha = arbol->existeVertice(*cell);
					}

				}
			}

			//Valida la casilla hacia la izquierda
			newPoint = Point(point.X - 1, point.Y);
			if (isValidPositionPanelMap(newPoint)) {
				cell->setPositionX(newPoint.X);
				cell->setPositionY(newPoint.Y);
				cell = listCell->findPositionXY(*cell)->getDataPtr();
				if (cell != nullptr && !cell->getIsKnown()) {
					//cell = listCell->findPositionXY(cell)->getData();
					cell->setIsKnown(true);
					//listCell->findPositionXY(cell)->getData().setIsKnown(true);

					groundIzquierda.setId(cell->getIdGround());
					groundIzquierda = listGround->findData(groundIzquierda)->getData();
					cell->setPrice(groundIzquierda.getValue());
					arbol->insertaVertice(*cell);
					if (groundIzquierda.getIsValid()) {
						destinoIzquierda = arbol->existeVertice(*cell);
					}

				}
			}
			textBox3->Text = priority[0];
			for (int i = 0; i < 4; i++) {
				if (priority[i] == "Arriba") {
					destino = destinoArriba;
					ground = groundArriba;
					//MessageBox::Show("Arriba");
				}
				else if (priority[i] == "Abajo") {
					destino = destinoAbajo;
					ground = groundAbajo;
					//MessageBox::Show("Abajo");
				}
				else if (priority[i] == "Derecha") {
					destino = destinoDerecha;
					ground = groundDerecha;
					//MessageBox::Show("Derecha");
				}
				else if (priority[i] == "Izquierda") {
					destino = destinoIzquierda;
					ground = groundIzquierda;
					//MessageBox::Show("izquierda");
				}
				else {
					//MessageBox::Show("No obteniendo destino prioridad");
				}
				//origen->elemento.getName();
				//MessageBox::Show("Insertando Origen: " + "hi");

				if (destino != nullptr && !arbol->existeArista(origen, destino)) {
					//MessageBox::Show("Añandiendo Origen: " + gcnew String(origen->elemento.getName().c_str()) + ", Destino: "+
						//gcnew String(destino->elemento.getName().c_str()));
					arbol->insertaArista(origen, destino, listGround->findData(ground)->getData().getValue());
				}

			}
			MessageBox::Show("here ok");
			ArrangeTree();
			picTree->Refresh();

		}*/
		void createArrayPriority() {
			arrayPriority = gcnew cli::array<String^>(24);
			arrayPriority[0] = "Abajo,Izquierda,Arriba,Derecha,";
			arrayPriority[1] = "Abajo,Izquierda,Derecha,Arriba,";
			arrayPriority[2] = "Abajo,Arriba,Derecha,Izquierda,";
			arrayPriority[3] = "Abajo,Arriba,Izquierda,Derecha,";
			arrayPriority[4] = "Abajo,Derecha,Izquierda,Arriba,";
			arrayPriority[5] = "Abajo,Derecha,Arriba,Izquierda,";
			arrayPriority[6] = "Izquierda,Arriba,Derecha,Abajo,";
			arrayPriority[7] = "Izquierda,Arriba,Abajo,Derecha,";
			arrayPriority[8] = "Izquierda,Derecha,Abajo,Arriba,";
			arrayPriority[9] = "Izquierda,Derecha,Arriba,Abajo,";
			arrayPriority[10] = "Izquierda,Abajo,Arriba,Derecha,";
			arrayPriority[11] = "Izquierda,Abajo,Derecha,Arriba,";
			arrayPriority[12] = "Arriba,Derecha,Abajo,Izquierda,";
			arrayPriority[13] = "Arriba,Derecha,Izquierda,Abajo,";
			arrayPriority[14] = "Arriba,Abajo,Derecha,Izquierda,";
			arrayPriority[15] = "Arriba,Abajo,Izquierda,Derecha,";
			arrayPriority[16] = "Arriba,Izquierda,Derecha,Abajo,";
			arrayPriority[17] = "Arriba,Izquierda,Abajo,Derecha,";
			arrayPriority[18] = "Derecha,Abajo,Izquierda,Arriba,";
			arrayPriority[19] = "Derecha,Abajo,Arriba,Izquierda,";
			arrayPriority[20] = "Derecha,Izquierda,Arriba,Abajo,";
			arrayPriority[21] = "Derecha,Izquierda,Abajo,Arriba,";
			arrayPriority[22] = "Derecha,Arriba,Abajo,Izquierda,";
			arrayPriority[23] = "Derecha,Arriba,Izquierda,Abajo,";
		}

		void moveTo(Cell cell) {

			moveEvent(Point(cell.getPositionX(), cell.getPositionY()));

		}

		void moveToDos(Cell cell) {

			moveEventDos(Point(cell.getPositionX(), cell.getPositionY()));

		}

		// //////////////////////////////////////////// ALGORTIMOS /////////////////////////////////////////////
		void A_Profundidad(Cell elem) {
			int value = Convert::ToInt32(numericUpDown1->Value);
			timer1->Interval = value * 100;
			Vertice* orig(arbol->existeVertice(elem));
			if (orig == nullptr) {
				/// Error
				MessageBox::Show("El vertice origen no existe\n");
			}
			else {
				pilaVertices = new Collection <Vertice*>;
				listVisitados = new Collection <Vertice*>;
				path = new Collection <Vertice*>;
				pilaVertices->push(orig);   /// Apilar el vértice origen.
				//MessageBox::Show("here");
				textBox1->Text = "";
				timer1->Start();
			}

		}

		void A_VorazPrimeroMejor(Cell elem) {
			int value = Convert::ToInt32(numericUpDown1->Value);
			timer1->Interval = value * 100;
			Vertice* orig(arbol->existeVertice(elem));
			if (orig == nullptr) {
				/// Error
				MessageBox::Show("El vertice origen no existe\n");
			}
			else {
				listaVertices = new Collection <Vertice*>;
				listVisitados = new Collection <Vertice*>;
				path = new Collection <Vertice*>;

				float distancia = listCell->findData(elem)->getData().getDistanciaHN();
				orig->elemento.setDistanciaHN(distancia);
				listaVertices->insertData(orig);

				textBox1->Text = "";
				timer1->Start();
			}
		}

		void A_CosteUniforme(Cell elem) {
			int value = Convert::ToInt32(numericUpDown1->Value);
			timer1->Interval = value * 100;
			Vertice* orig(arbol->existeVertice(elem));
			if (orig == nullptr) {
				/// Error
				MessageBox::Show("El vertice origen no existe\n");
			}
			else {
				listaVertices = new Collection <Vertice*>;
				listVisitados = new Collection <Vertice*>;
				path = new Collection <Vertice*>;

				float distancia = 0;
				orig->elemento.setDistanciaGN(distancia);
				listaVertices->insertData(orig);

				textBox1->Text = "";
				timer1->Start();
			}

		}

		void A_AEstrella(Cell elem) {
			int value = Convert::ToInt32(numericUpDown1->Value);
			timer1->Interval = value * 100;
			Vertice* orig(arbol->existeVertice(elem));
			if (orig == nullptr) {
				/// Error
				MessageBox::Show("El vertice origen no existe\n");
			}
			else {
				listaVertices = new Collection <Vertice*>;
				listVisitados = new Collection <Vertice*>;
				path = new Collection <Vertice*>;

				float distanciaGN = 0;
				float distanciaHN = listCell->findData(elem)->getData().getDistanciaHN();

				orig->elemento.setDistanciaGN(distanciaGN);
				orig->elemento.setDistanciaHN(distanciaHN);
				listaVertices->insertData(orig);

				textBox1->Text = "";
				timer1->Start();
			}

		}

		void showPath(Vertice* final) {
			Point point = panelMap->PointToClient(PointToScreen(pictureBox_Start->Location));
			Vertice* inicial;
			Cell cell, cell2;
			String ^string;
			point = Point(point.X / CELL_MAX_SIZE, point.Y / CELL_MAX_SIZE);
			cell.setPositionX(point.X);
			cell.setPositionY(point.Y);

			cell = listCell->findPositionXY(cell)->getData();
			inicial = arbol->existeVertice(cell);

			SolidBrush ^sb = gcnew SolidBrush(Color::Red);
			Pen ^p = gcnew Pen(Color::Red);
			final->isPath = true;
			path->push(final);
			//textBox3->Text = "";
			while (final != inicial) {
				final = arbol->anterior(final);
				//textBox3->Text += "1";
				if (final != nullptr) {
					final->isPath = true;
					path->push(final);

				}
			}
		}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		textBox3->Text = "\nEntrando Timer\n";
		if (comboBox_Algoritmos->SelectedIndex == 0) {
			//MANUAL
		}
		else if (comboBox_Algoritmos->SelectedIndex == 1) {
			/////////////////////////////PROFUNDIDAD///////////////////////////
			//std::string recorridoProfundidad(Cell elem) {
			Vertice* actual, *pathActual;
			Arista *aux;
			std::string result;
			String ^str;
			if (!pilaVertices->isEmpty()) {
				pathActual = actual = pilaVertices->pop();        ///Desapilar un vertice, sera el actual
				if (listVisitados->findData(actual) == nullptr) {      ///Si el vertice no ha sido visitado
					result += actual->elemento.getName() + ", ";              ///Se procesa

					str = gcnew String(actual->elemento.getName().c_str());
					textBox1->Text += str;
					listVisitados->insertData(actual);      ///colocar en visitados
					moveTo(actual->elemento);

					aux = actual->listaAdy;

					while (aux != nullptr) {        ///Recorrido de aristas para los vertices destino
						//textBox3->Text += ",Push: ";
						if (listVisitados->findData(aux->verticePertenece) == nullptr) {        ///si no han sido visitados
							//textBox3->Text += gcnew String(aux->verticePertenece->elemento.getName().c_str()) + ",";
							pilaVertices->push(aux->verticePertenece);         ///apilar
						}
						aux = aux->sigArista;
					}
				}
			}
			else {
				timer1->Enabled = false;
				MessageBox::Show("No se encontró el camino de regreso a casa");
			}
		}
		else if (comboBox_Algoritmos->SelectedIndex == 2) {
			//COSTE UNIFORME
			Vertice* actual, *pathActual, *menorCosto;
			Arista *aux;
			std::string result;
			String ^str;
			if (!listaVertices->isEmpty()) {

				//menorCosto = listaVertices->findMenorCostoGN();
				menorCosto = listaVertices->findMenorCostoGN();
				pathActual = actual = menorCosto;

				listaVertices->deleteData(menorCosto);      ///Eliminar el vertice, sera el actual
				if (listVisitados->findData(actual) == nullptr) {      ///Si el vertice no ha sido visitado
					result += actual->elemento.getName() + ", ";              ///Se procesa

					str = gcnew String(actual->elemento.getName().c_str());
					textBox1->Text += str;
					listVisitados->insertData(actual);      ///colocar en visitados
					moveToDos(actual->elemento);

					aux = actual->listaAdy;

					while (aux != nullptr) {        ///Recorrido de aristas para los vertices destino
						//textBox3->Text += ",Insertar: ";
						if (listVisitados->findData(aux->verticePertenece) == nullptr) {        ///si no han sido visitados
							//textBox3->Text += gcnew String(aux->verticePertenece->elemento.getName().c_str()) + ",";
							///
							float costoPadre = actual->elemento.getDistanciaGN();
							float costoTerreno = listGround->valueGround(aux->verticePertenece->elemento.getIdGround());
							float distancia = costoPadre + costoTerreno;

							aux->verticePertenece->elemento.setDistanciaGN(distancia);
							//listaVertices->findData(aux->verticePertenece)->getData()->elemento.setDistanciaGN(distancia);
							///
							/*if (listaVertices->findData(aux->verticePertenece) != nullptr) {   //Buscar si ya existe el adyacente en la lista
								float distanciaExistente, distanciaNueva;

								distanciaExistente = listaVertices->findData(aux->verticePertenece)->getData()->elemento.getDistanciaGN();

								distanciaNueva = aux->verticePertenece->elemento.getDistanciaGN();

								if (distanciaNueva < distanciaExistente) {
									listaVertices->deleteData(aux->verticePertenece);

									MessageBox::Show("Algo");
									listaVertices->insertData(aux->verticePertenece);
								}

							}*/
							listaVertices->insertData(aux->verticePertenece);         ///Insertar
						}
						aux = aux->sigArista;
					}
				}
			}
			else {
				timer1->Enabled = false;
				MessageBox::Show("No se encontró el camino de regreso a casa");
			}
		}
		else if (comboBox_Algoritmos->SelectedIndex == 3) {
			//VORAZ PRIMERO EL MEJOR				
			Vertice* actual, *pathActual, *menorCosto;
			Arista *aux;
			std::string result;
			String ^str;
			if (!listaVertices->isEmpty()) {

				menorCosto = listaVertices->findMenorCostoHN();
				pathActual = actual = menorCosto;

				listaVertices->deleteData(menorCosto);      ///Eliminar el vertice, sera el actual
				if (listVisitados->findData(actual) == nullptr) {      ///Si el vertice no ha sido visitado
					result += actual->elemento.getName() + ", ";              ///Se procesa

					str = gcnew String(actual->elemento.getName().c_str());
					textBox1->Text += str;
					listVisitados->insertData(actual);      ///colocar en visitados
					moveTo(actual->elemento);

					aux = actual->listaAdy;

					while (aux != nullptr) {        ///Recorrido de aristas para los vertices destino
						//textBox3->Text += ",Insertar: ";
						if (listVisitados->findData(aux->verticePertenece) == nullptr) {        ///si no han sido visitados
							//textBox3->Text += gcnew String(aux->verticePertenece->elemento.getName().c_str()) + ",";
							///
							float distancia = listCell->findData(aux->verticePertenece->elemento)->getData().getDistanciaHN();
							aux->verticePertenece->elemento.setDistanciaHN(distancia);
							///
							listaVertices->insertData(aux->verticePertenece);         ///Insertar
						}
						aux = aux->sigArista;
					}
				}
			}
			else {
				timer1->Enabled = false;
				MessageBox::Show("No se encontró el camino de regreso a casa");
			}
		}
		else if (comboBox_Algoritmos->SelectedIndex == 4) {
			//A*

			Vertice* actual, *pathActual, *menorCosto;
			Arista *aux;
			std::string result;
			String ^str;
			bool Is = true;
			if (!listaVertices->isEmpty()) {

				menorCosto = listaVertices->findMenorCostoAEst();
				textBox3->Text += "Sacando: " + gcnew String(menorCosto->elemento.getName().c_str()) + ":" + (menorCosto->elemento.getDistanciaGN() + menorCosto->elemento.getDistanciaHN());
				pathActual = actual = menorCosto;

				listaVertices->deleteData(menorCosto);      ///Eliminar el vertice, sera el actual
				if(listaVertices->findData(actual) == nullptr) {
					textBox3->Text += "No existe";
				}
				if (listVisitados->findData(actual) == nullptr) {      ///Si el vertice no ha sido visitado
					//result += actual->elemento.getName() + ", ";              ///Se procesa

					listVisitados->insertData(actual);      ///colocar en visitados
					textBox3->Text += "\n A Entrar";
					moveToDos(actual->elemento);
					textBox3->Text += "\nLlegó";
					aux = actual->listaAdy;
					
					while (aux != nullptr) {        ///Recorrido de aristas para los vertices destino
						//textBox3->Text += ",Insertar: ";
						textBox3->Text += "Nueva Vuelta \n";
						if (listVisitados->findData(aux->verticePertenece) == nullptr) {        ///si no han sido visitados
							//textBox3->Text += gcnew String(aux->verticePertenece->elemento.getName().c_str()) + ",";
							///
							float distanciaHN = listCell->findData(aux->verticePertenece->elemento)->getData().getDistanciaHN();
							aux->verticePertenece->elemento.setDistanciaHN(distanciaHN);

							float costoPadre = actual->elemento.getDistanciaGN();
							float costoTerreno = aux->verticePertenece->elemento.getPrice();
							float distanciaGN = costoPadre + costoTerreno;

							aux->verticePertenece->elemento.setDistanciaGN(distanciaGN);
							//textBox3->Text += "\nHasta acá";
							//textBox3->Text = (aux->verticePertenece->elemento.getDistanciaGN().ToString() + " - " +
							//	listaVertices->findData(aux->verticePertenece)->getData()->elemento.getDistanciaGN().ToString());
							///
							if (listaVertices->findData(aux->verticePertenece) != nullptr) {   //Buscar si ya existe el adyacente en la lista
								float distanciaExistenteGN, distanciaNueva, distanciaExistenteHN, distanciaExistente;

								distanciaExistenteGN = listaVertices->findData(aux->verticePertenece)->getData()->elemento.getDistanciaGN();
								distanciaExistenteHN = listaVertices->findData(aux->verticePertenece)->getData()->elemento.getDistanciaHN();

								distanciaExistente = distanciaExistenteGN + distanciaExistenteHN;

								distanciaNueva = aux->verticePertenece->elemento.getDistanciaGN() + aux->verticePertenece->elemento.getDistanciaHN();
								// textBox3->Text = "Distancias: " + distanciaNueva + " - " +distanciaExistente;
								if (distanciaNueva < distanciaExistente) {
									Is = true;
									listaVertices->deleteData(aux->verticePertenece);
									arbol->eliminarVertice(aux->verticePertenece);
									MessageBox::Show("Here");
									//listaVertices->insertData(aux->verticePertenece);
								}

							}
							textBox3->Text += "\nAl insertar: "+ gcnew String(aux->verticePertenece->elemento.getName().c_str());
							listaVertices->insertData(aux->verticePertenece);         ///Insertar
							textBox3->Text += "\nDespués de";
							
							
						}
						aux = aux->sigArista;
					}
				}
			}
			else {
				timer1->Enabled = false;
				MessageBox::Show("No se encontró el camino de regreso a casa");
			}
			textBox3->Text += "\nSaliendo Timer";
		}
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

		//MessageBox::Show(id.ToString());
		ground.setId(id);
		if (listGround->findData(ground) != nullptr) {
			if (colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				r = colorDialog1->Color.R;
				g = colorDialog1->Color.G;
				b = colorDialog1->Color.B;
				listGround->findData(ground)->getData().setColor(r, g, b);
				//listColor->findId(id)->getData().setColor(r,g,b);
				btn->BackColor = Color::FromArgb(r, g, b);
				//MessageBox::Show("color establecido como: " + listGround->findData(ground)->getData().getColor(0) + " - ");
				//drawMap(true);
				//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
				panelMap->Refresh();
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
			if (comboBox->SelectedIndex == var->SelectedIndex && comboBox->Name != var->Name) {
				comboBox->SelectedIndex = -1;
				repeated = true;
				newColor = Color::Gray;
				if (listGround->findData(ground) != nullptr) {
					//MessageBox::Show("asdf: " + button->Name);
					listGround->findData(ground)->getData().setColor(newColor.Gray.R, newColor.Gray.G, newColor.Gray.B);
					//drawMap(true);
					//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
					panelMap->Refresh();
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

						ground.setId(id);
						setCostosFromGround(comboBox, ground);

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

								panelMap->Refresh();
								//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
								//drawMap(true);
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
		CostoJugador costoJugador;
		String ^text;
		std::string str;
		int id;
		float costo;
		//MessageBox::Show("Cambió");
		if (txt->Text == "") {
			txt->Text == "0";
		}
		else if (System::Text::RegularExpressions::Regex::IsMatch(txt->Text, "^[0-9]*[.]?[0-9]+$") ||
			System::Text::RegularExpressions::Regex::IsMatch(txt->Text, "^[0-9]+[.]$")) {
			// ((.[0-9]+)|[0-9]+)  
			id = Int32::Parse(txt->Name->Substring(13));
			ground.setId(id);

			if (listGround->findData(ground) != nullptr) {
				text = txt->Text;
				//MessageBox::Show(System::Single::Parse(("0.12"), gcnew System::Globalization::CultureInfo("en-US")).ToString());
				listGround->findData(ground)->getData().setValue(System::Math::Truncate((Convert::ToDouble((txt->Text), gcnew System::Globalization::CultureInfo("en-US")) * 100)) / 100);
				
				marshalString(comboBox_Player->Text,str);
				costoJugador.setName(str);
				costoJugador.setGroundName(listGround->findData(ground)->getData().getName());
				//MessageBox::Show(gcnew String(listCostoJugador->findData(costoJugador)->getData().getName().c_str()));
				if (listCostoJugador->findData(costoJugador) != nullptr) {	
					listCostoJugador->findData(costoJugador)->getData().setCosto(listGround->findData(ground)->getData().getValue());
					//MessageBox::Show("Cambiando costo: " + costo + " - " + gcnew String(str.c_str()));
				}
				
			}
		}
		else {
			MessageBox::Show("Ingrese un valor numérico correcto");
			txt->Text = "0";
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
		setCostosFromPlayer();
		//MessageBox::Show("Function");
	}
	private: System::Void Map_Shown(System::Object^  sender, System::EventArgs^  e) {
		//this->Hide();
		chargeMap(fileNameMapGlobal);
		chargeCostoJugadorFile();
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
		if (isCorruptFile) {
			this->Close();
		}
	}


	/////////////////////// Eventos para Drag & drop de estado inicial y final //////////////////////////////77
	Point ^coordenadas = gcnew Point;
	Tree ^tree;
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
			//drawMap(true);
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
			/*MessageBox::Show(
				PointToClient(pictureBox_Start->Location).ToString());*/
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
		//MessageBox::Show("Entry");
	}

			 // Pinta el panel
	private: System::Void panelMap_Paint_1(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		Bitmap ^btm;
		if (isPlaying) {
			drawMap(false);
			//drawTree();
		}
		else {
			drawMap(true);
		}
		//this->SetStyle(ControlStyles::AllPaintingInWmPaint|ControlStyles::UserPaint|ControlStyles::OptimizedDoubleBuffer, true);
		//btm = gcnew Bitmap(panelMap->Width, panelMap->Height);
		//Graphics ^g;
		//g = Graphics::FromImage(btm);
		//g->DrawImage(btm, panelMap->Location);
	}

			 // Evento click para iniciar el juego
	private: System::Void btn_play_Click(System::Object^  sender, System::EventArgs^  e) {
		Point point;
		Point newPoint;
		Cell cell;
		Ground ground;
		priority = gcnew cli::array<String^>(4);
		//pictureBox_Start->SendToBack();
		panelMap->SendToBack();

		if (isReadyToPlay()) {
			isPlaying = true;
			disableObject();
			pictureBox_Player->Location = pictureBox_Start->Location;

			//CALCULAR DISTANCIAS MANHATTAN Y EUCLIDEANA
			Cell element, elementGoal;
			int goalId = pointGoal;
			elementGoal.setId(goalId);
			elementGoal = listCell->findData(elementGoal)->getData();

			for (int i = 0; i < listCell->getItemCounter(); i++) {
				element.setId(i);
				element = listCell->findData(element)->getData();

				/// AGREGAR SI EL COMBOBOX ES MANHATTAN O EUCLIDEANA ///////////////////////////////////////////////////////
				int selectedIndex = comboBox_Algoritmos->SelectedIndex;
				if (selectedIndex == 2) {
					listCell->findData(element)->getData().setDistanciaHN(0);
				}
				if (comboBox_Distance->SelectedIndex == 0 && (selectedIndex == 3 || selectedIndex == 4)) {
					listCell->findData(element)->getData().setDistanciaHN(element.calcularDistManhattan(element, elementGoal));
				}
				else if (comboBox_Distance->SelectedIndex == 1 && (selectedIndex == 3 || selectedIndex == 4)) {
					listCell->findData(element)->getData().setDistanciaHN(element.calcularDistEuclideana(element, elementGoal));
				}
			}

			arbol = new Arbol();
			priority = arrayPriority[comboBox_Priority->SelectedIndex]->Split(',');
			String ^str;
			for (int i = 0; i < 4; i++) {
				str += priority[i] + ",";
			}
			//MessageBox::Show("Array: " + arrayPriority[comboBox_Priority->SelectedIndex]);
			//MessageBox::Show("ComboBox: "+ comboBox_Priority->SelectedIndex.ToString() + str);

			point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
			newPoint = Point(point.X / CELL_MAX_SIZE, point.Y / CELL_MAX_SIZE);
			if (isValidPositionPanelMap(newPoint)) {
				cell.setPositionX(newPoint.X);
				cell.setPositionY(newPoint.Y);
				if (listCell->findPositionXY(cell) != nullptr) {

					listCell->findPositionXY(cell)->getData().setIsKnown(true);
					cell = listCell->findPositionXY(cell)->getData();
					ground.setId(cell.getIdGround());
					cell.setPrice(listGround->findData(ground)->getData().getValue());
					arbol->insertaVertice(cell);

					ArrangeTree();
					picTree->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Map::picTree_Paint);
					//arbol->insertaVertice(listCell-);
				}
			}
			unlockCell(point);

			setVisit(point);
			if (comboBox_Algoritmos->SelectedIndex == 0) {
				this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);
				textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);

				textBox1->Focus();
			}
			else if (comboBox_Algoritmos->SelectedIndex == 1) {
				A_Profundidad(cell);

			}
			else if (comboBox_Algoritmos->SelectedIndex == 2) {
				A_CosteUniforme(cell);

			}
			else if (comboBox_Algoritmos->SelectedIndex == 3) {
				A_VorazPrimeroMejor(cell);

			}
			else {
				A_AEstrella(cell);
			}


		}
		//panelMap->Focus();

	}

			 // Detectar el click de las teclas para mover el jugador
	private: System::Void Map_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		KeyDownEvent(e->KeyCode);
		MessageBox::Show("HEre");
	}

	private: void KeyDownEvent(Keys e) {
		Point point = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
		Point auxPoint = point;
		Point auxAuxPoint = auxPoint;
		Cell cell;
		stringstream toStr;
		int locationX, locationY, intAux;
		bool moved = false;
		//MessageBox::Show(e.ToString());
		if (pictureBox_Player->Location != pictureBox_Goal->Location) {
			//FLECHA IZQUIERDA
			if (e == Keys::Left) {
				point.X = point.X - CELL_MAX_SIZE;
				auxPoint = Point(point.X, auxPoint.Y);
				if (isValidGround(auxPoint) && isValidPositionPanelMap(point)) {
					pictureBox_Player->Location = Point(pictureBox_Player->Location.X - CELL_MAX_SIZE,
						pictureBox_Player->Location.Y);

					moved = true;
				}
			}
			//FLECHA ARRIBA
			else if (e == Keys::Up) {
				point.Y = point.Y - CELL_MAX_SIZE;
				auxPoint = Point(auxPoint.X, point.Y);
				if (isValidGround(auxPoint) && isValidPositionPanelMap(point)) {
					pictureBox_Player->Location = Point(pictureBox_Player->Location.X,
						pictureBox_Player->Location.Y - CELL_MAX_SIZE);

					moved = true;
				}
			}
			//FLECHA ABAJO
			else if (e == Keys::Down) {
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
			else if (e == Keys::Right) {
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
				setVisit(auxPoint);
				unlockCell(panelMap->PointToClient(PointToScreen(pictureBox_Player->Location)));
				//drawMap(false);
				//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
				panelMap->Refresh();
			}
		}
		if (pictureBox_Player->Location == pictureBox_Goal->Location) {
			MessageBox::Show("Has llegado a la meta \n");
			//pictureBox_Player->Location = pictureBox_Start->Location;
			pictureBox_Player->Location = pictureBoxPlayerPoint;
		}
	}

	// Mueve el jugador a una posición en específico.
	void moveEvent(Point pointNext) {
		Point pointActual = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
		Point auxPoint = pointActual;
		Point auxAuxPoint;
		Cell cell;
		stringstream toStr;
		int locationX, locationY, intAux;
		bool moved = false;

		cell.setPositionX(pointNext.X);
		cell.setPositionY(pointNext.Y);
		pointActual = Point(pointActual.X / CELL_MAX_SIZE, pointActual.Y / CELL_MAX_SIZE);
		// textBox3->Text += gcnew String(listCell->findPositionXY(cell)->getData().getName().c_str()) + ":" + pointNext.ToString() + "," + pointActual.ToString();
		auxPoint = Point(pointNext.X - pointActual.X, pointNext.Y - pointActual.Y);

		if (pictureBox_Player->Location != pictureBox_Goal->Location) {
			if (auxPoint.X != 0 || auxPoint.Y != 0) {
				auxAuxPoint = pictureBox_Player->Location;
				pictureBox_Player->Location = Point(auxAuxPoint.X + (auxPoint.X * CELL_MAX_SIZE), auxAuxPoint.Y + (auxPoint.Y * CELL_MAX_SIZE));
				moved = true;
			}
			else {
				// Nothing
			}
			if (moved) {
				pointActual = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
				setVisit(panelMap->PointToClient(PointToScreen(pictureBox_Player->Location)));
				unlockCell(panelMap->PointToClient(PointToScreen(pictureBox_Player->Location)));
				panelMap->Refresh();


				//drawMap(false);
				//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
				//panelMap->Refresh();
			}
		}
		//drawTree();
		if (pictureBox_Player->Location == pictureBox_Goal->Location) {
			timer1->Enabled = false;
			won = true;
			showPath(arbol->existeVertice(listVisitados->getTop()->elemento));
			picTree->Refresh();
			MessageBox::Show("Has llegado a la meta \n");

			//pictureBox_Player->Location = pictureBox_Start->Location;
			pictureBox_Player->Location = pictureBoxPlayerPoint;

		}
	}

	void moveEventDos(Point pointNext) {
		Point pointActual = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
		Point auxPoint = pointActual;
		Point auxAuxPoint;
		Cell cell;
		stringstream toStr;
		int locationX, locationY, intAux;
		bool moved = false;

		cell.setPositionX(pointNext.X);
		cell.setPositionY(pointNext.Y);
		pointActual = Point(pointActual.X / CELL_MAX_SIZE, pointActual.Y / CELL_MAX_SIZE);
		// textBox3->Text += gcnew String(listCell->findPositionXY(cell)->getData().getName().c_str()) + ":" + pointNext.ToString() + "," + pointActual.ToString();
		auxPoint = Point(pointNext.X - pointActual.X, pointNext.Y - pointActual.Y);

		if (pictureBox_Player->Location != pictureBox_Goal->Location) {
			if (auxPoint.X != 0 || auxPoint.Y != 0) {
				auxAuxPoint = pictureBox_Player->Location;
				pictureBox_Player->Location = Point(auxAuxPoint.X + (auxPoint.X * CELL_MAX_SIZE), auxAuxPoint.Y + (auxPoint.Y * CELL_MAX_SIZE));
				moved = true;
			}
			else {
				// Nothing
			}
			if (moved) {
				pointActual = panelMap->PointToClient(PointToScreen(pictureBox_Player->Location));
				setVisit(panelMap->PointToClient(PointToScreen(pictureBox_Player->Location)));
				unlockCellDos(panelMap->PointToClient(PointToScreen(pictureBox_Player->Location)));
				panelMap->Refresh();


				//drawMap(false);
				//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
				//panelMap->Refresh();
			}
		}
		//drawTree();
		if (pictureBox_Player->Location == pictureBox_Goal->Location) {
			timer1->Enabled = false;
			won = true;
			showPath(arbol->existeVertice(listVisitados->getTop()->elemento));
			picTree->Refresh();
			MessageBox::Show("Has llegado a la meta \n");

			//pictureBox_Player->Location = pictureBox_Start->Location;
			pictureBox_Player->Location = pictureBoxPlayerPoint;

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
			///MessageBox::Show(MousePosition.ToString());
			Point point = panelMap->PointToClient(MousePosition);
			tt->UseAnimation = true;
			System::String^ informacion = toolTipMensaje(point);
			tt->Show(informacion, win, PointToClient(MousePosition).X + 10, PointToClient(MousePosition).Y + 30, 2000);
			//tt->Show(informacion, win, PointToClient(MousePosition), 2000);
		}
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
	private: System::Void button_Reset_Click(System::Object^  sender, System::EventArgs^  e) {
		timer1->Stop();
		enableObject();
		isPlaying = false;
		won = false;

		picTree->Paint -= gcnew System::Windows::Forms::PaintEventHandler(this, &Map::picTree_Paint);
		this->KeyDown -= gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);
		textBox1->KeyDown -= gcnew System::Windows::Forms::KeyEventHandler(this, &Map::Map_KeyDown);

		for (int i = 0; i < listCell->getItemCounter(); i++) {
			listCell->findId(i)->getData().eraseVisitCounter();
			listCell->findId(i)->getData().setIsKnown(false);
		}
		pilaVertices = nullptr;
		listVisitados = nullptr;
		listVerticesAuxGlobal->deleteAll();
		path->deleteAll();
		visit = 0;
		//drawMap(false);
		//panelMap_Paint_1(panelMap, panelMap->InvokePaint);
		panelMap->Refresh();
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
			if (groundAux.getIsValid() && groundAux.getValue() >= 0) {
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
			if (cellAux.getVisitCounter() != "") {
				informacion = informacion + "Visita: " + gcnew String(cellAux.getVisitCounter().c_str()) + "\n";
			}
		}
		return informacion;
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^systemStr;
		std::string aux = "hi";
		aux = arbol->mostrarListaAdyacencia();
		MessageBox::Show(gcnew String(aux.c_str()));
	}

	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		int value = Convert::ToInt32(numericUpDown1->Value);

		if (numericUpDown1->Value < 1) {
			numericUpDown1->Value = 1;

		}
		value *= 50;
		timer1->Interval = value;
	}
	private: System::Void btn_ShowMap_Click(System::Object^  sender, System::EventArgs^  e) {

		tree = gcnew Tree(arbol);
		tree->Show();
	}

	///////////////////////////////////////// TreeNode ////////////////////////////////////////////
			// Center the tree on the form.
	void ArrangeTree()
	{
		int x, y;
		Graphics ^gr = picTree->CreateGraphics();
		{
			if (arbol->Orientation == arbol->Orientations::Horizontal)
			{

				//this->picTree->Size = System::Drawing::Size(picTree->Width + 10, arbol->nivelTotal() * 75 + 30);
				//}
				// Arrange the tree once to see how big it is.
				float xmin = 0, ymin = 0;
				//MessageBox::Show(gcnew String(arbol->mostrarListaAdyacencia().c_str()));
				arbol->Arrange(gr, xmin, ymin, arbol->getAncla());

				// Arrange the tree again to center it horizontally.
				//MessageBox::Show("Again");
				xmin = (picTree->ClientSize.Width - xmin) / 2;
				ymin = 10;
				arbol->Arrange(gr, xmin, ymin, arbol->getAncla());
				//MessageBox::Show("Again: " + picTree->ClientSize.Width);
				x = xmin;
				y = ymin;
			}
			else
			{
				// Arrange the tree.
				float xmin = arbol->Indent;//@
				float ymin = xmin;
				arbol->Arrange(gr, xmin, ymin, arbol->getAncla());
				x = xmin;
				y = ymin;
			}
			int nivel = arbol->nivelTotal();
			if (nivel > 8 && x > 500) {

				//this->picTree->MaximumSize = System::Drawing::Size(x + 10, y + 10);
				this->picTree->Size = System::Drawing::Size(x + 30, y + 30);
				//MessageBox::Show("X min: " + x + " - " + "yMin" + y);
			}
			else if (nivel > 8 && x < 500) {
				this->picTree->Size = System::Drawing::Size(picTree->Width, y + 33);
			}
			else if (nivel <= 8 && x > 500) {
				this->picTree->Size = System::Drawing::Size(x + 33, picTree->Height);
			}
		}

		picTree->Refresh();
	}

	// The currently selected node.
	Vertice *SelectedNode;

	// Display the text of the node under the mouse.
	void picTree_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs e)
	{
		// Find the node under the mouse.
		FindNodeUnderMouse(e.Location);

		// If there is a node under the mouse,
		// display the node's text.
		if (SelectedNode == nullptr)
		{
			//lblNodeText.Text = "";
		}
		else
		{
			//lblNodeText.Text = SelectedNode.Data.Text;
		}
	}

	// Set SelectedNode to the node under the mouse.
	void FindNodeUnderMouse(PointF pt)
	{
		Graphics ^gr = picTree->CreateGraphics();
		{
			SelectedNode = arbol->NodeAtPoint(gr, pt, arbol->getAncla());
		}
	}

	// Change the tree's orientation.
	private: System::Void radHorizontal_Click(System::Object^ sender, System::EventArgs ^e)
	{
		arbol->SetTreeDrawingParameters(5, 30, 20, 5,
			arbol->Orientations::Horizontal, arbol->getAncla());
		ArrangeTree();
	}

	private: System::Void radVertical_Click(System::Object^ sender, System::EventArgs ^e)
	{
		arbol->SetTreeDrawingParameters(5, 2, 20, 5,
			arbol->Orientations::Vertical, arbol->getAncla());
		ArrangeTree();
	}
	private: System::Void picTree_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {

		e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
		e->Graphics->TextRenderingHint = TextRenderingHint::AntiAliasGridFit;
		//MessageBox::Show("Painting");
		arbol->DrawTree(e->Graphics);
	}
	private: System::Void picTree_Resize_1(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show("Rezising");
		ArrangeTree();
	}


	private: System::Void comboBox_Algoritmos_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (comboBox_Algoritmos->SelectedIndex == 3 || comboBox_Algoritmos->SelectedIndex == 4) {
			comboBox_Distance->Enabled = true;
		}
		else {
			comboBox_Distance->Enabled = false;
		}
	}
};
}
