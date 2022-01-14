# les fichiers sources
SRC= sae.c testSae.c

#les fichiers objets : ils ont mêmes noms que les fichiers listés dans SRC
OBJ= $(SRC:.c=.o)

#edition des liens : génération de l'exécutable à partir des .o 
exe : $(OBJ)
	gcc $^ -o $@
# génération des .o à partir des .c et .h crrespondants : 
%.o: %.c %.h
	gcc -Wall -c $< -o $@

#nettoyage : destruction des .o et de l'exécutable
clean:
	rm *.o exe

#géneration de la documentation
doc :
	doxygen
