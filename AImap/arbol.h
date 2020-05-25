#pragma once

#include "cell.h"
#include <iostream>

using namespace System::Drawing;

class Arista;

class Vertice {
public:
	Vertice *sigVertice;
	Arista *listaAdy;
	Cell elemento;
	bool isArista = false;
	
	int nivel = -1;
	bool isPath = false;

	float DataCenterX;
	float DataCenterY;
	float SpotCenterX;
	float SpotCenterY;

	friend class Arbol;

	Vertice() {
		//*Text = "";
	}

	Vertice(Cell &elementoX) {
		elemento = elementoX;
	}

	SizeF GetSize(Graphics ^gr, Font ^font) {

		return gr->MeasureString(gcnew System::String(elemento.getName().c_str()), font) + SizeF(10, 10);
	}

	// Draw the object centered at (x, y).
	void Draw(float x, float y, System::Drawing::Graphics ^gr, System::Drawing::Pen ^pen, 
		System::Drawing::Brush ^bg_brush, System::Drawing::Brush ^text_brush, 
		System::Drawing::Font ^font, float xS, float yS)
	{
		// Fill and draw an ellipse at our location.
		System::Drawing::SizeF my_size = GetSize(gr, font);
		System::Drawing::RectangleF rect = System::Drawing::RectangleF(
			x - my_size.Width / 2,
			y - my_size.Height / 2,
			my_size.Width, my_size.Height);
		if (isPath) {
			gr->FillEllipse(Brushes::Yellow, rect);
		}
		else {
			gr->FillEllipse(bg_brush, rect);
		}
		
		gr->DrawEllipse(pen, rect);

		// Draw the text.
		System::Drawing::StringFormat ^string_format = gcnew System::Drawing::StringFormat();
		{
			string_format->Alignment = System::Drawing::StringAlignment::Center;
			string_format->LineAlignment = System::Drawing::StringAlignment::Center;
			gr->DrawString(gcnew System::String(elemento.getName().c_str()), font, text_brush, x, y, string_format);
			gr->DrawString(("Visita: " + gcnew System::String(elemento.getVisitCounter().c_str()) + "\nCosto: " + (elemento.getDistanciaGN() + elemento.getDistanciaHN())), 
				gcnew System::Drawing::Font("Arial", 7), text_brush, x+xS, y+yS);
		}
	}

	// Return true if the node is above this point.
	// Note: The equation for an ellipse with half
	// width w and half height h centered at the origin is:
	//      x*x/w/w + y*y/h/h <= 1.
	bool IsAtPoint(System::Drawing::Graphics ^gr, System::Drawing::Font ^font, 
		System::Drawing::PointF center_pt, System::Drawing::PointF target_pt)
	{
		// Get our size.
		System::Drawing::SizeF my_size = GetSize(gr, font);

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
};

class Arista {
public:
	Arista *sigArista;
	Vertice *verticePertenece;
	float peso;

	friend class Arbol;
};

class Arbol {
private:
	Vertice *ancla;
	System::Drawing::Font ^*myFont;
public:

	friend class Vertice;
	Arbol() {
		Inicializa();
	}

	Vertice* getAncla() {
		return ancla;
	}

	void Inicializa() {
		ancla = nullptr;
	}

	bool Vacio() {
		return ancla == nullptr;
	}

	int Tamanio() {
		Vertice *aux;
		int contador;

		contador = 0;
		aux = ancla;

		while (aux != nullptr) {
			aux = aux->sigVertice;
			contador++;
		}

		return contador;
	}

	Vertice *existeVertice(Cell elem) {  ///Retorna el puntero en donde se encuentra el vertice
		Vertice *aux;
		aux = ancla;

		while (aux != nullptr) {
			if (aux->elemento == elem) {
				return aux;
			}

			aux = aux->sigVertice;
		}

		return nullptr;
	}

