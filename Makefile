# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = prog.cc calendrier.cc difference.cc
OFILES = prog.o calendrier.o difference.o

# Definition de la premiere regle

prog: $(OFILES)
	$(CXX) $(OFILES) -o prog

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
calendrier.o: calendrier.cc calendrier.h
difference.o: difference.cc calendrier.h difference.h
prog.o: prog.cc calendrier.h difference.h
