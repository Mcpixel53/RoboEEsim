#include "Bola.h"
#include <cstring>
#include <iostream>
/*! \file DifferentialWheeled.cpp
	\brief Implementation of the features of differential wheeled robots
*/
namespace Enki
{
	template<typename T>
	T clamp(T v, T min, T max)
	{
		if (v < min)
			return min;
		else if (v > max)
			return max;
		else
			return v;
	}


 Bola::Bola(double radio, double maxSpeed, double noiseAmount) :
maxSpeed(maxSpeed),
noiseAmount(noiseAmount),r(radio),collisionElasticity(0){
	this->ghost = 1;
	this->setSpheric(radio,10);
	this->setColor(Color(0.3, 0.0, 0.9));
	this->collide = false;
	this->collXY = 0;
};
	/*DifferentialWheeled::DifferentialWheeled(double distBetweenWheels, double maxSpeed, double noiseAmount) :
		distBetweenWheels(distBetweenWheels),
		maxSpeed(maxSpeed),
		noiseAmount(noiseAmount),
		cmdAngSpeed(0),
		cmdSpeed(0)
	{
		leftSpeed = rightSpeed = 0;
		resetEncoders();
	}

	void DifferentialWheeled::resetEncoders()
	{
		leftEncoder = rightEncoder = 0.0;
		leftOdometry = rightOdometry = 0.0;
	}*/
	int Bola::getWall( float w, float h){//Check agaisnt which wall had a collision
		//printf("w %f e h %f ",w,h);
		//int prim = (this->pos.x >= w-this->r||this->pos.x<=this->r);
		//int sec = (this->pos.y >= h-this->r||this->pos.y<=this->r);
		if(this->pos.x >= w-this->r || this->pos.x <= this->r){
			//BOTH WALLS
			 if (this->pos.y >= h-this->r||this->pos.y <= this->r)
					 this->collXY = 3;
			 else
			 	//ONLY WALLX
					 this->collXY = 1;
			 }
			 // ONLY WALLY
		else if (this->pos.y >= h-this->r||this->pos.y <= this->r)
				this->collXY = 2;

		//		printf("debbug r %d, posX %f, posY %f, & collXY %d \n",this->r,this->pos.x,this->pos.y, this->collXY);
		//printf("x? %d  y? %d",(this->pos.x >= w-this->r || this->pos.x <= this->r),(this->pos.y >= h-this->r||this->pos.y <= this->r));
		return this->collXY; //prim*10+sec
	}


  void Bola::collisionEvent(PhysicalObject *o) {
		if (o==NULL){
			this->collide = true;
			//printf("Ball agaisnt Wall %d collision\n",this->collXY);
		}
		else{
			printf("Sth went wrong, ghost = %d. o ghost: %d",this->ghost,o->ghost);

		}

		Robot::collisionEvent(o);
	}


	void Bola::controlStep(double dt)
	{
		// Call parent
		Robot::controlStep(dt);
	}

	void Bola::applyForces(double dt)
	{
		/*const Vector cmdVelocity(
			cmdSpeed * cos(angle + angSpeed * dt * 0.5),
			cmdSpeed * sin(angle + angSpeed * dt * 0.5)
		);
		angSpeed = cmdAngSpeed;*/
		//speed = maxSpeed;
		Robot::applyForces(dt);
	}

}
