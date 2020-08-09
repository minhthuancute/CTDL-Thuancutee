
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <bits/stdc++.h>

#include <mylib2.h>
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
#define Space 32
#define Esc 27
#define F1 59
#define F2 60
#define F3 61


using namespace std;

// Global var
int soLuongDocGia = 0, maThe; // maThe -> global
// String to display new row in table DOC GIA
string firstName, lastName, SexTable;

/* Code by Thuanncuteeeee */

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
	if(x > 0 && y > 0){
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
string EditValue(string str, bool isNumber, int x, int y, bool isName){ // x: 17
	ShowConsoleCursor(true);
    unsigned long long Number;
    int CurrentCusor = str.length() + x, countSpace = 0;
	string temp = str; // string result
	char c;
	bool isFirst = true;

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
			DeleteOne(temp, CurrentCusor - x - 1);
			CurrentCusor--;
			if(CurrentCusor < x)
				CurrentCusor = x;

			// range delete [x -> x + temp.length()]
			// CurrentCusor = temp.length() + x ???
			// function handle delete 1 char [0 -> length()-1]

			if(isNumber && CurrentCusor == 0){
				temp = "1";
				CurrentCusor = 1;
				cout << temp;
			}
			else{
				gotoxy(x, y);
				cout << temp;
			}

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
			cout << "                    ";

			gotoxy(x, y);
			cout << temp;
		}

		// Case Add value
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
					gotoxy(CurrentCusor, y);
				}
			}
		}
		else{ // Case Add value string
			// Default countSpace = 0
			if(c == Space)
				//countSpace = countSpace + 1 <= 1 ? countSpace++ : 0; // 0 -> 1
				countSpace++;
			else{
				countSpace = 0;
				isFirst = false;
			}
			
			if(SearchAlphabet(c, isName)){
				// Prevent space first
				if(!isFirst){
					if(countSpace <= 1){
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
				
			}
		}

		if (c == Enter && temp != "")
			return temp;
	}
}
// End Edit Value Input

int ContinueOrExit(int y){
	ShowConsoleCursor(false);
	char input, arr[2][10] = {
		"Luu",
		"Thoat"
	};
	int chon = 0, step = 20;
	reset:
		step = 20;
		for(int i=0; i<2; i++){
			gotoxy(step, y);
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
				return chon == 0 ? 59 : 27;
		}
	}
}

/*    DAU SACH VA CAC HAM LIEN QUAN ( Mang con tro)    */
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// LOAD FILE
//void OpenFile_DAUSACH(DS_DAUSACH &ds, char *fileName){
//	DAU_SACH sach;
//	FILE *f;
//	f = fopen(fileName, "rb");
//
//	if (f == NULL)
//		cout << "Load file err"; return;
//
//	ds.soLuong = 0;
//	while (fread(&sach, sizeof(DAU_SACH), 1, f) != 0){
//		ds.dausach[ds.soLuong] = new DAU_SACH;
//		*ds.dausach[ds.soLuong] = sach;
//		ds.soLuong++;
//	}
//	fclose(f);
//	cout << "load file success";
//	
//}


