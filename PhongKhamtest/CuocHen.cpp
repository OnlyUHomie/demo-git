#include "CuocHen.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Constructor của lớp CuocHen
CuocHen::CuocHen(int idBenhNhan, string ngayHen, string gioHen, string lyDo)
    : idBenhNhan(idBenhNhan), ngayHen(ngayHen), gioHen(gioHen), lyDo(lyDo) {}

// Hiển thị thông tin cuộc hẹn
void CuocHen::hienThiThongTin() const {
  cout << "ID Benh Nhan: " << idBenhNhan << ", Ngay Hen: " << ngayHen
       << ", Gio Hen: " << gioHen << ", Ly Do: " << lyDo << endl;
}

// Getter cho ID
int CuocHen::getIDBN() const { return idBenhNhan; }

// Getter cho NgayHen
string CuocHen::getNgayHen() const { return ngayHen; }

// Getter cho GioHen
string CuocHen::getGioHen() const { return gioHen; }

// Getter cho LyDo
string CuocHen::getLyDo() const { return lyDo; }

// Nhập thông tin cuộc hẹn
CuocHen CuocHen::nhapCuocHen() {
  int id;
  string ngay, gio, lyDo;
  cout << "Nhap ID benh nhan: ";
  // Nếu người dùng nhập nhầm id thành ký tự thì sẽ nhập lại
  if (!(cin >> id)) {
    cout << "Nhap ID khong hop le! Vui long thu lai!";
    cin.clear(); // Xóa trạng thái lỗi
    cin.ignore(std::numeric_limits<std::streamsize>::max(),
               '\n'); // Bỏ qua input lỗi
  }
  cin.ignore();
  cout << "Nhap ngay hen (dd/mm/yyyy): ";
  getline(cin, ngay);
  cout << "Nhap gio hen (hh:mm): ";
  getline(cin, gio);
  cout << "Nhap ly do hen: ";
  getline(cin, lyDo);
  return CuocHen(id, ngay, gio, lyDo);
}