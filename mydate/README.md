# mydate-cpp

A C++ class that can stores and output a date with different styles, with checking and suggesting function. 

# description

Use `MyDate` class to store a date, and insert it to the outstream with different styles;

And you can also calculate the days between two date; rolling forward or back is also supported;

Several methods are provided;

`MyDate::print()`: Now support Chinese and English. Output what day it is now an optional setting, and applys to every output. A parameter to decide this when calling this function is under considering. 

`MyDate::set()`: Now, when `set()` function will **throw** a `MyDate` class out when it is processing illegal year-month-day combnation. 
The class it is throwing contains a legal date suggestion that is given out by function `MyDate::get_suggestion()`;

```cpp
MyDate my_date;
int y,m,d;
std::cin >> y >> m >> d;
try {
    my_date.set(y,m,d);
}
catch (MyDate advice)
{
    std::cout<<"Set failed! Illegal combination! ";
    std::cout<<"Did you mean: ";
    advice.print();
    std::cout<<"?"<<endl;
}
```

Well, maybe I should throw something else like the data which is illegal? I have no idea...
