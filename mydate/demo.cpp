#include <iostream>
#include <cmath>
#include "MyDate.h"

using std::cin;
using std::cout;
using std::endl;

void print_gap(const MyDate& A, const MyDate& B)
{
    cout << A.to_string() + " 和 " + B.to_string() + " 相距 " << MyDate::gap(A, B) << " 天 \n";
}

bool set_date_from_console_input(MyDate& d)
{
    cout << "Previous date is : " << d.to_string() << endl;
    int ty, tm, td;   
    bool finish = false;
    while(!finish) {
        cout << "Enter a new date: \n";
        cout << "Year:  "; cin >> ty;
        cout << "Month: "; cin >> tm;
        cout << "Day:   "; cin >> td;
        try {
            d.set(ty,tm,td);
            finish = true;
        }
        catch (MyDate td)
        {
            cout << "Illegal! Date set failed. Did you mean " << td.to_string() << "?" << endl;
            cout << "Try again!"<<endl;
        }
        catch (...)
        {
            cout << "Unknow error occurred! Date set failed." << endl;
            cout << "Try again!" << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    MyDate some_day;

    set_date_from_console_input(some_day);

    MyDate::set_format(MyDate::DayFormat::DAY_PRINT_ON);

    MyDate::set_format(MyDate::DayFormat::Normal);
    cout << "Print the day in Normal  format: " << some_day.to_string() << endl;
    MyDate::set_format(MyDate::DayFormat::Chinese);
    cout << "Print the day in Chinese format: " << some_day.to_string() << endl;
    cout << "Print the day in Chinese format: " << some_day.yesterday().to_string() << endl;

    std::cout << "The day you choose is the " 
        << MyDate::gap(some_day, MyDate(some_day.get_year(), 1, 1)) + 1 
        << " day of that year. ";

    return 0;
}
