#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>

const int maxEnergy = 50;
const int specialAttackEnergy = 50;

const int baseEnergyRegen = 6;
const int dodgeEnergyRegen = 3;
const int rechargeEnergyRegen = 24;

const int playerHealth = 100;
const int enemyHealth = 100;
const int maxHealth = 100;

const int chanceMax = 100;
const int attackDamageMax = 10;
const int specialDamageMax = 15;

//hit chances for every combination 
const int specialHitThreshold = 50;
const int specialRechargeThreshold = 55;
const int specialDodgeThreshold = 35;
const int hitThreshold = 80;
const int hitRechargeThreshold = 88;
const int hitDodgeThreshold = 56;

//enemy stats needed to use heal
const int enemyHealHealthThreshold = 10;
const int enemyHealEnergyThreshold = 40;

//enemy stats needed to use recharge
const int enemyRechargeEnergyThreshold = 5;

//enemy energy needed to use special
const int enemySpecialEnergyThreshold = 50;

//enemy health needed to use dodge
const int enemyDodgeHealthThreshold = 10;



int main()
{
	int playerDamage;
	int enemyDamage;

	int playerHealth = 100;
	int enemyHealth = 100;

	int playerEnergy = maxEnergy;
	int enemyEnergy = maxEnergy;
	int playerEnergyRegen = baseEnergyRegen;
	int enemyEnergyRegen = baseEnergyRegen;

	int playerScore = 0;
	int enemyScore = 0;

	//random number for hit chance
	int hitChance;

	//random based on time
	srand(time(NULL));

	int playerHeal;
	int playerHealMax = (playerEnergy * 0.5);
	int enemyHeal;
	int enemyHealMax = (enemyEnergy * 0.5);

	std::string playerAction;
	std::string enemyAction;

	//Does the player want to play again?
	//starts as yes so loop works
	std::string playerRestart = "yes";

	std::cout << "Welcome to Console Wars!" << "\n\n";
	std::cout << "Type 'start' to play or 'info' to view the rules before the game begins..." << "\n\n";

	//testing random gen remove this below

	//gives option to look at the instructions or start
	std::string menuChoice;
	std::cin >> menuChoice;
	std::cout << std::endl;

	while (menuChoice != "start" && menuChoice != "info") {
		std::cout << "error, please enter valid input..." << std::endl;
		std::cin >> menuChoice;
		std::cout << "\n\n";
	}
	
	//instructions page game starts straight after
	if (menuChoice == "info") {
		std::cout << "when the game starts the objective is to lower the enemie's health to 0." << std::endl;
		std::cout << "you'll take turns picking from a set of moves where each will cause unique effects" << std::endl;
		std::cout << "below is a brief explanation of each move" << std::endl;
		std::cout << "attack: a standard strike with a 80% hit chance which deals 1-10 damage." << std::endl;
		std::cout << "special: consumes 50 points of energy to have a 50% hit chance dealing 5-20 damage" << std::endl;
		std::cout << "recharge: do nothing, recharging energy at 4x speed but give the enemy +10% hit chance" << std::endl;
		std::cout << "dodge: attempt to dodge decreasing enemies hit chance by 30% but decreases energy recharge by 50%" << std::endl;
		std::cout << "heal: consume 50% of energy into health points and pick another ability (you cannot heal twice)" << "\n\n";
		std::cout << "PLEASE KEEP ALL ANSWERS IN LOWERCASE! Good Luck!" << "\n\n";
	}

	while (playerRestart == "yes") {

		//resetting stats for new game
		enemyHealth = maxHealth;
		playerHealth = maxHealth;
		enemyEnergy = maxEnergy;
		playerEnergy = maxEnergy;

		while (enemyHealth > 0 && playerHealth > 0) {

			//display total health for both parties, underscores and endlines are for visual effects
			std::cout << "_____________________________________________________________________________" << "\n\n\n";
			std::cout << "Player Creature HP: " << playerHealth << " / Player Creature EP: " << playerEnergy << std::endl;
			std::cout << "Enemy Creature HP: " << enemyHealth << " / Enemy Creature EP:  " << enemyEnergy << "\n\n";
			std::cout << "_____________________________________________________________________________" << "\n\n";

			std::cout << "Pick a move..." << "\n\n";
			std::cin >> playerAction;
			std::cout << std::endl;

			//input validation for move selection
			while (playerAction != "attack" && playerAction != "special" && playerAction != "recharge" && playerAction != "dodge" && playerAction != "heal") {
				std::cout << "Please enter valid input... (attack, special, recharge, dodge, heal)" << "\n\n";
				std::cin >> playerAction;
				std::cout << "\n\n";
			}

			//player picks a move for his turn
			//player heal - removes half of energy to restore a random value of that half to prevent spam healing
			if (playerAction == "heal") {
				playerHeal = (rand() % playerHealMax + 1);
				playerHealth += playerHeal;
				playerEnergy -= playerHealMax;

				if (playerHealth > maxHealth) {
					playerHealth = maxHealth;
				}

				std::cout << "You cast heal, restoring " << playerHeal << " HP," << " you now have " << playerHealth << " HP." << "\n\n";
				std::cout << "Pick a second move." << "\n\n";
				std::cin >> playerAction;
				std::cout << std::endl;

				while (playerAction == "heal")
				{
					std::cout << "You cannot heal twice in one round, pick a different move." << "\n\n";
					std::cin >> playerAction;
					std::cout << std::endl;
				}

				while (playerAction != "attack" && playerAction != "special" && playerAction != "recharge" && playerAction != "dodge") {
					std::cout << "Please enter valid input... (attack, special, recharge, dodge)" << std::endl;
					std::cin >> playerAction;
					std::cout << "\n\n";
				}
				
			}

			//player attack
			if (playerAction == "attack") {
				std::cout << "You attempt to attack the enemy" << std::endl;
				hitChance = (rand() % chanceMax + 1);

				if (hitChance <= hitDodgeThreshold && enemyAction == "dodge") {
					std::cout << "You successfully hit the enemy!" << "\n\n";
					playerDamage = (rand() % attackDamageMax + 1);
					enemyHealth -= playerDamage;
				}

				else if (enemyAction == "recharge" && hitChance <= hitRechargeThreshold) {
					std::cout << "You successfully hit the enemy whilst their defences are lowered!" << "\n\n";
					playerDamage = (rand() % attackDamageMax + 1);
					enemyHealth -= playerDamage;
				}

				else if (hitChance <= hitThreshold) {
					std::cout << "You successfully hit the enemy!" << "\n\n";
					playerDamage = (rand() % attackDamageMax + 1);
					enemyHealth -= playerDamage;
				}

				else {
					std::cout << "you missed!" << "\n\n";
				}

			}

			//player special, while loop to check if player have the required energy.
			while (playerAction == "special" && playerEnergy < 50)
			{
				std::cout << "Not enough EP, choose a different move." << "\n\n";
				std::cin >> playerAction;
				std::cout << std::endl;
			}

			if (playerAction == "special") {
				std::cout << "You attempt to use a special attack on the enemy" << "\n\n";
				hitChance = (rand() % chanceMax + 1);
				playerEnergy -= specialAttackEnergy;

				if (enemyAction == "dodge" && hitChance <= specialDodgeThreshold) {
					std::cout << "You successfully hit the enemy despite him trying to dodge!" << "\n\n";
					playerDamage = (rand() % specialDamageMax + 6);
					enemyHealth -= playerDamage;
				}

				else if (enemyAction == "recharge" && hitChance <= specialRechargeThreshold) {
					std::cout << "You successfully hit the enemy whilst their defences are lowered!" << "\n\n";
					playerDamage = (rand() % specialDamageMax + 6);
					enemyHealth -= playerDamage;
				}

				else if (hitChance <= specialHitThreshold) {
					std::cout << "You successfully hit the enemy!" << "\n\n";
					playerDamage = (rand() % specialDamageMax + 6);
					enemyHealth -= playerDamage;
				}

				else {
					std::cout << "you missed!" << "\n\n";
				}

			}

			//player recharge
			if (playerAction == "recharge") {
				std::cout << "You cast recharge! Your defences are lowered but you regenerate more energy!" << "\n\n";
				playerEnergyRegen = rechargeEnergyRegen;
			}

			//player dodge
			if (playerAction == "dodge") {
				std::cout << "You cast dodge. your energy regeneration is lowered in the attempt to evade the enemies next attack..." << "\n\n";
				playerEnergyRegen = dodgeEnergyRegen;
			}

			//quit option
			if (playerAction == "quit" || playerAction == "exit") {
				break;
			}

			//player energy regeneration and resetting its value to normal
			playerEnergy += playerEnergyRegen;
			playerEnergyRegen = baseEnergyRegen;

			if (playerEnergy >= maxEnergy) {
				playerEnergy = maxEnergy;
			}

			//enemies turn

			//Heal - removes half of energy to restore a random value of that half to prevent spam healing
			if (enemyHealth <= enemyHealHealthThreshold && enemyEnergy >= enemyHealEnergyThreshold) {
				enemyHeal = (rand() % enemyHealMax + 1);
				enemyHealth += enemyHeal;
				enemyEnergy -= enemyHealMax;
				std::cout << "The enemy healed for " << enemyHeal << " hitpoints!" << "\n\n";
			}

			//Recharge
			if (enemyEnergy <= enemyRechargeEnergyThreshold) {
				enemyEnergyRegen = rechargeEnergyRegen;
				std::cout << "The enemy used recharge, gaining extra energy!" << std::endl;
				std::cout << "The enemies defences' are lowered your attack chance is increased" << "\n\n";
				enemyAction = "recharge";
			}

			//Special
			else if (enemyEnergy >= (enemySpecialEnergyThreshold)) {
				std::cout << "The enemy used a special attack" << std::endl;
				hitChance = (rand() % chanceMax + 1);
				enemyAction = "special";
				enemyEnergy -= specialAttackEnergy;

				if (hitChance <= specialDodgeThreshold && playerAction == "dodge") {
					std::cout << "The enemy special attack was successful, despite your attempt to dodge!" << "\n\n";
					//+6 makes min damage 5 on random number 
					enemyDamage = (rand() % specialDamageMax + 6);
					playerHealth -= enemyDamage;
				}

				else if (hitChance <= specialRechargeThreshold && playerAction == "recharge") {
					std::cout << "The enemy special attack was successful whilst your defences were lowered!" << "\n\n";
					enemyDamage = (rand() % specialDamageMax + 6);
					playerHealth -= enemyDamage;
				}

				else if (hitChance <= specialHitThreshold) {
					std::cout << "The enemy special attack was successful!" << "\n\n";
					enemyDamage = (rand() % specialDamageMax + 6);
					playerHealth -= enemyDamage;
				}

				else {
					std::cout << "The enemy misses the special attack!" << "\n\n";
				}
			}

			//Dodge
			else if (enemyHealth <= enemyDodgeHealthThreshold) {
				std::cout << "The enemy used dodge, your attack chance is temporarily reduced..." << "\n\n";
				enemyAction = "dodge";
			}

			//Attack
			else if (true) {
				std::cout << "The enemy used attack" << std::endl;
				enemyAction = "attack";
				hitChance = (rand() % chanceMax + 1);

				if (hitChance <= hitDodgeThreshold && playerAction == "dodge") {
					std::cout << "The enemy attack was successful, despite your attempt to dodge!" << "\n\n";
					enemyDamage = (rand() % attackDamageMax + 1);
					playerHealth -= enemyDamage;
				}

				else if (hitChance <= hitRechargeThreshold && playerAction == "recharge") {
					std::cout << "The enemy attack was successful whilst your defences were lowered!" << "\n\n";
					enemyDamage = (rand() % attackDamageMax + 1);
					playerHealth -= enemyDamage;
				}

				else if (hitChance <= hitThreshold) {
					std::cout << "The enemy attack was successful!" << "\n\n";
					enemyDamage = (rand() % attackDamageMax + 1);
					playerHealth -= enemyDamage;
				}
				else
				{
					std::cout << "And misses!" << "\n\n";
				}

			}

			enemyEnergy += enemyEnergyRegen;
			enemyEnergyRegen = baseEnergyRegen;

			if (enemyEnergy > maxEnergy) {
				enemyEnergy = maxEnergy;
			}

			if (enemyHealth > maxHealth) {
				enemyHealth = maxHealth;
			}
		}


		//player scoring system
		if (playerHealth <= 0) {
			enemyScore += 1;
			std::cout << "You Lose!" << "\n\n";
		}
		else {
			playerScore += 1;
			std::cout << "You Win!" << "\n\n";
		}

		std::cout << "Player Score: " << playerScore << " ~~~~~ Enemy Score: " << enemyScore << "\n\n";

		std::cout << "Would you like to play again? (yes/no)" << "\n\n";
		std::cin >> playerRestart;

		while (playerRestart != "yes" && playerRestart != "no") {
			std::cout << "Invalid input, please enter 'yes' or 'no'" << "\n\n";
			std::cin >> playerRestart;
			std::cout << "\n\n";
		}

		if (playerRestart == "no") {
			break;
		}
		
	}
	
	return 0;
	}