CXXFLAGS += -g -O3 -Wall -std=c++11


DEPS=conv2d.cpp
DEPS1=test-lik.cpp
DEPSTREAM=stream.cpp
all:  stream#conv-papi conv-likw


conv-likw: $(DEPS)
	$(CXX) $(CXXFLAGS) -DLIKWID_PERFMON -DA $(LIKWID_INC) $(LIKWID_LIB) -o $@ $< $(LIKWID_LINK)

test-lik: $(DEPS1)
	$(CXX) $(CXXFLAGS) -DLIKWID_PERFMON -o $@ $< -llikwid

test-lik-novec: $(DEPS1)
	$(CXX) $(CXXFLAGS) -fno-tree-vectorize -DLIKWID_PERFMON -o $@ $< -llikwid

stream: $(DEPSTREAM)
	$(CXX) $(CXXFLAGS) -fopenmp -DLIKWID_PERFMON -o $@ $< -llikwid