#ifndef __DATA_T_H__
#define __DATA_T_H__

// ĐỔI CẤU TRÚC BỘ DỮ LIỆU + TÊN
typedef struct car_s{
    char bien_so[13];
    struct time{
        int hh;
        int mm;
        int ss;
        int DD;
        int MM;
        int YYYY;
    }time;
    int take_io;
}   car_t;

typedef car_t data_t;

// typedef int keyT;  // to find
// THAY ĐỔI KEY DÙNG ĐỂ SO SÁNH
typedef char* keyT;

void showData(data_t trans);
void showData_3(data_t trans);
// data_t convert(int number);
data_t convert(char *End, char *Viet);

int eq(const keyT key, const data_t* dat);
// less than
int lt(const keyT key, const data_t* dat);
// great than
int gt(const keyT key, const data_t* dat);

#endif