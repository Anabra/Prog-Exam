#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "studentpay.h"

using namespace std;

StudentPay StudentPay::operator+(const StudentPay& other) const
{
    if(this->name != other.getName())
    {
        throw StudentPayException("StudentPayException::operator=() : this->name != other.name");
    }
    return StudentPay(this->name, other.date, this->inpayment + other.inpayment, this->count + other.count);
}

StudentPay& StudentPay::operator+=(const StudentPay& other)
{
    if(this->name != other.getName())
    {
        throw StudentPayException("StudentPayException::operator=() : this->name != other.name");
    }
    this->inpayment += other.getInpayment();
    this->date = other.getDate();
    this->count += other.count;
    return *this;
}

bool operator<(const StudentPay& lhs, const StudentPay& rhs)
{
    /*
    if (lhs.getName() < rhs.getName()) return true;
    else if (!(lhs.getName() > rhs.getName()) && lhs.getDate() < rhs.getDate()) return true;
    else return false;
    */
    if (lhs.getName() < rhs.getName()) return true;
    else return false;
}

bool operator==(const StudentPay& lhs, const StudentPay& rhs)
{
    /* return !(lhs < rhs) && !(rhs < lhs); */
    return !(lhs.getName() < rhs.getName()) && !(rhs.getName() < lhs.getName());
}

template <class T>
std::istream& operator>>(std::istream& in, std::deque<T>& d)
{
    T tmp;
    while (in >> tmp)
    {
        d.push_back(tmp);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StudentPay& item)
{
    stringstream line;
    std::string tmpString;

    // handling empty line
    if(!getline(in, tmpString))
    {
        return in;
    }
    line << tmpString;

    std::deque<std::string> data;
    line >> data;

    item.inpayment = std::atoi(data.back().c_str());
    data.pop_back();
    item.date = data.back();
    data.pop_back();
    item.name = data.front();
    data.pop_front();
    for (std::deque<string>::const_iterator cit = data.begin(); cit != data.end(); ++cit)
    {
        item.name = item.name + " " + *cit;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const StudentPay& item)
{
    out << item.name << " " << item.date << " " << item.inpayment << " " << item.count;
    return out;
}
