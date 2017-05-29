/* En-tête du fichier */
///================== */
/* Fichier:			vehicle.h
// Auteur:			Olivier Lemay Dostie & Francis Forest
// Date création:	28/05/2017
// Description:		Projet en SFML basé sur le jeu de TRON.*/

/* Directives au pré-processeur */
///============================ */
#pragma once
using namespace std;
#include <SFML/Graphics.hpp>	
using namespace sf;

const float STARTMARGIN = 45;
const Vector2f BODYSIZE = Vector2f(3, 12);
const Vector2f WHEELSIZE = Vector2f(4, 6);
// 1280 par 720

struct carShape
{
private:
	const float BACKWHEEL = BODYSIZE.y / 2 + (BODYSIZE.y - WHEELSIZE.y * 2) / 2;
public:
	RectangleShape body;
	RectangleShape wheels[2];

	carShape() 
	{
		setSize();
	}
	carShape(Color paint, Color tire)
	{
		body.setFillColor(paint);
		wheels[0].setFillColor(tire);
		setSize();
	}
	void setSize()
	{
		body.setSize(BODYSIZE);
		body.setPosition(Vector2f(1,0));
		body.setOrigin(Vector2f(BODYSIZE.x / 2, BODYSIZE.y / 2));
		wheels[0].setSize(WHEELSIZE);
		wheels[1] = wheels[0];

		wheels[0].setPosition(Vector2f(0, 0));
		wheels[1].setPosition(Vector2f(0, BACKWHEEL));
		wheels[0].setOrigin(Vector2f(WHEELSIZE.x / 2, WHEELSIZE.y / 2));
	}
	void setPosition(Vector2f position)
	{
		body.setPosition(position);
		wheels[0].setPosition(position);
		wheels[1].setPosition(position);
	}
	void move(Vector2f translation)
	{
		body.move(translation);
		wheels[0].move(translation);
		wheels[1].move(translation);
	}
	void rotate(float angle)
	{
		body.rotate(angle);
		wheels[0].rotate(angle);
		wheels[1].rotate(angle);
	}
};

class vehicle
{
public:
	RenderWindow * window;
	int noPlayer = 0;
	float angle = 0;
	Vector2f position = Vector2f(STARTMARGIN, STARTMARGIN);
	carShape car;

	vehicle();
	~vehicle();

private:

};

vehicle::vehicle()
{

}

vehicle::~vehicle()
{
}
