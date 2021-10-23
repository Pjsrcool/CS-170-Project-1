build: 
	g++ main.cpp -o solve

run: 
	./solve

br:
	make build
	clear
	make run