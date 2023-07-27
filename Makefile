all: clox

clox: *.cpp *.h
	ccache g++ -std=c++17 -o clox *.cpp -Wall -Werror -O0;
clean:
	rm clox;