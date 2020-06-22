#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

/**************************************************************************
 * Function: is_int
 * Description: checks if a given string is a positive int
 * Parameters: string input
 * Pre-conditions: input must be a string
 * Post-conditions: must return a bool
 * ***********************************************************************/

bool is_int(string input) {
	if (input.length() == 0) {
		return false;
	}

	for (int i = 0; i < input.length(); i++) {
		if (input[i] < 48 || input[i] > 57) {
			return false;
		}	
	}

	return true;
}


/**************************************************************************
 * Function: string_to_int(string input)
 * Description: converts an int stored as a string into an actual int
 * Parameters: string input
 * Pre-conditions: input must be a string
 * Post-conditions: output must be an int
 * ***********************************************************************/

int string_to_int(string input) {
	int valid_int = 0;
	int len = input.length();

	for (int i = 0; i < len; i++) {
		int number = (int) input[i] - 48;
		valid_int += number * pow(10, (len - 1 - i));
	}

	return valid_int;
}


/**************************************************************************
 * Function: bubble_sort
 * Description: sorts a small array by continuously moving the largest value to the last index as index range decreases
 * Parameters: int* dice, int length
 * Pre-conditions: inputs must include a dynamic array and its length
 * Post-conditions: must change the values within the array but no return value
 * ***********************************************************************/

void bubble_sort(int* dice, int length) {
	for (int i = 0; i < (length - 1); i++) {
		for (int j = 0; j < (length - 1 - i); j++) {
			if (dice[j] > dice[j+1]) {
				int temp = dice[j];
				dice[j] = dice[j+1];
				dice[j+1] = temp;
			}
		}
	}
}


/***********************************************************************************
 * Function: init_array
 * Description: populates a dynamic array with 0's
 * Parameters: int* array, int length
 * Pre-conditions: must have access to the array and its length
 * Post-conditions: changes the values within the array
 * ********************************************************************************/

void init_array(int* array, int length) {
	for (int i = 0; i < length; i++) {
		array[i] = 0;
	}
}


/**************************************************************************
 * Function: get_num_players
 * Description: gets a valid int for number of players from the user
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: must return a positive int value of at least 2
 * ***********************************************************************/

int get_num_players() {
	int num_players = 0;
	string check_num = "";
	bool flag = false;

	do {
		cout << "How many players are there? ";
		getline(cin, check_num);
		if (is_int(check_num) == true) {
			num_players = string_to_int(check_num);
			if (num_players >= 2) {
				flag = true;	
			}
		}
	} while (flag == false);

	return num_players;
}


/****************************************************************************
 * Function: print_scores
 * Description: prints the score for each player on the scoreboard
 * Parameters: int* scoreboard, int num_players
 * Pre-conditions: inputs must include a dynamic array that holds the players' scores and the number of players (length of array)
 * Post-conditions: must print values at each index
 * *************************************************************************/

void print_scores(int* scoreboard, int num_players) {
	cout << endl << "SCOREBOARD:" << endl;
	for (int i = 0; i < num_players; i++) {
		cout << "Player " << (char) (i+65) << ": " << scoreboard[i] << endl;
	}
}


/*****************************************************************************
 * Function: check_ones_and_fives
 * Description: checks an array for 1's and 5's, length does not necessarily have to match
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditios: must return an int
 * **************************************************************************/

int check_ones_and_fives(int* dice, int length) {
	int count1 = 0;
	int count5 = 0;

	for (int i = 0; i < length; i++) {
		if (dice[i] == 1) {
			count1++;
		}
		else if (dice[i] == 5) {
			count5++;
		}
	}

	if (count1 > 0 || count5 > 0) {
		return (count1 + count5);
	}

	return 0;
}


/*****************************************************************************
 * Function: ones_and_fives
 * Description: adds up the point values of 1's and 5's in an array of dice
 * Parameters: int* dice, int length
 * Pre-conditions: inputs must include a dynamic array of dice and its length
 * Post-conditions: must return an int point value
 * ***************************************************************************/

int ones_and_fives(int* dice, int length) {
	int points = 0;
	int count1 = 0;
	int count5 = 0;

	for (int i = 0; i < length; i++) {
		if (dice[i] == 1) {
			count1++;
		}
		else if (dice[i] == 5) {
			count5++;
		}
	}

	if ((count1 + count5) != length) {
		return 0;
	}

	points = (count1 * 100) + (count5 * 50);

	return points;
}


/*****************************************************************************
 * Function: score_triplet
 * Description: returns the point value associated with a certain triplet
 * Parameters: int value
 * Pre-conditions: input must be the value of the dice that form a triplet
 * Post-conditions: must return the point value of that triplet
 * **************************************************************************/

int score_triplet(int value) {
	if (value == 1 || value == 3) {
		return 300;
	}
	else if (value == 2) {
		return 200;
	}
	else if (value == 4) {
		return 400;
	}
	else if (value == 5) {
		return 500;
	}
	else if (value == 6) {
		return 600;
	}
	else {
		return 0;
	}
}


/*******************************************************************************
 * Function: subset_ones_fives
 * Description: calculates the points of the extra 1's and 5's of a mixed combo
 * Parameters: int* subset, int subset_len
 * Pre-conditions: must have access to the subset of extras and its length
 * Post-conditions: must return a point value 
 * ****************************************************************************/

int subset_ones_fives(int* subset, int subset_len) {
	int count1 = 0;
	int count5 = 0;
	int points = 0;

	for (int i = 0; i < subset_len; i++) {
		if (subset[i] == 1) {
			count1++;
		}
		else if (subset[i] == 5) {
			count5++;
		}
	}

	points = (count1 * 100) + (count5 * 50);

	return points;
}


