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
		float price;
		bool isKnown = false;
		bool isGoal = false;
		bool isStart = false;

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
		bool getIsKnown() {
			return isKnown;
		}
		bool getIsStart() {
			return isStart;
		}
		bool getIsGoal() {
			return isGoal;
		}
		float getPrice() {
			return price;
		}
		std::string getName() {
			std::stringstream toStr;
			std::string str;
			str.push_back('A' + positionX);
			toStr << (positionY+1);
			str ="("+str+ "," + toStr.str()+")";
			return str;
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
		void eraseVisitCounter() {
			visitCounter = "";
		}

		void setPositionX(const int& positionXX) {
			positionX = positionXX;
		}

		void setPositionY(const int& positionYY) {
			positionY = positionYY;
		}

		void setIsKnown(const bool& isKnownX) {
			isKnown = isKnownX;
		}
		void setIsStart(const bool& isStartX) {
			isStart = isStartX;
		}
		void setIsGoal(const bool& isGoalX) {
			isGoal = isGoalX;
		}
		void setPrice(const float& priceX) {
			price = priceX;
		}

		Cell& operator =(const Cell& c){
			id = c.id;
			idGround = c.idGround;
			//*visitCounter = *c.visitCounter;
			visitCounter = c.visitCounter;
			positionX = c.positionX;
			positionY = c.positionY;
			lastVisitPosition = c.lastVisitPosition;
			isKnown = c.isKnown;
			isStart = c.isStart;
			isGoal = c.isGoal;
			price = c.price;
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