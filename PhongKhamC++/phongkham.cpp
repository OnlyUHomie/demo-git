// Đổi thư viện nếu dùng Mac hoặc Linux
#include <algorithm>
#include <conio.h> // Chỉ sử dụng cho Windows
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits> // Để sử dụng std::numeric_limits
#include <string>
#include <vector>

using namespace std;

// Hàm tiện ích để xóa màn hình
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Hàm hiển thị menu chính với điều hướng là >> <<
int menuGiaoDien(vector<string> options) {
  int selection = 0;
  char key;

  do {
    clearScreen();
    cout << "+-------------------------------------------------------+\n";
    cout << "|~~~~~~~~~~~~~~~ PHONG KHAM DA KHOA ~~~~~~~~~~~~~~~|\n";
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

// Lớp Dịch Vụ
class DichVu {
public:
  string tenDichVu;
  float gia;

  DichVu(string ten, float gia) : tenDichVu(ten), gia(gia) {}
};

// Lớp Bệnh Nhân
class BenhNhan {
private:
  int id;
  string ten;
  int tuoi;
  string diachi;
  string sdt;
  vector<DichVu> dichVuSuDung;
  float tongTien = 0;

public:
  BenhNhan(int id, string ten, int tuoi, string diachi, string sdt)
      : id(id), ten(ten), tuoi(tuoi), diachi(diachi), sdt(sdt) {}

  void ShowInfo() const {
    cout << "ID: " << id << ", Ten: " << ten << ", Tuoi: " << tuoi
         << ", Dia Chi: " << diachi << ", SDT: " << sdt << endl;
  }

  int getID() const { return id; }
  string getTen() const { return ten; }
  int getTuoi() const { return tuoi; }
  string getDiaChi() const { return diachi; }
  string getSDT() const { return sdt; }

  static BenhNhan nhapBenhNhan(int id) {
    string ten, diachi, sdt;
    int tuoi;
    clearScreen();
    cout << "Nhap ten benh nhan: ";
    cin.ignore();
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

  void themDichVu() {
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

  void hienThiHoaDon() const {
    cout << "\n--- Hoa don cua benh nhan " << ten << " ---\n";
    for (const auto &dv : dichVuSuDung) {
      cout << "Dich vu: " << dv.tenDichVu << " - Gia: " << dv.gia << " VND\n";
    }
    cout << "Tong tien: " << tongTien << " VND\n";
  }
};

// Danh sách bệnh nhân
vector<BenhNhan> danhSachBenhNhan;

// Lưu danh sách bệnh nhân ra file
void ghiDanhSachBenhNhan() {
  ofstream file("benhnhan.txt");
  for (const auto &bn : danhSachBenhNhan) {
    file
        << "\nID:" << bn.getID() << " | Ten:" << bn.getTen()
        << " | Tuoi:" << bn.getTuoi() << " | Diachi:" << bn.getDiaChi()
        << " | SDT:" << bn.getSDT()
        << "\n----------------------------------------------------------------";
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

// Lớp Cuộc Hẹn
class CuocHen {
private:
  int idBenhNhan;
  string ngayHen;
  string gioHen;
  string lyDo;
  vector<CuocHen> danhSachCuocHen;

public:
  CuocHen(int idBenhNhan, string ngayHen, string gioHen, string lyDo)
      : idBenhNhan(idBenhNhan), ngayHen(ngayHen), gioHen(gioHen), lyDo(lyDo) {}

  void hienThiThongTin() const {
    cout << "ID Benh Nhan: " << idBenhNhan << ", Ngay Hen: " << ngayHen
         << ", Gio Hen: " << gioHen << ", Ly Do: " << lyDo << endl;
  }

  int getIDBN() const { return idBenhNhan; }
  string getNgayHen() const { return ngayHen; }
  string getGioHen() const { return gioHen; }
  string getLyDo() const { return lyDo; }

  static CuocHen nhapCuocHen() {
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

  /*void huyHen(vector<CuocHen> &danhSachCuocHen) {
    for (auto it = danhSachCuocHen.begin(); it != danhSachCuocHen.end(); ++it) {
      if (it->getIDBN() == idBenhNhan) {
        danhSachCuocHen.erase(it);
        break;
      }
    }
  }*/
};

vector<CuocHen> danhSachCuocHen;

// Lưu dữ liệu vào file danh sách cuộc hẹn
void ghiDanhSachCuocHen() {
  ofstream file("cuochen.txt");
  for (const auto &bn : danhSachCuocHen) {
    file
        << "\nIDBN:" << bn.getIDBN() << " | NgayHen:" << bn.getNgayHen()
        << " | GioHen:" << bn.getGioHen() << " | LyDo:" << bn.getLyDo()
        << "\n----------------------------------------------------------------";
  }
  file.close();
}

// Thêm cuộc hẹn
void themCuocHen() {
  CuocHen ch = CuocHen::nhapCuocHen();
  danhSachCuocHen.push_back(ch);
  ghiDanhSachCuocHen(); // Ghi ngay vào file
  cout << "Them cuoc hen thanh cong!\n";
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

int main() {
  menu();
  return 0;
}