/***************************************************************************
 * Function: triplet
 * Description: finds a triplet in an array of dice and returns its point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a sorted dynamic array and its length (at least 3)
 * Post-conditions: must return a point value (int)
 * ************************************************************************/

int triplet(int* dice, int length) {
	for (int i = 0; i < length; i++) {
		if ((dice[i] == dice[i+1] && dice[i] == dice[i+2]) 
		    && ((i+1) < length && (i+2) < length)) {
			int value = dice[i];
			int score = score_triplet(value);
			return score;
		}
	}

	return 0;
}


/**************************************************************************
 * Function: triplet_and_1
 * Description: finds a triplet and returns the score of that triplet plus the extra one or five tacked on
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a sorted dynamic array and its length (at least 4)
 * Post-conditions: must return a point value (int)
 * ***********************************************************************/

int triplet_and_1(int* dice, int length) {
	if (triplet(dice, length) != 0) {
		int points = triplet(dice, length);
		for (int i = 0; i < length; i++) {

			if ((dice[i] == dice[i+1] && dice[i] == dice[i+2]) 
			   && ((i+1) < length && (i+2) < length)) {
				int subset_len = (length - 3), index = 0;
				int* subset = new int[subset_len];

				for (int j = 0; j < length; j++) {
					if (j != i && j != (i+1) && j != (i+2)) {
						subset[index] = dice[j];
						index++;
					}
				}

				if (check_ones_and_fives(subset, subset_len) >= 1) {
					points += subset_ones_fives(subset,subset_len);
					delete [] subset;
					return points;
				}
				else {
					delete [] subset;
					return 0;
				}
			}
		}
	}
}


/****************************************************************************
 * Function: four_in_a_row
 * Description: finds four of the same dice in an array and returns its point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a sorted dynamic array and its length (at least 4)
 * Post-conditions: must return a point value (int)
 * *************************************************************************/

int four_in_a_row(int* dice, int length) {
	for (int i = 0; i < length; i++) {
		if (dice[i] == dice[i+1] && (i+1) < length 
		    && dice[i] == dice[i+2] && (i+2) < length
		    && dice[i] == dice[i+3] && (i+3) < length) {
			return 1000;
		}
	}

	return 0;
}


/******************************************************************************
 * Function: triplet_and_2
 * Description: finds a triplet and two extra 1's or 5's and returns the point value of the combo
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (at least 5)
 * Post-conditions: must return a point value (int) 
 * ***************************************************************************/

int triplet_and_2(int* dice, int length) {
	if (triplet(dice, length) != 0) {
		int points = triplet(dice, length);
		for (int i = 0; i < length; i++) {

			if ((dice[i] == dice[i+1] && dice[i] == dice[i+2])
			   && ((i+1) < length && (i+2) < length)) {
				int subset_len = (length - 3), index = 0;
				int* subset = new int[subset_len];

				for (int j = 0; j < length; j++) {
					if (j != i && j != (i+1) && j != (i+2)) {
						subset[index] = dice[j];
						index++;
					}
				}

				if (check_ones_and_fives(subset, subset_len) >= 2) {
					points += subset_ones_fives(subset,subset_len);
					delete [] subset;
					return points;
				}
				else {
					delete [] subset; 
					return 0;
				}
			}
		}
	}
}


/*************************************************************************
 * Function: four_and_1
 * Description: finds the four and a row and extra 1 or 5 in an array and returns the associated point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (at least 5)
 * Post-conditions: must return a point value (int)
 * **********************************************************************/

int four_and_1(int* dice, int length) {
	if (four_in_a_row(dice, length) != 0) {
		int points = four_in_a_row(dice, length);
		for (int i = 0; i < length; i++) {

			if ((dice[i] == dice[i+1] && dice[i] == dice[i+2]
			   && dice[i] == dice[i+3])) {
				int subset_len = (length - 4);
				int* subset = new int[subset_len];
				int index = 0;

				for (int j = 0; j < length; j++) {
					if (j != i && j != (i+1) && j != (i+2)
					    && j != (i+3)) {
						subset[index] = dice[j];
						index++;
					}
				}

				if (check_ones_and_fives(subset, subset_len) >= 1) {
					points += subset_ones_fives(subset,subset_len);
					delete [] subset;
					return points;
				}
				else {
					delete [] subset;
					return 0;
				}
			}
		}
	}
}

/****************************************************************************
 * Function: five_in_a_row
 * Description: finds five of the same dice in an array and returns the point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (at least 5)
 * Post-conditions: must return a point value (int)
 * *************************************************************************/

int five_in_a_row(int* dice, int length) {
	for (int i = 0; i < length; i++) {
		if (dice[i] == dice[i+1] && dice[i] == dice[i+2]
		    && dice[i] == dice[i+3] && dice[i] == dice[i+4]
		    && (i+1) < length && (i+2) < length
		    && (i+3) < length && (i+4) < length) {

			return 2000;
		}
	}

	return 0;
}


/****************************************************************************
 * Function: four_and_2
 * Description: returns point value for an array of dice with four in a row and two extra 1's or 5's
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (should be 6)
 * Post-conditions: must return a point value (int)
 * **************************************************************************/

int four_and_2(int* dice, int length) {
	if (four_in_a_row(dice, length) != 0) {
		int points = four_in_a_row(dice, length);

		for (int i = 0; i < length; i++) {
			if (dice[i] == dice[i+1] && dice[i] == dice[1+2] 
			   && dice[i] == dice[i+3]) {
				int subset_len = (length - 4);
				int* subset = new int[subset_len];
				int index = 0;

				for (int j = 0; j < length; j++) {
					if (j != i && j != (i+1) && j != (i+2)
					    && j != (i+3)) {
						subset[index]  = dice[j];
						index++;
					}
				}

				if (check_ones_and_fives(subset, subset_len) >= 2) {
					points += subset_ones_fives(subset,subset_len);
					delete [] subset;
					return points;
				}
				else {
					delete [] subset;
					return 0;
				}
			}
		}
	}
}


