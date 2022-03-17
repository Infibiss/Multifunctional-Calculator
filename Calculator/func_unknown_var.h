#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void Findq(vector <ll> &q, ll a, ll b)
{
	while(b)
	{
		ll num = a / b;
		q.push_back(num);
		ll tmpa = b, tmpb = a - num * b;
		a = tmpa, b = tmpb;
	}
}

pair <ll, ll> Diafant(ll a, ll b, ll c)
{
	vector <ll> q;
	q.push_back(-1);
	Findq(q, a, b);
	vector <ll> p(q.size()); p[0] = 1;
	vector <ll> l(q.size()); l[0] = 0;

	for(int i = 1; i < q.size(); i++)
	{
		if(i == 1)
		{
			p[1] = q[1];
			l[1] = 1;
		}
		else if(i == 2)
		{
			p[2] = q[2] * p[1] + 1;
			l[2] = q[2];
		}
		else
		{
			p[i] = q[i] * p[i - 1] + p[i - 2];
			l[i] = q[i] * l[i - 1] + l[i - 2];
		}
	}

	pair <ll, ll> ans;
	ans.first = p[p.size() - 2]; ans.second = -l[l.size() - 2];
	if(q.size() % 2 == 0)
		ans.first *= c, ans.second *= c;
	else
		ans.first *= -c, ans.second *= -c;
	return ans;
}

void Fill_del(vector <ll> &v, ll num)
{
	num = abs(num);
	ll end = sqrt(num);
	for(ll i = 1; i <= end; i++)
		if(num % i == 0) {v.push_back(i); v.push_back(-i); v.push_back(num / i); v.push_back(-1 * num / i);} 

	sort(v.begin(), v.end());
}

void Highdeg(vector <string> &ans, vector <ll> &k)
{
	vector <ll> p;
	Fill_del(p, k[k.size() - 1]);
	vector <ll> q;
	Fill_del(q, k[0]);

	ll end = k.size();
	vector <ll> tmp(end);
	bool flag = false;
	for(int i = 0; !flag && i < p.size(); i++)
	{
		for(int j = 0; !flag && j < q.size(); j++)
		{
			double num = p[i] / (double)(q[j]);
			tmp[0] = k[0];
			for(int x = 1; x < end; x++)
				tmp[x] = tmp[x - 1] * num + k[x];

			if(tmp[end - 1] == 0)
			{
				for(int x = 0; x < end; x++)
					k[x] = tmp[x];
				ans.push_back(to_string(num));
				end--;
			}

			if(end == 3)
			{
				double d = k[1] * k[1] - 4 * k[0] * k[2];
				if(sqrt(d) != (ll)(sqrt(d)))
				{
					ans.push_back( "(" + to_string(-k[1]) + " + #" + to_string((ll)(d)) + ") / " + to_string(2 * k[0]) );
					ans.push_back( "(" + to_string(-k[1]) + " - #" + to_string((ll)(d)) + ") / " + to_string(2 * k[0]) );
					flag = true;
				}
			}
			if(end == 1) flag = true;
		}
	}

	return;
}