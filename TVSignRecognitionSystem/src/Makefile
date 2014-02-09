# Indicates compilator to use
CC      = g++

# Specifies compilator options
CFLAGS  = -o3 `pkg-config --cflags opencv` -D LINUX
LDFLAGS = 
LDLIBS  = `pkg-config --libs opencv` -lboost_filesystem-mt

# Files extensions .cpp, .o
SUFFIXES = .cpp .o 
.SUFFIXES: $(SUFFIXES) .

# Name of the main program
#PROG  = search 

# Object files .o necessary to build the main program
OBJS  = fasthessian.o integral.o surf.o utils.o ipoint.o \
		k_means.o vocabularytree.o matchpic.o interface.o \
		testtool.o TVSignRecognitionSystem.o Template.o

#lib
libtvSign.a: $(OBJS)
	ar rc ../lib/libtvSign.a $(OBJS)

#all: $(PROG)

# Compilation and link
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -g -o $(PROG) $(OBJS) $(LDLIBS)

.cpp.o:
	$(CC)   $(CFLAGS) -c $< -g -o $@

clean:
	-rm -f *.o
	-rm -f ../lib/libtvSign.a
