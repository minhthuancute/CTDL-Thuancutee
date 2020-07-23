
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

#define Left 75
#define Right 77
#define BACKSPACE 8

using namespace std;

int soLuongDocGia = 0;

// function delete string
void Delete(string &str, int end){
	string temp = "";
	for(int i=0; i<end; i++)
		temp += str[i];
	str = temp;
}

void Add(string &str){
	
}

void DeleteStr(string &str, int x, int y){
	char input;
	gotoxy(x, y);
	for(int i=0; i<str.length(); i++)
		cout << str[i];

	int length = str.length();

	while(1){
		input = getch();
		switch(input){
			case BACKSPACE:
				gotoxy(length-1+x, y);
				cout << " ";
				length--;
				Delete(str, length);
				break;
				
//			default:
//				break;
				
		}
		gotoxy(x, y);
		for(int i=0; i<length; i++){
			cout << str[i];
		}
		if(length == 0)
			break;
	}

}

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

string SinhISBNNgauNhien(DS_DAUSACH &ds){
   srand(time(NULL));
   string code;
   string box = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	while(true){
		for (int i = 0; i < 6; i++)
	      	code += box[rand() % 26];
	      	
		if(!SearchDS_DAUSACH(ds, code) != -1){
			return code;
		}
	}
}

void displayDS_DAUSACH(DS_DAUSACH &ds){
	system("color f0");
//	OpenFile_DAUSACH(ds, "C:\\Users\\thuancutee\\Desktop\\DauSach.txt");
	
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
	int x = 50 , dem = 2, stepCls = 6;
	ShowConsoleCursor(true);
	Draw_frame(X, Y);
	
	cls(15, 20, 3, 34);
	for(int i=1; i<=5; i++){
		gotoxy(17, dem + stepCls);
		stepCls += 3;
		cout << "              ";
	}
	
	while (1){
	Nhap:
		DrawBorder(1, 3, 38, 35, 3);
		DrawBorder(41, 3, 90, 35, 3);
		displayDS_DAUSACH(ds);
		
		gotoxy(3, dem + 3);
		sach.ISBN = SinhISBNNgauNhien(ds);
		SetColor(4);
		cout << "Ma sach       ";
		SetColor(0);
		DrawBorder(16, dem + 2, 20, 2, 3);
		gotoxy(17, dem + 3);
		cout << sach.ISBN << "\n";
		SetColor(4);
		gotoxy(3, dem + 6);
		cout << "Nam xuat ban";
		gotoxy(3, dem + 9);
		cout << "So trang";
		gotoxy(3, dem + 12);
		cout << "Ten sach";
		gotoxy(3, dem + 15);
		cout << "Ten tac gia";
		gotoxy(3, dem + 18);
		cout << "The loai";
		
		SetColor(0);
		DrawBorder(16, dem + 5, 20, 2, 3);
		DrawBorder(16, dem + 8, 20, 2, 3);
		DrawBorder(16, dem + 11, 20, 2, 3);
		DrawBorder(16, dem + 14, 20, 2, 3);
		DrawBorder(16, dem + 17, 20, 2, 3);
		
		gotoxy(17, dem + 6);
		cin >> sach.NXB;
		
		gotoxy(17, dem + 9);
		int tempSoTrang;
		InputNumber(sach.sotrang);
		
		gotoxy(17, dem + 12);
		fflush(stdin);
		char temp[1000];

		gets(temp);
		strcpy(sach.tensach, temp);
		gotoxy(17, dem + 15);
		
		gets(sach.tacgia);
		gotoxy(17, dem + 18);
		
		gets(sach.theloai);

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

//  string -> int
	return atoi(res);
}

// tree -> array
void ChuyenCayThanhMang(Tree t, DocGia a[], int &i){
	if (t == NULL)
		return;

	ChuyenCayThanhMang(t->pLeft, a, i);
	a[i++] = t->info;
	ChuyenCayThanhMang(t->pRight, a, i);
//	a[i++] = t->info;
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

int Compare(DocGia dg1, DocGia dg2){
	if(dg1.ten < dg2.ten)
		return 1;
	else if(dg1.ten == dg2.ten){
		if(dg1.ho < dg2.ho)
		return 1;
	}
}

// quick sort
int partition(DocGia arr[], int start, int end){
    string pivot = arr[end].ten;
    DocGia t;
    
    int  P_index = start;
    //P-index indicates the pivot value index

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

	//at last returning the pivot value index
	return P_index;
 }
 
void Quicksort(DocGia *arr, int start, int end){
	if(start < end){
		int P_index = partition(arr, start, end);
		Quicksort(arr, start, P_index-1);
		Quicksort(arr, P_index+1, end);
	}
}
// end quick sort

// SORT TREE (Quick Sort)
void Sort_DOCGIA(Tree t){
	int x = 0;
	DocGia *arr = new DocGia[soLuongDocGia];
	ChuyenCayThanhMang(t, arr, x);
	
	Quicksort(arr, 0, soLuongDocGia-1);
	for(int i=0; i<soLuongDocGia; i++){
		gotoxy(50, dong + i);
		cout<<arr[i].maThe;
		gotoxy(65,dong + i);
		cout<<arr[i].ho;
		gotoxy(82,dong + i);
		cout<<arr[i].ten;
		gotoxy(99,dong + i);
		cout<<arr[i].phai;
		gotoxy(116,dong + i);

		if(arr[i].trangThai == 0)
			cout << "Hoat Dong";
		else{
			SetColor(12);
			cout << "Bi Khoa";
		}
	}
	
}

// Sort theo ma the

void displayThe_DOCGIA(Tree t){
	system("color f0");
	if(t == NULL)
		return;
	SetColor(3);

	int x = 0;
	DocGia* a = new DocGia[soLuongDocGia];
	ChuyenCayThanhMang(t, a, x);
 
	for(int i=0; i<soLuongDocGia; i++){
		gotoxy(50, dong + i);
		cout<<a[i].maThe;
		gotoxy(65,dong + i);
		cout<<a[i].ho;
		gotoxy(82,dong + i);
		cout<<a[i].ten;
		
		gotoxy(99,dong + i);
		cout << "       ";
		gotoxy(99,dong + i);
		cout<<a[i].phai;
		gotoxy(116,dong + i);
		
		if(a[i].trangThai == 0)
			cout << "Hoat Dong";
		else{
			SetColor(12);
			cout << "Bi Khoa";
		}
	}
	
}

//void XuatDSDocGia(Tree t) {
//	if(t == NULL)
//		return;
//
//	XuatDSDocGia(t->pLeft);
//	XuatMotDocGia(t, dem); dem++;
//	XuatDSDocGia(t->pRight);
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

bool AddDocGia(Tree &t, int ID) {
	int x = 50 , dem = 2, step = 50;
	ShowConsoleCursor(true);
	DrawBorder(1, 3, 45, 35, 0);
	DrawBorder(48, 3, 82, 35, 0);

	gotoxy(17, dem + 3);
	cout << "               ";
	gotoxy(17, dem + 6);
	cout << "               ";
	gotoxy(17, dem + 9);
	cout << "               ";
	gotoxy(17, dem + 12);
	cout << "                     ";

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
			SetColor(4);
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

			DrawBorder(16, dem + 2, 27, 2, 3);
			gotoxy(27, 5);
			SetColor(3);
			cout << p->info.maThe;

			gotoxy(17, dem + 3);
			SetColor(12);
			gotoxy(3, dem + 6);
			cout << "Ho";
			gotoxy(3, dem + 9);
			cout << "Ten";
			gotoxy(3, dem + 12);
			cout << "Phai(Nam/Nu)";

			SetColor(0);
			// Ho
			DrawBorder(16, dem + 5, 27, 2, 3);
			// Ten
			DrawBorder(16, dem + 8, 27, 2, 3);
			// Gioi Tinh
			DrawBorder(16, dem + 11, 27, 2, 3);

			SetColor(3);
			fflush(stdin);
			gotoxy(17, dem + 6);
			getline(cin, p->info.ho);
			
			gotoxy(17, dem + 9);
			getline(cin, p->info.ten);

			gotoxy(17, dem + 12);
			p->info.phai = Sex();
			gotoxy(20, 14);
			cout << "                    ";
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
					if(step + 3 != 16){
						DrawBorder(16, step+3, 27, 2, 3);
					}
					input = getch();
					switch(input){
						case Enter:
							switch(chon){
								case 0:
									DeleteStr(p->info.ho, 17, 8);
									gotoxy(17, dem + 6);
									getline(cin, p->info.ho);
									break;
								case 1:
									DeleteStr(p->info.ten, 17, 11);
									gotoxy(17, dem + 9);
									getline(cin, p->info.ten);
									break;
								case 2:
									gotoxy(17, dem + 12);
									gotoxy(20, 14);
									cout << "                    ";
									DrawBorder(16, dem + 11, 27, 2, 3);
									p->info.phai = Sex();
									SetColor(3);
									gotoxy(20, 14);
									cout << "                    ";
									gotoxy(28, 14);
									cout << p->info.phai;
									break;
							}
							break;
					}
				}
				else{
					DrawBorder(16, step, 27, 2, 3);
				}
				step += 3;
			}
			
			while(exit){
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
						exit = false;
						break;
				}
			}
			// end edit before add(Ho & Ten)

			t = p;
			//	check continue
			SetColor(3);
			gotoxy(14, 17);
			cout << "An ENTER De Tiep Tuc.";
			gotoxy(12, 18);
			cout << "An Phim Bat Ki De Thoat!";

			if(char exit = getch() == Enter){
				SetColor(12);
				gotoxy(12, 20);
				cout << "Them Doc Gia Thanh Cong!";
				Sleep(600);
				return true;
			}
			else
				return false;
		}
		// end handle input
		
	}
	else if (t->info.maThe > ID)
		AddDocGia(t->pLeft, ID);
	else if(t->info.maThe < ID)
		AddDocGia(t->pRight, ID);

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

