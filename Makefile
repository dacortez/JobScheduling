SYSTEM     = x86-64_darwin9_gcc4.0
LIBFORMAT  = static_pic

#------------------------------------------------------------
# IMPORTANTE: CPLEXDIR e CONCERTDIR devem ser alterados para
# o diretório onde CPLEX e CONCERT estão instalados na sua 
# máquina.
#
# MODIFICAR AS LINHAS DE BAIXO DE ACORDO!!!
#
#------------------------------------------------------------

CPLEXDIR      = /Users/dacortez/Applications/IBM/ILOG/CPLEX_Studio124/cplex
CONCERTDIR    = /Users/dacortez/Applications/IBM/ILOG/CPLEX_Studio124/concert

# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++ -O0

# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fexceptions -DNDEBUG -DIL_STD

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m64 \
	-lm -lpthread -framework CoreFoundation -framework IOKit -Wall -ansi -pedantic
CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 

#------------------------------------------------------------
#  make all      : to compile the examples. 
#------------------------------------------------------------

BIN = ./bin
SRC = ./src

OBJECTS = $(BIN)/cplex_scheduler.o $(BIN)/generator.o $(BIN)/job.o $(BIN)/lpt_scheduler.o \
	$(BIN)/machine.o $(BIN)/main.o $(BIN)/scheduler.o 

EXEC = projeto325

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CCC) $(CCFLAGS) $(OBJECTS) -o $(BIN)/$(EXEC) $(CCLNFLAGS)

# ------------------------------------------------------------

$(BIN)/cplex_scheduler.o: $(SRC)/cplex_scheduler.h $(SRC)/scheduler.h $(SRC)/cplex_scheduler.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/cplex_scheduler.cpp -o $(BIN)/cplex_scheduler.o

$(BIN)/generator.o: $(SRC)/generator.h $(SRC)/job.h $(SRC)/machine.h $(SRC)/generator.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/generator.cpp -o $(BIN)/generator.o

$(BIN)/job.o: $(SRC)/job.h $(SRC)/job.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/job.cpp -o $(BIN)/job.o

$(BIN)/lpt_scheduler.o: $(SRC)/lpt_scheduler.h $(SRC)/scheduler.h $(SRC)/lpt_scheduler.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/lpt_scheduler.cpp -o $(BIN)/lpt_scheduler.o

$(BIN)/machine.o: $(SRC)/machine.h $(SRC)/machine.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/machine.cpp -o $(BIN)/machine.o

$(BIN)/main.o: $(SRC)/cplex_scheduler.h $(SRC)/generator.h $(SRC)/job.h $(SRC)/lpt_scheduler.h \
	$(SRC)/machine.h $(SRC)/scheduler.h $(SRC)/main.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/main.cpp -o $(BIN)/main.o

$(BIN)/scheduler.o: $(SRC)/generator.h $(SRC)/scheduler.h $(SRC)/scheduler.cpp
	$(CCC) -c $(CCFLAGS) $(SRC)/scheduler.cpp -o $(BIN)/scheduler.o

# ------------------------------------------------------------

clean:
	rm -rf $(BIN)/$(EXEC) $(BIN)/*.o
	rm -rf  *.out *~
	rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log *.clp

# ------------------------------------------------------------
