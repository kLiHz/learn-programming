# MyDate

A C++ class that can stores and output a date with different styles, with checking and suggesting function. 

## Description

Use `MyDate` class to store a date, and obtain a `std::string` of it in various forms;

You can find out how many days are there between two certain dates; rolling forward or backward is also supported;

Several methods are provided;

`MyDate::to_string()`: Return a string of the date. Now support Chinese and English. Whether to print what day it is today is optional, and currently such settings apply to each call. 

`MyDate::set()`: Now, when `set()` function will **throw** out a `MyDate` class when it is processing illegal "year-month-day" combination. This object representing a legal date suggestion, which is suggested by the function `MyDate::get_suggestion()`;

```cpp
MyDate my_date;
int y,m,d;
std::cin >> y >> m >> d;
try {
    my_date.set(y,m,d);
}
catch (MyDate advice)
{
    std::cout << "Set failed! Illegal combination! ";
    std::cout << "Did you mean: " << advice.to_string() << "?" << std::endl;
}
```

Well, maybe I should throw something else like the data which is illegal? I have no idea...
