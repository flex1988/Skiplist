FILES=skiplist_test.c skiplist.h skiplist.c

all:$(FILES)
	$(CC) $(FILES)

clean:
	rm -rf *.dSYM
	rm skiplist.h.gch
	rm a.out
