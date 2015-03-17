#Programmer's Name: Joe Martinez

SRVRheader=inc/server.h
CLNTheader=inc/client.h
SRVRsource=src/server.c
CLNTsource=src/client.c
SRVR=server
CLNT=client
CFLAGS = -Wall
CC = gcc

all: $(SRVR) $(CLNT) 

$(SRVR): $(SRVRsource)
	$(CC) $(CFLAGS) -Iinc $(SRVRsource) -o ./$@
 
$(CLNT): $(CLNTsource)
	$(CC) $(CFLAGS) -Iinc $(CLNTsource) -o ./$@	

runclient: $(CLNT)
	./$(CLNT)

runserver: $(SRVR)
	./$(SRVR)

run: all
	./$(SRVR)
	./$(CLNT)

clean:
	-rm -f $(SRVR) $(CLNT) 

tarball:
	cd ; tar czf Martinez_Joe_FinalProject.tar.z CSC60 

car:
	@echo '           __---~~~~~~--__                      __--~~~~~~---__'
	@echo '           \---~~~~~~~~~~\\                    //~~~~~~~~~~---/'
	@echo '            \/~~~~~~~~~~~\||                  ||/~~~~~~~~~~~\/'
	@echo '                          `\\                //'
	@echo '                            `\\            //'
	@echo '                              ||          ||  '
	@echo '                         _--~~~~~~~~~~~~~~~~~~--_ '
	@echo '               ___    _-~                        ~-_    ___'
	@echo '               \__)\/~                              ~\/(__/' 
	@echo '               _--`-___                            ___-`--_'
	@echo '             /~     `\ ~~~~~~~~------------~~~~~~~~ /`     ~\'
	@echo '            /|        `\         ________         /`        |\'
	@echo '           | `\   ______`\_      \------/      _/`______   /` |' 
	@echo '           |   `\_~-_____\ ~-________________-~ /_____-~_/`   |'
	@echo '           `.     ~-__________________________________-~     .'
	@echo '            `.      [_______/------|~~|------\_______]      .'
	@echo '             `\--___((____)(________\/________)(____))___--/'
	@echo '              |>>>>>>||                            ||<<<<<<|'
	@echo '              `\<<<<</`                            `\>>>>>/'	

# End of Makefile