	void insertaVertice(Cell elem) {
		Vertice *nuevoVertice = new Vertice;
		nuevoVertice->elemento = elem;
		nuevoVertice->sigVertice = nullptr;
		nuevoVertice->listaAdy = nullptr;

		if (Vacio()) {
			nuevoVertice->nivel = 0;
			ancla = nuevoVertice;
			//System::Windows::Forms::MessageBox::Show("Insertando Vacio: " + System::Char::ToString('A' + elem.getPositionX()) + "," + (elem.getPositionY() + 1).ToString());
		}
		else {
			if (existeVertice(elem) == nullptr) {
				Vertice *aux;
				aux = ancla;
				while (aux->sigVertice != nullptr) {
					aux = aux->sigVertice;
				}

				//System::Windows::Forms::MessageBox::Show("Insertando: " + System::Char::ToString('A' + elem.getPositionX()) + ","+(elem.getPositionY()+1).ToString());
				aux->sigVertice = nuevoVertice;
			}
		}
	}

	void insertaArista(Vertice* origen, Vertice* destino, float peso) {
		Arista *nuevaArista = new Arista;
		nuevaArista->peso = peso;
		nuevaArista->sigArista = nullptr;
		nuevaArista->verticePertenece = nullptr;

		Arista *aux;

		aux = origen->listaAdy;

		if (aux == nullptr) {
			origen->listaAdy = nuevaArista;
			nuevaArista->verticePertenece = destino;
			if (destino->nivel == -1) {
				destino->nivel = origen->nivel + 1;
			}
		}
		else {
			while (aux->sigArista != nullptr) {
				aux = aux->sigArista;
			}

			aux->sigArista = nuevaArista;
			nuevaArista->verticePertenece = destino;
			if (destino->nivel == -1) {
				destino->nivel = origen->nivel + 1;
			}
		}
	}

	/*std::string mostrarListaAdyacencia() {
		Vertice *verticeAux;
		Arista *aristaAux;
		std::string cadenaListaAdy;
		std::stringstream toStr;

		verticeAux = ancla;
		System::Windows::Forms::MessageBox::Show(Tamanio().ToString());
		while (verticeAux != nullptr) {
			cadenaListaAdy += verticeAux->elemento.getName()+"->";
			aristaAux = verticeAux->listaAdy;

			while (aristaAux != nullptr) {
				toStr.str("");
				if (aristaAux->sigArista == nullptr) {
					toStr << aristaAux->peso;
					cadenaListaAdy += aristaAux->verticePertenece->elemento.getName() + ':' + toStr.str();
				}
				else {
					toStr << aristaAux->peso;
					cadenaListaAdy += aristaAux->verticePertenece->elemento.getName() + ':' + toStr.str();
					cadenaListaAdy += "->";
				}
				aristaAux = aristaAux->sigArista;
			}

			verticeAux = verticeAux->sigVertice;
			cadenaListaAdy += '\n';
		}
		return cadenaListaAdy;
	}*/

	std::string mostrarListaAdyacencia() {
		Vertice *verticeAux;
		Arista *aristaAux;
		std::string cadenaListaAdy;
		std::stringstream toStr;
		std::stringstream toStr2;       //Agregado para mostrar nivel

		verticeAux = ancla;

		while (verticeAux != nullptr) {
			toStr2.str("");              //Agregado para mostrar nivel
			//cadenaListaAdy += verticeAux->elemento.getName()+"->";     //Anteriormente...
			toStr2 << verticeAux->nivel;  //Agregado para mostrar nivel
			cadenaListaAdy += verticeAux->elemento.getName() + "(" + toStr2.str() + ")" + "->";  //Agregado para mostrar nivel
			aristaAux = verticeAux->listaAdy;

			while (aristaAux != nullptr) {
				toStr.str("");
				if (aristaAux->sigArista == nullptr) {
					toStr << aristaAux->peso;
					cadenaListaAdy += aristaAux->verticePertenece->elemento.getName() + ':' + toStr.str();
				}
				else {
					toStr << aristaAux->peso;
					cadenaListaAdy += aristaAux->verticePertenece->elemento.getName() + ':' + toStr.str();
					cadenaListaAdy += "->";
				}
				aristaAux = aristaAux->sigArista;
			}

			verticeAux = verticeAux->sigVertice;
			cadenaListaAdy += '\n';
		}
		return cadenaListaAdy;
	}

