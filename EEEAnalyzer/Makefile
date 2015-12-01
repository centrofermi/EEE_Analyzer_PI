CC = g++
CFLAGS = -c -Wall -malign-double
EXECUTABLE = EEE_Analyzer_PI_V2
ROOT_INCLUDE = -I/home/boss/EuTelescope/v01-17-05/root/5.34.18/include
ROOT_LIB= -L/home/boss/EuTelescope/v01-17-05/root/5.34.18/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic
all: EEE_Analyzer_PI

EEE_Analyzer_PI:E3Cluster.o E3Event.o E3Fitter.o E3Gps.o E3Hit.o E3Point.o E3RawData.o E3RecoEvent.o E3Calib.o E3Run.o E3StripData.o E3Track.o E3Vector.o stdafx.o E3OutFileBase.o E3OutFile2TT.o E3OutFileSUM.o E3OutFileOUT.o E3OutFileTIM.o
	$(CC)    E3OutFileBase.o E3OutFile2TT.o E3OutFileSUM.o E3OutFileOUT.o E3OutFileTIM.o E3Cluster.o E3Event.o E3Fitter.o E3Gps.o E3Hit.o E3Point.o E3RawData.o E3RecoEvent.o E3Calib.o E3Run.o E3StripData.o E3Track.o E3Vector.o stdafx.o EEEAnalyzer.cpp -o 		$(EXECUTABLE) $(ROOT_INCLUDE) $(ROOT_LIB)

E3OutFileBase.o: E3OutFileBase.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3OutFileBase.cpp
E3OutFileOUT.o: E3OutFileOUT.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3OutFileOUT.cpp
E3OutFileTIM.o: E3OutFileTIM.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3OutFileTIM.cpp
E3OutFile2TT.o: E3OutFile2TT.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3OutFile2TT.cpp
E3OutFileSUM.o: E3OutFileSUM.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3OutFileSUM.cpp    
E3Cluster.o: E3Cluster.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Cluster.cpp
E3Event.o: E3Event.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Event.cpp
E3Fitter.o: E3Fitter.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Fitter.cpp
E3Gps.o: E3Gps.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Gps.cpp
E3Hit.o: E3Hit.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Hit.cpp
E3Point.o: E3Point.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Point.cpp
E3RawData.o: E3RawData.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3RawData.cpp
E3RecoEvent.o: E3RecoEvent.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3RecoEvent.cpp	
E3Calib.o: E3Calib.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Calib.cpp
E3Run.o: E3Run.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Run.cpp
E3StripData.o: E3StripData.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3StripData.cpp
E3Track.o: E3Track.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Track.cpp
E3Vector.o: E3Vector.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) E3Vector.cpp
stdafx.o: stdafx.cpp
	$(CC) $(CFLAGS) $(ROOT_INCLUDE) stdafx.cpp
clean:
	rm -rf *o *~
cleanall: clean
	rm -rf $(EXECUTABLE)
