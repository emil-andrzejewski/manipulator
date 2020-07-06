TASKNO=5
APP=manipulator
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

__start__: obj ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir -p obj

./${APP}: obj/start.o obj/start.o obj/lacze_do_gnuplota.o obj/manipulator.o obj/wielobok.o obj/wektor.o obj/okrag.o obj/lista_przeszkod.o
	g++ -ggdb -o ./${APP} obj/start.o obj/lacze_do_gnuplota.o obj/manipulator.o obj/wielobok.o obj/wektor.o obj/okrag.o obj/lista_przeszkod.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/start.o: src/start.cpp inc/lacze_do_gnuplota.hh inc/manipulator.hh inc/wielobok.hh inc/wektor.hh inc/okrag.hh inc/lista_przeszkod.hh 
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/start.o src/start.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/manipulator.o: src/manipulator.cpp inc/manipulator.hh
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/manipulator.o src/manipulator.cpp

obj/wielobok.o: src/wielobok.cpp inc/wielobok.hh
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/wielobok.o src/wielobok.cpp

obj/wektor.o: src/wektor.cpp inc/wektor.hh
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/wektor.o src/wektor.cpp

obj/okrag.o: src/okrag.cpp inc/okrag.hh
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/okrag.o src/okrag.cpp

obj/lista_przeszkod.o: src/lista_przeszkod.cpp inc/lista_przeszkod.hh
	g++ -ggdb -Iinc -W -Wall -pedantic -c -o obj/lista_przeszkod.o src/lista_przeszkod.cpp


clean:
	rm -f obj/* ./${APP}_rozszerzony ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
