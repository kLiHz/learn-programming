#ifndef _MYDATE_CPP_
#define _MYDATE_CPP_

#include "mydate.h"

void MyDate::set_style(int t) 
{
    if(t == day_print_on) if_print_day = true;
    else if (t == day_print_off) if_print_day = false;
    else if (t == day_print) if_print_day = !if_print_day;
    else style = t;
}

MyDate::MyDate()
{
    year  = 1970;
    month = 1;
    day   = 1;
}

MyDate::MyDate(int y_, int m_, int d_)
{
    if (is_legal(y_,m_,d_)) 
    {
        year = y_; month = m_; day = d_;
    }
    else
    {
        cout<<"class: MyDate: Construction Failure: ";
        cout<<"Initialization failed. \n Date is set to ";
        year = 1970; month = 1; day = 1;
        print();
        cout<<". "<<endl;
    }
}

int MyDate::days() const
{
    int days[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (month==2)
    {
        if(is_leap()) return 29;
        else return 28;
    }
    else return days[month];
}

int MyDate::days(int y, int m)
{
    int days[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m==2)
    {
        if(is_leap(y)) return 29;
        else return 28;
    }
    else return days[m];
}

bool MyDate::is_legal(int ty, int tm, int td)
{
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
    if (d > advice.days() && d < 32) d = advice.days();
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
    if( (year % 4 ==0 && year % 100 != 0) || year % 400 == 0 ) return 1;
    else return 0;
}

int MyDate::is_leap(int year)
{ 
    if( (year % 4 ==0 && year % 100 != 0) || year % 400 == 0 ) return 1;
    else return 0;
}

void MyDate::print() const
{
    static char months_eng[13][15] = {"0","January","February","March","April",
        "May","June","July","August","September","October","November","December"};
    if (style == Chinese) {
        cout<<year<<"年"<<month<<"月"<<day<<"日";
        if (if_print_day) {cout<<"  "; print_day();}
    }
    else if (style == Normal) {
        cout<<year<<"/"<<month<<"/"<<day;
    }
    else if (style == American) {
        if (if_print_day) {print_day(); cout<<", ";}
        cout<<months_eng[month]<<" "<<day<<", "<<year;
    }
    else if (style == English) {
        if (if_print_day) {print_day(); cout<<", ";}
        cout<<day<<" "<<months_eng[month]<<", "<<year;
    }
    /*else
    {
        char s[4][4]={"th","st","nd","rd"};
        if (style == 4) 
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
        if (style == 5)
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
}
bool MyDate::equals(const MyDate& date) const
{
    return (date.year == year && date.month == month && date.day == day);
}
void MyDate::tomorrow()
{
    day++;
    if (day > days()) 
    {
        day = 1;
        month++;
        if(month > 12) 
        {
            month = 1;
            year++;
        }
    }
}
void MyDate::yesterday()
{
    day--;
    if (day<1) 
    {
        month--;
        if(month<1)
        {
            year--;
            month = 12;
        }
        day = days();
    }
}

int MyDate::compare(const MyDate & dst) const
{
    if (1000 * year + 100 * month + day > 1000 * dst.year + 100 * dst.month + dst.day) return 1;
    else if (equals(dst) == 1) return 0;
    else return -1;
}

void MyDate::forward(int k)
{
    int sum_days = k + day;
    day += k;
	while(day > days())
	{
		day -= days();
    	month++;
    	if(month > 12)
		{
			year++;
			month = 1;
		}
	}
}
void MyDate::rollback(int k)
{
    while(k >= day)
	{
		k = k - day;
		month--;
		if(month<1)
		{
			year--;
			month = 12;
		}
		day=days();
	}
	day -= k;
}

void MyDate::rolling(int k)
{
    if (k>0) forward(k); 
    else rollback(-k);
}

void MyDate::rolling_1(int dif) //not recommend
{
    int k = dif;
    if (k<0) while(k!=0) {yesterday(); k++;}
    else while (k!=0) {tomorrow(); k--;}
}

int MyDate::get_gap_2(const MyDate& dst) const //not recommend
{
    int gap = 0;
    MyDate now(year,month,day);
    MyDate tgt(dst);
    if (compare(dst) == 1) 
        while (tgt.equals(now)==0) {
            tgt.tomorrow();
            gap++;
        }
    else 
        while (now.equals(tgt)==0) {
            now.tomorrow();
            gap++;
        }
    return gap;
}

int MyDate::get_gap_1(const MyDate& dst) const 
{
    int cy = year, cm = month, cd = day;
    int ey = dst.year, em = dst.month, ed = dst.day;
    int sum = 0;
    if (compare(dst)==1)
    {
        swap(cy,ey); swap(cm,em); swap(cd,ed);
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

int MyDate::get_gap(const MyDate& date) const
{
    int sum = 0, sum1 = 0, sum2 = 0;

	for(int i=1; i<month; i++) sum1 += days(year,i);
	sum1 += day;
	for(int i=1; i<date.month; i++) sum2 += days(date.year,i);
	sum2 += date.day;
    
    if (year == date.year) sum = abs(sum2-sum1);
    else
	{
		int y1 = year, y2 = date.year;
		if (y1 > y2) 
        {
            swap(y1,y2); 
            swap(sum1,sum2);
        }
        sum = sum2 + (365 + is_leap(y1) - sum1);

		for (int i = y1+1; i<y2; i++)
		{
			if (is_leap(i)==1) sum+=366;
			else sum+=365;
		}
	}
	return sum;
}

int MyDate::get_day() const
{
    MyDate date(2020,3,15); //Sunday;
    int dif = get_gap(date);
    dif %= 7;
    if (dif == 0) return 7;
    //current date is later than the standard date:
    else if (compare(date)==1) return dif;
    else return 7-dif;
}

void MyDate::print_day() const
{
    static const char* chs_str[7] = {"一","二","三","四","五","六","七"};
    static const char* eng_str[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    if (style == Chinese || style == Normal)
    {
        cout<<"星期";
        cout<<chs_str[get_day()-1];
    }
    else if(style == English || style == American)
    {
        cout<<eng_str[get_day()-1];
    }
}

#endif
