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
		
		Tree(Arbol* ancla)
		{
			InitializeComponent();
			root = ancla;
			//
			//TODO: agregar código de constructor aquí
			//
			/*Cell raiz,a_node, b_node, c_node, d_node, e_node, f_node, g_node, h_node;
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
			/root->insertaArista(root->existeVertice(e_node), root->existeVertice(h_node), 1);
			*/

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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picTree))->BeginInit();
			this->SuspendLayout();
			// 
			// picTree
			// 
			this->picTree->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->picTree->Location = System::Drawing::Point(6, 42);
			this->picTree->Name = L"picTree";
			this->picTree->Size = System::Drawing::Size(390, 490);
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
			// 
			// Tree
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(405, 544);
			this->Controls->Add(this->radVertical);
			this->Controls->Add(this->radHorizontal);
			this->Controls->Add(this->picTree);
			this->Name = L"Tree";
			this->Text = L"Tree";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picTree))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		

		// Center the tree on the form.
		void picTree_Resize(System::Object^ sender, System::EventArgs e)
		{
			ArrangeTree();
		}

		void ArrangeTree()
		{
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
					//MessageBox::Show("Again: " + picTree->ClientSize.Width);
				}
				else
				{
					// Arrange the tree.
					float xmin = root->Indent;//@
					float ymin = xmin;
					root->Arrange(gr, xmin, ymin, root->getAncla());
				}
			}

			picTree->Refresh();
		}
		/*
		// The currently selected node.
		Howtoo::TreeNode *SelectedNode;

		// Display the text of the node under the mouse.
		void picTree_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs e)
		{
			// Find the node under the mouse.
			FindNodeUnderMouse(e.Location);

			// If there is a node under the mouse,
			// display the node's text.
			if (SelectedNode == nullptr)
			{
				lblNodeText.Text = "";
			}
			else
			{
				lblNodeText.Text = SelectedNode.Data.Text;
			}
		}

		// If this is a right button down and the
		// mouse is over a node, display a context menu.
		private void picTree_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button != MouseButtons.Right) return;

			// Find the node under the mouse.
			FindNodeUnderMouse(e.Location);

			// If there is a node under the mouse,
			// display the context menu.
			if (SelectedNode != null)
			{
				// Don't let the user delete the root node.
				// (The TreeNode class can't do that.)
				ctxNodeDelete.Enabled = (SelectedNode != root);

				// Display the context menu.
				ctxNode.Show(this, e.Location);
			}
		}

		// Set SelectedNode to the node under the mouse.
		private void FindNodeUnderMouse(PointF pt)
		{
			using (Graphics gr = picTree.CreateGraphics())
			{
				SelectedNode = root.NodeAtPoint(gr, pt);
			}
		}

		// Add a child to the selected node.
		private void ctxNodeAddChild_Click(object sender, EventArgs e)
		{
			NodeTextDialog dlg = new NodeTextDialog();
			if (dlg.ShowDialog() == DialogResult.OK)
			{
				TreeNode<CircleNode> child =
					new TreeNode<CircleNode>(new CircleNode(dlg.txtNodeText.Text));
				child.Orientation = root.Orientation;
				SelectedNode.AddChild(child);

				// Rearrange the tree to show the new node.
				ArrangeTree();
			}
		}

		// Delete this node from the tree.
		private void ctxNodeDelete_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Are you sure you want to delete this node?",
				"Delete Node?", MessageBoxButtons.YesNo,
				MessageBoxIcon.Question) == DialogResult.Yes)
			{
				// Delete the node and its subtree.
				root.DeleteNode(SelectedNode);

				// Rearrange the tree to show the new structure.
				ArrangeTree();
			}
		}
		*/
		// Change the tree's orientation.
		void radHorizontal_Click(System::Object^ sender, System::EventArgs e)
		{
			root->SetTreeDrawingParameters(5, 10, 20, 5,
				root->Orientations::Horizontal, root->getAncla());
			ArrangeTree();
		}

		void radVertical_Click(System::Object^ sender, System::EventArgs e)
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
