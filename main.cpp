
#include <iostream>
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

using namespace std;


/*    DAU SACH VA CAC HAM LIEN QUAN    */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LOAD FILE
void OpenFile(DS_DAUSACH &ds, char *filename){
	// ptr file
	FILE *f;
	DAU_SACH sach;
	if ((f = fopen(filename, "rb")) == NULL){
	//      BaoLoi("Loi mo file de doc");
		cout << "Load file err"; return;
	}
	ds.soLuong = 0;
	while (fread(&sach, sizeof(DAU_SACH), 1, f) != 0){
		ds.dausach[ds.soLuong] = new DAU_SACH;
		*ds.dausach[ds.soLuong] = sach;
		ds.soLuong++;
	}
	fclose(f);
//   BaoLoi("Da load xong danh sach vao bo nho");
	cout << "load file success";
}

// WRITE TO FILE
void SaveFile(DS_DAUSACH ds, char *filename){
   FILE *f;
   if ((f = fopen(filename, "wb")) == NULL){
//      BaoLoi("Loi mo file de ghi");
		cout << "Load file err"; return;
   }
   for (int i=0; i<ds.soLuong; i++)
		fwrite(ds.dausach[i], sizeof(DAU_SACH), 1, f);
//		f << ds.dausach[i];

	fclose(f);
//   BaoLoi("Da ghi xong danh sach vao file");
		cout << "Save file success";
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
	char menu[6][20] = {
		"Ma Sach",
		"Ten Sach",
		"Tac Gia",
		"So Trang",
		"Nha Xuat Ban",
		"The Loai"
	};
	Draw_frame(X, Y);
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
	int x = 50 , dem = 2;
	gotoxy(x, 5);
	ShowConsoleCursor(true);
	cls(4, 60, 2, 110);
	while (1){
	Nhap:
		Draw_frame(X, Y);
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
		
		// draw border for input
		SetColor(0);
		DrawBorder(16, dem + 5, 20, 2, 3);
		DrawBorder(16, dem + 8, 20, 2, 3);
		DrawBorder(16, dem + 11, 20, 2, 3);
		DrawBorder(16, dem + 14, 20, 2, 3);
		DrawBorder(16, dem + 17, 20, 2, 3);
		
		gotoxy(17, dem + 6);
		cin >> sach.NXB;
		
		gotoxy(17, dem + 9);
		cin >> sach.sotrang;
		
		gotoxy(17, dem + 12);
		fflush(stdin);
		char temp[150];

		gets(temp);
		strcpy(sach.tensach, temp);
		gotoxy(17, dem + 15);
		
		gets(sach.tacgia);
		gotoxy(17, dem + 18);
		
		gets(sach.theloai);

  	// 	check continue
		cout << "\n";
		char exit;
		gotoxy(10, 23);
		cout << "An ENTER De Tiep Tuc.";
		gotoxy(8, 24);
		cout << "An Phim Bat Ki De Thoat!";

		if(exit = getch() == Enter){
			displayStr("Them Dau Sach Thanh Cong!", 6, 29);
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
		
//	 reset ds[] -> add
//	if (flag){
//		while (ds.soLuong > 0){
//			delete ds.dausach[ds.soLuong - 1];
//			ds.soLuong--;
//		}
//	}++

//  start add sach
	while (ds.soLuong < MAX_DAU_SACH){
//		displayDS_DAUSACH(ds);
		
		ds.dausach[ds.soLuong] = new DAU_SACH;
		bool temp = NhapDauSach(ds, sach);

		*ds.dausach[ds.soLuong] = sach;
		ds.soLuong++;
		
		if (!temp){
//			SaveFile(ds, "C:\\Users\\thuancutee\\Desktop\\test.txt");
//			OpenFile(ds, "C:\\Users\\thuancutee\\Desktop\\test.txt");
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
//void TreetoArray(Tree t, DocGia a[], int &i){
//	if (t == NULL)
//		return;
//
//	else{
//		ChuyenCayThanhMang(t->pLeft, a, i);
//		a[i++] = t->info;
//		ChuyenCayThanhMang(t->pRight, a, i);
//	}
//}

void displayThe_DOCGIA(Tree &t){
	system("color f0");
	int i = 0;
	if(t == NULL)
		return;
		
	char menu[4][20] = {
		"Ma Doc Gia",
		"Ho",
		"Ten",
		"Phai (Nam/Nu)"
	};
	Draw_frame(X, Y);
	SetColor(4);
	int step = 52;
	for(int i=0; i<4; i++){
		gotoxy(step, 4);
		if(i == 0)
			step += 16;
		else
			step += 20;
		cout << menu[i];
	}

	SetColor(0);
	gotoxy(47, 3 + i);
	cout << t->info.maThe;
	gotoxy(58, 3 + i);
	cout << t->info.ho << endl;
	gotoxy(68, 3 + i);
	cout << t->info.ten << endl;
	gotoxy(79, 3 + i);
	cout << t->info.phai << endl;
	gotoxy(89, 3 + i);
	cout << t->info.trangThai << endl;
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

bool AddDocGia(Tree& t, int ID) {
	int x = 50 , dem = 2;
	gotoxy(x, 5);
	ShowConsoleCursor(true);
	cls(4, 60, 2, 110);

	ShowConsoleCursor(true);
	system("cls");
	Draw_frame(X, Y);

	
	// handle add
	if (t == NULL) {
		// cout
		CAYNHIPHANTK_TheDocGia* p = new CAYNHIPHANTK_TheDocGia;
		p->info.maThe = ID;

		while(1){
			Draw_frame(X, Y);
			DrawBorder(1, 3, 45, 35, 3);
			DrawBorder(48, 3, 82, 35, 3);
//			displayThe_DOCGIA(t);

			SetColor(3);
			gotoxy(3, 5);
			cout << "Ma Doc Gia";

			DrawBorder(16, dem + 2, 27, 2, 3);
			gotoxy(27, 5);
			cout << p->info.maThe;

			gotoxy(17, dem + 3);
			SetColor(3);
			gotoxy(3, dem + 6);
			cout << "Ho";
			gotoxy(3, dem + 9);
			cout << "Ten";
			gotoxy(3, dem + 12);
			cout << "Phai(Nam/Nu)";

			SetColor(0);
			DrawBorder(16, dem + 5, 27, 2, 3);
			DrawBorder(16, dem + 8, 27, 2, 3);
			DrawBorder(16, dem + 11, 27, 2, 3);
			
			// bat dau nhap
			fflush(stdin);
			gotoxy(18, dem + 6);
			getline(cin, p->info.ho);
			gotoxy(18, dem + 9);
			getline(cin, p->info.ten);
			gotoxy(18, dem + 12);
			getline(cin, p->info.phai);
			p->info.trangThai = 0;
			p->pLeft = NULL;
			p->pRight = NULL;

	//		t.soLuongDocGia++;
			t = p;

	  	// 	check continue
			cout << "\n";
			char exit;
			gotoxy(15, 17);
			SetColor(3);
			cout << "An ENTER De Tiep Tuc.";
			gotoxy(13, 18);
			cout << "An Phim Bat Ki De Thoat!";
			if(exit = getch() == Enter){
				displayStr("Them Doc Gia Thanh Cong!", 10, 21);
				return true;
			}
			else
				return false;
		}

	}
	else {
		if (t->info.maThe > ID) {
			AddDocGia(t->pLeft, ID);
		}
		if (t->info.maThe < ID) {
			AddDocGia(t->pRight, ID);
		}
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
	cls(4, 60, 2, 110);
	system("color f0");
	ShowConsoleCursor(false);
	int chon, res, arr[3] = {55, 57, 54};
	while (1){
		SetBGColor(3);
		chon = MenuThuancutee(CauA, 3, 0, 29, arr, 50);
		SetBGColor(15);
		switch (chon){
		case 1:
			AddDocGia(t, randomID());
			break;
		case 2:
			system("cls");
//			displayDS_DAUSACH(ds);
			break;
		case 3:
			
//			draw_case3();
			break;
		}
		Sleep(1000);
   }
}

// Cau c: NHap thong tin dau sach va danh ma sach tu dong
void draw_case3(){
	cls(4, 50, 2, 100);
	DS_DAUSACH ds;
	int chon, flag = 1, arr[7] = {55, 55, 55, 55, 55, 55, 55};
	system("color f0");
	while (1){
		chon = MenuThuancutee(CauC, 7, 5, 30, arr, 52);
		switch (chon){
		case 1:
			system("cls");
			NhapDSDS(ds);
			break;
		case 2:
			system("cls");
			displayDS_DAUSACH(ds);
			break;
		case 3:
//			draw_case3();
			break;
		case 4:
			break;
		}
		Sleep(1000);
   }
}

void Menu(char td[][100], Tree t){
	system("color f0");
	cls(4, 35, 2, 100);
	int chon, arr[4] = {57, 59, 58, 61};
	while (1){
		chon = MenuThuancutee(td, 4, 5, 22, arr, 53);
		switch (chon){
		case 1:
			draw_case1(t);
			break;
		case 2:
			draw_case3();
			break;
		case 3:
			draw_case3();
			break;
//		case 4:
			
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
