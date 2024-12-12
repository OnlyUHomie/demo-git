#ifndef DANHSACHCUOCHEN_H
#define DANHSACHCUOCHEN_H

#include "CuocHen.h"
#include <vector>

// Danh sách bệnh nhân
extern std::vector<CuocHen> danhSachCuocHen;

// Hàm quản lý bệnh nhân
void ghiDanhSachCuocHen();
void themCuocHen();
void hienThiCuocHen();
void huyHen(vector<CuocHen> &danhSachCuocHen, int idBenhNhan);
void huyCuocHen();
#endif
