#pragma once
#include "arbol.h"

namespace AImap {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Drawing::Text;
	Arbol *root;
	/// <summary>
	/// Resumen de Tree
	/// </summary>
	public ref class Tree : public System::Windows::Forms::Form
	{
	public:
		
		Tree(void) {
			InitializeComponent();
			Cell raiz,a_node, b_node, c_node, d_node, e_node, f_node, g_node, h_node;
			root = new Arbol();
			raiz.setPositionX(9);
			raiz.setPositionY(9);

			a_node.setPositionX(0);
			a_node.setPositionY(0);

			b_node.setPositionX(1);
			b_node.setPositionY(0);

			c_node.setPositionX(2);
			c_node.setPositionY(0);

			d_node.setPositionX(3);
			d_node.setPositionY(0);

			e_node.setPositionX(4);
			e_node.setPositionY(0);

			f_node.setPositionX(5);
			f_node.setPositionY(0);

			g_node.setPositionX(6);
			g_node.setPositionY(0);

			h_node.setPositionX(7);
			h_node.setPositionY(0);

			a_node.setId(0);
			b_node.setId(1);
			c_node.setId(2);
			d_node.setId(3);
			e_node.setId(4);
			f_node.setId(5);
			g_node.setId(6);
			h_node.setId(7);

			root->insertaVertice(raiz);
			root->insertaVertice(a_node);
			root->insertaVertice(b_node);
			root->insertaVertice(c_node);
			root->insertaVertice(d_node);
			root->insertaVertice(e_node);
			root->insertaVertice(f_node);
			root->insertaVertice(g_node);
			root->insertaVertice(h_node);

			root->insertaArista(root->existeVertice(raiz), root->existeVertice(a_node), 1);
			root->insertaArista(root->existeVertice(raiz), root->existeVertice(b_node), 1);
			root->insertaArista(root->existeVertice(a_node), root->existeVertice(c_node), 1);
			root->insertaArista(root->existeVertice(a_node), root->existeVertice(d_node), 1);
			root->insertaArista(root->existeVertice(b_node), root->existeVertice(e_node), 1);
			root->insertaArista(root->existeVertice(b_node), root->existeVertice(f_node), 1);
			root->insertaArista(root->existeVertice(b_node), root->existeVertice(g_node), 1);
			root->insertaArista(root->existeVertice(e_node), root->existeVertice(h_node), 1);
			
			
			ArrangeTree();
		}

		Tree(Arbol* ancla)
		{
			InitializeComponent();
			root = ancla;
			//
			//TODO: agregar código de constructor aquí
			//
			
			ArrangeTree();
			
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Tree()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  picTree;
	private: System::Windows::Forms::RadioButton^  radHorizontal;
	private: System::Windows::Forms::RadioButton^  radVertical;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
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
			this->picTree = (gcnew System::Windows::Forms::PictureBox());
			this->radHorizontal = (gcnew System::Windows::Forms::RadioButton());
			this->radVertical = (gcnew System::Windows::Forms::RadioButton());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picTree))->BeginInit();
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// picTree
			// 
			this->picTree->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->picTree->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->picTree->Location = System::Drawing::Point(3, 3);
			this->picTree->Name = L"picTree";
			this->picTree->Size = System::Drawing::Size(281, 392);
			this->picTree->TabIndex = 0;
			this->picTree->TabStop = false;
			this->picTree->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Tree::picTree_Paint);
			this->picTree->Resize += gcnew System::EventHandler(this, &Tree::picTree_Resize_1);
			// 
			// radHorizontal
			// 
			this->radHorizontal->AutoSize = true;
			this->radHorizontal->Location = System::Drawing::Point(12, 12);
			this->radHorizontal->Name = L"radHorizontal";
			this->radHorizontal->Size = System::Drawing::Size(72, 17);
			this->radHorizontal->TabIndex = 1;
			this->radHorizontal->TabStop = true;
			this->radHorizontal->Text = L"Horizontal";
			this->radHorizontal->UseVisualStyleBackColor = true;
			this->radHorizontal->Click += gcnew System::EventHandler(this, &Tree::radHorizontal_Click);
			// 
			// radVertical
			// 
			this->radVertical->AutoSize = true;
			this->radVertical->Location = System::Drawing::Point(119, 12);
			this->radVertical->Name = L"radVertical";
			this->radVertical->Size = System::Drawing::Size(60, 17);
			this->radVertical->TabIndex = 2;
			this->radVertical->TabStop = true;
			this->radVertical->Text = L"Vertical";
			this->radVertical->UseVisualStyleBackColor = true;
			this->radVertical->Click += gcnew System::EventHandler(this, &Tree::radVertical_Click);
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->Controls->Add(this->picTree);
			this->flowLayoutPanel1->Location = System::Drawing::Point(1, 53);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(287, 425);
			this->flowLayoutPanel1->TabIndex = 3;
			// 
			// Tree
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(289, 490);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->radVertical);
			this->Controls->Add(this->radHorizontal);
			this->Name = L"Tree";
			this->Text = L"Tree";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picTree))->EndInit();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// Center the tree on the form.
		void ArrangeTree()
		{
			float x, y;
			Graphics ^gr = picTree->CreateGraphics();
			{
				if (root->Orientation == root->Orientations::Horizontal)
				
				{
					// Arrange the tree once to see how big it is.
					float xmin = 0, ymin = 0;
					//MessageBox::Show(gcnew String(root->mostrarListaAdyacencia().c_str()));
					root->Arrange(gr, xmin, ymin, root->getAncla());

					// Arrange the tree again to center it horizontally.
					//MessageBox::Show("Again");
					xmin = (picTree->ClientSize.Width - xmin) / 2;
					ymin = 10;
					root->Arrange(gr, xmin, ymin, root->getAncla());
					x = xmin;
					y = ymin;
					//MessageBox::Show("Again: " + picTree->ClientSize.Width);
				}
				else
				{
					// Arrange the tree.
					float xmin = root->Indent;//@
					float ymin = xmin;
					root->Arrange(gr, xmin, ymin, root->getAncla());
					x = root->nivelTotal() * 30;
					y = ymin;
				}
				picTree->Size = System::Drawing::Size(x+30, y+30);
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
				//SelectedNode = root->NodeAtPoint(gr, pt);
			}
		}

		
		// Change the tree's orientation.
		private: System::Void radHorizontal_Click(System::Object^ sender, System::EventArgs ^e)
		{
			root->SetTreeDrawingParameters(5, 30, 20, 5,
				root->Orientations::Horizontal, root->getAncla());
			ArrangeTree();
		}

		private: System::Void radVertical_Click(System::Object^ sender, System::EventArgs ^e)
		{
			root->SetTreeDrawingParameters(5, 2, 20, 5,
				root->Orientations::Vertical, root->getAncla());
			ArrangeTree();
		}
		private: System::Void picTree_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	
			e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
			e->Graphics->TextRenderingHint = TextRenderingHint::AntiAliasGridFit;
			//MessageBox::Show("Painting");
			root->DrawTree(e->Graphics);
		}
		private: System::Void picTree_Resize_1(System::Object^  sender, System::EventArgs^  e) {
			//MessageBox::Show("Rezising");
			ArrangeTree();
		}
};
}
