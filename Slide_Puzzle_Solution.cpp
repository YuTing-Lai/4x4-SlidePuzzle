//============================================================================
// Name        : Slide_Puzzle_solution.cpp
// Author      : TimLai
// Version     :
// Copyright   : Your copyright notice
// Description : 4x4 Slide Puzzle Solution in C++
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <iomanip>
#include <cstring>
#include <queue>

using namespace std;

queue<string> move_step;
int puzzle[6][6] = {{0}};
int cc;


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

void swap_puzzle(char mode){
	cc++;
	int pos=0;
	for(; pos<16; pos++){
		if(puzzle[pos/4 +1][pos%4 +1] == 16)
			break;
	}
	int row = pos/4 + 1;
	int col = pos%4 + 1;

	switch(mode)
	{
		case 'u':
			puzzle[row][col] = puzzle[row-1][col];
			puzzle[row-1][col] = 16;
			move_step.push("down");
			break;
		case 'd':
			puzzle[row][col] = puzzle[row+1][col];
			puzzle[row+1][col] = 16;
			move_step.push("up");
			break;
		case 'l':
			puzzle[row][col] = puzzle[row][col-1];
			puzzle[row][col-1] = 16;
			move_step.push("right");
			break;
		case 'r':
			puzzle[row][col] = puzzle[row][col+1];
			puzzle[row][col+1] = 16;
			move_step.push("left");
			break;
	}


}

bool correct(){
	for(int i=0; i<16; i++){
		if(puzzle[i/4 +1][i%4 +1] != i+1)
			return false;
	}
	return true;
}

void putOne(){
	if(puzzle[1][1] != 1){
		int posA=0;
		for(; posA<16; posA++){
			if(puzzle[posA/4 +1][posA%4 +1] == 16)
				break;
		}
		int rowA = posA/4 + 1;
		int colA = posA%4 + 1;
		
		//move the 16 to row1 col1
		for(int i=0; i<rowA-1; i++){
			swap_puzzle('u');
		}
		for(int i=0; i<colA-1; i++){
			swap_puzzle('l');
		}

		//number 1's position
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 1)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;




		//move 1 to the row1 first
		//if 1 is at row1, put 16 to the left side of 1
		if(rowB == 1){
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('r');
			}
		}
		//1 is not at row1, then put 1 to row 1
		else{
			//move 16 to the upside of 1
			for(int i=0; i<colB-1; i++){
				swap_puzzle('r');
			}
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
			}

			//if 1 is at col1, counterclockwise
			if(colB == 1){
				for(int i=0; i<rowB-2; i++){
					swap_puzzle('d');
					swap_puzzle('r');
					swap_puzzle('u');
					swap_puzzle('u');
					swap_puzzle('l');
				}
				swap_puzzle('d');
				swap_puzzle('r');
				swap_puzzle('u');
			}
			//1 is not at col1, clockwise
			else{
				for(int i=0; i<rowB-2; i++){
					swap_puzzle('d');
					swap_puzzle('l');
					swap_puzzle('u');
					swap_puzzle('u');
					swap_puzzle('r');
				}
				swap_puzzle('d');
				swap_puzzle('l');
				swap_puzzle('u');

				//1 is at row 1, put it to col1
				//16 is at the left side of 1
				for(int i=0; i<colB-2; i++){
					swap_puzzle('r');
					swap_puzzle('d');
					swap_puzzle('l');
					swap_puzzle('l');
					swap_puzzle('u');
				}
				swap_puzzle('r');
			}
		}
	}
	else{
		int posA=0;
		for(; posA<16; posA++){
			if(puzzle[posA/4 +1][posA%4 +1] == 16)
				break;
		}
		int rowA = posA/4 + 1;
		int colA = posA%4 + 1;

		if(colA ==1){
			swap_puzzle('r');
		}
		for(int i=0; i<rowA-1; i++){
			swap_puzzle('u');
		}
		for(int i=0; i<colA-2; i++){
			swap_puzzle('l');
		}
	}







}

