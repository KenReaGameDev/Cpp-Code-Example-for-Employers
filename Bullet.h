#ifndef BULLET_H
#define BULLET_H

#include "Structs.h"
#include "Object.h"
#include "BoxCollider.h"

// Screen Space Only
class Bullet : public Object {

public:

	Bullet(Structs::L_POINT pos, Structs::L_POINT vel, int size, bool enabled);
	Bullet();
	~Bullet();

	void Enable(Structs::L_POINT pos, Structs::L_POINT vel);

	void Update();
	const void Draw();

private:

	int m_Size;

protected:


};

#endif // #ifndef BULLET_H