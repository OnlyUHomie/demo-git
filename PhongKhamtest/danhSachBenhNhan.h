#ifndef DANHSACHBENHNHAN_H
#define DANHSACHBENHNHAN_H

#include "BenhNhan.h"
#include <vector>

// Danh sách bệnh nhân
extern std::vector<BenhNhan> danhSachBenhNhan;

// Hàm quản lý bệnh nhân
void ghiDanhSachBenhNhan();
void themBenhNhan();
void hienThiBenhNhan();
void quanLyThanhToan();

#endif
