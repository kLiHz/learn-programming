#ifndef _H_INT_H_
#define _H_INT_H_

#include <iostream>
#include <cstring>

class h_int
{
private:
    int *ptr;
    int len;
    //bool if_negative;
public:
    h_int();
    h_int(int);
    h_int(const h_int&);
    h_int(const char *);
    h_int(const std::string & str);
    ~h_int();
    h_int& operator=(const h_int&);
    h_int& operator=(int);
    h_int& multiply(const h_int&);
    h_int& operator*=(const h_int&);
    h_int& add(const h_int&);
    h_int& operator+=(const h_int&);
    void output() const;
    friend std::ostream& operator<<(std::ostream& o, const h_int& a);
    friend std::istream& operator>>(std::istream& i, h_int & a);
};

#endif
