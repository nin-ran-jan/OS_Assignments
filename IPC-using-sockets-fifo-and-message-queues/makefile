all: 1S 1R 2S 2R 3S 3R

1S: 1sender.c
	gcc 1sender.c -o 1sender

2S: 2sender.c
	gcc 2sender.c -o 2sender

3S: 3sender.c
	gcc 3sender.c -o 3sender

1R: 1receiver.c
	gcc 1receiver.c -o 1receiver

2R: 2receiver.c
	gcc 2receiver.c -o 2receiver

3R: 3receiver.c
	gcc 3receiver.c -o 3receiver

clean:
	rm 1sender 1receiver 2sender 2receiver 3sender 3receiver

unlink:
	rm mySocket.socket
	
fifoDel:
	rm myFifo
	rm _myFifo
	