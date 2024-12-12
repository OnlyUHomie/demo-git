#ifndef BENHNHAN_H
#define BENHNHAN_H

#include "DichVu.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
  BenhNhan(int id, string ten, int tuoi, string diachi, string sdt);

  void ShowInfo() const;
  void themDichVu();
  void hienThiHoaDon() const;

  int getID() const;
  string getTen() const;
  int getTuoi() const;
  string getDiaChi() const;
  string getSDT() const;

  static BenhNhan nhapBenhNhan(int id);
};

#endif // BENHNHAN_H
