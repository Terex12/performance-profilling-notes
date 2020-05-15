CXXFLAGS += -g -O3 -Wall -Werror -std=c++11
PAPI_DIR=/home/yufan/Software/papi
PAPI_INC = -I$(PAPI_DIR)/include 
PAPI_LIB = -L$(PAPI_DIR)/src
PAPI_LINK = -Wl,-rpath=$(PAPI_DIR)/src -lpapi

DEPS=test.cpp

all: seq

seq: $(DEPS)
	$(CXX) $(CXXFLAGS) $(PAPI_INC) $(PAPI_LIB) -o $@ $< $(PAPI_LINK)