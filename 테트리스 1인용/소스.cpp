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

// �� ũ��
#define mapx 16
#define mapy 24

#define debug 1  //�ʵ� ������ �� ���� = 2  ������ ���� = 1


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
int score = 0; //���� ����
int kx = 0, ky = 0; // Ű���� �Է°�
int bx, by;; // �� ��ǥ��
int b_t = 0; //��� ������ ���� 
int b_r = 0; //��� ȸ���� ���� 

int orgmap[mapx][mapy] = { 0 }; /////////////�ʵ� ũ��

int cpymap[mapx][mapy] = { 0 }; /////////////ī���� �ʵ�

int chanse = 0; //�ٴ� �浹�� ������ ��ȸ


int block[7][4][4][4] = {
{{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0},//�簢�� block[0]
 {0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0},{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0},//���ں� block[1]
 {0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0},{0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0}},
{{0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,0,2,0,0,2,2,0,0,2,0,0},//������ block[2]
 {0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0},{0,0,0,0,0,0,2,0,0,2,2,0,0,2,0,0}},
{{0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0},{0,0,0,0,2,0,0,0,2,2,0,0,0,2,0,0},//�����ݴ��� block[3]
 {0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0},{0,0,0,0,2,0,0,0,2,2,0,0,0,2,0,0}},
{{0,0,0,0,0,0,2,0,2,2,2,0,0,0,0,0},{0,0,0,0,2,2,0,0,0,2,0,0,0,2,0,0},//�Ҹ�� block[4]
 {0,0,0,0,0,0,0,0,2,2,2,0,2,0,0,0},{0,0,0,0,0,2,0,0,0,2,0,0,0,2,2,0}},
{{0,0,0,0,2,0,0,0,2,2,2,0,0,0,0,0},{0,0,0,0,0,2,0,0,0,2,0,0,2,2,0,0},//����� block[5]
 {0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,0},{0,0,0,0,0,2,2,0,0,2,0,0,0,2,0,0}},
{{0,0,0,0,0,2,0,0,2,2,2,0,0,0,0,0},{0,0,0,0,0,2,0,0,0,2,2,0,0,2,0,0},//�̸�� block[6]
 {0,0,0,0,0,0,0,0,2,2,2,0,0,2,0,0},{0,0,0,0,0,2,0,0,2,2,0,0,0,2,0,0}}
}; //��ϸ�� ����





int main() {
	char y = 0;
	srand(time(NULL));//���� ���� �ʱ�ȭ

	int cloor = rand() % 15;

	if (cloor == 0) {
		cloor += 1;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cloor);
	printf("������������������������������\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                 ����Ʈ����2022��                     ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��                                                      ��\n");
	printf("��  -Push any key for play-                             ��\n");
	printf("��                                   made by anjaemin   ��\n");
	printf("������������������������������\n");


	y = _getch();


	while (1) {

		system("cls");

		score = 0;
		int g = 0;
		srand(time(NULL));//���� ���� �ʱ�ȭ
		bx = 6;        //�ʱ� �� ��ǥ
		by = 1;
		ti = clock();   //�ʱ� ��Ÿ�� üũ
		CursorView();    // Ŀ�� ����
		int nanido = 0;

		map_make();  //�ʵ� ����
		map_drow(); // �ʱ� �ʵ� ���
		blockdrow();//�� ���


		xyw(0, 0);
		while (1) {


			kbin(1); //Ű���� �ޱ�

			blockdrow();//�� ���
			map_drow();//�ʵ� ���

			if (lineremove() == 1) {
				xyw(0, 0);
			}


			if (speed()) { // �ð��� �� ���
				by++;
			}

			g = gameover();//���� ���� üũ

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
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);     ///Ŀ�� ����                                                                                  
}




void map_make() {

	for (int iy = 0; iy < mapy; iy++) {//�ʵ� �ʱ�ȭ
		for (int ix = 0; ix < mapx; ix++) {
			cpymap[ix][iy] = 0;
		}
	}

	for (int i = 0; i < 16; i++) {
		orgmap[i][0] = 1;     ///õ�� ����
		cpymap[i][0] = 1;
	}
	for (int i = 0; i < 16; i++) {
		orgmap[i][23] = 1;    ///�ٴ� �ʵ� ����
		cpymap[i][23] = 1;
	}
	for (int i = 0; i < 24; i++) {
		orgmap[15][i] = 1;    ///������ �ʵ� ����
		cpymap[15][i] = 1;
	}
	for (int i = 0; i < 24; i++) {
		orgmap[0][i] = 1;     ///�޺� �ʵ� ����  
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


	//org cpy ��
	for (int ix = 0; ix < mapx; ix++) {
		for (int iy = 0; iy < mapy; iy++) {
			if (orgmap[ix][iy] != cpymap[ix][iy]) {
				ch = 1;
			}                                          //org cpy ��
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
					printf("��");
#elif (debug == 2)    
					printf("%d ", cpymap[ix][iy]);
#endif
				}
				else if (cpymap[ix][iy] == 2 || cpymap[ix][iy] == 3) {
#if (debug == 1)
					printf("��");
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

	//�ʵ� ��ȭ�� ������ cpy ���

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
	//���ֱ��� cpymap �ʱ�ȭ

	int c = crushcheck();


	if (c == 2) {
		bx -= kx;
	}
	// ���� ������

	if (c == 0) {
		for (int iy = 0; iy < 4; iy++) {
			for (int ix = 0; ix < 4; ix++) {
				if (block[b_t][b_r][ix][iy] != 0) {
					cpymap[bx + ix][by + iy] = block[b_t][b_r][ix][iy];
				}

			}
		}
	}
	//�� ����x


	//�� ������
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







	//�� ������


	return;
}



int xyw(int x, int y) {
	COORD pos;
	pos.X = 0;
	pos.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("                                  ��score : %d�� \n", score);
	pos.X = 0;
	pos.Y = 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("                               ------------ DEADLINE");

	return 0;
	////////////////////////////////////////�� ��ǥ��
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
	// ȸ���� �浹�� �Ͼ�ٸ� ȸ�� ���
}



int gameover() {

	for (int ix = 1; ix < 14; ix++) {
		if (cpymap[ix][3] == 1)
			return 1;

	}

	return 0;
}




