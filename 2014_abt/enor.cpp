#include <iostream>
#include "enor.h"
#include "studentpay.h"

using namespace std;

template<>
void StreamEnor<StudentPay>::next()
{
    if (isEndOfStream = stream.fail()) return;
    cur = preRead;
    while((stream >> preRead) && preRead.getName() == cur.getName())
    {
        cur += preRead;
    }
}

template<>
void DoubleStreamEnor<StudentPay>::first()
{
    enor_1.first();
    enor_2.first();
}

template<>
StudentPay DoubleStreamEnor<StudentPay>::current()
{
    StudentPay cur1  = enor_1.current();
    StudentPay cur2  = enor_2.current();
    bool isFirstEnd  = enor_1.end();
    bool isSecondEnd = enor_2.end();

    if      (isSecondEnd || (!isFirstEnd  && cur1 < cur2)) { return cur1; }
    else if (isFirstEnd  || (!isSecondEnd && cur2 < cur1)) { return cur2; }
    else if (!isFirstEnd && !isSecondEnd  && cur1 == cur2) { return cur1 + cur2; }
}

template<>
void DoubleStreamEnor<StudentPay>::next()
{
    StudentPay cur1  = enor_1.current();
    StudentPay cur2  = enor_2.current();
    bool isFirstEnd  = enor_1.end();
    bool isSecondEnd = enor_2.end();

    if      (isSecondEnd || (!isFirstEnd  && cur1 < cur2)) { enor_1.next(); }
    else if (isFirstEnd  || (!isSecondEnd && cur2 < cur1)) { enor_2.next(); }
    else if (isFirstEnd  || (!isSecondEnd && cur2 < cur1)) { enor_2.next(); }
    else if (!isFirstEnd && !isSecondEnd  && cur1 == cur2) { enor_1.next(); enor_2.next(); }
}