int SearchDS_DANHMUCSACH(DS_DANHMUCSACH &dsdms, string masach){
	for(ptrDMSach p = dsdms.pHead; p != NULL; p = p->pNext){
		if(masach == p->data.maSach){
			return 1;
		}
	}
	return -1;
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


void Traverser(DS_DANHMUCSACH &head, int i, int &j){
    for(ptrDMSach p = head.pHead; p != NULL; p = p->pNext){
    	gotoxy(i + 5, j);
    	cout<<p->data.maSach;
    	gotoxy(i + 25, j);
    	cout<<p->data.trangThai;
    	gotoxy(i + 45, j);
    	cout<<p->data.viTri;
    	j++;
	}
}


string CatLayMaDauSach(string str) {
	string str1;
	for (int i = 0; i < str.length(); i++) {
		if (i == 6) {
			break;
		}
		str1 += str[i];
	}
	return str1;
}

void displayDS_DANHMUCSACH(DS_DAUSACH &dsds){
	system("color f0");
	int count = 6;
	char menu[3][20] = {
		"Ma Sach",
		"Trang Thai",
		"Vi Tri"
	};
	int arrX[] = {48+5, 48+25, 48+45};
	
	SetColor(12);
	for(int i=0; i<3; i++){
		gotoxy(arrX[i], 4);
		cout << menu[i];
	}
	for(int i = 0; i < dsds.soLuong; i++){
		Traverser(dsds.dausach[i]->DMS, 48, count);
		count += i;
	}
}

void displayDS_DAUSACH(DS_DAUSACH &ds){
	system("color f0");
	
	char menu[8][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nam",
		"The Loai",
		"SL Dau Sach",
		"Vi Tri"
	};
	int arrX[] = {43, 52, 65, 75, 88, 95, 107, 120};
	
	SetColor(12);
	for(int i=0; i<8; i++){
		gotoxy(arrX[i], 4);
		cout << menu[i];
	}

	for(int i=0; i<ds.soLuong; i++){
		i == ds.soLuong - 1 ? SetColor(3) : SetColor(0);
		gotoxy(arrX[0], 6 + i);
		cout << ds.dausach[i]->ISBN;
		gotoxy(arrX[1], 6 + i);
		cout << ds.dausach[i]->tensach;
		gotoxy(arrX[2], 6 + i);
		cout << ds.dausach[i]->tacgia;
		gotoxy(arrX[3], 6 + i);
		cout << ds.dausach[i]->sotrang;
		gotoxy(arrX[4], 6 + i);
		cout << ds.dausach[i]->NXB;
		gotoxy(arrX[5], 6 + i);
		cout << ds.dausach[i]->theloai;
		gotoxy(arrX[6], 6 + i);
		cout<<ds.dausach[i]->DMS.SoLuong<<"\t\t";
		gotoxy(arrX[7], 6 + i);
		cout<<ds.dausach[i]->DMS.pHead->data.viTri<<endl;
	}
}

string TheLoai(){
	ShowConsoleCursor(false);
	char c, source[][50] = { // lenght: 5
		"Tinh Cam",
		"Tieu Thuyet",
		"Truyen Tranh",
		"Khoa Hoc&Xa Hoi",
		"Sach Giao Khoa"
	};
	
	int arrX[] = {21, 20, 19, 18, 18}, current = 0;
	while(1){
		gotoxy(18, 20);
		cout << "                 ";
		gotoxy(arrX[current], 20);
		cout << source[current];
		
		c = GetKey();
		switch(c){
			case -75: // Case left
				current--;
				if(current < 0)
					current = 4;
					
				break;
				
			case -77: // Case Right
				current++;
				if(current > 4)
					current = 0;
					
				break;
				
			case Enter:
				return source[current];

		}
	}

}

ptrDMSach Newnode(DANH_MUC_SACH dms){   
	ptrDMSach p = new NODE_DanhMucSach;
	if(p == NULL){
		return NULL;
	}
	p->data = dms;
	p->pNext = NULL;
	return p;
}

void InsertFirstDMS(DS_DANHMUCSACH &list, ptrDMSach p){
	if(list.pHead == NULL){
		list.pHead = p;
	}
	else{
		p->pNext = list.pHead;
		list.pHead = p;
	}
}

string random(){
    string box = "0123456789";
	int indexRand;
	string res;
	for(int i=0; i<4; i++){
		indexRand = rand() % 10;
		if(indexRand == 0 && i == 0){
			indexRand = rand() % 9 + 1;
		}
		res += box[indexRand];
	}

	return res;
}

void SinhMaSachTuDong(string isbn, int soLuong,DS_DANHMUCSACH &dsDMS , string vtDau){
	srand(time(NULL));
	DANH_MUC_SACH dms;
	string masach;
	for(int i = 0;i < soLuong ; i++){
		masach = isbn + random();
		dms.maSach = masach;
		dms.trangThai = 0;
		dms.viTri = vtDau;
		ptrDMSach ptrDMS;
		ptrDMSach p = Newnode(dms);
		
		InsertFirstDMS(dsDMS, p);
		dsDMS.SoLuong++;
		
	}
}


// ADD 1 CUON SACH
bool NhapDauSach(DS_DAUSACH &ds, DAU_SACH &sach){
	sach.ISBN = RandomISBN(ds);
	DS_DANHMUCSACH ds_dms;
	int x = 50, count = 2;
	int SoLuong = 1;
	string ViTriDau = "";
	
	ShowConsoleCursor(false);
	Draw_frame(X, Y);
	
	DrawBorder(1, 3, 38, 35, 3); // Draw Table Left
	DrawBorder(41, 3, 90, 35, 3); // Draw Table Right
	
	cls(5, 32, 3, 34); // cls Table left
	displayDS_DAUSACH(ds);

	SetColor(3);
	int y = 4;
	for(int i=1; i<=8; i++){ // count = 2 -> 4, 7, 10
		DrawBorder(13, y, 23, 2, 3);
		y += 3;
	}
		
	char exit, menu[8][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nam",
		"The Loai",
		"So Luong",
		"Vi Tri"
	};
	
//	5, 8, 11
	SetColor(12);
	y = 5;
	for(int i=0; i<8; i++){
		gotoxy(3, y);
		cout << menu[i];
		y += 3;
	}
		
	SetColor(3);
	gotoxy(23, count + 3);
	cout << sach.ISBN << "\n";
	
//	The loai
	gotoxy(14, 20);
	cout << "<";
	gotoxy(35, 20);
	cout << ">";
	
//	y: 8, 11, 14, 17 -> 26
	gotoxy(17, count + 12);
	sach.tensach = EditValue("", false, 14, 8, false); // Ten Sach
	
	gotoxy(17, count + 15);
	sach.tacgia = EditValue("", false, 14, 11, false); // Tac Gia
	
	gotoxy(17, count + 9);
	sach.sotrang = StringToNumber(EditValue("", true, 14, 14, false)); // So Trang
	
	InputNXB: // Nan Xuat Ban
	gotoxy(17, count + 6);
//	cout << "            ";
	sach.NXB = StringToNumber(EditValue(sach.NXB == NULL ? "" : NumberToString(sach.NXB), true, 14, 17, false)); 
//	if(NumberToString(sach.NXB).length() != 4)
//		goto InputNXB;
	
	gotoxy(17, count + 18);
	sach.theloai = TheLoai(); // The Loai

	gotoxy(17, count + 21);
	SoLuong = StringToNumber(EditValue("", true, 14, 23, false)); // So Luong

	gotoxy(17, count + 24);
	ViTriDau = EditValue("", false, 14, 26, false); 
//	ViTriDau = StringToNumber(EditValue("", true, 14, 26, false)); // Vi Tri Dau
	sach.demSoLanMuon = 0;
	SinhMaSachTuDong(sach.ISBN, SoLuong, ds_dms, ViTriDau);
	sach.DMS = ds_dms;
	
//	Edit Before Add
//  reset edit input
	int chon = 8, countEnter = 0;
	char input;
	SetColor(3);
	gotoxy(14, 29);
	cout << "An F1 De Luu!";
	gotoxy(12, 30);
	cout << "An ESC De Thoat!";
	
	reset:
		ShowConsoleCursor(false);
		SetColor(3);
		y = 4;
		
		for(int i=0; i<8; i++){ // count = 2 -> 4, 7, 10,...
			i == chon ? DrawBorder(13, y, 23, 2, 12) : DrawBorder(13, y, 23, 2, 3);
			y += 3;
		}
		
	while(1){
		input = getch(); // Edit 8 field
		switch(input){
			case Up:
				if(chon > 1)
					chon--;
				goto reset;
				break;

			case Down:
				if(chon + 1 < 8)
					chon++;
				goto reset;
				break;

			
			// case ENTER
			case Enter:

				switch(chon){
					case 1: // Ten Sach
						gotoxy(17, count + 12);
						sach.tensach = EditValue(sach.tensach, false, 14, 8, false);
						ShowConsoleCursor(false);
						break;

					case 2: // Tac Gia
						gotoxy(17, count + 15);
						sach.tacgia = EditValue(sach.tacgia, false, 14, 11, false);
						ShowConsoleCursor(false);
						break;

					case 3: // So Trang
						gotoxy(17, count + 9);
						sach.sotrang = StringToNumber(EditValue(NumberToString(sach.sotrang), true, 14, 14, false));
						ShowConsoleCursor(false);
						break;

					case 4: // Nam Xuat Ban
						gotoxy(17, count + 6);
						sach.NXB = StringToNumber(EditValue(sach.NXB == NULL ? "" : NumberToString(sach.NXB), true, 14, 17, false));
						ShowConsoleCursor(false);
						break;

					case 5: // The Loai
						gotoxy(17, count + 18);
						sach.theloai = TheLoai();
						ShowConsoleCursor(false);
						break;

					case 6: // So Luong
						gotoxy(17, count + 21);
						SoLuong = StringToNumber(EditValue("", true, 14, 23, false));
						ShowConsoleCursor(false);
						break;

					case 7: // Vi Tri Dau
						gotoxy(17, count + 24);
						ViTriDau = StringToNumber(EditValue("", true, 14, 26, false));
						ShowConsoleCursor(false);
						break;

				}
				break;
			// end case ENTER
			
			case F1: // Case Save
				return true;
				
			case Esc:
				return false;

		}
	}
	// End edit before add
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

// DELETE SACH THEO ISBN
void XoaSach(DS_DAUSACH &ds, string ISBN, int index){
   if (SearchDS_DAUSACH(ds, ISBN) != -1){
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

void XoaDau(DS_DANHMUCSACH &l){
	if (l.pHead == NULL){
		return;
	}
	ptrDMSach p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}

bool XoaNodeCoKhoaBatKy(DS_DANHMUCSACH &l, string masach){
	if (l.pHead == NULL){
		return false;
	}
	if (l.pHead->data.maSach == masach){
		XoaDau(l);
		return true;
	}

	ptrDMSach g = new NODE_DanhMucSach;
	for (ptrDMSach k = l.pHead; k != NULL; k = k->pNext){
		if (k->data.maSach == masach){
			g->pNext = k->pNext; 
			delete k; 
			return true;
		}
		g = k;
	}

}


void XoaMaSachChuaMuon (DS_DAUSACH &ds){
	DS_DANHMUCSACH dsdms;
	string masach;
	int index = 0;
	system("cls");
	DrawBorder(1, 3, 38, 35, 3); // Draw Table Left
	DrawBorder(41, 3, 90, 35, 3); // Draw Table Right
	
	displayDS_DANHMUCSACH(ds);
	gotoxy(2, 5);
	cout << "Nhap ma sach can xoa :" ;
	DrawBorder(2, 7, 30, 2, 3);
	ShowConsoleCursor(true);
	gotoxy(3, 8);
	getline(cin, masach);
	string isbn = CatLayMaDauSach(masach);
	for(int i = 0; i < ds.soLuong; i++){
		if(ds.dausach[i]->ISBN == isbn){
			dsdms = ds.dausach[i]->DMS;
			index = i;
		}
	}
	if(XoaNodeCoKhoaBatKy(dsdms, masach)){
		ds.dausach[index]->DMS.SoLuong--;
		ds.dausach[index]->DMS = dsdms;
		displayStr("Xoa Thanh Cong!", 50, 10);
		Sleep(500);
	}
	
//	for(NODE_DanhMucSach *d = dsdms.pHead; d != NULL ; d = d->pNext){
//		if(d->data.maSach == masach){
//			DeleteLastDMS(d);
//			ds.dausach[index]->DMS.SoLuong--;
//			ds.dausach[index]->DMS = dsdms;
//			displayStr("Xoa Thanh Cong!", 50, 10);
//			Sleep(500);
//		}
//	}
}


/* KET THUC DAU SACH */
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* DOC GIA VA CAC HAM LIEN (CAY NHI PHAN TIM KIEM) */
////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read + Write File DOC GIA
void SaveFile(char *FileName, int size, string *arr){
	ofstream save;
	save.open(FileName);
	for(int i=0; i<size; i++)
		save << arr[i] << endl;

	save.close();
}

void ReadFile(char *FileName, int size, string *arr){
	ifstream read;
	read.open(FileName);
	for(int i=0; i<size; i++)
		read >> arr[i];

	read.close();
}

void InitTree(Tree &t){
	t = NULL;
}

void FileToTree(Tree &t){
	ifstream read;
	char *fileName = "file.dat";
	read.open(fileName);
		
	int i = 0;
//	soLuongDocGia++;
	while(read != NULL){
//		if(t == NULL){
			CAYNHIPHANTK_TheDocGia* p = new CAYNHIPHANTK_TheDocGia;
			read >> p->info.maThe;

			read >> p->info.ho;

			read >> p->info.ten;

			read >> p->info.phai;
			p->info.trangThai = 0;
			p->pLeft = NULL;
			p->pRight = NULL;
			soLuongDocGia++;
			
			t = p;
//		}

	}

	read.close();

//	if (t == NULL) {
//		CAYNHIPHANTK_TheDocGia* p = new CAYNHIPHANTK_TheDocGia;
//		p->info.maThe = MaRandom;
//
//		getline(cin, p->info.ho);
//
//		getline(cin, p->info.ten);
//
//		getline(cin, p->info.phai);
//		p->info.trangThai = 0;
//		p->pLeft = NULL;
//		p->pRight = NULL;
//		soLuongDocGia++;
//		t = p;
//	}
//	else {
//		if (t->info.maThe > MaRandom) {
//			ThemDocGia(t->pLeft, MaRandom);
//		}
//		if (t->info.maThe < MaRandom) {
//			ThemDocGia(t->pRight, MaRandom);
//		}
//	}

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
void TreeToArray(Tree t, DocGia a[], int &i){
	if (t == NULL)
		return;

	TreeToArray(t->pLeft, a, i);
	a[i++] = t->info;
	TreeToArray(t->pRight, a, i);
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

// sort dau sach
// Quick sort DOC GIA
//int partition_DOCGIA(DocGia arr[], int start, int end){
//    string pivot = arr[end].ten;
//    DocGia t;
//    
//    int  P_index = start;
//
//    for(int i=start; i<end; i++){
//    	// compare
//		if(Compare(arr[i], arr[end])){
//		    t = arr[i];
//		    
//		    arr[i] = arr[P_index];
//		    arr[P_index] = t;
//		    P_index++;
//		}
//	}
//
//	t = arr[end];
//	arr[end] = arr[P_index];
//	arr[P_index] = t;
//
//	return P_index;
// }
// 
//void Quicksort_DOCGIA(DocGia *arr, int start, int end){
//	if(start < end){
//		int P_index = partition_DOCGIA(arr, 0, soLuongDocGia - 1);
//		Quicksort_DOCGIA(arr, start, P_index-1);
//		Quicksort_DOCGIA(arr, P_index+1, end);
//	}
//}
// End Quick sort DOC GIA



// Buble Sort DOC GIA

bool CompareWord(string str1, string str2){
	int length = min(str1.length(), str2.length());
	// a=97, b=98 -> a < b
	// alphabet a, b, c, d,... -> z
	for(int i=0; i<length; i++){
		// a, b, c, d, ... -> z
		if( str1.substr(i, 1) > str2.substr(i, 1))
			return true;
		else
			return false;
	}

}

// Compare Sort (dg1, dg2: -> 1: dg1>dg2, 2: dg1>dg2, 3: dg1==dg2
bool CompareName(DocGia dg1, DocGia dg2){
	if(dg1.ho == dg2.ho && dg1.ten == dg2.ten)
		return false;
	else if(dg1.ten == dg2.ten){
		if(dg1.ho > dg2.ho)
			return true;
	}
	else
	if(dg1.ten > dg2.ten)
		return true;
}

void SortByName_DOCGIA(DocGia *arr){
	if(arr == NULL)
		return;
		
	DocGia temp;
	for(int i=0; i<soLuongDocGia; i++)
		for(int j=0; j<soLuongDocGia - 1; j++){
			if(CompareName(arr[j], arr[j + 1])){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
}

void SortByID_DOCGIA(DocGia *arr){
	if(arr == NULL)
		return;

	DocGia temp;
	for(int i=0; i<soLuongDocGia; i++)
		for(int j=0; j<soLuongDocGia - 1; j++){
			if(arr[j].maThe > arr[j+1].maThe){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
}

// End Buble Sort DOC GIA

void displayThe_DOCGIA(Tree t, int &RowTable){
	if(t == NULL)
		return;
	system("color f0");
	cls(5, 36, 49, 80); // cls table right
		
	int x = 0, row = 6;
	DocGia* arr = new DocGia[soLuongDocGia];
	TreeToArray(t, arr, x); // Tree -> Array
		
	for(int i=0; i<soLuongDocGia; i++){
//		50 62 92 110 121
		if(arr[i].maThe != maThe){
			gotoxy(50, row);
			cout << arr[i].maThe;
			gotoxy(62, row);
			cout << arr[i].ho;
			gotoxy(92, row);
			cout << arr[i].ten;

			gotoxy(110, row);
			cout << "       ";
			gotoxy(110, row);
			cout << arr[i].phai;
			gotoxy(121, row);

			if(arr[i].trangThai == 1)
				cout << "Hoat Dong";
			else{
				SetColor(12);
				cout << "Bi Khoa";
			}
			row++;

		}
	}
	
}

void displayEdit_DOCGIA(int SortBy, DocGia *arr){
	if(arr == NULL)
		return;
	system("color f0");
	cls(7, 36, 49, 80); // cls table right
	int x = 0, row = 6;

	// 0: Sort by Name, 1: Sort by ID
	SortBy == 0 ? SortByName_DOCGIA(arr) : SortByID_DOCGIA(arr);

	for(int i=0; i<soLuongDocGia; i++){
//		50 62 92 110 121
		if(arr[i].maThe != maThe){
			gotoxy(50, row);
			cout << arr[i].maThe;
			gotoxy(62, row);
			cout << arr[i].ho;
			gotoxy(92, row);
			cout << arr[i].ten;

			gotoxy(110, row);
			cout << "       ";
			gotoxy(110, row);
			cout << arr[i].phai;
			gotoxy(121, row);

			if(arr[i].trangThai == 0)
				cout << "Hoat Dong";
			else{
				SetColor(12);
				cout << "Bi Khoa";
			}
			row++;
		}
	}

}

//void Search_DOCGIA(Tree t, int MaThe, DocGia &dg){
//	if(t == NULL)
//		return;
//		
//	if (t->info.maThe == MaThe){
//		dg = t->info; return;
//	}
//	else{
//		if (MaThe > t->info.maThe)
//			Search_DOCGIA(t->pRight, MaThe, dg);
//			
//		if (MaThe < t->info.maThe)
//			Search_DOCGIA(t->pLeft, MaThe, dg);
//	}
//}

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

string Sex(int y){
	ShowConsoleCursor(false);
	char input, arr[2][10] = {
		"Nam",
		"Nu"
	};
	int chon = 0, step = 20;
	reset:
		step = 20;
		for(int i=0; i<2; i++){
			gotoxy(step, y);
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



void HeaderTable_DOCGIA(int row){
	char menu[5][20] = {
		"ID",
		"Ho",
		"Ten",
		"Phai",
		"Trang Thai"
	};
//	50 62 92 110 121
	gotoxy(50, row); 
	cout << menu[0]; // Ma doc gia
	gotoxy(62, row);
	cout << menu[1]; // Ho
	gotoxy(92, row);
	cout << menu[2]; // Ten
	gotoxy(110, row);
	cout << menu[3]; // Phai
	gotoxy(121, row);
	cout << menu[4]; // Trang thai
	SetColor(12);
}

bool TimDocGia(Tree t, int MaThe, Tree& tam) {
	if (t == NULL){
		return false;
	}
	if (t->info.maThe == MaThe){
		tam = t;
		return true;
	}
	if (MaThe > t->info.maThe){
		TimDocGia(t->pRight, MaThe, tam);
	}
	if (MaThe < t->info.maThe){
		TimDocGia(t->pLeft, MaThe, tam);
	}
	return false;
}

void AddDocGia(Tree &t, int ID, int &RowTable, bool &isExit){
	int x = 50 , count = 2, RowHeader = 4;
	DrawBorder(1, 3, 45, 35, 0);  // draw border left
	DrawBorder(48, 3, 84, 35, 0); // draw border right

	cls(4, 20, 3, 43); // cls bottom

	if(t == NULL) {
		CAYNHIPHANTK_TheDocGia* p = new CAYNHIPHANTK_TheDocGia;
		p->info.maThe = ID;

		while(1){
			ShowConsoleCursor(false);
			// Display new row in table
			SetColor(3);
			if(firstName.length() != 0){ // global var
				SetColor(3);
				gotoxy(50, RowTable - 1);
				cout << "             ";
				gotoxy(50, RowTable - 1);
				cout << maThe;

				gotoxy(62, RowTable - 1);
				cout << "             ";
				gotoxy(62, RowTable - 1);
				cout << firstName;

				gotoxy(92, RowTable - 1);
				cout << "             ";
				gotoxy(92, RowTable - 1);
				cout << lastName;

				gotoxy(110, RowTable - 1);
				cout << "       ";
				gotoxy(110, RowTable - 1);
				cout << SexTable;

				gotoxy(121, RowTable - 1);
				cout << "       ";
				gotoxy(121, RowTable - 1);
				cout << "Hoat Dong";
			}
			// End display new row in table
			
			SetColor(12);
			HeaderTable_DOCGIA(RowHeader);

			SetColor(12);
			gotoxy(3, 5);
			cout << "Ma Doc Gia";
			gotoxy(3, count + 6);
			cout << "Ho";
			gotoxy(3, count + 9);
			cout << "Ten";
			gotoxy(3, count + 12);
			cout << "Phai(Nam/Nu)";

			DrawBorder(16, count + 2, 27, 2, 3); // ID
			DrawBorder(16, count + 5, 27, 2, 3); // Ho
			DrawBorder(16, count + 8, 27, 2, 3); // Ten
			DrawBorder(16, count + 11, 27, 2, 3); // Gioi Tinh
			
			gotoxy(27, 5);
			SetColor(3);
			cout << p->info.maThe;
			
			SetColor(3);
			gotoxy(17, count + 6);
			p->info.ho = EditValue("", false, 17, 8, false); // Ho
			CapsLock(p->info.ho, 17, 8);

			gotoxy(17, count + 9);
			p->info.ten = EditValue("", false, 17, 11, true); // Ten
			CapsLock(p->info.ten, 17, 11);
				
			gotoxy(17, count + 12);
			p->info.phai = Sex(14); // Phai
			gotoxy(20, 14);
			cout << "                     ";
			gotoxy(28, 14);
			SetColor(3);
			cout << p->info.phai;

			p->info.trangThai = 1;
			p->info.slSachDangMuon = 0;
	
			p->info.DS_MUONTRA.pHead = NULL;
			p->info.DS_MUONTRA.pLast = NULL;

			p->pLeft = NULL;
			p->pRight = NULL;
			
			// Assign value for global var( firstName, ...)
			firstName = p->info.ho;
			lastName = p->info.ten;
			SexTable = p->info.phai;
			maThe = ID;

			// edit before add(Ho & Ten)
			char input, exit;
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
									firstName = p->info.ho; // global var
									ShowConsoleCursor(false);
									break;
									
								case 1:
									p->info.ten = EditValue(p->info.ten, false, 17, 11, true);
									CapsLock(p->info.ten, 17, 11);
									lastName = p->info.ten; // global var
									ShowConsoleCursor(false);
									break;
									
								case 2:
									gotoxy(17, count + 12);
									gotoxy(20, 14);
									cout << "                    ";
									DrawBorder(16, count + 11, 27, 2, 3);
									p->info.phai = Sex(14);
									SexTable = p->info.phai; // global var
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
			
			SetColor(3);
			gotoxy(14, 17);
			cout << "An F1 De Luu!";
			gotoxy(12, 18);
			cout << "An ESC De Luu Va Thoat!";
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
						
						
					case F1: // Case Add
						t = p;
						
						soLuongDocGia++;
						SetColor(12);
						gotoxy(50, RowTable);
						cout << "             ";
						gotoxy(50, RowTable);
						cout << p->info.maThe;

						gotoxy(62, RowTable);
						cout << "             ";
						gotoxy(62, RowTable);
						cout << p->info.ho;

						gotoxy(92, RowTable);
						cout << "             ";
						gotoxy(92, RowTable);
						cout << p->info.ten;

						gotoxy(110, RowTable);
						cout << "       ";
						gotoxy(110, RowTable);
						cout << p->info.phai;

						gotoxy(121, RowTable);
						cout << "       ";
						gotoxy(121, RowTable);
						cout << "Hoat Dong";
						// End display new row in table
						
						if(RowTable + 1 < 37) // Max row table right: 37, cls right: cls(5, 36, 49, 80);
							RowTable++;
						else{
							RowTable = 7;
							firstName = "";
							cls(5, 36, 49, 80); // cls table right
						}
						
						isExit = true;
						return;
						
					case Esc:
						t = p;
						soLuongDocGia++;
						isExit = false;
						return;
						
				}
			}
			// end edit before add(Ho & Ten)

		}
		// end handle input

	}
	else{
		if (t->info.maThe > ID)
			AddDocGia(t->pLeft, ID, RowTable, isExit);
			
		if(t->info.maThe < ID)
			AddDocGia(t->pRight, ID, RowTable, isExit);
	}

}

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
}

void XoaDocGiaChuaMuonSach(Tree &t){
	int madocgia;
	int row = 48;
	Tree tam;
	bool check = false;
	system("cls");
	DrawBorder(1, 3, 45, 35, 0);  // draw border left
	DrawBorder(48, 3, 84, 35, 0); // draw border right
	SetColor(12);
	gotoxy(row + 1, 4);
	cout << "Ma Doc Gia";
	gotoxy(row + 15, 4);
	cout << "Ho";
	gotoxy(row + 45, 4);
	cout << "Ten";
	gotoxy(row + 55, 4);
	cout << "Phai(Nam/Nu)";
	gotoxy(row + 70, 4);
	cout << "Trang Thai";
	displayThe_DOCGIA(t, row);
	gotoxy(2, 5);
	cout<<"Nhap ma doc gia can xoa: ";
	DrawBorder(2, 7, 30, 2, 3);
	ShowConsoleCursor(true);
	gotoxy(3, 8);
	cin>>madocgia;
	if(TimDocGia(t, madocgia, tam) == false){
		check = false;
	}
	if(tam->info.DS_MUONTRA.pHead == NULL){
		check = true;
	}
	if(check){
		XoaDocGia(t, madocgia);
		displayStr("Xoa doc gia thanh cong!!", 50, 10);
		soLuongDocGia--;
		Sleep(500);
		return;
	}
	else{
		displayStr("Khong the xoa doc gia!", 50, 10);
		Sleep(500);
		return;
	}
}

// Case Edit DOC GIA
string TrimSpace(string str){
	string res;
	for(int i=0; i < str.length(); i++)
		if(str[i] != ' ')
			res += str[i];
	return res;
}

string UnCapsLock(string str){
	string res = TrimSpace(str);

	for(int i=0; i<res.length(); i++)
		if(res[i] >= 65 && res[i] <= 90)
			res[i] += 32;

	return res;
}

bool Include(string str, string key){
	string SubStr, tempStr, tempKey;
	
	tempStr = UnCapsLock(str);
	tempKey = UnCapsLock(key);

	for(int i=0; i<tempStr.length(); i++){
		SubStr = tempStr.substr(i, key.length());

		if(SubStr == tempKey)
			return true;
	}

	return false;
}

void Search_DOCGIA(DocGia *arr, string InputValue, int &CountSearch, bool &isSearch){
	isSearch = true;
	int row = 9, count = 0;
	
	for(int i=0; i<soLuongDocGia; i++)
		if(Include(arr[i].ten, InputValue))
			count++;
	
	DocGia *res = new DocGia[count];
	
	count = 0;
	for(int i=0; i<soLuongDocGia; i++){
		if(Include(arr[i].ten, InputValue)){
			res[count] = arr[i];
			count++;
		}
	}
	
	gotoxy(3, 3);
	CountSearch = count;
	arr = res;
}

void Edit_DOCGIA(Tree &t, int RowTableEdit){
	if(t == NULL)
		return;
		
	int count = 5, CurrentRow = 6, sizeArr = 0, row = 6, indexArr = 0;
	char input;
	string InputValue = "", SortName = "Name";
	
	cls(5, 36, 49, 80); // cls table right
	
	DrawBorder(1, 6, 45, 32, 0);  // draw border left
	DrawBorder(48, 6, 84, 32, 0); // draw border right
	
	DrawBorder(1, 3, 131, 2, 3); // Draw border search

	SetColor(0);
	gotoxy(3, 4);
	cout << "Tim Doc Gia Theo Ten(F1)"; // -59
	
	DrawBorder(16, count + 2, 27, 2, 3); // ID
	DrawBorder(16, count + 5, 27, 2, 3); // Ho
	DrawBorder(16, count + 8, 27, 2, 3); // Ten
	DrawBorder(16, count + 11, 27, 2, 3); // Gioi Tinh
	
	int RowHeader = 7;
	HeaderTable_DOCGIA(RowHeader);
	gotoxy(50, 6);
	
	DocGia* arr = new DocGia[soLuongDocGia];
	TreeToArray(t, arr, sizeArr); // Tree -> Array

	SortByName_DOCGIA(arr);
	
	int SortBy = 0, countSearch = 0; // Default Sort By Name
	bool isSearch = false;
	
	while(1){
		cls(8, 30, 49, 82); // cls table right
		row = 9;
		countSearch = 0;
		
		SetColor(12);
		gotoxy(3, count + 3);
		cout << "Ma Doc Gia";
		gotoxy(3, count + 6);
		cout << "Ho";
		gotoxy(3, count + 9);
		cout << "Ten";
		gotoxy(3, count + 12);
		cout << "Phai(Nam/Nu)";
		
		gotoxy(50, 8);
		SetColor(3);
		cout << "Sort By " << SortName;

		HeaderTable_DOCGIA(RowHeader);
		
		for(int i=0; i<soLuongDocGia; i++){
			i == indexArr ? SetColor(3) : SetColor(0);
			
			if((Include(arr[i].ten, InputValue) || Include(arr[i].ho, InputValue)))
				countSearch++;
			
			if(isSearch ? (Include(arr[i].ten, InputValue) || Include(arr[i].ho, InputValue)) : true){
				gotoxy(50, row);
				cout << arr[i].maThe;

				gotoxy(62, row);
				cout << arr[i].ho;

				gotoxy(92, row);
				cout << arr[i].ten;

				gotoxy(110, row);
				cout << "       ";

				gotoxy(110, row);
				cout << arr[i].phai;
				gotoxy(121, row);

				if(arr[i].trangThai == 0)
					cout << "Hoat Dong";
				else{
					SetColor(12);
					cout << "Bi Khoa";
				}
				row++;
			}
		}
		
		DrawBorder(1, 3, 131, 2, 3); // Draw border search

		input = getch();
		switch(input){
			case Up:
				if(indexArr - 1 >= 0)
					indexArr--;

				break;
				
			case Down:
				if(isSearch)
					if(indexArr + 1 < countSearch)
						indexArr++;
						
				if(!isSearch)
					if(indexArr + 1 < soLuongDocGia)
						indexArr++;

				break;
				
			case Enter:
				SetColor(3);
				gotoxy(27, count + 3); // count = 5
				cout << arr[indexArr].maThe;
				gotoxy(17, count + 6);
				cout << arr[indexArr].ho;
				gotoxy(17, count + 9);
				cout << arr[indexArr].ten;
				gotoxy(17, count + 12);
				cout << "                     ";
				gotoxy(28, count + 12);
				cout << arr[indexArr].phai;

				EditValue(arr[indexArr].ho, false, 17, 11, false);
				EditValue(arr[indexArr].ten, false, 17, 14, true);
				
				gotoxy(17, 17);
				cout << "                     ";
				arr[indexArr].phai = Sex(17);
				gotoxy(17, 17);
				cout << "                     ";
				gotoxy(28, 17);
				cout << arr[indexArr].phai;

				break;

			// Case search DOC GIA
			case F1:
				gotoxy(3, 4);
				cout << "                                   ";
				gotoxy(3, 4);
				SetColor(0);
				isSearch = true;
				InputValue = EditValue("", false, 3 , 4, true);
				ShowConsoleCursor(false);
				break;
				
			case F2:
				SortByName_DOCGIA(arr);
				SortName = "Name";
				break;
				
			case F3:
				SortByID_DOCGIA(arr);
				SortName = "ID";
				break;
				
			case Esc:
				return;
		}
	}
}

// End Case Edit DOC GIA

/* KET THUC DOC GIA */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//muon sach ne

void MuonSach_Them(Tree &t, DS_DAUSACH &dsds, NODE_DanhMucSach* &n_dms) {
	DAU_SACH ds;
	time_t ti = time(0);   // get time now
	tm* now = localtime(&ti);
	int dayNow = now->tm_mday;
	int monthNow = now->tm_mon + 1;
	int yearNow = (now->tm_year + 1900);
	
	n_dms->data.trangThai = 1;
	t->info.slSachDangMuon++;
	
	ptrMuonTra p = new NODE_MUONTRA;
	if (p == NULL) {
		return;
	}
	p->info.maSach = n_dms->data.maSach;
	p->info.NgayMuon.Nam = yearNow;// nam hien tai
	p->info.NgayMuon.Ngay = dayNow;// ngay hien tai
	p->info.NgayMuon.Thang = monthNow;// thang hien tai
	
	p->info.NgayTra.Nam = 0;
	p->info.NgayTra.Ngay = 0;
	p->info.NgayTra.Thang = 0;
	p->info.trangThai = 0;
	
	p->pLeft = NULL;
	p->pRight = NULL;
	
	if (t->info.DS_MUONTRA.pHead == NULL) {
		t->info.DS_MUONTRA.pHead = p;
		t->info.DS_MUONTRA.pLast = p;
	}
	else {
		t->info.DS_MUONTRA.pLast->pRight = p;
		p->pLeft = t->info.DS_MUONTRA.pLast;
		t->info.DS_MUONTRA.pLast = p;
	}
}


bool LayThongTinSach(DS_DAUSACH dsds, string masach, NODE_DanhMucSach *&n_dms, DAU_SACH *&ds){
	for(int i = 0; i < dsds.soLuong; i++){
		if(CatLayMaDauSach(masach) == dsds.dausach[i]->ISBN){
			for(NODE_DanhMucSach* k = dsds.dausach[i]->DMS.pHead; k != NULL; k = k->pNext){
				if(masach == k->data.maSach){
					ds = dsds.dausach[i];
					n_dms = k;
					return true;
				}
			}
		}
	}
	return false;
}

void XuatMotDocGia(Tree t, int i, int j) {
	SetColor(1);
	gotoxy(j+5, i);
	cout << t->info.maThe<< "\t";
	gotoxy(j+25, i);
	cout << t->info.ho << "\t";
	gotoxy(j+45, i);
	cout << t->info.ten << "\t";
	gotoxy(j+55, i);
	cout << t->info.phai << "\t";
	
	if(t->info.trangThai == 0){
		gotoxy(j+75, i);
		cout<<"Bi Khoa";
	}
	else{
		gotoxy(j+75, i);
		cout<<"Hoat Dong";
	}
}
void XuatSachDangMuonCua1DocGia(Tree t, int i, int row){
	SetColor(1);
	for (NODE_MUONTRA* k = t->info.DS_MUONTRA.pHead; k != NULL; k = k->pRight){
		if (k->info.trangThai == 0){
			gotoxy(row + 5, i + 3);
			cout << k->info.maSach;
			gotoxy(row + 25, i + 3);
			cout << k->info.NgayMuon.Ngay << "/" << k->info.NgayMuon.Thang << "/" << k->info.NgayMuon.Nam<<"\t";
			gotoxy(row + 45, i + 3);
			cout << k->info.NgayTra.Ngay << "/" << k->info.NgayTra.Thang << "/" << k->info.NgayTra.Nam<<"\t";
			if(k->info.trangThai == 0){
				gotoxy(row + 65, i + 3);
				cout<<"Dang Muon";
			}
			i++;
		}
	}
}


void MuonSach(Tree &t, DS_DAUSACH &dsds) {
	int i = 5;
	int row = 39;
	int madg;
	Tree tam;
	DAU_SACH* ds;
	MUON_TRA mt;
	NODE_DanhMucSach* n_dms;
	ptrDMSach dms;
	string masach;
	ShowConsoleCursor(true);
	Draw_frame(X, Y);
	DrawBorder(1, 3, 38, 35, 3); // Draw Table Left
	DrawBorder(row, 3, 90, 35, 3);
//	displayThe_DOCGIA(t, row);
	gotoxy(2, i + 1);
	cout << "Ma doc gia can tim: ";
	DrawBorder(2, i + 3, 20, 2, 3);
	gotoxy(3, i + 4);
	cin >> madg;
	if (madg == 0) {
		return;
	}
	TimDocGia(t, madg, tam);
	
	gotoxy(row + 5, i);
	cout << "Ma Doc Gia";
	gotoxy(row + 25, i);
	cout << "Ho";
	gotoxy(row + 45, i);
	cout << "Ten";
	gotoxy(row + 55, i);
	cout << "Phai(Nam/Nu)";
	gotoxy(row + 75, i);
	cout << "Trang Thai";
	gotoxy(row + 5, i + 1);
	XuatMotDocGia(tam, i + 2, row);
	
	SetColor(3);
	gotoxy(40, 8);
	for (int i = 0; i < 89; i++) {
		cout << char(196);
	}
	SetColor(3);
	gotoxy(60, 9);
	cout<<"DANH SACH CAC SACH MA DOC GIA DANG MUON";
	gotoxy(40, 10);
	for (int i = 0; i < 89; i++) {
		cout << char(196);
	}
	gotoxy(row + 5, i + 7);
	cout << "Ma Sach";
	gotoxy(row + 25, i + 7);
	cout << "Ngay Muon";
	gotoxy(row + 45, i + 7);
	cout << "Ngay Tra";
	gotoxy(row + 65, i + 7);
	cout << "Trang Thai";
	XuatSachDangMuonCua1DocGia(tam, i + 6, row);
	
	if (tam->info.slSachDangMuon < 3 && tam->info.trangThai == 1) {
		SetColor(3);
		gotoxy(2, i + 10);
		cout << "Nhap ma sach can muon: ";
		fflush(stdin);
		DrawBorder(2, i + 13, 20, 2, 3);
		gotoxy(3, i + 14);
		getline(cin, masach);
		bool checkMS = LayThongTinSach(dsds, masach, n_dms, ds), checkM = true;
		if(checkMS == false){
			ShowConsoleCursor(false);
			displayStr("Ma sach khong ton tai", 50, 15);
			Sleep(1000);
			checkM = false;
		}
		for(ptrMuonTra ptrmt = tam->info.DS_MUONTRA.pHead; ptrmt != NULL; ptrmt = ptrmt->pRight){
			cout<<"thu nhat: "<<CatLayMaDauSach(masach)<<"thu hai"<<CatLayMaDauSach(ptrmt->info.maSach);
			if (CatLayMaDauSach(masach) == CatLayMaDauSach(ptrmt->info.maSach)) {
				displayStr("Ma sach thuoc dau sach ma may dang muon, cho nen khong muon duoc nua", 50, 15);
				Sleep(1000);
				checkM = false;
			}
		}
		if(n_dms->data.trangThai == 1){
			displayStr("Ma sach nay dang muon boi doc gia khac, cho nen khong muon duoc nha", 50, 15);
			Sleep(1000);
			checkM = false;
		}
		else if(n_dms->data.trangThai == 2){
			displayStr("Ma sach nay da duoc thanh ly, cho nen khong muon duoc nha", 50, 15);
			Sleep(1000);
			checkM = false;
		}
		if(checkM){
			MuonSach_Them(tam, dsds, n_dms);
			ShowConsoleCursor(false);
			displayStr("Muon thanh cong nha!", 50, 15);
			Sleep(1000);
		}
	}
}

void XuatDauSach(int arrX[], DS_DAUSACH &ds){
	for(int i=0; i<ds.soLuong; i++){
		SetColor(3);
		if(i == 0){
			SetColor(0);
		}
		gotoxy(arrX[0], 6 + i);
		cout << ds.dausach[i]->ISBN;
		gotoxy(arrX[1], 6 + i);
		cout << ds.dausach[i]->tensach;
		gotoxy(arrX[2], 6 + i);
		cout << ds.dausach[i]->tacgia;
		gotoxy(arrX[3], 6 + i);
		cout << ds.dausach[i]->sotrang;
		gotoxy(arrX[4], 6 + i);
		cout << ds.dausach[i]->NXB;
		gotoxy(arrX[5], 6 + i);
		cout << ds.dausach[i]->theloai;
		gotoxy(arrX[6], 6 + i);
		cout<<ds.dausach[i]->DMS.SoLuong;
		gotoxy(arrX[7], 6 + i);
		cout<<ds.dausach[i]->DMS.pHead->data.viTri;
			
	}
}

void XuatDSDauSach(DS_DAUSACH &ds){
	system("color f0");
	gotoxy(60, 2);
	cout<<"DANH SACH DAU SACH";
	char input;
	char menu[8][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nam",
		"The Loai",
		"SL Dau Sach",
		"Vi Tri"
	};
	int arrX[] = {2, 15, 35, 55, 75, 95, 115, 135};
	
	SetColor(12);
	for(int i=0; i<8; i++){
		gotoxy(arrX[i], 4);
		cout << menu[i];
	}
//	int y;
//	while(1){
//		XuatDauSach(arrX,ds);
		for(int i=0; i<ds.soLuong; i++){
			SetColor(3);
			if(i == 0){
				SetColor(0);
			}
			gotoxy(arrX[0], 6 + i);
			cout << ds.dausach[i]->ISBN;
			gotoxy(arrX[1], 6 + i);
			cout << ds.dausach[i]->tensach;
			gotoxy(arrX[2], 6 + i);
			cout << ds.dausach[i]->tacgia;
			gotoxy(arrX[3], 6 + i);
			cout << ds.dausach[i]->sotrang;
			gotoxy(arrX[4], 6 + i);
			cout << ds.dausach[i]->NXB;
			gotoxy(arrX[5], 6 + i);
			cout << ds.dausach[i]->theloai;
			gotoxy(arrX[6], 6 + i);
			cout<<ds.dausach[i]->DMS.SoLuong;
			gotoxy(arrX[7], 6 + i);
			cout<<ds.dausach[i]->DMS.pHead->data.viTri;
				
		}
	getch();
}

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
////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* MENU VA CAC HAM LIEN QUAN*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Cau a: them xoa sua THE DOC GIA
void Menu_DOCGIA(Tree &t){
	system("color f0");
	ShowConsoleCursor(false);
	int chon, res, arr[5] = {55, 54, 57, 61}, ISBN, RowTable, RowTableEdit;
	bool case1;
	
	while (1){
		cls(3, 39, 1, 134);
		chon = MenuThuancutee(CauA, 4, 0, 29, arr, 50);

		firstName = "";
		maThe = NULL;
		RowTable = 6 + soLuongDocGia;
		RowTableEdit = 12 + soLuongDocGia;
		case1 = true;
		
		switch (chon){
		// Case Add DOC GIA
		case 1:
			cls(4, 30, 30, 50);
			displayThe_DOCGIA(t, RowTable);
			while(case1)
				AddDocGia(t, randomID(), RowTable, case1);

			break;
			
		// Case Edit DOC GIA
		case 2:
			Edit_DOCGIA(t, RowTableEdit);
			break;
		case 3:
			XoaDocGiaChuaMuonSach(t);
			break;
		case 4:
			return;
		}
		Sleep(300);
   }
}

void Menu_MUONTRA(Tree &t, DS_DAUSACH &dsds){
	system("color f0");
	ShowConsoleCursor(false);
	int chon, res, arr[4] = {61, 61, 52, 61};
	bool case1;
	
	while (1){
		cls(3, 39, 1, 134);
		chon = MenuThuancutee(CauF, 4, 0, 29, arr, 50);
		case1 = true;
		switch (chon){
		case 1:
			system("cls");
			MuonSach(t, dsds);
			break;
			
		case 2:
//			LietKeSachDangMuonCua1DocGia(t);
//			getch();
//			TraSach();
			break;
		case 3:
			return;
		}
		Sleep(300);
   }
}


// Cau c: NHap thong tin dau sach va danh ma sach tu dong
void Menu_DAUSACH(DS_DAUSACH &ds){
	Tree t;
	DS_DANHMUCSACH dsdms;
	system("color f0");
	cls(4, 35, 2, 110);
	int chon, flag = 1, arr[4] = {59, 55, 57, 62};
	
	char Case_DauSach[4][100] = {
									"Them Dau Sach",
									"Danh Sach Cac Dau Sach",
									"Xoa Mot Dau Sach",
									"Thoat!"
								};

	while (1){
		cls(3, 39, 1, 134);
		chon = MenuThuancutee(Case_DauSach, 4, 0, 30, arr, 50);
		switch(chon){
			case 1:
				system("cls");
				NhapDSDS(ds);
				break;
			case 2:
				system("cls");
				XuatDSDauSach(ds);
				break;
			case 3:
				XoaMaSachChuaMuon(ds);
	//			draw_case3();
				break;
			case 4:
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
		gotoxy(1, i);
		cout << "           ";
	}
}

void Menu(char td[][100], Tree &t, DS_DAUSACH &dsds){
	
	system("color f0");
	cls(4, 35, 2, 100);
	int chon, arr[4] = {57, 58, 58, 61};
	while (1){
		chon = MenuThuancutee(td, 4, 5, 22, arr, 53);
		switch (chon){
		case 1:
			Menu_DOCGIA(t);
			break;
			
		case 2:
			Menu_DAUSACH(dsds);
			break;
			
		case 3:
			Menu_MUONTRA(t, dsds);
			break;

		case 4:
			exit();
			return;
		}
		Sleep(1000);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	Normal();
	SetConsoleTitle("Quan li thu vien - Chosss thuaanj");
	SetBGColor(15);
	
	DS_DAUSACH dsds;
	DAU_SACH sach;
	
	Tree t;

//	if(login()){
		InitTree(t);
		FileToTree(t);
		Menu(listMainMenu, t, dsds);
//	}

	return 0;
}
