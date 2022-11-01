#really wish we could use autotools, or that we actually got to learn cmake

CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iinc/

terrordb: src/main.cpp
	${CXX} ${CXX_FLAGS} src/main.cpp -o terrordb
.DEFAULT_GOAL := terrordb
.PHONY: clean terrordb unzip

unzip:
	unzip *.zip

clean:
	rm -f terrordb
	rm -rf *.dSYM
