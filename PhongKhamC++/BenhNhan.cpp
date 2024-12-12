#include "BenhNhan.h"
#include "DichVu.h"
#include "Utils.h" // Để sử dụng hàm clearScreen
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Constructor của lớp BenhNhan
BenhNhan::BenhNhan(int id, string ten, int tuoi, string diachi, string sdt)
    : id(id), ten(ten), tuoi(tuoi), diachi(diachi), sdt(sdt) {}

// Hiển thị thông tin bệnh nhân
void BenhNhan::ShowInfo() const {
  cout << "ID: " << id << ", Ten: " << ten << ", Tuoi: " << tuoi
       << ", Dia Chi: " << diachi << ", SDT: " << sdt << endl;
}

// Getter cho ID
int BenhNhan::getID() const { return id; }

// Getter cho tên
string BenhNhan::getTen() const { return ten; }

// Getter cho tuổi
int BenhNhan::getTuoi() const { return tuoi; }

// Getter cho địa chỉ
string BenhNhan::getDiaChi() const { return diachi; }

// Getter cho số điện thoại
string BenhNhan::getSDT() const { return sdt; }

// Nhập thông tin bệnh nhân
BenhNhan BenhNhan::nhapBenhNhan(int id) {
  string ten, diachi, sdt;
  int tuoi;

  clearScreen(); // Xóa màn hình
  cout << "Nhap ten benh nhan: ";
  // cin.ignore();
  getline(cin, ten);

  cout << "Nhap tuoi: ";
  cin >> tuoi;
  cin.ignore();

  cout << "Nhap dia chi: ";
  getline(cin, diachi);

  cout << "Nhap so dien thoai: ";
  getline(cin, sdt);

  return BenhNhan(id, ten, tuoi, diachi, sdt);
}

// Thêm dịch vụ vào danh sách sử dụng
void BenhNhan::themDichVu() {
  string tenDichVu;
  float gia;

  clearScreen();
  cout << "Nhap ten dich vu: ";
  cin.ignore();
  getline(cin, tenDichVu);

  cout << "Nhap gia dich vu: ";
  cin >> gia;

  dichVuSuDung.push_back(DichVu(tenDichVu, gia));
  tongTien += gia;

  cout << "Da them dich vu thanh cong!\n";
}

// Hiển thị hóa đơn của bệnh nhân
void BenhNhan::hienThiHoaDon() const {
  cout << "\n--- Hoa don cua benh nhan " << ten << " ---\n";
  for (const auto &dv : dichVuSuDung) {
    cout << "Dich vu: " << dv.tenDichVu << " - Gia: " << dv.gia << " VND\n";
  }
  cout << "Tong tien: " << tongTien << " VND\n";
}
