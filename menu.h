
#include <bits/stdc++.h>
//#include <mylib.h>

//#define X 134

const int Y = 39;
const int X = 134;

using namespace std;

const int so_item = 10;
const int dong = 6;
const int cot = 40;

// key up
const int Up = 72;
// key down
const int Down = 80;

char listMenu[so_item][100] =  {
								"  1. Nhap the doc gia.                                        ",
								"  2. In danh sach doc gia.                                    ",
								"  3. Nhap thong tin dau sach.                                 ",
								"  4. In danh sach dau sach theo the loai.                     ",
								"  5. Tim sach theo ten.                                       ",
								"  6. Muon sach.                                               ",
								"  7. Tra sach.                                                ",
								"  8. Liet ke cac sach 1 doc gia dang muon.                    ",
								"  9. Danh sach doc gia muon sach qua han(thoi gian giam dan). ",
								"  10. 10 dau sach co so luot muon nhieu nhat.                 "};
								

int MenuDong(char td[][100], int size, int marginLeft){
	cls(4, 35, 2, 60);
	hidecursor();
	Normal();
	Draw_frame(X, Y);
	int chon = 0;
	for (int i=0; i<size; i++){
		SetBGColor(15);
		gotoxy(cot+marginLeft, dong + i);
		cout << td[i];
	}
	HighLight();
	gotoxy(cot+marginLeft, dong + chon);
	cout << td[chon];
	char kytu;
	do{
		kytu = getch();
		if (kytu == -32)
		kytu = getch();

		switch (kytu){
		case Up:
			if (chon > 0){
				Normal();
				gotoxy(cot+marginLeft, dong + chon);
				cout << td[chon];
				chon--;
				HighLight();
				gotoxy(cot+marginLeft, dong + chon);
				cout << td[chon];
			}
			break;
		case Down:
			if (chon + 1 < size){
				Normal();
				gotoxy(cot+marginLeft, dong + chon);
				cout << td[chon];
				chon++;
				HighLight();
				gotoxy(cot+marginLeft, dong + chon);
				cout << td[chon];
			}
			break;
		case 13:
			return chon + 1;
	}
	  // end switch

	} while (1);
}

int MenuThuancutee(char td[][100], int size, int marginLeft, int width, int arr[], int x){
	cls(4, 35, 2, 60);
	hidecursor();
	Draw_frame(X, Y);
	int chon = 0;
			
	reset:
		int step = 6;
		for (int i=0; i<size; i++){

	  		if(i == chon){
	  			SetColor(12);
	  			DrawBorder(x, step, width, 2, 12);
	  			gotoxy(arr[i], step+1);
	  			cout << td[i];
			}
			else{
				SetColor(3);
				DrawBorder(x, step, width, 2, 3);
				gotoxy(arr[i], step+1);
				cout << td[i];
			}
			step += 4;
		}
		
	char kytu;
	int count = 1;
	do{
		kytu = getch();
		if (kytu == -32)
		kytu = getch();

		SetColor(0);
		switch (kytu){
			case Up:
				if (chon > 0){
					chon--;
					goto reset;
				}
				break;
			case Down:
				if (chon + 1 != size){
					chon++;
					goto reset;
				}
				break;
		case 13:
			return chon + 1;
		}

	} while (1);
}

void intro(){
//	Normal();
	SetConsoleTitle("Quan li thu vien - Thuancutee");
	char a[1000]=" - QUAN LI THU VIEN - NHOM 26     ", b[1000],c[40];
	strcpy(b, a);
	strcat(a, b);
	int strl = strlen(a);
	for(int i=0; i<strl; i++){
		strncpy(c, a+i, 30);
		c[30] = 0;
		Sleep(90);
		gotoxy(50, 1); cout << c;
		int per = (i*102/strl);
		Sleep(0);
		gotoxy(i+25,Y/2); printf("%c %d%%", 219, per);
	}
	gotoxy(45, 1); cout << b;
}

