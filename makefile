#makefile de test_bechfulladder
#la variable EXE correspond au nom du test a effectuer 

EXE = shape_Handler
COMP = g++
RM = rm
EDL = g++
ECHO = @echo
INTF = Intersection.h MultiPoly.h Point.h Polygon.h Rectangle.h Segment.h Shape.h ShapeHandler.h Union.h
REAL = $(INTF:.h=.cpp) main.cpp
OBJ =  $(REAL:.cpp=.o)
OUTPUT = -o
RMFLAGS = -f
EDLOPTION = 
CPPFLAGS = -c
COMPFLAGS = -std=c++11 -Wall #-FMAP
EDLFALGS = 
LIBS =
LIBPATH =
INPATH =
CLEAN = clean
SOS = backup

EXEC_OPT =

RUN : $(EXE)
	./$(EXE) $(EXEC_OPT)

$(EXE) : $(OBJ)
	$(ECHO) "Edition des liens"
	$(EDL) $(OUTPUT) $(EXE) $(EDLFLAGS) $(LIBPATH) $(OBJ) $(LIBS)

Intersection.o : Intersection.cpp Intersection.h Point.h MultiPoly.h Shape.h
MultiPoly.o : MultiPoly.cpp MultiPoly.h Shape.h Point.h
Point.o : Point.cpp Point.h
Polygon.o : Polygon.cpp Polygon.h Point.h Shape.h
Rectangle.o : Rectangle.cpp Rectangle.h Polygon.h Point.h
Segment.o : Segment.cpp Segment.h Polygon.h
Shape.o : Shape.cpp Shape.h Point.h
ShapeHandler.o : ShapeHandler.cpp ShapeHandler.h Point.h Shape.h Intersection.h Union.h Polygon.h Segment.h Rectangle.h ErrorCode.h
Union.o : Union.cpp Union.h MultiPoly.h

%.o : %.cpp
	$(ECHO) "Compilation de <$<>"
	$(COMP) $(CPPFLAGS) $(INPATH) $(COMPFLAGS) $<

$(CLEAN) :
	$(ECHO) "Nettoyage des fichiers crees !"
	$(RM) $(RMFLAGS) $(EXE) $(OBJ) $(EDLOPTION) #core

#$(SOS)
