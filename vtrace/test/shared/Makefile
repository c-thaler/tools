TARGET := libshared.so
OBJ := \
	shared.o \
	../../src/cvtrace.o

CFLAGS += -finstrument-functions -g3 -fPIC

$(TARGET) : $(OBJ) $(STARGET)
	$(CC) --shared -o $@ -L./ -lpthread $(OBJ)

.PHONY:
all : $(TARGET)

.PHONY:
clean :
	rm $(OBJ) $(TARGET)
