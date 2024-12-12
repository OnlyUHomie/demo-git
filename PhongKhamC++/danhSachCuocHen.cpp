#include "danhSachCuocHen.h"
#include "CuocHen.h"
#include "Utils.h"
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

// Danh sách cuộc hẹn
std::vector<CuocHen> danhSachCuocHen;

// Các hàm quản lý cuộc hẹn
//----------------------------------------------------------------
/*// Lưu dữ liệu vào file danh sách cuộc hẹn
void ghiDanhSachCuocHen() {
  ofstream file("cuochen.csv");
  for (const auto &bn : danhSachCuocHen) {
    file << "IDBN:" << bn.getIDBN() << " | NgayHen:" << bn.getNgayHen()
         << " | GioHen:" << bn.getGioHen() << " | LyDo:" << bn.getLyDo()
         << "\n";
  }
  file.close();
}*/

// Lưu danh sách bệnh nhân ra file (theo định dạng CSV)
void ghiDanhSachCuocHen() {
  ofstream file("cuochen.csv");

  // Ghi tiêu đề cột
  file << "IDBenhNhan,NgayHen,GioHen,LyDo\n";

  // Ghi dữ liệu bệnh nhân
  for (const auto &bn : danhSachCuocHen) {
    file << bn.getIDBN() << " , " << bn.getNgayHen() << " , " << bn.getGioHen()
         << " , " << bn.getLyDo() << "\n";
  }

  file.close();
}

// Thêm cuộc hẹn
void themCuocHen() {
  CuocHen ch = CuocHen::nhapCuocHen();
  danhSachCuocHen.push_back(ch);
  ghiDanhSachCuocHen(); // Ghi ngay vào file
  cout << "Them cuoc hen thanh cong!\n";
  cout << "Nhan mot phim bat ki de quay lai.";
}

// Hiển thị danh sách cuộc hẹn
void hienThiCuocHen() {
  if (danhSachCuocHen.empty()) {
    cout << "Khong co cuoc hen nao!\n";
    return;
  } else {
    for (const auto &ch : danhSachCuocHen) {
      ch.hienThiThongTin();
    }
  }
  cout << "\nNhap phim bat ky de quay lai.";
  _getch();
}

// Tìm vị trí cuộc hẹn muốn hủy
void huyHen(vector<CuocHen> &danhSachCuocHen, int idBenhNhan) {
  auto it = std::remove_if(
      danhSachCuocHen.begin(), danhSachCuocHen.end(),
      [idBenhNhan](const CuocHen &ch) { return ch.getIDBN() == idBenhNhan; });

  if (it != danhSachCuocHen.end()) {
    danhSachCuocHen.erase(it, danhSachCuocHen.end());
    cout << "\nHuy cuoc hen thanh cong!\n";
  } else {
    cout << "Khong tim thay cuoc hen voi ID benh nhan: " << idBenhNhan << endl;
  }
}

/*void huyCuocHen() {
  int id;
  clearScreen();
  cout << "Nhap ID benh nhan can huy cuoc hen: ";
  cin >> id;

  for (auto &bn : danhSachCuocHen) {
    bn.huyHen(danhSachCuocHen);
    if (bn.getIDBN() == id) {
      cout << "\nHuy cuoc hen thanh cong!";
      cout << "\nNhap phim bat ky de quay lai.";
      _getch();
      return;
    }
  }

  cout << "Benh nhan khong ton tai!\n";
  _getch();
}*/
// Hủy cuộc hẹn muốn hủy
void huyCuocHen() {
  int id;
  clearScreen();
  cout << "Nhap ID benh nhan can huy cuoc hen: ";

  // Nếu người dùng nhập nhầm id thành ký tự thì sẽ nhập lại
  if (!(cin >> id)) {
    cout << "Nhap ID khong hop le! Vui long thu lai!";
    cin.clear(); // Xóa trạng thái lỗi
    cin.ignore(std::numeric_limits<std::streamsize>::max(),
               '\n'); // Bỏ qua input lỗi
  }

  huyHen(danhSachCuocHen, id); // Gọi hàm huyHen với ID cần hủy

  cout << "\nNhap phim bat ky de quay lai.";
  _getch();
}