	void eliminarArista(Vertice* origen, Vertice* destino) {
		int band = 0;
		Arista *actual, *anterior;
		actual = origen->listaAdy;

		if (actual == nullptr) {
			std::cout << "El vértice origen no tiene aristas";
		}
		else if (actual->verticePertenece == destino) {
			origen->listaAdy = actual->sigArista;
			delete(actual);
		}
		else {
			while (actual != nullptr) {
				if (actual->verticePertenece == destino) {
					band = 1;
					anterior->sigArista = actual->sigArista;
					delete (actual);
					break;
				}

				anterior = actual;
				actual = actual->sigArista;
			}

			if (band == 0) {
				std::cout << "Los vértices no están conectados entre ellos";
			}
		}
	}

	void eliminarTodo() {
		Vertice *aux;
		Arista *aristaAux, *auxElimi;

		while (ancla != nullptr) {
			aux = ancla;

			aristaAux = ancla->listaAdy;
			while (aristaAux != nullptr) {
				auxElimi = aristaAux;
				aristaAux = aristaAux->sigArista;
				delete(auxElimi);
			}

			ancla = ancla->sigVertice;
			delete(aux);
		}
	}

	void eliminarVertice(Vertice* vertice) {
		Vertice *actual, *anterior;
		Arista *aux;

		actual = ancla;

		while (actual != nullptr) {
			aux = actual->listaAdy;
			while (aux != nullptr) {
				if (aux->verticePertenece == vertice) {
					eliminarArista(actual, aux->verticePertenece);
					break;
				}
				aux = aux->sigArista;
			}
			actual = actual->sigVertice;
		}

		actual = ancla;

		if (ancla == vertice) {
			ancla = ancla->sigVertice;
			delete(actual);
		}
		else {
			while (actual != vertice) {
				anterior = actual;
				actual = actual->sigVertice;
			}

			anterior->sigVertice = actual->sigVertice;
			delete(actual);
		}
	}

	bool existeArista(Vertice* origen, Vertice *destino) {
		Arista *aristaAux;

		aristaAux = origen->listaAdy;

		if (aristaAux == nullptr) {
			std::cout << "Este vértice no tiene aristas";
			return false;
		}

		while (aristaAux != nullptr) {
			if (aristaAux->verticePertenece == destino) {
				return true;
				break;
			}

			aristaAux = aristaAux->sigArista;
		}
		return false;
	}

	//Cantidad de hojas en todo el arbol
	int hojasTotal() {
		Vertice *verticeAux;
		Arista *aristaAux;
		int cantHojas = 0;

		verticeAux = ancla;

		while (verticeAux != nullptr) {
			aristaAux = verticeAux->listaAdy;

			if (aristaAux == nullptr) {
				cantHojas++;
			}
			verticeAux = verticeAux->sigVertice;
		}
		return cantHojas;
	}

	///Cuantas hojas tiene un vertice
	int cantHojas(Vertice* origen) {
		Vertice *verticeAux;
		Arista *aristaAux;
		int cantHojas = 0;

		verticeAux = origen;

		if (verticeAux != nullptr) {
			aristaAux = verticeAux->listaAdy;

			while (aristaAux != nullptr) {

				if (aristaAux->verticePertenece->listaAdy == nullptr) {
					cantHojas++;
				}
				aristaAux = aristaAux->sigArista;
			}
		}
		return cantHojas;
	}

	//Cuantos niveles hay desde un vertice 
	int cantNiveles(Vertice* origen) {
		int totalNivel, cantNivel = 0;

		totalNivel = nivelTotal();

		cantNivel = totalNivel - origen->nivel;

		return cantNivel;
	}

	int nivelTotal() {    //Profundidad
		Vertice *aux;
		int nivelMax = 0;

		aux = ancla;
		while (aux != nullptr) {
			if (aux->nivel > nivelMax) {
				nivelMax = aux->nivel;
			}
			aux = aux->sigVertice;
		}
		return nivelMax;
	}

