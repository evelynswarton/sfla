#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <random>

using std::cout;
using std::endl;
using std::setw;
using std::max;
using std::cin;

Matrix::Matrix(unsigned m_numRows, unsigned m_numCols, double initialValue) {
	this->m_numRows = m_numRows;
	this->m_numCols = m_numCols;
	m_matrix.resize(m_numRows);
	for (unsigned i = 0; i < m_numRows; i++) {
		m_matrix[i].resize(m_numCols, initialValue);
	}
}

Matrix::Matrix(unsigned numRows, unsigned numCols, string type) {
	string input = "";
	m_numRows = numRows;
	m_numCols = numCols;
	m_matrix.resize(m_numRows);
	for (unsigned i = 0; i < m_numRows; i++) {
		m_matrix[i].resize(m_numCols, 0);
	}
	if (type == "man") { // manually enter values
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				cout << i << " " << j << " : ";
				getline(cin, input);
				m_matrix[i][j] = stod(input);
				print();
			}
		}
	} else if (type == "id") { // identity matrix
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				m_matrix[i][j] = (i == j);
			}
		}
	} else if (type == "rand") { // random value matrix
		srand(time(NULL));
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				m_matrix[i][j] = 1.0 / ((float)rand() / (float)RAND_MAX);
			}
		}
	} else if (type == "ones") {
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				m_matrix[i][j] = 1.0f;
			}
		}
	} else if (type == "zeros") {
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				m_matrix[i][j] = 0.0f;
			}
		}
	} else {
		throw("Matrix: invalid constructor flag");
	}
}

Matrix::Matrix(unsigned numRows, unsigned numCols, vector<double> values) {
	if ((numRows * numCols) != values.size()) {
		cout << "ERROR: called constructor that accepts vector: vector passed was of incorrect length" << endl;
		throw("Constructor recieved vector of incorrect length (should be n by m)");
	} else {
		m_numRows = numRows;
		m_numCols = numCols;
		unsigned k = 0;
		m_matrix.resize(m_numRows);
		for (unsigned i = 0; i < m_numRows; i++) {
			m_matrix[i].resize(m_numCols);
			for (unsigned j = 0; j < m_numCols; j++) {
				m_matrix[i][j] = values[k];
				k++;
			}
		}
	}
}

Matrix::Matrix(const Matrix &A) {
	m_numRows = A.m_numRows;
	m_numCols = A.m_numCols;
	m_matrix = A.m_matrix;
}

// Subscript operator
vector<double> Matrix::operator[](unsigned i) {
	return m_matrix[i];
}

// Assignment
Matrix Matrix::operator=(const Matrix &A) {
	m_numRows = A.m_numRows;
	m_numCols = A.m_numCols;
	m_matrix = A.m_matrix;
	return *this;
}

// Scalar addition
Matrix Matrix::operator+(double _c_) {
	for (unsigned i = 0; i < m_numRows; i++) {
		for (unsigned j = 0; j < m_numCols; j++) {
			m_matrix[i][j] += _c_;
		}
	}
	return *this;
}

// Scalar subtraction
Matrix Matrix::operator-(double _c_) {
	for (unsigned i = 0; i < m_numRows; i++) {
		for (unsigned j = 0; j < m_numCols; j++) {
			m_matrix[i][j] -= _c_;
		}
	}
	return *this;
}

// Scalar multiplication
Matrix Matrix::operator*(double _c_) {
	for (unsigned i = 0; i < m_numRows; i++) {
		for (unsigned j = 0; j < m_numCols; j++) {
			m_matrix[i][j] *= _c_;
		}
	}
	return *this;
}

// Scalar division
Matrix Matrix::operator/(double _c_) {
	for (unsigned i = 0; i < m_numRows; i++) {
		for (unsigned j = 0; j < m_numCols; j++) {
			m_matrix[i][j] /= _c_;
		}
	}
	return *this;
}

// Entrywise addition
Matrix Matrix::operator+(const Matrix &A) {
	if (m_numRows != A.m_numRows || m_numCols != A.m_numCols) {
		cout << "ERROR: matrix addition of invalid dimension" << endl;
		throw("Matrix addition invalid dimension");
	} else {
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				if (i < A.m_numRows && j < A.m_numCols) {
					m_matrix[i][j] += A.m_matrix[i][j];
				}
			}
		}
	}
	return *this;
}

