ifeq ($(OS),Windows_NT)
	OUTPUT = test.exe
else ifeq ($(OS),Linux)
	OUTPUT = test.out
endif
COMPILER = g++
MAINFILE = .\src\test.cpp
all : $(OUTPUT)
$(OUTPUT) : .\src\oreno.h .\src\oreno.cpp .\src\calculate.cpp .\src\calculate.h $(MAINFILE)
	$(COMPILER) $(MAINFILE) .\src\oreno.cpp .\src\calculate.cpp -o $(OUTPUT)