build:
	mkdir bin || true
	g++ src/main.cpp -o bin/pmt -I src/algorithms -O2