all:
	cc baza.c main.c -o mydb -Wall --pedantic

test: all
	./mydb baza.csv lista_studentow

test-dodaj_studenta: all
	./mydb baza.csv dodaj_studenta Andrzej Andrzejewski 111 mail@edu.pl
  
test-dodaj_przedmiot: all
	./mydb baza.csv dodaj_przedmiot 1DM4456 "GZK" 2020Z

test-ile_studentow: all
	./mydb baza.csv ile_studentow

test-memory: all
	valgrind ./mydb baza.csv ile_studentow