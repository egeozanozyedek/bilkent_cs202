/*
* Title: Trees
* Author: Ege Ozan Özyedek
* ID: 21703374
* Assignment: 2
* Description: An  exception class for BST's. Taken from the slides.
*/

#ifndef TreeException_h
#define TreeException_h

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class TreeException : public std::exception{

private:
    string msg;

public:
    virtual const char* what() const throw()
    {
        return msg.c_str();
    }
   TreeException(const string & message =""):
    exception(), msg(message) {};
    ~TreeException() throw() {};

};

#endif /* TreeException_h */
