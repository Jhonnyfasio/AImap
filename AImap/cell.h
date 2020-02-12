#pragma once

#include <iostream>

class Cell {
	private:
		int id;
		int idGround;
		int visitCounter;

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

		void setId(const int& idX) {
			id = idX;
		}
		void setIdGround(const int& idGroundX){
			idGround = idGroundX;
		}
		void setVisitCounter(const int& visitCounderX){
			visitCounter = visitCounderX;
		}
};