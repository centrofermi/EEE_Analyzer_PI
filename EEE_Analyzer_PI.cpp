// EEEAnalyzer.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"


using namespace std;

int main(int argc, char* argv[])
{
	
	E3Run E3Evt;
	if (argc==1) 
		E3Evt.analyzeRun("C:/Users/Boss/Desktop/Data/PISA-01-2015-02-21-00004.bin","C:/Users/Boss/Desktop/Data/Out/");
	if (argc==2)
	{
		std::string sourceFile=argv[1];
		std::string OutDir = sourceFile.substr(0,sourceFile.find_last_of("\\/",sourceFile.size()-2)+1);

		E3Evt.analyzeRun(sourceFile,OutDir);
	}
	if (argc==3)
	{
		std::string sourceFile=argv[1];
		std::string OutDir = argv[2];

		E3Evt.analyzeRun(sourceFile,OutDir);
	}

	
	
	return 0;
}

