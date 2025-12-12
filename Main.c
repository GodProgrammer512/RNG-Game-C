/* Include guard: */
#ifndef _RNG_GAME_C_
#define _RNG_GAME_C_

/* Importations: */
#include <cutils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Global variables: */
static long double all_attempts = 0.0L;
static long double wins = 0.0L;
static long double loses = 0.0L;

/* Functions prototype: */
static void save_data(); /* Save game data function. */
static void load_data(); /* Load game data function. */

/* Main code: */
int main()
{
	/* Start seed: */
	srand((unsigned)(time(NULL)));

	/* RNG Game version variables: */
	#define RNG_GAME_FULL_VERSION  301.0L /* RNG Game full version variable (3.0.0).  */
	#define RNG_GAME_MAJOR_VERSION 3.0L   /* RNG Game major version variable (3).     */
	#define RNG_GAME_MINOR_VERSION 0.0L   /* RNG Game minor version variable (0).     */
	#define RNG_GAME_PATCH_VERSION 1.0L   /* RNG Game patch version variable (0).     */

	/* Main variables: */
	#define MIN                    0      /* Minimum value variable.                  */
	#define MAX                    10     /* Maximum value variable.                  */
	char loop1 = 1;                       /* First loop variable.                     */
	int number = 0;                       /* Number variable.                         */
	int old_random_number = 0;            /* Old random number variable.              */
	int random_number = rand() % 11;      /* Random number between 0 and 10 variable. */
	long double round_attempts = 0.0L;    /* Attempts variable.                       */
	char option1[8192] = "";              /* First option variable.                   */
	char snumber[8192] = "";              /* String number variable.                  */

	/* Initializations before the game (load): */
	enable_vt_and_utf8();
	load_data();

	/* Main loop: */
	while(loop1 == 1)
	{
		CLEAR_TERMINAL();
		puts("========================================");
		printf("============ RNG Game %.0Lf.%.0Lf.%.0Lf ============\n", RNG_GAME_MAJOR_VERSION, RNG_GAME_MINOR_VERSION, RNG_GAME_PATCH_VERSION);
		puts("========================================");
		puts("         [ 0 ] Options...");
		puts("         [ 1 ] Play game!");
		fputs("\t   Your answer: ", stdout);
		scanf("%8191s", option1);
		CLEAR_TERMINAL();

		if(strcmp(option1, "0") == 0)
		{
			++loop1;

			while(loop1 == 2)
			{
				puts("==================================");
				puts("============ Options =============");
				puts("==================================");
				printf("  %s[ 0 ] Return%s\n", BOLD, BASE_TERMINAL);
				printf("  %s[ 1 ] Save%s and %squit...%s\n", GREEN_COLOR, BASE_TERMINAL, RED_COLOR, BASE_TERMINAL);
				printf("  %s[ 2 ] Change the random number%s\n", CYAN_COLOR, BASE_TERMINAL);
				printf("  %s[ 3 ] View statistics%s\n", YELLOW_COLOR, BASE_TERMINAL);
				printf("  %s[ 4 ] Read \"READ-ME\"%s\n", YELLOW_COLOR, BASE_TERMINAL);
				fputs("\t Your answer: ", stdout);
				scanf("%8191s", option1);

				if(strcmp(option1, "0") == 0)
				{
					--loop1;
				}

				else if(strcmp(option1, "1") == 0)
				{
					loop1 = 0, save_data(), CLEAR_TERMINAL();
				}

				else if(strcmp(option1, "2") == 0)
				{
					CLEAR_TERMINAL();
					old_random_number = random_number;
					printf("Now your attempts have been reseted and the random number has changed to a new value! (Old random number: %d)\n", old_random_number);
					random_number = rand() % 11, round_attempts = 0.0L;
					petc();
					CLEAR_TERMINAL();
				}

				else if(strcmp(option1, "3") == 0)
				{
					CLEAR_TERMINAL();
					printf("Number of all attempts: %0.Lf\n", all_attempts);
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					printf("Number of wins: %0.Lf\n", wins);
					printf("Number of loses: %0.Lf\n", loses);
					petc();
					CLEAR_TERMINAL();
				}

				else if(strcmp(option1, "3.14") == 0 || strcmp(option1, "3,14") == 0)
				{
					CLEAR_TERMINAL();
					easter_egg_function();
					CLEAR_TERMINAL();
				}

				else if(strcmp(option1, "4") == 0)
				{
					CLEAR_TERMINAL();
					rrmf();
					petc_a();
					CLEAR_TERMINAL();
				}

				else
				{
					CLEAR_TERMINAL();
				}
			}
		}

		else if(strcmp(option1, "1") == 0)
		{
			printf("Type the number that you think it is (%sMin: 0%s, %sMax: 10%s, if you type another number below 0 it will be rounded to 0, and the same will hapend to the number above 10...): ", BOLD, BASE_TERMINAL, BOLD, BASE_TERMINAL);
			scanf("%8191s", snumber);
			number = atoi(snumber);
			CLEAR_TERMINAL();
			fputs("Soo... ", stdout);

			if(number > MAX)
			{
				number = MAX;

				if(number > random_number)
				{
					printf("%s%sYou lose!%s The random number is below 10!\n", BOLD, RED_COLOR, BASE_TERMINAL);
					++all_attempts, ++round_attempts, ++loses;
					save_data();
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = 10!\n", BOLD, GREEN_COLOR, BASE_TERMINAL);
					puts("Now the random number has changed to a new value!");
					++all_attempts, ++round_attempts, ++wins;
					save_data();
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					random_number = rand() % 11, round_attempts = 0.0L;
				}
			}

			else if(number < MIN)
			{
				number = MIN;

				if(number < random_number)
				{
					printf("%s%sYou lose!%s The random number is above 0!\n", BOLD, RED_COLOR, BASE_TERMINAL);
					++all_attempts, ++round_attempts, ++loses;
					save_data();
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = 0\n", BOLD, GREEN_COLOR, BASE_TERMINAL);
					puts("Now the random number has changed to a new value!");
					++all_attempts, ++round_attempts, ++wins;
					save_data();
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					random_number = rand() % 11, round_attempts = 0.0L;
				}
			}

			else
			{
				if(number < random_number)
				{
					printf("%s%sYou lose!%s The random number is above %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);
					++all_attempts, ++round_attempts, ++loses;
					save_data();
				}

				else if(number == random_number)
				{
					printf("%s%sYou win!%s The random number is = %d!\n", BOLD, GREEN_COLOR, BASE_TERMINAL, number);
					puts("Now the random number has changed to a new value!");
					++all_attempts, ++round_attempts, ++wins;
					save_data();
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					random_number = rand() % 11, round_attempts = 0.0L;
				}

				else if(number > random_number)
				{
					printf("%s%sYou lose!%s The random number is below %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);
					++all_attempts, ++round_attempts, ++loses;
					save_data();
				}
			}

			petc();
		}
	}

	return 0;
}

/* Save data function: */
static void save_data()
{
	MKDIR("data");
	FILE *statistics = fopen("data/statistics.csv", "w");
	fprintf(statistics, "%Lf,%Lf,%Lf\n", all_attempts, wins, loses);
	fclose(statistics);
}

/* Load data function: */
static void load_data()
{
	FILE *statistics = fopen("data/statistics.csv", "r");
	if(!statistics)
	{
		save_data();
		return;
	}

	char buffer[64] = "";

	if(fgets(buffer, sizeof(buffer), statistics) != NULL)
	{
		long double values[3] = {0.0L, 0.0L, 0.0L};
		int itens = sscanf(buffer, "%Lf,%Lf,%Lf", &values[0], &values[1], &values[2]);
		
		if(itens == 3)
		{
			all_attempts = values[0];
			wins         = values[1];
			loses        = values[2];
		}

		else
		{
			save_data();
		}
	}

	else
	{
		save_data();
	}

	fclose(statistics);
}

/* End code: */
#endif