// Entrywise subtraction
Matrix Matrix::operator-(const Matrix &A) {
	if (m_numRows != A.m_numRows || m_numCols != A.m_numCols) {
		cout << "ERROR: matrix subtraction of invalid dimension" << endl;
		throw("Matrix subtraction invalid dimension");
	} else {
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				if (i < A.m_numRows && j < A.m_numCols) {
					m_matrix[i][j] -= A.m_matrix[i][j];
				}
			}
		}
	}
	return *this;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix &A) {
	if (m_numCols != A.m_numRows) {
		cout << "ERROR: matrix multiplication of invalid dimension" << endl;
		throw("Matrix multiplication: invalid dimensions");
	} else {
		unsigned p = m_numCols;
		vector< vector<double> > result (m_numRows, vector<double> (A.m_numCols, 0));
		for (unsigned i = 0; i < result.size(); i++) {
			for (unsigned j = 0; j < result[0].size(); j++) {
				for (unsigned k = 0; k < p; k++) {
					result[i][j] += (m_matrix[i][k] * A.m_matrix[k][j]); 
				}
			}
		}
		m_numCols = A.m_numCols;
		m_matrix = result;
	}
	return *this;
}

// Determinant
float Matrix::determinant() {
	float det = 0;
	if (m_numCols != m_numRows) {
		cout << "ERROR: determinant invalid dimension" << endl;
		throw("Matrix determinant: invalid dimensions");
	} else {
		// Calculate the determinant
		if (m_numRows == 2) {
			det = (m_matrix[0][0] * m_matrix[1][1]) - (m_matrix[0][1] * m_matrix[1][0]); 
		} else {
			for (unsigned j = 0; j < m_numCols; j++) {
				Matrix submatrix = *this;
				submatrix.removeRowAt(0);
				submatrix.removeColAt(j);
				if (j % 2 == 0) {
					det += m_matrix[0][j] * submatrix.determinant();
				} else {
					det -= m_matrix[0][j] * submatrix.determinant();
				}
			}
		}
	}
	return det;
}

// Transpose
void Matrix::transpose() {
	vector< vector<double> > result (m_numCols, vector<double> (m_numRows, 0));
	for (unsigned i = 0; i < m_numRows; i++) {
		for (unsigned j = 0; j < m_numCols; j++) {
			result[j][i] = m_matrix[i][j];
		}
	}
	m_matrix = result;
	unsigned swap = m_numRows;
	m_numRows = m_numCols;
	m_numCols = swap;
}

// Entrywise multiplication
void Matrix::hadamardProduct(const Matrix &A) {
	if (m_numRows != A.m_numRows || m_numCols != A.m_numCols) {
		cout << "error: hadamard mult. attempted on matrix of unequal dim" << endl;
		throw("dimension error");
	} else {
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				m_matrix[i][j] *= A.m_matrix[i][j];
			}
		}
	}
}

// Kronecker product
void Matrix::kroeneckerProduct(const Matrix &A) {
	Matrix result(0, A.m_numCols * m_numCols, 0);
	for (unsigned i = 0; i < m_numRows; i++) {
		Matrix row(A.m_numRows, 0, 0);
		for (unsigned j = 0; j < m_numCols; j++) {
			Matrix B = A;
			row.appendRight(B * m_matrix[i][j]);
		}
		result.appendBottom(row);
	}
	m_numRows *= A.m_numRows;
	m_numCols *= A.m_numCols;
	m_matrix = result.m_matrix;
}

// Golub and Kahan - 1970
void Matrix::QR(Matrix& Q, Matrix &R) {
	R = this;
	for (unsigned j = 0; j < R.m_numCols; j++) {
		// Find H = I - c*w*w'
		// Get R[j:m,j]
		double normx = 
		int s = (R[j][j] >= 0) ? -1 : 1;
		double u1 = R[j][j] - (s * normx);
		vector<double> w = R.slice("j:m,j") / u1;
		w[1] = 1;
		doulbe tau = -s * u1 / normx;
	}
}

