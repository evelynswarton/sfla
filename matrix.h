/* --------------------------------------
 *           MATRIX LIBRARY
 *    Author: Evelyn Warton
 *    Purpose: Research in spectral graph
 *        graph theory
 *    Date: 05/04/2020
 * -------------------------------------*/

#ifndef MATRIX_H
#define MATRIX_H

#include<vector>
#include<string>

using std::vector;
using std::string;

class Matrix {
    private:
        unsigned m_numRows;
        unsigned m_numCols;
        vector< vector<double> > m_matrix;

    public:
        /* --- CONSTRUCTORS --- */
        Matrix(unsigned, unsigned, double); // Constructor
        Matrix(unsigned, unsigned, string);
        Matrix(unsigned, unsigned, vector<double>);
        Matrix(const Matrix &); // Copy constructor

        /* --- ASSIGNMENT AND INDEX OPERATORS --- */
		vector<double> operator[](unsigned);
        Matrix operator=(const Matrix &); // Assignment operator overload

        /* --- SCALING ALGEBRA OPERATORS --- */
        Matrix operator+(double);
        Matrix operator-(double);
        Matrix operator*(double);
        Matrix operator/(double);

        /* --- MATRIX ALGEBRA OPERATORS --- */
        Matrix operator+(const Matrix &);
        Matrix operator-(const Matrix &);
        Matrix operator*(const Matrix &);

        /* --- MATRIX CALCULATIONS --- */
        void transpose();
        float determinant();
        void hadamardProduct(const Matrix &); 
        void kroeneckerProduct(const Matrix &); 
		vector<Matrix> SVD();

        /* --- DEBUGGING --- */
        void print() const;
        double getValueAt(unsigned i, unsigned j) const;

        /* --- BASIC MANIPULATION --- */
        Matrix removeRowAt(unsigned);
        Matrix removeColAt(unsigned);

		void appendLeft(const Matrix &);
		void appendRight(const Matrix &);
		void appendTop(const Matrix &);
		void appendBottom(const Matrix &);
};

#endif