	Vertice* anterior(Vertice* toFind) {
		Vertice *verticeAux, *aux;
		int cantHojas = 0;

		verticeAux = ancla;

		while (verticeAux != nullptr) {

			if (existeArista(verticeAux, toFind)) {
				return verticeAux;
			}
		verticeAux = verticeAux->sigVertice;
		}
		return nullptr;
	}

	Vertice* first() {
		if (!Vacio()) {
			return ancla;
		}
		return nullptr;
	}

	//En un nivel especifico cuantos vertices hay
	int cantidadVertices(int nivel) {
		Vertice *aux;
		int cantVertices = 0;
		bool existeNivel = false;

		aux = ancla;
		while (aux != nullptr) {
			if (aux->nivel == nivel) {
				existeNivel = true;
				cantVertices++;
			}
			aux = aux->sigVertice;
		}
		if (!existeNivel) {
			cantVertices = -1;
		}
		return cantVertices;
	}

	int cantidadHijos(Vertice* padre) {
		int cantHijos = 0;
		Arista* aux = padre->listaAdy;
		while (aux != nullptr) {
			cantHijos++;
			aux = aux->sigArista;
		}
		return cantHijos;
	}

	///////////////////////////////////// TreeNodes ////////////////////////////////////////////////

	private:
		
		bool something = false;
public:

	// The data.
	//std::list<TreeNodes> Children;

	// Child nodes in the tree.

	//System::Collections::Generic::List<TreeNode> Children = new List<TreeNode>();


	// Drawing parameters.
	// Space to skip horizontally between siblings
	// and vertically between generations.
	float HOffset = 5;
	float VOffset = 30;

	// Spacing for verticaly orientation.
	float Indent = 20;
	float SpotRadius = 5;

	enum Orientations
	{
		Horizontal,
		Vertical
	};

	Orientations Orientation = Orientations::Horizontal;
	// Drawing properties.


	// Recursively set the subtree's orientation.
	void SetTreeDrawingParameters(float h_offset, float v_offset, float indent, float node_radius, 
		Orientations orien, Vertice* vertice)
	{
		HOffset = h_offset;
		VOffset = v_offset;
		Indent = indent;
		SpotRadius = node_radius;
		Orientation = orien;

		// Recursively sedt the properties for the subtree.
		/*for (it = Children.begin(); it != Children.end(); it++) {

		}*/
		for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
			SetTreeDrawingParameters(h_offset, v_offset,
				indent, node_radius, orien, child->verticePertenece);
		}
		/*for each(TreeNode child in Children)
			child.SetTreeDrawingParameters(h_offset, v_offset,
				indent, node_radius, orientation);*/
	}

	// Constructor.
	/*TreeNodes(CircleNode new_data)
	{
		Data = new_data;
		something = true;
	}*/

	// Add a TreeNode to out Children list.
	/*void AddChild(TreeNodes *child)
	{
		Children.push_back(*child);
	}*/

	// Arrange the node and its children in the allowed area.
	// Set xmin to indicate the right edge of our subtree.
	// Set ymin to indicate the bottom edge of our subtree.
	void Arrange(System::Drawing::Graphics ^gr, float& xmin, float& ymin, Vertice *vertice)
	{
		
		if (Orientation == Arbol::Orientations::Horizontal)
		{
			ArrangeHorizontally(gr, xmin, ymin, vertice);
		}
		else
		{
			ArrangeVertically(gr, xmin, ymin, vertice);
		}
	}