/***************************************************************************
 * Function: five_and_1
 * Description: returns the point value of a five in a row and extra 1 or 5
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a point value (int)
 * ***********************************************************************/

int five_and_1(int* dice, int length) {
	int points = 0;

	if (five_in_a_row(dice, length) != 0) {
		points = five_in_a_row(dice, length);
		if (dice[0] == 5 && dice[5] == 6) {
			points += 50;    //the only time 5 will be in front
		}
		else if (dice[0] == 1 && dice[0] != dice[1]) {
			points += 100;    //assuming there's a 1 in front
		}
		else if (dice[5] == 5 && dice[5] != dice[4]) {
			points += 50;     //assuming there's a 5 at the end
		}
		else {
			return 0;
		}
		return points;
	}

	return 0;
}


/****************************************************************************
 * Function: six_in_a_row
 * Description: finds six of the same dice in an array and returns the point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a point value (int)
 * **************************************************************************/

int six_in_a_row(int* dice, int length) {
	if (dice[0] == dice[1] && dice[0] == dice[2] && dice[0] == dice[3] 
	    && dice[0] == dice[4] && dice[0] == dice[5]) {
		return 3000;
	}

	return 0;
}


/*****************************************************************************
 * Function: straight
 * Description: looks for 1-6 straight in an array of dice and returns the points
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * ***************************************************************************/

int straight(int* dice, int length) {
	int straight[6] = {1, 2, 3, 4, 5, 6};  
	//won't need to delete because on stack in this stack frame, will collapse

	for (int i = 0; i < length; i++) {
		if (dice[i] != straight[i]) {
			return 0;
		}
	}

	return 1500;
}


/******************************************************************************
 * Function: three_pairs
 * Description: looks for 3 pairs in an array and returns the point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a point value (int) 
 * ***************************************************************************/

int three_pairs(int* dice, int length) {
	if (dice[0] == dice[1] && dice[0] != dice[2]
	    && dice[2] == dice[3] && dice[2] != dice[2] != dice[4] 
	    && dice[4] == dice[5] && dice[4] != dice[3]) {

		return 1500;
	}

	return 0;
}


/*******************************************************************************
 * Function: two_triplets
 * Description: looks for two triplets in an array and returns the point value
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a point value (int)
 * *****************************************************************************/

int two_triplets(int* dice, int length) {
	if (dice[0] == dice[1] && dice[0] == dice[2] && dice[0] != dice[3]
	    && dice[3] == dice[4] && dice[3] == dice[5]) {
		return 2500;
	}

	return 0;
}


/******************************************************************************
 * Function: four_and_pair
 * Description: looks for a pair and a four in a row in an array of dice and returns the point value
 * Parameter: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a point value (int) 
 * ****************************************************************************/

int four_and_pair(int* dice, int length) {
	if (dice[1] != dice[2]) {
		if (four_in_a_row(dice, length) != 0 && dice[0] == dice[1]) {
			return 1500;
		}
	}
	else if (dice[3] != dice[4]) {
		if (four_in_a_row(dice, length) != 0 && dice[4] == dice[5]) {
			return 1500;	
		}
	}

	return 0;
}


/*******************************************************************************
 * Function: check15
 * Description: checks if an array is all 1's or all 5's
 * Parameters: int* dice, int length
 * Pre-conditions: input must be an array and its length
 * Post-conditions: must return a int (1 for all 1's, 5 for all 5's, else 0)
 * *****************************************************************************/

int check15(int* dice, int length) {
	bool flag1 = true;
	bool flag5 = true;

	for (int i = 0; i < length; i++) {
		if (dice[i] != 1) {
			flag1 = false;
		}
		if (dice[i] != 5) {
			flag5 = false;
		}
	}

	if (flag1 == true && flag5 == false) {
		return 1;
	}
	else if (flag5 == true && flag1 == false) {
		return 5;
	}
	else {
		return 0;
	}
}


/*******************************************************************************
 * Function: special_triplet_2
 * Description: finds a triplet and 2 extra 1's and 5's in a special array of only 1's or only 5's
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * ****************************************************************************/

int special_triplet_2(int* dice, int length) {
	int value = check15(dice, length);	
	int points = 0;

	if (triplet(dice, length) != 0) {
		points = triplet(dice, length);
		if (value == 1) {
			points += 200;   //for the extra two 1's
		}
		else if (value == 5) {
			points += 100;    //for the extra two 5's
		}
		return points;
	}

	return 0;
}


/********************************************************************************
 * Function: special_four_1
 * Description: finds a four in a row and an extra 1 or 5 in a special array composed of soley 1's or soley 5's
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * *****************************************************************************/

int special_four_1(int* dice, int length) {
	int value = check15(dice, length);
	int points = 0;

	if (four_in_a_row(dice, length) != 0) {
		points = four_in_a_row(dice, length);
		if (value == 1) {
			points += 100;    //for the extra 1
		}
		else if (value == 5) {
			points += 50;     //for the extra 5
		}

		return points;
	}

	return 0;
}


/****************************************************************************
 * Function: special_four_2
 * Description: finds a four in a row and 2 extra 1's or 5's in a special array composed of solely 1's or solely 5's
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * *************************************************************************/

int special_four_2(int* dice, int length) {
	int value = check15(dice, length);
	int points = 0;

	if (four_in_a_row(dice, length) != 0) {
		points = four_in_a_row(dice, length);
		if (value == 1) {
			points += 200;    //for the 2 extra 1's
		}
		else if (value == 5) {
			points += 100;    //for the extra 2 5's
		}
		return points;
	}

	return 0;
}


