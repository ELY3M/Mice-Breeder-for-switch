#include <string.h>
#include <stdio.h>
#include <stdlib.h>	

#include <switch.h>

/*

My father breed mice and I love mice 
ELY M.  


I used Hamster NX (https://github.com/Cid2mizard/Hamsters_NX/) as a base. Thanks to Cid2mizard

*/

	
bool mode_intro;
bool error;
int mode_game;

u8 Month;

typedef struct 
{
	u16 ADULTS;
	u16 YOUNGS;
	u16 CAGES;
	int nb_par_cage;
} 
info;
info MALES, FEMALES;

int FOOD;
float PRICE;
float CHECKOUT;
float SCORE;
int DEAD_HUNGRY;
int DEAD_SUFFOCATED;

int males_to_sell;
int females_to_sell;
int number_coupling;
int food_to_buy;
int buy_cages_males;
int buy_cages_females;
int selection;



void clean()
{
	printf("\x1b[28;1H                                               ");
	printf("\x1b[29;1H                                               ");
	printf("\x1b[30;1H                                               ");
	printf("\x1b[31;1H                                               ");
	printf("\x1b[32;1H                                               ");
	printf("\x1b[33;1H                                               ");
	printf("\x1b[34;1H                                               ");
	printf("\x1b[35;1H                                               ");
	printf("\x1b[36;1H                                               ");
	printf("\x1b[37;1H                                               ");
	printf("\x1b[38;1H                                               ");
	printf("\x1b[39;1H                                               ");
	printf("\x1b[40;1H                                               ");
	printf("\x1b[41;1H                                               ");
	printf("\x1b[42;1H                                               ");
	printf("\x1b[43;1H                                               ");
	printf("\x1b[44;1H                                               ");
	printf("\x1b[45;1H                                               ");
}


void printGame()
{
	if (mode_intro)
	{
		printf ("\x1b[2;30H%s%s%s", CONSOLE_CYAN, "***** Mice Breeder *****", CONSOLE_RESET);

        printf("\x1b[4;1HThe purpose of the game is to manage breeding");
			printf("\x1b[5;1Hmice 12 months by making profits.");
			printf("\x1b[6;1H* You can sell or couple only the adults.");
			printf("\x1b[7;1H* Youngs become adults after 1 month.");
			printf("\x1b[8;1H* Each coupling can give a maximum of 18 youngs.");
			printf("\x1b[10;1H** Press A to continue...");

	}
	else if ((mode_game > 0) && (mode_game < 8))
	{

			printf("\x1b[12;1H-------------------------------------------------");
			printf("\x1b[13;15HSITUATION OF THE MONTH No %d   ", Month);
			printf("\x1b[15;10HMALES                 FEMALES");
			printf("\x1b[16;10HADULTS  : %d   ", MALES.ADULTS);
			printf("\x1b[16;32HADULTS  : %d   ", FEMALES.ADULTS);
			printf("\x1b[17;10HYOUNGS  : %d   ", MALES.YOUNGS);
			printf("\x1b[17;32HYOUNGS  : %d   ", FEMALES.YOUNGS);
			printf("\x1b[18;10HCAGES   : %d   ", MALES.CAGES);
			printf("\x1b[18;32HCAGES   : %d   ", FEMALES.CAGES);
			printf("\x1b[19;6Hnb per cage : %d   ", MALES.nb_par_cage);
			printf("\x1b[19;28Hnb per cage : %d   ", FEMALES.nb_par_cage);
			printf("\x1b[21;1HREMAINING FOOD              : %d KG   ", FOOD);
			printf("\x1b[22;1HPRICE OF HAMSTER THIS MONTH : %.2f $   ", PRICE);
			printf("\x1b[23;1HCHECKOUT                    : %.2f $   ", CHECKOUT);	
			printf("\x1b[24;1HDEAD HUNGRY                 : %d   ", DEAD_HUNGRY);
			printf("\x1b[25;1HDEAD SUFFOCATED             : %d   ", DEAD_SUFFOCATED);	
			printf("\x1b[26;1H** Press A to continue...");
			printf("\x1b[27;1H-------------------------------------------------");

			if (mode_game == 2)
			{
				printf("\x1b[28;1HMALES FOR SALE ? %d   ", males_to_sell);
			}
			if (mode_game == 3)
			{
				printf("\x1b[29;1HFEMALES FOR SALE ? %d   ", females_to_sell);
			}
			if (mode_game == 4)
			{
				printf("\x1b[30;1HNUMBER COUPLING ? %d   ", number_coupling);
			}
			if (mode_game == 5)
			{
				printf("\x1b[31;1HFOOD TO BUY ? %d   ", food_to_buy);
			}
			if (mode_game == 6)
			{
				printf("\x1b[32;1HPURCHASE CAGES FOR MALES ? %d   ", buy_cages_males);
			}
			if (mode_game == 7)
			{
				printf("\x1b[33;1HPURCHASE CAGES FOR FEMALES ? %d   ", buy_cages_females);
			}

		if (error)
			printf("\x1b[34;1HIMPOSSIBLE   ");
		else
			printf("\x1b[34;1H             ");
	}
	else if (mode_game == 8)
	{

			printf("\x1b[35;1H...........END OF GAME...........   ");

			if (SCORE <=150)
			{
				printf("\x1b[37;1HOOPS!, YOUR BREEDING METHOD IS FAILING.   ");
			}
			else if ((SCORE > 150) && (SCORE <= 500))
			{
				printf("\x1b[37;1HWELL DONE, YOU PROPERLY MANAGE BREEDING.   ");
			}
			else if (SCORE > 500)
			{
				printf("\x1b[37;1HGREAT JOB, YOU ARE A CHAMPION OF BREEDING.   ");
			}

			printf("\x1b[38;1HYOU HAVE AFTER THESE 12 MONTHS :   ");
			printf("\x1b[39;1H%d ADULTS   ", MALES.ADULTS + FEMALES.ADULTS);
			printf("\x1b[40;1H%d YOUNGS   ", MALES.YOUNGS + FEMALES.YOUNGS);
			printf("\x1b[41;1H%d CAGES   ", MALES.CAGES + FEMALES.CAGES);
			printf("\x1b[42;1H%d KG OF FOOD   ", FOOD);
			printf("\x1b[43;1HTHE VALUE OF YOUR BREEDING IS %.2f $   ", SCORE);
			printf("\x1b[45;1H** PRESS A TO PLAY AGAIN...   ");
		
	}
}

