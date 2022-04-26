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
    MyDate() : year(1970), month(1), day(1) {}

    MyDate(int y_, int m_, int d_) : MyDate() {
        if (is_legal(y_,m_,d_)) { year = y_; month = m_; day = d_; }
    }

    enum class Day {
        Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
    };

    enum class DayFormat {
        DAY_PRINT_ON, DAY_PRINT_OFF, Normal, Chinese, English, American 
    };

    static void     set_format(DayFormat fmt);
    static int      is_leap(int);
    static MyDate   get_suggestion(int, int, int);
    static int      days(int, int);
    static bool     is_legal(int ty, int tm, int td);

    static int gap  (const MyDate& a, const MyDate& b);
    static int gap_1(const MyDate& a, const MyDate& b);
    static int gap_2(const MyDate& a, const MyDate& b);

    bool set(int y_, int m_, int d_);
    void set(const MyDate& );

    int get_year()  const { return this->year;    };
    int get_month() const { return this->month;   };
    int get_day()   const { return this->day;     };

    MyDate tomorrow()   const;
    MyDate yesterday()  const;
    MyDate& forward(int);
    MyDate& rollback(int);
    MyDate& rolling(int);

    std::string to_string() const;
    Day what_day() const;

    bool equals_to(const MyDate& ) const;
    bool is_leap() const;
    friend bool operator <(const MyDate& a, const MyDate& b);
    friend bool operator >(const MyDate& a, const MyDate& b);
    friend bool operator==(const MyDate& a, const MyDate& b);
    friend bool operator!=(const MyDate& a, const MyDate& b);

    friend int operator-(MyDate const & a, MyDate const & b);
    friend MyDate operator+(MyDate const & a, int);
    friend MyDate operator-(MyDate const & a, int);

private:
    int year, month, day;
    static DayFormat print_format;
    static bool print_day_of_the_week;
    std::string day_string() const;
    static std::map<Day, std::string> chs_str;
    static std::map<Day, std::string> eng_str;
};

#endif