/******************************************************************************
 * Function: special_five_1
 * Description: finds a five in a row and an extra 1 or 5 in a special array composed of solely 1's or solely 5's
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * ***************************************************************************/

int special_five_1(int* dice, int length) {
	int value = check15(dice, length);
	int points = 0;

	if (five_in_a_row(dice, length) != 0) {
		points = five_in_a_row(dice, length);
		if (value == 1) {
			points += 100;   //for the extra 1
		}
		else if (value == 5) {
			points += 50;   //for the extra 5
		}
		return points;
	}

	return 0;
}


/********************************************************************************
 * Function: scores_len4
 * Description: finds and returns the score for arrays of length 4
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (4)
 * Post-conditions: must return a point value (int)
 * *****************************************************************************/

int scores_len4(int* dice, int length) {
	int points = 0;

	if (four_in_a_row(dice, length) != 0) {
		points = four_in_a_row(dice, length);
	}
	else if (triplet_and_1(dice, length) != 0) {
		points = triplet_and_1(dice, length);
	}
	else if (ones_and_fives(dice, length) != 0) {
		points = ones_and_fives(dice, length);
	}

	return points;
}


/******************************************************************************
 * Function: scores_len5
 * Description: finds and returns the score for arrays of length 5
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (5)
 * Post-conditions: must return a point value (int)
 * ***************************************************************************/

int scores_len5(int* dice, int length) {
	int points = 0;

	if (five_in_a_row(dice, length) != 0) {
		points = five_in_a_row(dice, length);
	}
	else if (four_and_1(dice, length) != 0) {
		points = four_and_1(dice, length);
	}
	else if (triplet_and_2(dice, length) != 0) {
		points = triplet_and_2(dice, length);
	}

	return points;
}


/*******************************************************************************
 * Function: scores_special6
 * Description: finds and returns the score for special combinations of arrays of length 6 (straight, three_pairs, two_triplets, four_and_pair)
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a point value (int)
 * ****************************************************************************/

int scores_special6(int* dice, int length) {
	int points = 0;

	if (straight(dice, length) != 0) {
		points = straight(dice, length);
	}
	else if (three_pairs(dice, length) != 0) {
		points = three_pairs(dice, length);
	}
	else if (two_triplets(dice, length) != 0) {
		points = two_triplets(dice, length);
	}
	else if (four_and_pair(dice, length) != 0) {
		points = four_and_pair(dice, length);
	}

	return points;
}


/***********************************************************************************
 * Function: scores_len6
 * Description: finds and returns the score for combinations of arrays of length 6 (four_and_2, five_and_1, six_in_a_row)
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * ********************************************************************************/

int scores_len6(int* dice, int length) {
	int points = 0;

	if (six_in_a_row(dice, length) != 0) {
		points = six_in_a_row(dice, length);
	}
	else if (five_and_1(dice, length) != 0) {
		points = five_and_1(dice, length);
	}
	else if (four_and_2(dice, length) != 0) {
		points = four_and_2(dice, length);
	}

	return points;
}


/**********************************************************************************
 * Function: calc_score56
 * Description: calculates the scores for arrays of length 5 or 6
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int) 
 * ********************************************************************************/

int calc_score56(int* dice, int length) {
	int points = 0;

	if (length == 5) {
		points = scores_len5(dice, length);
	}
	else if (length == 6) {
		if (scores_special6(dice, length) != 0) {
			points = scores_special6(dice, length);
		}	
		else {
			points = scores_len6(dice, length);
		}
	}

	return points;
}


/******************************************************************************
 * Function: print_options_5
 * Description: prints the various scoring options for a special array of length 5 that contains only 1's or only 5's
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: must print options (void)
 * ****************************************************************************/

void print_options_5() {
	cout << "Your scoring options are: " << endl;
	cout << "(1) five in a row" << endl;
	cout << "(2) four in a row and an extra 1 or 5" << endl;
	cout << "(3) a triplet and two extra 1's or 5's" << endl;
	cout << "(4) all individual 1's or 5's" << endl;
}


/*******************************************************************************
 * Function: get_option_5
 * Description: gets a scoring option for a special array of length 5 that is composed of solely 1's or solely 5's
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: must return a valid scoring option (int)
 * ****************************************************************************/

int get_option_5() {
	int valid_option = 0;
	string check_option = "";
	bool flag = false;

	do {
		cout << "Which scoring option would you like to pick? ";
		getline(cin, check_option);
		if (is_int(check_option) == true) {
			valid_option = string_to_int(check_option);
			if (valid_option >= 1 && valid_option <= 4) {
				flag = true;
			}
		}
	} while (flag == false);

	return valid_option;
}


/*****************************************************************************
 * Function: special_scores_5
 * Description: takes the scoring option for a special array of length 5 and calculates the points of the combo the user chose
 * Parameters: int* dice, int length, int option
 * Pre-conditions: inputs must include a dynamic array, its length (5), and the scoring option number the user picked
 * Post-conditions: must return a point value (int) 
 * **************************************************************************/

int special_scores_5(int* dice, int length, int option) {
	int points = 0;

	if (option == 1) {
		points = 2000;
	}
	else if (option == 2) {
		points = special_four_1(dice, length);
	}
	else if (option == 3) {
		points = special_triplet_2(dice, length);
	}
	else if (option == 4) {
		points = ones_and_fives(dice, length);
	}

	return points;
}


/******************************************************************************
 * Function: print_options_6
 * Description: tells the user what options they have for scoring a special array of length 6 that is composed of solely 1's or solely 5's
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: must print to screen (void)
 * ***************************************************************************/

void print_options_6() {
	cout << "Your scoring options are: " << endl;
	cout << "(1) six in a row" << endl;
	cout << "(2) five in a row and an extra 1 or 5" << endl;
	cout << "(3) four in a row and two extra 1's or 5's" << endl;
	cout << "(4) four and a pair" << endl;
	cout << "(5) two triplets" << endl;
	cout << "(6) three pairs" << endl;
	cout << "(7) all individual 1's or 5's" << endl;
}


