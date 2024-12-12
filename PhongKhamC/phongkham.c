#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPTIONS 7
#define MAX_OPTION_LENGTH 100
#define MAX_BENHNHAN 100
#define MAX_CUOCHEN 100
#define MAX_DICHVU 10

// Hàm tiện ích để xóa màn hình
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Hàm hiển thị menu với điều hướng là >> <<
int menuGiaoDien(char options[MAX_OPTIONS][100], int numOptions) {
  int selection = 0;
  char key;

  do {
    clearScreen();
    printf("+-------------------------------------------------------+\n");
    printf("|~~~~~~~~~~~~~~~ PHONG KHAM DA KHOA ~~~~~~~~~~~~~~~|\n");
    printf("+-------------------------------------------------------+\n\n");

    for (int i = 0; i < numOptions; ++i) {
      if (i == selection)
        printf(">> %s <<\n", options[i]);
      else
        printf("   %s\n", options[i]);
    }

    key = _getch(); // Nhận phím người dùng
    if (key == 72)  // Phím mũi tên lên
      selection = (selection - 1 + numOptions) % numOptions;
    else if (key == 80) // Phím mũi tên xuống
      selection = (selection + 1) % numOptions;
    else if (key == 13) // Phím Enter
      break;
  } while (1);

  return selection;
}

// Cấu trúc Dịch Vụ
typedef struct {
  char tenDichVu[100];
  float gia;
} DichVu;

// Cấu trúc Bệnh Nhân
typedef struct {
  int id;
  char ten[100];
  int tuoi;
  char diachi[100];
  char sdt[20];
  DichVu dichVuSuDung[MAX_DICHVU]; // Giới hạn số dịch vụ là 10
  int dichVuCount;
  float tongTien;
} BenhNhan;

BenhNhan danhSachBenhNhan[MAX_BENHNHAN];
int soBenhNhan = 0;

// Cấu trúc Cuộc Hẹn
typedef struct {
  int idBenhNhan;
  char ngayHen[20];
  char gioHen[10];
  char lyDo[100];
} CuocHen;

CuocHen danhSachCuocHen[MAX_CUOCHEN];
int soCuocHen = 0;

