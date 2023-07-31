main: main.cpp *.hpp
	g++ main.cpp -o main -std=c++11

clean:
	touch main
	rm main
