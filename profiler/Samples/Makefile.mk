# Common Makefile for all Samples
#
# Copyright (c) 2012, Eccam s.r.o.
# 
# All rights reserved.

# Should be included in a sample specific Makefile which should define SOURCES
ifndef TOOLS_PLATFORM
    TOOLS_PLATFORM=$(PLATFORM)
endif

EPROFILER_DIR=../../../EProfiler/$(PLATFORM)/lib
SYMBOL_GENERATOR=../../../PerformanceAnalyzer/$(TOOLS_PLATFORM)/bin/EProfilerSymGen

CFLAGS=$(PLATFORM_CFLAGS) -Wall -O2 -finstrument-functions -c
ifeq ($(PLATFORM),windows64-mingw)
    LDFLAGS=$(PLATFORM_LDFLAGS) -Wl,-Map $(EXECUTABLE).map
else
    LDFLAGS=$(PLATFORM_LDFLAGS) -Wl,-Map=$(EXECUTABLE).map
endif    
LIBS=-L$(EPROFILER_DIR) -lEProfiler -Wl,-rpath=$(EPROFILER_DIR)

VPATH=$(CURDIR)/..
OBJECTS=$(SOURCES:.cpp=.o)

# Targets
.PHONY: all build symbols

all: build symbols

build : $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

symbols: $(EXECUTABLE).map
	$(SYMBOL_GENERATOR) $(EXECUTABLE).map $(EXECUTABLE).sym

$(EXECUTABLE).map: build

clean:
	rm *.o *.map *.sym $(EXECUTABLE)

