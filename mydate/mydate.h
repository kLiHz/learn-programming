#ifndef _MYDATE_H_
#define _MYDATE_H_

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
class MyDate 
{
public:
    enum {day_print_on, day_print_off, day_print, Chinese, Normal, English, American};
    MyDate();
    MyDate(int y_, int m_, int d_);

    static void set_style(int t);
    static int is_leap(int);
    static MyDate get_suggestion(int, int, int);
    static int days(int, int);
    static bool is_legal(int ty, int tm, int td);

    bool set(int y_, int m_, int d_);
    void set(const MyDate& );

    void tomorrow();
    void yesterday();
    void forward(int);
    void rollback(int);
    void rolling(int);
    void rolling_1(int);

    void print() const;
    void print_day() const;
    int  get_day() const;
    int  days() const;

    bool equals(const MyDate& ) const;
    int  compare(const MyDate& ) const;
    bool is_leap() const;

    int  get_gap(const MyDate& ) const;
    int  get_gap_1(const MyDate& ) const;
    int  get_gap_2(const MyDate& ) const;

private:
    int  year, month, day;
    static int style;
    static bool if_print_day;
};
int MyDate::style = MyDate::Chinese;
bool MyDate::if_print_day = false;

#endif
