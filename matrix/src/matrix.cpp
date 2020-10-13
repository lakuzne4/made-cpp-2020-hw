#include "matrix.h"

using namespace task;


Matrix task::operator*(const double& a, const Matrix& b){
	Matrix new_matrix(b.rows,b.cols);
	for (size_t i=0; i<b.rows; ++i){
		for (size_t j = 0; j<b.cols; ++j){
			new_matrix.set(i, j, a * b[i][j]);
		}
	}

	return new_matrix;
}

std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix){
		for (size_t i = 0; i < matrix.rows; ++i) {
			for (size_t j = 0; j < matrix.cols; ++j) {
				output << matrix.get(i,j) << " ";
			}
			output << std::endl;
		}
		return output;
};

std::istream& task::operator>>(std::istream& input, Matrix& matrix){
		size_t inp_rows;
		size_t inp_cols;
		input >> inp_rows;
		input >> inp_cols;
		matrix.rows = inp_rows;
		matrix.cols = inp_cols;
		double inp_value;
		for (size_t i=0; i < inp_rows; ++i){
			for (size_t j=0; j< inp_cols; ++j) {
				input >> inp_value;
				matrix.set(i,j,inp_value);
			}
		};
};