void Matrix::appendLeft(const Matrix &A) {
	if (m_numRows != A.m_numRows) {
		cout << "ERROR: append left - invalid dimensions" << endl;
		throw ("append dimension error");
	} else {
		Matrix result(m_numRows, m_numCols + A.m_numCols, 0);
		// Copy current matrix in on right
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				result.m_matrix[i][j + A.m_numRows] = m_matrix[i][j];
			}
		}
		// Copy other matrix in on left
		for (unsigned i = 0; i < A.m_numRows; i++) {
			for (unsigned j = 0; j < A.m_numCols; j++) {
				result.m_matrix[i][j] = A.m_matrix[i][j];
			}
		}
		m_numCols += A.m_numCols;
		m_matrix = result.m_matrix;
	}
}

void Matrix::appendRight(const Matrix &A) {
	if (m_numRows != A.m_numRows) {
		cout << "ERROR: append right - invalid dimensions" << endl;
		throw ("append dimension error");
	} else {
		Matrix result(m_numRows, m_numCols + A.m_numCols, 0);
		// Copy current matrix in on left
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				result.m_matrix[i][j] = m_matrix[i][j];
			}
		}
		// Copy other matrix in on right
		for (unsigned i = 0; i < A.m_numRows; i++) {
			for (unsigned j = 0; j < A.m_numCols; j++) {
				result.m_matrix[i][j + m_numCols] = A.m_matrix[i][j];
			}
		}
		m_numCols += A.m_numCols;
		m_matrix = result.m_matrix;
	}
}

void Matrix::appendTop(const Matrix &A) {
	if (m_numCols != A.m_numCols) {
		cout << "ERROR: append top - invalid dimensions" << endl;
		throw ("append dimension error");
	} else {
		Matrix result(m_numRows + A.m_numRows, m_numCols, 0);
		// Copy current matrix on bottom
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				result.m_matrix[i + A.m_numRows][j] = m_matrix[i][j];
			}
		}
		// Copy other matrix on top
		for (unsigned i = 0; i < A.m_numRows; i++) {
			for (unsigned j = 0; j < A.m_numCols; j++) {
				result.m_matrix[i][j] = A.m_matrix[i][j];
			}
		}
		m_numRows += A.m_numRows;
		m_matrix = result.m_matrix;
	}
}

void Matrix::appendBottom(const Matrix &A) {
	if (m_numCols != A.m_numCols) {
		cout << "ERROR: append bottom - invalid dimensions" << endl;
		throw ("append dimension error");
	} else {
		Matrix result(m_numRows + A.m_numRows, m_numCols, 0);
		// Copy current matrix on bottom
		for (unsigned i = 0; i < m_numRows; i++) {
			for (unsigned j = 0; j < m_numCols; j++) {
				result.m_matrix[i][j] = m_matrix[i][j];
			}
		}
		// Copy other matrix on top
		for (unsigned i = 0; i < A.m_numRows; i++) {
			for (unsigned j = 0; j < A.m_numCols; j++) {
				result.m_matrix[i + m_numRows][j] = A.m_matrix[i][j];
			}
		}
		m_numRows += A.m_numRows;
		m_matrix = result.m_matrix;
	}
}

void Matrix::print() const {
	for (unsigned i = 0; i < m_numRows; i++) {
		cout << "[ ";
		for (unsigned j = 0; j < m_numCols; j++) {
			cout << setw(9) << m_matrix[i][j];
			(j == m_numCols - 1) ? cout << "" : cout << ",";
		}
		cout << "]";
		cout << endl;
	}
}

double Matrix::getValueAt(unsigned i, unsigned j) const {
	return m_matrix[i][j];
}

Matrix Matrix::removeRowAt(unsigned i) {
	if (i >= m_numRows) {
		cout << "error; out of range" << endl;
	} else {
		m_matrix.erase(m_matrix.begin() + i);
		m_numRows--;
	}
	return *this;
}

Matrix Matrix::removeColAt(unsigned j) {
	if (j >= m_numCols) {
		cout << "error; out of range" << endl;
	} else {
		for (unsigned i = 0; i < m_numRows; i++) {
			m_matrix[i].erase(m_matrix[i].begin() + j);
		}
		m_numCols--;
	}
	return *this;
}

