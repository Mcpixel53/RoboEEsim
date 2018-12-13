#include <enki/PhysicalEngine.h>
//#include <enki/robots/e-puck/EPuck.h>
#include <enki/robots/khepera/Khepera.h>
#include <iostream>

int main(int argc, char *argv[])
{
	// Create the world
	Enki::World world(200, 200);

	// Create a Khepera and position it
	Enki::Khepera *khepera = new Enki::Khepera();
	khepera->pos = Enki::Point(100, 100);
	khepera->leftSpeed = 30;
	khepera->rightSpeed = 20;

	// objects are garbage collected by the world on destruction
	world.addObject(khepera);

	Enki::Polygon p;
	const double amount = 9;
	const double radius = 5;
	const double height = 20;
	for (double a = 0; a < 2*M_PI; a += 2*M_PI/amount)
		p.push_back(Enki::Point(radius * cos(a), radius * sin(a)));
	Enki::PhysicalObject* o = new Enki::PhysicalObject;
	Enki::PhysicalObject::Hull hull(Enki::PhysicalObject::Part(p, height));
	o->setCustomHull(hull, 1);
	o->pos = Enki::Point(100, 100);
	o->setColor(Enki::Color(0.4,0.6,0.8));
	world.addObject(o);

	// Run for some times
	for (unsigned i=0; i<10; i++)
	{
		// step of 50 ms
		world.step(0.05);
			std::cout << "Khepera pos is (" << khepera->pos.x << "," << khepera->pos.y << ")" << std::endl;

	}
}
