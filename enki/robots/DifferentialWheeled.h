/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2008 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006-2008 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication 
    arising from research using this software are asked to add the 
    following reference:
    Enki - a fast 2D robot simulator
    http://lis.epfl.ch/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __ENKI_DIFFERENTIAL_WHEELED_H
#define __ENKI_DIFFERENTIAL_WHEELED_H

/*!	\file DifferentialWheeled.h
	\brief Header of the features of differential wheeled robots
*/

#include <enki/PhysicalEngine.h>

namespace Enki
{
	class DifferentialWheeled: public Robot
	{
	public:
		//! The thrust produced by wheels on contact point. We use a simple model that always produce the same thrust regardless the resulting speed of the contact point. In mN
		double contactPointThrust;
		
		//! Left speed of the robot
		double leftSpeed;
		//! Reft speed of the robot
		double rightSpeed;
		//! The encoder for left wheel; this is not a real encoder, but rather the physical leftSpeed
		double leftEncoder;
		//! The encoder for right wheel; this is not a real encoder, but rather the physical rightSpeed
		double rightEncoder;
		//! The odometry (accumulation of encoders) for left wheel
		double leftOdometry;
		//! The odometry (accumulation of encoders) for right wheel
		double rightOdometry;
		
	protected:
		//! Save of last position to compute encoders.
		Vector oldPos;
		//! Save of last angle to compute encoders.
		double oldAngle;
		
		//! Distance between the left and right driving wheels
		double distBetweenWheels;
		//! Maximum speed wheels can provide
		double maxSpeed;
		//! Relative amount of motor noise
		double noiseAmount;
		
	public:
		//! Constructor
		DifferentialWheeled(double distBetweenWheels, double maxSpeed, double noiseAmount);
		
		//! Reset the encoder. Should be called when robot is moved manually. Odometry is cleared too.
		void resetEncoders();
		
		//! Set the real speed of the robot given leftSpeed and rightSpeed. Add noise. Update encoders.
		virtual void step(double dt);
	};
}

#endif
