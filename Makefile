# Definitions de macro

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc
OFILES = projet.o
OFILESTEST = testsuit.o
# Definition de la premiere regle

build: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

test: $(OFILESTEST)
	@echo " *** Lance les test définit dans testsuit ***"
	$(CXX) testsuit.o -o testsuit
	./testsuit

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@echo " *** LANCER APRES CHAQUE AJOUT DE MODULE ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

testsuit.o: testsuit.cc testsuit.h textstorage.cc textstorage.h
projet.o: projet.cc projet.h
projet.o: projet.cc projet.h
projet.o: projet.cc projet.h
