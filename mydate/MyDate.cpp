#include "MyDate.h"

MyDate::DayFormat MyDate::print_format = MyDate::DayFormat::Normal;
bool MyDate::print_day_of_the_week = false;

void MyDate::set_format(DayFormat fmt) 
{
    if (fmt == DayFormat::DAY_PRINT_ON) print_day_of_the_week = true;
    else if (fmt == DayFormat::DAY_PRINT_OFF) print_day_of_the_week = false;
    else print_format = fmt;
}

int MyDate::days(int y, int m)
{
    const static int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2)
    {
        if(is_leap(y)) return 29;
        else return 28;
    }
    else return days[m - 1];
}

bool MyDate::is_legal(int ty, int tm, int td)
{
    using std::cout; 
    using std::endl;
    bool if_y = true, if_m = true, if_d = true;
    if (ty < 1700 || ty > 2999) if_y = false;
    else if (tm < 1 || tm > 12) if_m = false;
    else if (td < 1 || td > days(ty, tm)) if_d = false;

    if (!if_y) {
        cout << ty << " is not a legal year." << endl;
        return false;
    }
    else if (!if_m) {
        cout << tm << " is not a legal month." << endl;
        return false;
    }
    else if (!if_d) {
        cout << td << " is not a legal day." << endl;
        return false;
    }
    else return true;
}

MyDate MyDate::get_suggestion(int y, int m, int d)
{
    MyDate advice;

    if (y < 700) y += 2000;
    else if (y < 1000) y += 1000;
    else if (y < 1700) y += 1000;
    else if (y > 2999) y = 2999;
    advice.year = y;

    if (m == 0) m = 1;
    else if (m < 0) m = -m;
    if (m > 12) m = m % 10;
    advice.month = m;

    if (d == 0) d = 1;
    else if (d < 1) d = -d;
    if (d > MyDate::days(y,m) && d < 32) d = MyDate::days(y,m);
    else d = d % 10;
    advice.day = d;

    return advice;
}

bool MyDate::set(int y_, int m_, int d_)
{
    if (is_legal(y_,m_,d_) == 0) 
    {
        throw get_suggestion(y_,m_,d_);
        return false;
    }
    else {
        year = y_; month = m_; day = d_;
        return true;
    }
}

void MyDate::set(const MyDate& date)
{
    year = date.year;
    month = date.month;
    day = date.day;
}

bool MyDate::is_leap() const
{ 
    return (year % 4 ==0 && year % 100 != 0) || year % 400 == 0;
}

int MyDate::is_leap(int year)
{ 
    return (year % 4 ==0 && year % 100 != 0) || year % 400 == 0;
}

std::string MyDate::to_string() const
{
    static char months_eng[13][15] = {"0","January","February","March","April",
        "May","June","July","August","September","October","November","December"};
    std::string str;
    auto year_str  = std::to_string(this->year);
    auto month_str = std::to_string(this->month);
    auto day_str   = std::to_string(this->day);
    if (print_format == DayFormat::Chinese) {
        str = year_str + "年" + month_str + "月" + day_str + "日";
        if (print_day_of_the_week) { str += "  "; str += this->day_string(); }
    }
    else if (print_format == DayFormat::Normal) {
        str = year_str + "/" + month_str + "/" + day_str;
    }
    else if (print_format == DayFormat::American) {
        if (print_day_of_the_week) { str += (this->day_string() + ", "); }
        str += (std::string(months_eng[month]) + " " + day_str + ", " + year_str);
    }
    else if (print_format == DayFormat::English) {
        if (print_day_of_the_week) { str += (this->day_string() + ", "); }
        str += (day_str + " " + months_eng[month] + ", " + year_str); 
    }
    /*else
    {
        char s[4][4]={"th","st","nd","rd"};
        if (print_format == 4) 
        {
            cout<<months_eng[month]<<" ";
            cout<<day;
            if(day>10&&day<14) cout<<s[0];
            else {
                if (day%10 > 0 && day % 10 < 4) cout<<s[day%10];
                else cout<<s[0];
            }
            cout<<", "<<year;
        }
        if (print_format == 5)
        {
            cout<<day;
            if(day>10&&day<14) cout<<s[0];
            else {
                if (day%10 > 0 && day % 10 < 4) cout<<s[day%10];
                else cout<<s[0];
            }
            cout<<" "<<months_eng[month]<<", ";
            cout<<year;
        }
    } */
    return str;
}

bool MyDate::equals_to(const MyDate& date) const
{
    return (date.year == year && date.month == month && date.day == day);
}

MyDate MyDate::tomorrow() const
{
    auto t_day   = day + 1;
    auto t_month = month;
    auto t_year  = year;
    if (t_day > days(year, month)) {
        t_day = 1; t_month++;
        if (t_month > 12) {
            t_month = 1;
            t_year++;
        }
    }
    return MyDate(t_year, t_month, t_day);
}

MyDate MyDate::yesterday() const
{
    auto t_day   = day - 1;
    auto t_month = month;
    auto t_year  = year;
    if (t_day < 1) {
        t_month--;
        if (t_month < 1) {
            t_year--;
            t_month = 12;
        }
        t_day = days(t_year, t_month);
    }
    return MyDate(t_year, t_month, t_day);
}

bool operator<(const MyDate& a, const MyDate& b) {
    return (1000 * a.year + 100 * a.month + a.day) < (1000 * b.year + 100 * b.month + b.day);
}

bool operator>(const MyDate& a, const MyDate& b) {
    return (1000 * a.year + 100 * a.month + a.day) > (1000 * b.year + 100 * b.month + b.day);
}

