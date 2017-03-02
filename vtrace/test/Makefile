TARGET := test
STARGET := libshared.so
OBJ := \
	main.o \
	../src/cvtrace.o

SOBJ := \
	shared.o

CFLAGS += -finstrument-functions -g3 -fPIC

$(TARGET) : $(OBJ) $(STARGET)
	$(CC) -o $@ -L./ -lpthread $(OBJ) -lshared

$(STARGET) : $(SOBJ)
	$(CC) --shared -o $@ $^

.PHONY:
all : $(TARGET)

.PHONY:
clean :
	rm $(OBJ)i $(SOBJ) $(TARGET) $(STARGET)
