/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2006 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006 Laboratory of Robotics Systems, EPFL, Lausanne
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

#include "AsebaMarxbot.h"
#include <set>
#include <cassert>

/*!	\file Marxbot.cpp
	\brief Implementation of the aseba-enabled marXbot robot
*/

namespace Enki
{
	static std::set<unsigned> usedPorts;
	
	void AsebaMarxbot::step(double dt)
	{
		
		DifferentialWheeled::step(dt);
	}
	
	void AsebaMarxbot::incomingData(Socket *socket)
	{
		unsigned short len;
		unsigned short source;
		socket->read(&len, 2);
		socket->read(&source, 2);
		std::valarray<unsigned char> buffer(static_cast<size_t>(len) + 2);
		socket->read(&buffer[0], buffer.size());
		// TODO : call Aseba debugger
	}
	
	void AsebaMarxbot::incomingConnection(Socket *socket)
	{
		// do nothing in addition to what is done by NetworkServer
	}
	
	void AsebaMarxbot::connectionClosed(Socket *socket)
	{
		// do nothing in addition to what is done by NetworkServer
	}
}
