#include "myint.h"

h_int::h_int()
{
    ptr = new int[1];
    ptr[0] = 0;
    len = 1;
    //if_negative = false;
}
h_int::h_int(int a)
{
    ptr = new int[32];
    int i = 0;
    while (a > 0)
    {
        ptr[i++] = a % 10;
        a /= 10;
    }
    len = i;
}
h_int::h_int(const char *str)
{
    int str_length = strlen(str);
    if (str_length == 0) { h_int(); return; }
    int i = 0;
    while (i < str_length && !(str[i] >= '0' && str[i] <= '9')) ++i;
    int j = i;
    while (str[j] >= '0' && str[j] <= '9') ++j;
    --j;
    len = j - i + 1;
    ptr = new int [len];
    int k = 0;
    while (j >= i) ptr[k++] = str[j--] - '0';
}

h_int::h_int(const std::string & str)
{
    auto begin_pos = str.find_first_of("0123456789");
    if (str.length() == 0 || begin_pos == std::string::npos) { *this = 0; return; }
    auto end_pos = str.find_first_not_of("0123456789", begin_pos);
    auto s = str.substr(begin_pos, end_pos);
    len = s.length();
    ptr = new int[len];
    ptr[0] = 0;
    auto i = s.rbegin();
    for (int k = 0; i != s.rend(); ++i, ++k) ptr[k] = *i - '0';
    while (ptr[len - 1] == 0 && len > 1) --len;
}

h_int::~h_int()
{
    if (ptr)
        delete[] ptr;
}
h_int::h_int(const h_int& a)
{
    len = a.len;
    ptr = new int [len];
    memcpy(ptr,a.ptr,sizeof(int)*len);
}
h_int& h_int::operator=(const h_int& a)
{
    len = a.len;
    if (ptr) delete[] ptr;
    ptr = new int [len];
    memcpy(ptr,a.ptr,sizeof(int)*len);
    return *this;
}
h_int& h_int::operator=(int a)
{
    ptr = new int[32];
    int i = 0;
    while (a > 0)
    {
        ptr[i++] = a % 10;
        a /= 10;
    }
    len = i;
    return *this;
}
void h_int::output() const
{
    //if (if_negative) cout<<'-';
    for (int i = len - 1; i >= 0; i--) std::cout << ptr[i];
}

h_int& h_int::multiply(const h_int& a)
{
    //bool result_negative = false;
    //if(if_negative && a.if_negative) result_negative = true;
    //else if (!if_negative && !a.if_negative) result_negative = true;
    //else result_negative = false;

    int result_len = len + a.len;
    int * result_ptr = new int [result_len];
    memset(result_ptr,0,sizeof(int)*result_len); 
    int tmp = 0, cnt = 0;
    for (int i = 0; i< a.len;i++)
    {
        for (int j  = 0;j<len;j++)
        {
            tmp = a.ptr[i] * ptr[j];
            cnt = 0;
            while(tmp > 0)
            {
                tmp += result_ptr[i+j+cnt];
                result_ptr[i+j+cnt] = tmp%10;
                tmp/=10;
                if(tmp == 0) break;
                cnt++;
            }
        }
    }
    result_len = len + a.len + cnt - 1;
    
    delete[] ptr;
    ptr = result_ptr;
    len = result_len;
    //if_negative = result_negative;
    
    return *this;
}
h_int& h_int::operator*=(const h_int& a)
{
    return multiply(a);
}

h_int& h_int::add(const h_int& a)
{
    int result_len = std::max(len, a.len) + 1; //ensure enough space for adding
    int * result_ptr = new int [result_len];
    memset(result_ptr,0,sizeof(int)*result_len); 
    memcpy(result_ptr, ptr, sizeof(int)*len);
    int k = 0;
    for (int i = 0; i < a.len; i++)
    {
        result_ptr[i] += a.ptr[i];
        k = i;
        while (result_ptr[k] > 9)
        {
            result_ptr[k+1] += result_ptr[k] / 10;
            result_ptr[k] %= 10;
            k++;
        }
    }
    result_len = std::max(k+1,len);

    delete[] ptr;
    ptr = result_ptr;
    len = result_len;
    
    return *this;
}
h_int& h_int::operator+=(const h_int& a)
{
    return add(a);
}

std::ostream& operator<<(std::ostream& o, const h_int& a)
{
    a.output();
    return o;
}

std::istream& operator>>(std::istream& i, h_int & a) 
{
    std::string str;
    i >> str;
    a = h_int(str);
    return i;
}
