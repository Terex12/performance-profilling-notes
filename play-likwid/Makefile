CXXFLAGS += -g -O3 -Wall -std=c++11

#CHPC env
LIKWID_INC=/uufs/chpc.utah.edu/sys/installdir/likwid/5.0.1/include
LIKWID_LIB=/uufs/chpc.utah.edu/sys/installdir/likwid/5.0.1/lib
RUN_PATH=-Wl,-rpath,/uufs/chpc.utah.edu/sys/installdir/likwid/5.0.1/lib

DEPSTREAM=stream.cpp
all: stream test-lik


test-lik: test-lik.cpp
	$(CXX) $(CXXFLAGS) -I$(LIKWID_INC) -L$(LIKWID_LIB) $(RUN_PATH) -DLIKWID_PERFMON -o $@ $< -llikwid

test-lik-novec: test-lik.cpp
	$(CXX) $(CXXFLAGS) -I$(LIKWID_INC) -L$(LIKWID_LIB) $(RUN_PATH) -fno-tree-vectorize -DLIKWID_PERFMON -o $@ $< -llikwid

stream: $(DEPSTREAM)
	$(CXX) $(CXXFLAGS) -I$(LIKWID_INC) -L$(LIKWID_LIB) $(RUN_PATH) -fopenmp -DLIKWID_PERFMON -o $@ $< -llikwid


matmul-slow: matmul.slow.c
	gcc -DTIME -I$(LIKWID_INC) -L$(LIKWID_LIB) $(RUN_PATH) -DLIKWID_PERFMON -o $@ $< -llikwid

matmul-fast: matmul.fast.c
	gcc -DTIME -I$(LIKWID_INC) -L$(LIKWID_LIB) $(RUN_PATH) -DLIKWID_PERFMON -o $@ $< -llikwid

matmul-def: matmul.default.c
	gcc -DTIME -I$(LIKWID_INC) -L$(LIKWID_LIB) i$(RUN_PATH) -DLIKWID_PERFMON -o $@ $< -llikwid


clean:
	rm test-lik stream matmul-*
