#include <misc.h>

bool test_linspace() {

	// using the linspace function
	std::vector<int> int_lin0 = linspace<int>(-5, 5, 11);
	std::vector<int> int_lin1 = linspace<int>(-5, 5, 1);
	std::vector<int> int_lin2 = linspace<int>(-5, 5, 2);
	std::vector<int> int_lin3 = linspace<int>(-1, 1, 3);

	std::vector<unsigned int> uint_lin0 = linspace<unsigned int>(0, 1, 3);

	std::vector<float> float_lin0 = linspace<float>(-1, 1, 3);
	std::vector<float> float_lin1 = linspace<float>(-1, 1, 1);
	std::vector<float> float_lin2 = linspace<float>(-1, 1, 2);

	std::vector<double> double_lin0 = linspace<double>(-1, 1, 3);
	std::vector<double> double_lin1 = linspace<double>(0, 5, 6);
	std::vector<double> double_lin2 = linspace<double>(0, 5, 1);
	std::vector<double> double_lin3 = linspace<double>(0, 5, 2);
	
	// manually, to compare
	std::vector<int> int_lin0_m = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };
	std::vector<int> int_lin1_m = { -5 };
	std::vector<int> int_lin2_m = { -5, 5 };
	std::vector<int> int_lin3_m = { -1, 0, 1 };

	std::vector<unsigned int> uint_lin0_m = { 0, 0, 1 };

	std::vector<float> float_lin0_m = { -1, 0, 1 };
	std::vector<float> float_lin1_m = { -1 };
	std::vector<float> float_lin2_m = { -1, 1 };

	std::vector<double> double_lin0_m = { -1, 0, 1 };
	std::vector<double> double_lin1_m = { 0, 1, 2, 3, 4, 5 };
	std::vector<double> double_lin2_m = { 0 };
	std::vector<double> double_lin3_m = { 0, 5 };

	if (!(int_lin0 == int_lin0_m)) { return false; }
	if (!(int_lin1 == int_lin1_m)) { return false; }
	if (!(int_lin2 == int_lin2_m)) { return false; }
	if (!(int_lin3 == int_lin3_m)) { return false; }

	if (!(uint_lin0 == uint_lin0_m)) { return false; }

	if (!(float_lin0 == float_lin0_m)) { return false; }
	if (!(float_lin1 == float_lin1_m)) { return false; }
	if (!(float_lin2 == float_lin2_m)) { return false; }

	if (!(double_lin0 == double_lin0_m)) { return false; }
	if (!(double_lin1 == double_lin1_m)) { return false; }
	if (!(double_lin2 == double_lin2_m)) { return false; }
	if (!(double_lin3 == double_lin3_m)) { return false; }

	return true;
}

int main() {
	if (test_linspace()) {return 0;}
	return 1;
}