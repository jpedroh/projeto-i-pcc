build:
	mkdir bin || true
	g++ -O3 src/main.cpp -o bin/pmt -I src/algorithms