#pragma once
#include <vector>
#include <iostream>

namespace task
{

using std::istream;
using std::ostream;
using std::vector;

ostream &operator<<(ostream &ostr, const vector<double> &a)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        ostr << a[i] << " ";
    }
    ostr << std::endl;
    return ostr;
}

istream &operator>>(istream &input, vector<double> &a)
{
    size_t n;
    input >> n;
    if (n == 0)
    {
        a.clear();
        return input;
    }
    double d;
    a.resize(n);
    for (size_t i = 0; i < a.size(); ++i)
    {
        input >> d;
        a[i] = d;
    }
    return input;
}

vector<double> operator+(const vector<double> &a, const vector<double> &b)
{
    vector<double> c(a.size());
    for (size_t i = 0; i < c.size(); ++i)
        c[i] = a[i] + b[i];
    return c;
}

vector<double> operator+(const vector<double> &a)
{
    vector<double> c(a.size());
    for (size_t i = 0; i < c.size(); ++i)
        c[i] = +a[i];
    return c;
}

vector<double> operator-(const vector<double> &a, const vector<double> &b)
{
    vector<double> c(a.size());
    for (size_t i = 0; i < c.size(); ++i)
        c[i] = a[i] - b[i];
    return c;
}

vector<double> operator-(const vector<double> &a)
{
    vector<double> c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
        c[i] = -a[i];
    return c;
}

double operator*(const vector<double> &a, const vector<double> &b)
{
    double c = 0;
    for (size_t i = 0; i < a.size(); ++i)
        c += a[i] * b[i];

    return c;
}

vector<double> operator%(const vector<double> &a, const vector<double> &b)
{
    vector<double> c(3);
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
    return c;
}

bool operator||(const vector<double> &a, const vector<double> &b)
{
    double mul = 0;
    size_t first_not_zero_ind = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        if ((b[i] == 0) and (a[i] != 0))
            return false;
        else if ((b[i] == 0) and (a[i] == 0))
        {
            first_not_zero_ind += 1;
            continue;
        }
        else
        {
            mul = a[i] / b[i];
            break;
        }
        first_not_zero_ind = i;
    }
    if (first_not_zero_ind == a.size())
        return true;

    for (size_t i = first_not_zero_ind; i < a.size(); ++i)
    {
        if (b[i] != 0)
        {
            if (a[i] - mul * b[i] > 1e-10)
                return false;
        }
        else if (a[i] != 0)
            return false;
    }
    return true;
}

bool operator&&(const vector<double> &a, const vector<double> &b)
{
    if (!(a || b))
        return false;
    else
    {
        for (size_t i = 0; i < a.size(); ++i)
        {
            if (b[i] != 0)
            {
                if (a[i] / b[i] > 0)
                    return true;
                else
                    return false;
            }
        }
        return false;
    }
}

vector<double> reverse(vector<double> &a)
{
    double tmp;
    for (size_t i = 0; i < a.size() / 2; ++i)
    {
        std::swap(a[i], a[a.size() - 1 - i]);
    }
    return a;
}

vector<int> operator|(const vector<int> &a, const vector<int> &b)
{
    vector<int> c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = a[i] | b[i];
    }
    return c;
}

vector<int> operator&(const vector<int> &a, const vector<int> &b)
{
    vector<int> c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = a[i] & b[i];
    }
    return c;
}

} // namespace task
