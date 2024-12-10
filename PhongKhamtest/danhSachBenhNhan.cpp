#include "danhSachBenhNhan.h"
#include "BenhNhan.h"
#include "Utils.h"
#include <conio.h>
#include <fstream>
#include <limits>
#include <vector>

// Danh sách bệnh nhân
std::vector<BenhNhan> danhSachBenhNhan;

// Các hàm quản lý bệnh nhân
//----------------------------------------------------------------
/*// Lưu danh sách bệnh nhân ra file txt
void ghiDanhSachBenhNhan() {
  ofstream file("benhnhan.csv");
  for (const auto &bn : danhSachBenhNhan) {
    file << "ID:" << bn.getID() << " | Ten:" << bn.getTen()
         << " | Tuoi:" << bn.getTuoi() << " | Diachi:" << bn.getDiaChi()
         << " | SDT:" << bn.getSDT() << "\n";
  }
  file.close();
}*/

// Lưu danh sách bệnh nhân ra file (theo định dạng CSV)
void ghiDanhSachBenhNhan() {
  ofstream file("benhnhan.csv");

  // Ghi tiêu đề cột
  file << "ID,Ten,Tuoi,DiaChi,SDT\n";

  // Ghi dữ liệu bệnh nhân
  for (const auto &bn : danhSachBenhNhan) {
    file << bn.getID() << "," << bn.getTen() << "," << bn.getTuoi() << ","
         << bn.getDiaChi() << "," << bn.getSDT() << "\n";
  }

  file.close();
}

// Thêm bệnh nhân
void themBenhNhan() {
  int id = danhSachBenhNhan.size() + 1;
  BenhNhan bn = BenhNhan::nhapBenhNhan(id);
  danhSachBenhNhan.push_back(bn);
  ghiDanhSachBenhNhan(); // Ghi ngay vào file
  cout << "Them benh nhan thanh cong!\n";
  cout << "Nhan mot phim bat ki de quay lai.";
  _getch();
}

// Hiển thị danh sách bệnh nhân
void hienThiBenhNhan() {
  clearScreen();
  if (danhSachBenhNhan.empty()) {
    cout << "Danh sach benh nhan trong!\n";
  } else {
    for (const auto &bn : danhSachBenhNhan) {
      bn.ShowInfo();
    }
  }
  cout << "\nNhap phim bat ky de quay lai.";
  _getch();
}

// Quản lý thanh toán
void quanLyThanhToan() {
  while (true) { // Bắt đầu vòng lặp
    int id;
    clearScreen();
    cout << "Nhap ID benh nhan can thanh toan: ";

    // Kiểm tra nhập ID hợp lệ
    if (!(cin >> id)) {
      cout << "Nhap ID khong hop le! Vui long thu lai!\n";
      cin.clear(); // Xóa trạng thái lỗi
      cin.ignore(std::numeric_limits<std::streamsize>::max(),
                 '\n'); // Bỏ qua input lỗi
      _getch();         // Dừng màn hình để hiển thị thông báo
      continue;         // Quay lại đầu vòng lặp
    }

    // Kiểm tra xem ID có tồn tại hay không
    for (auto &bn : danhSachBenhNhan) {
      if (bn.getID() == id) {
        bn.themDichVu();
        bn.hienThiHoaDon();
        cout << "\nNhap phim bat ky de quay lai.";
        _getch();
        return; // Thoát hàm sau khi thanh toán
      }
    }

    // Nếu không tìm thấy ID, yêu cầu nhập lại
    cout << "Khong tim thay benh nhan voi ID: " << id
         << ". Vui long thu lai!\n";
    _getch(); // Dừng màn hình để hiển thị thông báo
  }
}
