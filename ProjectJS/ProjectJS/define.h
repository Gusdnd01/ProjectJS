#pragma once

//about singleton
#define SINGLE(type)			\
private:						\
	type() {}					\
	~type(){}					\
public:							\
	static type* GetInst()		\
	{							\
		static type m_pInst;	\
		return &m_pInst;		\
	}
#define GETINST(type) type::GetInst()

//about window
#define WINDOW_CLASS_NAME L"Gamep"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//about draw
#define RECT_RENDER(posx, posy, scalex, scaley, hdc) Rectangle(hdc, posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2)
#define Ellipse_RENDER(posx, posy, scalex, scaley, hdc) Ellipse(hdc, posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2)
#define RECT_MAKE(posx, posy, scalex, scaley) {posx-scalex/2, posy-scaley/2, posx+scalex/2, posy+scaley/2}

//about time
#define fDT TimeManager::GetInst()->GetDT()

//about key
#define KEY_CHECK(key, state) KeyManager::GetInst()->GetKey(key)==state
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_UP(key) KEY_CHECK(key, KEY_STATE::UP)
#define KEY_DOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define KEY_PRESS(key) KEY_CHECK(key, KEY_STATE::PRESS)

//about time
#define PI M_PI