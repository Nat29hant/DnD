/*
Nathan Tran
Assignement 3
*/
#include <iostream>
#include <memory>// header file for shared pointers
#include <string>// header file for string
#include <time.h>// header file for base class
using namespace std;

class CommonStatistics//base class, but is abstract because it has virtual functions
{
	protected:// is protected so the derived classes have access to them
		int HP;// HP = hit points or health
		int AD;// AD = attack damage
		int armor;// every dervied class has armor
		string name;// every dervied class has a name
		int speed;// every dervied class has their own speed
		int modifier;// every dervied class their own attack modifier
		int die20;// every dervied class must roll for Initiative
	public:
		CommonStatistics()//default constructor
		{

		}
		int getHP()// function to get HP
		{
			return HP;
		}
		int getAD()// function to get AD
		{
			return AD;
		}
		int getArmor()// function to get armor
		{
			return armor;
		}
		int getSpeed()// function to get speed
		{
			return speed;
		}
		string getName()// function to get name
		{
			return name;
		}
		int Initiative()// function for rolling a die between 1 - 20
		{
			int die20 = rand() % 20 + 1;
			return die20;
		}
		int totalSpeed(int sp)// function to get get total speed
		{
			return sp + getSpeed();
		}
		int Heal()//function for healing
		{
			int die5 = (rand() % 5 + 1) + (rand() % 5 + 1);
			return die5;
		}
		int newHP(int hp)// function to get the new HP
		{
			return hp + getHP();
		}
		int getModifier()// function to get attack modifier
		{
			return modifier;
		}
		int fairyHeal()// function to restore full health
		{
			HP = 20;
			return HP;
		}
		int totalAD(int die)
		{
			return die + getModifier();
		}
		bool Dodge()// function to determine if the opponent will dodge
		{
			int d = rand() % 2 + 1;// a value between 1-2
			if (d == 1)// d stands for Dodge
			{
				return true;
			}
			else if(d == 0)
			{
				return false;
			}

		}
		void Menu()// function prints menu;
		{
			cout << "\nWhat will you do?\n";
			cout << "1: Attack\n";
			cout << "2. Heal\n";
			cout << "Your move: ";
		}
		void recieveDamage(int dmg, int h)// function to recieve damage
		{
			if (dmg < 0)// just in case if the armor is greater than the damge, which will lead to a (-) number which must be cahnge into 0
			{
				dmg = 0;
			}
			HP = newHP(h) - dmg;
			cout << endl << name << " has taken "<< dmg << " damage and is now at " << HP << " HP\n";
		}
		virtual int getAttackDie() = 0;// each derived class will have their own attack die
		virtual void displayStats() = 0;// each derived class will diplay their own stats
};
class Warrior : public CommonStatistics// dervied class
{
	public:
		Warrior() :CommonStatistics()// default constructor
		{
			srand(time(0));
			name = "Knight Lancelot";
			speed = rand() % 5 + 1;
			modifier = rand() % 5 + 1;
			HP = rand() % 20 + 1;
			armor = rand() % 5 + 1;
		}
		virtual void displayStats()// inherits the displayStats function
		{
			cout << "Warrior " << name << "'s current stats:\n";
			cout << "Health: " << HP << endl;
			cout << "Healing Die: 2 D5\n";
			cout << "Base Attack Die: 1 D6\n";
			cout << "Armor: " << armor << endl;
			cout << "Attack Modifier (Strength): " << modifier << endl;
			cout << "Initiative Modifier (Speed): " << speed << endl;
		}
		virtual int getAttackDie()// inherits the getAttackDie function
		{
			int die6 = rand() % 6 + 1;
			return die6;
		}
};
class Mage : public CommonStatistics// dervied class
{
	public:
		Mage() : CommonStatistics()
		{
			srand(time(0));
			name = "Wizard Osh";
			HP = rand() % 20 + 1;
			armor = rand() % 5 + 1;
			modifier = rand() % 10 + 1;
			speed = 0;
		}
		virtual void displayStats()// inherits the displayStats function
		{
			cout << "\nMage " << name << "'s current stats:\n";
			cout << "Health: " << HP << endl;
			cout << "Base Attack Die: 1 D4\n";
			cout << "Armor: " << armor << endl;
			cout << "Attack Modifier (Intellect): " << modifier << endl;
		}
		virtual int getAttackDie()// inherits the getAttackDie function
		{
			int die4 = rand() % 4 + 1;
			return die4;
		}
};

