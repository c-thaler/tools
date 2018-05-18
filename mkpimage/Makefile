TARGET=mkpimage

$(TARGET) : mkpimage.o
	$(CC) -o $@ $^

.PHONY:
all : $(TARGET)

.PHONY:
clean : 
	rm -f *.o $(TARGET)
