SHELL := /bin/bash
all: qsort

qsort: main.cpp lib/user.hpp
	g++ -std=c++20 main.cpp -o qsort

install:
	mv -f qsort /usr/local/bin
	if [[ ! -d "/etc/qsort" ]]; then \
		mkdir "/etc/qsort"; \
	else \
		echo -e "\033[0;31m/etc/qsort folder already exist, If you did any configurations, then everything will be reset to default. \nPress Enter to continue.\033[0m"; \
		read -s; \
	fi 
	cp -f "./conf/extensions.json" "/etc/qsort"
	cp -f "./conf/qsort.conf" "/etc/qsort"
	cp -f "./conf/qsort-completion.bash" "/etc/bash_completion.d"

deb: qsort-debian.deb

qsort-debian.deb:
	g++ -std=c++20 main.cpp -o qsort
	mkdir -p qsort-debian/usr/local/bin
	cp -fr DEBIAN qsort-debian/
	cp -f qsort qsort-debian/usr/local/bin/
	mkdir -p qsort-debian/etc/qsort qsort-debian/etc/bash_completion.d
	cp -f conf/* qsort-debian/etc/qsort/
	mv qsort-debian/etc/qsort/qsort-completion.bash qsort-debian/etc/bash_completion.d
	dpkg-deb --build qsort-debian
	rm -drf qsort-debian

autofill: conf/qsort-completion.bash
	sudo cp "./conf/qsort-completion.bash" "/etc/bash_completion.d/"

clean:
	rm qsort