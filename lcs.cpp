#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int max(const int& a, const int& b)
{
	return (a > b)?a:b;
}

int lcs(const string& s1, const string& s2, int m, int n)
{
	if(m == 0 || n == 0)
		return 0;

	if(s1[m-1] == s2[n-1])
	{
		
		return 1 + lcs(s1,s2,m-1, n-1);
	}
	else
	{	
		return max(lcs(s1, s2, m, n-1), lcs(s1, s2, m-1, n));
	}
} 

int getval(const vector< vector<int> >& v, int x, int y)
{
	if(x < 0 || y < 0)
		return 0;

	return v[x][y];
}


void printval(int v)
{
	printf("%d ",v);
}

void getlcsString(const string& s1, const string& s2, const vector< vector<int> >& v, int m, int n)
{
	string res("");

	for(int i = 0; i <= s1.length(); i++)
	{
		for_each(v[i].begin(), v[i].end(), printval);
		printf("\n");
	}

	while(m >= 0 && n >= 0)
	{
		if(m > 0 && n > 0 && s1[m-1] == s2[n-1])
		{
			res.push_back(s1[m-1]);
			m--;
			n--;
		}
		else
		{
			if(getval(v, m, n-1) > getval(v, m-1, n))
				n--;
			else
				m--;
		}
	}

	std::reverse(res.begin(), res.end());
	printf("LCS string : %s\n", res.c_str());
}

int lcsdp(const string& s1, const string& s2, int m, int n)
{
	vector< vector<int> > table(m+1, vector<int>(n+1) );
	
	for(int i = 0; i <= m; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			if(i == 0 || j == 0)
				table[i][j] = 0;
			else if(s1[i-1] == s2[j-1])
				table[i][j] = 1 + getval(table, i-1, j-1);
			else
				table[i][j] = max(getval(table, i, j-1), getval(table, i-1, j));
		}
	}
	
	getlcsString(s1,s2,table,m,n);
	return table[m][n];
}

int main(int argc, char* argv[])
{

	string s1("sjskfhsdufsshcbxncbsjsdhsfgyrewirusdjfhsfjhsdfjhsidufyfhsdfjhurysuifhsjfhurysfhrtreiotureoihdabcdfgjv");
	string s2("dhfskjafrutfhfhsfkjshdfusdhfksfhdydiuryewrsdkjfsdkfhwiureysafhskjfhjsdkfhskdjfhafgruoijkxbcdfdgnmdfjg");

//	string s1("AGGTAB");
//	string s2("GXTXAYB");

	int l = lcsdp(s1, s2, s1.length(), s2.length());
	
	printf("LCS is : %d\n",l);

	return 0;
}
