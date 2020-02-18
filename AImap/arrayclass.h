#pragma once

#include <iostream>


template <class T> class ArrayClass {
private:
	T row;
	T column;
	T value;
	T size = 0;

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
};