class Rogue : public CommonStatistics// dervied class
{
	public:
		Rogue() : CommonStatistics()
		{
			srand(time(0));
			name = "Assassian Corvo";
			HP = rand() % 15 + 1;
			modifier = rand() % 5 + 1;
			armor = rand() % 5 + 1;
			speed = rand() % 3 + 1;
		}
		virtual void displayStats()// inherits the displayStats function
		{
			cout << "\nRogue " << name << "'s current stats:\n";
			cout << "Health: " << HP << endl;
			cout << "Base Attack Die: 2 D4\n";
			cout << "Armor: " << armor << endl;
			cout << "Attack Modifier (Agility): " << modifier << endl;
			cout << "Initiative Modifier (Speed): " << speed << endl;
			cout << "Dodge: 50% chance to dodge an incoming attack\n";
		}
		virtual int getAttackDie()// inherits the getAttackDie function
		{
			int die4 = (rand() % 4 + 1) + (rand() % 4 + 1);
			return die4;
		}
};
int main()
{
	srand((time(0)));
	int choice;// needed for user to input a choice
	int tempAttack;// needed to hold a valure for attack
	int Speed;// player's speed
	int Speed2;// mage's speed
	int Speed3;// rogue's speed
	int health;// player's healing dice
	int die1;// player's attack die
	int die2;// mage's attack die
	int die3;// rogue's attack die
	shared_ptr<CommonStatistics> player = make_shared<Warrior>();// creates an object from the base class, but ties it with the Warrior class
	shared_ptr<CommonStatistics> enemy1 = make_shared<Mage>();// creates an object from the base class, but ties it with the Mage class
	shared_ptr<CommonStatistics> enemy2 = make_shared<Rogue>();// creates an object from the base class, but ties it with the Rogue class
	cout << "You are now " << player->getName() << ", a ferocious Warrior\n";
	cout << "A Mage named " << enemy1->getName() << " appears and is ready for battle!\n\n";
	player->displayStats();// shows Warrior stats
	enemy1->displayStats();// shows Mage stats
	while (player->getHP() > 0 && enemy1->getHP() > 0)// a loop for the battle
	{
		Speed = player->Initiative();// must set it = to Initiative for later uses
		Speed2 = enemy1->Initiative();// must set it = to Initiative for later uses
		health = player->Heal();// must set it = to Heal for later uses
		die1 = player->getAttackDie();// must set it = to AttackDie for later uses
		die2 = enemy1->getAttackDie();// must set it = to AttackDie for later uses
		cout << "\nYou rolled one dice(1-20): Initiative score of " << Speed << " + a speed modifier of "// reason why it has spped instead of Initiative is because it will call the function again
			<< player->getSpeed() << " for a total of " << player->totalSpeed(Speed);// of retaining the same value from Initiative
		cout << "\nThe Mage rolled one dice(1-20): Initiative score of " << Speed2 << " and has no bonus speed modifier\n";// same thing for the mage
		if (player->totalSpeed(Speed) > enemy1->totalSpeed(Speed2))// player will go 1st if its speed is higher than the enemy
		{
			player->Menu();// calls the Menu function
			cin >> choice;
			if (choice == 1)
			{
				cout << "You rolled one dice(1-6): Damage score of " << die1 << " + a strength modifier of "
					<< player->getModifier() << " for a total of " << player->totalAD(die1);// similar reason why it has die1 in the parameters like speed
				tempAttack = (player->totalAD(die1) - enemy1->getArmor());// will calculate the damage
				enemy1->recieveDamage(tempAttack , 0);// calls the recieveDamage function, also has 0 to indicate no new change in health
				if (enemy1->getHP() <= 0)
				{
					break;// will break the loop if health = 0
				}
				cout << enemy1->getName() << "'s Move:\n";
				cout << enemy1->getName() << " rolled one dice(1-4): Damage score of " << die2 << " + a intellect modifier of "
					<< enemy1->getModifier() << " for a total of " << enemy1->totalAD(die2);// same thing with player
				tempAttack = (enemy1->totalAD(die2) - player->getArmor()); // will calculate the damage
				player->recieveDamage(tempAttack, 0);// calls the recieveDamage function, also has 0 to indicate no new change in health
				if (player->getHP() <= 0)
				{
					break;// will break the loop if health = 0
				}

			}
			else if (choice == 2)
			{
				cout << "You heal your self for " << health << " hit points!\n";
				cout << "Total HP now at: " << player->newHP(health) << endl;// similar reason why it has health in the parameters like speed
				cout << enemy1->getName() << "'s Move:\n";
				cout << enemy1->getName() << " rolled one dice(1-4): Damage score of " << die2 << " + a intellect modifier of "
					<< enemy1->getModifier() << " for a total of " << enemy1->totalAD(die2);
				tempAttack = (enemy1->totalAD(die2) - player->getArmor());// will calculate the damage
				player->recieveDamage(tempAttack, health);// calls the recieveDamage function, has health in the parameter to get the new health instead of the previous
				if (player->getHP() <= 0)
				{
					break;// will break the loop if health = 0
				}
			}

		}
		if(enemy1->totalSpeed(Speed2) > player->totalSpeed(Speed))// enemy1 will go 1st if its speed is higher than the player
		{
			cout<< enemy1->getName() << "'s Move:\n";
			cout<< enemy1->getName() << " rolled one dice(1-4): Damage score of " << die2 << " + a intellect modifier of "
				<< enemy1->getModifier() << " for a total of " << enemy1->totalAD(die2);
			tempAttack = (enemy1->totalAD(die2) - player->getArmor());
			player->recieveDamage(tempAttack, 0);
			if (player->getHP() <= 0)
			{
				break;
			}
			player->Menu();// calls the Menu function
			cin >> choice;
			if (choice == 1)
			{
				cout << "You rolled one dice(1-6): Damage score of " << die1 << " + a strength modifier of "
					<< player->getModifier() << " for a total of " << player->totalAD(die1);
				tempAttack = (player->totalAD(die1) - enemy1->getArmor());// will calculate the damage
				enemy1->recieveDamage(tempAttack, 0);
				if (enemy1->getHP() <= 0)
				{
					break;// will break the loop if health = 0
				}
				cout << enemy1->getName() << "'s Move:\n";
				cout << enemy1->getName() << " rolled one dice(1-4): Damage score of " << die2 << " + a intellect modifier of "
					<< enemy1->getModifier() << " for a total of " << enemy1->totalAD(die2);
				tempAttack = (enemy1->totalAD(die2) - player->getArmor());// will calculate the damage
				player->recieveDamage(tempAttack, 0);
				if (player->getHP() <= 0)
				{
					break;// will break the loop if health = 0
				}
			}
			else if (choice == 2)
			{
				cout << "You heal your self for " << health << " hit points!\n";
				cout << "Total HP now at: " << player->newHP(health) << endl;
				cout << enemy1->getName() << "'s Move:\n";
				cout << enemy1->getName() << " rolled one dice(1-4): Damage score of " << die2 << " + a intellect modifier of "
					<< enemy1->getModifier() << " for a total of " << enemy1->totalAD(die2);
				tempAttack = (enemy1->totalAD(die2) - player->getArmor());// will calculate the damage
				player->recieveDamage(tempAttack, health);// calls the recieveDamage function, has health in the parameter to get the new health instead of the previous
				if (player->newHP(0) <= 0)
				{
					break;// will break the loop if health = 0
				}
			}
		}
		if (enemy1->totalSpeed(Speed2) == player->totalSpeed(Speed))// will print something to show if both speeds are =
		{
			cout << "Roll again\n";
		}

	}
	if (player->getHP() <= 0)// when the loop breaks and if the player's health is 0 or below
	{
		cout << "You have been slain GG.\n";
	}
	if (enemy1->getHP() <= 0)// when the loop breaks and if the enemy's health is 0 or below
	{
		cout << "The Mage have been slain!\n";
		cout << "A magical fairy visists, your HP has been reset to " << player->fairyHeal() << "!\n";
		player->displayStats();
		enemy2->displayStats();
		while (player->getHP() > 0 && enemy2->getHP() > 0)// a new loop, but it's simlar to the warrior vs mage fight, but with a few differences
		{
			Speed3 = enemy2->Initiative();// must set it = to Initiative for later uses
			die3 = enemy2->getAttackDie();// must set it = to AttackDie for later uses
			cout << "\nYou rolled one dice(1-20): Initiative score of " << Speed << " + a speed modifier of "
				<< player->getSpeed() << " for a total of " << player->totalSpeed(Speed);
			cout << "\nThe Assassian rolled one dice(1-20): Initiative score of " << Speed3 << " + a speed modifier of "
				<< enemy2->getSpeed() << " for a total of " << enemy2->totalSpeed(Speed3);// the rogue has a speed modidfier which needs the speed3 in the parameter for totalSpeed
			if (player->totalSpeed(Speed) > enemy2->totalSpeed(Speed3))// player will go 1st if its speed is higher than the enemy
			{
				player->Menu();// calls the Menu function
				cin >> choice;
				if (choice == 1)
				{
					cout << "You rolled one dice(1-6): Damage score of " << die1 << " + a strength modifier of "
						<< player->getModifier() << " for a total of " << player->totalAD(die1);
					tempAttack = (player->totalAD(die1) - enemy2->getArmor());
					if (enemy2->Dodge() == true)// if the function is true then the rogue will not dodge the attack
					{
						enemy2->recieveDamage(tempAttack, 0);
						if (enemy2->getHP() <= 0)
						{
							break;// will break the loop if health = 0
						}
					}
					else// if the function is false then the rogue will dodge the attack
					{
						cout << endl << enemy2->getName() << " Dodged the attack!\n";
					}
					cout << enemy2->getName() << "'s Move:\n";
					cout<< enemy2->getName() << " rolled two dice(1-4): Damage score of " << die3 << " + an agility modifier of "
						<< enemy2->getModifier() << " for a total of " << enemy2->totalAD(die3);
					tempAttack = (enemy2->totalAD(die3) - player->getArmor());
					player->recieveDamage(tempAttack, 0);
					if (player->getHP() <= 0)
					{
						break;// will break the loop if health = 0
					}

				}
				else if (choice == 2)
				{
					cout << "You heal your self for " << health << " hit points!\n";
					cout << "Total HP now at: " << player->newHP(health) << endl;
					cout << enemy2->getName() << "'s Move:\n";
					cout << enemy2->getName() << " rolled two dice(1-4): Damage score of " << die3 << " + an agility modifier of "
						<< enemy2->getModifier() << " for a total of " << enemy2->totalAD(die3);
					tempAttack = (enemy2->totalAD(die3) - player->getArmor());
					player->recieveDamage(tempAttack, health);// calls the recieveDamage function, has health in the parameter to get the new health instead of the previous
					if (player->getHP() <= 0)
					{
						break;// will break the loop if health = 0
					}
				}
			}
			if (player->totalSpeed(Speed) < enemy2->totalSpeed(Speed3))// enemy2 will go 1st if its speed is higher than the player
			{
				cout << enemy2->getName() << "'s Move:\n";
				cout << enemy2->getName() << " rolled two dice(1-4): Damage score of " << die3 << " + an agility modifier of "
					<< enemy2->getModifier() << " for a total of " << enemy2->totalAD(die3);
				tempAttack = (enemy2->totalAD(die3) - player->getArmor());
				player->recieveDamage(tempAttack, 0);
				if (player->getHP() <= 0)
				{
					break;// will break the loop if health = 0
				}
				player->Menu();// calls the Menu function
				cin >> choice;
				if (choice == 1)
				{
					cout << "You rolled one dice(1-6): Damage score of " << die1 << " + a strength modifier of "
						<< player->getModifier() << " for a total of " << player->totalAD(die1);
					tempAttack = (player->totalAD(die1) - enemy2->getArmor());
					if (enemy2->Dodge() == true)// if the function is true then the rogue will not dodge the attack
					{
						enemy2->recieveDamage(tempAttack, 0);
						if (enemy2->getHP() <= 0)
						{
							break;// will break the loop if health = 0
						}
					}
					else// if the function is false then the rogue will dodge the attack
					{
						cout << endl << enemy2->getName() << " Dodged the attack!\n";
					}
					cout << enemy2->getName() << "'s Move:\n";
					cout << enemy2->getName() << " rolled two dice(1-4): Damage score of " << die3 << " + an agility modifier of "
						<< enemy2->getModifier() << " for a total of " << enemy2->totalAD(die3);
					tempAttack = (enemy2->totalAD(die3) - player->getArmor());
					player->recieveDamage(tempAttack, 0);
					if (player->getHP() <= 0)
					{
						break;// will break the loop if health = 0
					}

				}
				else if (choice == 2)
				{
					cout << "You heal your self for " << health << " hit points!\n";
					cout << "Total HP now at: " << player->newHP(health) << endl;
					cout << enemy2->getName() << "'s Move:\n";
					cout << enemy2->getName() << " rolled two dice(1-4): Damage score of " << die3 << " + an agility modifier of "
						<< enemy2->getModifier() << " for a total of " << enemy2->totalAD(die3);
					tempAttack = (enemy2->totalAD(die3) - player->getArmor());
					player->recieveDamage(tempAttack, health);
					if (player->getHP() <= 0)
					{
						break;// will break the loop if health = 0
					}
				}
			}
			if (enemy2->totalSpeed(Speed2) == player->totalSpeed(Speed))
			{
				cout << "Roll again\n";
			}
		}
		if (player->getHP() <= 0)// if the player's health is 0 or below
		{
			cout << "You have been slain.";
		}
		if (enemy2->getHP() <= 0)// if the rogue's health is 0 or below
		{
			cout << "You have won the Video game.";
		}
	}

	system("pause>nul");
	return 0;
}
