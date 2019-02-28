CC=gcc
CXX=g++
RM=rm -rf
CPPFLAGS=-g $(ncusesw5-config --cflags)
LDFLAGS=-g $(ncusesw5-config --ldflags)
LDLIBS=$(ncusesw5-config  --libs)

SRCS=main.cpp ../../lib/interfacetty/interfacetty.cpp ../../lib/parser/parser.cpp ../../lib/preParser/preParser.cpp ../../lib/gründ/Head.cpp ../../lib/gründ/Field.cpp ../../lib/gründ/Record.cpp Vokabel.cpp ../../lib/gründ/commun.cpp original2.cpp pedagogie.cpp ../../lib/winRoutines/winRoutines.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main -lpanel -lmenu -lform -lncursesw $(OBJS) $(LDLIBS) 

main.o: main.cpp ../../lib/interfacetty/interfacetty.hpp ../../lib/gründ/parser.hpppp ../../lib/gründ/preParser.hpppp ../../lib/gründ/Head.hpp ../../lib/gründ/Field.hpp ../../lib/gründ/Record.hpp ../../lib/gründ/commun.hpp Vokabel.hpp original2.hpp pedagogie.hpp ../../lib/winRoutines/winRoutines.hpp 

interfacetty.o: ../../lib/interfacetty/interfacetty.hpp 	../../lib/interfacetty/interfacetty.cpp
parser.o: 	../../lib/parser/parser.cpp			../../lib/gründ/parser.hpppp
preParser.o:	../../lib/preParser/preParser.cpp		../../lib/gründ/preParser.hpppp

Head.o:   	../../lib/gründ/Head.hpp 	../../lib/gründ/Head.cpp 	../../lib/interfacetty/interfacetty.hpp
Record.o: 	../../lib/gründ/Record.hpp 	../../lib/gründ/Record.cpp 	../../lib/interfacetty/interfacetty.hpp
Field.o:  	../../lib/gründ/Field.hpp 	../../lib/gründ/Field.cpp 	../../lib/interfacetty/interfacetty.hpp
commun.o: 	../../lib/gründ/commun.cpp 	../../lib/gründ/commun.hpp 	../../lib/interfacetty/interfacetty.hpp

pedagogie.o: 	pedagogie.hpp 		pedagogie.cpp
Vokabel.o: 	Vokabel.cpp 		Vokabel.hpp

original2.o: 	original2.hpp 		original2.cpp

winRoutines.o: 	../../lib/winRoutines/winRoutines.hpp 	../../lib/winRoutines/winRoutines.cpp

clean:
	$(RM) *.o ../../lib/gründ/*.o ../../lib/interfacetty/*.o ../../lib/parser/*.o ../../lib/preParser/*.o ../../lib/winRoutines/*.o

