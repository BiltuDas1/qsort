all: qsort

qsort: main.cpp
	g++ -std=c++17 main.cpp -o qsort

install:
	sudo mv qsort /usr/local/bin

clean:
	rm qsort