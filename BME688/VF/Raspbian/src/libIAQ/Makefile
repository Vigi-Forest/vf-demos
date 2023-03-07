CC=gcc

CFLAGS= -O2

PROG= libiaq_test

LIBIAQ= libIAQ.a

OBJS= iaq_eco2.o

$(PROG): $(LIBIAQ)
	$(CC) -o $(PROG) $(PROG).c $(OBJS) -L. -lIAQ -lm

$(LIBIAQ): $(OBJS)
	$(AR) rv $(LIBIAQ) $(OBJS)

clean:
	rm -f  $(OBJS) $(PROG) $(LIBIAQ) *~ 
