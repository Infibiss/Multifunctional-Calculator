#include "func_main.h"
#include "func_numsystems.h"
#include "func_out.h"
#include "func_unknown_var.h"

using namespace std;

#define forup(i, n) for(int i = 0; i < n; i++)
typedef string str;
typedef double db;
typedef long long ll;
const ll INF = 9999999999999;
const db PI = acos(-1);

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
				if(i == -1) throw 1;

				pair <char, int> x = {s[i], Priority(s[i])};
				while(!operat.empty() && operat.back().second >= x.second && 
					operat.back().first != '(' && operat.back().first != '#' && 
					operat.back().first != ':' && operat.back().first != ';' && 
					operat.back().first != '$' && operat.back().first != '@')
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
			if(operat.empty()) throw 1;
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
			ans.push_back({true, num, '~'});
		}
	}
	while(!operat.empty())
	{
		ans.push_back({false, db(INF), operat.back().first});
		operat.pop_back();
	}
}

void MainOut(vector <Cell> &ans)
{
	stack <db> out;
	forup(i, ans.size())
	{
		if(ans[i].isnum)
			out.push(ans[i].num);
		else
		{
			if(out.empty())
				throw 1;
			db x1 = out.top();
			out.pop();

			switch(ans[i].oper)
			{
				case '+': 
				{
					if(out.empty()) throw 2; 
					db x2 = out.top(); out.pop(); out.push(x2 + x1); break;
				}
				case '-': 
				{
					if(out.empty()) throw 3; 
					db x2 = out.top(); out.pop(); out.push(x2 - x1); break;
				}
				case '*': 
				{
					if(out.empty()) throw 4; 
					db x2 = out.top(); out.pop(); out.push(x2 * x1); break;
				}
				case '/': 
				{
					if(out.empty()) throw 5; 
					db x2 = out.top(); out.pop(); out.push(x2 / x1); break;
				}
				case '^': 
				{
					if(out.empty()) throw 6; 
					db x2 = out.top(); out.pop(); out.push(pow(x2, x1)); break;
				}
				case '$': 
				{
					out.push(abs(x1)); break;
				}
				case '#': 
				{
					if(x1 < 0) throw 7;
					out.push(sqrt(x1)); break;
				}
				case '@': 
				{
					if(x1 < 0) throw 18;
					out.push(cbrt(x1)); break;
				}
				case '\\':
				{
					if(out.empty()) throw 8;
					if(x1 == 0) throw 9;
					db x2 = out.top(); out.pop();
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) throw 8;
					out.push((ll)(x2) / (ll)(x1)); break;
				}
				case '!': 
				{
					if(x1 == int(x1))
					{
						if(x1 < 0) throw 10;
						out.push(fact(x1)); break;
					}
				}
				case '%':
				{
					if(out.empty() || x1 == 0) throw 11; 
					db x2 = out.top(); out.pop(); 
					if(x2 == (ll)(x2) && x1 == (ll)(x1)) 
					{
						out.push( (ll)(x2) % (ll)(x1) ); 
						break;
					}
				}
				case ':': 
				{
					if(x1 < 0) throw 12; 
					out.push(sin(x1 * PI / 180)); break;
				}
				case ';':
				{
					if(x1 < 0) throw 13; 
					out.push(cos(x1 * PI / 180)); break;
				}
				case '&':
				{
					if(out.empty() || x1 < 0) throw 14;
					db x2 = out.top(); out.pop(); 
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) throw 14;
					out.push((ll)(x2) & (ll)(x1)); break;
				}
				case '|':
				{
					if(out.empty() || x1 < 0) throw 15;
					db x2 = out.top(); out.pop(); 
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) throw 15;
					out.push((ll)(x2) | (ll)(x1)); break;
				}
				case '~':
				{
					if(out.empty() || x1 < 0) throw 16;
					db x2 = out.top(); out.pop(); 
					if(x1 != (ll)(x1) || x2 != (ll)(x2)) throw 16;
					out.push((ll)(x2) ^ (ll)(x1)); break;
				}

				default: throw 1;
			}
		}
	}

	if(out.size() != 1) throw 1;
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

    	try
    	{
			if(inp == "clear" || inp == "Clear" || inp == "CLEAR" || inp == "cls") 
			{
				system("cls");
				StartScreenMain();
				if(mode == 1) StartScreen1();
				else if(mode == 2) StartScreen2();
				else
				{
					if(tmpmode == 1) {cout << '\n'; StartScreen3_1();}
					else if(tmpmode == 2) {cout << '\n'; StartScreen3_2();}
					else {cout << '\n'; StartScreen3_3();}
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
							printy("1) Diophantine equation 2) Equation of higher degrees 3) Advanced Euclid algorithm\n");
							str choosemode1; getline(cin, choosemode1);
							tmpmode = choosemode1[0] - '0';
							if(tmpmode == 1) {cout << '\n'; StartScreen3_1(); break;}
							else if(tmpmode == 2) {cout << '\n'; StartScreen3_2(); break;}
							else if(tmpmode == 3) {cout << '\n'; StartScreen3_3(); break;}
							else {printr("Error -> "); printy("Wrong input\n\n");};
						}
					}
				}
				else throw 1;
			}
			else
			{
				if(mode == 1)
				{
					CheckWords(inp);

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
					}
					else throw 1;
				}
				if(mode == 2)
				{
					vector <str> res;
					Split(res, inp, ' ');

					for(int i = 0; i < res.size(); i++)
						for(int j = 0; j < res[i].size(); j++)
							if(isdigit(res[i][j]) == 0)
								throw 1;
					
					int radix1 = stoi(res[0]), radix2 = stoi(res[1]); str num = res[2];
					if(radix1 < 2 || radix1 > 36 || radix2 < 2 || radix2 > 36)
						throw 1;
					else
					{
						string result = Num2Num(radix1, radix2, num);
						if(result == "WRONG NUMBER")
							throw 1;
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
				if(mode == 3)
				{
					vector <str> res;
					Split(res, inp, ' ');

					if(res.size() == 0) 
						throw 1;

					forup(i, res.size())
						forup(j, res[i].size())
							if(IfOper(res[i][j]) != 4 && res[i][j] != ' ' && res[i][j] != '-' && res[i][j] != '+')
								throw 1;

					if(tmpmode == 1)
					{
						if(res.size() != 3) throw 1;
						int x = stoi(res[0]), y = stoi(res[1]), z = stoi(res[2]);
						if(x == 0 || y == 0) throw 1;
						pair <ll, ll> a = Diafant(x, y, z);

						printg("Answer:\n"); 
						green(); cout << "/ x = " << a.second;
						if(y > 0) cout << " - " << y << " * t\n";
						else cout << " + " << y << " * t\n";

						cout << "\\ y = " << a.first;
						if(x > 0) cout << " + " << x << " * t\n";
						else cout << " - " << x << " * t\n\n";

					}
					else if(tmpmode == 2)
					{
						vector <ll> k(res.size());
						for(int i = 0; i < res.size(); i++)
							k[i] = stoi(res[i]);

						vector <str> ans;
						Highdeg(ans, k);

						if(ans.size() == 0)
							throw 17;
						printg("Roots = | ");
						for(int i = 0; i < ans.size(); i++)
							printg(ans[i] + " | ");
						cout << "\n\n";
					}
					else
					{
						if(res.size() != 2) throw 1;
						ll a = stoi(res[0]), b = stoi(res[1]), x0, y0, gcdnum;
						gcdnum = gcd(a, b, x0, y0);

						printg("Answer:\n"); 
						green(); cout << "gcd = " << gcdnum << '\n';
						cout << "/ x = " << x0;
						if(b > 0) cout << " - " << b << " * t\n";
						else cout << " + " << b << " * t\n";

						cout << "\\ y = " << y0;
						if(a > 0) cout << " + " << a << " * t\n";
						else cout << " - " << a << " * t\n\n";
					}
				}
			}
    	}

		catch(int err)
		{
			if(err == 1)  {printr("Error -> "); printy("Wrong input\n\n");}
			if(err == 2)  {printr("Error -> "); printy("Wrong input + \n\n");}
			if(err == 3)  {printr("Error -> "); printy("Wrong input - \n\n");}
			if(err == 4)  {printr("Error -> "); printy("Wrong input * \n\n");}
			if(err == 5)  {printr("Error -> "); printy("Wrong input / \n\n");}
			if(err == 6)  {printr("Error -> "); printy("Wrong input ^ \n\n");}
			if(err == 7)  {printr("Error -> "); printy("Negative square root\n\n");}
			if(err == 18) {printr("Error -> "); printy("Negative cubic root\n\n");}
			if(err == 8)  {printr("Error -> "); printy("Wrong input \\ \n\n");}
			if(err == 9)  {printr("Error -> "); printy("Devision by zero\n\n");}
			if(err == 10) {printr("Error -> "); printy("Negative factorial\n\n");}
			if(err == 11) {printr("Error -> "); printy("Wrong input \% \n\n");}
			if(err == 12) {printr("Error -> "); printy("Wrong input sin\n\n");}
			if(err == 13) {printr("Error -> "); printy("Wrong input cos\n\n");}
			if(err == 14) {printr("Error -> "); printy("Wrong input & \n\n");}
			if(err == 15) {printr("Error -> "); printy("Wrong input | \n\n");}
			if(err == 16) {printr("Error -> "); printy("Wrong input ~ \n\n");}
			if(err == 17) {printr("Error -> "); printy("Bad root\n\n");}
		} 

    }
    CloseHandle(hOUTPUT);
    return 0;
}
