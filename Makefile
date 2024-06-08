files = startingmessage program testvaluemaker

execute: $(files)
	./testvaluemaker > testfile.txt
	./program < testfile.txt > output.txt

program: vec3.cpp
	echo "Compiling vec3"
	g++ vec3.cpp -o program

testvaluemaker: testvaluemaker.cpp
	echo "Compiling testvaluemaker"
	g++ testvaluemaker.cpp -o testvaluemaker

startingmessage:
	echo "These are the targets:" $(files)

clean: 
	rm -f program testvaluemaker testfile.txt output.txt

print: $(wildcard *.cpp)
	ls -la $?