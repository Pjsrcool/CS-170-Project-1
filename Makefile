build: 
	g++ main.cpp Search.cpp -o solve

run: 
	./solve

br:
	make build
	clear
	make run