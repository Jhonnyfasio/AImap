#pragma once

#include <iostream>

class Player {
	private:
		int id;
		std::string name;
		
	public:
		int getId() {
			return id;
		}
		std::string getName() {
			return name;
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setName(const std::string& nameX) {
			name = nameX;
		}

		Player& operator =(const Player& c) {
			id = c.id;
			name = c.name;

			return *this;
		}

		bool operator == (const Player& c) {
			return id == c.id;
		}

		bool operator != (const Player& c) {
			return id != c.id;
		}

		bool operator < (const Player& c) {
			return id < c.id;
		}

		bool operator > (const Player& c) {
			return id > c.id;
		}

		bool operator <= (const Player& c) {
			return id <= c.id;
		}

		bool operator >= (const Player& c) {
			return id >= c.id;
		}

		bool operator [](const Player& c) {

		}
};