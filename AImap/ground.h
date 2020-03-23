#pragma once

#include <iostream>

class Ground {
	private:
		int id;
		int color[3];
		float value;
		std::string name;
		bool isValid;


	public:
		Ground() {
			id = -1;
			color[0] = -1;
			color[1] = -1;
			color[2] = -1;
			name = "";
			value = -1;
		}

		int getId() {
			return id;
		}
		int getColor(const int& colorX){
			return color[colorX];
		}

		float getValue() {
			return value;
		}
		std::string getName() {
			return name;
		}
		bool getIsValid() {
			return isValid;
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setColor(const int r, const int g, const int b) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}

		void setValue(const float& valueX) {
			value = valueX;
		}
		void setName(const std::string& nameX) {
			name = nameX;
		}
		void setIsValid(const bool isValidX) {
			isValid = isValidX;
		}

		Ground& operator = (const Ground& c) {
			id = c.id;
			color[0] = c.color[0];
			color[1] = c.color[1];
			color[2] = c.color[2];
			value = c.value;
			name = c.name;
			isValid = c.isValid;
			return *this;
		}
		
		bool operator == (const Ground& c) {
			return id == c.id;
		}

		bool operator != (const Ground& c) {
			return id != c.id;
		}

		bool operator < (const Ground& c) {
			return id < c.id;
		}

		bool operator > (const Ground& c) {
			return id > c.id;
		}

		bool operator <= (const Ground& c) {
			return id <= c.id;
		}

		bool operator >= (const Ground& c) {
			return id >= c.id;
		}
};