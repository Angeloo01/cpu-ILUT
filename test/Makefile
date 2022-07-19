LIB_PATH = ../include
SRC_PATH = ../src
OUT_PATH = ../bin/test

COMMON_PATH = ../common

SRC_FILES := $(wildcard $(SRC_PATH)/*.cpp) $(wildcard $(SRC_PATH)/**/*.cpp)
COMMON_FILES := $(wildcard $(COMMON_PATH)/*.cpp) $(wildcard $(COMMON_PATH)/**/*.cpp)

$(info SRC_FILES [${SRC_FILES}])

COMP=g++
COMPFLAGS=$(addprefix -I,$(LIB_PATH)) $(addprefix -I,$(SRC_PATH)) -I$(COMMON_PATH)/include -g -O3

ALL = $(patsubst %.cpp,$(OUT_PATH)/%, $(wildcard *.cpp))
$(info Compiling [${ALL}])
all: $(ALL)

$(ALL): $(OUT_PATH)/%: %.cpp $(SRC_FILES) $(COMMON_FILES)
	$(COMP) $(COMPFLAGS) -o $@ $^


.PHONY: clean
clean:
	rm -f *.o $(ALL) *.d $(OUT_PATH)/*.o