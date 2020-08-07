#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <iomanip>
#include <cstdlib>
#include "HangSo.h"

#pragma warning (disable:4996)
#pragma warning (disable:4018)
#pragma warning (disable:4551)
#pragma warning (disable:4751)
#pragma warning (disable:4715)
#pragma warning (disable:26495)
#pragma warning (disable:6262)

using namespace std;

//int pointer = 10;
//int toadoXBox = 65;
//int toadoYBox = 9;

struct Date{
	int Ngay;
	int Thang;
	int Nam;
};

//_____________DANH MUC SACH_________
// su dung danh sach lien ket don
struct DANH_MUC_SACH{
	//info
	string maSach;
	string viTri;//hang-ke
	int trangThai;//0: cho muon duoc, 1: da co doc gia muon, 2: sach da thanh ly
	
	//pointer
	DANH_MUC_SACH* pNext;
};

struct DS_DANHMUCSACH{
	int SoLuong = 0;
	DANH_MUC_SACH* pHead = NULL;
};

typedef struct DS_DANHMUCSACH* PTR_DMS;

//__________DAU SACH_____________
// su dung danh sach tuyen tinh la 1 mang con tro
//struct DauSach
//{
//	string ISBN;
//	string tenSach;
//	string tacGia;
//	int soTrang;
//	int NXB; //nam
//	string theLoai;
//
//	int demSoLanMuon;//cau j
//
//	DS_DanhMucSach DMS;
//};
struct DAU_SACH{
	string ISBN; // ma sach quoc te

	string tensach;
	string tacgia;
	int sotrang;
	int NXB; //nam xuat ban

	int demSoLanMuon;//cau j
	string theloai;
	//	char theloai[50];
	DS_DANHMUCSACH *DMS;//Con tro se tro den cac dau sach tuong ung
};

struct DS_DAUSACH{
	int soLuong = 0;
	DAU_SACH* dausach[MAX_DAU_SACH];
};

//________MUON TRA___________
// Su dung danh sach lien ket kep
struct MUON_TRA{
	string maSach;
	DATE NgayMuon;
	DATE NgayTra;
	int trangThai;//0: la sach ddang muon, 1: la sach da tra, 2: lam mat sach
};

struct NODE_MUONTRA{
	MUON_TRA info;
	NODE_MUONTRA* pLeft;
	NODE_MUONTRA* pRight;
};

struct DS_MUONTRA{
	NODE_MUONTRA* pHead;
	NODE_MUONTRA* pLast;
};

//__________THE DOC GIA_________

struct DocGia{
	int maThe;
	string ho;
	string ten;
	string phai = "Nam";
	int trangThai;
	//	DS_MuonTra DS_muontra;
	DS_MUONTRA *DS_MUONTRA;
};

struct CAYNHIPHANTK_TheDocGia{
	DocGia info;

	int	soLuongDocGia = 0;
	CAYNHIPHANTK_TheDocGia* pLeft;
	CAYNHIPHANTK_TheDocGia* pRight;
};

typedef CAYNHIPHANTK_TheDocGia* Tree;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char listMainMenu[10][100] =  {
								"Quan Ly Doc Gia",
								"Quan Ly Sach",
								"Muon Tra Sach",
								"Thoat!",
								};

char 	Case_DauSach[7][100] = 		{
							 "Nhap Danh Sach Dau Sach",
                             "Tim Kiem Dau Sach",
                             "Xoa Mot Dau Sach",
                             "Ghi Danh Sach",
                             "Mo Danh Sach",
                             "Sap Xep Theo Ten Sach",
                             "Thoat!"};

char 	CauA[3][100] = 		{
							 "Them The Doc Gia Moi",
                             "Hieu Chinh The Doc Gia",
							 "Thoat!",
							 };
                             
