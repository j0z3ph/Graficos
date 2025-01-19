MAIN=main.cpp
COMPILER=g++
APP=main.exe
GRAFICOS_H=graficos.hpp
GRAFICOS_LIB=graficos.o
GRAFICOS_SRC=graficos.cpp
WIN_FLAGS=-mwindows
run: $(APP)
	./$(APP)

$(APP): $(MAIN) $(GRAFICOS_H) $(GRAFICOS_LIB)
	$(COMPILER) -o $(APP) $(GRAFICOS_LIB) $(MAIN) $(WIN_FLAGS)

$(GRAFICOS_LIB): $(GRAFICOS_H) $(GRAFICOS_SRC)
	$(COMPILER) -c $(GRAFICOS_SRC) -o $(GRAFICOS_LIB)

clean: 
	del $(APP) $(GRAFICOS_LIB)