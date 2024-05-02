MAIN=test.c
run: main.exe
	.\main.exe

main.exe: miniwin.c $(MAIN) miniwin.h
	gcc -o main.exe miniwin.c $(MAIN) -mwindows