#include <iostream>
#include <cmath>
#include <iomanip>
#include "mydate.h"

void print_gap(MyDate& A, MyDate& B)
{
    A.print();
    cout<<" 和 ";
    B.print();
    cout<<" 相距 ";
    cout<<A.get_gap(B);
    cout<<" 天 \n";
}

bool set_date(MyDate& d)
{
    cout<<left;
    cout<<"Previous: ";
    d.print();
    cout<<endl;
    cout<<"New: \n";
    int ty,tm,td;
    cout<<setw(7)<<"Year:"; cin>>ty;
    cout<<setw(7)<<"Month:"; cin>>tm;
    cout<<setw(7)<<"Day:"; cin>>td;
    try {
        d.set(ty,tm,td);
    }
    catch(MyDate td)
    {
        cout<<"Illegal! Date set failed. Did you mean ";
        td.print();
        cout<<"?"<<endl;
        cout<<"Try again!"<<endl;
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
    a.print();
    cout << endl;
    return 0;
}
