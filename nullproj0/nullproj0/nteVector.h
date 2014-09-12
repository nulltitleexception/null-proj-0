#ifndef NTEVECTOR_H
#define NTEVECTOR_H

namespace nte {
	typedef Vector2f vec2;
	class Vector2f {
	public:
		float x, y;
		Vector2f(float, float);
		~Vector2f();
		float dot(Vector2f);
		Vector2f add(Vector2f);
		Vector2f subtract(Vector2f);
		Vector2f mult(Vector2f);
		Vector2f div(Vector2f);
		float sqlen();
		float len();
	};
}

#endif // NTEVECTOR_H