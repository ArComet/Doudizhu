client-tmp:game.cpp net.cpp server
	g++ game.cpp net.cpp client-tmp.c -o client
server:server.cpp 
	g++ server.cpp -o server
