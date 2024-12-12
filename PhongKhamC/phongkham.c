#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_PHONE_LENGTH 15
#define MAX_DATE_LENGTH 11
#define MAX_TIME_LENGTH 6
#define MAX_REASON_LENGTH 100

// Cấu trúc Bệnh Nhân
typedef struct {
  int id;
  char ten[MAX_NAME_LENGTH];
  int tuoi;
  char diachi[MAX_ADDRESS_LENGTH];
  char sdt[MAX_PHONE_LENGTH];
} BenhNhan;

// Cấu trúc Cuộc Hẹn
typedef struct {
  int idBenhNhan;
  char ngayHen[MAX_DATE_LENGTH];
  char gioHen[MAX_TIME_LENGTH];
  char lyDo[MAX_REASON_LENGTH];
} CuocHen;

BenhNhan danhSachBenhNhan[MAX_PATIENTS];
int soBenhNhan = 0;

CuocHen danhSachCuocHen[MAX_APPOINTMENTS];
int soCuocHen = 0;

void clearScreen() { system("cls"); }

void themBenhNhan() {
  if (soBenhNhan >= MAX_PATIENTS) {
    printf("Danh sach benh nhan da day!\n");
    return;
  }

  BenhNhan bn;
  bn.id = soBenhNhan + 1;

  clearScreen();
  printf("Nhap ten benh nhan: ");
  fflush(stdin);
  fgets(bn.ten, MAX_NAME_LENGTH, stdin);
  bn.ten[strcspn(bn.ten, "\n")] = 0;

  printf("Nhap tuoi: ");
  scanf("%d", &bn.tuoi);
  fflush(stdin);

  printf("Nhap dia chi: ");
  fgets(bn.diachi, MAX_ADDRESS_LENGTH, stdin);
  bn.diachi[strcspn(bn.diachi, "\n")] = 0;

  printf("Nhap so dien thoai: ");
  fgets(bn.sdt, MAX_PHONE_LENGTH, stdin);
  bn.sdt[strcspn(bn.sdt, "\n")] = 0;

  danhSachBenhNhan[soBenhNhan++] = bn;
  printf("Them benh nhan thanh cong!\n");
  getch();
}

void hienThiBenhNhan() {
  clearScreen();
  if (soBenhNhan == 0) {
    printf("Danh sach benh nhan trong!\n");
  } else {
    for (int i = 0; i < soBenhNhan; i++) {
      printf("ID: %d, Ten: %s, Tuoi: %d, Dia Chi: %s, SDT: %s\n",
             danhSachBenhNhan[i].id, danhSachBenhNhan[i].ten,
             danhSachBenhNhan[i].tuoi, danhSachBenhNhan[i].diachi,
             danhSachBenhNhan[i].sdt);
    }
  }
  printf("\nNhap phim bat ky de quay lai.");
  getch();
}

void themCuocHen() {
  if (soCuocHen >= MAX_APPOINTMENTS) {
    printf("Danh sach cuoc hen da day!\n");
    return;
  }

  CuocHen ch;
  printf("Nhap ID benh nhan: ");
  scanf("%d", &ch.idBenhNhan);
  fflush(stdin);

  printf("Nhap ngay hen (dd/mm/yyyy): ");
  fgets(ch.ngayHen, MAX_DATE_LENGTH, stdin);
  ch.ngayHen[strcspn(ch.ngayHen, "\n")] = 0;

  printf("Nhap gio hen (hh:mm): ");
  fgets(ch.gioHen, MAX_TIME_LENGTH, stdin);
  ch.gioHen[strcspn(ch.gioHen, "\n")] = 0;

  printf("Nhap ly do hen: ");
  fgets(ch.lyDo, MAX_REASON_LENGTH, stdin);
  ch.lyDo[strcspn(ch.lyDo, "\n")] = 0;

  danhSachCuocHen[soCuocHen++] = ch;
  printf("Them cuoc hen thanh cong!\n");
  getch();
}

void hienThiCuocHen() {
  clearScreen();
  if (soCuocHen == 0) {
    printf("Khong co cuoc hen nao!\n");
  } else {
    for (int i = 0; i < soCuocHen; i++) {
      printf("ID Benh Nhan: %d, Ngay Hen: %s, Gio Hen: %s, Ly Do: %s\n",
             danhSachCuocHen[i].idBenhNhan, danhSachCuocHen[i].ngayHen,
             danhSachCuocHen[i].gioHen, danhSachCuocHen[i].lyDo);
    }
  }
  printf("\nNhap phim bat ky de quay lai.");
  getch();
}

void huyCuocHen() {
  int id;
  clearScreen();
  printf("Nhap ID benh nhan can huy cuoc hen: ");
  scanf("%d", &id);

  int found = 0;
  for (int i = 0; i < soCuocHen; i++) {
    if (danhSachCuocHen[i].idBenhNhan == id) {
      for (int j = i; j < soCuocHen - 1; j++) {
        danhSachCuocHen[j] = danhSachCuocHen[j + 1];
      }
      soCuocHen--;
      found = 1;
      break;
    }
  }

  if (found) {
    printf("\nHuy cuoc hen thanh cong!\n");
  } else {
    printf("Khong tim thay cuoc hen voi ID benh nhan: %d\n", id);
  }

  printf("\nNhap phim bat ky de quay lai.");
  getch();
}

void menu() {
  char *options[] = {"1.Them benh nhan moi", "2.Hien thi danh sach benh nhan",
                     "3.Them cuoc hen",      "4.Hien thi danh sach cuoc hen",
                     "5.Huy cuoc hen",       "6.Thoat"};
  int numOptions = sizeof(options) / sizeof(options[0]);

  while (1) {
    clearScreen();
    printf("+-------------------------------------------------------+\n");
    printf("|~~~~~~~~~~~~~~~ PHONG KHAM DA KHOA ~~~~~~~~~~~~~~~|\n");
    printf("+-------------------------------------------------------+\n\n");

    for (int i = 0; i < numOptions; i++) {
      printf("%s\n", options[i]);
    }

    printf("\nChon chuc nang (1-%d): ", numOptions);
    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      themBenhNhan();
      break;
    case 2:
      hienThiBenhNhan();
      break;
    case 3:
      themCuocHen();
      break;
    case 4:
      hienThiCuocHen();
      break;
    case 5:
      huyCuocHen();
      break;
    case 6:
      printf("Thoat chuong trinh.\n");
      return;
    default:
      printf("Lua chon khong hop le. Vui long thu lai.\n");
      getch();
      break;
    }
  }
}

int main() {
  menu();
  return 0;
}