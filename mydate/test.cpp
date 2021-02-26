#include <iostream>
#include <cmath>
#include <iomanip>
#include "mydate.h"

using std::cin;
using std::cout;
using std::endl;

void print_gap(const MyDate& A, const MyDate& B)
{
    cout << A.to_string() + " 和 " + B.to_string() + " 相距 " << MyDate::gap(A, B) << " 天 \n";
}

bool set_date(MyDate& d)
{
    cout << "Previous: " << d.to_string() << endl;
    cout << "New: \n";
    int ty, tm, td;
    cout << "Year:  "; cin >> ty;
    cout << "Month: "; cin >> tm;
    cout << "Day:   "; cin >> td;
    try {
        d.set(ty,tm,td);
    }
    catch(MyDate td)
    {
        cout << "Illegal! Date set failed. Did you mean " << td.to_string() << "?" << endl;
        cout << "Try again!"<<endl;
        return set_date(d);
    }
    catch(...)
    {
        cout<<"Unknow error occurred! Date set failed."<<endl;
        cout<<"Try again!"<<endl;
        return set_date(d);
    }
    return true;
}

int main()
{
    MyDate::set_style(MyDate::Normal);
    MyDate::set_style(MyDate::day_print_on);
    MyDate a;
    set_date(a);
    cout << a.to_string() << endl;
    return 0;
}
