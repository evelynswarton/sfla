#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <complex.h>


/* TODO: number class
 * vctr_complex
 * vctr_real
 * vctr_integer
 * vctr_bool
 */

typedef struct {
	int rows;
	int cols;
	double complex* data;
} mtrx;

mtrx* mtrx_alloc(int rows, int cols) {
	mtrx* M = malloc(sizeof(mtrx));
	M->rows = rows;
	M->cols = cols;
	M->data = malloc(rows * cols * sizeof(double complex));
	return M;
}

void mtrx_free(mtrx* M) {
	free(M->data);
	free(M);
}

void mtrx_fill(mtrx* M, double complex value) {
	for (int i = 0; i < M->rows; i++) {
		for (int j = 0; j < M->cols; j++) {
			M->data[i * M->cols + j] = value;
		}
	}
}

mtrx* mtrx_zeros(int rows, int cols) {
	mtrx* M = mtrx_alloc(rows, cols);
	mtrx_fill(M, 0.0);
	return M;
}

mtrx* mtrx_ones(int rows, int cols) {
	mtrx* M = mtrx_alloc(rows, cols);
	mtrx_fill(M, 1.0);
	return M;
}

mtrx* mtrx_id(int rows, int cols) {
	assert(rows == cols);
	mtrx* M = mtrx_alloc(rows, cols);
	for (int i = 0; i < rows; i++) {
		M->data[i * rows + i] = 1.0;
	}
	return M;
}

void mtrx_print(const mtrx *M) {
	for (int i = 0; i < M->rows; i++) {
		for (int j = 0; j < M->cols; j++) {
			printf("%f+%fi, ", creal(M->data[i * M->cols + j]), cimag(M->data[i * M->cols + j]));

		}
		printf("\n");
	}
}

void mtrx_set_elem(mtrx* M, int row, int col, double complex value) {
	// Check index validity
	assert(row < M->rows);
	assert(col < M->cols);

	M->data[row * M->cols + col] = value;
}

double complex mtrx_get_elem(mtrx* M, int row, int col) {
	// Check index validity
	assert(row < M->rows);
	assert(col < M->cols);
	
	return M->data[row * M->cols + col];
}

void mtrx_swp_rows(mtrx* M, int row_a, int row_b) {
	assert(row_a < M->rows);
	assert(row_b < M->rows);
	for (int i = 0; i < M->cols; i++) {
		double complex tmp = M->data[row_a * M->cols + i];
		M->data[row_a * M->cols + i] = M->data[row_b * M->cols + i];
		M->data[row_b * M->cols + i] = tmp;
	}
}

void mtrx_transpose(mtrx* M) {
	for (int i = 0; i < M->rows; i++) {
		for (int j = 0; j < M->cols; j++) {
			double complex tmp = M->data[i * M->cols + j];
			M->data[i * M->cols + j] = M->data[j * M->cols + i];
			M->data[j * M->cols + i] = tmp;
		}
	}
}

void mtrx_mem_test() {
	mtrx* M = mtrx_id(4, 4);
	mtrx_swp_rows(M, 0, 2);
	mtrx_transpose(M);
	mtrx_print(M);
	mtrx_free(M);
}

int main() {
	mtrx_mem_test();
	return 0;
}