// Hàm nhập thông tin bệnh nhân
BenhNhan nhapBenhNhan(int id) {
  BenhNhan bn;
  bn.id = id;
  printf("Nhap ten benh nhan: ");
  fgets(bn.ten, sizeof(bn.ten), stdin);
  bn.ten[strcspn(bn.ten, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

  printf("Nhap tuoi benh nhan: ");
  scanf("%d", &bn.tuoi);
  getchar(); // Đọc ký tự xuống dòng

  printf("Nhap dia chi benh nhan: ");
  fgets(bn.diachi, sizeof(bn.diachi), stdin);
  bn.diachi[strcspn(bn.diachi, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

  printf("Nhap so dien thoai benh nhan: ");
  fgets(bn.sdt, sizeof(bn.sdt), stdin);
  bn.sdt[strcspn(bn.sdt, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

  bn.dichVuCount = 0;
  bn.tongTien = 0;
  return bn;
}

// Hàm thêm bệnh nhân
void themBenhNhan() {
  int id = soBenhNhan + 1;
  BenhNhan bn = nhapBenhNhan(id);
  danhSachBenhNhan[soBenhNhan++] = bn;
  printf("Them benh nhan thanh cong!\n");
  clearScreen();
}

// Hàm hiển thị thông tin bệnh nhân
void hienThiBenhNhan() {
  clearScreen();
  if (soBenhNhan == 0) {
    printf("Danh sach benh nhan trong!\n");
  } else {
    for (int i = 0; i < soBenhNhan; i++) {
      printf("ID: %d | Ten: %s | Tuoi: %d | Dia chi: %s | SDT: %s\n",
             danhSachBenhNhan[i].id, danhSachBenhNhan[i].ten,
             danhSachBenhNhan[i].tuoi, danhSachBenhNhan[i].diachi,
             danhSachBenhNhan[i].sdt);
    }
  }
  printf("\nNhap phim bat ky de quay lai.");
  getchar(); // Đợi nhấn phím bất kỳ để quay lại
}

// Hàm in hóa đơn
void inHoaDon(BenhNhan bn) {
  clearScreen();
  printf("\n=== HOA DON THANH TOAN ===\n");
  printf("Ten benh nhan: %s\n", bn.ten);
  printf("Dia chi: %s\n", bn.diachi);
  printf("SDT: %s\n", bn.sdt);
  printf("Tong tien: %.2f VND\n", bn.tongTien);
  printf("\nChi tiet cac dich vu:\n");
  for (int i = 0; i < bn.dichVuCount; i++) {
    printf("- %s: %.2f VND\n", bn.dichVuSuDung[i].tenDichVu,
           bn.dichVuSuDung[i].gia);
  }
  printf("\n=========================\n");
  printf("Nhap phim bat ky de quay lai.");
  getchar(); // Chờ nhấn phím bất kỳ để quay lại
}

// Hàm quản lý thanh toán
void quanLyThanhToan() {
  while (1) { // Bắt đầu vòng lặp
    int id;
    clearScreen();
    printf("Nhap ID benh nhan can thanh toan: ");
    if (!(scanf("%d", &id))) {
      printf("Nhap ID khong hop le! Vui long thu lai!\n");
      getchar(); // Đọc ký tự xuống dòng sau khi nhập lỗi
      continue;
    }

    // Đọc ký tự xuống dòng dư thừa sau scanf
    getchar();

    int found = 0;
    for (int i = 0; i < soBenhNhan; i++) {
      if (danhSachBenhNhan[i].id == id) {
        found = 1;
        printf("Them dich vu cho benh nhan %s\n", danhSachBenhNhan[i].ten);

        // Nhập dịch vụ và tính tiền ở đây
        printf("Nhap ten dich vu: ");
        fgets(danhSachBenhNhan[i]
                  .dichVuSuDung[danhSachBenhNhan[i].dichVuCount]
                  .tenDichVu,
              sizeof(danhSachBenhNhan[i]
                         .dichVuSuDung[danhSachBenhNhan[i].dichVuCount]
                         .tenDichVu),
              stdin);
        danhSachBenhNhan[i]
            .dichVuSuDung[danhSachBenhNhan[i].dichVuCount]
            .tenDichVu[strcspn(
                danhSachBenhNhan[i]
                    .dichVuSuDung[danhSachBenhNhan[i].dichVuCount]
                    .tenDichVu,
                "\n")] = '\0';

        printf("Nhap gia dich vu: ");
        scanf("%f", &danhSachBenhNhan[i]
                         .dichVuSuDung[danhSachBenhNhan[i].dichVuCount]
                         .gia);

        danhSachBenhNhan[i].tongTien +=
            danhSachBenhNhan[i]
                .dichVuSuDung[danhSachBenhNhan[i].dichVuCount]
                .gia;
        danhSachBenhNhan[i].dichVuCount++;

        // In hóa đơn sau khi thêm dịch vụ
        inHoaDon(danhSachBenhNhan[i]);

        break;
      }
    }

    if (!found) {
      printf("Khong tim thay benh nhan voi ID: %d. Vui long thu lai!\n", id);
    } else {
      break;
    }
    getchar(); // Chờ nhấn phím bất kỳ để quay lại
  }
}

// Hàm nhập cuộc hẹn
CuocHen nhapCuocHen() {
  CuocHen ch;
  printf("Nhap ID benh nhan: ");
  scanf("%d", &ch.idBenhNhan);
  getchar(); // Đọc ký tự xuống dòng sau khi nhập ID

  printf("Nhap ngay hen (dd/mm/yyyy): ");
  fgets(ch.ngayHen, sizeof(ch.ngayHen), stdin);
  ch.ngayHen[strcspn(ch.ngayHen, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

  printf("Nhap gio hen (hh:mm): ");
  fgets(ch.gioHen, sizeof(ch.gioHen), stdin);
  ch.gioHen[strcspn(ch.gioHen, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

  printf("Nhap ly do hen: ");
  fgets(ch.lyDo, sizeof(ch.lyDo), stdin);
  ch.lyDo[strcspn(ch.lyDo, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng

  return ch;
}

// Hàm hiển thị danh sách cuộc hẹn
void hienThiCuocHen() {
  clearScreen();
  if (soCuocHen == 0) {
    printf("Khong co cuoc hen nao!\n");
  } else {
    for (int i = 0; i < soCuocHen; i++) {
      printf("ID Benh Nhan: %d | Ngay Hen: %s | Gio Hen: %s | Ly Do: %s\n",
             danhSachCuocHen[i].idBenhNhan, danhSachCuocHen[i].ngayHen,
             danhSachCuocHen[i].gioHen, danhSachCuocHen[i].lyDo);
    }
  }
  printf("\nNhap phim bat ky de quay lai.");
  getchar(); // Chờ nhấn phím bất kỳ để quay lại
}

// Tìm và hủy cuộc hẹn
void huyHen(int idBenhNhan) {
  int found = 0;
  for (int i = 0; i < soCuocHen; i++) {
    if (danhSachCuocHen[i].idBenhNhan == idBenhNhan) {
      found = 1;
      for (int j = i; j < soCuocHen - 1; j++) {
        danhSachCuocHen[j] =
            danhSachCuocHen[j + 1]; // Dịch các phần tử còn lại lên
      }
      soCuocHen--; // Giảm số lượng cuộc hẹn
      printf("\nHuy cuoc hen thanh cong!\n");
      return;
    }
  }

  if (!found) {
    printf("Khong tim thay cuoc hen voi ID benh nhan: %d\n", idBenhNhan);
  }
}

// Hủy cuộc hẹn
void huyCuocHen() {
  int id;
  clearScreen();
  printf("Nhap ID benh nhan can huy cuoc hen: ");

  if (!(scanf("%d", &id))) {
    printf("Nhap ID khong hop le! Vui long thu lai!\n");
    getchar(); // Đọc ký tự xuống dòng sau khi nhập lỗi
  }

  huyHen(id); // Gọi hàm huyHen với ID cần hủy

  printf("\nNhap phim bat ky de quay lai.");
  getchar(); // Chờ nhấn phím bất kỳ để quay lại
}

// Menu chính
void menu() {
  char options[MAX_OPTIONS][MAX_OPTION_LENGTH] = {
      "1. Them benh nhan moi",
      "2. Hien thi danh sach benh nhan",
      "3. Quan ly thanh toan va hien thi hoa don",
      "4. Them cuoc hen",
      "5. Hien thi danh sach cuoc hen",
      "6. Huy cuoc hen",
      "7. Thoat"};

  int numOptions = 7;

  while (1) {
    int choice = menuGiaoDien(options, numOptions);
    switch (choice) {
    case 0:
      themBenhNhan();
      break;
    case 1:
      hienThiBenhNhan();
      break;
    case 2:
      quanLyThanhToan();
      break;
    case 3:
      danhSachCuocHen[soCuocHen++] = nhapCuocHen();
      break;
    case 4:
      hienThiCuocHen();
      break;
    case 5:
      huyCuocHen();
      break;
    case 6:
      // ghiDanhSachBenhNhan();
      // ghiDanhSachCuocHen();
      clearScreen();
      printf("Du lieu da duoc luu. Thoat chuong trinh.\n");
      return;
    default:
      break;
    }
  }
}

int main() {
  menu();
  return 0;
}
