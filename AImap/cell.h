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
};