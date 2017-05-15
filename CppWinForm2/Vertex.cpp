#pragma once
#include "Vertex.h"

namespace MyVector
{
	using namespace System;

		Vertex::Vertex(){
			this->X = 0.00;
			this->Y = 0.00;
			this->Z = 0.00;
		}

		Vertex::Vertex(float x, float y, float z)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}
	
		Vertex::Vertex(Vertex * p)
		{
			X = p->getX();
			Y = p->getY();
			Z = p->getZ();
		}
		Vertex  Vertex::Normalize()
		{
			float length = (float)Math::Sqrt(X*X + Y*Y + Z*Z);
			X /= length;
			Y /= length;
			Z /= length;
			return *this;
		}

		float  Vertex::Length()
		{
			return (float)Math::Sqrt(X*X + Y*Y + Z*Z);;
		}

		Vertex  Vertex::CrossProduct(Vertex p)
		{
			return  Vertex(
				Y*p.Z - Z*p.Y,
				Z*p.X - X*p.Z,
				X*p.Y - Y*p.X);
		}

		Vertex  Vertex::operator + (Vertex p)
		{
			return Vertex(X + p.X, Y + p.Y, Z + p.Z);
		}

		Vertex  Vertex::operator - (Vertex p)
		{
			return Vertex(X - p.X, Y - p.Y, Z - p.Z);
		}

		float  Vertex::operator * (Vertex p)
		{
			return X * p.X + Y * p.Y + Z * p.Z;
		}

		Vertex  Vertex::operator * (float f)
		{
			return Vertex(f*X, f*Y, f*Z);
		}

		Vertex  Vertex::operator / (float f)
		{
			return  Vertex(X / f, Y / f, Z / f);
		}

		Vertex  Vertex::operator=(Vertex p)
		{
			this->X = p.getX();
			this->Y = p.getY();
			this->Z = p.getZ();
			return *this;
		}

		bool Vertex::operator <	(Vertex v1)
		{
			return  (this->getX() - v1.getX()) > 0;
		}

		Vertex  operator * (float f, Vertex p)
		{
			return Vertex(f * p.getX(), f * p.getY(), f * p.getZ());
		}
		//// getters-setters////		
		void Vertex::setX(float x)
		{
			this->X = x;
		}

		void Vertex::setY(float y)
		{
			this->Y = y;
		}

		void Vertex::setZ(float z)
		{
			this->Z = z;
		}

		float  Vertex::getX()
		{
			return X;
		}

		float  Vertex::getY()
		{
			return this->Y;
		}

		float  Vertex::getZ()
		{
			return this->Z;
		}
}
