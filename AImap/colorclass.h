#pragma once

class ColorClass {
	private:
		int id;
		int color[3];
		float value;
		std::string groundName;


	public:
		ColorClass() {
			id = -1;
			color[0] = -1;
			color[1] = -1;
			color[2] = -1;
			groundName = "";
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

		std::string getGroundName() {
			return groundName;
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setColor(const int& r, const int& g, const int& b) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}

		void setValue(const float& valueX) {
			value = valueX;
		}

		void setGroundName(const std::string& groundNameX) {
			groundName = groundNameX;
		}

		ColorClass& operator = (const ColorClass& c) {
			id = c.id;
			color[0] = c.color[0];
			color[1] = c.color[1];
			color[2] = c.color[2];
			value = c.value;
			groundName = c.groundName;
			return *this;
		}
		
		bool operator == (const ColorClass& c) {
			return id == c.id;
		}

		bool operator != (const ColorClass& c) {
			return id != c.id;
		}

		bool operator < (const ColorClass& c) {
			return id < c.id;
		}

		bool operator > (const ColorClass& c) {
			return id > c.id;
		}

		bool operator <= (const ColorClass& c) {
			return id <= c.id;
		}

		bool operator >= (const ColorClass& c) {
			return id >= c.id;
		}
};