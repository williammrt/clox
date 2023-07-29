all: clox_debug

clox_debug: *.cpp *.h
	ccache g++ -std=c++17 -o clox *.cpp -Wall -Werror -g;
clox_release:
	g++ -std=c++17 -o clox *.cpp -O2;
clean:
	rm clox;