#include <misc.h>

void draw_bool_matrix(const std::vector<std::vector<bool>>& matrix) {
	if ((matrix[0].size() > 0) && (matrix[1].size() > 0)) {
		for (unsigned int i = 0; i < matrix[0].size(); i++) {
			for (unsigned int j = 0; j < matrix[1].size(); j++) {
				if (matrix[i][j]) { std::cout << "."; }
				else { std::cout << " "; }
			}
			std::cout << "\n";
		}
	}
	else {
		std::cout << "Null matrix\n";
	}
}