void putTwo(){
	// number 16 is at row1 col2

	//find number 2
	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == 2)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	// if 2 is at row 1, move it to row1 col2
	if(rowB == 1){
		if(colB == 3){
			swap_puzzle('r');
		}else{
			swap_puzzle('r');
			swap_puzzle('r');
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
			swap_puzzle('r');
		}
	}
	//2 is at row2 or row3 or row4
	//put 2 to the col2 first
	else{
		//if 2 is at col1
		if(colB == 1){
			if(rowB == 2){
				swap_puzzle('d');
				swap_puzzle('l');
				swap_puzzle('d');
				swap_puzzle('r');
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('u');
				swap_puzzle('l');
			}
			else{
				for(int i=0; i<rowB-1; i++){
					swap_puzzle('d');
				}
				swap_puzzle('l');
				swap_puzzle('u');
				swap_puzzle('r');
			}
		}
		//if 2 is at col2, put 16 at the upside of 2
		else if(colB ==2){
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
			}
		}
		//2 is at col3 or col4
		else{
			//put 16 to the same row as 2
			for(int i=0; i<rowB-1; i++){
				swap_puzzle('d');
			}
			//put 16 to the left side of 2
			for(int i=0; i<colB-3; i++){
				swap_puzzle('r');
			}
			//start swaping until 2 is at the col2,
			//and 16 is at the upside of 2
			if(rowB==4){
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('d');
			}
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('l');
		}

		//2 is at the col2, and 16 is at the upside of 2
		for(int i=0; i<rowB-2; i++){
			swap_puzzle('d');
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('u');
			swap_puzzle('l');
		}
		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');
	}


}

void putThree(){
	//put 16 to row1 col4 first
	swap_puzzle('r');

	//check if 3 is at row1 col3
	if(puzzle[1][3] != 3){
		//find number 3
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 3)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;

		//if 3 is at col4
		if(colB == 4){
			//put 16 to the upside of 3
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
			}

			//put 3 to row1, clockwise
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
				swap_puzzle('l');
				swap_puzzle('u');
				swap_puzzle('u');
				swap_puzzle('r');
			}
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('u');
			//put 3 to row1 col3
			swap_puzzle('r');
		}
		//if 3 is not at col4
		else {
			//put 3 to col3 first
			if(colB != 3){
				//put 16 to the same row as 3
				for(int i=0; i<rowB-1; i++){
					swap_puzzle('d');
				}
				//put 16 to the right side of 3
				for(int i=0; i<3-colB; i++){
					swap_puzzle('l');
				}

				//if 3 is at row4, clockwise
				if(rowB == 4){
					if(colB == 1){
						swap_puzzle('l');
						swap_puzzle('u');
						swap_puzzle('r');
						swap_puzzle('r');
						swap_puzzle('d');
					}
					swap_puzzle('l');
					swap_puzzle('u');
					swap_puzzle('r');
				}else{
					// counterclockwise
					for(int i=0; i<3-colB;i++){
						swap_puzzle('l');
						swap_puzzle('d');
						swap_puzzle('r');
						swap_puzzle('r');
						swap_puzzle('u');
					}
					swap_puzzle('u');
					swap_puzzle('l');

				}

			}
			//if 3 is at col3
			else{
				//put 16 to the col3
				swap_puzzle('l');
				//put 16 to the upside of 3
				for(int i=0; i<rowB-2; i++){
					swap_puzzle('d');
				}
			}

			//now 3 is at col3, and 16 is at the upside of 3
			//counterclockwise
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('u');
				swap_puzzle('l');
			}
			swap_puzzle('d');
			swap_puzzle('r');
			swap_puzzle('u');
		}
	}
}

void putFour(){
	//put 16 to row2 col3
	swap_puzzle('d');
	swap_puzzle('l');


	//check if 4 is at row1 col4
	if(puzzle[1][4] != 4){
		//move 1 2 3 to be like a '「'
//		swap_puzzle('u');
//		swap_puzzle('r');
//		swap_puzzle('r');

		//try to put 4 at row2 col3, and put 16 at row2 col1
		//find 4 first
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 4)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;

		if(rowB == 2){
			if(colB == 4){
				swap_puzzle('r');
				swap_puzzle('d');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('u');
			}
			else{
				if(colB == 1){
					swap_puzzle('l');
					swap_puzzle('l');
					swap_puzzle('d');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('u');
				}
				swap_puzzle('l');
				swap_puzzle('l');
			}
		}
		else if (rowB == 3){
			if(colB == 4){
				swap_puzzle('d');
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
			}else if(colB <3){
				swap_puzzle('d');
				if(colB == 1){
					swap_puzzle('l');
					swap_puzzle('l');
					swap_puzzle('d');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('u');
				}
				swap_puzzle('l');
				swap_puzzle('u');
				swap_puzzle('r');
			}
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
		}
		//rowB == 4
		else{
			swap_puzzle('d');
			swap_puzzle('d');
			if(colB == 4){
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('d');
			}
			else if(colB < 3){
				if(colB == 1){
					swap_puzzle('l');
					swap_puzzle('l');
					swap_puzzle('u');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('d');
				}
				swap_puzzle('l');
				swap_puzzle('u');
				swap_puzzle('r');
				swap_puzzle('d');
			}

			swap_puzzle('l');
			swap_puzzle('u');
			swap_puzzle('u');
			swap_puzzle('r');
			swap_puzzle('d');

			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');

		}

		//4 is placed at row2 col3, and 16 is at row2 col1
		swap_puzzle('u');
		swap_puzzle('r');
		swap_puzzle('r');
		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');
		swap_puzzle('l');
		swap_puzzle('l');
		swap_puzzle('l');
		swap_puzzle('d');
	}
	else{
		swap_puzzle('l');
		swap_puzzle('l');
	}
}

