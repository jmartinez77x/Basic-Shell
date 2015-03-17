#Programmer's name: Joe Martinez

# Beginning of Makefile
LIB = lib/libparser.a lib/libshutil.a lib/libparser.so lib/libshutil.so
OBJS = obj/shutil.o obj/parser.o obj/sshell.o
HEADER_FILES = include/shell.h include/parser.h
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

#Recursively build object files
obj/%.o: src/%.c
	$(CC) $(LIBCFLAGS)  -c -Iinclude -o $@ $<

#Define dependencies for objects based on header files
#We are overly conservative here, parser.o should depend on parser.h only
$(OBJS) : $(HEADER_FILES)

clean:
	-rm -f $(EXECUTABLE) obj/*.o lib/*.a lib/*.so
run: 
	make $(EXECUTABLE)
	(export LD_LIBRARY_PATH=lib; ./$(EXECUTABLE))
#	./$(EXECUTABLE)

tarball:
	-rm -f $(EXECUTABLE) *.o 
	(cd .. ; tar czf Your_Name_a3.tar.z shell )

# End of Makefile