/**************************************************************************
 * Function: get_option_6
 * Description: gets a valid scoring option from the user for their special array of length 6 composed solely of 1's or solelye 5's
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: must return a valid scoring option (int)
 * ************************************************************************/

int get_option_6() {
	int valid_option = 0;
	string check_option = "";
	bool flag = false;

	do {
		cout << "Which scoring option would you like to pick? ";
		getline(cin, check_option);
		if (is_int(check_option) == true) {
			valid_option = string_to_int(check_option);
			if (valid_option >= 1 && valid_option <= 7) {
				flag = true;
			}
		}
	} while (flag == false);

	return valid_option;
}


/*****************************************************************************
 * Function: special_scores_6
 * Description: takes the user's scoring option and calculates the points for the chosen combination
 * Parameters: int* dice, int length, int option
 * Pre-conditions: inputs must include a dynamic array, its length (6), and the scoring option
 * Post-conditions: must return a point value (int)
 * **************************************************************************/

int special_scores_6(int* dice, int length, int option) {
	int points = 0;

	if (option == 1) {
		points = six_in_a_row(dice, length);
	}
	else if (option == 2) {

		points = special_five_1(dice, length);
	}
	else if (option == 3) {
		points = special_four_2(dice, length);
	}
	else if (option == 4) {
		points = four_and_pair(dice, length);
	}
	else if (option == 5) {

		points = two_triplets(dice, length);
	}
	else if (option == 6) {

		points = three_pairs(dice, length);
	}
	else if (option == 7) {

		points = ones_and_fives(dice, length);
	}

	return points;
}


/*******************************************************************************
 * Function: special_scores
 * Description: gives the user options for scoring their ambiguous dice, takes in their option, and calculates the score for the chosen combination
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (5 or 6)
 * Post-conditions: must return a point value
 * ***************************************************************************/

int special_scores(int* dice, int length) {
	int option = 0;
	int points = 0;

	cout << "Looks like there are multiple ways to score this!" << endl;

	if (length == 5) {
		print_options_5();
		option = get_option_5();
		points = special_scores_5(dice, length, option);
	}

	else if (length == 6) {
		print_options_6();
		option = get_option_6();
		points = special_scores_6(dice, length, option);
	}

	return points;
}


/****************************************************************************
 * Function: calc_score
 * Description: calculates the score for a given array of dice
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a point value (int)
 * *************************************************************************/

int calc_score(int* dice, int length) {
	bubble_sort(dice, length);
	int points = 0;

	if (length < 4) {
		if (triplet(dice, length) != 0) {
			points = triplet(dice, length);
		}
		else if (ones_and_fives(dice, length) != 0) {
			points = ones_and_fives(dice, length);
		}
	}
	else if (length == 4) {
		points = scores_len4(dice, length);
	}
	else if (check15(dice, length) == 1 || check15(dice, length) == 5) {
		points = special_scores(dice, length);
	}
	else {
		points = calc_score56(dice, length);
	}

	return points;
}


/*****************************************************************************
 * Function: check_simple
 * Description: checks if an array contains at least a 1, a 5, or a triplet (checks that it is a point-scoring array) and tells the user
 * Parameters: int* dice, int length
 * Pre-conditions: inputs must include a dynamic arry and its length
 * Post-conditions: must return a bool
 * **************************************************************************/

bool check_simple(int* dice, int length) {
	bool valid_dice = false;

	if (check_ones_and_fives(dice, length) != 0) {
		cout << "You can select out 1's and/or 5's" << endl;
		valid_dice = true;
	}
	if (triplet(dice, length) != 0) {
		cout << "You can select out a triplet" << endl;
		valid_dice = true;
	}
	if (valid_dice == true) {
		return true;
	}
	cout << endl;

	return false;
}


/*****************************************************************************
 * Function: check_4
 * Description: checks an array of length 4 for posssible combinations and tells the user which they can pick
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: must return a bool
 * ***************************************************************************/

bool check_4(int* dice, int length) {
	bool valid_dice = false;

	if (four_in_a_row(dice, length) != 0) {
		cout << "You can select out a four in a row" << endl;
		valid_dice = true;
	}
	if (triplet_and_1(dice, length) != 0) {
		cout << "You can select out a triplet and an extra 1 or 5" << endl;
		valid_dice = true;
	}
	if (valid_dice == true) {
		return true;
	}

	return false;
}


/******************************************************************************
 * Function: check-5
 * Description: checks an array of length 5 for point-scoring combinations and tells the user
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (5)
 * Post-conditions: must return a bool
 * ***************************************************************************/

bool check_5(int* dice, int length) {
	bool valid_dice = false;

	if (triplet_and_2(dice, length) != 0) {
		cout << "You can select out a triplet and two extra 1's and 5's" << endl;
		valid_dice = true;
	}
	if (four_and_1(dice, length) != 0) {
		cout << "You can select out a four in a row and an extra 1 or 5" << endl;
		valid_dice = true;
	}
	if (five_in_a_row(dice, length) != 0) {
		cout << "You can select out five in a row" << endl;
		valid_dice = true;
	}
	if (valid_dice == true) {
		return true;
	}

	return false;
}


/*****************************************************************************
 * Function: check_6
 * Description: checks an array of length 6 for point-scoring combinatons and tells the user
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length
 * Post-conditions: returns a bool
 * **************************************************************************/

