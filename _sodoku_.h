#ifndef _sodoku_
#define _sodoku_

int check_col(int, int, int, int **);
int check_row(int, int, int, int **);
int check_square(int, int, int, int **);
int sodoku_solver(int, int, int **);
void print_sodoku(int , int , int **);
int one_solution(int , int , int **);

#endif