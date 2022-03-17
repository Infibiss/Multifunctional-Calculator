#include "func_main.h"
#include "func_numsystems.h"
#include "func_out.h"
#include "func_unknown_var.h"

using namespace std;

#define forup(i, n) for(int i = 0; i < n; i++)
typedef string str;
typedef double db;
typedef long long ll;
const ll INF = 999999999;
const db PI = acos(-1);

bool error = false;
struct Cell{bool isnum; db num; char oper;};

void MakeAnswer(str s, vector <Cell> &ans)
{
	vector < pair <char, int> > operat;
	forup(i, s.size())
	{
		if(s[i] == ' ') continue;

		int type = IfOper(s[i]);

		if(type == 1)
		{
			if((s[i] == '+' || s[i] == '-') && IfRealOper(s, i) == false)
				type = 4;
			else
			{
				if(i == -1)
				{
					printr("1 WRONG INPUT!\n\n");
					error = true;
					return;
				}

				pair <char, int> x = {s[i], Priority(s[i])};
				while(!operat.empty() && operat.back().second >= x.second && 
					operat.back().first != '(' && operat.back().first != '#' && 
					operat.back().first != ':' && operat.back().first != ';' && 
					operat.back().first != '$')
				{
					ans.push_back({false, db(INF), operat.back().first});
					operat.pop_back();
				}
				operat.push_back(x);
			}
		}

		if(type == 2)
			operat.push_back( {s[i], Priority(s[i])} );

		if(type == 3)
		{
			while(!operat.empty() && operat.back().first != '(')
			{
				ans.push_back({false, db(INF), operat.back().first});
				operat.pop_back();
			}
			if(operat.empty())
			{
				printr("2 WRONG INPUT!\n\n");
				error = true;
				return;
			}
			operat.pop_back();
		}

		if(type == 4)
		{
			str number = "";
			number += s[i++];
			for(; i < s.size() && (IfOper(s[i]) == 4 || s[i] == '.') && s[i] != ' '; i++)
				number += s[i];
			i--;

			db num = atof(number.c_str());
			//cout << num << endl;
			ans.push_back({true, num, '~'});
		}

		/*for(auto it : operat)
			cout << it.first;
		cout << endl;*/
	}
	while(!operat.empty())
	{
		ans.push_back({false, db(INF), operat.back().first});
		operat.pop_back();
	}
}

void MainOut(vector <Cell> &ans)
{
	if(error)
		return;
	stack <db> out;
	forup(i, ans.size())
	{
		if(ans[i].isnum)
			out.push(ans[i].num);
		else
		{
			if(out.empty()) { printr("3 WRONG INPUT!\n\n"); return;}
			db x1 = out.top();
			out.pop();

			switch(ans[i].oper)
			{
				case '+': {if(out.empty()) {printr("4 WRONG INPUT!\n\n"); return;} db x2 = out.top(); out.pop(); out.push(x2 + x1); break;}
				case '-': {if(out.empty()) {printr("5 WRONG INPUT!\n\n"); return;} db x2 = out.top(); out.pop(); out.push(x2 - x1); break;}
				case '*': {if(out.empty()) {printr("6 WRONG INPUT!\n\n"); return;} db x2 = out.top(); out.pop(); out.push(x2 * x1); break;}
				case '/': {if(out.empty()) {printr("7 WRONG INPUT!\n\n"); return;} db x2 = out.top(); out.pop(); out.push(x2 / x1); break;}
				case '^': {if(out.empty()) {printr("8 WRONG INPUT!\n\n"); return;} db x2 = out.top(); out.pop(); out.push(pow(x2, x1)); break;}
				case '$':{out.push(abs(x1)); break;}
				case '#': 
				{
					if(x1 < 0) {printr("NEGATIVE SQUARE ROOT!\n\n"); return;}
					out.push(sqrt(x1)); break;
				}
				case '\\':
				{
					if(out.empty()) {printr("8.1 WRONG INPUT!\n\n"); return;}
					if(x1 == 0) {printr("Division by zero!\n\n"); return;}
					db x2 = out.top(); out.pop();
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) {printr("Float point WRONG INPUT!\n\n"); return;}
					out.push((ll)(x2) / (ll)(x1)); break;
				}
				case '!': 
				{
					if(x1 == int(x1))
					{
						if(x1 < 0) {printr("NEGATIVE FACTORIAL!\n\n"); return;}
						out.push(fact(x1)); break;
					}
				}
				case '%':
				{
					if(out.empty() || x1 == 0) {printr("9 WRONG INPUT!\n\n"); return;} 
					db x2 = out.top(); out.pop(); 
					if(x2 == (ll)(x2) && x1 == (ll)(x1)) 
					{
						out.push( (ll)(x2) % (ll)(x1) ); 
						break;
					}
				}
				case ':': 
				{
					if(x1 < 0) {printr("sin WRONG INPUT!\n\n"); return;} 
					out.push(sin(x1 * PI / 180)); break;
				}
				case ';':
				{
					if(x1 < 0) {printr("cos WRONG INPUT!\n\n"); return;} 
					out.push(cos(x1 * PI / 180)); break;
				}
				case '&':
				{
					if(out.empty() || x1 < 0) {printr("1 and WRONG INPUT!\n\n"); return;}
					db x2 = out.top(); out.pop(); 
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) {printr("2 and WRONG INPUT!\n\n"); return;}
					out.push((ll)(x2) & (ll)(x1)); break;
				}
				case '|':
				{
					if(out.empty() || x1 < 0) {printr("1 or WRONG INPUT!\n\n"); return;}
					db x2 = out.top(); out.pop(); 
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) {printr("2 or WRONG INPUT!\n\n"); return;}
					out.push((ll)(x2) | (ll)(x1)); break;
				}
				case '~':
				{
					if(out.empty() || x1 < 0) {printr("1 xor WRONG INPUT!\n\n"); return;}
					db x2 = out.top(); out.pop(); 
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) {printr("2 xor WRONG INPUT!\n\n"); return;}
					out.push((ll)(x2) ^ (ll)(x1)); break;
				}

				default: printr("10 WRONG INPUT!\n\n"); return;
			}
		}
	}

	if(out.size() != 1)
		{ printr("11 WRONG INPUT!\n\n"); return; }
	printg("Answer = "); green(); cout << fixed << setprecision(3) << out.top() << "\n\n";
}