bool check_6(int* dice, int length) {
	bool valid_dice = false;

	if (four_and_2(dice, length) != 0) {
		cout << "You can select out four in a row and two extra 1's and 5's" << endl;
		valid_dice = true;
	}
	if (five_and_1(dice, length) != 0) {
		cout << "You can select out five in a row and an extra 1 or 5" << endl;
		valid_dice = true;
	}
	if (six_in_a_row(dice, length) != 0) {
		cout << "You can select out six in a row" << endl;
		valid_dice = true;
	}
	if (valid_dice == true) {
		return true;
	}

	return false;
}


/*******************************************************************************
 * Function: check_combos
 * Description: checks an array of length 6 for special combinations and tells user the possible combos
 * Parameters: int* dice, int length
 * Pre-conditions: input must be a dynamic array and its length (6)
 * Post-conditions: must return a bool
 * ****************************************************************************/

bool check_combos(int* dice, int length) {
	bool valid_dice = false;

	if (four_and_pair(dice, length) != 0) {
		cout << "You can select out a pair and four in a row" << endl;
		valid_dice = true;
	}
	if (two_triplets(dice, length) != 0) {
		cout << "You can select out two triplets" << endl;
		valid_dice = true;
	}	
	if (three_pairs(dice, length) != 0) {
		cout << "You can select out three pairs" << endl;
		valid_dice = true;
	}
	if (straight(dice, length) != 0) {
		cout << "You can select all the dice for a straight flush 1-6" << endl;
		valid_dice = true;
	}
	if (valid_dice == true) {
		return true;
	}

	return false;
}


/**********************************************************************************
 * Function: copy_array
 * Description: copies the values in a dynamic array into another one
 * Parameters: int* original, int length
 * Pre-conditions: need a dynamic array to copy and its length
 * Post-conditions: must return the copy array
 * *******************************************************************************/

int* copy_array(int* original, int length) {
	int* copy = new int[length];
	for (int i = 0; i < length; i++) {
		copy[i] = original[i];
	}

	return copy;
}


/*****************************************************************************
 * Function: check_select
 * Description: checks an array for point-scoring combinations
 * Parameters: int* dice, int length
 * Pre-conditions: int* dice, int length
 * Post-conditions: must return a bool
 * ***************************************************************************/

bool check_select(int* dice, int length) {
	int* dice_copy = copy_array(dice, length);
	bubble_sort(dice_copy, length);
	bool valid_dice = false;

	if (check_simple(dice_copy, length) == true) {
		valid_dice = true;
	}
	if (length >= 4) {
		if (check_4(dice_copy, length) == true) {	
			valid_dice = true;
		}
	}
	if (length >= 5) {
		if (check_5(dice_copy, length) == true) {
			valid_dice = true;
		}
	}
	if (length == 6) {
		if (check_combos(dice_copy, length) == true
		    || check_6(dice_copy, length) == true) {
			valid_dice = true;
		}
	}

	delete [] dice_copy;

	if (valid_dice == true) {
		return true;
	}

	return false;
}


/******************************************************************************
 * Function: get_num_dice
 * Description: gets a valid integer for number of dice to remove from the roll
 * Parameters: int rolled_dice
 * Pre-conditions: input must be an int for number of dice rolled in that roll
 * Post-conditions: must return a valid integer
 * ***************************************************************************/

int get_num_dice(int rolled_dice) {
	string check_num = "";
	int num_dice = 0;
	bool flag = false;

	do {
		cout << "\nHow many dice would you like to remove from the roll? ";
		getline(cin, check_num);
		if (is_int(check_num) == true) {
			num_dice = string_to_int(check_num);
			if (num_dice >= 1 && num_dice <= rolled_dice) {
				return num_dice;
			}	}
	} while (flag == false);
}


/****************************************************************************
 * Function: check_first_last
 * Description: checks for correct formatting of selection input if it's the first or last index
 * Parameters: string selection, int dice_rolled, int index
 * Pre-conditions: inputs must include a string, an int for number of dice that were rolled, and an into to signal first or last index of selection
 * Post-conditions: must return a bool
 * **************************************************************************/

bool check_first_last(string selection, int dice_rolled, int index) {
	int len = selection.length();

	for (int i = 0; i < len; i++) {
		if (index == 0 && i == 0) {
			//checks for correct number and a space after it	
			if ((int) selection[0] >= 49
			    && ((int) selection[0] <= (dice_rolled + 48)
			    && (int) selection[1] == 32)) {
					return true;
			}
		}
		else if (index == (len - 1) && i == (len - 1)) {
			//checks for correct number and space before it
			if ((int) selection[len-1] >= 49
			   && ((int) selection[len-1] <= (dice_rolled + 48) 
			   && (int) selection[len-2] == 32)) {
					return true;
			}
		}
	}

	return false;
}


/*****************************************************************************
 * Function: check_dice_options
 * Description: checks the string check_num for proper format
 * Parameters: string selection, int dice_rolled
 * Pre-conditions: inputs must include a string and an int for number of dice that were rolled in that roll
 * Post-conditions: must return a bool
 * **************************************************************************/

bool check_dice_options(string selection, int dice_rolled) {
	if (selection.length() == 0) {
		return false;
	}

	for (int i = 0; i < selection.length(); i++) {
		//enter conditional if find a number between 1-6 (inclusive)
		if ((int) selection[i] >= 49 && (int) selection[i] <= 54) {
			//if first index, check only for # and space after
			if (i == 0) {
				if (check_first_last(selection, \
				dice_rolled, 0) == false) {
					return false;
				}
			}
			//if last index, check only for # and space before
			else if (i == (selection.length() - 1)) {
				if (check_first_last(selection, dice_rolled, \
				(selection.length() - 1)) == false) {
					return false;
				}
			}
			//else check for space in front and behind and correct #
			else {
				if (selection[i-1] != 32 || selection[i+1] != 32
				    || (int) selection[i] < 49 
				    || ((int) selection[i] > (dice_rolled + 48)
				    && (int) selection[i] != 32)) {
						return false;
				}
			}
		} 

		else if ((int) selection[i] != 32)  {
			return false;
		}
	}

	return true;
}


