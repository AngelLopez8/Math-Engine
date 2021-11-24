CXX=g++
VECTORFILES=Vector/lib/Vector.cpp
MATRIXFILES=Matrix/lib/Matrix.cpp
FILES= $(VECTORFILES) $(MATRIXFILES)

Main: Main.cpp
	$(CXX) Main.cpp $(FILES) -o Main