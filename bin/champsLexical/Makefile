CC=gcc
CXX=g++
RM=rm -rf
CPPFLAGS= -std=c++11
LDFLAGS= -std=c++11
LDLIBS=

SRCS=main.cpp ../../lib/interfacetty/interfacetty.cpp ../../lib/gründ/commun.cpp ../../lib/gründ/parser.cpp ../../lib/gründ/preParser.cpp ../../lib/gründ/Head.cpp ../../lib/gründ/fichier.cpp ../../lib/gründ/lego.hpp freqFragment.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main  $(OBJS) $(LDLIBS) -std=c++11 -Wall -lglut -lGLU -lGL -lXmu -lX11 

main.o: main.cpp ../../lib/interfacetty/interfacetty.hpp ../../lib/gründ/parser.hpp ../../lib/gründ/preParser.hpp ../../lib/gründ/Head.hpp ../../lib/gründ/commun.hpp ../../lib/gründ/fichier.cpp ../../lib/gründ/lego.hpp freqFragment.hpp

interfacetty.o: 	../../lib/interfacetty/interfacetty.hpp 	../../lib/interfacetty/interfacetty.cpp
commun.o: 		../../lib/gründ/commun.cpp 	../../lib/gründ/commun.hpp 	../../lib/interfacetty/interfacetty.hpp

parser.o: 		../../lib/gründ/parser.cpp	../../lib/gründ/parser.hpp
preParser.o:		../../lib/gründ/preParser.cpp	../../lib/gründ/preParser.hpp
Head.o:   		../../lib/gründ/Head.hpp 	../../lib/gründ/Head.cpp 	../../lib/interfacetty/interfacetty.hpp
fichier.o:		../../lib/gründ/fichier.cpp
lego.o:                 ../../lib/gründ/lego.hpp
freqFragment.o:		freqFragment.cpp

clean:
	$(RM) *.o ../../lib/gründ/*.o ../../lib/interfacetty/*.o

