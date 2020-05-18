#include <list>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Drawing;


namespace Howtoo {
	class AristaNode;

	class VerticeNode {
	public:
		VerticeNode *sigVertice;
		AristaNode *listaAdy;
		Cell elemento;
		int nivel = -1;

		friend class Arbol;
	};

	class AristaNode {
	public:
		AristaNode *sigArista;
		VerticeNode *verticePertenece;
		float peso;

		friend class Arbol;
	};

	class TreeNodes {
	private:
		float DataCenterX;
		float DataCenterY;
		float SpotCenterX;
		float SpotCenterY;
		Font ^*MyFont;
		bool something = false;
	public:

		class CircleNode
		{
			// The string we will draw.
		private:
			int algo;


			// Constructor.
		public:

			std::string Text;
			CircleNode() {
				//*Text = "";
			}

			CircleNode(std::string new_text) {
				Text = new_text;
			}

			// Return the size of the string plus a 10 pixel margin.
			SizeF GetSize(Graphics ^gr, Font ^font) {

				return gr->MeasureString(gcnew String(Text.c_str()), font) + SizeF(10, 10);
			}

			// Draw the object centered at (x, y).
			void Draw(float x, float y, Graphics ^gr, Pen ^pen, Brush ^bg_brush, Brush ^text_brush, Font ^font)
			{
				// Fill and draw an ellipse at our location.
				SizeF my_size = GetSize(gr, font);
				RectangleF rect = RectangleF(
					x - my_size.Width / 2,
					y - my_size.Height / 2,
					my_size.Width, my_size.Height);
				gr->FillEllipse(bg_brush, rect);
				gr->DrawEllipse(pen, rect);

				// Draw the text.
				System::Windows::Forms::MessageBox::Show("Drawing: " + gcnew String(Text.c_str()));
				System::Drawing::StringFormat ^string_format = gcnew StringFormat();
				{
					string_format->Alignment = StringAlignment::Center;
					string_format->LineAlignment = StringAlignment::Center;
					gr->DrawString(gcnew String(Text.c_str()), font, text_brush, x, y, string_format);
				}
			}

			// Return true if the node is above this point.
			// Note: The equation for an ellipse with half
			// width w and half height h centered at the origin is:
			//      x*x/w/w + y*y/h/h <= 1.
			bool IsAtPoint(Graphics ^gr, Font ^font, PointF center_pt, PointF target_pt)
			{
				// Get our size.
				SizeF my_size = GetSize(gr, font);

				// translate so we can assume the
				// ellipse is centered at the origin.
				target_pt.X -= center_pt.X;
				target_pt.Y -= center_pt.Y;

				// Determine whether the target point is under our ellipse.
				float w = my_size.Width / 2;
				float h = my_size.Height / 2;
				return
					target_pt.X * target_pt.X / w / w +
					target_pt.Y * target_pt.Y / h / h
					<= 1;
			}
		} Data;


		// The data.
		std::list<TreeNodes> Children;

		// Child nodes in the tree.

		//System::Collections::Generic::List<TreeNode> Children = new List<TreeNode>();


		// Drawing parameters.
		// Space to skip horizontally between siblings
		// and vertically between generations.
		float HOffset = 5;
		float VOffset = 10;

		// Spacing for verticaly orientation.
		float Indent = 20;
		float SpotRadius = 5;

		enum Orientations
		{
			Horizontal,
			Vertical
		} Orientatio;

		Orientations Orientation = Orientations::Horizontal;
		// Drawing properties.


		// Recursively set the subtree's orientation.
		void SetTreeDrawingParameters(float h_offset, float v_offset, float indent, float node_radius, Orientations orientation)
		{
			HOffset = h_offset;
			VOffset = v_offset;
			Indent = indent;
			SpotRadius = node_radius;
			Orientation = orientation;

			// Recursively sedt the properties for the subtree.
			/*for (it = Children.begin(); it != Children.end(); it++) {

			}*/
			for (TreeNodes child : Children) {
				child.SetTreeDrawingParameters(h_offset, v_offset,
					indent, node_radius, orientation);
			}
			/*for each(TreeNode child in Children)
				child.SetTreeDrawingParameters(h_offset, v_offset,
					indent, node_radius, orientation);*/
		}

