#ifndef ENOR_H_INCLUDED
#define ENOR_H_INCLUDED

#include <iostream>
#include <exception>
#include <cstdlib>

class StudentPay;
template <class T> class DoubleStreamEnor;

class StreamEnorException : public std::exception
{
    const std::string errMsg;
public:
    explicit StreamEnorException(const std::string& errMsg) : errMsg(errMsg) {}
    const char* what() const noexcept override { return errMsg.c_str(); }
};

class DoubleStreamEnorException : public std::exception
{
    const std::string errMsg;
public:
    explicit DoubleStreamEnorException(const std::string& errMsg) : errMsg(errMsg) {}
    const char* what() const noexcept override { return errMsg.c_str(); }
};

template <class T>
class Enor
{
public:
    virtual void first() = 0;
    virtual T current() = 0;
    virtual void next()  = 0;
    virtual bool end()   = 0;
};

template <class T>
class StreamEnor : public Enor<T>
{
protected:
    std::istream& stream;
    T cur;
    T preRead;
    bool isEndOfStream;
public:
    StreamEnor (std::istream& stream) : stream(stream), isEndOfStream(false)
        { if(stream.fail()) throw StreamEnorException("StreamEnor: invalid stream"); }

    void first() { isEndOfStream = !(stream >> preRead); next(); }
    // for complex types, we rely on RVO
    T current() { return cur; }
    void next();
    bool end()  { return isEndOfStream; }

    friend DoubleStreamEnor<T>;
};

template <class T>
class DoubleStreamEnor : public Enor<T>
{
private:
    StreamEnor<T> enor_1;
    StreamEnor<T> enor_2;
    T cur;
    bool isEndOfStream;
public:
    DoubleStreamEnor (std::istream& stream_1, std::istream& stream_2)
        try : enor_1(stream_1), enor_2(stream_2), isEndOfStream(false)
        {}
        catch (StreamEnorException e)
        {
            std::cerr << e.what() << std::endl;
            throw DoubleStreamEnorException("DoubleStreamEnor: couldn't construct underlying StreamEnor<T>");
        }

    void first();
    // for complex types, we rely on RVO
    T current();
    void next();
    bool end()  { return enor_1.isEndOfStream && enor_2.isEndOfStream; }
};

#endif // ENOR_H_INCLUDED
