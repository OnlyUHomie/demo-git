#ifndef DICHVU_H
#define DICHVU_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Lớp Dịch Vụ
class DichVu {
public:
  string tenDichVu;
  float gia;

  DichVu(string ten, float gia);
};

#endif