void newGame()
{
	Month = 1;
	MALES.ADULTS = 1;
	FEMALES.ADULTS = 1;
	MALES.YOUNGS = 0;
	FEMALES.YOUNGS = 0;
	MALES.CAGES = 1;
	FEMALES.CAGES = 1;
	MALES.nb_par_cage = 1;
	FEMALES.nb_par_cage = 1;
	FOOD = 5;
	PRICE = 1 + (rand()%2)*0.10 ;//1.00 ou 1.10;
	CHECKOUT = 5.00;
	DEAD_SUFFOCATED = 0;
	DEAD_HUNGRY = 0;
}

void readInput(u64 kDown)
{
		
	if ((kDown & HidNpadButton_A) && (mode_intro == true))
	{
		mode_intro = false;
		mode_game = 1;
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 1))
	{
		//start of month
		selection = 0;
		mode_game = 2;
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 2))
	{
		if (males_to_sell <= MALES.ADULTS)
		{
			selection = 0;
			mode_game = 3;
			MALES.ADULTS -= males_to_sell;
			CHECKOUT += males_to_sell*PRICE;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 3))
	{
		if (females_to_sell <= FEMALES.ADULTS)
		{
			selection = 0;
			mode_game = 4;
			FEMALES.ADULTS -= females_to_sell;
			CHECKOUT += females_to_sell*PRICE;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 4))
	{
		if ((number_coupling <= MALES.ADULTS) && (number_coupling <= FEMALES.ADULTS))
		{
			selection = 0;
			mode_game = 5;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 5))
	{
		if (food_to_buy*0.10 <= CHECKOUT)
		{
			selection = 0;
			mode_game = 6;
			FOOD += food_to_buy;
			CHECKOUT -= food_to_buy*0.10;
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 6))
	{
		if (buy_cages_males*5 <= CHECKOUT)
		{
			selection = 0;
			mode_game = 7;
			MALES.CAGES += buy_cages_males;
			CHECKOUT -= buy_cages_males*5;//5$ la cage
			error = false;
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 7))
	{
		if (buy_cages_females*5 <= CHECKOUT)
		{
			selection = 0;
			FEMALES.CAGES += buy_cages_females;
			CHECKOUT -= buy_cages_females*5;//5$ la cage
			error = false;

			DEAD_SUFFOCATED = 0;
			DEAD_HUNGRY = 0;

			//Les petits grandissent...
			MALES.ADULTS += MALES.YOUNGS;
			MALES.YOUNGS = 0;
			FEMALES.ADULTS += FEMALES.YOUNGS;
			FEMALES.YOUNGS = 0;

			//Les accouplements
			if (number_coupling >= 1)
			{
				int i, m, f;
				int quantity;

				for (i = 1; i <= number_coupling;i++)
				{
					//Nombre aléatoire de petits maxi 18
					quantity = rand() % 18 + 1;

					//On divise males et females
					m = rand() % quantity + 1;
					f = quantity - m;

					//On ajoute les petits aux effectifs adultes
					MALES.YOUNGS += m;
					FEMALES.YOUNGS += f;
				}
			}

			//Help the losers, if more animals, we make a young couple a bonus
			if (MALES.ADULTS + FEMALES.ADULTS + MALES.YOUNGS + FEMALES.YOUNGS == 0)
			{
				MALES.YOUNGS = 1;
				FEMALES.YOUNGS = 1;
			}

			//male cages
			MALES.nb_par_cage = (MALES.ADULTS + MALES.YOUNGS) / MALES.CAGES;

			//Reset the number of dead
			DEAD_SUFFOCATED = 0;

			//calculate the dead
			while (MALES.nb_par_cage > 20)
			{
				//kill the little ones first
				if (MALES.YOUNGS > 0) MALES.YOUNGS--;
				//Sinon un adulte
				else MALES.ADULTS--;

				DEAD_SUFFOCATED++;

				MALES.nb_par_cage = (MALES.ADULTS + MALES.YOUNGS) / MALES.CAGES;
			}

			//female cages
			FEMALES.nb_par_cage = (FEMALES.ADULTS + FEMALES.YOUNGS) / FEMALES.CAGES;

			while (FEMALES.nb_par_cage > 20)
			{
				//kill small first
				if (FEMALES.YOUNGS > 0) FEMALES.YOUNGS--;
				//If not an adult
				else FEMALES.ADULTS--;

				DEAD_SUFFOCATED++;

				FEMALES.nb_par_cage = (FEMALES.ADULTS + FEMALES.YOUNGS) / FEMALES.CAGES;
			}

			//the food
			int workforce;
			workforce = MALES.ADULTS + FEMALES.ADULTS + MALES.YOUNGS + FEMALES.YOUNGS;
			DEAD_HUNGRY = 0;

			if (FOOD > workforce) FOOD -= workforce;
			else
			{
				DEAD_HUNGRY = workforce - FOOD;

				while (	workforce > FOOD)
				{
					int choix;

					choix = rand() % 4 + 1;

					if ((choix == 1) && (MALES.ADULTS > 0)) 			MALES.ADULTS--;
					else if ((choix == 2) && (FEMALES.ADULTS > 0)) 	FEMALES.ADULTS--;
					else if ((choix == 3) && (MALES.YOUNGS > 0)) 		MALES.YOUNGS--;
					else if ((choix == 4) && (FEMALES.YOUNGS > 0)) 	FEMALES.YOUNGS--;

					workforce = MALES.ADULTS + FEMALES.ADULTS + MALES.YOUNGS + FEMALES.YOUNGS;
				}

				FOOD = 0;
			}

			//pass month
			Month++;

	
			males_to_sell = 0;
			females_to_sell = 0;
			number_coupling = 0;
			food_to_buy = 0;
			buy_cages_males = 0;
			buy_cages_females = 0;

			//New price
			PRICE = 1 + (rand()%2)*0.10 ;//1.00 ou 1.10;

			if (Month >= 13)
			{
				mode_game = 8;
				SCORE = CHECKOUT + MALES.ADULTS + FEMALES.ADULTS + MALES.YOUNGS + FEMALES.YOUNGS + MALES.CAGES + FEMALES.CAGES;
			}
			else
			{
				mode_game = 1;
				clean();
			}
		}
		else
		{
			//IMPOSSIBLE
			error = true;
		}
	}
	else if ((kDown & HidNpadButton_A) && (mode_game == 8))
	{
		SCORE = 0;
		mode_game = 1;
		clean();
		newGame();
	}

	//the selection at D-pad
	else if ((kDown & HidNpadButton_Right) && (mode_game >= 2) && (mode_game < 8))
	{
		selection++;
	}
	else if ((kDown & HidNpadButton_Left) && (selection >= 1) && (mode_game >= 2) && (mode_game < 8))
	{
		selection--;
	}
	else if ((kDown & HidNpadButton_Up) && (mode_game >= 2) && (mode_game < 8))
	{
		selection+=10;
	}
	else if ((kDown & HidNpadButton_Down) && (selection >= 10) && (mode_game >= 2) && (mode_game < 8))
	{
		selection-=10;
	}
	else if ((kDown & HidNpadButton_R) && (mode_game >= 2) && (mode_game < 8))
	{
		selection+=100;
	}
	else if ((kDown & HidNpadButton_L) && (selection >= 100) && (mode_game >= 2) && (mode_game < 8))
	{
		selection-=100;
	}
}


int main(int argc, char **argv)
{
	
	
	consoleInit(NULL);
	setInitialize();
	
	padConfigureInput(1, HidNpadStyleSet_NpadStandard);
	PadState pad;
	padInitializeDefault(&pad);

	mode_intro = true;
	newGame();

	while(appletMainLoop())
	{
		printGame();

		//Assign the inputs
		if (mode_game == 2) males_to_sell = selection;
		else if (mode_game == 3) females_to_sell = selection;
		else if (mode_game == 4) number_coupling = selection;
		else if (mode_game == 5) food_to_buy = selection;
		else if (mode_game == 6) buy_cages_males = selection;
		else if (mode_game == 7) buy_cages_females = selection;

        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
				
		readInput(kDown);
		if (kDown & HidNpadButton_Plus) { 
		break; 
		} // break in order to return to hbmenu

		consoleUpdate(NULL);
		
		//gfxFlushBuffers();
		//gfxSwapBuffers();
		//gfxWaitForVsync();
	}

	setExit();
	consoleExit(NULL);
	return 0;
}

