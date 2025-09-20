ifeq ($(OS),Windows_NT)
	SYM = /
	OUTPUT = test.exe
else
	SYM = /
	OUTPUT = test.out
endif
.PHONY : all
COMPILER = g++
MAINFILE = .$(SYM)src$(SYM)test.cpp
all : $(OUTPUT)
$(OUTPUT) : .$(SYM)src$(SYM)oreno.h .$(SYM)src$(SYM)oreno.cpp .$(SYM)src$(SYM)calculate.cpp .$(SYM)src$(SYM)calculate.h $(MAINFILE)
	$(COMPILER) $(MAINFILE) .$(SYM)src$(SYM)oreno.cpp .$(SYM)src$(SYM)calculate.cpp -o $(OUTPUT)