void XoaDocGia(Tree& t, int x) {
	if (x > t->info.maThe) {
		XoaDocGia(t->pRight, x);
	}
	else if (x < t->info.maThe) {
		XoaDocGia(t->pLeft, x);
	}
	else {
		Tree tam = t;
		if (t->pLeft == NULL) {
			t = t->pRight;
		}
		else if (t->pRight == NULL) {
			t = t->pLeft;
		}
		else if (t->pLeft != NULL && t->pRight != NULL) {
			DeleteNodeLeftRight(tam, t->pRight);
		}
		delete tam;
	}
//	BaoLoi("Xoa doc gia thanh cong!!");
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
	int chon, res, arr[4] = {55, 57, 54, 61};
	bool case1 = true;
	while (1){
		SetBGColor(3);
		cls(3, 39, 1, 130);
		chon = MenuThuancutee(CauA, 4, 0, 29, arr, 50);
		SetBGColor(15);
		switch (chon){
		case 1:
			cls(4, 30, 30, 50);
			displayThe_DOCGIA(t);
  			while(case1 = AddDocGia(t, randomID())){
				displayThe_DOCGIA(t);
				if(case1 == false)
					break;
			}
			break;
		case 2:
			displayThe_DOCGIA(t);
			break;
		case 3:
//			while(1){
//				thuancute(t);
//			}
			break;
		case 4:
			return;
		}
		Sleep(1000);
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
		Sleep(1000);
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
		Sleep(100);
	}
	gotoxy(51, 7);
	for(int i=0; i<strlen(str2); i++){
		cout << str2[i];
		Sleep(100);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
