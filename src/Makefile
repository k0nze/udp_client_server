all: client server

client: FORCE
	cd client && make all

server: FORCE
	cd server && make all

FORCE: ;

.PHONY clean:
	cd client && make clean
	cd server && make clean
