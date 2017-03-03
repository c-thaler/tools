TARGET := test
OBJ := \
	main.o \

CFLAGS += -g3 -fPIC

$(TARGET) : $(OBJ) ./shared/libshared.so
	$(CC) -o $@ -L./shared -lpthread $(OBJ) -lshared

./shared/libshared.so :
	make -C ./shared

.PHONY:
all : $(TARGET)

.PHONY:
clean :
	rm $(OBJ) $(TARGET)
