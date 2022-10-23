#pragma once

#include <vector>
#include <assert.h>
#include <iostream>

template <typename T>
std::vector<T> linspace(const T& min, const T& max, const unsigned int& size) {
	std::vector<T> returned_vector;
	
	assert(size > 0);
	assert(min < max);
	
	if (size == 1) {
		returned_vector.push_back(static_cast<T>(min));
	}
	else {
		const double step = (max - min) / (size - 1);
		for (unsigned int i = 0; i < size - 1; i++) {
			returned_vector.push_back(static_cast<T>(min + step * i));
		}
		returned_vector.push_back(static_cast<T>(max));
	}
	return returned_vector;
}

template <typename T>
void print_std_vector(const std::vector<T> &vector) {
	if (vector.size() > 0) {
		for (unsigned int i = 0; i < vector.size(); i++) {
				std::cout << vector[i] << " | ";
			}
			std::cout << "\n";
	}
	else {
		std::cout << "Null vector \n";
	}
}

template <typename T>
void print_matrix(const std::vector < std::vector<T>> & matrix) {
	if ( (matrix.size() > 0) && (matrix[0].size() > 0)) {
		for (unsigned int i = 0; i < matrix.size(); i++) {
			print_std_vector(matrix[i]);
		}
	}
	else {
		std::cout << "Null matrix\n";
	}
}

void draw_bool_matrix(const std::vector<std::vector<bool>>& matrix);