#include "Menu.h"
#include "BenhNhan.h"
#include "CuocHen.h"
#include "DichVu.h"
#include "Utils.h"
#include "danhSachBenhNhan.h"
#include "danhSachCuocHen.h"
#include <conio.h>
#include <limits>
#include <vector>

using namespace std;

// Hàm hiển thị menu chính với điều hướng là >> <<
int menuGiaoDien(vector<string> options) {
  int selection = 0;
  char key;

  do {
    clearScreen();
    cout << "+-------------------------------------------------------+\n";
    cout << "|~~~~~~~~~~~~~~~~~ PHONG KHAM DA KHOA ~~~~~~~~~~~~~~~~~~|\n";
    cout << "+-------------------------------------------------------+\n\n";
    for (size_t i = 0; i < options.size(); ++i) {
      if (i == selection)
        cout << ">> " << options[i] << " <<\n";
      else
        cout << "   " << options[i] << "\n";
    }

    key = _getch(); // Nhận phím người dùng
    if (key == 72)  // Phím mũi tên lên
      selection = (selection - 1 + options.size()) % options.size();
    else if (key == 80) // Phím mũi tên xuống
      selection = (selection + 1) % options.size();
    else if (key == 13) // Phím Enter
      break;
  } while (true);

  return selection;
}

// Menu chính
void menu() {
  vector<string> options = {"1.Them benh nhan moi",
                            "2.Hien thi danh sach benh nhan",
                            "3.Quan ly thanh toan va hien thi hoa don",
                            "4.Them cuoc hen",
                            "5.Hien thi danh sach cuoc hen",
                            "6.Huy cuoc hen",
                            "7.Thoat "};

  while (true) {
    int choice = menuGiaoDien(options);
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
      themCuocHen();
      break;
    case 4:
      hienThiCuocHen();
      break;
    case 5:
      huyCuocHen();
      break;
    case 6:
      ghiDanhSachBenhNhan();
      ghiDanhSachCuocHen();
      clearScreen();
      cout << "Du lieu da duoc luu. Thoat chuong trinh.\n";
      return;
    default:
      break;
    }
  }
}
