#pragma once

class Object;
enum class STATE {
	JUMP,
	MOVE,
	HURT,
	DIE,
	END = 10
};

class FSM
{
public:
	virtual void StateChanged(STATE _type) abstract;

public:
	void IdleState();
	void MoveState(bool left);
	void JumpState();

private:
	Object* p_owner;
};

