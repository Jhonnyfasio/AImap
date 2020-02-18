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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button_OpenFile = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_ChargeMap = (gcnew System::Windows::Forms::Button());
			this->textBox_FileNameMap = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Archivos de texto|*.txt";
			// 
			// button_OpenFile
			// 
			this->button_OpenFile->Location = System::Drawing::Point(277, 149);
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
			this->label1->Location = System::Drawing::Point(12, 158);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Ruta:";
			// 
			// button_ChargeMap
			// 
			this->button_ChargeMap->Location = System::Drawing::Point(136, 189);
			this->button_ChargeMap->Name = L"button_ChargeMap";
			this->button_ChargeMap->Size = System::Drawing::Size(75, 23);
			this->button_ChargeMap->TabIndex = 3;
			this->button_ChargeMap->Text = L"Crear Mapa";
			this->button_ChargeMap->UseVisualStyleBackColor = true;
			this->button_ChargeMap->Click += gcnew System::EventHandler(this, &MenuMap::button_ChargeMap_Click);
			// 
			// textBox_FileNameMap
			// 
			this->textBox_FileNameMap->Location = System::Drawing::Point(51, 151);
			this->textBox_FileNameMap->Name = L"textBox_FileNameMap";
			this->textBox_FileNameMap->Size = System::Drawing::Size(220, 20);
			this->textBox_FileNameMap->TabIndex = 4;
			// 
			// MenuMap
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(364, 224);
			this->Controls->Add(this->textBox_FileNameMap);
			this->Controls->Add(this->button_ChargeMap);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_OpenFile);
			this->Name = L"MenuMap";
			this->Text = L"MenuMap";
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
		map = gcnew Map(this, aux);
		this->Hide();
		map->Show();
	}
};
}
