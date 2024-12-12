#ifndef CUOCHEN_H
#define CUOCHEN_H

#include "DichVu.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Lớp Cuộc Hẹn
class CuocHen {
private:
  int idBenhNhan;
  string ngayHen;
  string gioHen;
  string lyDo;
  vector<CuocHen> danhSachCuocHen;

public:
  CuocHen(int idBenhNhan, string ngayHen, string gioHen, string lyDo);

  void hienThiThongTin() const;

  int getIDBN() const;
  string getNgayHen() const;
  string getGioHen() const;
  string getLyDo() const;

  static CuocHen nhapCuocHen();

  /*void huyHen(vector<CuocHen> &danhSachCuocHen) {
    for (auto it = danhSachCuocHen.begin(); it != danhSachCuocHen.end(); ++it) {
      if (it->getIDBN() == idBenhNhan) {
        danhSachCuocHen.erase(it);
        break;
      }
    }
  }*/
};

#endif