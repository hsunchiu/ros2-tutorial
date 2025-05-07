#pragma once

namespace polygon_base {
	class RegularPolygon{
		public:
			virtual void initialize(double side_length) = 0;
			virtual double area() = 0;
			virtual ~RegularPolygon() = default;	

protected:
			RegularPolygon() = default;
	};

} // polygon_base
