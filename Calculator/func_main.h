#pragma once

#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int IfOper(char c) 
{ 
	if (c == '+' || c == '-' || c == '/' || c == '\\' || c == '$' || c == '*' || c == '%' || c == '^' || c == '!' || c == '#' || c == '@' || c == ':' || c == ';' || c == '|' || c == '&' || c == '~') return 1; 
	else if (c == '(') return 2; 
	else if (c == ')') return 3; 
	else if(c >= '0' && c <= '9') return 4;
	else return -1;
}

bool IfRealOper(string &s, int &i)
{
	bool flagr = false, flagl = false;
	int j;

	for(j = i + 1; j < s.size() && s[j] == ' ';) j++;
	if(j == s.size()) {i = -1; return 1;}
	if(IfOper(s[j]) == 4)
		flagr = true;
	
	for(j = i - 1; j >= 0 && s[j] == ' ';) j--;
	if(j == -1 || IfOper(s[j]) == 1 || IfOper(s[j]) == 2)
		flagl = true;
		
	if(flagr && flagl) return false;
	else return true;

}

int Priority(char c)
{
	switch(c)
	{
		case '|': return 1; break;
		case '~': return 2; break;
		case '&': return 3; break;
		case '+': return 4; break;
		case '-': return 4; break;
		case '*': return 5; break;
		case '/': return 5; break;
		case '\\': return 5; break;
		case '%': return 5; break;
		case '$': return 6; break;
		case '^': return 6; break;
		case '!': return 6; break;
		case '#': return 6; break;
		case '@': return 6; break;
		case ':': return 6; break;
		case ';': return 6; break;
		case '(': return 7; break;
		case ')': return 7; break;
		default:  return 0; break;
	}
}

bool CheckBrackets(string &s)
{
	int x = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == '(') x++;
		else if(s[i] == ')') x--;
	}

	return (x == 0);
}

void CheckMulti(string &s)
{
	for(int i = 0, j, z; i < s.size(); i++)
	{
		if(s[i] == '(' || s[i] == '#' || s[i] == '@' || s[i] == ':' || s[i] == ';' || s[i] == '$')
		{	
			for(j = i - 1; j >= 0 && s[j] == ' ';) j--;

			if(j != -1 && IfOper(s[j]) == 4 || IfOper(s[j]) == 3 || s[j] == '!')
			{
				s.insert(i, "*");
				i++;
			}
		}
	}
	return;
}

void CheckWords(string &s)
{
	for(int i = 0; i + 2 < s.size(); i++)
	{
		if(s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n')
		{
			s.erase(i, 3);
			s.insert(i, ":"); // sin
		}
		else if(s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's')
		{
			s.erase(i, 3);
			s.insert(i, ";"); // cos
		}
		else if(s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 's')
		{
			s.erase(i, 3);
			s.insert(i, "$"); // abs
		}
		else if(i + 3 < s.size() && s[i] == 's' && s[i + 1] == 'q' && s[i + 2] == 'r' && s[i + 3] == 't')
		{
			s.erase(i, 4);
			s.insert(i, "#"); // sqrt
		}
		else if(i + 3 < s.size() && s[i] == 'c' && s[i + 1] == 'b' && s[i + 2] == 'r' && s[i + 3] == 't')
		{
			s.erase(i, 4);
			s.insert(i, "@"); // cbrt
		}
	}
}

double fact(double n)
{
    if(n == 1 || n == 0) return 1;
    else return fact(n - 1) * n;
}