bool operator==(const MyDate& a, const MyDate& b) {
    return (a.year == b.year) && (a.month == b.month) && (a.day == b.day);
}

bool operator!=(const MyDate& a, const MyDate& b) {
    return (a.year != b.year) || (a.month != b.month) || (a.day != b.day);
}

void MyDate::forward(int k)
{
    day += k;
    while (day > days(year, month)) {
        day -= days(year, month);
        month++;
        if (month > 12) {
            year++;
            month = 1;
        }
    }
}
void MyDate::rollback(int k)
{
    while (k >= day) {
        k -= day;
        month--;
        if (month < 1) {
            year--;
            month = 12;
        }
        day = days(year, month);
    }
    day -= k;
}

void MyDate::rolling(int k)
{
    if (k>0) forward(k); 
    else rollback(-k);
}

int MyDate::gap_2(const MyDate& bgn, const MyDate& dst) //not recommend
{
    int cnt = 0;
    MyDate now(bgn), tgt(dst);
    if (now > dst)  
        while (tgt.equals_to(now)==0) {
            tgt = tgt.tomorrow();
            cnt++;
        }
    else 
        while (now.equals_to(tgt)==0) {
            now = now.tomorrow();
            cnt++;
        }
    return cnt;
}

int MyDate::gap_1(const MyDate& now, const MyDate& dst) 
{
    int cy = now.year, cm = now.month, cd = now.day;
    int ey = dst.year, em = dst.month, ed = dst.day;
    int sum = 0;
    if (now > dst)
    {
        std::swap(cy,ey); std::swap(cm,em); std::swap(cd,ed);
    }
    if (ey == cy)
    {
        if (em == cm) sum = ed - cd; //如果同月，则日期相减即得
        if (em > cm) //如果不同月
        {
            sum += (days(cy,cm) - cd); //则该月剩余天数，
            sum += ed; //加上目标月已过天数，
            for (int i = cm + 1; i < em; i++) sum += days(cy,i);
            //再加上中间的间隔，即得sum！
        }
        // 另外的写法
        /*int sum1=0, sum2=0;
        for (int i=1; i<cm; i++) sum1 += days(cy,i);
        sum1 += cd;
        for (int i=1; i<em; i++) sum2 += days(cy,i);
        sum2 += ed;
        sum = sum2 - sum1;*/
    }
    if (ey > cy)
    {
        //不同年可以分成五个阶段
        //1. 累加当前月的剩余天数
        sum += (days(cy,cm) - cd); 
        //2. 累加当前年内，当前日期到年底之间所有整月的天数
        for (int i = cm + 1; i <= 12; i++) sum += days(cy,i);
        //3. 累加之间年份的整天数
        for (int i = cy + 1; i < ey; i++) 
        {
            if (is_leap(i)==1) sum += 366;
            else sum += 365;
        }
        //4. 累加目标年到目标日期之间的所有整月的天数
        for (int i = 1;i < em; i++) sum += days(ey, i);
        //5. 累加目标月的天数
        sum += ed;
    }
    return sum;
}

int MyDate::gap(const MyDate& a, const MyDate& b)
{
    int sum = 0, sum1 = 0, sum2 = 0;

    for (int i = 1; i < a.month; i++) 
        sum1 += MyDate::days(a.year,i);
    sum1 += a.day;

    for (int i = 1; i < b.month; i++) 
        sum2 += MyDate::days(b.year,i);
    sum2 += b.day;
    
    if (a.year == b.year) sum = abs(sum2-sum1);
    else
    {
        int y1 = a.year, y2 = b.year;
        if (y1 > y2) 
        {
            std::swap(y1,y2); 
            std::swap(sum1,sum2);
        }
        sum += (365 + (is_leap(y1) ? 1 : 0) - sum1);
        sum += sum2;

        for (int i = y1 + 1; i < y2; i++)
        {
            if (is_leap(i)) sum += 366;
            else sum += 365;
        }
    }
    return sum;
}

MyDate::Day MyDate::what_day() const
{
    MyDate date(2020,3,15); //Sunday;
    auto dif = gap(*this, date) % 7;
    if (*this < date) dif = (7 - dif) % 7; // current date is earlier than the standard
    switch (dif)
    {
        case 1: return Day::Monday;
        case 2: return Day::Tuesday;
        case 3: return Day::Wednesday;
        case 4: return Day::Thursday;
        case 5: return Day::Friday;
        case 6: return Day::Saturday;
        case 0: default: return Day::Sunday;
    }
}

std::map<MyDate::Day, std::string> MyDate::chs_str = {
    { Day::Monday,      "一" },
    { Day::Tuesday,     "二" },
    { Day::Wednesday,   "三" },
    { Day::Thursday,    "四" },
    { Day::Friday,      "五" },
    { Day::Saturday,    "六" },
    { Day::Sunday,      "日" }
};

std::map<MyDate::Day, std::string> MyDate::eng_str = {
    { Day::Monday,      "Monday"     },
    { Day::Tuesday,     "Tuesday",   },
    { Day::Wednesday,   "Wednesday"  },
    { Day::Thursday,    "Thursday"   },
    { Day::Friday,      "Friday"     },
    { Day::Saturday,    "Saturday"   },
    { Day::Sunday,      "Sunday"     }
};

std::string MyDate::day_string() const
{
    std::string str;
    if (print_format == DayFormat::Chinese || print_format == DayFormat::Normal)
    {
        str += "星期";
        str += chs_str[this->what_day()];
    }
    else if(print_format == DayFormat::English || print_format == DayFormat::American)
    {
        str += eng_str[this->what_day()];
    }
    return str;
}
