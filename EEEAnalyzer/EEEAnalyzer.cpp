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
	TheRun.analyzeRun(sourceFile,OutDir);
	/*TheRun.open(sourceFile);
	
	//retrive struct
	TheRun.getArchStruct();
	TheRun.getGpsStruct();
	TheRun.getHeaderStruct();
	TheRun.getWsStruct();

	while(TheRun.analyzeEvent()==0)
	{
		cout<< "EVENT NUMBER "<<TheRun.getEvtNum()-1<<endl;
	  //get strip data
		E3StripDataVec vector=TheRun.getStripDataVector(kTopPlane);
		for (int i = 0;i< vector.size();i++)
		{
			vector.at(i).fillStream(std::cout);
			cout<<endl;
		}
		TheRun.getStripDataVector(kMidPlane);
		TheRun.getStripDataVector(kBotPlane);	

	 // get event time information


	}*/


	
	return 0;
}

