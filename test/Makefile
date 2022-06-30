LIB_PATH = ../include
SRC_PATH = ../src
OUT_PATH = ../bin/test

SRC_FILES := $(wildcard $(SRC_PATH)/*.cpp) $(wildcard $(SRC_PATH)/**/*.cpp)

$(info SRC_FILES [${SRC_FILES}])

COMP=g++
COMPFLAGS=$(addprefix -I,$(LIB_PATH)) $(addprefix -I,$(SRC_PATH)) -g -O3

ALL = $(patsubst %.cpp,$(OUT_PATH)/%, $(wildcard *.cpp))
$(info Compiling [${ALL}])
all: $(ALL)

$(ALL): $(OUT_PATH)/%: %.cpp $(SRC_FILES)
	$(COMP) $(COMPFLAGS) -o $@ $^


.PHONY: clean
clean:
	rm -f *.o $(ALL)