	// Arrange the subtree horizontally.
	void ArrangeHorizontally(Graphics ^gr, float& xmin, float& ymin, Vertice *vertice)
	{
		// See how big this node is.
		SizeF my_size = vertice->GetSize(gr, gcnew Font("Times New Roman", 12));
		//
		// Recursively arrange our children,
		// allowing room for this node.
		float x = xmin;
		float biggest_ymin = ymin + my_size.Height;
		float subtree_ymin = ymin + my_size.Height + VOffset;
	//	System::Windows::Forms::MessageBox::Show("Arraging: Biggest" + biggest_ymin + "\nSubtree" + subtree_ymin);
		for (Arista* child= vertice->listaAdy; child != nullptr; child = child->sigArista) {
	//		System::Windows::Forms::MessageBox::Show("X: " + x + " - "+ "Padre: "+ gcnew System::String(vertice->elemento.getName().c_str()) +
	//			" - Hijo: " + gcnew System::String(child->verticePertenece->elemento.getName().c_str()));
			// Arrange this child's subtree.
			float child_ymin = subtree_ymin;

	//		System::Windows::Forms::MessageBox::Show("Inicial first arraging: " + x + "\nBiggest " + biggest_ymin +
	//			"\nChild " + child_ymin);

			Arrange(gr, x, child_ymin, child->verticePertenece);

			// See if this increases the biggest ymin value.
			if (biggest_ymin < child_ymin) biggest_ymin = child_ymin;

			// Allow room before the next sibling.
			x += HOffset;
	//		System::Windows::Forms::MessageBox::Show("Ending first arraging: " + x + "\nBiggest " + biggest_ymin +
	//			"\nChild " + child_ymin);
		}

		// Remove the spacing after the last child.
	//	System::Windows::Forms::MessageBox::Show("X: " + x);
		if (cantidadHijos(vertice) > 0) x -= HOffset;

		// See if this node is wider than the subtree under it.
		float subtree_width = x - xmin;
	//	System::Windows::Forms::MessageBox::Show(my_size.Width + " - " + subtree_width + " - " + x);
		if (my_size.Width > subtree_width)
		{
			// Center the subtree under this node.
			// Make the children rearrange themselves
			// moved to center their subtrees.
			x = xmin + (my_size.Width - subtree_width) / 2;
	//		System::Windows::Forms::MessageBox::Show("Padre: " + gcnew System::String(vertice->elemento.getName().c_str()) + "x: " + x);
			for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
				// Arrange this child's subtree.
	//			System::Windows::Forms::MessageBox::Show("Second Arragin");
				Arrange(gr, x, subtree_ymin, child->verticePertenece);

				// Allow room before the next sibling.
				x += HOffset;
			}

			// The subtree's width is this node's width.
			subtree_width = my_size.Width;
	//		System::Windows::Forms::MessageBox::Show("Ending: " + x + "\nSubtree Width " + subtree_width);
		}

		// Set this node's center position.
		vertice->DataCenterX = xmin + subtree_width / 2;
		vertice->DataCenterY = ymin + my_size.Height / 2;

		// Increase xmin to allow room for
		// the subtree before returning.
		xmin += subtree_width;

