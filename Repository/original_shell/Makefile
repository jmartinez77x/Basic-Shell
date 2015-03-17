# Beginning of Makefile
OBJS = shutil.o parser.o sshell.o
HEADER_FILES = shell.h parser.h
EXECUTABLE = simpleshell
CFLAGS = -Wall
CC = gcc
# End of configuration options

#What needs to be built to make all files and dependencies
all: $(EXECUTABLE)

#Create the main executable
$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

#Recursively build object files
%.o: %.c
	$(CC) $(CFLAGS)  -c -o $@ $<

#Define dependencies for objects based on header files
#We are overly conservative here, parser.o should depend on parser.h only
$(OBJS) : $(HEADER_FILES)

clean:
	-rm -f $(EXECUTABLE) *.o 
run: $(EXECUTABLE)
	./$(EXECUTABLE)

tarball:
	-rm -f $(EXECUTABLE) *.o 
	(cd .. ; tar czf Your_Name_a3.tar.z shell )

# End of Makefile

