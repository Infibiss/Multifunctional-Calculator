#pragma once

#include <bits/stdc++.h>
#include <sstream>

using namespace std;

void Split(vector <string> &result, string &s, char delim) 
{
    result.clear();
    stringstream ss(s);
    string word;

    while (getline (ss, word, delim)) 
        result.push_back (word);
}

int MakeNum(char c)
{
	if(c >= '0' && c <= '9') return c - '0';
	else if(c >= 'A' && c <= 'Z') return c - 'A' + 10;
	else if(c >= 'a' && c <= 'z') return c - 'a' + 10;
	else return -1;
}

char MakeChar(long long c)
{
    if(c <= 9) return c + '0';
    else return c - 10 + 'a';
}

void dtoa(double &result, string &str, double radix)
{
    while(result)
    {
        double r = fmod(result, radix);
        str += MakeChar((long long)(r));
        result = (result - r) / radix;
    }
}

string Num2Num(double radix1, int radix2, string first)
{
	double result = 0;
    for(long long i = first.size() - 1, cnt = 0; i >= 0; i--)
    {
    	long long num = MakeNum(first[i]);
    	if(num == -1 || num >= radix1) return ("WRONG NUMBER");
        result += num * pow(radix1, cnt++);
    }
    
    string str = "";
    dtoa(result, str, radix2);
    return str;
}