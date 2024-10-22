#pragma once

namespace BOMB
{
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
		GameObject* owner;
		BombComp(GameObject* _owner);
		~BombComp();

		static constexpr const char* TypeName = "BombComp";
	};
}
