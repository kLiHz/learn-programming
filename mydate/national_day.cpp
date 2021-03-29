#include <iostream>
#include "MyDate.h"

int main() {
    // PRC's Nation Day
    int national_day_m = 10;
    int national_day_d = 1;
    int cnt = 0;
    // How many National Days are Sunday from 1949 to 2012?
    for (int year = 1949; year <= 2012; ++year) {
        if (MyDate(year, national_day_m, national_day_d).what_day() == MyDate::Day::Sunday) ++cnt;
    }
    std::cout << "There are " << cnt << " National Day(s) that are Sunday.\n";
}
