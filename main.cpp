
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <bits/stdc++.h>

#include <mylib.h>
#include "menu.h"
#include "khaibao.h"

#define USERNAME "thuan"
#define PASSWORD "123"

#define Enter 13
#define Backspace 8
#define Left 75
#define Right 77
#define Up 72
#define Down 80

using namespace std;

int soLuongDocGia = 0;

// Code by Thuanncuteeeee

// Edit Value Input

void CapsLock(string &str, int x, int y){
	for(int i=0; i<str.length(); i++){
		if(i == 0){
			if(str[i] >= 97 && str[i] <= 122)
				str[i] -= 32;
		}
		else{
			if(str[i-1] == ' '){
				if(str[i] >= 97 && str[i] <= 122)
					str[i] -= 32;
			}
		}
	}
	if(x>0 && y>0){
		gotoxy(x, y);
		cout << str;
	}
}

bool SearchNumber(int key){
    int box[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
	for(int i=0; i<10; i++)
		if(box[i] == key)
			return true;

	return false;
}

bool SearchAlphabet(int key, bool isName){
	int	box[] = {113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 97, 115, 100, 102, 103, 104, 106, 107,
		108, 122, 120, 99, 118, 98, 110, 109, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
		81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 32
	};
	for(int i=0; i<53; i++)
		if(isName){
			if(box[i] == key && key != 32)
				return true;

		}
		else
			if(box[i] == key)
				return true;

	return false;
}

string InsertString(string str, int index, char insert){
	string res = str;
	res += " ";
	for(int i=index+1; i<str.length()+1; i++)
		res[i] = str[i-1];

	res[index] = insert;
	return res;
}

void DeleteOne(string &str,int index){
    for(int i=index; i<str.length(); i++)
		str[i] = str[i+1];
	str[str.length()-1] = '\0';
}

string NumberToString(unsigned long long num){
	ostringstream res;
	res << num;
	return res.str();
}

unsigned long long StringToNumber(string str){
	unsigned long long res;
	stringstream temp(str);
	temp >> res;
	return res;
}

void ToLowerCase(char &c){
	if(c >65 && c<=90)
		c += 32;
}

int GetKey(){
	char key;
	key = _getch();
	if (key == -32 || key == 0)
		return -_getch();
	else return key;
}

// Edit Value

string EditValue(string str, bool isNumber, int x, int y, bool isName){
	ShowConsoleCursor(true);
    unsigned long long Number;
    int CurrentCusor = str.length() + x;
	string temp = str;
	char c;

	gotoxy(x ,y);
	cout << str;

	while (1){
		if(isNumber)
			c = _getch();
		else{
			Number = GetKey();
			c = Number;
		}

		// x-> cout string -> Min current cusor: x
		if(c == Backspace){
			CurrentCusor--;
			if(CurrentCusor < x)
				CurrentCusor = x;

			// range delete [x -> x + temp.length()]
			// CurrentCusor = temp.length() + x ???
			// function handle delete 1 char [0 -> length()-1]

			DeleteOne(temp, CurrentCusor - x);
			gotoxy(x, y);

			if(isNumber && CurrentCusor == 0){
				temp = "1";
				CurrentCusor = 1;
				cout << temp;
			}
			else
				cout << temp;

			gotoxy(CurrentCusor, y);
		}

		// Case Left -- Right
		// Range Left -- Right: x -> x + temp.length()
		// Case left min: x
		if(isNumber){
			if(c == Left){
				if(CurrentCusor - 1 >= x)
					CurrentCusor--;

				gotoxy(CurrentCusor-1, y);
			}

			if(c == Right){
				if(CurrentCusor + 1 < x + temp.length())
					CurrentCusor++;
				gotoxy(CurrentCusor, y);
			}
		}
		else{
			if(Number == -75){
				if(CurrentCusor - 1 >= x)
					CurrentCusor--;
				gotoxy(CurrentCusor-1, y);
			}

			if(Number == -77){
				if(CurrentCusor + 1 <= x + temp.length())
					CurrentCusor++;
				gotoxy(CurrentCusor, y);
			}
		}

		if(c == Up && isNumber){
			temp = NumberToString(StringToNumber(temp) + 1);
			gotoxy(x, y);

			cout << temp;
			CurrentCusor = temp.length() + x;
		}

		if(c == Down && isNumber){
			CurrentCusor = temp.length() + x;

			if(StringToNumber(temp) - 1 == 0)
				temp = "1";
			else
				temp = NumberToString(StringToNumber(temp) - 1);

			gotoxy(x, y);
			cout << "                                ";

			gotoxy(x, y);
			cout << temp;
		}

		// Case Add
		if(isNumber){
			if(SearchNumber((int)c)){
				CurrentCusor++;
				if(CurrentCusor <= temp.length() + x){
					temp = InsertString(temp, CurrentCusor - 1 - x, c);

					gotoxy(x, y);
					cout << temp;
					gotoxy(CurrentCusor, y);
				}
				else if(CurrentCusor >= temp.length() + x){
					temp += c;
					gotoxy(x, y);
					cout << temp;
					gotoxy(CurrentCusor - 1, y);
				}
			}
		}
		else{
			if(SearchAlphabet(c, isName)){
				CurrentCusor++;
				if(CurrentCusor <= temp.length() + x){
					temp = InsertString(temp, CurrentCusor - 1 - x, c);

					gotoxy(x, y);
					cout << temp;
					gotoxy(CurrentCusor, y);
				}
				else if(CurrentCusor >= temp.length() + x){
					temp += c;
					gotoxy(CurrentCusor - 1, y);
					cout << c;
				}
			}
		}

		if (c == Enter)
			return temp;
	}
}

// End Edit Value Input

/* End Cong Diem */

/*    DAU SACH VA CAC HAM LIEN QUAN ( Mang con tro)    */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LOAD FILE
void OpenFile_DAUSACH(DS_DAUSACH &ds, char *fileName){
	DAU_SACH sach;
	FILE *f;
	f = fopen(fileName, "rb");

	if (f == NULL)
		cout << "Load file err"; return;

	ds.soLuong = 0;
	while (fread(&sach, sizeof(DAU_SACH), 1, f) != 0){
		ds.dausach[ds.soLuong] = new DAU_SACH;
		*ds.dausach[ds.soLuong] = sach;
		ds.soLuong++;
	}
	fclose(f);
	cout << "load file success";
	
}

// SAVE TO FILE
void SaveFile_DAUSACH(DS_DAUSACH ds, char *fileName){
//	FILE *f;
//	if ((f = fopen(filename, "wb")) == NULL){
//		cout << "Load file err"; return;
//	}
//	for (int i=0; i<ds.soLuong; i++)
//		fwrite(ds.dausach[i], sizeof(DAU_SACH), 1, f);
//
//	fclose(f);
//	cout << "Save file success";
}

int SearchDS_DAUSACH(DS_DAUSACH &DAUSACH, string maISBN){
   for (int i=0; i<DAUSACH.soLuong; i++){
      if (DAUSACH.dausach[i]->ISBN == maISBN)
			return i;
   }
   return -1;
}

bool isFull(DS_DAUSACH &ds){
	return ds.soLuong == MAX_DAU_SACH ? true : false;
}

string RandomISBN(DS_DAUSACH &ds){
	srand(time(NULL));
	string code;
	string box = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	while(true){
		for (int i = 0; i < 6; i++)
			code += box[rand() % 26];
	      	
		if(!SearchDS_DAUSACH(ds, code) != -1)
			return code;
	}
}

// Todo List
//void RandomMaSach(string isbn, int soLuong, ptrDMSach dms){
//	srand(time(NULL));
//	int viTriDau = 1;
//	string masach;
//	for(int i=0;i<soLuong;i++){
//		masach = isbn + random();
//		AddAt(dms, masach, viTriDau, i);
//		viTriDau++;
//	}
//}

void displayDS_DAUSACH(DS_DAUSACH &ds){
	system("color f0");
	
	char menu[6][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nha Xuat Ban",
		"The Loai"
	};
	SetColor(4);
	int step = 45;
	for(int i=0; i<6; i++){
		gotoxy(step, 4);
		if(i == 4)
			step += 18;
		else
			step += 14;
		cout << menu[i];
	}
	
	SetColor(0);
	for(int i=0; i<ds.soLuong; i++){
		SetColor(0);
		gotoxy(45, 6+i);
		cout << ds.dausach[i]->ISBN;
		gotoxy(59, 6+i);
		cout << ds.dausach[i]->tensach;
		gotoxy(73, 6+i);
		cout << ds.dausach[i]->tacgia;
		gotoxy(87, 6+i);
		cout << ds.dausach[i]->sotrang;
		gotoxy(101, 6+i);
		cout << ds.dausach[i]->NXB;
		gotoxy(119, 6+i);
		cout << ds.dausach[i]->theloai;
	}
}

// ADD 1 CUON SACH
bool NhapDauSach(DS_DAUSACH &ds, DAU_SACH &sach){
	int x = 50 , count = 2, stepCls = 6;
	
//	int SoLuong
	ShowConsoleCursor(true);
	Draw_frame(X, Y);
	
	cls(15, 20, 3, 34);
	for(int i=1; i<=5; i++){
		gotoxy(17, count + stepCls);
		stepCls += 3;
		cout << "              ";
	}
	
	while (1){
	Nhap:
		DrawBorder(1, 3, 38, 35, 3);
		DrawBorder(41, 3, 90, 35, 3);
		displayDS_DAUSACH(ds);
		
		gotoxy(3, count + 3);
		sach.ISBN = RandomISBN(ds);
		SetColor(4);
		cout << "Ma sach       ";
		SetColor(0);
		DrawBorder(16, count + 2, 20, 2, 3);
		gotoxy(23, count + 3);
		cout << sach.ISBN << "\n";
		
		SetColor(4);
		gotoxy(3, count + 6);
		cout << "Nam xuat ban";
		gotoxy(3, count + 9);
		cout << "So trang";
		gotoxy(3, count + 12);
		cout << "Ten sach";
		gotoxy(3, count + 15);
		cout << "Ten tac gia";
		gotoxy(3, count + 18);
		cout << "The loai";
		
		SetColor(0);
		DrawBorder(16, count + 5, 20, 2, 3);
		DrawBorder(16, count + 8, 20, 2, 3);
		DrawBorder(16, count + 11, 20, 2, 3);
		DrawBorder(16, count + 14, 20, 2, 3);
		DrawBorder(16, count + 17, 20, 2, 3);
		// So luong
		DrawBorder(16, count + 20, 20, 2, 3);
		// Vi tri
		DrawBorder(16, count + 23, 20, 2, 3);
		
		/*         Handle Input          */
		// NXB
		gotoxy(17, count + 6);
		cin >> sach.NXB;
		
		// So Trang
		gotoxy(17, count + 9);
		int tempSoTrang;
		InputNumber(sach.sotrang);
		
		// Ten Sach
		fflush(stdin);
		gotoxy(17, count + 12);
		getline(cin, sach.tensach);
		
		// Tac Gia
		gotoxy(17, count + 15);
		getline(cin, sach.tacgia);
		
		// The Loai
		gotoxy(17, count + 18);
		getline(cin, sach.theloai);

		// So Luong
		gotoxy(17, count + 21);
//		InputNumber(sach);
		cout << "\n";
		char exit;
		gotoxy(10, 23);
		cout << "An ENTER De Tiep Tuc.";
		gotoxy(8, 24);
		cout << "An Phim Bat Ki De Thoat!";

		if(exit = getch() == Enter){
			gotoxy(7, 26);
			SetColor(12);
			cout << "Them Dau Sach Thanh Cong!";
			return true;
		}
		else
			return false;
   }
	return true;
}

// DELETE SACH THEO ISBN
void XoaSach(DS_DAUSACH &ds, string ISBN, int index){
   if (SearchDS_DAUSACH(ds, ISBN) != -1){
   	//      displayDS_DAUSACH("Ma so sach khong co trong danh sach");
		cout << "Ma sach kh ton tai";
		return;
   }
   else{
		// display ISBN
		SetColor(4);
		cout << "Chon Ma Sach Can Xoa!";
		char listMenu[ds.soLuong][6];
		for(int i=0; i<ds.soLuong; i++){
			cout << ds.dausach[i]->ISBN;
		}
		
		int index = SearchDS_DAUSACH(ds, ISBN);
		delete ds.dausach[index];
		for (int j=index+1; j<ds.soLuong; j++)
			ds.dausach[j - 1] = ds.dausach[j];
		ds.soLuong--;
   }
}

// ADD NHIEU CUON SACH SACH
void NhapDSDS(DS_DAUSACH &ds){
	DAU_SACH sach;
	if (ds.soLuong == MAX_DAU_SACH){
		displayStr("Danh sach day!!", 50, 5); return;
 	}

	while (ds.soLuong < MAX_DAU_SACH){
		ds.dausach[ds.soLuong] = new DAU_SACH;
		bool temp = NhapDauSach(ds, sach);
		*ds.dausach[ds.soLuong] = sach;
		ds.soLuong++;
		
		if (!temp){
			break;
		}
	}
}

/* KET THUC DAU SACH */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* DOC GIA VA CAC HAM LIEN (CAY NHI PHAN TIM KIEM) */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InitTree(Tree &t){
	t = NULL;
}

int randomID(){
	string box = "0123456789";
	char res[6];
	for(int i=0; i<6; i++){
		int indexRand = rand()% 10;
		if(indexRand == 0 && i == 0)
			indexRand = rand()% 9 + 1;
		res[i] = box[indexRand];
	}

	return atoi(res);
}

// Tree -> array
void ChuyenCayThanhMang(Tree t, DocGia a[], int &i){
	if (t == NULL)
		return;

	ChuyenCayThanhMang(t->pLeft, a, i);
	a[i++] = t->info;
	ChuyenCayThanhMang(t->pRight, a, i);
}

// Sort Tree
//int Compare_DG(DocGia *dg1, DocGia *dg2){
//	if(mode == MODE_MaThe){
//		return dg1->Mathe-dg2->Mathe;
//	}else if(mode == MODE_Ten){
//		if(strcmp(dg1->Ten,dg2->Ten)==0){
//			return strcmp(dg1->Ho,dg1->Ho);
//		}else return strcmp(dg1->Ten,dg2->Ten);
//	}
//	return 0;
//}


// Compare Sort (dg1, dg2: -> 1: dg1>dg2, 2: dg1>dg2, 3: dg1==dg2
int Compare(DocGia dg1, DocGia dg2){
	if(dg1.ten < dg2.ten)
		return 1;
	else if(dg1.ten == dg2.ten){
		if(dg1.ho < dg2.ho)
			return 1;
	}
	
	return false;
}

// Quick sort DOC GIA
int partition_DOCGIA(DocGia arr[], int start, int end){
    string pivot = arr[end].ten;
    DocGia t;
    
    int  P_index = start;

    for(int i=start; i<end; i++){
    	// compare
		if(Compare(arr[i], arr[end])){
		    t = arr[i];
		    
		    arr[i] = arr[P_index];
		    arr[P_index] = t;
		    P_index++;
		}
	}

	t = arr[end];
	arr[end] = arr[P_index];
	arr[P_index] = t;

	return P_index;
 }
 
void Quicksort_DOCGIA(DocGia *arr, int start, int end){
	if(start < end){
		int P_index = partition_DOCGIA(arr, 0, soLuongDocGia - 1);
		Quicksort_DOCGIA(arr, start, P_index-1);
		Quicksort_DOCGIA(arr, P_index+1, end);
	}
}
// End Quick sort DOC GIA

// Buble Sort DOC GIA

void BubleSort_DOCGIA(DocGia *arr){
	if(arr == NULL)
		return;
		
	DocGia temp;
	for(int i=0; i<soLuongDocGia; i++)
		for(int j=i; j<soLuongDocGia-i-1; j++){
			if(Compare(arr[j], arr[j+1])){
				temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
}

// End Buble Sort DOC GIA

void displayThe_DOCGIA(Tree t, bool isSort){
	system("color f0");
	if(t == NULL)
		return;
		
	SetColor(3);
	int x = 0, row = soLuongDocGia == 1 ? 6 : 7, y = 0;
	DocGia* a = new DocGia[soLuongDocGia];
	ChuyenCayThanhMang(t, a, x); // Tree -> Array
	if(isSort)
		BubleSort_DOCGIA(a);
		
	for(int i=0; i<soLuongDocGia; i++){
		y = row + i;

		gotoxy(50, y);
		cout << a[i].maThe;
		gotoxy(65, y);
		cout << a[i].ho;
		gotoxy(82, y);
		cout << a[i].ten;

		gotoxy(99, y);
		cout << "       ";
		gotoxy(99, y);
		cout << a[i].phai;
		gotoxy(116, y);

		if(a[i].trangThai == 0)
			cout << "Hoat Dong";
		else{
			SetColor(12);
			cout << "Bi Khoa";
		}
	}
	
}

//int Count_Node_Tree(Tree &root){
//	int count = 0;
//	Tree *p;
//	while( root ){
//		if( root->pLeft == NULL ){
//			count = count + 1;
//			root = root->pRight;
//		}
//		else{
//			p = root->pLeft;
//			while(p->pRight && p->pRight != root ){
//				p = p->pRight;
//			}
//			if( p->pRight == NULL ){
//				p->pRight = root;
//				count = count + 1;
//				root = root->pLeft;
//			}
//			else{
//				p->pRight = NULL;
//				root = root->pRight;
//			}
//		}
//	}
//	 return count;
//}

string Sex(){
	ShowConsoleCursor(false);
	char input, arr[2][10] = {
		"Nam",
		"Nu"
	};
	int chon = 0, step = 20;
	reset:
		step = 20;
	for(int i=0; i<2; i++){
		gotoxy(step, 14);
		if(i == chon){
			SetColor(12);
			cout << arr[i];
		}
		else{
			SetColor(3);
			cout << arr[i];
		}
		step += 16;
	}
	
	while(1){
		input = getch();
		switch(input){
			case Left:
				chon = 0;
				goto reset;
				break;
				
			case Right:
				chon = 1;
				goto reset;
				break;
				
			case Enter:
				return chon == 0 ? "Nam" : "Nu";
		}
	}
}

bool AddDocGia(Tree &t, int ID, int &RowTable){
	int x = 50 , count = 2, step = 50;
	string tempInput;

	ShowConsoleCursor(true);
	DrawBorder(1, 3, 45, 35, 0); // draw border left
	DrawBorder(48, 3, 82, 35, 0); // draw border right

	gotoxy(17, count + 3);
	cout << "                       ";
	gotoxy(17, count + 6);
	cout << "                       ";
	gotoxy(17, count + 9);
	cout << "                       ";
	gotoxy(17, count + 12);
	cout << "                       ";

	// cls bottom
	cls(15, 20, 3, 34);

	if(t == NULL) {
		CAYNHIPHANTK_TheDocGia* p = new CAYNHIPHANTK_TheDocGia;
		p->info.maThe = ID;

		// handle input
		while(1){
			char menu[5][20] = {
				"Ma Doc Gia",
				"Ho",
				"Ten",
				"Phai(Nam/Nu)",
				"Trang Thai"
			};
			SetColor(12);
			for(int i=0; i<5; i++){
				gotoxy(step, 4);
				if(i == 0)
					step += 15;
				else
					step += 17;
				cout << menu[i];
			}

			SetColor(12);
			gotoxy(3, 5);
			cout << "Ma Doc Gia";

			DrawBorder(16, count + 2, 27, 2, 3);
			gotoxy(27, 5);
			SetColor(3);
			cout << p->info.maThe;

			gotoxy(17, count + 3);
			SetColor(12);
			gotoxy(3, count + 6);
			cout << "Ho";
			gotoxy(3, count + 9);
			cout << "Ten";
			gotoxy(3, count + 12);
			cout << "Phai(Nam/Nu)";

			// Ho
			DrawBorder(16, count + 5, 27, 2, 3);
			// Ten
			DrawBorder(16, count + 8, 27, 2, 3);
			// Gioi Tinh
			DrawBorder(16, count + 11, 27, 2, 3);

			// Ho
			InputHo:
			SetColor(3);
			gotoxy(17, count + 6);
			p->info.ho = EditValue("", false, 17, 8, false);
			if(p->info.ho.length() == 0)
				goto InputHo;

			// Ten
			InputTen:
			gotoxy(17, count + 9);
//			getline(cin, p->info.ten);
			p->info.ten = EditValue("", false, 17, 11, true);
			if(p->info.ten.length() == 0)
				goto InputTen;
				
			// Phai
			gotoxy(17, count + 12);
			p->info.phai = Sex();
			gotoxy(20, 14);
			cout << "                     ";
			gotoxy(28, 14);
			SetColor(3);
			cout << p->info.phai;

			p->info.trangThai = 0;
			p->pLeft = NULL;
			p->pRight = NULL;
			soLuongDocGia++;

			// edit before add(Ho & Ten)
			char input;
			bool exit = true;
			int chon = 3, step;
			
			// reset edit input
			reset:
			step = 7;
			for(int i=0; i<3; i++){
				if(i == chon){
					DrawBorder(16, step, 27, 2, 12);
					if(step + 3 != 16)
						DrawBorder(16, step + 3, 27, 2, 3);
					
					input = getch();
					switch(input){
						// case ENTER
						case Enter:
							switch(chon){
								case 0:
									p->info.ho = EditValue(p->info.ho, false, 17, 8, false);
									CapsLock(p->info.ho, 17, 8);
									ShowConsoleCursor(false);
									break;
									
								case 1:
									p->info.ten = EditValue(p->info.ten, false, 17, 11, true);
									CapsLock(p->info.ten, 17, 11);
									ShowConsoleCursor(false);
									break;
									
								case 2:
									gotoxy(17, count + 12);
									gotoxy(20, 14);
									cout << "                    ";
									DrawBorder(16, count + 11, 27, 2, 3);
									p->info.phai = Sex();
									SetColor(3);
									gotoxy(20, 14);
									cout << "                    ";
									gotoxy(28, 14);
									cout << p->info.phai;
									break;
							}
							break;
						// end case ENTER
					}
				}
				else{
					DrawBorder(16, step, 27, 2, 3);
				}
				step += 3;
			}
			
			while(1){
				input = getch();
				switch(input){
					case Up:
						if(chon > 0){
							chon--;
							goto reset;
						}
						break;

					case Down:
						if(chon + 1 < 3){
							chon++;
							goto reset;
						}
						break;
						
					case Enter:
						// Add node tree
						t = p;
						
						// Display new row in table
						SetColor(3);
						gotoxy(50, RowTable);
						cout << "             ";
						gotoxy(50, RowTable);
						cout << p->info.maThe;
						
						gotoxy(65, RowTable);
						cout << "             ";
						gotoxy(65, RowTable);
						cout << p->info.ho;
						
						gotoxy(82, RowTable);
						cout << "             ";
						gotoxy(82, RowTable);
						cout << p->info.ten;

						gotoxy(99, RowTable);
						cout << "       ";
						gotoxy(99, RowTable);
						cout << p->info.phai;
						
						gotoxy(116, RowTable);
						cout << "       ";
						gotoxy(116, RowTable);
						cout << "Hoat Dong";
						// End display new row in table

						SetColor(3);
						gotoxy(14, 17);
						cout << "An ENTER De Tiep Tuc.";
						gotoxy(12, 18);
						cout << "An Phim Bat Ki De Thoat!";

						if(char exit = getch() == Enter){
							if(RowTable + 1 < 30)
								RowTable++;
							else{
								RowTable = 6;
								// cls table
//								DrawBorder(48, 3, 82, 35, 0);
								cls(4, 34, 49, 80);
							}
							SetColor(12);
							gotoxy(12, 20);
							cout << "Them Doc Gia Thanh Cong!";
							Sleep(500);
							return true;
						}
						else
							return false;

				}
			}
			// end edit before add(Ho & Ten)

		}
		// end handle input
		
	}
	else if (t->info.maThe > ID)
		AddDocGia(t->pLeft, ID, RowTable);
	else if(t->info.maThe < ID)
		AddDocGia(t->pRight, ID, RowTable);

}

//int AddAt(ptrDMSach &head, string masach, int vitri, int position){
//    if(position == 0 || head == NULL){
//        InsertFirst(head, vitri, masach);
//    }else{
//        int k = 1;
//        ptrDMSach p = head;
//        while(p != NULL && k != position){
//            p->pHead = p->pHead->pNext;
//            ++k;
//        }
//
//        if(k != position){
//            InsertLast(head, vitri, masach);
//        }else{
//            ptrDMSach temp = Newnode();
//            temp->pHead->pNext = p->pHead->pNext;
//            p->pHead->pNext = temp->pHead;
//        }
//    }
//    return 1;
//}

void DeleteNodeLeftRight(Tree& temp, Tree& t) {
	if (t->pLeft != NULL) {
		DeleteNodeLeftRight(temp, t->pLeft);
	}
	else {
		temp->info = t->info;
		temp = t;
		t = t->pRight;
	}
}

void XoaDocGia(Tree& t, int x){
	if(x > t->info.maThe)
		XoaDocGia(t->pRight, x);
		
	else if(x < t->info.maThe)
		XoaDocGia(t->pLeft, x);
		
	else{
		Tree tam = t;
		if(t->pLeft == NULL)
			t = t->pRight;

		else if(t->pRight == NULL)
			t = t->pLeft;

		else if(t->pLeft != NULL && t->pRight != NULL)
			DeleteNodeLeftRight(tam, t->pRight);

		delete tam;
	}

	cout << "Xoa doc gia thanh cong";
}

/* KET THUC DOC GIA */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool login(){
 	system("cls");
	Normal();
	char userName[100], passWord[40];
	Draw_frame(X, Y);
	
	while(true){
		gotoxy(50, 1);
		SetColor(0);
		Nhaplai:
			gotoxy(50, 4);
			SetColor(12);
			cout << "User name :                                                  ";
			gotoxy(50, 5);
			cout << "Password  :                                                  ";
			gotoxy(50, 7);
			cout << "                                                             ";

			SetColor(0);
			gotoxy(62, 4);
			
			gets(userName);
			gotoxy(62, 5);
			char *pwd = Pwd();
			if( strcmp(userName, USERNAME) == 0 && strcmp(pwd, PASSWORD) == 0 ){
				return true;
			}
			else if(strcmp(userName, USERNAME) == 0 && strcmp(pwd, PASSWORD) != 0){
				SetColor(3);
				gotoxy(55, 7);
				cout << "Sai Mat Khau!";
				Sleep(1000);
				goto Nhaplai;
			}
			else if(strcmp(userName, USERNAME) != 0){
				SetColor(3);
				gotoxy(55, 7);
				cout << "Sai Ten Dang Nhap!";
				Sleep(1000);
				goto Nhaplai;
			}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* MENU VA CAC HAM LIEN QUAN*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Cau a: them xoa sua THE DOC GIA
void draw_case1(Tree t){
	system("color f0");
	ShowConsoleCursor(false);
	int chon, res, arr[4] = {55, 57, 54, 61}, ISBN, RowTable = 6;
	bool case1 = true, isSort = false;
	
	while (1){
		SetBGColor(3);
		cls(3, 39, 1, 130);
		chon = MenuThuancutee(CauA, 4, 0, 29, arr, 50);
		SetBGColor(15);
		switch (chon){
		case 1:
			cls(4, 30, 30, 50);
  			while(case1 = AddDocGia(t, randomID(), RowTable)){
					
				if(case1 == false)
					break;
			}
			break;
		case 2:
//			displayThe_DOCGIA(t);
			break;
		case 3:
			
			break;
		case 4:
			return;
		}
		Sleep(300);
   }
}

// Cau c: NHap thong tin dau sach va danh ma sach tu dong
void draw_case2(){
	DS_DAUSACH ds;
	
	system("color f0");
	cls(4, 35, 2, 110);
	int chon, flag = 1, arr[7] = {54, 57, 57, 59, 59, 55, 62};

	while (1){
		chon = MenuThuancutee(CauC, 7, 0, 30, arr, 50);
		switch (chon){
		case 1:
			system("cls");
			NhapDSDS(ds);
			break;
		case 2:
//			system("cls");
//			SaveFile_DAUSACH(ds, "C:\\Users\\thuancutee\\Desktop\\DauSach.txt");
//			displayDS_DAUSACH(ds);
			break;
		case 3:
//			draw_case3();
			break;
		case 7:
			return;
		}
		Sleep(300);
   }
}

// case EXIT
void exit(){
	cls(4, 35, 3, 80);
	char str1[] = "- Cam On Da Su Dung Chuong Trinh -";
	char str2[] = "- Xin Chao Va Hen Gap Lai! -";
	SetColor(3);
	gotoxy(48, 6);
	for(int i=0; i<strlen(str1); i++){
		cout << str1[i];
		Sleep(50);
	}
	gotoxy(51, 7);
	for(int i=0; i<strlen(str2); i++){
		cout << str2[i];
		Sleep(50);
	}
	for(int i=8; i<36; i++){
		gotoxy(0, i);
		cout << "           ";
	}
}

void Menu(char td[][100], Tree t){
	system("color f0");
	cls(4, 35, 2, 100);
	int chon, arr[4] = {57, 58, 58, 61};
	while (1){
		chon = MenuThuancutee(td, 4, 5, 22, arr, 53);
		switch (chon){
		case 1:
			draw_case1(t);
			break;
		case 2:
			draw_case2();
			break;
		case 3:
//			draw_case2();
			break;
		// case exit
		case 4:
			exit();
			return;
		}
		Sleep(1000);
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	Normal();
	SetConsoleTitle("Quan li thu vien - Thuancutee");
	SetBGColor(15);
	
	DS_DAUSACH ds;
	DAU_SACH sach;
	
	Tree t;

//	if(login()){
		InitTree(t);
		Menu(listMainMenu, t);
//	}

	return 0;
}
