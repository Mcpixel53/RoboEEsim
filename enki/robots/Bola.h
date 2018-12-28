
#include <enki/PhysicalEngine.h>
//#include <enki/robots/DifferentialWheeled.h>
namespace Enki
{
	class Bola: public virtual Robot
	{
	protected:
	//! Maximum speed wheels can provide
		double maxSpeed;
		//! Relative amount of motor noise
		double noiseAmount;

	private:
		//! Resulting angular speed from wheels
		double cmdAngSpeed;
		//! Resulting tangent speed from wheels
		double cmdSpeed;


	public:
		//! Constructor
		Bola(double radio, double maxSpeed, double noiseAmount);

		//public overcharge of radius
		int r;

		//speed
		double neutralSpeed;

		double leftSpeed;
		//! Reft speed of the robot
		double rightSpeed;
		//! collides
		bool collide;
		//agaisnt which wall collided?
		int  collXY; 		//TODO turn into Enum

		bool collisionElasticity;
		//! Collider, o == NULL if collides with walls
		void collisionEvent(PhysicalObject *o);
		int getWall( float w, float h);

		//! Reset the encoder. Should be called when robot is moved manually. Odometry is cleared too.

		//! Set the real speed of the robot given leftSpeed and rightSpeed. Add noise. Update encoders.
		virtual void controlStep(double dt);
		//! Consider that robot wheels have immobile contact points with ground, and override speeds. This kills three objects dynamics, but is good enough for the type of simulation Enki covers (and the correct solution is immensely more complex)
		virtual void applyForces(double dt);
	};
}
