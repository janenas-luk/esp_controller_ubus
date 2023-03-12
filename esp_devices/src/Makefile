BIN:=esp_devices
SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:.c=.o)
CFLAGS+=-Wall
LDLIBS:=-lserialport -lubus -lblobmsg_json -lubox

.PHONY:all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $^ 

clean: 
	$(RM) $(BIN) $(OBJS)