#pragma once

#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
void yellow(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN);}
void white(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);}
void red(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED);}
void green(){SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN);}
void printy(string s){ yellow(); cout << s; white(); }
void printw(string s){ white(); cout << s;           }
void printg(string s){ green(); cout << s; white();  }
void printr(string s){ red(); cout << s; white();    }

void StartScreenMain()
{
	printr("Commands: ");
	printy("\"clear\" | \"close\" | \"mode\"\n\n");
}

void StartScreen1()
{
	printr("Operators: ");
	printy("+  -  *  /  \\  \%  ^  !  sqrt  cbrt  sin  cos  abs  &  |  ~\n");
	printr("Type \"help\" for better instruction for mode 1\n\n");
}

void StartScreen2()
{
	printr("Radix 2 - 36\nType: "); 
	printy("<Radix from> <Radix to> <Number>\n");
	printr("Example: "); 
	printy("10 2 1111      ");
	printr("Result --> "); 
	printy("1111\n\n");
}

void StartScreen3_1()
{
	printr("Type: ");
	printy("<a> <b> <c>\n");
	printr("Example: "); 
	printy("13 11 215\n");
	printr("Result:\n"); 
	printy("/ x = -1075 - 11 * t\n\\ y = 1290 + 13 * t\n\n");
}

void StartScreen3_2()
{
	printr("Type: ");
	printy("<k1> <k2> <k3> ...\n");
	printr("Example: "); 
	printy("If you have: 2x^2 - 5x + 2 = 0    Type: 2 -5 2      ");
	printr("Result --> "); 
	printy("2 | 0.5\n\n");
}

void StartScreen3_3()
{
	printr("Type: ");
	printy("<num1> <num2>\n");
	printr("Example: "); 
	printy("12 17\n");
	printr("Result:\n"); 
	printy("gcd = 1\n/ x = -7 - 17 * t\n\\ y = 5 + 12 * t\n\n");
}

void Instruction()
{
	printr("\nCommands:");
	printy("\nclear --> clear the cmd\nclose --> close the program\nmode --> change mode\n");
	printr("Operators:");
	printy("\n+ --> addition\n- --> subtraction\n* --> multiplication\n/ --> floating point division\n\\ --> integer division\n\% --> modulus\n^ --> exponentiation\n! --> factorial\nsqrt --> square root\ncbrt --> cubic root\nsin --> sine\ncos --> cosine\nabs --> absolute value\n& --> AND\n| --> OR\n~ --> XOR\n");
	printr("Examples:");
	printy("\n\"a + b\" | \"a - b\" | \"a * b\" | \"a / b\" | \"a \% b\" | \"a ^ b\" | \"a!\" | \"sqrt(a)\" | \"cbrt(a)\" | \"sin(a)\" | \"cos(b)\" | \"abs(a)\" | \"a & b\" | \"a | b\" | \"a ~ b\"\n\n");
}

