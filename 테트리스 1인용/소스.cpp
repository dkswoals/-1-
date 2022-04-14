#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include <stdlib.h>

#define _CRT_NONSTDC_NO_WARNINGS
#define left 75
#define right 77
#define up 72
#define down 80

// 맵 크기
#define mapx 16
#define mapy 24

#define debug 1  //필드 데이터 값 보기 = 2  도형값 보기 = 1


time_t ti;
time_t cti;


void blockr();
void kbin(int g);
void gotoxy(int x, int y);
int lineremove();
void CursorView();
void map_make();
void blockdrow();
void map_drow();
int xyw(int x, int y);
int speed(void);
int crushcheck(void);
int gameover();



int hard = 1000;
int score = 0; //점수 저장
int kx = 0, ky = 0; // 키보드 입력값
int bx, by;; // 블럭 좌표값
int b_t = 0; //블록 종류를 저장 
int b_r = 0; //블록 회전값 저장 

int orgmap[mapx][mapy] = { 0 }; /////////////필드 크기

int cpymap[mapx][mapy] = { 0 }; /////////////카피할 필드

int chanse = 0; //바닥 충돌시 움직일 기회


int block[7][4][4][4] = {
{{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0},//사각블럭 block[0]
 {0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0},{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0},//일자블럭 block[1]
 {0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0},{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0}},
{{0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,0,2,0,0,2,2,0,0,2,0,0},//ㄱㄴ블럭 block[2]
 {0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,0,2,0,0,2,2,0,0,2,0,0}},
{{0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0},{0,0,0,0,2,0,0,0,2,2,0,0,0,2,0,0},//ㄱㄴ반대모양 block[3]
 {0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0},{0,0,0,0,2,0,0,0,2,2,0,0,0,2,0,0}},
{{0,0,0,0,0,0,2,0,2,2,2,0,0,0,0,0},{0,0,0,0,2,2,0,0,0,2,0,0,0,2,0,0},//ㅢ모양 block[4]
 {0,0,0,0,0,0,0,0,2,2,2,0,2,0,0,0},{0,0,0,0,0,2,0,0,0,2,0,0,0,2,2,0}},
{{0,0,0,0,2,0,0,0,2,2,2,0,0,0,0,0},{0,0,0,0,0,2,0,0,0,2,0,0,2,2,0,0},//ㄴ모양 block[5]
 {0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,0},{0,0,0,0,0,2,2,0,0,2,0,0,0,2,0,0}},
{{0,0,0,0,0,2,0,0,2,2,2,0,0,0,0,0},{0,0,0,0,0,2,0,0,0,2,2,0,0,2,0,0},//ㅜ모양 block[6]
 {0,0,0,0,0,0,0,0,2,2,2,0,0,2,0,0},{0,0,0,0,0,2,0,0,2,2,0,0,0,2,0,0}}
}; //블록모양 저장





int main() {
	char y = 0;
	srand(time(NULL));//게임 난수 초기화

	int cloor = rand() % 15;

	if (cloor == 0) {
		cloor += 1;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cloor);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                 ★테트리스2022★                     ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■                                                      ■\n");
	printf("■  -Push any key for play-                             ■\n");
	printf("■                                   made by anjaemin   ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");


	y = _getch();


	while (1) {

		system("cls");

		score = 0;
		int g = 0;
		srand(time(NULL));//게임 난수 초기화
		bx = 6;        //초기 블럭 좌표
		by = 1;
		ti = clock();   //초기 런타임 체크
		CursorView();    // 커서 삭제
		int nanido = 0;

		map_make();  //필드 생성
		map_drow(); // 초기 필드 출력
		blockdrow();//블럭 출력


		xyw(0, 0);
		while (1) {


			kbin(1); //키보드 받기

			blockdrow();//블럭 출력
			map_drow();//필드 출력

			if (lineremove() == 1) {
				xyw(0, 0);
			}


			if (speed()) { // 시간차 블럭 드랍
				by++;
			}

			g = gameover();//게임 종료 체크

			if (g == 1) {

				break;
			}
		}


		gotoxy(16, 6);
		printf("GAME OVER");
		Sleep(1500);

		system("cls");
		gotoxy(0, 0);
		printf("CONTINUE?\n\nY\/N\n");
		scanf_s(" %c", &y);

		if (y == 'y' || y == 'Y')
			continue;
		if (y == 'n' || y == 'N')
			break;

	}


	return 0;
}



