client-tmp:game.cpp  server
	g++ game.cpp  client.cpp -o client
server:server.cpp 
	g++ server.cpp -o server
