all:
	cc baza.c main.c -o mydb -Wall --pedantic

test: all
	./mydb baza.csv list_students

test-dodaj_studenta: all
	./mydb baza.csv add_student Andrzej Andrzejewski 111 mail@edu.pl
  
test-dodaj_przedmiot: all
	./mydb baza.csv add_course 1DM4456 "GZK" 2020Z

test-ile_studentow: all
	./mydb baza.csv count_students

test-memory: all
	valgrind ./mydb baza.csv count_students

