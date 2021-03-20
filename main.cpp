/*
 * main.cpp
 *
 *  Created on: Mar 19, 2021
 *      Author: d-w-h
 */

#include <stdio.h>
#include <cstdlib>
#include <time.h>

double** mat2D(int nx, int ny);
void lu_decomposition(double** A,
                      int N,
                      double** L,
                      double** U);

int main(int argc, char* argv[]) {

    int N = 4;

    double** A = mat2D(N, N);
    double** L = mat2D(N, N);
    double** U = mat2D(N, N);

    /* Initialize A */
    srand (time(NULL));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            A[i][j] = (double) rand() / RAND_MAX;
        }
    }

    /* LU decomposition */
    lu_decomposition(A, N, L, U);

    /* Print results */
    printf("L:\n");
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("L[%i][%i]: %f, ", i, j, L[i][j]);
        }
        printf("\n");
    }

    printf("U:\n");
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("U[%i][%i]: %f, ", i, j, U[i][j]);
        }
        printf("\n");
    }

    printf("done\n");

    return 0;
}

double** mat2D(int nx, int ny) {

    double** f = new double*[nx];

    for(int i = 0; i < nx; ++i) {
        f[i] = new double[ny];
    }

    return f;
}

void lu_decomposition(double** A,
                      int N,
                      double** L,
                      double** U) {

    /* Initialize L */
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(i == j) {
                L[i][j] = 1.0;
            }
            else {
                L[i][j] = 0.0;
            }
        }
    }

    /* Initialize U */
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(i > j) {
                U[i][j] = 0.0;
            }
        }
    }

    /* LU decomposition */
    for(int k = 0; k < N; ++k) {
        U[k][k] = A[k][k];
        for(int i = k + 1; i < N; ++i) {
            L[i][k] = A[i][k] / U[k][k];
            U[k][i] = A[k][i];
        }
        for(int i = k + 1; i < N; ++i) {
            for(int j = k + 1; j < N; ++j) {
                A[i][j] = A[i][j] - L[i][k]*U[k][j];
            }
        }
    }
}
