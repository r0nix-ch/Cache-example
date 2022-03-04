#include <iostream>
#include <chrono>

using namespace std;

struct Matrix {
    double** data;
    int m_rows, m_cols;

    Matrix(int rows, int cols);

    void fill_matrix();
    void print();
};


Matrix::Matrix(int rows, int cols) {
    data = new double*[rows];
    this->m_rows = rows;
    this->m_cols = cols;

    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
    }
}


void Matrix::fill_matrix() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            data[i][j] = rand() % (100 - 10 + 1) + 10;
        }
    }
}


Matrix matrix_mul(Matrix& a, Matrix& b) {
    Matrix c(a.m_rows, b.m_cols);
    for (int i = 0; i < a.m_rows; i++) {
        for (int j = 0; j < b.m_cols; j++) {
            c.data[i][j] = 0;
            for (int k = 0; k < a.m_cols; k++) {
                c.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return c;
}

Matrix transposition(Matrix& matrix) {
    Matrix transp(matrix.m_cols, matrix.m_rows);
    for (int i = 0; i < matrix.m_rows; i++) {
        for (int j = 0; j < matrix.m_cols; j++) {
            transp.data[j][i] = matrix.data[i][j];
        }
    }

    return transp;
}

Matrix matrix_mul_transposed(Matrix& a, Matrix& b) {
    Matrix result(a.m_rows, b.m_cols);
    Matrix b_transp = transposition(b);

    for (int i = 0; i < a.m_rows; i++) {
        for (int j = 0; j < b.m_cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.m_cols; k++) {
                result.data[i][j] += a.data[i][k] * b_transp.data[j][k];
            }
        }
    }

    return result;
}


double time_mul_matrix(Matrix& a, Matrix& b) {
    auto start = chrono::steady_clock::now();
    Matrix result = matrix_mul(a, b);
    auto end = chrono::steady_clock::now();

    return chrono::duration<double>(end - start).count();
}

double time_mul_matrix_transposed(Matrix& a, Matrix& b) {
    auto start = chrono::steady_clock::now();
    Matrix result = matrix_mul_transposed(a, b);
    auto end = chrono::steady_clock::now();

    return chrono::duration<double>(end - start).count();
}


void Matrix::print() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int rows1 = 1200;
    int cols1 = 1000;
    int rows2 = cols1;
    int cols2 = 1600;

    Matrix a(rows1, cols1);
    Matrix b(rows2, cols2);
    a.fill_matrix();
    b.fill_matrix();

    cout << "time mul_matrix: " << time_mul_matrix(a, b) << "s" << endl;
    cout << "time mul_matrix_transposed: " << time_mul_matrix_transposed(a, b) << "s" << endl;

}