void CursorView() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);     ///커서 삭제                                                                                  
}




void map_make() {

	for (int iy = 0; iy < mapy; iy++) {//필드 초기화
		for (int ix = 0; ix < mapx; ix++) {
			cpymap[ix][iy] = 0;
		}
	}

	for (int i = 0; i < 16; i++) {
		orgmap[i][0] = 1;     ///천장 생성
		cpymap[i][0] = 1;
	}
	for (int i = 0; i < 16; i++) {
		orgmap[i][23] = 1;    ///바닥 필드 생성
		cpymap[i][23] = 1;
	}
	for (int i = 0; i < 24; i++) {
		orgmap[15][i] = 1;    ///오른벽 필드 생성
		cpymap[15][i] = 1;
	}
	for (int i = 0; i < 24; i++) {
		orgmap[0][i] = 1;     ///왼벽 필드 생성  
		cpymap[0][i] = 1;
	}



	return;
}



void map_drow() {
	int ch = 0;
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);


	//org cpy 비교
	for (int ix = 0; ix < mapx; ix++) {
		for (int iy = 0; iy < mapy; iy++) {
			if (orgmap[ix][iy] != cpymap[ix][iy]) {
				ch = 1;
			}                                          //org cpy 비교
		}
	}


	pos.X = 0;
	pos.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);


	if (ch == 1) {
		for (int iy = 0; iy < mapy; iy++) {
			for (int ix = 0; ix < mapx; ix++) {
				if (cpymap[ix][iy] == 1) {
#if (debug == 1)
					printf("■");
#elif (debug == 2)    
					printf("%d ", cpymap[ix][iy]);
#endif
				}
				else if (cpymap[ix][iy] == 2 || cpymap[ix][iy] == 3) {
#if (debug == 1)
					printf("□");
#elif (debug == 2)    
					printf("%d ", cpymap[ix][iy]);
#endif
				}

				else {
#if (debug == 1)
					printf("  ");
#elif (debug == 2)    
					printf("  ");
#endif
				}
			}
			printf("\n");
		}

	}

	//필드 변화가 있을시 cpy 출력

	return;
}






void blockdrow() {


	for (int iy = 0; iy < mapy; iy++) {
		for (int ix = 0; ix < mapx; ix++) {
			if (cpymap[ix][iy] != 1 && cpymap[ix][iy] != 3) {
				cpymap[ix][iy] = 0;
			}
		}
	}
	//블럭넣기전 cpymap 초기화

	int c = crushcheck();


	if (c == 2) {
		bx -= kx;
	}
	// 벽에 닿을시

	if (c == 0) {
		for (int iy = 0; iy < 4; iy++) {
			for (int ix = 0; ix < 4; ix++) {
				if (block[b_t][b_r][ix][iy] != 0) {
					cpymap[bx + ix][by + iy] = block[b_t][b_r][ix][iy];
				}

			}
		}
	}
	//블럭 누적x


	//블럭 누적시
	if (c == 1) {


		while (1)
		{

			kbin(0);
			c = crushcheck();
			if (c == 2) {
				bx -= kx;
			}

			for (int iy = 0; iy < mapy; iy++) {
				for (int ix = 0; ix < mapx; ix++) {
					if (cpymap[ix][iy] != 1 && cpymap[ix][iy] != 3) {
						cpymap[ix][iy] = 0;
					}
				}
			}

			for (int iy = 0; iy < 4; iy++) {
				for (int ix = 0; ix < 4; ix++) {
					if (block[b_t][b_r][ix][iy] != 0) {
						cpymap[bx + ix][by + iy] = block[b_t][b_r][ix][iy];
					}

				}
			}

			map_drow();

			if (c == 0)
				return;

			if (speed()) {
				break;
			}

		}

		if (c == 0)
			return;


		for (int iy = 0; iy < 4; iy++) {
			for (int ix = 0; ix < 4; ix++) {
				if (block[b_t][b_r][ix][iy] != 0) {
					cpymap[bx + ix][by + iy] = 1;
				}
			}
		}
		bx = 6;
		by = 1;
		b_t = rand() % 7;

	}







	//블럭 누적시


	return;
}



