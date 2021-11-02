build: 
	g++ main.cpp UniformCostSearch.cpp AStar_Manhattan.cpp -o solve

run: 
	./solve

br:
	make build
	clear
	make run