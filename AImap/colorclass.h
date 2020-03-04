#pragma once

class ColorClass {
	private:
		int id;
		std::string name;
		int color[3];


	public:
		ColorClass() {
			id = -1;
			color[0] = -1;
			color[1] = -1;
			color[2] = -1;
			name = "";
		}

		int getId() {
			return id;
		}
		int getColor(const int& colorX) {
			return color[colorX];
		}

		std::string getName() {
			return name;
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setColor(const int r, const int g, const int b) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}

		void setName(const std::string& nameX) {
			name = nameX;
		}

		ColorClass& operator = (const ColorClass& c) {
			id = c.id;
			color[0] = c.color[0];
			color[1] = c.color[1];
			color[2] = c.color[2];
			name = c.name;
			return *this;
		}

		bool operator == (const ColorClass& c) {
			return name == c.name;
		}

		bool operator != (const ColorClass& c) {
			return name != c.name;
		}

		bool operator < (const ColorClass& c) {
			return name < c.name;
		}

		bool operator > (const ColorClass& c) {
			return name > c.name;
		}

		bool operator <= (const ColorClass& c) {
			return name <= c.name;
		}

		bool operator >= (const ColorClass& c) {
			return name >= c.name;
		}
};