int xyw(int x, int y) {
	COORD pos;
	pos.X = 0;
	pos.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("                                  ☆score : %d☆ \n", score);
	pos.X = 0;
	pos.Y = 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("                               ------------ DEADLINE");

	return 0;
	////////////////////////////////////////블럭 좌표값
}


void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}




int speed() {
	cti = clock();
	double s;
	s = (double)(cti - ti);
	if (s > hard) {
		ti = cti;
		return 1;
	}
	else
		return 0;

}


int crushcheck() {

	if (kx != 0)
		for (int iy = 0; iy < 4; iy++) {
			for (int ix = 0; ix < 4; ix++) {
				if (block[b_t][b_r][ix][iy] != 0) {
					if ((cpymap[bx + ix][by + iy] + block[b_t][b_r][ix][iy]) == 3) {
						return 2;
					}
				}
			}
		}


	for (int iy = 0; iy < 4; iy++) {
		for (int ix = 0; ix < 4; ix++) {
			if (block[b_t][b_r][ix][iy] != 0) {
				if ((cpymap[bx + ix][by + iy + 1] + block[b_t][b_r][ix][iy]) == 3) {
					return 1;
				}
			}
		}
	}


	return 0;
}





int lineremove() {
	int f = 0;
	int cnt = 0;


	for (int iy = 22; iy > 2; iy--) {
		for (int ix = 1; ix < 15; ix++) {
			if (cpymap[ix][iy] == 1) {
				f++;
			}
		}
		if (f == 14) {
			cnt++;
			score++;
			if (score % 2 == 0) {
				if (hard - 200 != 0) {
					hard -= 200;
				}
			}
			for (int cx = 1; cx < 15; cx++)
				cpymap[cx][iy] = 0;
		}
		f = 0;
	}

	if (cnt > 0) {
		while (cnt) {
			for (int iy = 22; iy > 2; iy--) {
				for (int ix = 1; ix < 15; ix++) {
					if (cpymap[ix][iy] != 0) {
						f++;
					}
				}
				if (f == 0) {
					for (int cy = iy; cy > 2; cy--) {
						for (int cx = 1; cx < 15; cx++) {
							cpymap[cx][cy] = cpymap[cx][cy - 1];

						}
					}
				}
				f = 0;
			}
			cnt--;
		}
		return 1;
	}



	return 0;

}



void kbin(int g) {
	kx = 0;
	ky = 0;

	int k1 = 0;

	if (_kbhit()) {
		k1 = _getch();
		k1 = _getch();
		switch (k1) {
		case left:
			kx--;
			break;
		case up:
			if (g == 1) {
				blockr();
				break;
			}
		case right:
			kx++;
			break;
		case down:
			if (g == 1) {
				ky++;
				break;
			}
		}
	}

	bx += kx;
	by += ky;

}


void blockr() {

	b_r = (b_r + 1) % 4;
	for (int iy = 0; iy < 4; iy++) {
		for (int ix = 0; ix < 4; ix++) {
			if (block[b_t][b_r][ix][iy] != 0) {
				if ((cpymap[bx + ix][by + iy + 1] + block[b_t][b_r][ix][iy]) == 3) {
					b_r -= 1;
				}
			}
		}
	}
	// 회전시 충돌이 일어난다면 회전 취소
}



int gameover() {

	for (int ix = 1; ix < 14; ix++) {
		if (cpymap[ix][3] == 1)
			return 1;

	}

	return 0;
}




