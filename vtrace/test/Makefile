TARGET := test
OBJ := \
	main.o \
	../src/cvtrace.o

CFLAGS += -finstrument-functions -g3

$(TARGET) : $(OBJ)
	$(CC) -o $@ -lpthread $^

.PHONY:
clean :
	rm $(OBJ) $(TARGET)