		// Constructor.
		TreeNodes(CircleNode new_data)
		{
			Data = new_data;
			something = true;
		}
		/*TreeNode(CircleNode new_data, Font^ *fg_font)
		{
			Data = new_data;
			MyFont = fg_font;
		}*/

		// Add a TreeNode to out Children list.
		void AddChild(TreeNodes *child)
		{
			Children.push_back(*child);
		}

		// Arrange the node and its children in the allowed area.
		// Set xmin to indicate the right edge of our subtree.
		// Set ymin to indicate the bottom edge of our subtree.
		void Arrange(Graphics ^gr, float xmin, float ymin)
		{
			if (Orientation == TreeNodes::Orientations::Horizontal)
			{
				ArrangeHorizontally(gr, xmin, ymin);
			}
			else
			{
				ArrangeVertically(gr, xmin, ymin);
			}
		}

		// Arrange the subtree horizontally.
		void ArrangeHorizontally(Graphics ^gr, float xmin, float ymin)
		{
			// See how big this node is.
			SizeF my_size = Data.GetSize(gr, gcnew System::Drawing::Font("Arial", 7));

			// Recursively arrange our children,
			// allowing room for this node.
			float x = xmin;
			float biggest_ymin = ymin + my_size.Height;
			float subtree_ymin = ymin + my_size.Height + VOffset;
			for (TreeNodes child : Children)
			{
				System::Windows::Forms::MessageBox::Show("Hijo: " + gcnew String(child.Data.Text.c_str()));
				// Arrange this child's subtree.
				float child_ymin = subtree_ymin;
				child.Arrange(gr, x, child_ymin);

				// See if this increases the biggest ymin value.
				if (biggest_ymin < child_ymin) biggest_ymin = child_ymin;

				// Allow room before the next sibling.
				x += HOffset;
			}

			// Remove the spacing after the last child.
			if (Children.size() > 0) x -= HOffset;

			// See if this node is wider than the subtree under it.
			float subtree_width = x - xmin;
			if (my_size.Width > subtree_width)
			{
				// Center the subtree under this node.
				// Make the children rearrange themselves
				// moved to center their subtrees.
				x = xmin + (my_size.Width - subtree_width) / 2;
				for (TreeNodes child : Children)
				{
					// Arrange this child's subtree.
					child.Arrange(gr, x, subtree_ymin);

					// Allow room before the next sibling.
					x += HOffset;
				}

				// The subtree's width is this node's width.
				subtree_width = my_size.Width;
			}

			// Set this node's center position.
			DataCenterX = xmin + subtree_width / 2;
			DataCenterY = ymin + my_size.Height / 2;

			// Increase xmin to allow room for
			// the subtree before returning.
			xmin += subtree_width;

			// Set the return value for ymin.
			ymin = biggest_ymin;
		}

		// Arrange the subtree vertically.
		void ArrangeVertically(Graphics ^gr, float xmin, float ymin)
		{
			// See how big this node is.
			SizeF my_size = Data.GetSize(gr, gcnew System::Drawing::Font("Arial", 7));
			my_size.Width += 3 * SpotRadius;

			// Set the position of this node's spot.
			SpotCenterX = xmin + SpotRadius;
			SpotCenterY = ymin + (my_size.Height - 2 * SpotRadius) / 2;

			// Set the position of this node's data.

			DataCenterX = SpotCenterX + SpotRadius + my_size.Width / 2;
			DataCenterY = SpotCenterY;


			// Allow vertical room for this node.
			ymin += my_size.Height + VOffset;

			// Recursively arrange our children.
			for (TreeNodes child : Children)
			{
				// Arrange this child's subtree.
				child.ArrangeVertically(gr, xmin + Indent, ymin);
			}
		}

