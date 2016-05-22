#include <iostream>
#include <fstream>
#include <cstdlib>
#include "enor.h"
#include "studentpay.h"

using namespace std;

template<class T>
struct QueryResult
{
    T data;
    bool found;

    QueryResult() : found(false) {}
    QueryResult(const T& data) : data(data), found(true) {}
};

struct PaidAll
{
    bool operator() (const StudentPay& item)
    {
        return item.getInpayment() >= 11000;
    }
};

struct CountMore
{
    bool operator() (const StudentPay& lhs, const StudentPay& rhs)
    {
        return lhs.getCount() > rhs.getCount();
    }
};

template <class ElemT, class Pred, class Comp = std::less<ElemT> >
QueryResult<ElemT> condMaxSearch (Enor<ElemT> &e)
{
    Pred pred;
    Comp comp;
    bool l = false;
    ElemT maxElem;

    for(e.first(); !e.end(); e.next())
    {
        if(pred(e.current()) && !l)
        {
            maxElem = e.current();
            l = true;
        }
        else if(pred(e.current()) && l)
        {
            if (comp(maxElem, e.current()))
            {
                maxElem = e.current();
            }
        }
    }

    return l ? QueryResult<ElemT>(maxElem) : QueryResult<ElemT>();
}

struct GetInpayment
{
    int operator() (const StudentPay& item)
    {
        return item.getInpayment();
    }
};

template <class T, class ElemT, class Function>
T summarize (Enor<ElemT> &e, T neutral = 0)
{
    Function f;
    T sum = neutral;

    for (e.first(); !e.end(); e.next())
    {
        sum += f(e.current());
    }
    return sum;
}

int main()
{
    ifstream in1("in1.txt");
    ifstream in2("in2.txt");
    ofstream out("out.txt");

    try
    {
        DoubleStreamEnor<StudentPay> e (in1, in2);


        // parallel algorithm
        int sum = 0;
        GetInpayment f;

        PaidAll pred;
        CountMore comp;
        bool l = false;
        StudentPay maxElem;

        for(e.first(); !e.end(); e.next())
        {
            cout << e.current() << endl;
            sum += f(e.current());

            if(pred(e.current()) && !l)
            {
                maxElem = e.current();
                l = true;
            }
            else if(pred(e.current()) && l)
            {
                if (comp(maxElem, e.current()))
                {
                    maxElem = e.current();
                }
            }
        }

        string result;
        result = l ? maxElem.getName() : "no element found with the given criteria";
        cout << "The sum is: " << sum << endl << "Result of conditional maximum search: " << result << endl;
    }
    catch (DoubleStreamEnorException e)
    {
        cout << e.what() << endl;
        exit(1);
    }


    /* 3-as
    try
    {
        StreamEnor<StudentPay> e(in1);


        // parallel algorithm
        int sum = 0;
        GetInpayment f;

        PaidAll pred;
        CountMore comp;
        bool l = false;
        StudentPay maxElem;

        for(e.first(); !e.end(); e.next())
        {
            cout << e.current() << endl;
            sum += f(e.current());

            if(pred(e.current()) && !l)
            {
                maxElem = e.current();
                l = true;
            }
            else if(pred(e.current()) && l)
            {
                if (comp(maxElem, e.current()))
                {
                    maxElem = e.current();
                }
            }
        }

        string result;
        result = l ? maxElem.getName() : "no element found with the given criteria";
        cout << "The sum is: " << sum << endl << "Result of conditional maximum search: " << result << endl;
    }
    catch (StreamEnorException e)
    {
        cout << e.what() << endl;
        exit(1);
    }
    */


    return 0;
}
