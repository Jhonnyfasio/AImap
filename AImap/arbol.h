#pragma once
#pragma once

#include "cell.h"
#include <iostream>

class Arista;

class Vertice {
	Vertice *sigVertice;
	Arista *listaAdy;
	Cell elemento;

	friend class Arbol;
};

class Arista {
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
			ancla = nuevoVertice;
		}
		else {
			if (existeVertice(elem) == nullptr) {
				Vertice *aux;
				aux = ancla;
				while (aux->sigVertice != nullptr) {
					aux = aux->sigVertice;
				}

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
		}
		else {
			while (aux->sigArista != nullptr) {
				aux = aux->sigArista;
			}

			aux->sigArista = nuevaArista;
			nuevaArista->verticePertenece = destino;
		}
	}

	std::string mostrarListaAdyacencia() {
		Vertice *verticeAux;
		Arista *aristaAux;
		std::string cadenaListaAdy;
		std::stringstream toStr;
		
		verticeAux = ancla;

		while (verticeAux != nullptr) {
			cadenaListaAdy += verticeAux->elemento.getName();
			aristaAux = verticeAux->listaAdy;

			while (aristaAux != nullptr) {
				toStr.str("");
				if (aristaAux->sigArista == nullptr) {
					toStr << aristaAux->peso;
					cadenaListaAdy += verticeAux->elemento.getName() + ':' + toStr.str();
				}
				else {
					toStr << aristaAux->peso;
					cadenaListaAdy += verticeAux->elemento.getName() + ':' + toStr.str();
					cadenaListaAdy += '->';
				}
				aristaAux = aristaAux->sigArista;
			}

			verticeAux = verticeAux->sigVertice;
			cadenaListaAdy += '\n';
			return cadenaListaAdy;
		}
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
};