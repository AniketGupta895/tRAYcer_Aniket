files = multiplesphere

execute: $(files)
	./image4 > sampleimages/sampleimage4.ppm

multiplesphere: multiplesphere.cpp
	echo "Compiling multiplesphere.cpp"
	g++ -std=c++20 multiplesphere.cpp -o image4

tester: testvaluemaker.cpp
	echo "Compiling testvaluemaker.cpp"
	g++ testvaluemaker.cpp -o tester

clean: 
	rm -f image3 testvaluemaker testfile.txt output.txt

print: $(wildcard *.cpp)
	ls -la $?