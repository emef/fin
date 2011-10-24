OBJS = fin.o classes.o money.o
CC = g++
LIBRARIES = -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -lboost_system
CFLAGS = -Wall -g

.SUFFIXES: .cxx
.PHONY: clean

.cxx.o:
	$(CC) $(CFLAGS) -c -o $@ $<

fin: $(OBJS)
	$(CC) $(OBJS) $(LIBRARIES) -o $@

clean:
	@rm *.o *~ fin > /dev/null

#dependencies
$(OBJS): classes.h global.h money.h
