// João Pedro Kosour Guimarães - 11218556
#include <stdio.h>
#include <stdlib.h>
#include "_sodoku_.h"

int main(void) {
 	char c;
	int i, j, k;
	// Aloca memoria para a matriz que representa o sodoku.
	int **sodoku = (int **) calloc(16, sizeof(int *));
	for(i = 0; i < 17; i++)
		sodoku[i] = calloc(16, sizeof(int));

	//enquanto le transforma de char para int para mais facil manipulação.
	for(i = 0; i < 16; i++)
		for(j = 0; j < 16; j++){
			scanf("%c", &c);
			if(c == '\n')
				j--;
			if(c == '.') //posiçoes nao preenchidas sao representadas por -1.
				sodoku[i][j] = -1;
			else if(c == 'A')
				sodoku[i][j] = 10;
			else if(c == 'B')
				sodoku[i][j] = 11;
			else if(c == 'C')
				sodoku[i][j] = 12;
			else if(c == 'D')
				sodoku[i][j] = 13;
			else if(c == 'E')
				sodoku[i][j] = 14;
			else if(c == 'F')
				sodoku[i][j] = 15;
			else
				sodoku[i][j] = c - 48;
		}
	
	//Enquanto existem casas com só uma solução preenche elas.
	for(k = 0; k < 2; k++)
		for(i = 0; i < 16; i++)
			for(j = 0; j < 16; j++)
				if(sodoku[i][j] == -1){
					sodoku[i][j] = one_solution(i, j, sodoku);
					if(sodoku[i][j] != -1)
						k = 0;
				}

	sodoku_solver(0, 0, sodoku);
	print_sodoku(16, 16, sodoku);

	free(sodoku);
  return 0;
}

//printa o sodoku substituindo os numeros de 10 a 15 por seus valores em hexa.
void print_sodoku(int row, int col, int **sodoku){
	int i, j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			if(sodoku[i][j] == 10)
				printf("A");
			else if(sodoku[i][j] == -1)
				printf(".");
			else if(sodoku[i][j] == 11)
				printf("B");
			else if(sodoku[i][j] == 12)
				printf("C");
			else if(sodoku[i][j] == 13)
				printf("D");
			else if(sodoku[i][j] == 14)
				printf("E");
			else if(sodoku[i][j] == 15)
				printf("F");
			else
				printf("%d", sodoku[i][j]);
		}
	printf("\n");
	}
}

//- Função recursiva que testa possibilidades em cada casa que nao possui um valor.
//- Caso não encontre nenhum numero que caiba naquela casa utiliza backtracking para mudar um valor anterior.
//- num_atual é o numero que esta sendo testado para a casa.
//- x, tempx, y, tempy representam as posicoes i, j da matriz.
int sodoku_solver(int x, int y, int **sodoku){
	int num_atual = 0, tempx = 0, tempy = 0;
	if(sodoku[x][y] != -1){
		if(x == 16 && y == 16)
			return 1;
		if(x < 16) x++;
		else{
			x = 0;
			y++;
		}
		if(sodoku_solver(x, y, sodoku))
			return 1;
		else 
			return 0;
	}

	if(sodoku[x][y] == -1){
		while(num_atual < 16){
			if(!check_col(x, y, num_atual, sodoku) && !check_row(x, y, num_atual, sodoku) && !check_square(x, y, num_atual, sodoku)){
			if(x == 16 && y == 16)
				return 1;
				
			sodoku[x][y] = num_atual;

			if(sodoku[x][y] != -1){
				if(x < 16) 
					tempx = x+1;
				else
					if(y < 16){
						tempx = 0;
						tempy = y + 1;
					}
				if(sodoku_solver(tempx, tempy, sodoku))
					return 1;
				}
			}
			num_atual++;
		}
		sodoku[x][y] = -1;
		return 0;
	}
	return 1;
}

//percorre coluna procurando se existe um numero similar.
int check_col(int x, int y, int key, int **sodoku){
	int i;
	for(i = 0; i < 16; i++)
		if(sodoku[x][i] == key)
			return 1;
	return 0;
}

//percorre a linha procurando se existe um numero similar.
int check_row(int x, int y, int key, int **sodoku){
	int i;
	for(i = 0; i < 16; i++)
		if(sodoku[i][y] == key)
			return 1;
	return 0;
}

//- A funçao checa se o numero ja existe em um quadrante (representado nesse caso por 4x4).
//- As condicoes de if no inicio da funcao fazem com que x e y fiquem posicionados no inicio do quadrante para o for poder percorrer todo o quadrante em todos os casos.
int check_square(int x, int y, int key, int **sodoku){
	int i, j;

	if(x < 4) x = 0;
	else if(x < 8) x = 4;
	else if(x < 12) x = 8;
	else x = 12;

	if(y < 4) y = 0;
	else if(y < 8) y = 4;
	else if(y < 12) y = 8;
	else y = 12;

	for(i = x; i < x + 4; i++)
		for(j = y; j < y + 4; j++)
			if(sodoku[i][j] == key)
				return 1;
	return 0;
}

//A função chama as subrotinas de coluna, linha e quadrante para determinar se existe só uma solução, caso só exista uma retorna ela, se nao retorna -1 para indicar que nenhum valor unico foi encontrado para aquela posição.
int one_solution(int x, int y, int **sodoku){
	int i, aux = -1, cont = 0;
		for(i = 0; i < 16; i++){
		if(!check_col(x, y, i, sodoku) && !check_row(x, y, i, sodoku) && !check_square(x, y, i, sodoku)){
			aux = i;
			cont++;
		}
	}
	if(cont == 1) return aux;
	else return -1;
}
