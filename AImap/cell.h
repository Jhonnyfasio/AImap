#pragma once

#include <iostream>

class Cell {
	private:
		int id;
		int idGround;
		int visitCounter;
		int positionX;
		int positionY;

	public:
		int getId() {
			return id;
		}
		int getIdGround(){
			return idGround;
		}
		int getVisitCounter(){
			return visitCounter;
		}

		int getPositionX() {
			return positionX;
		}

		int getPositionY() {
			return positionY;
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setIdGround(const int& idGroundX){
			idGround = idGroundX;
		}
		void setVisitCounter(const int& visitCounderX){
			visitCounter = visitCounderX;
		}

		void setPositionX(const int& positionXX) {
			positionX = positionXX;
		}

		void setPositionY(const int& positionYY) {
			positionY = positionYY;
		}

		Cell& operator =(const Cell& c){
			id = c.id;
			idGround = c.idGround;
			visitCounter = c.visitCounter;
			positionX = c.positionX;
			positionY = c.positionY;

			return *this;
		}

		bool operator == (const Cell& c) {
			return id == c.id;
		}

		bool operator != (const Cell& c) {
			return id != c.id;
		}

		bool operator < (const Cell& c) {
			return id < c.id;
		}

		bool operator > (const Cell& c) {
			return id > c.id;
		}

		bool operator <= (const Cell& c) {
			return id <= c.id;
		}

		bool operator >= (const Cell& c) {
			return id >= c.id;
		}

		bool operator [](const Cell& c){

		}
};