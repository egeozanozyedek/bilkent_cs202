/*
* Title: Heaps
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 3
* Description: Simple exception class which enables the program to throw string exceptions for invalid arguments
*/

#ifndef HeapException_h
#define HeapException_h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class HeapException : public std::exception{

private:
    string msg;

public:
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
   HeapException(const string & message =""):
    exception(), msg(message) {};
    ~HeapException() throw() {};

};

#endif
