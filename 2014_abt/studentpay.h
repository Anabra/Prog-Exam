#ifndef STUDENTPAY_H_INCLUDED
#define STUDENTPAY_H_INCLUDED

#include <exception>
#include "enor.h"

class StudentPayException : public std::exception
{
    const std::string errMessage;
public:
    explicit StudentPayException(const std::string& errMessage) : errMessage(errMessage) {}
    const char* what() const noexcept override { return errMessage.c_str(); }
};

class StudentPay
{
private:
    std::string name;
    std::string date;
    int inpayment;
    unsigned int count;

public:
    StudentPay() : count(1) {}
    StudentPay(const std::string& name, const std::string& date, int inpayment, unsigned int count = 1) :
        name(name), date(date), inpayment(inpayment), count(count) {}

    std::string getName() const  { return name; }
    std::string getDate() const  { return date; }
    int getInpayment()    const  { return inpayment; }
    unsigned int getCount()  const  { return count; }

    void setDate(const std::string date) { this->date = date; }
    void setInpayment(int inpayment) { this->inpayment = inpayment; }

    // works only for instances that for which (this->name == other.name) holds true
    StudentPay  operator+(const StudentPay&) const;
    StudentPay& operator+=(const StudentPay&);

    friend std::istream& operator>>(std::istream&, StudentPay&);
    friend std::ostream& operator<<(std::ostream&, const StudentPay&);
    friend StreamEnor<StudentPay>;
    friend DoubleStreamEnor<StudentPay>;
};

bool operator< (const StudentPay&, const StudentPay&);
bool operator==(const StudentPay&, const StudentPay&);

#endif // STUDENTPAY_H_INCLUDED
