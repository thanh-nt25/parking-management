#include <stdio.h>
#include <string.h>
#include "data_t.h"

// THAY ĐỔI IN DỮ LIỆU
void showData(data_t trans) {
  // printf("%s - %s\n", data.Eng, data.Viet);
  printf("%d-%d-%d %02d:%02d:%02d %s %d\n", 
    trans.time.YYYY, trans.time.MM, trans.time.DD, 
    trans.time.hh, trans.time.mm, trans.time.ss,
    trans.bien_so, trans.take_io);
}

void showData_3(data_t trans) {
  // printf("%s - %s\n", data.Eng, data.Viet);
  printf("%-15s %02d-%02d-%02d %02d:%02d:%02d\n", trans.bien_so,
    trans.time.YYYY, trans.time.MM, trans.time.DD, 
    trans.time.hh, trans.time.mm, trans.time.ss);
}

// data_t convert(int number) { return number; }
// THAY ĐỔI THEO CẤU TRÚC DỮ LIỆU
// data_t convert(char *Eng, char *Viet){
//   data_t tmp;
//   strcpy(tmp.Eng, Eng);
//   strcpy(tmp.Viet, Viet);
//   return tmp;
// }


// equal
int eq(const keyT key, const data_t* dat) {
  return (strcmp(key, dat->bien_so) == 0); // THAY ĐỔI TRƯỜNG SO SÁNH
}

// less than
int lt(const keyT key, const data_t* dat) {
  return (strcmp(key, dat->bien_so) < 0); // THAY ĐỔI TRƯỜNG SO SÁNH
}

// great than
int gt(const keyT key, const data_t* dat) {
  return (strcmp(key, dat->bien_so) > 0); // THAY ĐỔI TRƯỜNG SO SÁNH
}