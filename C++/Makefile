MAIN=main.cpp

run: main.exe
	.\main.exe

main.exe: miniwin.cpp $(MAIN) miniwin.hpp
	g++ -o main.exe miniwin.cpp $(MAIN) -mwindows