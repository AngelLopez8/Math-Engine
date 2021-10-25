CXX=g++
INC=include/
LIB=lib/
FILES=$(LIB)Vector3D.cpp

Main: Main.cpp
	$(CXX) Main.cpp $(FILES) -o Main