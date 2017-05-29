/* En-tête du fichier */
///================== */
/* Fichier:			tron.cpp
// Auteur:			Olivier Lemay Dostie & Francis Forest
// Date création:	28/05/2017
// Description:		Projet en SFML basé sur le jeu de TRON.*/

/* Directives au pré-processeur */
///============================ */
#include <iomanip>				
#include <locale>				
#include <string>				
#include <vector>				
#include <cstdlib>				
using namespace std;
#include <SFML/Graphics.hpp>	
#include <SFML/Audio.hpp>		
#include "saisieSFML.h"			
#include "bolide.h"				
#include "trace.h"				
#include "salle.h"				
using namespace sf;


/* Prototypes des fonctions */
///======================== */

double toRads(double deg);
void move(CircleShape& head, double angle);
bool collisionQueue(CircleShape head, vector<CircleShape> queue);
bool siTrou();


/* Programme principal */
///=================== */
int main()
{
	srand(NULL);

	RenderWindow window(VideoMode(1280, 600), "Vroooom!!!");					//Fenêtre
	window.setFramerateLimit(60);												//Limite le nombre d'images par secondes

	CircleShape head;

	vector<CircleShape> queue;
	Clock tempsJeu;
	Time temps;
	bool jouer = true;
	double angle = 90;
	bool hole = false;

	Event event;


	head.setFillColor(Color::Blue);
	head.setRadius(2);
	head.setOrigin(2, 2);
	head.setPosition(Vector2f(300, 300));


	while (jouer)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				jouer = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			angle += 5;
		}


		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			angle -= 5;
		}

		move(head, angle);

		if (collisionQueue(head, queue))
		{
			jouer = false;
		}


		if (!hole)
		{
			if (siTrou())
			{
				hole = true;
				tempsJeu.restart();
			}
			else
			{
				CircleShape queueTest;
				queueTest.setFillColor(Color::Blue);
				queueTest.setRadius(2);
				queueTest.setOrigin(2, 2);
				queueTest.setPosition(head.getPosition());

				queue.push_back(queueTest);
			}

		}
		else
		{

			temps = tempsJeu.getElapsedTime();
			if (temps.asSeconds() > 0.1)
			{
				hole = false;

			}
		}

		window.clear(Color(0, 0, 0));

		window.draw(head);

		for (CircleShape& ele : queue)
		{
			window.draw(ele);
		}

		window.display();

	}
}

void move(CircleShape& head, double angle)
{
	head.move(2 * cos(toRads(angle)), 2 * sin(toRads(angle)));
}

double toRads(double deg)
{
	double pi = atan(1) * 4;

	return deg * pi / 180;
}

bool collisionQueue(CircleShape head, vector<CircleShape> queue)
{

	for (CircleShape ele : queue)
	{
		double distX;
		double distY;
		double dist;

		distX = head.getPosition().x - ele.getPosition().x;
		distY = head.getPosition().y - ele.getPosition().y;
		dist = sqrt(distX * distX + distY * distY);

		if (dist < ele.getRadius() - 0.05)
		{
			return true;
		}
	}

	return false;
}

bool siTrou()
{
	if ((rand() % 100 + 1) < 2)
	{
		return true;
	}

	return false;
}
