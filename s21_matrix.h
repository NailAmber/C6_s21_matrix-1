#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

// Матрица - это набор чисел, расположенных в фиксированном количестве строк и
// столбцов.
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result);
// Удаление матрицы
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение матрицы на матрицу
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Вспомогательные функции:

// Возвращает единицу если заданные размеры меньше 1, то есть некорректны для
// матрицы
int is_bad_size(const int rows, const int columns);
// Возвращает единицу если размеры матриц одинаковы
int is_eq_size(const matrix_t *A, const matrix_t *B);
void fill_matrix(const matrix_t *A);
void text_matrix(const matrix_t *A);
int is_nan_inf_matrix(const matrix_t *A);
int is_mult_size(const matrix_t *A, const matrix_t *B);
int gaussian_elimination(const matrix_t *A, matrix_t *result);
void inverse_gaussian_elimination(const matrix_t *A, matrix_t *result);
void swap_rows(const int n1, const int n2, matrix_t *A);
int sort_zeros(const int n1, const int m, matrix_t *A);
void copy_matrix(const matrix_t *A, matrix_t *B);
double first_minor(const int row, const int column, const matrix_t *A);

#endif  // S21_MATRIX_H_