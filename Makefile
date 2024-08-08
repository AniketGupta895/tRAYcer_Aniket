files = multiplesphere

execute: $(files)
	./main > sampleimages/final_render.ppm

main: main.cpp
	echo "Compiling multiplesphere.cpp"
	g++ -std=c++20 main.cpp -o main

tester: testvaluemaker.cpp
	echo "Compiling testvaluemaker.cpp"
	g++ testvaluemaker.cpp -o tester

clean: 
	rm -f image3 testvaluemaker testfile.txt output.txt

print: $(wildcard *.cpp)
	ls -la $?