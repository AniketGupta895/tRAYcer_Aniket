files = program

execute: $(files)
	./program > image1.ppm

program: testimage.cpp
	echo "Compiling testimage.cpp"
	g++ testimage.cpp -o program

# testvaluemaker: testvaluemaker.cpp
# 	echo "Compiling testvaluemaker"
# 	g++ testvaluemaker.cpp -o testvaluemaker

clean: 
	rm -f program testvaluemaker testfile.txt output.txt

print: $(wildcard *.cpp)
	ls -la $?