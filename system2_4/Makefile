tree: demo run

demo:
	g++ -o demo Demo.cpp -I/usr/include/SFML -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system

run: demo
	./demo
	
test: 
	g++ -o test Test.cpp tree.hpp node.hpp
	./test
