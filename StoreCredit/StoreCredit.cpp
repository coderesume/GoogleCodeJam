// StoreCredit.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#ifdef _UNICODE
	typedef std::wstring _tstring;
	typedef std::wstringstream _tstringstream;
#else
	typedef std::string _tstring;
	typedef std::stringstream _tstringstream;
#endif

using namespace std;

// 3つの回答の中では1番速い
void Answer1_Quick( ofstream& ofs, int index, int credit, int numItems, vector<int>& prices )
{
	vector<int> original = prices;
	int s1 = -1;
	int s2 = -1;

	// 大きい順にソート
	std::sort( prices.begin(), prices.end(), std::greater<int>() );

	// credit より小さい要素をバイナリサーチで検索。
	vector<int>::iterator iter1 = std::lower_bound( prices.begin(), prices.end(), credit - 1, std::greater<int>() );
	if( iter1 == prices.end() )
	{
		// 見つからないはずはないらしいので、ここには来ないはず。
		return;
	}

	bool found = false;
	for( ; iter1 != prices.end(); iter1++ )
	{
		s1 = *iter1;
		vector<int>::const_iterator iter2 = std::lower_bound( iter1 + 1, prices.end(), credit - s1, std::greater<int>() );
		if( iter2 == prices.end() )
			continue;

		s2 = *iter2;
		if( s1 + s2 == credit )
		{
			found = true;
			break;
		}
	}

	if( 0 <= s1 && 0 <= s2 )
	{
		// ソートする前の配列を使って、何番目に出てくるのかを調べる。高速化の余地があるが、これでも合格できるみたい。
		vector<int>::iterator iter = std::find( original.begin(), original.end(), s1 );
		int v1 = iter - original.begin() + 1;
		if( s1 != s2 )
			iter = std::find( original.begin(), original.end(), s2 );
		else
			iter = std::find( iter + 1, original.end(), s2 );

		int v2 = iter - original.begin() + 1;

		if( v1 < v2 )
			ofs << "Case #" << index << ": " << v1 << " " << v2 << endl;
		else
			ofs << "Case #" << index << ": " << v2 << " " << v1 << endl;
	}
}

// 3つの回答の中では2番目に速い
void Answer2_Quick( ofstream& ofs, int index, int credit, int numItems, vector<int>& prices )
{
	vector<int> original = prices;
	int s1 = -1;
	int s2 = -1;

	// 大きい順にソート
	std::sort( prices.begin(), prices.end(), std::greater<int>() );

	// credit より小さい要素をバイナリサーチで検索。
	vector<int>::const_iterator iter = std::lower_bound( prices.begin(), prices.end(), credit - 1, std::greater<int>() );
	if( iter == prices.end() )
	{
		// 見つからないはずはないらしいので、ここには来ないはず。
		return;
	}

	int startIndex = iter - prices.begin();
	bool found = false;
	for( int i = startIndex; i < numItems; i++ )
	{
		s1 = prices[ i ];
		for( int j = i + 1; j < numItems; j++ )
		{
			s2 = prices[ j ];
			if( s1 + s2 == credit )
			{
				found = true;
				break;
			}
		}

		if( found )
			break;
	}

	if( 0 <= s1 && 0 <= s2 )
	{
		// ソートする前の配列を使って、何番目に出てくるのかを調べる。高速化の余地があるが、これでも合格できるみたい。
		vector<int>::iterator iter = std::find( original.begin(), original.end(), s1 );
		int v1 = iter - original.begin() + 1;
		if( s1 != s2 )
			iter = std::find( original.begin(), original.end(), s2 );
		else
			iter = std::find( iter + 1, original.end(), s2 );

		int v2 = iter - original.begin() + 1;

		if( v1 < v2 )
			ofs << "Case #" << index << ": " << v1 << " " << v2 << endl;
		else
			ofs << "Case #" << index << ": " << v2 << " " << v1 << endl;
	}
}

// 3つの回答の中では最も遅い。O(n*n)のオーダなので、アルゴリズムとしても良くない。
void Answer3_NotQuick( ofstream& ofs, int index, int credit, int numItems, const vector<int>& prices )
{
	int s1 = -1;
	int s2 = -1;

	vector<int>::const_iterator iter1 = prices.begin();
	vector<int>::const_iterator end = prices.end();
	for( ; iter1 != end; iter1++ )
	{
		s1 = *iter1;
		vector<int>::const_iterator iter2 = iter1 + 1;

		for( ; iter2 != end; iter2++ )
		{
			s2 = *iter2;
			if( s1 + s2 == credit )
				break;
		}
	}

	if( 0 <= s1 && 0 <= s2 )
	{
		// ソートする前の配列を使って、何番目に出てくるのかを調べる。高速化の余地があるが、これでも合格できるみたい。
		vector<int>::const_iterator iter = std::find( prices.begin(), prices.end(), s1 );
		int v1 = iter - prices.begin() + 1;
		if( s1 != s2 )
			iter = std::find( prices.begin(), prices.end(), s2 );
		else
			iter = std::find( iter + 1, prices.end(), s2 );

		int v2 = iter - prices.begin() + 1;

		if( v1 < v2 )
			ofs << "Case #" << index << ": " << v1 << " " << v2 << endl;
		else
			ofs << "Case #" << index << ": " << v2 << " " << v1 << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tstring inPath = _T("C:\\GoogleCodeJam\\StoreCredit\\data\\input.txt");
	_tstring outPath = _T("C:\\GoogleCodeJam\\StoreCredit\\data\\output.txt");

	ifstream ifs( inPath.c_str() );
	if( ifs.is_open() == false )
	{
		cout << _T("inPath open error.") << endl << inPath.c_str() << endl;
		getchar();
		return 0;
	}

	ofstream ofs( outPath.c_str(), ios::out );
	if( ofs.is_open() == false )
	{
		cout << _T("outPath open error.") << endl << outPath.c_str() << endl;
		getchar();
		return 0;
	}

	int numCases;
	ifs >> numCases;

	for( int i = 0; i < numCases; i++ )
	{
		vector<int> prices;
		int credit, numItems;
		ifs >> credit;
		ifs >> numItems;
		for( int j = 0; j < numItems; j++ )
		{
			int price;
			ifs >> price;
			prices.push_back( price );
		}

		// 3つの回答の中では1番速い
		Answer1_Quick( ofs, i + 1, credit, numItems, prices );

		// 3つの回答の中では2番目に速い
//		Answer2_Quick( ofs, i + 1, credit, numItems, prices );

		// 3つの回答の中では最も遅い。O(n*n)のオーダなので、アルゴリズムとしても良くない。
//		Answer2_Quick( ofs, i + 1, credit, numItems, prices );
	}

	cout << "done." << endl;
	getchar();

	return 0;
}

