#pragma once

#include <iostream>

class Cell {
	private:
		int id;
		int idGround;
		int visitCounter[20];
		int positionX;
		int positionY;
		int lastVisitPosition = 0;

	public:

		int getId() {
			return id;
		}
		int getIdGround(){
			return idGround;
		}
		int* getVisitCounter(){
			return visitCounter;
		}

		int getPositionX() {
			return positionX;
		}

		int getPositionY() {
			return positionY;
		}

		int getLastVisitPosition() {
			return lastVisitPosition;
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setIdGround(const int& idGroundX){
			idGround = idGroundX;
		}
		void setVisitCounter(const int& visitCounderX){
			visitCounter[lastVisitPosition] = visitCounderX;
			lastVisitPosition++;
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
			*visitCounter = *c.visitCounter;
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