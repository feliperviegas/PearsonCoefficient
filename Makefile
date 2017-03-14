main:   main.cpp coef.cpp
	g++ -O3 -std=c++0x main.cpp coef.cpp -o coefPerson -lm

clean :
	rm coefPerson

