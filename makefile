main: main.o JNIHelper.o FileSystem.o FileOutStream.o FileInStream.o Status.o
	g++ -std=c++11  main.o JNIHelper.o FileOutStream.o FileInStream.o FileSystem.o Status.o -o testjava  -lpthread -ljvm

main.o: main.cpp include/JNIHelper.h include/FileSystem.h include/FileOutStream.h include/FileInStream.h
	g++ -std=c++11 -c main.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include -lpthread -o main.o

FileSystem.o: src/FileSystem.cpp include/FileSystem.h include/Options.hpp include/Wire.hpp include/JNIHelper.h include/FileOutStream.h include/FileInStream.h include/Status.h
	g++ -std=c++11 -c src/FileSystem.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -I/home/innkp/pasa/jsoncpp/include -lpthread -o FileSystem.o


FileOutStream.o: src/FileOutStream.cpp include/FileOutStream.h include/JNIHelper.h include/Status.h
	g++ -std=c++11 -c src/FileOutStream.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include   -lpthread -o FileOutStream.o

FileInStream.o: src/FileInStream.cpp include/FileInStream.h include/JNIHelper.h
	g++ -std=c++11 -c src/FileInStream.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include -lpthread -o FileInStream.o

JNIHelper.o: src/JNIHelper.cpp include/JNIHelper.h include/Status.h
	g++ -std=c++11 -c src/JNIHelper.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -lpthread -o JNIHelper.o

Wire.o: include/Wire.hpp
	g++ -std=c++11 -c include/Wire.hpp -I/home/innkp/Alluxio-Cpp/include  -o Wire.o

Options.o: include/Options.hpp
	g++ -std=c++11 -c include/Options.hpp -I/home/innkp/Alluxio-Cpp/include  -o Options.o


Status.o: src/Status.cpp include/Status.h
	g++ -std=c++11 -c src/Status.cpp -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L${JRE_HOME}/lib/amd64/server -I/home/innkp/Alluxio-Cpp/include  -lpthread  -o Status.o

