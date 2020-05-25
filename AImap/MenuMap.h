#pragma once
#include "Map.h"

namespace AImap {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MenuMap
	/// </summary>
	public ref class MenuMap : public System::Windows::Forms::Form
	{
	public:
		MenuMap(void)
		{
			InitializeComponent();
			float numero = 0.10;
			String ^specifier = "G";
			//System::Windows::Forms::MessageBox::Show(numero.ToString(specifier, gcnew System::Globalization::CultureInfo("eu-Es")));
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MenuMap()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected:
	private: System::Windows::Forms::Button^  button_OpenFile;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button_ChargeMap;
	private: System::Windows::Forms::TextBox^  textBox_FileNameMap;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MenuMap::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button_OpenFile = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_ChargeMap = (gcnew System::Windows::Forms::Button());
			this->textBox_FileNameMap = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->AutoUpgradeEnabled = false;
			this->openFileDialog1->Filter = L"Archivos de texto|*.txt";
			// 
			// button_OpenFile
			// 
			this->button_OpenFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_OpenFile->Location = System::Drawing::Point(303, 258);
			this->button_OpenFile->Name = L"button_OpenFile";
			this->button_OpenFile->Size = System::Drawing::Size(75, 23);
			this->button_OpenFile->TabIndex = 0;
			this->button_OpenFile->Text = L"Abrir";
			this->button_OpenFile->UseVisualStyleBackColor = true;
			this->button_OpenFile->Click += gcnew System::EventHandler(this, &MenuMap::button_OpenFile_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Location = System::Drawing::Point(23, 261);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Ruta:";
			// 
			// button_ChargeMap
			// 
			this->button_ChargeMap->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button_ChargeMap->Location = System::Drawing::Point(303, 287);
			this->button_ChargeMap->Margin = System::Windows::Forms::Padding(1);
			this->button_ChargeMap->Name = L"button_ChargeMap";
			this->button_ChargeMap->Size = System::Drawing::Size(75, 40);
			this->button_ChargeMap->TabIndex = 3;
			this->button_ChargeMap->Text = L"Crear Mapa";
			this->button_ChargeMap->UseVisualStyleBackColor = true;
			this->button_ChargeMap->Click += gcnew System::EventHandler(this, &MenuMap::button_ChargeMap_Click);
			// 
			// textBox_FileNameMap
			// 
			this->textBox_FileNameMap->Location = System::Drawing::Point(77, 260);
			this->textBox_FileNameMap->Name = L"textBox_FileNameMap";
			this->textBox_FileNameMap->Size = System::Drawing::Size(220, 20);
			this->textBox_FileNameMap->TabIndex = 4;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(87, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(226, 240);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// MenuMap
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(398, 336);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->textBox_FileNameMap);
			this->Controls->Add(this->button_ChargeMap);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_OpenFile);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MenuMap";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MenuMap";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	String ^aux;
	
	private: System::Void button_OpenFile_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			textBox_FileNameMap->Text = openFileDialog1->FileName;
			aux = openFileDialog1->FileName;
		}
	}
	private: System::Void button_ChargeMap_Click(System::Object^  sender, System::EventArgs^  e) {
		Map ^map;
		fstream readerFile;
		std::string str;
		
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(textBox_FileNameMap->Text)).ToPointer();
		str = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));

		readerFile.open(str, ios::in);
		if (readerFile.is_open()) {
			readerFile.close();
			map = gcnew Map(aux);
			//this->Hide();
			this->CenterToScreen();
			map->Show();
		}
		else {
			MessageBox::Show("Error, no se puede abrir la ruta especificada");
		}
		readerFile.close();
	}
};
}