void putFive(){
	//find 5
	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == 5)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	if(rowB == 2){
		//put 16 to the left side of 5
		for(int i=0; i< colB-2; i++){
			swap_puzzle('r');
		}
		//clockwise
		for(int i=0; i<colB-2; i++){
			swap_puzzle('r');
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
		}
		swap_puzzle('r');
	}
	//5 is at row3 or row4
	else{
		if(colB != 1){
			//if 5 is not at col1, put 16 at the same row as 5
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
			}
			for(int i=0; i<colB-2; i++){
				swap_puzzle('r');
			}
			for(int i=0; i<colB-2; i++){
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('d');
			}
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('l');
		}

		if(rowB == 4){
			swap_puzzle('d');
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('u');
			swap_puzzle('l');
		}

		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');
	}
}

void putSix(){
	//find 6
	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == 6)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	//if 6 is at row2
	if(rowB == 2){
		if(colB == 4){
			swap_puzzle('r');
			swap_puzzle('r');
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
		}
		//6 is at row2 col3, 16 is at col2 row2
		swap_puzzle('r');
	}
	//6 is at row3 or row4
	else{
		if(colB != 2){
			//put 16 at the same row as 6
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
			}
			//if 6 is at col1
			if(colB == 1){
				//if 6 is at row4, clockwise
				if(rowB == 4){
					swap_puzzle('l');
					swap_puzzle('u');
					swap_puzzle('r');
				}
				//6 is at row3
				else{
					swap_puzzle('l');
					swap_puzzle('d');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('u');
					swap_puzzle('u');
					swap_puzzle('l');
				}
			}
			// if 6 is at col3 or col4
			else if(colB > 2){
				//if 6 is at col4
				if(colB == 4){
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('u');
					swap_puzzle('l');
					swap_puzzle('l');
					swap_puzzle('d');
				}
				//if 6 is at col3
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
			}



		}
		// 6 is at col2 now
		//if 6 is at row4
		if(rowB == 4){
			swap_puzzle('d');
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('u');
			swap_puzzle('l');
		}
		//6 is at row3 col2, 16 is at row2 col2
		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');
	}
}

void putSeven(){
	//put 16 to row2 col4
	swap_puzzle('r');

	if(puzzle[2][3] != 7){
		//find 7
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 7)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;

		//if 7 is not at col4
		if(colB != 4){
			//put 16 to the same row as 7
			for(int i=0; i<rowB-2; i++){
				swap_puzzle('d');
			}

			//put 16 to the right side of 7
			for(int i=0; i<3-colB; i++){
				swap_puzzle('l');
			}

			//if 7 is at row 3, counterclockwise
			if(rowB == 3){
				for(int i=0; i<3-colB; i++){
					swap_puzzle('l');
					swap_puzzle('d');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('u');
				}
				swap_puzzle('l');
				swap_puzzle('u');
				swap_puzzle('r');
			}
			//7 is at row4, clockwise
			else{
				for(int i=0; i<3-colB; i++){
					swap_puzzle('l');
					swap_puzzle('u');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('d');
				}
				swap_puzzle('l');
				swap_puzzle('u');
				swap_puzzle('r');
			}
		}
		//now 7 is at col4
		if(rowB ==4){
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('u');
			swap_puzzle('u');
			swap_puzzle('r');
		}
		//now 7 is at row3 col4
		swap_puzzle('d');
		swap_puzzle('l');
		swap_puzzle('u');

		//now 7 is at row2 col4, 16 is at row2 col3
		swap_puzzle('r');
		//finished
	}




}

