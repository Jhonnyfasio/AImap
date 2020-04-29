#pragma once
#pragma once

#include "cell.h"
#include <iostream>

class Arista;

class Vertice {
public:
	Vertice *sigVertice;
	Arista *listaAdy;
	Cell elemento;
	int nivel = -1;

	friend class Arbol;
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

public:
	Arbol() {
		Inicializa();
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


};