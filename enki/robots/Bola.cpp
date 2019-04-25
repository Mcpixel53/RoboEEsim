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


 Bola::Bola(double radio, double maxSpeed, double noiseAmount, Color col = Color(0.0, 0.0, 1.0)):
maxSpeed(maxSpeed),
noiseAmount(noiseAmount),
r(radio),
cmdAngSpeed(0),
cmdSpeed(0),
collisionElasticity(0)
{
	ghost = 1;
	setSpheric(radio,10);
	setColor(col);
	collide = false;
	collXY = 0;
	 dryFrictionCoefficient = 0.25;
	// dryFrictionCoefficient = 2.5;
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
		const double baseFactor = 1 - noiseAmount;
		const double noiseFactor = 2 * noiseAmount;

		const double realSpeed = clamp(
			neutralSpeed * (baseFactor + random.getRange(noiseFactor)),
			-maxSpeed,maxSpeed
		);
		// set non slipping, override speed
		cmdSpeed = realSpeed;// (realLeftSpeed + realRightSpeed) * 0.5;
		cmdAngSpeed = 0;
		//printf("UEHA! %f %f SPEDA:  %f \n ",realSpeed, noiseFactor,speed);

		Robot::controlStep(dt);


	}


		void Bola::applyForces(double dt)
		{
			const Vector cmdVelocity(
				 cmdSpeed * cos(angle),
				 cmdSpeed * sin(angle)
			);
			angSpeed = cmdAngSpeed;
			speed = cmdVelocity;
			// printf("UEHA! %f %f ",angle,speed);
			//Robot::applyForces(dt);
		}

}