		// Draw the subtree rooted at this node
		// with the given upper left corner.
		void DrawTree(Graphics ^gr, float x, float y)
		{
			// Arrange the tree.
			Arrange(gr, x, y);

			// Draw the tree.
			DrawTree(gr);
		}

		// Draw the subtree rooted at this node.
		void DrawTree(Graphics ^gr)
		{
			// Draw the links.
			DrawSubtreeLinks(gr);

			// Draw the nodes.
			DrawSubtreeNodes(gr);
		}

		// Draw the links for the subtree rooted at this node.
		void DrawSubtreeLinks(Graphics ^gr)
		{
			if (Orientation == TreeNodes::Orientations::Horizontal)
			{
				DrawSubtreeLinksHorizontal(gr);
			}
			else
			{
				DrawSubtreeLinksVertical(gr);
			}
		}

		// Draw the links for the horizontal subtree rooted at this node.
		void DrawSubtreeLinksHorizontal(Graphics ^gr)
		{
			for (TreeNodes child : Children)
			{
				// Draw the link between this node this child.
				gr->DrawLine(Pens::Black, PointF(DataCenterX, DataCenterY), Point(child.DataCenterX, child.DataCenterY));
				// Recursively make the child draw its subtree nodes.
				child.DrawSubtreeLinksHorizontal(gr);
			}
		}

		// Draw the links for the subtree rooted at this node.
		void DrawSubtreeLinksVertical(Graphics ^gr)
		{
			for (TreeNodes child : Children)
			{
				// Draw the link between this node this child.
				gr->DrawLine(Pens::Black, SpotCenterX, SpotCenterY, SpotCenterX, child.SpotCenterY);
				gr->DrawLine(Pens::Black, SpotCenterX, child.SpotCenterY, child.SpotCenterX, child.SpotCenterY);

				// Recursively make the child draw its subtree nodes.
				child.DrawSubtreeLinksVertical(gr);
			}
		}

		// Draw the nodes for the subtree rooted at this node.
		void DrawSubtreeNodes(Graphics ^gr)
		{
			// Draw this node.

			Data.Draw(DataCenterX, DataCenterY, gr, Pens::Black, Brushes::White, Brushes::Black, gcnew System::Drawing::Font("Arial", 7));

			// If oriented vertically, draw the node's spot.
			if (Orientation == TreeNodes::Orientations::Vertical)
			{
				RectangleF rect = RectangleF(
					SpotCenterX - SpotRadius, SpotCenterY - SpotRadius,
					2 * SpotRadius, 2 * SpotRadius);
				if (Children.size() > 0)
				{
					gr->FillEllipse(Brushes::LightBlue, rect);
				}
				else
				{
					gr->FillEllipse(Brushes::Orange, rect);
				}
				gr->DrawEllipse(Pens::Black, rect);
			}

			// Recursively make the child draw its subtree nodes.
			for (TreeNodes child : Children)
			{
				child.DrawSubtreeNodes(gr);
			}
		}
		// Return the TreeNode at this point (or null if there isn't one there).
		bool& operator == (const TreeNodes& T) {
			return *this == T;
		}

		TreeNodes *NodeAtPoint(Graphics ^gr, PointF target_pt)
		{
			// See if the point is under this node.
			if (Data.IsAtPoint(gr, gcnew System::Drawing::Font("Arial", 7), PointF(DataCenterX, DataCenterY), target_pt)) return this;

			// See if the point is under a node in the subtree.
			for (TreeNodes child : Children)
			{
				TreeNodes *hit_node = child.NodeAtPoint(gr, target_pt);
				if (hit_node != nullptr) return hit_node;
			}

			return nullptr;
		}

		// Delete a target node from this node's subtree.
		// Return true if we delete the node.
		bool DeleteNode(TreeNodes target)
		{
			// See if the target is in our subtree.
			for (TreeNodes child : Children)
			{
				// See if it's the child.
				if (child == target)
				{
					// Delete this child.
					Children.remove(child);
					return true;
				}

				// See if it's in the child's subtree.
				if (child.DeleteNode(target)) return true;
			}

			// It's not in our subtree.
			return false;
		}
	};

}