/*****************************************************************************
 * Function: num_chosen
 * Description: counts the number of unique dice the user selected out
 * Parameters: string selection, int num_dice
 * Pre-conditions: input must be a string with valid dice options in them and an int for number of dice the user said they wanted to pick out
 * Post-conditions: returns the count of number of dice they chose
 * **************************************************************************/

int num_chosen(string selection, int num_dice, int dice_rolled) {
	int dice_nums[6] = {1, 2, 3, 4, 5, 6};
	int len = selection.length();
	int count = 0;

	for (int i = 0; i < len; i++) {  //iterate thru selection
		if ((int) selection[i] >= 49   //find dice number
		    && (int) selection[i] <= (dice_rolled + 48)) {
			for (int j = 0; j < 6; j++) {
				if ((int) (selection[i] - 48) == dice_nums[j]) {
					dice_nums[j] = 0;
					count++;
				}
			}
		}
	}

	return count;
}


/******************************************************************************
 * Function: get_dice_options
 * Description: gets the dice options the user wants to select out in a string
 * Parameters: int num_dice, int dice_rolled
 * Pre-conditions: inputs must include an int for number of dice user intends to select out and and int for number of dice rolled
 * Post-conditions: must return a string of valid selections
 * ***************************************************************************/

string get_dice_options(int num_dice, int dice_rolled) {
	string selection = "";
	bool valid_options = false;

	do {
		cout << "\nPlease enter the dice you would like to remove.\n";
		cout << "Enter a space after each number. Example: 1 3 6" << endl;
		getline(cin, selection);

		bool check = check_dice_options(selection, dice_rolled);

		if (check == true) {
			if (num_chosen(selection, num_dice, \
			dice_rolled) == num_dice) {
				valid_options = true;
			}
		}
	} while (valid_options == false);

	return selection;
}


/*******************************************************************************
 * Function: convert_store
 * Description: takes the dice the user selected out and stores the values in another array called chosen_dice
 * Parameters: int* dice, int* chosen_dice, string selection
 * Pre-conditions: inputs must be a dynamic array of available dice just rolled, a dynamic array not yet filled, and a string for user's chosen dice selections
 * Post-conditions: must add dice values to chosen_dice
 * *****************************************************************************/

void convert_store(int* dice, int* chosen_dice, string selection) {
	int dice_value = 0;
	int dice_number = 0;
	int index = 0;
	string substring = "";

	for (int i = 0; i < selection.length(); i++) {
		if ((int) selection[i] >= 49 && (int) selection[i] <= 54) {
			substring = selection[i];
			dice_number = string_to_int(substring);
			dice_number -= 1;
			dice_value = dice[dice_number];
			chosen_dice[index] = dice_value;
			index++;
		}
	}
}


/*****************************************************************************
 * Function: select_dice
 * Description: allows user to select out dice from a roll, stores the dice values in chosen_dice, and checks if the selected dice is a valid combo
 * Parameters: int* dice, int* chosen_dice, int dice_rolled, int num_dice
 * Pre-conditions: inputs must include the array of available dice to choose from , an array to store selected dice values, an int for number of dice rolled, and and int for number of dice user intends to select
 * Post-conditions: must store dice values in chosen_array and return true if selection was successful
 * **************************************************************************/

bool select_dice(int* dice, int* chosen_dice, int dice_rolled, int num_dice) {
	string selection = "";
	bool valid_selection = false;

	selection = get_dice_options(num_dice, dice_rolled);
	convert_store(dice, chosen_dice, selection);
	int check = calc_score(chosen_dice, num_dice);

	if (check != 0) {
		valid_selection = true;
	}
	if (valid_selection == true) {
		return true;
	}
	else {
		return false;
	}
}


/*******************************************************************************
 * Function: ask_roll_again
 * Description: asks the user if they would like to roll again
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: returns a bool
 * *****************************************************************************/

bool ask_roll_again() {
	string check_answer = "";
	int answer = 0;
	bool flag = false;

	do {
		cout << endl << "Would you like to roll again?" << endl;
		cout << "Enter (0) for No, (1) for Yes: ";

		getline(cin, check_answer);

		if (is_int(check_answer) == true) {
			answer = string_to_int(check_answer);
			if (answer == 1 || answer == 0) {
				flag = true;
			}
		}
	} while (flag == false);

	if (answer == 0) {
		return false;
	}

	return true;
}


/*********************************************************************************
 * Function: reroll
 * Description: determines if the user has to or wants to roll again
 * Parameters: int* scoreboard, int index, int running_total, int dice_rolled
 * Pre-conditions: must have access to the scoreboard at the player's index, their running total, and the number of dice they have left to roll
 * Post-conditions: must return a bool
 * *******************************************************************************/

bool reroll(int* scoreboard, int index, int running_total, int & dice_rolled) {
	if ( scoreboard[index] == 0 && running_total < 500
	    && dice_rolled >= 0) {  //automatic reroll if not yet on scoreboard
		return true;
	}
	else if ((scoreboard[index] == 0 && running_total > 500)
		|| (scoreboard[index] != 0 && dice_rolled >= 0)) {
		bool ask_reroll = ask_roll_again();

		if (ask_reroll == true) {
			if (dice_rolled == 0) {
				dice_rolled = 6;
			}
			return true;
		}
		else {
			return false;
		}
	}
}


/*****************************************************************************
 * Function: roll_dice
 * Description: provides random dice values (1-6) for a certain number of dice
 * Parameters: int* dice, int dice_rolled
 * Pre-conditions: inputs must be a dynamic array for randomized values to fill and an int for the index to stop at
 * Post-conditions: text to screen (void)
 * **************************************************************************/

