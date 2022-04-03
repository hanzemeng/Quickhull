main: main.o Line.o
	g++ main.o Line.o -std=c++17 -Wall -o main

main.o: main.cpp Line.cpp
	g++ main.cpp -std=c++17 -Wall -c

Line.o: Line.cpp
	g++ Line.cpp -std=c++17 -Wall -c

clean:
	rm -f *.o main

run:
	./main points_500000.txt

runTime:
	./main points_10.txt
	./main points_20.txt
	./main points_30.txt
	./main points_40.txt
	./main points_50.txt
	./main points_100.txt
	./main points_500.txt
	./main points_1000.txt
	./main points_5000.txt
	./main points_10000.txt
	./main points_50000.txt
	./main points_100000.txt
	./main points_500000.txt
	./main points_1000000.txt
