#include "GameEngine.h"


using namespace std;
using namespace sf;


sf::Socket::Status VSend(sf::TcpSocket* sock, string msg);

void receiveText(TcpSocket* sock, vector<string>* msgArray);

string name;

GameEngine::GameEngine()
{	
}

GameEngine::~GameEngine()
{
}

void GameEngine::start() {

	cout << "Client" << endl;
	//PER PROVAR QUE FUNCION
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;

	char connectionType;
	std::string intro = "Connected to: Servidor";

	std::vector<std::string> aMensajes;
	aMensajes.push_back(intro);

	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow gameWindow;
	sf::RenderWindow chatWindow;


	sf::Font font;

	centerCard = pocker.getSprite(rand() % 39);
	centerCard.setPosition(380,280);

	playerPocker.push_back(pocker.getSprite(10));playerPocker.push_back(pocker.getSprite(1));playerPocker.push_back(pocker.getSprite(20));
	playerPocker.push_back(pocker.getSprite(30));playerPocker.push_back(pocker.getSprite(39));
	
	playerPockerPos.push_back({ 280,450 }); playerPockerPos.push_back({ 330,450 }); playerPockerPos.push_back({ 380,450 }); playerPockerPos.push_back({ 430,450 }); playerPockerPos.push_back({ 480,450 });

	for (int i = 0; i < 5; i++) {
		playerPocker[i].setPosition(playerPockerPos[i].x,playerPockerPos[i].y);
	}

	otherPlayerPockerPos.push_back({ 280,100 });
	otherPlayerPockerPos.push_back({ 330,100 });
	otherPlayerPockerPos.push_back({ 380,100 });
	otherPlayerPockerPos.push_back({ 430,100 });
	otherPlayerPockerPos.push_back({ 480,100 });

	otherPlayerPockerPos.push_back({ 700,180 }); 
	otherPlayerPockerPos.push_back({ 700,230 }); 
	otherPlayerPockerPos.push_back({ 700,280 }); 
	otherPlayerPockerPos.push_back({ 700,330 }); 
	otherPlayerPockerPos.push_back({ 700,380 });
	
	otherPlayerPockerPos.push_back({ 170,180 });
	otherPlayerPockerPos.push_back({ 170,230 });
	otherPlayerPockerPos.push_back({ 170,280 });
	otherPlayerPockerPos.push_back({ 170,330 });
	otherPlayerPockerPos.push_back({ 170,380 });

	for (int i = 0; i < 15; i++) {
		otherPlayerPocker.push_back(pocker.getSprite(40));
		otherPlayerPocker[i].setPosition(otherPlayerPockerPos[i].x, otherPlayerPockerPos[i].y);
		if(i>4)
		otherPlayerPocker[i].setRotation(90);
	}

	if (!font.loadFromFile("courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	sf::String mensaje = ">";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);


	sf::Text text(mensaje, font, 14);


	text.setFillColor(sf::Color(0, 160, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);
	
	Socket::Status status = socket.connect(ip, 5000);
	socket.setBlocking(false);


	if (status != Socket::Done) {
		cout << "Error de connexi¨® al servidor\n";
		exit(0);
	}
	else if (status == Socket::Done) {
		cout << "Ok\n";

		char buffer[100];
		size_t nameSize;
		while (name == "")
		{

			socket.receive(buffer, sizeof(buffer), nameSize);
			buffer[nameSize] = '\0';
			name = buffer;

		}
		gameWindow.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Game");
		chatWindow.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat");
	}
	while (gameWindow.isOpen())
	{		
		sf::Event evento;
		
		//GAMEPLAY
		while (gameWindow.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::Closed:
				gameWindow.close();
				chatWindow.close();
				break;				
			}
		}		
		for (int i = 0; i < 5; i++) {
			gameWindow.draw(playerPocker[i]);
		}
		for (int i = 0; i < 15; i++) {
			gameWindow.draw(otherPlayerPocker[i]);
		}
		gameWindow.draw(centerCard);
		gameWindow.display();
		gameWindow.clear();

		//CHAT
		if (aMensajes.size() >= 25) aMensajes.clear();
		
		while (chatWindow.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::Closed:
				chatWindow.close();
				break;
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					chatWindow.close();
				else if (evento.key.code == sf::Keyboard::Return)
				{

					//	SEND
					//Enviem al altre					
					if (VSend(&socket, mensaje) != Socket::Status::Done) {
						aMensajes.push_back("there is no connection");
					}

					if (aMensajes.size() > 25)
					{
						aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
					}
					mensaje = ">";
				}
				break;
			case sf::Event::TextEntered:
				if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
					mensaje += (char)evento.text.unicode;
				else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
					mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
				break;
			}
		}
		chatWindow.draw(separator);
		receiveText(&socket, &aMensajes);

		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			chatWindow.draw(chattingText);
		}
		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		chatWindow.draw(text);

		chatWindow.display();
		chatWindow.clear();
	}
	

	socket.disconnect();
}

sf::Socket::Status VSend(sf::TcpSocket* sock, string msg) {

	sf::Socket::Status status;
	string toSend = name + msg;
	size_t bytesSend;

	do
	{
		status = sock->send(toSend.c_str(), toSend.length() + 1, bytesSend);
		if (status == sf::Socket::Partial) {
			toSend = toSend.substr(bytesSend + 1, toSend.length() - bytesSend);
		}
	} while (status == sf::Socket::Partial);
	return status;
}
void receiveText(sf::TcpSocket* sock, std::vector<std::string>* aMensajes) {
	size_t received;
	sf::Socket::Status status;
	string tmp;
	char buffer[500];

	status = sock->receive(buffer, sizeof(buffer), received);

	switch (status)
	{
	case sf::Socket::Done:
		buffer[received] = '\0';
		tmp = buffer;
		aMensajes->push_back(tmp);
		break;

	case sf::Socket::Partial:
		break;
	case sf::Socket::Disconnected:
		tmp = "Disconnected";
		aMensajes->push_back(tmp);
		exit(0);
		break;
	case sf::Socket::Error:
		tmp = "Error to receive";
		aMensajes->push_back(tmp);
		break;
	default:
		break;
	}

}