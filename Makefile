build: 
	g++ main.cpp UniformCostSearch.cpp -o solve

run: 
	./solve

br:
	make build
	clear
	make run