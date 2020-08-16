heapsort: heapsort.o heap.o
	g++ heapsort.o heap.o -o heapsort

heapsort.o: heapsort.cpp
	g++ -c heapsort.cpp

heap.o: heap.cpp
	g++ -c heap.cpp

clean:
	rm *.o heapsort
