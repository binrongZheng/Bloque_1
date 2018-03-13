#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <list>

using namespace std;
using namespace sf;

// Create a list to store the future clients
list<TcpSocket*> clients;
void ServerManager();
void SendAllPlayers(string msg, TcpSocket* clientToExclude);


int main()
{
	ServerManager();	
	
	return 0;
}

void ServerManager()
{
	bool running = true;
	// Create a socket to listen to new connections
	TcpListener listener;
	Socket::Status status = listener.listen(5000);
	if (status != Socket::Done)
	{
		cout << "Error al abrir listener\n";
		exit(0);
	}
	else
		cout << "Port ok" << endl;

	// Create a selector
	SocketSelector selector;
	// Add the listener to the selector
	selector.add(listener);

	//Define the number of players you want
	int maxPlayers = 1;

	// Endless loop that waits for new connections
	while (running)
	{
		// Make the selector wait for data on any socket
		if (selector.wait())
		{
			// Test the listener
			if (selector.isReady(listener))
			{
				// The listener is ready: there is a pending connection
				TcpSocket* client = new TcpSocket;
				if (listener.accept(*client) == Socket::Done)
				{
					// Add the new client to the clients list
					std::cout << "Llega el cliente con puerto: " << client->getRemotePort() << std::endl;
					clients.push_back(client);
					// Add the new client to the selector so that we will be notified when he sends something
					selector.add(*client);

					//Avisem a tots els clients que hi ha una nova connexio
					SendAllPlayers("New client connected!", client);
					string name = "c "+ std::to_string( clients.size());
					client->send(name.c_str(),name.length());
					//Si tots els jugadors ja estan conectats avisem
					if (clients.size() == maxPlayers) {
						cout << "Todos los jugadores estan conectados!" << endl;
						SendAllPlayers("All players are connected", NULL);
					}
					else {
						SendAllPlayers("Waiting for players...", NULL);
					}

				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					cout << "Error al recoger conexion nueva\n";
					delete client;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				list<TcpSocket*>::iterator it = clients.begin();				

				while (it != clients.end())
				{
					bool shouldErase = false;
					TcpSocket& client = **it;
					if (selector.isReady(client))
					{
						// The client has sent some data, we can receive it
						//Packet packet;
						char buffer[500];
						size_t received;
						status = client.receive(buffer, sizeof(buffer), received);						
						if (status == Socket::Done && clients.size() == maxPlayers) //si estan tots els jugadors ja podem començar a rebre i enviar missatges.
																					//Pero ho posem aqui i a dalt pq igualment volem comprovar desconnexions
						{
							buffer[received] = '\0';
							string strRec = buffer;
							//packet >> strRec;
							cout << "He recibido '" << strRec << "' del puerto " << client.getRemotePort() << endl;
							SendAllPlayers(strRec, NULL);
						}
						else if (status == Socket::Disconnected)
						{
							selector.remove(client);
							shouldErase = true;
							cout << "Elimino el socket con puerto : " << client.getRemotePort() << " que se ha desconectado" << endl;
							SendAllPlayers("A client disconnected", &client);
						}
						else
						{
							if (clients.size() == maxPlayers) //pq sino ens imprimeix error i simplement es que encara no volem rebre missatges
								cout << "Error al recibir de " << client.getRemotePort() << endl;
						}
					}
					//Si volem borrar elements de la llista hem de controlar que no ens sortim fora amb l'iterador
					if (shouldErase)
						it = clients.erase(it);
					else
						++it;
				}
			}
		}
	}

}

void SendAllPlayers(string msg,TcpSocket* clientToExclude) {
	for (list<TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		TcpSocket& clientRef = **it;
		if (&clientRef != clientToExclude)
			clientRef.send(msg.c_str(), msg.length());
	}
}