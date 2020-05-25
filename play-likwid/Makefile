CXXFLAGS += -g -O3 -Wall -Werror -std=c++11
PAPI_DIR=/home/yufan/Software/papi
PAPI_INC = -I$(PAPI_DIR)/include 
PAPI_LIB = -L$(PAPI_DIR)/src
PAPI_LINK = -Wl,-rpath=$(PAPI_DIR)/src -lpapi

                                                    
# LIKWID_DIR=/home/yufan/Software/likwid-5.0.1
# #/uufs/chpc.utah.edu/sys/installdir/likwid/5.0.1
# LIKWID_INC = -I$(LIKWID_DIR)/include
# LIKWID_LIB = -L$(LIKWID_DIR)/src
# LIKWID_LINK = -Wl,-rpath=$(LIKWID_DIR)/src -llikwid

DEPS=conv2d.cpp
DEPS1=test-lik.cpp
all: test-lik test-lik-novec #conv-papi conv-likw

conv-papi: $(DEPS)
	$(CXX) $(CXXFLAGS) -DPAPI_PERFMON -DA $(PAPI_INC) $(PAPI_LIB) -o $@ $< $(PAPI_LINK)

conv-likw: $(DEPS)
	$(CXX) $(CXXFLAGS) -DLIKWID_PERFMON -DA $(LIKWID_INC) $(LIKWID_LIB) -o $@ $< $(LIKWID_LINK)

test-lik: $(DEPS1)
	$(CXX) $(CXXFLAGS) -DLIKWID_PERFMON -o $@ $< -llikwid

test-lik-novec: $(DEPS1)
	$(CXX) $(CXXFLAGS) -fno-tree-vectorize -DLIKWID_PERFMON -o $@ $< -llikwid