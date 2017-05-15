#pragma once

namespace MyVector
{
	using namespace System;

	public class Vertex
	{	
		public:
			Vertex();
			Vertex(float x, float y, float z);
			// copy const
		//	Vertex(const  Vertex & p);
			Vertex(Vertex * p);

			Vertex  Normalize();
			float  Length();
			Vertex  CrossProduct(Vertex p);
			Vertex  operator + (Vertex p);
			Vertex  operator - (Vertex p);
			float   operator * (Vertex p);
			Vertex  operator * (float f);
			Vertex  operator / (float f);
			Vertex  operator = (Vertex p);
			bool	operator < (Vertex v1);
			
			//setters and getters
			void   setX(float x);
			void   setY(float y);
			void   setZ(float z);
			float  getX();
			float  getY();
			float  getZ();
		private:
			float X;
			float Y;
			float Z;

	};
	Vertex  operator * (float f, Vertex p);
	
}
