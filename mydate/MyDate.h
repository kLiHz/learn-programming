#ifndef _MYDATE_H_
#define _MYDATE_H_

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <map>

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

    MyDate tomorrow();
    MyDate yesterday();
    void forward(int);
    void rollback(int);
    void rolling(int);

    enum class Day {
        Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
    };

    std::string to_string() const;
    Day what_day() const;

    bool equals_to(const MyDate& ) const;
    bool is_leap() const;
    friend bool operator <(const MyDate& a, const MyDate& b);
    friend bool operator >(const MyDate& a, const MyDate& b);
    friend bool operator==(const MyDate& a, const MyDate& b);
    friend bool operator!=(const MyDate& a, const MyDate& b);

    static int   gap(const MyDate& a, const MyDate& b);
    static int gap_1(const MyDate& a, const MyDate& b);
    static int gap_2(const MyDate& a, const MyDate& b);

private:
    int year, month, day;
    static int style;
    static bool with_what_day;
    std::string day_string() const;
    static std::map<Day, std::string> chs_str;
    static std::map<Day, std::string> eng_str;
};

#endif
