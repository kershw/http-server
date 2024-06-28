CC=gcc

http: http.c
	$(CC) http.c -o http -lws2_32