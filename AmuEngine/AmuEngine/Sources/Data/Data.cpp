#include "Data.h"
#include <iostream>

void Data::PlayerData::PrintPlayerData(Data::PlayerData data)
{
	std::cout << "Player BoubCount : "				<< data.bombCount				<< std::endl;
	std::cout << "Player ExplosionRadius : "		<< data.explosionRadius			<< std::endl;
	std::cout << "Player MoveSpeed : "				<< data.moveSpeed				<< std::endl;
	std::cout << "Player HP : "						<< data.hp						<< std::endl;
	std::cout << "Player CurrentBombType : "		<< data.currentBombType			<< std::endl;
	std::cout << "Player ItemVitalizationFlag : "	<< data.itemVitalizationFlag	<< std::endl;
	PrintSeparator();
}

void Data::PrintSeparator()
{
	std::cout << "---------------------------" << std::endl;
}
