all: qsort

qsort: main.cpp
	g++ -std=c++17 main.cpp -o qsort

clean:
	rm qsort