SHELL := /bin/bash
all: qsort

qsort: main.cpp
	g++ -std=c++17 main.cpp -o qsort

install:
	sudo mv -f qsort /usr/local/bin
	if [[ ! -d "${HOME}/.qsort" ]]; then \
		mkdir "${HOME}/.qsort"; \
	else \
		echo -e "\033[0;31m${HOME}/.qsort folder already exist, If you did any configurations, then everything will be reset to default. \nPress Enter to continue.\033[0m"; \
		read -s; \
	fi 
	cp -f "./extensions.json" "${HOME}/.qsort"
	cp -f "./examples/qsort.conf" "${HOME}/.qsort"
	sed -i 's/"biltudas1"/"${USER}"/g' "${HOME}/.qsort/qsort.conf"

clean:
	rm qsort