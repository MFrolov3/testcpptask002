#include <iostream>
using namespace std;

class Vector3D
{
private:
	double X;
	double Y;
	double Z;

public:
	Vector3D() {
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
	}

	Vector3D(double X, double Y, double Z) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	static double Dot(Vector3D a, Vector3D b) {
		return a.GetX() * b.GetX() + a.GetY() * b.GetY() + a.GetZ() * b.GetZ();
	}

	static Vector3D cross(Vector3D a, Vector3D b) {
		double ax = a.GetX();
		double ay = a.GetX();
		double az = a.GetX();
		double bx = a.GetX();
		double by = a.GetX();
		double bz = a.GetX();
		return Vector3D(1, 0, 0) * (ay * bz - az * by) - Vector3D(0, 1, 0) * (ay * bz - az * by) + Vector3D(0, 0, 1) * (ay * bz - az * by);
	}

	double GetX() { return this->X; }
	double GetY() { return this->Y; }
	double GetZ() { return this->Z; }

	void SetX(double X) { this->X = X; }
	void SetY(double Y) { this->Y = Y; }
	void SetZ(double Z) { this->Z = Z; }

	Vector3D operator+(Vector3D v) {
		return Vector3D(this->X + v.GetX(), this->Y+v.GetY(), this->Z+v.GetZ());
	}

	Vector3D operator-(Vector3D v) {
		return Vector3D(this->X - v.GetX(), this->Y - v.GetY(), this->Z - v.GetZ());
	}

	Vector3D operator=(Vector3D& v) {
		this->X = v.GetX();
		this->Y = v.GetY();
		this->Z = v.GetZ();
		return *this;
	}

	bool operator== (Vector3D a)
	{
		return this->X == a.GetX() && this->Y == a.GetY() && this->Z == a.GetZ();
	}

	Vector3D operator*(double val) {
		return Vector3D(this->X * val, this->Y * val, this->Z * val);
	}

	Vector3D operator/(double val) {
		return Vector3D(this->X / val, this->Y / val, this->Z / val);
	}
};

class Segment3D
{
private:
	Vector3D start;
	Vector3D end;
public:
	Vector3D Getstart() {
		return this->start;
	}
	Vector3D Getend() {
		return this->end;
	}
	Segment3D(Vector3D start, Vector3D end) {
		this->start = start;
		this->end = end;
	}
};

Vector3D Intersect(Segment3D a, Segment3D b) //here i used plucker to define coordinates
{
	Vector3D Pd = a.Getend() - a.Getstart();
	Vector3D Pm = Vector3D::cross(a.Getstart(), a.Getend());
	Vector3D Qd = b.Getend() - b.Getstart();
	Vector3D Qm = Vector3D::cross(b.Getstart(), b.Getend());


	if (Vector3D::Dot(Pd, Qm) + Vector3D::Dot(Qd, Pm) > -1e-5
		&& Vector3D::Dot(Pd, Qm) + Vector3D::Dot(Qd, Pm) < 1e5
		&& !(Vector3D::cross(Pd, Qm) == Vector3D(0, 0, 0))) {


		Vector3D N = Vector3D(1, 0, 0);

		Vector3D x = (Qd * (Vector3D::Dot(Pm, N))
			- Pd * (Vector3D::Dot(Qm, N))
			- N * (Vector3D::Dot(Pm, Qd))) / 
			(Vector3D::Dot(Vector3D::cross(Pd, Qd), N));

		return x;
	}
	else {
		throw invalid_argument("no intersection");
	}	
}

int main()
{
	Segment3D pt1 = Segment3D(Vector3D(-6, -6, 0), Vector3D(3, 2.5, 0));
	Segment3D pt2 = Segment3D(Vector3D(-4, 2.5, 3), Vector3D(1.5, -4.5, 5));     //here is example how to run function
	Intersect(pt1, pt2);

	return 0;
}