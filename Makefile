files = image4 tester

execute: $(files)
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage1.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage2.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage3.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage4.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage5.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage6.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage7.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage8.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage9.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage10.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage11.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage12.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage13.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage14.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage15.ppm
	./tester > testfile.txt && ./image4 < testfile.txt > sampleimages/sampleimage16.ppm

image4: image4.cpp
	echo "Compiling image4.cpp"
	g++ -std=c++20 image4.cpp -o image4

# testvaluemaker: testvaluemaker.cpp
# 	echo "Compiling testvaluemaker"
# 	g++ testvaluemaker.cpp -o testvaluemaker

tester: testvaluemaker.cpp
	echo "Compiling testvaluemaker.cpp"
	g++ testvaluemaker.cpp -o tester

clean: 
	rm -f image3 testvaluemaker testfile.txt output.txt

print: $(wildcard *.cpp)
	ls -la $?