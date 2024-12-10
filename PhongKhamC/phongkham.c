#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h> // Sử dụng _getch trên Windows
#else
#include <termios.h>
#include <unistd.h>

#define MAX_BENHNHAN 500
#define MAX_BENHNHAN 50

// Hàm mô phỏng _getch trên hệ điều hành Unix/Linux/macOS
char _getch() {
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt); // Lấy trạng thái terminal hiện tại
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // Tắt chế độ canonical và echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Cập nhật trạng thái terminal
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Khôi phục trạng thái terminal cũ
  return ch;
}
#endif

// Hàm để xóa màn hình
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Hàm hiển thị menu chính với điều hướng là >> <<
int menuGiaoDien(char *options[], int optionCount) {
  int selection = 0;
  char key;

  do {
    clearScreen();
    printf("+-------------------------------------------------------+\n");
    printf("|~~~~~~~~~~~~~~~ PHONG KHAM DA KHOA ~~~~~~~~~~~~~~~|\n");
    printf("+-------------------------------------------------------+\n\n");
    for (int i = 0; i < optionCount; ++i) {
      if (i == selection)
        printf(">> %s <<\n", options[i]);
      else
        printf("   %s\n", options[i]);
    }

    key = _getch(); // Nhận phím từ người dùng
    if (key == 72)  // Phím mũi tên lên
      selection = (selection - 1 + optionCount) % optionCount;
    else if (key == 80) // Phím mũi tên xuống
      selection = (selection + 1) % optionCount;
    else if (key == 13) // Phím Enter
      break;
  } while (1);

  return selection;
}

struct BenhNhan() {
  int id;
  char ten[150];
  int tuoi;
  char diachi[500];
  char sdt[500];
}

// Menu chính
void menu() {
  vector<string> options = {
      "1.Them benh nhan moi",          "2.Hien thi danh sach benh nhan",
      "3.Quan ly thanh toan",          "4.Them cuoc hen",
      "5.Hien thi danh sach cuoc hen", "6.Thoat "};

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
      clearScreen();
      printf("Thoat chuong trinh.\n");
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
