CC=gcc
CXX=g++
RM=rm -rf
CPPFLAGS=-g
LDFLAGS=-g 
LDLIBS=

SRCS=main.cpp ../../../voca/lib/gründ/fichier.cpp ../../../voca/lib/interfacetty/interfacetty.cpp ../../../voca/lib/gründ/commun.cpp ../../../voca/lib/gründ/parser.cpp ../../../voca/lib/gründ/Head.cpp ../../../voca/lib/gründ/preParser.cpp 

OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS) 

main.o: main.cpp ../../../voca/lib/gründ/fichier.hpp ../../../voca/lib/interfacetty/interfacetty.hpp ../../../voca/lib/gründ/parser.hpp ../../../voca/lib/gründ/preParser.hpp ../../../voca/lib/gründ/Head.hpp ../../../voca/lib/gründ/commun.hpp

../../../voca/lib/gründ/fichier.o:	../../../voca/lib/gründ/fichier.cpp		../../../voca/lib/gründ/fichier.hpp
interfacetty.o: 	../../../voca/lib/interfacetty/interfacetty.hpp 	../../../voca/lib/interfacetty/interfacetty.cpp
commun.o: 		../../../voca/lib/gründ/commun.cpp 	../../../voca/lib/gründ/commun.hpp 	../../../voca/lib/interfacetty/interfacetty.hpp
head.o:			../../../voca/lib/gründ/Head.cpp  ../../../voca/lib/gründ/Head.hpp
parser.o: 		../../../voca/lib/gründ/parser.cpp	../../../voca/lib/gründ/parser.hpp
preParser.o:		../../../voca/lib/gründ/preParser.cpp	../../../voca/lib/gründ/preParser.hpp


clean:
	$(RM) *.o ../../../voca/lib/gründ/*.o ../../../voca/lib/interfacetty/*.o

