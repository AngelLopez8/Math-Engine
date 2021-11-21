CXX=g++
FILES=Vector/lib/Vector.cpp Vector/lib/Vector3D.cpp Matrix/lib/Matrix.cpp

Main: Main.cpp
	$(CXX) Main.cpp $(FILES) -o Main