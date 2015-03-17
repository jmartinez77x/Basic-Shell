#Programmer's name: Joe Martinez

# Beginning of Makefile
LIB = lib/libparser.a lib/libshutil.a lib/libparser.so lib/libshutil.so
OBJS = obj/shutil.o obj/parser.o obj/sshell.o obj/variables.o obj/hash_table.o 
HEADER_FILES = include/shell.h include/parser.h include/variables.h include/hash_table.h 
EXECUTABLE = simpleshell
CFLAGS = -Wall
LIBCFLAGS = $(CFLAGS) -D_REENTRANT -fPIC
CC = gcc
# End of configuration options

#What needs to be built to make all files and dependencies
all: $(EXECUTABLE)

#Create the main executable
$(EXECUTABLE): lib $(LIB) $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

#Create .a files in /lib directory
lib/libparser.a : obj/parser.o	
	ar cr lib/libparser.a obj/parser.o
	ranlib lib/libparser.a

lib/libshutil.a : obj/shutil.o	
	ar cr lib/libshutil.a obj/shutil.o
	ranlib lib/libshutil.a

#Create .so files in /lib directory
lib/libparser.so : obj/parser.o
	$(CC) -shared -o $@ obj/parser.o -lc

lib/libshutil.so : obj/shutil.o
	$(CC) -shared -o $@ obj/shutil.o -lc

record: obj/record.o
	$(CC) -o record obj/record.o

#Recursively build object files
obj/%.o: src/%.c
	$(CC) $(LIBCFLAGS)  -c -Iinclude -o $@ $<

#Define dependencies for objects based on header files
#We are overly conservative here, parser.o should depend on parser.h only
$(OBJS) : $(HEADER_FILES) 

clean:
	-rm -f $(EXECUTABLE) record obj/*.o lib/*.a lib/*.so bin/record
run: 
	make record
	#(export LD_LIBRARY_PATH=~/.bashrc; ./record)
	make $(EXECUTABLE)
	(export LD_LIBRARY_PATH=lib; ./$(EXECUTABLE))

tarball:
	#(cd .. ; tar czf Martinez_Joe_a6.tar.z shell)

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