#pragma once

#include <vector>
#include <iostream>


namespace task {

const double EPS = 1e-6;


class OutOfBoundsException : public std::exception {};
class SizeMismatchException : public std::exception {};

class ProxyClass {
public:
	double* some_data=nullptr;
	
	ProxyClass(double* input_some_data){
		some_data = &(input_some_data[0]);
	};
	
	~ProxyClass(){
		if (some_data!=nullptr){
			delete[] some_data;
		}
	};
	
	double& operator[](size_t idx){
		return *(some_data + idx);
	};
};

class Matrix {

	double* matrix_data = nullptr;

public:
	size_t rows;
	size_t cols;

    Matrix(){
		rows = 1;
		cols = 1;
		matrix_data = new double[1];
		*matrix_data = 1;
	};
	
    Matrix(size_t rows, size_t cols){
		this->rows = rows;
		this->cols = cols;
		matrix_data = new double[rows * cols];
		
		for (size_t i = 0; i<rows ; ++ i ) {
			for (size_t j = 0; j < cols; ++ j) {
				if (i==j) *(matrix_data + i * cols + j ) = 1.;
				else *(matrix_data + i * cols + j )  = 0.;
			}
		};
	};
	
	~Matrix(){
		if (matrix_data != nullptr) {
			delete[] matrix_data;
		};
	}
	
    Matrix(const Matrix& copy){
		rows = copy.rows;
		cols = copy.cols;
		
		matrix_data = new double[rows * cols];
		
		for (size_t i = 0; i< rows * cols; ++i) {
			*(matrix_data + i) = *(copy.matrix_data + i);
		}
	};
    Matrix& operator=(const Matrix& a){
		
		if (this != &a)
		{
			
			rows = a.rows;
			cols = a.cols;
			
			double* new_matrix_data = new double[rows * cols];
			for (size_t i = 0; i < rows * cols; ++i) {
				*(new_matrix_data + i) = *(a.matrix_data + i);
			}; 
			
			delete[] matrix_data;
			matrix_data = new_matrix_data;
			;
		}
		
		return *this;
	};

    double& get(size_t row, size_t col){
		return *(matrix_data + cols * row + col);	
	};
    const double& get(size_t row, size_t col) const{
		const double* result = (matrix_data + cols * row + col);
		return *result;
	};
    void set(size_t row, size_t col, const double& value){
		*(matrix_data + cols * row + col) = value;
	};
    void resize(size_t new_rows, size_t new_cols){
		rows = new_rows;
		cols = new_cols;
	};

    ProxyClass operator[](size_t row){
		return ProxyClass((matrix_data + row * cols));
	};
    ProxyClass operator[](size_t row) const{
		return ProxyClass((matrix_data + row * cols));
	};

    Matrix& operator+=(const Matrix& a){
		for (size_t i=0; i< rows * cols; ++i) {
				*(matrix_data + i)= *(matrix_data + i) + *(a.matrix_data + i );
		}
		return *this;
	};
    Matrix& operator-=(const Matrix& a){
		for (size_t i=0; i< rows * cols; ++i) {
				*(matrix_data + i)= *(matrix_data + i) - *(a.matrix_data + i );
		}
		return *this;
	};
    Matrix& operator*=(const Matrix& a){
		for (size_t i=0; i< rows * cols; ++i) {
				*(matrix_data + i)= (*(matrix_data + i)) * (*(a.matrix_data + i ));
		}
		return *this;
	};
    Matrix& operator*=(const double& number){
		for (size_t i=0; i< rows * cols; ++i) {
				*(matrix_data + i)= (*(matrix_data + i)) * number;
		}
		return *this;
	};

    Matrix operator+(const Matrix& a) const{
		Matrix result_matrix(rows,cols);
		for (size_t i=0; i< rows * cols; ++i) {
				*(result_matrix.matrix_data + i)= *(matrix_data + i) + *(a.matrix_data + i );
		}
		return result_matrix;
	};
    Matrix operator-(const Matrix& a) const{
		Matrix result_matrix(rows,cols);
		for (size_t i=0; i< rows * cols; ++i) {
				*(result_matrix.matrix_data + i)= *(matrix_data + i) - *(a.matrix_data + i );
		}
		return result_matrix;
	};
    Matrix operator*(const Matrix& a) const{
		Matrix result_matrix(rows,cols);
		for (size_t i=0; i< rows * cols; ++i) {
				*(result_matrix.matrix_data + i)= *(matrix_data + i) * *(a.matrix_data + i );
		}
		return result_matrix;
	};
    Matrix operator*(const double& a) const{
		Matrix result_matrix(rows,cols);
		for (size_t i=0; i< rows * cols; ++i) {
				*(result_matrix.matrix_data + i)= *(matrix_data + i) * a;
		}
		return result_matrix;
	};

    Matrix operator-() const{
		Matrix result_matrix(rows,cols);
		for (size_t i=0; i< rows * cols; ++i) {
				*(result_matrix.matrix_data + i)= -(*(matrix_data + i));
		}
		
		return result_matrix;
	};
    Matrix operator+() const{
		Matrix result_matrix(rows,cols);
		for (size_t i=0; i< rows * cols; ++i) {
				*(result_matrix.matrix_data + i)= +(*(matrix_data + i));
		}
		
		return result_matrix;
	};

    double det() const{
		double det = 0;
		if ((rows == 2) && (cols == 2)) {
			return this->get(0,0) * this->get(1,1) - this->get(0,1) * this->get(1,0);
			}
		else {
			
			Matrix submatrix(rows - 1, cols - 1);
			
			for (int main_ind = 0; main_ind < cols; main_ind++){
				int sub_i =0;
				for (int i = 1; i < rows ; ++i){
					int sub_j = 0;
					for (int j = 0; j < cols; j++) {
						if (j == main_ind)
							continue;
						submatrix.set(sub_i,sub_j,this->get(i,j));
						sub_j ++;
					}
				sub_i ++;
				}
			int odd_index = (main_ind % 2 == 0) ? 1 : - 1;
			det = det + odd_index * this->get(0, main_ind) * submatrix.det();
			
			}
		}
		return det;
	};
    void transpose(){
		size_t tmp = rows;
		rows = cols;
		cols = tmp;
	};
    Matrix transposed() const{
		Matrix transposed_matrix(cols,rows);
		return transposed_matrix;
	};
    double trace() const {
		double trace_ = 0;
		for (size_t i = 0 ; i < rows ; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				if (i==j) trace_ += this->get(i,j);
			}
		}
		return trace_;
	};

    std::vector<double> getRow(size_t row){
		std::vector<double> result;
		for (size_t j =0 ; j < this->cols ; ++ j){
				result.push_back(*(matrix_data + cols * row + j));
			}
		return result;
	};
    std::vector<double> getColumn(size_t column){
		std::vector<double> result;
		for (size_t i = 0; i < rows ; ++i) {
			result.push_back(*(matrix_data + cols * i + column));
		}
		return result;
	};

    bool operator==(const Matrix& a) const{
		for (size_t i=0; i< this->rows; ++i){
			for (size_t j=0; j< this->cols; ++j){
				if (this->get(i,j) - a.get(i,j) > EPS ) return (bool) false;
				
			}
		}
		return true;
	};
    bool operator!=(const Matrix& a) const{
		return !(*this == a);
	};



};


Matrix operator*(const double& a, const Matrix& b);

std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
std::istream& operator>>(std::istream& input, Matrix& matrix);



}  // namespace task


