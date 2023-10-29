#include <iostream>
#include <conio.h>
#include<stdio.h>
#include <time.h>
#include <windows.h>
using namespace std;

#define N 4
#define MINE 2


bool getstart() {
	char value;
	cin >> value;

	switch (value)
	{
	case 'y':
		system("cls");
		return true;
		break;
	case 'n':
		return false;
		break;
	default:
		system("cls");
		return true;
		break;
	}
}

bool check_flag_map(char** mine_mx, char** mx, int count_flags) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mx[i][j] == 'f' &&  mine_mx[i][j] == '*') {
				count += 1;
			}
		}
	}

	if (count == MINE && count_flags == MINE) {
		return true;
	}
	else {
		return false;
	}
}

void open_cells(int y, int x, char** mine_mx, char** mx) {
	for (int i = y - 1, s = 0; s < 3; i++, s++) {
		for (int j = x - 1, d = 0; d < 3; j++, d++) {
			if (i < 0 || j < 0) {
				continue;
			}
			else if (i >= N || j >= N) {
				continue;
			}
			else {
				mx[i][j] = mine_mx[i][j];
			}
		}
	}
}

void gameplay(char** mx, char** sq_mx, char** mine_mx, char** base_flags) {
	char enter = 'p';
	int count_flags = 0;
	
	int x = 0; int y = 0;
	while (enter != '!'){
		system("cls");
		char just_char = mx[y][x];
		mx[y][x] = '#';

		// Print game matrix
		for (int i = 0; i < N; i++) {
			cout << endl;
			for (int j = 0; j < N; j++) {
				cout << mx[i][j] << " ";
			}
		}
		
		mx[y][x] = just_char;
		
		
		
		cout << endl <<  "Take move (a/w/d/s/f (flag)): ";
		cin >> enter;
		switch (enter)
		{
		case 'w':
			if (y - 1 >= 0)
				y -= 1;
			break;
		case 'd':
			if (x + 1 < N) 
				x += 1;
			break;
		case 'a':
			if(x - 1 >= 0)
				x -= 1;
			break;
		case 's':
			if(y + 1 < N)
				y += 1;
			break;
		case 'k':
			if (mine_mx[y][x] == '*') {
				enter = '!';
			}
			if (mine_mx[y][x] == '0') {
				open_cells(y, x, mine_mx, mx);
			}
			else {
				mx[y][x] = mine_mx[y][x];
			}
			break;
		case 'f':
			if (base_flags[y][x] == '0') {
				base_flags[y][x] = mx[y][x];
				mx[y][x] = 'f';
				count_flags += 1;
			}
			else {
				mx[y][x] = base_flags[y][x];
				base_flags[y][x] = '0';
				count_flags -= 1;
			}
			break;
		default:
			break;
		}
	}

	if (check_flag_map(mine_mx, mx, count_flags) == true) {
		cout << "You win";
	}
	else cout << "You lost";

	// Check visual matrix with mines
	for (int i = 0; i < N; i++) {
		cout << endl;
		for (int j = 0; j < N; j++) {
			cout << mine_mx[i][j];
		}
	}
}


// If there was an error, there will be a warning
void check(char** mine_mx, int c_m) {
	int count_mine = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mine_mx[i][j] == '*') {
				count_mine += 1;
			}
		}
	}
	if (count_mine == c_m) {
		
	}
	else {
		//system("cls");
		cout << "ERROR MINE";
		Sleep(2000);
	}

}

// generate mine
char** generate_mine(char** mine_mx, int count_mine) {
	srand(time(NULL));
	int x, y;
	int** rand_num = (int**)calloc(N, sizeof(int*));
	for (int i = 0; i < N; i++) {
		rand_num[i] = (int*)calloc(2, sizeof(int));
	}
	// Create mines
	for (int i = 0; i < count_mine; i++) {
		y = rand() % N;
		x = rand() % N;
		if (rand_num[y][x] == 0) {
			rand_num[y][x] = -1;
		}else 
			while (rand_num[y][x] == -1) {
				y = rand() % N;
				x = rand() % N;
			}
		mine_mx[y][x] = '*';
	}

	// cheak count mines
	check(mine_mx, count_mine);

	for (int i = 0; i < MINE; i++) {
		free(rand_num[i]);
	}
	free(rand_num);
	return mine_mx;
}

char count_mine_check(int y, int x, char** mine_mx, char** sq_mx) {
	for (int i = y - 1, s = 0; s < 3; i++, s++) {
		//cout << endl;
		for (int j = x - 1, d = 0; d < 3; j++, d++) {
			if (i < 0 || j < 0) {
				sq_mx[s][d] = '-';
				//cout << sq_mx[s][d];
			}
			else if (i >= N || j >= N) {
				sq_mx[s][d] = '-';
				//cout << sq_mx[s][d];
			}
			else {
				sq_mx[s][d] = mine_mx[i][j];
				//cout << sq_mx[s][d];
			}
		}
	}

	int counter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (sq_mx[i][j] == '*') {
				counter += 1;
			}
		}
	}
	char count_mines = '0' + counter;
	return count_mines;
}

char** create_mine_map(char** mine_mx, char** sq_mx) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mine_mx[i][j] != '*') {
				mine_mx[i][j] = count_mine_check(i, j, mine_mx, sq_mx);
			}
		}
	}
	
	return mine_mx;
}

int main() {
	
	char** mx = (char**)malloc(N* sizeof(char*));
	char** mine_mx = (char**)calloc(N, sizeof(char*));
	char** base_flags = (char**)calloc(N, sizeof(char*));

	for (int i = 0; i < N; i++) {
		mx[i] = (char*)malloc(N* sizeof(char));
		mine_mx[i] = (char*)malloc(N * sizeof(char));
		base_flags[i] = (char*)malloc(N * sizeof(char));
		for (int j = 0; j < N; j++) {
			mx[i][j] = '@';
			mine_mx[i][j] = '0';
			base_flags[i][j] = '0';
		}
	}
	

	const int n = 3;
	char** sq_mx = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		sq_mx[i] = (char*)malloc(n * sizeof(char));
	}
	


	// pritnf matrix
	for (int i = 0; i < N; i++) {
		cout << endl;
		for (int j = 0; j < N; j++) {
			cout << mx[i][j] << " ";
		}
	}

	cout << endl << "Are u ready? (y/n): ";
	
	if (getstart() == true) {
		
	}
	system("cls");

	mine_mx = generate_mine(mine_mx, MINE);
	mine_mx = create_mine_map(mine_mx, sq_mx);
	gameplay(mx, sq_mx, mine_mx, base_flags);
	
	
for (int i = 0; i < N; i++) {
		free(mx[i]);
		free(mine_mx[i]);
		free(base_flags[i]);
	}
	free(mx);
	free(mine_mx);
	free(base_flags);

	for (int i = 0; i < n; i++) {
		free(sq_mx[i]);
	}
	free(sq_mx);
	
	return 0;
}