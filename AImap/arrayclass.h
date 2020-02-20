#pragma once

template <class T, class U> class ArrayClass {
private:
	T row;
	T column;
	T value;
	T size = 0;
	U cell;

public:
	T getRow() {
		return row;
	}

	T getColumn() {
		return column;
	}

	T getValue() {
		return value;
	}

	T getSize() {
		return size;
	}

	U getCell() {
		return cell;
	}

	void setRow(T rowX) {
		row = rowX;
	}

	void setColumn(T columnX){
		column = columnX;
	}
		
	void setValue(T valueX){
		value = valueX;
	}

	void setSize(T& sizeX){
		size = sizeX;
	}

	void setCell(U& cellX) {
		cell = cellX;
	}
};