void putEight(){
	//put 16 to row3 col3 first
	swap_puzzle('d');
	swap_puzzle('l');
	//check if 8 is at row2 col4
	if(puzzle[2][4] == 8){
		//if it is, put 16 to row3 col1
		swap_puzzle('l');
		swap_puzzle('l');
	}
	else{
		//try to put 8 at row3 col3
		//find 8 first
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 8)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;

		//if 8 is at row3
		if(rowB == 3){
			//if 8 is at row3 col4
			if(colB == 4){
				//put 8 at row3 col3, 16 is at row3 col1
				swap_puzzle('r');
				swap_puzzle('d');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('u');
			}
			else{
				if(colB == 1){
					swap_puzzle('l');
					swap_puzzle('l');
					swap_puzzle('d');
					swap_puzzle('r');
					swap_puzzle('r');
					swap_puzzle('u');
				}
				swap_puzzle('l');
				swap_puzzle('l');
			}
		}
		//8 is at row4
		else{
			if(colB != 3){
				swap_puzzle('d');
				if(colB == 4){
					swap_puzzle('r');
					swap_puzzle('u');
					swap_puzzle('l');
				}
				else{
					if(colB == 1){
						swap_puzzle('l');
						swap_puzzle('l');
						swap_puzzle('u');
						swap_puzzle('r');
						swap_puzzle('r');
						swap_puzzle('d');
					}
					swap_puzzle('l');
					swap_puzzle('u');
					swap_puzzle('r');
				}
			}
			//now 8 is at row4 col3, 16 is at row3 col3
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
		}

		//now 8 is at row3 col3; 16 is at row3 col1
		//put 8 inside
		swap_puzzle('u');
		swap_puzzle('r');
		swap_puzzle('r');
		swap_puzzle('d');

		swap_puzzle('r');
		swap_puzzle('u');
		swap_puzzle('l');
		swap_puzzle('l');
		swap_puzzle('l');
		swap_puzzle('d');
	}

}

void putNine(){
	//find 9
	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == 9)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	if(rowB == 3){
		//put 16 to the left side of 9
		for(int i=0; i<colB-2; i++){
			swap_puzzle('r');
		}
		//clockwise
		for(int i=0; i<colB-2; i++){
			swap_puzzle('r');
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
		}
		//9 is at row3 col2, 16 is at row3 col1, move it
		//put 16 at row4 col1
		swap_puzzle('r');
		swap_puzzle('d');
		swap_puzzle('l');
	}
	//9 is at row4
	else{
		if(colB != 1){
			swap_puzzle('d');
			for(int i=0; i<colB-2; i++){
				swap_puzzle('r');
			}
			//counterclockwise
			for(int i=0; i<colB-2; i++){
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('d');
			}
			//9 is at row4 col2, 16 is at row4 col1, move it
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('l');
		}
		swap_puzzle('d');

	}
}

void putThirteen(){
	swap_puzzle('r');
	if(puzzle[4][1] == 13){
		swap_puzzle('u');
	}
	//try to put 13 at row4 col3, put 16 at row4 col2
	else{
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 13)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;

		if(rowB == 3){
			if(colB == 2){
				//clockwise
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('d');
				swap_puzzle('r');
			}
			//colB == 3or 4
			else{
				if(colB == 4){
					swap_puzzle('r');
					swap_puzzle('u');
					swap_puzzle('r');
					swap_puzzle('d');
					swap_puzzle('l');
					swap_puzzle('l');
				}
				//counterclockwise
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('d');
			}

		}
		//13 is at row4, col3 or col4
		else{
			if(colB == 4){
				swap_puzzle('r');
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('d');
			}
		}

		//now 13 is at row4 col3, 16 is at row4 col2
		//put 13 inside, and put 16 at row3 col2
		swap_puzzle('l');
		swap_puzzle('u');
		swap_puzzle('r');
		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');
		swap_puzzle('l');
		swap_puzzle('l');
		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');

	}

}

