
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
#define Space 32
#define Esc 27
#define F1 59
#define F2 60
#define F3 61
#define F4 62

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
			else{
				if(str[i] >= 65 && str[i] <= 71)
					str[i] += 32;
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

bool SearchAlphabetSecond(int key, bool isName){
	int	box[] = {113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 97, 115, 100, 102, 103, 104, 106, 107,
		108, 122, 120, 99, 118, 98, 110, 109, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
		81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 32, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57
	};
	for(int i=0; i<63; i++)
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
string EditValue(string str, bool isNumber, int x, int y, bool isName, bool isPoss){ // x: 17
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

//			gotoxy(x, y);
//			cout << "                    ";

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
			
			if(isPoss ? SearchAlphabetSecond(c, isName) : SearchAlphabet(c, isName)){
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

/*    DAU SACH VA CAC HAM LIEN QUAN ( Mang con tro)    */
//////////////////////////////////////////////////////////////////////////////////////////////////////////

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

string CatLayMaDauSach(string str){
	string res;
	for(int i=0; i<6; i++)
		res += str[i];

	return res;
}

//void displayDS_DANHMUCSACH(DS_DAUSACH &dsds){
//	system("color f0");
//	int count = 6;
//	char menu[3][20] = {
//		"Ma Sach",
//		"Trang Thai",
//		"Vi Tri"
//	};
//	int arrX[] = {48+5, 48+25, 48+45};
//	
//	SetColor(12);
//	for(int i=0; i<3; i++){
//		gotoxy(arrX[i], 4);
//		cout << menu[i];
//	}
//	for(int i = 0; i < dsds.soLuong; i++){
//		Traverser(dsds.dausach[i]->DMS, 48, count);
//		count += i;
//	}
//}

void displayDS_DAUSACH(DS_DAUSACH &ds){ // Pagination ???
	system("color f0");
	
	char menu[8][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nam",
		"The Loai",
		"So Luong",
		"Vi Tri"
	};
	int arrX[] = {38, 48, 72, 96, 106, 113, 129, 140}, PageNum = ds.soLuong/31;
	
	SetColor(12);
	gotoxy(38, 37);
	cout << "Trang " << PageNum + 1;
	
	for(int i=0; i<8; i++){
		gotoxy(arrX[i], 4);
		cout << menu[i];
	}

	int row = 6, start = (ds.soLuong/31)*31; // 27 + 6 = 33
//	gotoxy(45, 15);
//	cout << "test sl " << ds.soLuong;
	for(int i=start; i<ds.soLuong; i++){
		if(row + 1 == 37){ // Pagination
			row = 6;
			cls(6, 37, 38, 108); // cls Table Right
			PageNum++;
			SetColor(12);
			gotoxy(38, 37);
			cout << "Trang " << PageNum + 1;
		}
		
		i == ds.soLuong - 1 ? SetColor(3) : SetColor(0);
		gotoxy(arrX[0], row);
		cout << ds.dausach[i]->ISBN;

		gotoxy(arrX[1], row);
		cout << ds.dausach[i]->tensach;

		gotoxy(arrX[2], row);
		cout << ds.dausach[i]->tacgia;

		gotoxy(arrX[3], row);
		cout << ds.dausach[i]->sotrang;
		gotoxy(arrX[4], row);

		cout << ds.dausach[i]->NXB;
		gotoxy(arrX[5], row);

		cout << ds.dausach[i]->theloai;
		gotoxy(arrX[6], row);
		cout<<ds.dausach[i]->DMS.SoLuong<<"\t\t";

		gotoxy(arrX[7], row);
		cout<<ds.dausach[i]->DMS.pHead->data.viTri<<endl;

		row++;
	}
}

string TheLoai(){
	ShowConsoleCursor(false);
	char c, source[][50] = { // lenght: 5
		"Tinh Cam",
		"Tieu Thuyet",
		"Truyen Tranh",
		"Khoa Hoc",
		"Sach Giao Khoa",
	};
	
	int arrX[] = {13, 12, 12, 14, 10}, current = 0;
	while(1){
		gotoxy(5, 26);
		cout << "                         ";
		gotoxy(arrX[current], 26);
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
	if(p == NULL)
		return NULL;

	p->data = dms;
	p->pNext = NULL;
	return p;
}

void InsertFirstDMS(DS_DANHMUCSACH &list, ptrDMSach p){
	if(list.pHead == NULL)
		list.pHead = p;
	else{
		p->pNext = list.pHead;
		list.pHead = p;
	}
}

string random(){
    string box = "0123456789";
	int indexRand;
	string res;
	srand(time(NULL));
	for(int i=0; i<4; i++){
		indexRand = rand() % 10;
		if(indexRand == 0 && i == 0)
			indexRand = rand() % 9 + 1;

		res += box[indexRand];
	}

	return res;
}

void SinhMaSachTuDong(string isbn, int soLuong,DS_DANHMUCSACH &dsDMS , string vtDau){
	srand(time(NULL));
	DANH_MUC_SACH dms;
	string masach;
	
	for(int i=0; i<soLuong; i++){
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

// Save FILE
void SaveFile_DAUSACH(DS_DAUSACH &dsds){
    ofstream FileOut;
	DS_DANHMUCSACH dsdms;
	
	FileOut.open("DauSach.txt", ios::out);
	FileOut << dsds.soLuong << endl;

	for (int i=0; i<dsds.soLuong; i++){
		FileOut << dsds.dausach[i]->ISBN << "/";
		FileOut << dsds.dausach[i]->tacgia << "/";
		FileOut << dsds.dausach[i]->tensach << "/";
		FileOut << dsds.dausach[i]->theloai << "/";
		FileOut << dsds.dausach[i]->NXB << "/";
		FileOut << dsds.dausach[i]->demSoLanMuon << "/";
		FileOut << dsds.dausach[i]->DMS.pHead->data.viTri << "/";
		FileOut << dsds.dausach[i]->sotrang << endl;
		dsdms = dsds.dausach[i]->DMS;
		FileOut << dsdms.SoLuong << endl;

		for (ptrDMSach p = dsdms.pHead; p != NULL; p = p->pNext){
			FileOut << p->data.maSach << "/";
			FileOut << p->data.trangThai << endl;
		}
	}
	FileOut.close();
}

// Load file DAU SACH
void LoadFile_DAUSACH(DS_DAUSACH &dsds){
	ifstream FileIn;
	FileIn.open("DauSach.txt", ios::in);
	
	int n, soLuong;
	string vitri;
	FileIn >> n;
	FileIn.ignore();
	dsds.soLuong = n;

	for (int i=0; i<dsds.soLuong; i++){
		DS_DANHMUCSACH dsdms;
		dsds.dausach[i] = new DAU_SACH;
		
		getline(FileIn, dsds.dausach[i]->ISBN, '/');
		getline(FileIn, dsds.dausach[i]->tacgia, '/');
		getline(FileIn, dsds.dausach[i]->tensach, '/');
		getline(FileIn, dsds.dausach[i]->theloai, '/');
		FileIn >> dsds.dausach[i]->NXB;
		FileIn.ignore();
		FileIn >> dsds.dausach[i]->demSoLanMuon;
		FileIn.ignore();
		getline(FileIn, vitri, '/');
		FileIn >> dsds.dausach[i]->sotrang;
		FileIn.ignore();
		dsds.dausach[i]->DMS.pHead = NULL;
		FileIn >> soLuong;
		FileIn.ignore();
		dsdms.SoLuong = soLuong;

		for(int i=0; i<soLuong; i++){
			DANH_MUC_SACH dms;
			ptrDMSach p = Newnode(dms);
			
			getline(FileIn, p->data.maSach, '/');
			FileIn >> p->data.trangThai;
			FileIn.ignore();
			p->data.viTri = vitri;
			InsertFirstDMS(dsdms, p);
		}
		dsds.dausach[i]->DMS = dsdms;
	}
	FileIn.close();
}

// ADD 1 CUON SACH
bool Add_DAUSACH(DS_DAUSACH &ds, DAU_SACH &sach){
	ShowConsoleCursor(false);
	sach.ISBN = RandomISBN(ds);
	DS_DANHMUCSACH ds_dms;

	int x = 50, y;
	int SoLuong = 1;
	string ViTriDau = "";
	
	displayDS_DAUSACH(ds); // Display new row in table

	SetColor(3);
	y = 5;
	for(int i=1; i<=8; i++){ // 5, 9, 13
		DrawBorder(3, y, 28, 2, 3);
		y += 4;
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

	SetColor(12);
	y = 6; // cls Table Left
	for(int i=1; i<=8; i++){
		gotoxy(4, y);
		cout << "                           ";
		y += 4;
	}
	gotoxy(3, 36);
	cout << "                        ";
	gotoxy(3, 37);
	cout << "                        ";
	
	y = 4;
	for(int i=0; i<8; i++){
		gotoxy(3, y);
		cout << menu[i];
		y += 4;
	}

	SetColor(3);
	gotoxy(14, 6);
	cout << sach.ISBN;

//	The loai
	gotoxy(4, 26);
	cout << "<";
	gotoxy(30, 26);
	cout << ">";

//	y: 9, 13, 17,... ->
	DrawBorder(3, 9, 28, 2, 12);
	SetColor(3);
	sach.tensach = EditValue("", false, 4, 10, false, false); // Ten Sach
	CapsLock(sach.tensach, 4, 10);
	DrawBorder(3, 9, 28, 2, 3);

	DrawBorder(3, 13, 28, 2, 12);
	SetColor(3);
	sach.tacgia = EditValue("", false, 4, 14, false, false); // Tac Gia
	CapsLock(sach.tacgia, 4, 14);
	DrawBorder(3, 13, 28, 2, 3);

	DrawBorder(3, 17, 28, 2, 12);
	SetColor(3);
	sach.sotrang = StringToNumber(EditValue("", true, 4, 18, false, false)); // So Trang
	DrawBorder(3, 17, 28, 2, 3);

	DrawBorder(3, 21, 28, 2, 12);
	SetColor(3);
	sach.NXB = StringToNumber(EditValue("", true, 4, 22, false, false)); //	Nam Xuat Ban
	DrawBorder(3, 21, 28, 2, 3);

	DrawBorder(3, 25, 28, 2, 12);
	SetColor(3);
	sach.theloai = TheLoai(); // The Loai
	DrawBorder(3, 25, 28, 2, 3);

	DrawBorder(3, 29, 28, 2, 12);
	SetColor(3);
	SoLuong = StringToNumber(EditValue("", true, 4, 30, false, false)); // So Luong
	DrawBorder(3, 29, 28, 2, 3);

	DrawBorder(3, 33, 28, 2, 12);
	SetColor(3);
	ViTriDau = EditValue("", false, 4, 34, false, true); // Vi Tri Dau
	CapsLock(ViTriDau, 4, 34);
	DrawBorder(3, 33, 28, 2, 12);

	sach.demSoLanMuon = 0;
	SinhMaSachTuDong(sach.ISBN, SoLuong, ds_dms, ViTriDau);
	sach.DMS = ds_dms;

//	Edit Before Add
	int chon = 8, countEnter = 0;
	char input;

	SetColor(3);
	gotoxy(3, 36); // Save
	cout << "F1 : Save";
	gotoxy(3, 37);
	cout << "Esc: Save & Exit";

	reset:
		ShowConsoleCursor(false);
		SetColor(3);
		y = 5;

		for(int i=0; i<8; i++){ // 4, 8, 12,...
			i == chon ? DrawBorder(3, y, 28, 2, 12) : DrawBorder(3, y, 28, 2, 3);
			y += 4;
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
						sach.tensach = EditValue(sach.tensach, false, 4, 10, false, false);
						ShowConsoleCursor(false);
						break;

					case 2: // Tac Gia
						sach.tacgia = EditValue(sach.tacgia, false, 4, 14, false, false);
						ShowConsoleCursor(false);
						break;

					case 3: // So Trang
						sach.sotrang = StringToNumber(EditValue(NumberToString(sach.sotrang), true, 4, 18, false, false));
						ShowConsoleCursor(false);
						break;

					case 4: // Nam Xuat Ban
						sach.NXB = StringToNumber(EditValue(sach.NXB == NULL ? "" : NumberToString(sach.NXB), true, 4, 22, false, false));
						ShowConsoleCursor(false);
						break;

					case 5: // The Loai
						sach.theloai = TheLoai();
						ShowConsoleCursor(false);
						break;

					case 6: // So Luong
						SoLuong = StringToNumber(EditValue("", true, 4, 26, false, false));
						ShowConsoleCursor(false);
						break;

					case 7: // Vi Tri Dau
						ViTriDau = StringToNumber(EditValue("", true, 4, 30, false, false));
						ShowConsoleCursor(false);
						break;

				}
				break;
			// end case ENTER

			case F1: // Case Save
//				SaveFile_DAUSACH(ds);
				return true;

			case Esc: //  Save + Exit
//				SaveFile_DAUSACH(ds);
				return false;

		}
	}
	// End edit before add
}

// ADD NHIEU CUON SACH SACH
void AddList_DAUSACH(DS_DAUSACH &ds){
	DAU_SACH sach;
	
	if(ds.soLuong == MAX_DAU_SACH){
		displayStr("Danh sach day!!", 50, 5); return;
	}

	while(ds.soLuong < MAX_DAU_SACH){
		ds.dausach[ds.soLuong] = new DAU_SACH;
		bool temp = Add_DAUSACH(ds, sach);
		*ds.dausach[ds.soLuong] = sach;
		ds.soLuong++;

		if(!temp)
			break;
	}
	SaveFile_DAUSACH(ds); // error Save File ????
}

// DELETE SACH THEO ISBN
void XoaSach(DS_DAUSACH &ds, string ISBN, int index){
	if(SearchDS_DAUSACH(ds, ISBN) != -1){
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
	if(l.pHead == NULL)
		return;

	ptrDMSach p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
}

bool XoaNodeCoKhoaBatKy(DS_DANHMUCSACH &l, string masach){
	if(l.pHead == NULL)
		return false;

	if(l.pHead->data.maSach == masach){
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

void XoaMaSachChuaMuon(DS_DAUSACH &ds){
	DS_DANHMUCSACH dsdms;
	string masach;
	int index = 0;
	system("cls");
	DrawBorder(1, 3, 38, 35, 3); // Draw Table Left
	DrawBorder(41, 3, 90, 35, 3); // Draw Table Right
	
//	displayDS_DANHMUCSACH(ds);
	gotoxy(2, 5);
	cout << "Nhap ma sach can xoa :" ;
	DrawBorder(2, 7, 30, 2, 3);
	ShowConsoleCursor(true);
	gotoxy(3, 8);
	getline(cin, masach);
	string isbn = CatLayMaDauSach(masach);
	
	for(int i = 0; i<ds.soLuong; i++){
		if(ds.dausach[i]->ISBN == isbn){
			dsdms = ds.dausach[i]->DMS;
			index = i;
		}
	}
	
	if(XoaNodeCoKhoaBatKy(dsdms, masach)){
		dsdms.SoLuong--;
//		ds.dausach[index]->DMS.SoLuong--;
		ds.dausach[index]->DMS = dsdms;
		displayStr("Xoa Thanh Cong!", 50, 10);
		Sleep(300);
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
void SaveFile_DOCGIA(Tree &t, ofstream &FileOut){
    if(t != NULL){
		FileOut << t->info.maThe << "/";
		FileOut << t->info.ho << "/";
		FileOut << t->info.ten << "/";
		FileOut << t->info.phai << "/";
		FileOut << t->info.slSachDangMuon << "/";
		FileOut << t->info.trangThai << endl;
		
		SaveFile_DOCGIA(t->pLeft, FileOut);
		SaveFile_DOCGIA(t->pRight, FileOut);
	}
}

void DocFileDocGia_Them(Tree &t, ifstream &FileIn, DocGia a){
	if(t == NULL){
		CAYNHIPHANTK_TheDocGia *p = new CAYNHIPHANTK_TheDocGia;
		p->info = a;
		p->info.DS_MUONTRA.pHead = NULL;
		p->info.DS_MUONTRA.pLast = NULL;
		p->pLeft = NULL;
		p->pRight = NULL;
		t = p;
		soLuongDocGia++;
	}
	else{
		if(t->info.maThe > a.maThe)
			DocFileDocGia_Them(t->pLeft, FileIn, a);

		if(t->info.maThe < a.maThe)
			DocFileDocGia_Them(t->pRight, FileIn, a);

	}
}

void LoadFile_DOCGIA(Tree &t){
	DocGia a[100];

	ifstream FileIn;
	FileIn.open("DocGia.txt", ios::in);
	
	int mathe = 0, i = 0;
	while(!FileIn.eof()){
		FileIn >> a[i].maThe;
		FileIn.ignore();
		getline(FileIn, a[i].ho, '/');
		getline(FileIn, a[i].ten, '/');
		getline(FileIn, a[i].phai, '/');
		
		FileIn >> a[i].slSachDangMuon;
		FileIn.ignore();
		FileIn >> a[i].trangThai;
		FileIn.ignore();
		if(a[i].maThe == 0)
			break;

		DocFileDocGia_Them(t, FileIn, a[i]);
		i++;
//		if(FileIn.eof()){
//			break;
//		}
	}
	FileIn.close();
}

void InitTree(Tree &t){
	t = NULL;
}

bool Find_DOCGIA(Tree t, int MaThe, Tree& temp){
	if(t == NULL)
		return false;

	if(t->info.maThe == MaThe){
		temp = t;
		return true;
	}

	if(MaThe > t->info.maThe)
		Find_DOCGIA(t->pRight, MaThe, temp);

	if(MaThe < t->info.maThe)
		Find_DOCGIA(t->pLeft, MaThe, temp);

	return false;
}

string Sex_DOCGIA(int y){
	ShowConsoleCursor(false);
	char c, source[][50] = { // lenght: 2
		"Nam",
		"Nu"
	};

	int current = 0;
	SetColor(3);
	while(1){
		gotoxy(5, y);
		cout << "                ";
		gotoxy(16, y);
		cout << source[current];

		c = GetKey();
		switch(c){
			case -75: // Case left
				current--;
				if(current < 0)
					current = 1;

				break;

			case -77: // Case Right
				current++;
				if(current > 1)
					current = 0;

				break;

			case Enter:
				return source[current];

		}
	}

}

int Mode_DOCGIA(){
	ShowConsoleCursor(false);
	
	char c, source[][50] = { // lenght: 5
		"Bi Khoa",
		"Hoat Dong"
	};

	int arrX[] = {14, 13}, current = 0;
	while(1){
		gotoxy(5, 25);
		cout << "                   ";
		gotoxy(arrX[current], 25);
		cout << source[current];

		c = GetKey();
		switch(c){
			case -75: // Case left
				current--;
				if(current < 0)
					current = 1;

				break;

			case -77: // Case Right
				current++;
				if(current > 1)
					current = 0;

				break;

			case Enter:
				return current;
		}
	}
}

void Update_DOCGIA(Tree &t, int MaThe){
	if(t == NULL)
		return;

	if(t->info.maThe == MaThe){
		DrawBorder(3, 12, 28, 2, 12); // 12, 16,... ->
		SetColor(3);
		t->info.ho =  EditValue(t->info.ho, false, 4, 13, false, false); // Ho
		DrawBorder(3, 12, 28, 2, 3);

		DrawBorder(3, 16, 28, 2, 12);
		SetColor(3);
		t->info.ten = EditValue(t->info.ten, false, 4, 17, true, false); // Ten
		DrawBorder(3, 16, 28, 2, 3);

		gotoxy(5, 21);
		cout << "                ";
		DrawBorder(3, 20, 28, 2, 12);
		SetColor(3);
		t->info.phai = Sex_DOCGIA(21); // Gioi Tinh
		gotoxy(5, 21);
		cout << "                ";
		gotoxy(13, 21);
		t->info.phai == "Nam" ?	gotoxy(16, 21) : gotoxy(17, 21);
		cout << t->info.phai;
		DrawBorder(3, 20, 28, 2, 3);
		
		DrawBorder(3, 24, 28, 2, 12);
		SetColor(3);
		t->info.trangThai = Mode_DOCGIA();
		DrawBorder(3, 24, 28, 2, 3);
	}

	if(MaThe > t->info.maThe)
		Update_DOCGIA(t->pRight, MaThe);

	if(MaThe < t->info.maThe)
		Update_DOCGIA(t->pLeft, MaThe);

}

int randomID(){
	string box = "0123456789";
	char res[6];
	srand(time(NULL));
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
	if(t == NULL)
		return;

	TreeToArray(t->pLeft, a, i);
	a[i++] = t->info;
	TreeToArray(t->pRight, a, i);
}

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
		
	int x = 0, row = 6, arrX[] = {38, 50, 92, 122, 134};
	DocGia* arr = new DocGia[soLuongDocGia];
	TreeToArray(t, arr, x); // Tree -> Array
		
	for(int i=0; i<soLuongDocGia; i++){
//		35 45 80 110 120
		if(arr[i].maThe != maThe){
			gotoxy(arrX[0], row);
			cout << arr[i].maThe;
			
			gotoxy(arrX[1], row);
			cout << arr[i].ho;
			
			gotoxy(arrX[2], row);
			cout << arr[i].ten;

			gotoxy(arrX[3], row);
			cout << "       ";
			gotoxy(arrX[3], row);
			cout << arr[i].phai;
			
			gotoxy(arrX[4], row);
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

void HeaderTable_DOCGIA(int row, int *arrX){
	SetColor(12);
	char menu[5][20] = {
		"ID",
		"Ho",
		"Ten",
		"Phai",
		"Trang Thai"
	};
	
//	int arrX[] = {5, 20, 70, 100, 134};
//	35 45 80 110 120
	gotoxy(arrX[0], row);
	cout << menu[0]; // Ma doc gia
	
	gotoxy(arrX[1], row);
	cout << menu[1]; // Ho
	
	gotoxy(arrX[2], row);
	cout << menu[2]; // Ten
	
	gotoxy(arrX[3], row);
	cout << menu[3]; // Phai
	
	gotoxy(arrX[4], row);
	cout << menu[4]; // Trang thai
	SetColor(12);
}

bool Search_DOCGIA(Tree t, int MaThe, Tree& temp) {
	if(t == NULL)
		return false;

	if(t->info.maThe == MaThe){
		temp = t;
		return true;
	}
	
	if(MaThe > t->info.maThe)
		Search_DOCGIA(t->pRight, MaThe, temp);

	if(MaThe < t->info.maThe)
		Search_DOCGIA(t->pLeft, MaThe, temp);

	return false;
}

void Add_DOCGIA(Tree &t, int ID, int &RowTable, bool &isExit){
	int x = 50, RowHeader = 4;

	int y, count = 2, arrX[] = {38, 50, 92, 122, 134};
	if(t == NULL){
		CAYNHIPHANTK_TheDocGia* p = new CAYNHIPHANTK_TheDocGia;
		p->info.maThe = ID;

		while(1){
			ShowConsoleCursor(false);
			HeaderTable_DOCGIA(RowHeader, arrX);
			
			y = 5;
			for(int i=1; i<=4; i++){ // 5, 9, 13
				DrawBorder(3, y, 28, 2, 3);
				y += 4;
			}

			char menu[][20] = {
				"Ma Doc Gia",
				"Ho",
				"Ten",
				"Gioi Tinh"
			};

			SetColor(12);
			y = 6; // cls Table Left
			for(int i=0; i<4; i++){
				gotoxy(4, y);
				cout << "                          ";
				y += 4;
			}
			SetColor(3);
			gotoxy(3, 20);
			cout << "                   ";
			gotoxy(3, 21);
			cout << "                   ";
			
			y = 4;
			for(int i=0; i<4; i++){
				gotoxy(3, y);
				cout << menu[i];
				y += 4;
			}

			SetColor(3);
			gotoxy(14, 6);
			cout << p->info.maThe;
			
			// Display new row in table
			SetColor(0);
			if(firstName.length() != 0){ // global var
				gotoxy(arrX[0], RowTable - 1);
				cout << "             ";
				gotoxy(arrX[0], RowTable - 1);
				cout << maThe;

				gotoxy(arrX[1], RowTable - 1);
				cout << "             ";
				gotoxy(arrX[1], RowTable - 1);
				cout << firstName;

				gotoxy(arrX[2], RowTable - 1);
				cout << "             ";
				gotoxy(arrX[2], RowTable - 1);
				cout << lastName;

				gotoxy(arrX[3], RowTable - 1);
				cout << "       ";
				gotoxy(arrX[3], RowTable - 1);
				cout << SexTable;

				gotoxy(arrX[4], RowTable - 1);
				cout << "       ";
				gotoxy(arrX[4], RowTable - 1);
				cout << "Hoat Dong";
			}
			// End display new row in table
			
			SetColor(3);
			gotoxy(4, 18);
			cout << "<";
			gotoxy(30, 18);
			cout << ">";

			SetColor(3);
			DrawBorder(3, 9, 28, 2, 12);
			SetColor(3);
			p->info.ho = EditValue("", false, 4, 10, false, false); // Ho
			CapsLock(p->info.ho, 4, 10);
			DrawBorder(3, 9, 28, 2, 3);

			DrawBorder(3, 13, 28, 2, 12);
			SetColor(3);
			p->info.ten = EditValue("", false, 4, 14, true, false); // Ten
			CapsLock(p->info.ten, 4, 14);
			DrawBorder(3, 13, 28, 2, 3);

			DrawBorder(3, 17, 28, 2, 12);
			p->info.phai = Sex_DOCGIA(18); // Phai
			gotoxy(6, 18);
			cout << "              ";
			gotoxy(16, 18);
			cout << p->info.phai;
			DrawBorder(3, 17, 28, 2, 3);

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
			
			SetColor(3);
			gotoxy(3, 20);
			cout << "F1 : Save";
			gotoxy(3, 21);
			cout << "Esc: Save & Exit";

			// edit before add(Ho & Ten)
			char input, exit;
			int chon = 4, step;
			
			// reset edit input
			reset:
				ShowConsoleCursor(false);
				SetColor(3);
				y = 5;

				for(int i=0; i<4; i++){ // 4, 8, 12,...
					i == chon ? DrawBorder(3, y, 28, 2, 12) : DrawBorder(3, y, 28, 2, 3);
					y += 4;
				}
					
			while(1){
				input = getch();
				switch(input){
					case Up:
						if(chon - 1 > 0){
							chon--;
							goto reset;
						}
						break;

					case Down:
						if(chon + 1 < 4){
							chon++;
							goto reset;
						}
						break;
						
					// case ENTER
					case Enter:
						switch(chon){
							case 1: // Ho
								p->info.ho = EditValue(p->info.ho, false, 4 ,10, false, false);
								CapsLock(p->info.ho, 4, 10);
								firstName = p->info.ho; // global var
								ShowConsoleCursor(false);
								break;

							case 2: // Ten
								p->info.ten = EditValue(p->info.ten, false, 4, 14, true, false);
								CapsLock(p->info.ten, 4, 14);
								lastName = p->info.ten; // global var
								ShowConsoleCursor(false);
								break;

							case 3: // Gioi Tinh
								gotoxy(6, 18);
								cout << "               ";
								p->info.phai = Sex_DOCGIA(18);
								SexTable = p->info.phai; // global var
								SetColor(3);
								gotoxy(6, 18);
								cout << "               ";
								gotoxy(16, 18);
								cout << p->info.phai;
								break;
						}
						break;
					// end case ENTER
						
					case F1: // Case Add
						t = p; // Add node
						
						soLuongDocGia++;
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
			Add_DOCGIA(t->pLeft, ID, RowTable, isExit);
			
		if(t->info.maThe < ID)
			Add_DOCGIA(t->pRight, ID, RowTable, isExit);
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
	cout << "Nhap ma doc gia can xoa: ";
	DrawBorder(2, 7, 30, 2, 3);
	ShowConsoleCursor(true);
	gotoxy(3, 8);
	cin >> madocgia;
	if(Search_DOCGIA(t, madocgia, tam) == false){
		check = false;
	}
	if(tam->info.DS_MUONTRA.pHead == NULL){
		check = true;
	}
	if(check){
		XoaDocGia(t, madocgia);
		displayStr("Xoa doc gia thanh cong!!", 50, 10);
		soLuongDocGia--;
		Sleep(300);
		return;
	}
	else{
		displayStr("Khong the xoa doc gia!", 50, 10);
		Sleep(300);
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

void Search_DOCGIA(DocGia *arr, int size, string InputValue, int &sizeArr){
	DocGia *temp = new DocGia[size];
	int count = 0;
	for(int i=0; i<size; i++){
		if(Include(arr[i].ten, InputValue) || Include(arr[i].ho, InputValue)){
			temp[count] = arr[i];
			count++;
		}
	}
	sizeArr = count;
	arr = temp;
}

void Edit_DOCGIA(Tree &t, int RowTableEdit){
	if(t == NULL)
		return;
	
	Tree temp; // Tree Edit
	
	SetColor(0);
	gotoxy(3, 4);
	cout << "Tim Doc Gia Theo Ten(F1)"; // -59
	
	int RowHeader = 7,  arrX[] = {38, 50, 92, 122, 134};
	HeaderTable_DOCGIA(RowHeader, arrX);
	gotoxy(50, 6);
	
	int SortBy = 0, countSearch = 0, y = 8; // Default Sort By Name
	bool isSearch = false;
	int count = 5, CurrentRow = 6, sizeArr = 0, row = 10, indexArr = 0;
	char input;
	string InputValue = "", SortName = "Name", StrModeDg;

	int sizeArray;
	DocGia* arr = new DocGia[soLuongDocGia];
	TreeToArray(t, arr, sizeArr); // Tree -> Array

//	SortByName_DOCGIA(arr);

	// cls(5, 36, 49, 80); // cls table right
	countSearch = 0;
	y = 8;
	sizeArray = soLuongDocGia;
	
	for(int i=1; i<=5; i++){
		DrawBorder(3, y, 28, 2, 3);
		y += 4;
	}

	char menu[][20] = {
		"Ma Doc Gia",
		"Ho",
		"Ten",
		"Gioi Tinh",
		"Trang Thai"
	};

//		5, 8, 11
	SetColor(12);
	y = 7;
	for(int i=0; i<4; i++){
		gotoxy(3, y);
		cout << menu[i];
		y += 4;
	}
	
	y = 9; // cls Table Left
	for(int i=0; i<5; i++){
		gotoxy(5, y);
		i < 3 ? cout << "                         " : cout << "                         ";
		y += 4;
	}
	gotoxy(3, 23);
	cout << "                     ";
	
	gotoxy(38, 8);
	cout << "                     ";
//	SetColor(3);
//	gotoxy(38, 8);
//	cout << "Sort By " << SortName;
	
	Display:
	row = 9;
	for(int i=0; i<soLuongDocGia; i++){
		i == indexArr ? SetColor(3) : SetColor(0);

		if((Include(arr[i].ten, InputValue) || Include(arr[i].ho, InputValue)))
			countSearch++;

		if(isSearch ? (Include(arr[i].ten, InputValue) || Include(arr[i].ho, InputValue)) : true){
			gotoxy(arrX[0], row);
			cout << arr[i].maThe;

			gotoxy(arrX[1], row);
			cout << arr[i].ho;

			gotoxy(arrX[2], row);
			cout << arr[i].ten;

			gotoxy(arrX[3], row);
			cout << "       ";
			gotoxy(arrX[3], row);
			cout << arr[i].phai;
			
			gotoxy(arrX[4], row);
			cout << "          ";
			gotoxy(arrX[4], row);
			if(arr[i].trangThai == 1)
				cout << "Hoat Dong";
			else{
				SetColor(12);
				cout << "Bi Khoa";
			}
			row++;
		}
	}
	DrawBorder(1, 3, 147, 2, 0); // Draw border search
	
	SetColor(3);
	gotoxy(4, 21);
	cout << "<";
	gotoxy(30, 21);
	cout << ">";
	SetColor(3);
	gotoxy(4, 25);
	cout << "<";
	gotoxy(30, 25);
	cout << ">";
	
	SetColor(3);
	gotoxy(3, 27);
	cout << "Esc:   Save & Exit";
	gotoxy(3, 28);
	cout << "Enter: Continue Edit";
		
	while(1){
		input = getch();
		switch(input){
			case Up:
				if(indexArr - 1 >= 0)
					indexArr--;
				goto Display;
				
				break;
				
			case Down:
				if(isSearch)
					if(indexArr + 1 < countSearch)
						indexArr++;
						
				if(!isSearch)
					if(indexArr + 1 < soLuongDocGia)
						indexArr++;
				goto Display;
				
				break;
				
			case Enter: // Case Get ID Doc Gia -> Edit
				SetColor(3);
				gotoxy(15, 9);
				cout << arr[indexArr].maThe;
				gotoxy(4, 13);
				cout << arr[indexArr].ho;
				gotoxy(4, 17);
				cout << arr[indexArr].ten;
				gotoxy(5, 21);
				cout << "                ";
				arr[indexArr].phai == "Nam" ?	gotoxy(16, 21) : gotoxy(17, 21);
				cout << arr[indexArr].phai;
				
				arr[indexArr].trangThai == 1 ? gotoxy(13, 25) : gotoxy(14, 25);
				StrModeDg = arr[indexArr].trangThai == 0 ? "Bi Khoa" : "Hoat Dong";
				cout << StrModeDg;
				
				Update_DOCGIA(t, arr[indexArr].maThe); // Handle Update Tree
				
				sizeArr = 0;
				TreeToArray(t, arr, sizeArr); // Tree -> Array
				
				y = 9; // cls Table Left
				for(int i=1; i<=5; i++){
					gotoxy(4, y);
					cout << "                          ";
					y += 4;
				}
				
				goto Display;
				
				break;
				
			case F1: // Case Continue
				break;
				
			case F2: // Case Sort By Name
				SortByName_DOCGIA(arr);
				SortName = "Name";
				break;

			case F3: // Case Sort By ID
				SortByID_DOCGIA(arr);
				SortName = "ID";
				break;

			case F4: // Case search DOC GIA
				gotoxy(3, 4);
				cout << "                                   ";
				gotoxy(3, 4);
				SetColor(0);
				isSearch = true;
				DrawBorder(1, 3, 147, 2, 3); // Draw border search
				InputValue = EditValue("", false, 3 , 4, true, false);
				
				cls(8, 29, 38, 115); // cls table right
				ShowConsoleCursor(false);
				
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
void XuatSachDangMuonCua1DocGia(Tree &t, int i, int row){
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

//bool TimDocGia(Tree t, int MaThe, Tree& temp){
//	if(t == NULL)
//		return false;
//
//	if(t->info.maThe == MaThe){
//		temp = t;
//		return true;
//	}
//
//	if(MaThe > t->info.maThe)
//		TimDocGia(t->pRight, MaThe, temp);
//	
//	if(MaThe < t->info.maThe)
//		TimDocGia(t->pLeft, MaThe, temp);
//
//	return false;
//}
//
//void UpdateTree(Tree &t, int MaThe, Tree temp){
//	if(t == NULL)
//		return;
//
//	if(t->info.maThe == MaThe)
//		t = temp;
//
//	if(MaThe > t->info.maThe)
//		TimDocGia(t->pRight, MaThe, temp);
//
//	if(MaThe < t->info.maThe)
//		TimDocGia(t->pLeft, MaThe, temp);
//
//}

void MuonSach(Tree &t, DS_DAUSACH &dsds){
	ShowConsoleCursor(false);
	Tree temp;
	DAU_SACH* ds;
	MUON_TRA mt;
	NODE_DanhMucSach* n_dms;
	ptrDMSach dms;

	int i = 5, row = 39, IDDocGia = NULL;
	string IDSach;
	
	cls(3, 30, 2, 145); // Cls Main Table
	DrawBorder(1, 6, 147, 32, 0); // Main Table
	DrawBorder(1, 3, 147, 2, 3); // Draw border search

	SetColor(0);
	gotoxy(3, 4);
	cout << "Nhap Ma Doc Gia";
	
	DocGia *arr = new DocGia[soLuongDocGia];
	int count = 0, arrX[] = {5, 20, 70, 100, 134};;
	TreeToArray(t, arr, count);
	
	Input:
	IDDocGia = StringToNumber(EditValue(IDDocGia == NULL ? "" : NumberToString(IDDocGia), true, 20, 4, true, false)); // Input for Search DOC GIA
	if(NumberToString(IDDocGia).length() != 6)
		goto Input;
		
//	Search ID Doc Gia ????

//	SortByName_DOCGIA(arr);

	int SortBy = 0, countSearch = 0, y; // Default Sort By Name
	string InputValue = NumberToString(IDDocGia);
	char input;
	bool isSearch = true;

	row = 9;
	y = 8;

//	HeaderTable_DOCGIA(RowHeader);

	gotoxy(row + 5, i + 7);
	cout << "Ma Sach";
	gotoxy(row + 25, i + 7);
	cout << "Ngay Muon";
	gotoxy(row + 45, i + 7);
	cout << "Ngay Tra";
	gotoxy(row + 65, i + 7);
	cout << "Trang Thai";
	
	SetColor(3);
	gotoxy(60, 9);
	cout << "DANH SACH CAC SACH MA DOC GIA DANG MUON";
	Find_DOCGIA(t, IDDocGia, temp);

//	XuatSachDangMuonCua1DocGia(temp, i + 6, row); // Error ????

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
	
	
	
	while(1){
		if(temp->info.slSachDangMuon < 3 && temp->info.trangThai == 1){
			SetColor(3);
			gotoxy(2, i + 10);
			cout << "Nhap ma sach can muon: ";
			fflush(stdin);
			DrawBorder(2, i + 13, 20, 2, 3);
			gotoxy(3, i + 14);
			getline(cin, IDSach);

			bool checkMS = LayThongTinSach(dsds, IDSach, n_dms, ds), checkM = true;
			if(checkMS == false){
				ShowConsoleCursor(false);
				displayStr("Ma sach khong ton tai", 50, 15);
				Sleep(300);
				checkM = false;
			}

			for(ptrMuonTra ptrmt = temp->info.DS_MUONTRA.pHead; ptrmt != NULL; ptrmt = ptrmt->pRight){
				cout<<"thu nhat: "<<CatLayMaDauSach(IDSach)<<"thu hai"<<CatLayMaDauSach(ptrmt->info.maSach);

				if (CatLayMaDauSach(IDSach) == CatLayMaDauSach(ptrmt->info.maSach)){
					displayStr("Ma sach thuoc dau sach ma may dang muon, cho nen khong muon duoc nua", 50, 15);
					Sleep(300);
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
				MuonSach_Them(temp, dsds, n_dms);
				ShowConsoleCursor(false);
				displayStr("Muon thanh cong nha!", 50, 15);
				Sleep(1000);
			}
		}
	}
}

void XuatDauSach(int arrX[], DS_DAUSACH &ds){
	for(int i=0; i<ds.soLuong; i++){
		i == 0 ? SetColor(0) : SetColor(3);

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

void Display_DAUSACH(DS_DAUSACH &ds){
	system("color f0");
	
	SetColor(3);
	gotoxy(60, 3);
	cout<<"DANH SACH DAU SACH";
	
	DrawBorder(1, 3, 147, 2, 0); // Draw border search
	DrawBorder(1, 6, 147, 32, 0); // Main Table
	
	SetColor(0);
	gotoxy(3, 4);
	cout << "Tim Sach Theo Ten Sach, Tac Gia(F1)"; // -59
	
	char input, menu[8][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nam",
		"The Loai",
		"So Luong",
		"Vi Tri"
	};
	
	int arrX[] = {3, 13, 48, 88, 99, 107, 125, 138};
	
	bool isSearch;
	string InputValue;
	while(1){

		SetColor(12);
		for(int i=0; i<8; i++){
			gotoxy(arrX[i], 7);
			cout << menu[i];
		}
		
		int row = 9;
		for(int i=0; i<ds.soLuong; i++){
//			i == 0 ? SetColor(3) : SetColor(0);
			SetColor(0);
//			Search by TenSach or TenTacGia
			if(isSearch ? (Include(ds.dausach[i]->tensach, InputValue) || Include(ds.dausach[i]->tacgia, InputValue)) : true){
				gotoxy(arrX[0], row);
				cout << ds.dausach[i]->ISBN;
				gotoxy(arrX[1], row);
				cout << ds.dausach[i]->tensach;
				gotoxy(arrX[2], row);
				cout << ds.dausach[i]->tacgia;
				gotoxy(arrX[3], row);
				cout << ds.dausach[i]->sotrang;
				gotoxy(arrX[4], row);
				cout << ds.dausach[i]->NXB;
				gotoxy(arrX[5], row);
				cout << ds.dausach[i]->theloai;
				gotoxy(arrX[6], row);
				cout<<ds.dausach[i]->DMS.SoLuong;
				gotoxy(arrX[7], row);
				cout<<ds.dausach[i]->DMS.pHead->data.viTri;
				
				row++;
			}
		}
		
		char input;
		input = getch();
		switch(input){
			case F1: // Case search DOC GIA
				InputValue = "";
				gotoxy(3, 4);
				cout << "                                   ";
				gotoxy(3, 4);
				SetColor(0);
				DrawBorder(1, 3, 147, 2, 3); // Draw border search
				InputValue = EditValue("", false, 3 , 4, false, false);

				isSearch = InputValue == "" ? false : true;
				cls(8, 30, 3, 140); // cls Main Table
				ShowConsoleCursor(false);
				break;
		}
	}
	
	getch();
}

bool login(){
	system("cls");
	Normal();
	char userName[100], passWord[40];
	Draw_frame();
	
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
	int chon, res, arrX[5] = {62, 61, 64, 68}, ISBN, RowTable, RowTableEdit;
	bool case1;

	while(1){
		cls(3, 39, 1, 148); // system('cls')
		chon = MenuThuancutee(CauA, 4, 0, 29, arrX, 57);

		firstName = "";
		maThe = NULL;
		RowTable = 6 + soLuongDocGia;
		RowTableEdit = 12 + soLuongDocGia;
		case1 = true;
		
		switch (chon){
			case 1: // Case Add DOC GIA
				cls(4, 30, 30, 80); // cls table right
				displayThe_DOCGIA(t, RowTable);
				
				DrawBorder(1, 3, 32, 35, 3); // Draw Table Left
				DrawBorder(35, 3, 113, 35, 3); // Draw Table Right
				while(case1)
					Add_DOCGIA(t, randomID(), RowTable, case1);

				break;

			case 2: // Case Edit DOC GIA
				cls(4, 35, 2, 110);
				DrawBorder(1, 6, 32, 32, 3); // Draw Table Left
				DrawBorder(35, 6, 113, 32, 3); // Draw Table Right
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
	cls(4, 35, 2, 140);
	int chon, res, arrX[4] = {68, 68, 59, 68};
	
	while (1){
		cls(3, 39, 1, 134);
		chon = MenuThuancutee(CauF, 4, 0, 29, arrX, 57);

		switch (chon){
			case 1: // Case Muon Sach
				MuonSach(t, dsds);
				break;

			case 2:
//				LietKeSachDangMuonCua1DocGia(t);
//				getch();
//				TraSach();
				break;

			case 4:
				return;
			}
		Sleep(300);
   }
}


// Cau c: NHap thong tin dau sach va danh ma sach tu dong
void Menu_DAUSACH(DS_DAUSACH &ds){
	system("color f0");
	
	Tree t;
	DS_DANHMUCSACH dsdms;
	
	LoadFile_DAUSACH(ds); // File -> Danh Sach Dau Sach

	int chon, flag = 1, arrX[4] = {66, 62, 64, 69};
	char Case_DauSach[][100] = {
									"Them Dau Sach",
									"Danh Sach Cac Dau Sach",
									"Xoa Mot Dau Sach",
									"Thoat!"
								};

	while(1){
		cls(3, 40, 1, 149); // Cls Main Table
		chon = MenuThuancutee(Case_DauSach, 4, 0, 30, arrX, 57);
		
		switch(chon){
			case 1: // Case Add DAU SACH
				cls(3, 30, 2, 145); // Cls Main Table
				DrawBorder(1, 3, 32, 35, 3); // Draw Table Left
				DrawBorder(35, 3, 113, 35, 3); // Draw Table Right
				AddList_DAUSACH(ds);
				break;
				
			case 2:
				cls(3, 30, 1, 147); // Cls Main Table
				Display_DAUSACH(ds);
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
void Exit(){
	cls(4, 35, 3, 100);
	char str1[] = "- Cam On Da Su Dung Chuong Trinh -";
	char str2[] = "- Xin Chao Va Hen Gap Lai! -";
	
	SetColor(3);
	gotoxy(55, 6);
	for(int i=0; i<strlen(str1); i++){
		cout << str1[i];
		Sleep(50);
	}
	
	gotoxy(58, 7);
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
	int chon, arrX[4] = {65, 66, 66, 69};
	
	while(1){
		chon = MenuThuancutee(td, 4, 0, 30, arrX, 57);
		
		switch(chon){
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
				Exit();
				return;
			}
		Sleep(300);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	SetConsoleTitle("Quan li thu vien - Thuancuteee");
	SetBGColor(15);
	
	DS_DAUSACH dsds;
	DAU_SACH sach;
	
	Tree t;

//	if(login()){
		InitTree(t);
		Menu(listMainMenu, t, dsds);
//	}

	return 0;
}
