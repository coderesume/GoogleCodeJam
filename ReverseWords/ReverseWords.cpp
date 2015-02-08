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

void Answer( ofstream& ofs, int index, vector<string>& words )
{
	vector<string>::reverse_iterator iter = words.rbegin();
	vector<string>::reverse_iterator end = words.rend();

	ofs << "Case #" << index << ": " ;

	for( ;  iter != end; iter++ )
	{
		ofs << *iter << " ";
	}

	ofs << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tstring inPath = _T("C:\\GoogleCodeJam\\ReverseWords\\data\\input.txt");
	_tstring outPath = _T("C:\\GoogleCodeJam\\ReverseWords\\data\\output.txt");

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

	// Ÿ‚Ìs‚Éi‚ß‚éB
	// go to next line.
	string line;
	std::getline( ifs, line );

	for( int i = 0; i < numCases; i++ )
	{
		line.clear();
		std::getline( ifs, line );
		
		vector<string> words;

		string::const_iterator iter = line.begin();
		string::const_iterator end = line.end();

		string curr;
		for( ; iter != end; iter++ )
		{
			if( _T(' ') != *iter )
			{
				curr.push_back( *iter );
			}
			else
			{
				words.push_back( curr );
				curr.clear();
			}
		}

		words.push_back( curr );

		Answer( ofs, i + 1, words );
	}

	cout << "done." << endl;
	getchar();

	return 0;
}

