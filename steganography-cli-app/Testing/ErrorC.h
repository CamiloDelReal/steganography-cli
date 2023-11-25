#pragma once
#include <xstring>
using namespace std;

class ErrorC : public exception
{
public:
	ErrorC(string _msg) : exception(_msg.c_str()) {};
};

