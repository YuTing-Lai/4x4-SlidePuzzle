//============================================================================
// Name        : Slide_Puzzle.cpp
// Author      : YuTing-Lai
// Version     :
// Copyright   : Your copyright notice
// Description : Slide Puzzle
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <iomanip>

using namespace std;

int question[16];
int puzzle[6][6] = {{0}};


void swap(int arr[16], int a, int b){
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void print_puzzle(int arr[6][6]){
	for(int i=1; i<=4; i++){
		for(int j=1; j<=4; j++){
			if(arr[i][j] == 16)
				cout << setw(3) << " " << " ";
			else
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << endl;
	}
}

bool near(int a){
	if(a>15 || a<1)
		return false;

	int posA=0;
	for(; posA<16; posA++){
		if(puzzle[posA/4 +1][posA%4 +1] == 16)
			break;
	}
	int rowA = posA/4 + 1;
	int colA = posA%4 + 1;

	//upside
	if(puzzle[rowA-1][colA] == a)
		return true;
	//left side
	else if(puzzle[rowA][colA-1] == a)
		return true;
	//right side
	else if(puzzle[rowA][colA+1] == a)
		return true;
	//down side
	else if(puzzle[rowA+1][colA] == a)
		return true;

	//not near
	return false;


}

void swap_puzzle(int a){
	int posA=0;
	for(; posA<16; posA++){
		if(puzzle[posA/4 +1][posA%4 +1] == 16)
			break;
	}
	int rowA = posA/4 + 1;
	int colA = posA%4 + 1;

	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == a)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	puzzle[rowA][colA] = a;
	puzzle[rowB][colB] = 16;
}

bool correct(){
	for(int i=0; i<16; i++){
		if(puzzle[i/4 +1][i%4 +1] != i+1)
			return false;
	}
	return true;
}

int main() {
	srand( time(NULL) );



//	cout << puzzle[2][2];

	for(int i=0; i<16; i++){
		question[i] = i+1;
	}

//	for(int i=0; i<100; i++){
//		int x = rand() % 16;
//		swap(question, x, (i%16));
//	}

	int question_pos=0;
	for(int i=1; i<=4; i++){
		for(int j=1; j<=4; j++){
			puzzle[i][j] = question[question_pos];
			question_pos++;
		}
	}

//	print_puzzle(puzzle);

	for(int i=0; i<10000; i++){
		int random_switch = rand() % 15 + 1;
		if(near(random_switch))
			swap_puzzle(random_switch);
	}
	print_puzzle(puzzle);

	int move_number;
	while(scanf("%d",&move_number) != EOF){
		if(near(move_number))
			swap_puzzle(move_number);

		else
			cout << "error!!" << endl;


		print_puzzle(puzzle);

		if(correct()){
			cout << "Finished! Great Job!" << endl;
			break;
		}else{
			cout << "Enter the number you want to move:" << endl;
		}
	}



	return 0;
}
