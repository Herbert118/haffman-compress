OUT = main.out
CC = g++
ODIR = o
SDIR = cpp
INC = -Iinc

_OBJS = main.o encoding.o fileUtil.o huffmanTree.o decoding.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	g++ -o $(OUT) $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)
