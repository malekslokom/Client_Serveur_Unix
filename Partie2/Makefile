CC = gcc
CFLAGS = -Wall
CLI_TARGET = Client
SERV_TARGET = Serveur
APP_TARGET = clientServeur

all: $(CLI_TARGET) $(SERV_TARGET) $(APP_TARGET)

$(CLI_TARGET):
	$(CC) $(CFLAGS) -o ./obj/$(CLI_TARGET) ./src/$(CLI_TARGET).c

$(SERV_TARGET): 
	$(CC) $(CFLAGS) -o ./obj/$(SERV_TARGET) ./src/$(SERV_TARGET).c

$(APP_TARGET): 
	$(CC) $(CFLAGS) -o ./obj/$(APP_TARGET) ./src/$(APP_TARGET).c

clean:
	rm -f Client Serveur
	rm -f ./obj/*