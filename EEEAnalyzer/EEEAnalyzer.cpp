// EEEAnalyzer.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"


using namespace std;

int main(int argc, char* argv[])
{

	if (argc<2)
	{
		cout<< "Please provide input file"<<endl;
		return 1;
	}

	std::string sourceFile=argv[1];
	std::string OutDir = sourceFile.substr(0,sourceFile.find_last_of("\\/",sourceFile.size()-2)+1);

	E3Run TheRun;
	//TheRun.analyzeRun(sourceFile,OutDir);
	TheRun.open(sourceFile);
	TheRun.analyzeEvent();

	
	return 0;
}

