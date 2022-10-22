#pragma once

#include <vector>
#include <assert.h>
#include <iostream>

template <typename T>
std::vector<T> linspace(const T& start, const T& end, const unsigned int& size) {
	std::vector<T> returned_vector;
	
	assert(size != 0);
	
	if (size == 1) {
		returned_vector.push_back(static_cast<T>(start));
	}
	else {
		const double step = (end - start) / (size - 1);
		for (unsigned int i = 0; i < size - 1; i++) {
			returned_vector.push_back(static_cast<T>(start + step * i));
		}
		returned_vector.push_back(static_cast<T>(end));
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
	if (if ((matrix[0].size() > 0) && (matrix[1].size() > 0))) {
		for (unsigned int i = 0; i < matrix[0].size(); i++) {
			print_std_vector(matrix[i]);
		}
	}
	else {
		std::cout << "Null matrix\n";
	}
}

void draw_bool_matrix(const std::vector<std::vector<bool>>& matrix);