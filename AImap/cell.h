#pragma once

#include <iostream>

class Cell {
	private:
		int id;
		int idGround;
		// int visitCounter[20];
		std::string visitCounter = "";
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
		std::string getVisitCounter(){
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
		/*void setVisitCounter(const int& visitCounterX){
			
			visitCounter[lastVisitPosition] = visitCounterX;
			System::Windows::Forms::MessageBox::Show("setting: " + visitCounter[lastVisitPosition].ToString());
			++lastVisitPosition;
		}*/
		void setVisitCounter(const std::string& visitCounterX) {
			visitCounter += "," + visitCounterX;
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
			//*visitCounter = *c.visitCounter;
			visitCounter = c.visitCounter;
			positionX = c.positionX;
			positionY = c.positionY;
			lastVisitPosition = c.lastVisitPosition;

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