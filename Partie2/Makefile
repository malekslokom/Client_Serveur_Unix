CC = gcc
CFLAGS = -Wall
CLI_TARGET = Client
SERV_TARGET = Serveur

all: $(CLI_TARGET) $(SERV_TARGET) $(APP_TARGET)

$(CLI_TARGET):
	$(CC) $(CFLAGS) -o ./obj/$(CLI_TARGET) ./src/$(CLI_TARGET).c

$(SERV_TARGET): 
	$(CC) $(CFLAGS) -o ./obj/$(SERV_TARGET) ./src/$(SERV_TARGET).c

clean:
	rm -f Client Serveur
	rm -f ./obj/*