void putTen(){
	//find 10
	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == 10)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	//try to put 10 at row3 col2, put 16 at row4 col2
	if(rowB == 3){
		if(colB == 4){
			swap_puzzle('r');
			swap_puzzle('r');
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('l');
			swap_puzzle('u');
		}
		swap_puzzle('r');
		swap_puzzle('d');
		swap_puzzle('l');
	}
	else{
		if(colB != 2){
			swap_puzzle('d');
			if(colB == 4){
				swap_puzzle('r');
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('l');
				swap_puzzle('d');
			}
			swap_puzzle('r');
			swap_puzzle('u');
			swap_puzzle('l');
		}
		//now 10 is at row4 col2, and 16 is at row3 col2, move it
		swap_puzzle('d');
	}
}

void putFourteen(){
	swap_puzzle('r');
	//check if 14 is at row4 col2
	if(puzzle[4][2] == 14){
		swap_puzzle('u');
	}
	else{
		//find 14
		int posB=0;
		for(; posB<16; posB++){
			if(puzzle[posB/4 +1][posB%4 +1] == 14)
				break;
		}
		int rowB = posB/4 + 1;
		int colB = posB%4 + 1;

		/*
		 * Three possibles
		 * 1. 14 is at row3 col3
		 * 2. 14 is at row3 col4
		 * 3. 13 is at row4 col4
		 */

		//try to put 12 at row4 col4, put 16 at row4 col3
		if(rowB == 3){
			if(colB == 3){
				//clockwise
				swap_puzzle('u');
				swap_puzzle('r');
				swap_puzzle('d');
				swap_puzzle('l');
			}
			else{
				//counterclockwise
				swap_puzzle('r');
				swap_puzzle('u');
				swap_puzzle('l');
				swap_puzzle('d');
			}
		}

		//14 and 16 is set, put 14 inside
		swap_puzzle('l');
		swap_puzzle('u');
		swap_puzzle('r');
		swap_puzzle('d');
		swap_puzzle('r');
		swap_puzzle('u');
		swap_puzzle('l');
		swap_puzzle('l');
		swap_puzzle('d');
		swap_puzzle('r');

		//put 16 at row3 col3
		swap_puzzle('u');
	}
}

void putEleven(){
	//find 11
	int posB=0;
	for(; posB<16; posB++){
		if(puzzle[posB/4 +1][posB%4 +1] == 11)
			break;
	}
	int rowB = posB/4 + 1;
	int colB = posB%4 + 1;

	/*
	 * Three possibles: right, down, right and down
	 */
	if(colB == 3){
		swap_puzzle('d');
		swap_puzzle('r');
	}
	else{
		if(rowB == 4){
			swap_puzzle('r');
			swap_puzzle('d');
			swap_puzzle('l');
			swap_puzzle('u');
		}
		swap_puzzle('r');
		swap_puzzle('d');
	}
}

void printMoveSteps(){
	int nextLine = 1;
	cout << "The moves: " << endl;
	while(!move_step.empty()){
		cout << setiosflags(ios::left) << setw(6) << move_step.front() << " ";
		move_step.pop();
		if(nextLine == 10){
			nextLine = 0;
			printf("\n");
		}
		nextLine++;
	}
	printf("\n");
}


int main() {
	cc = 0;

	cout << "Input the puzzle, from left to right, from up to down." << endl;
	cout << "If it is the blank, input 16." << endl;

	int puzzle_number;
	for(int i=0; i<16; i++){
		cin >> puzzle_number;
		puzzle[i/4 +1][i%4 +1] = puzzle_number;
	}

	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 1" << endl;
	putOne();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 2" << endl;
	// number 16 is at row1 col2
	putTwo();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 3" << endl;
	// number 16 is at row1 col3
	putThree();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 4" << endl;
	//number 16 is at row1 col4
	putFour();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 5" << endl;
	//number 16 is at row2 col1
	putFive();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 6" << endl;
	//number 16 is at row2 col2
	putSix();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 7" << endl;
	//number 16 is at row2 col3
	putSeven();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 8" << endl;
	//number 16 is at row2 col4
	putEight();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 9" << endl;
	//number 16 is at row3 col1
	putNine();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 13" << endl;
	//number 16 is at row4 col1
	putThirteen();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 10" << endl;
	//number 16 is at row3 col2
	putTen();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 14" << endl;
	//number 16 is at row3 col2
	putFourteen();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;

	cout << "Move 11" << endl;
	//number 16 is at row3 col3
	putEleven();
	printMoveSteps();
	print_puzzle(puzzle);
	cout << endl;


	cout << "It takes " << cc << " moves" << endl;









	return 0;
}
