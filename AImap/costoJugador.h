#pragma once

#include <iostream>

class CostoJugador {
private:
	int id;
	std::string name;
	std::string idGround;
	float costo;

public:

	int getId() {
		return id;
	}
	std::string getName() {
		return name;
	}
	std::string getGroundName() {
		return idGround;
	}
	float getCosto() {
		return costo;
	}

	void setId(const int& idX) {
		id = idX;
	}
	void setName(const std::string& nameX) {
		name = nameX;
	}
	void setGroundName(const std::string& idGroundX) {
		idGround = idGroundX;
	}
	void setCosto(const float& costoX) {
		costo = costoX;
	}

	CostoJugador& operator =(const CostoJugador& c) {
		id = c.id;
		name = c.name;
		idGround = c.idGround;
		//*visitCounter = *c.visitCounter;
		costo = c.costo;
		return *this;
	}

	bool operator == (const CostoJugador& c) {
		return (name == c.name && idGround == c.idGround);
	}

	bool operator != (const CostoJugador& c) {
		return (name != c.name && idGround != c.idGround);
	}

	bool operator < (const CostoJugador& c) {
		return (name < c.name && idGround < c.idGround);
	}

	bool operator > (const CostoJugador& c) {
		return (name > c.name && idGround > c.idGround);
	}

	bool operator <= (const CostoJugador& c) {
		return (name <= c.name && idGround <= c.idGround);
	}

	bool operator >= (const CostoJugador& c) {
		return (name >= c.name && idGround >= c.idGround);
	}

	bool operator [](const CostoJugador& c) {

	}
};