		// Set the return value for ymin.
		ymin = biggest_ymin;
	}

	// Arrange the subtree vertically.

	void ArrangeVertically(Graphics ^gr, float xmin, float& ymin, Vertice *vertice)
	{
		// See how big this node is.
		SizeF my_size =vertice->GetSize(gr, gcnew Font("Times New Roman", 12));
		my_size.Width += 3 * SpotRadius;

		// Set the position of this node's spot.
		vertice->SpotCenterX = xmin + SpotRadius;
		vertice->SpotCenterY = ymin + (my_size.Height - 2 * SpotRadius) / 2;

		// Set the position of this node's data.

		vertice->DataCenterX = vertice->SpotCenterX + SpotRadius + my_size.Width / 2;
		vertice->DataCenterY = vertice->SpotCenterY;


		// Allow vertical room for this node.
		ymin += my_size.Height + VOffset;

		/*System::Windows::Forms::MessageBox::Show("Vertically: \n" + vertice->SpotCenterX + "\n" + 
		vertice->SpotCenterY + "\n" + vertice->DataCenterX + "\n" + vertice->DataCenterY + 
		"\nYMin: " + ymin);*/

		// Recursively arrange our children.
		for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
			// Arrange this child's subtree.
			ArrangeVertically(gr, xmin + Indent, ymin, child->verticePertenece);
		}
	}
	
	// Draw the subtree rooted at this node
	// with the given upper left corner.
	void DrawTree(Graphics ^gr, float& x, float y)
	{
		// Arrange the tree.
		Arrange(gr, x, y, ancla);

		// Draw the tree.
		DrawTree(gr);
	}

	// Draw the subtree rooted at this node.
	void DrawTree(Graphics ^gr)
	{
		
		// Draw the links.
		DrawSubtreeLinks(gr);
		
		// Draw the nodes.
		DrawSubtreeNodes(gr, ancla);
	}

	// Draw the links for the subtree rooted at this node.
	void DrawSubtreeLinks(Graphics ^gr)
	{
		if (Orientation == Arbol::Orientations::Horizontal)
		{
			DrawSubtreeLinksHorizontal(gr, ancla);
		}
		else
		{
			DrawSubtreeLinksVertical(gr, ancla);
		}
	}

	// Draw the links for the horizontal subtree rooted at this node.
	void DrawSubtreeLinksHorizontal(Graphics ^gr, Vertice* vertice)
	{
		for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
			// Draw the link between this node this child.
			gr->DrawLine(Pens::Black, PointF(vertice->DataCenterX, vertice->DataCenterY), PointF(child->verticePertenece->DataCenterX, child->verticePertenece->DataCenterY));
			// Recursively make the child draw its subtree nodes.
			DrawSubtreeLinksHorizontal(gr, child->verticePertenece);
		}
	}

	// Draw the links for the subtree rooted at this node.
	
	void DrawSubtreeLinksVertical(Graphics ^gr, Vertice* vertice)
	{
		
		for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
			// Draw the link between this node this child.
			gr->DrawLine(Pens::Black, vertice->SpotCenterX, vertice->SpotCenterY, vertice->SpotCenterX, child->verticePertenece->SpotCenterY);
			gr->DrawLine(Pens::Black, vertice->SpotCenterX, child->verticePertenece->SpotCenterY, child->verticePertenece->SpotCenterX, child->verticePertenece->SpotCenterY);

			// Recursively make the child draw its subtree nodes.
			DrawSubtreeLinksVertical(gr, child->verticePertenece);
		}
	}
	
	// Draw the nodes for the subtree rooted at this node.
	void DrawSubtreeNodes(Graphics ^gr, Vertice* vertice)
	{
		// Draw this node.
		if (Orientation == Orientations::Vertical) {
			vertice->Draw(vertice->DataCenterX, vertice->DataCenterY, gr, Pens::Black, Brushes::White, Brushes::Black, gcnew System::Drawing::Font("Arial", 12), 30, -5);
		}
		else {
			vertice->Draw(vertice->DataCenterX, vertice->DataCenterY, gr, Pens::Black, Brushes::White, Brushes::Black, gcnew System::Drawing::Font("Arial", 12), 4, 15);
		}
		

		// If oriented vertically, draw the node's spot.
		if (Orientation == Arbol::Orientations::Vertical)
		{
			//System::Windows::Forms::MessageBox::Show("Vertically");
			RectangleF rect = RectangleF(
				vertice->SpotCenterX - SpotRadius, vertice->SpotCenterY - SpotRadius,
				2 * SpotRadius, 2 * SpotRadius);
			if (cantidadHijos(vertice) > 0)
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
		for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
			DrawSubtreeNodes(gr, child->verticePertenece);
		}
	}
	// Return the TreeNode at this point (or null if there isn't one there).
	
	Vertice *NodeAtPoint(Graphics ^gr, PointF target_pt, Vertice* vertice)
	{
		// See if the point is under this node.
		if (vertice->IsAtPoint(gr, gcnew System::Drawing::Font("Times New Roman", 12), PointF(vertice->DataCenterX, vertice->DataCenterY), target_pt)) return vertice;

		// See if the point is under a node in the subtree.
		for (Arista* child = vertice->listaAdy; child != nullptr; child = child->sigArista) {
			Vertice *hit_node = NodeAtPoint(gr, target_pt, child->verticePertenece);
			if (hit_node != nullptr) return hit_node;
		}

		return nullptr;
	}
};