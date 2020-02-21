#pragma once

class ColorClass {
	private:
		int id;
		int color[3];

	public:
		ColorClass() {
			color[0] = -1;
			color[1] = -1;
			color[2] = -1;
		}

		int getId() {
			return id;
		}
		int getColor(const int& colorX){
			return color[colorX];
		}

		void setId(const int& idX) {
			id = idX;
		}
		void setColor(const int& r, const int& g, const int& b) {
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}

};