void debug(vector <Cell> &ans)
{
	for(int i = 0; i < ans.size(); i++)
	{
		if(ans[i].isnum == true)
			cout << ans[i].num << ' ';
		else
			cout << ans[i].oper << ' ';
	}
	cout << '\n';
}

int main()
{
	StartScreenMain();
	StartScreen1();

	int mode = 1, tmpmode = 1;
    while(1)
    {
    	white(); str inp; getline(cin, inp);

		if(inp == "clear" || inp == "Clear" || inp == "CLEAR" || inp == "cls") 
		{
			system("cls");
			StartScreenMain();
			if(mode == 1) StartScreen1();
			else if(mode == 2) StartScreen2();
			else
			{
				if(tmpmode == 1) {cout << '\n'; StartScreen3_1();}
				else {cout << '\n'; StartScreen3_2();}
			}
		}
		else if(inp == "close" || inp == "Close" || inp == "CLOSE")
			break;
		else if(inp == "help" || inp == "HELP" || inp == "Help")
			Instruction();
		else if(inp == "mode" || inp == "Mode" || inp == "MODE")
		{
			printy("\n1) Usual calculator 2) Number systems calculator 3) Unknown var calculator\n");
			str choosemode; getline(cin, choosemode);
			if(choosemode == "1" || choosemode == "2" || choosemode == "3") 
			{
				mode = choosemode[0] - '0';
				if(mode == 1) {cout << '\n'; StartScreen1();}
				else if(mode == 2) {cout << '\n'; StartScreen2();}
				else
				{
					cout << '\n';
					while(1)
					{
						printy("1) Diophantine equation 2) Equation of higher degrees\n");
						str choosemode1; getline(cin, choosemode1);
						tmpmode = choosemode1[0] - '0';
						if(tmpmode == 1) {cout << '\n'; StartScreen3_1(); break;}
						else if(tmpmode == 2) {cout << '\n'; StartScreen3_2(); break;}
						else printr("11.1 WRONG INPUT\n\n");
					}
				}
			}
			else printr("12 WRONG INPUT\n\n");
		}
		else
		{
			if(mode == 1)
			{
				CheckSinCosAbs(inp);

				bool flag = true;
				forup(i, inp.size())
					if(IfOper(inp[i]) == -1 && inp[i] != ' ' && inp[i] != '.')
						{flag = false; break;}

				if(inp.size() != 0 && flag && CheckBrackets(inp))
				{
					CheckMulti(inp);

					//cout << inp;
					//return 0;

			    	vector <Cell> ans;
			    	MakeAnswer(inp, ans);

			    	//debug(ans);
			    	//return 0;

			    	MainOut(ans);
			    	error = false;
				}
				else
					printr("13 WRONG INPUT!\n\n");
			}
			if(mode == 2)
			{
				vector <str> res;
				Split(res, inp, ' ');
				if( (res[0].size() == 1 && isdigit(res[0][0]) || res[0].size() == 2 && isdigit(res[0][0]) && isdigit(res[0][1]) ) &&
					(res[1].size() == 1 && isdigit(res[1][0]) || res[1].size() == 2 && isdigit(res[1][0]) && isdigit(res[1][1]) ) )
				{
					int radix1 = stoi(res[0]), radix2 = stoi(res[1]); str num = res[2];
					if(radix1 < 2 || radix1 > 36 || radix2 < 2 || radix2 > 36)
						printr("14 WRONG INPUT!\n\n");
					else
					{
						string result = Num2Num(radix1, radix2, num);
						if(result == "WRONG NUMBER")
							printr("15 WRONG INPUT!\n\n");
						else
						{
							printg("Answer = ");
							for(int i = result.size() - 1; i >=0 ; i--)
							{
								str s = ""; s += result[i];
								printg(s);
							}
							printg("\n\n");
						}
					}

				}
				else {printr("16 WRONG INPUT!\n\n"); continue;}
			}
			if(mode == 3)
			{
				vector <str> res;
				Split(res, inp, ' ');

				if(tmpmode == 1)
				{
					int x = stoi(res[0]), y = stoi(res[1]), z = stoi(res[2]);
					pair <ll, ll> a = Diafant(x, y, z);

					printg("Answer = "); printg(to_string(a.first)); printg("x "); 
					if(a.second < 0) printg("- "); else printg("+ "); printg(to_string(abs(a.second))); printg("y");
					printg(" = "); printg(to_string(z));
					cout << "\n\n";
				}
				else
				{
					vector <ll> k(res.size());
					for(int i = 0; i < res.size(); i++)
						k[i] = stoi(res[i]);

					vector <str> ans;
					Highdeg(ans, k);

					if(ans.size() == 0)
					{
						printr("Bad root\n\n");
						continue;
					}
					printg("Answer = | ");
					for(int i = 0; i < ans.size(); i++)
						printg(ans[i] + " | ");
					cout << "\n\n";
				}
			}
		}

    }
    CloseHandle(hOUTPUT);
    return 0;
}
