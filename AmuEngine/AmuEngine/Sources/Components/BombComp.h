#pragma once

static enum KindOfBomb
{
	Default,
	Poison,
	Magma,
	Ice
};

class BombComp
{
private:
	//after carry to data
	
	KindOfBomb kindOfBomb = Default;
public:
	BombComp();
	~BombComp();

	static constexpr const char* TypeName = "BombComp";
};