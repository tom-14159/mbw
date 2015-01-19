#CFLAGS=-O2 -Wall  -mfpu=neon
CFLAGS=-O2 -mfpu=neon --static 

NAME=mbw
TARFILE=${NAME}.tar.gz

mbw: mbw.c
	$(CC) $(CFLAGS) -c -o mbw.o mbw.c
	$(CC) $(CFLAGS) -o mbw mbw.o -lpthread 

clean:
	rm -f mbw mbw.o
	rm -f ${NAME}.tar.gz

${TARFILE}: clean
	 tar cCzf .. ${NAME}.tar.gz --exclude-vcs ${NAME} || true

rpm: ${TARFILE}
	 rpmbuild -ta ${NAME}.tar.gz 