void roll_dice(int* dice, int dice_rolled) {
	cout << "Press enter to roll!" << endl;
	while (cin.get() != '\n');
	cout << endl << "You have rolled the following: " << endl;

	for (int i = 0; i < dice_rolled; i++) {
		dice[i] = (rand() % 6) + 1;
		cout << "Dice " << (i + 1) << " : " << dice[i] << endl;
	}
}


/*********************************************************************************
 * Function: take_turn
 * Description: allows a player to take their turn (roll dice, select dice, accumulate points in running_total)
 * Parameters: int* scoreboard, int* dice, int & running_total
 * Pre-conditions: must have access to scoreboard array, dice array, and running_total
 * Post-conditions: must return a bool to signal if turn was successful (no Farkle)
 * ******************************************************************************/

bool take_turn(int* scoreboard, int index, int* dice, int & running_total) {
	int dice_rolled = 6, num_dice = 0; 
	bool roll_again = true, result = false;

	do {
		roll_dice(dice, dice_rolled);
		if (check_select(dice, dice_rolled) == false) {
			cout << endl << "Oh no! You Farkled!" << endl << endl;
			return false;
		}

		int* chosen_dice;

		do {
			num_dice = get_num_dice(dice_rolled);
			chosen_dice = new int[num_dice];
			init_array(chosen_dice, num_dice);

			result = select_dice(dice, chosen_dice, dice_rolled, num_dice);

			if (result == false) {
				delete [] chosen_dice;
			}
		} while (result == false);

		dice_rolled -= num_dice;
		running_total += calc_score(chosen_dice, num_dice);
		cout << endl << "Your running total is: " << running_total << endl;

		roll_again = reroll(scoreboard, index, running_total, dice_rolled);
		delete [] chosen_dice;
	} while (roll_again == true);

	return true;
}


/****************************************************************************
 * Function: add_to_score
 * Description: adds running_total to scoreboard depending on whether player needs to reach 500 yet or not
 * Parameters: int & running_total, int* scoreboard, int index
 * Pre-conditions: inputs must include the running total to be added, the scoreboard, and the index at which to add the score
 * Post-conditions: changes score at a certain index in scoreboard
 * **************************************************************************/

void add_to_score(int & running_total, int* scoreboard, int index) {
	if (scoreboard[index] == 0) {
		if (running_total >= 500) {
			scoreboard[index] += running_total;
		}
		else {
			cout << endl << "You don't have 500 points yet!" << endl;
		}
	}
	else if (scoreboard[index] != 0) {
		scoreboard[index] += running_total;
	}
}


/*****************************************************************************
 * Function: final_round
 * Description: allows all but the player who first reached 10000 points to play one more turn
 * Parameters: int* scoreboard, int num_players, int* dice, int first_to_10k
 * Pre-conditions: must have access to scoreboard, number of players, dice array, and the index that doesn't get to play another turn
 * Post-conditions: changes the scoreboard
 * **************************************************************************/

void final_round(int* scoreboard, int num_players, int* dice, int first_to_10k) {
	for (int i = 0; i < num_players; i++) {
		if (i != first_to_10k) {
			cout << "\nPlayer " << ((char) (i+65)) << "'s Turn!" << endl;
			int running_total = 0;

			bool turn_result = take_turn(scoreboard, i, dice, running_total);
			if (turn_result == true) {
				add_to_score(running_total, scoreboard, i);
			}

			print_scores(scoreboard, num_players);
		}
	}
}


/*****************************************************************************
 * Function: play_game
 * Description: simulates the gameplay of Farkle from the 1st through final rounds
 * Parameters: int* scoreboard, int* dice, int num_players
 * Pre-conditoins: must have access to the scoreboard, the dice array, and number of players
 * Post-conditions: changes the scoreboard and dice arrays as game moves along
 * ****************************************************************************/

void play_game(int* scoreboard, int* dice, int num_players) {
	int first_to_10k = 0;
	bool final_yet = false;

	do {
		for (int i = 0; i < num_players; i++) {
			cout << "\nPlayer " << ((char) (i+65)) << "'s Turn!" << endl;
			int running_total = 0;

			bool turn_result = take_turn(scoreboard, i, dice, running_total);
			if (turn_result == true) {
				add_to_score(running_total, scoreboard, i);
				running_total = 0;
			}

			print_scores(scoreboard, num_players);

			if (scoreboard[i] >= 10000) {
				final_yet = true;
				first_to_10k = i;
			}
		}
	} while (final_yet == false);

	final_round(scoreboard, num_players, dice, first_to_10k);
}


/*****************************************************************************
 * Function: declare_winner
 * Description: finds the highest score and prints who the winner is
 * Parameter: int* scoreboard, int num_players
 * Pre-conditions: must have access to dynamic array scoreboard and its length (aka number of players)
 * Post-conditions: prints who the winner is, doesn't change scoreboard
 * **************************************************************************/

void declare_winner(int* scoreboard, int num_players) {
	int highest_score = scoreboard[0];
	int winner = 0;

	for (int i = 0; i < num_players; i++) {
		if (scoreboard[i] > highest_score) {
			highest_score = scoreboard[i];
			winner = i;
		}
	}

	cout << endl << "The winner is Player " << ((char) (winner + 65)) \
	<< " with a score of " << highest_score << endl;
}



int main() {
	srand(time(NULL));	//seeded random number generator

	int* dice = new int[6];
	init_array(dice, 6);

	int num_players = 0;
	num_players = get_num_players();

	int* scoreboard = new int[num_players];
	init_array(scoreboard, num_players);

	cout << endl << "Let's play Farkle!" << endl;
	play_game(scoreboard, dice, num_players);
	declare_winner(scoreboard, num_players);

	delete [] dice;
	delete [] scoreboard;
	return 0;
}
