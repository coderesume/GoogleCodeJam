// T9Spelling.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
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

void Answer( ofstream& ofs, int index, const string& line )
{
	string::const_iterator iter = line.begin();
	string::const_iterator end = line.end();

	string output;
	char prev = -1;
	for( ; iter != end; iter++ )
	{
		char curr = *iter;

		switch( curr )
		{
		case ' ':
			if( '0' == prev )
				output.push_back( ' ' );
			prev = '0';
			output.push_back( '0' );
			break;
		case 'a':
		case 'b':
		case 'c':
			if( '2' == prev )
				output.push_back( ' ' );
			prev = '2';
			for( int i = 0; i < curr - 'a' + 1; i++ )
				output.push_back( '2' );
			break;
		case 'd':
		case 'e':
		case 'f':
			if( '3' == prev )
				output.push_back( ' ' );
			prev = '3';
			for( int i = 0; i < curr - 'd' + 1; i++ )
				output.push_back( '3' );
			break;
		case 'g':
		case 'h':
		case 'i':
			if( '4' == prev )
				output.push_back( ' ' );
			prev = '4';
			for( int i = 0; i < curr - 'g' + 1; i++ )
				output.push_back( '4' );
			break;
		case 'j':
		case 'k':
		case 'l':
			if( '5' == prev )
				output.push_back( ' ' );
			prev = '5';
			for( int i = 0; i < curr - 'j' + 1; i++ )
				output.push_back( '5' );
			break;
		case 'm':
		case 'n':
		case 'o':
			if( '6' == prev )
				output.push_back( ' ' );
			prev = '6';
			for( int i = 0; i < curr - 'm' + 1; i++ )
				output.push_back( '6' );
			break;
		case 'p':
		case 'q':
		case 'r':
		case 's':
			if( '7' == prev )
				output.push_back( ' ' );
			prev = '7';
			for( int i = 0; i < curr - 'p' + 1; i++ )
				output.push_back( '7' );
			break;
		case 't':
		case 'u':
		case 'v':
			if( '8' == prev )
				output.push_back( ' ' );
			prev = '8';
			for( int i = 0; i < curr - 't' + 1; i++ )
				output.push_back( '8' );
			break;
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			if( '9' == prev )
				output.push_back( ' ' );
			prev = '9';
			for( int i = 0; i < curr - 'w' + 1; i++ )
				output.push_back( '9' );
			break;
		default:
			ATLASSERT( 0 );
			break;
		}
	}

	ofs << "Case #" << index << ": " << output << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tstring inPath = _T("C:\\GoogleCodeJam\\T9Spelling\\data\\input.txt");
	_tstring outPath = _T("C:\\GoogleCodeJam\\T9Spelling\\data\\output.txt");

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

	// 次の行に進める。
	string line;
	std::getline( ifs, line );

	for( int i = 0; i < numCases; i++ )
	{
		line.clear();
		std::getline( ifs, line );
		Answer( ofs, i + 1, line );
	}

	cout << "done." << endl;
	getchar();

	return 0;
}

