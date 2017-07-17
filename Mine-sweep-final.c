/****************************************************** MINESWEEPER GAME *******************************************************/
/****************************************************** Coded Ariyan HASAN ************************************************/
/************************************ Reference Websites: google.com and wikipedia.com *****************************************/
/******************** Reference Books: Problem Solving and Design In C, C For Engineering and Scientist ************************/

/**Include Libraries**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/**Definitions**/
#define TRUE 0
#define FALSE 1

/**Global Variables**/
char plot[11][11];
char game_plot[11][11];
int lost = 0;

/**Function prototypes**/
int signup();
int login();
int compare();
int Homescreen();
void open_game();
void create_plot();
void place_mines();
void gaming_plot();
int play_game();
void check_for_mine(int, int);
int check_for_nearby_mines(int, int);
int check_win_game();
void display_plot();
void display_full_plot();
void play_again();

/**Structure Data**/
struct user
{

    char username[20];
    char password[20];
};

/**Main Function**/
void main()
{
    int n;
    menu: ///Create a Start Point
        printf("\t\t\t********** MINESWEEPER GAMES **********\n\n");
        printf("\t\t\t   WELLCOME TO MINESWEEPER GAMES \n\n");                  ///Display Welcome Screen
        printf("\t\t\t***************************************\n");
        printf("\t\tPress 1 for Sign Up \n\t\tPress 2 for Login\n\t\tPress 3 for Help\n\t\t");
    scanf("%d",&n);
    if (n==1)       /// Sign Up
        signup();   ///Go to sign up Function
    else if (n==2)  ///login
        login();    ///Go to login function.
    else if (n==3)  ///Help
    {
        system("cls"); ///Get Rid Of First Screen
        printf("\t\t\t********** MINESWEEPER GAMES **********\n\n");
        printf("\n\nThis is a simple minesweeper game. For privacy purpose you must sign up\nand login to play this game.\n");
        printf("To sign up, press '1' and Enter your User name and password.\n\n");
        printf("After Signing up you must login by pressing '2' with your entered user name and password to go to game menu\n");
        printf("'\nThank you!!!\n\nTo go to Back,Press Enter\n");
        getchar();
        getchar();      /// wait for pressing Enter.
        system("cls");  ///Get Rid of Help Screen.
        goto menu;      ///Go to Welcome Screen Again where creating a menu point.
    }
    else
        system("cls");  ///Get Rid of Welcome Screen and Clear Error Input.
        goto menu;      ///Go to welcome Screen where creating a menu point.
}
/**Signup Function**/
int signup()
{
    struct user signup;                                  /// Declare a structure type Variable.
    FILE *fgame;                                     ///Declare a File type Variables for File.
    fgame=fopen("Signup_File.txt","w");              ///Write or create a file, named Signup_File,which is a text file.
    if(fgame==NULL)
    {
        printf("Error!");
        exit(1);
    }
    getc(stdin);
    printf("\n\t\tEnter username: ");
    gets(signup.username);
    fprintf(fgame,"User Name : %s\n",signup.username);
    printf("\n\t\tEnter a Password: ");
    gets(signup.password);
    fprintf(fgame,"Password : %s\n",signup.password);
    printf("\n\t\tSign up successful\n\nNow you must login to play minesweeper games\n\nPress Enter\n");
    getchar();
    system("cls");
    fclose(fgame);
    return 0;
}


/**Login Function **/
int login()
{
    FILE *fgame;        ///Declare a File type Variables for File.
    struct user login;          /// Declare a structure type Variable and two character type variables
    fgame = fopen("Login_File.txt", "w");             ///Write or create a file, named Login_File,which is a text file.
    if(fgame==NULL){
        printf("Error!");
        exit(1);
   }
    getc(stdin);
    printf("\n\t\tEnter username: ");
    gets(login.username);                              ///Write user  name in the Login_File
    fprintf(fgame,"User Name : %s\n",login.username);   ///Display user name in console
    printf("\n\t\tEnter a Password: ");
    gets(login.password);                                  ///Write Password in the login_File
    fprintf(fgame,"Password : %s\n",login.password);        ///Display user name in console
    fclose(fgame);                                   /// Close Login_File
    compare();                                          ///Go to cmp Function for compare between Login_file and sign up_file

   return (0);
}


/**Compare Function**/
int compare()
{
   FILE *fSignup_File, *fLogin_File;
   int ch1, ch2;

   fSignup_File = fopen("Signup_File.txt", "r");
   fLogin_File = fopen("Login_File.txt", "r");

   if (fSignup_File !=NULL && fLogin_File !=NULL){

        ch1 = getc(fSignup_File);
        ch2 = getc(fLogin_File);

        while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
         ch1 = getc(fSignup_File);
         ch2 = getc(fLogin_File);
      }

      if (ch1 == ch2){
        printf("login Success\n");
        system("cls");
        Homescreen();

      }


      else if (ch1 != ch2)
        printf("\n\t\tInvalid username or password. try again\n");
        getchar();
        system("cls");
        fclose(fSignup_File);
        fclose(fLogin_File);
   }else
        system("cls");
    return 0;
}

///Home_screen Function///
int Homescreen()
{
    int num;
    menu:
        puts("\t\t\t********** Welcome to Minesweeper **********\n\n");
        puts("\n\n");

        printf("\n\t\t\tPress 1 to START GAME\n\t\t\tPress 2 For Instruction: How To Play Minesweeper Game");
        printf("\n\t\t\tPress 3 to EXIT\n");
        printf("\t\t\t****************************************************\n\t\t\t");

    scanf("%d",&num);
    if (num==1){
        open_game();
        system("cls");
    }
    else if(num==2){
        system("cls");
        printf("\t\t\t********** MINESWEEPER GAMES **********\n\n");
        printf("\n\nThe Object: \n\n");
        printf("Find the empty points while avoiding the mines. Clear all the empty points without hitting mine to win the game.\n\n");
        printf("\n\n\n\nHow to Play: \n");
        printf("The rules in Minesweeper are simple:\n\n");
        printf("1. Uncover a mine, and the game ends.\n\n");
        printf("2. Uncover an empty points, and you keep playing.\n\n");
        printf("3. An uncovered empty point show a number, and it tells you how many mines lay hidden in the eight surrounding points-\n\n");
        printf(" that information you use to deduce which nearby squares are safe to click.\n\n");
        printf("4. To select a point on the game plot, enter row and column number with X and Y.\n\n");
        printf("\n\nEnjoy Minesweeping !!!\n");
        printf("\n\nThank you!!!\n\nTo go to Back,Press Enter\n");
        getch();
        system("cls");
        goto menu;

    }
    else if (num==3)
        system("cls");
        printf("\t\t\t********** MINESWEEPER GAMES **********\n\n");
        printf("\nCome again later.\nGood-Bye!!!\n\n");
        getchar();
        exit(EXIT_SUCCESS);
    return 0;

}

/**Open Game Function**/
void open_game()
{
    system("cls");
    lost = 0;                       /// User has not lost yet
    create_plot();                  /// Build both game plots (one for the user to see,and the one with the mines).
    gaming_plot();
    do                      /// Start playing game
    {
    play_game();
    display_plot();
    } while(lost != 1);    /// While the user has not lost, loop continue.
    display_full_plot();            /// Once user is lost, print the plot with all the mines.
    play_again();
}


/**Create_Plot**/
void create_plot()            ///Function used for created board and places random mines
{
    int i, j;
    for(i = 0; i < 11; i++)
        for(j = 0; j < 11; j++)
        plot[i][j] = '.';  ///Assign Character for plot elements.
        place_mines();      ///Place mines in this plot, it remains hidden from user until the game has finished.
}

/**Place_Mines Function**/          ///Places random mines in the plot using rand() function.
void place_mines()
{
    int i, random;


    srand(time(0));                 /// Sending srand() with time(0) so that mine locations are not the same every time the game is played.

    for (i = 1; i < 10; i++)
    {
        random = rand() % (9);       ///define the value of random, randomly wit rand() function.
        plot[random][i] = '*';      ///Assign '*' as a mine randomly into row;
    }

}

/**Gaming_Plot Function**/ ///Assign char '.' for all plot elements
void gaming_plot()
{
    int i, j;
    int row, col;
    printf("\nPLAY! \n\n");

    for(i = 0; i < 11; i++)
        for(j = 0; j < 11; j++)
            game_plot[i][j] = '.';

    printf("   ");
    for(col = 1; col < 10; col++)            ///Display Plot
        printf("%d ", col );

    printf("\n\n");

    for(row = 1; row < 10; row++)

    {
        printf("%d  ", row );
        for(col = 1; col < 10; col++)
        {

            printf("%c ", game_plot[row][col]);
        }

        printf("\n");
    }

}

/**Play Game Function */
int play_game()             ///Take user input for playing of the game
{
    int row_selection = 0, col_selection = 0,nearbymines = 0,constant=0;

    do
    {
        printf("\n\nEnter X for Row & Enter Y for Column\n");
        printf("\nEnter X (1 to 9): ");
        scanf("%d", &row_selection);                          ///Receives data from the user, first the row
        printf("Enter Y (1 to 9): ");                       ///number, then the column number...
        scanf("%d", &col_selection);
    } while(row_selection < 1 || row_selection > 9 || col_selection < 1 || col_selection > 9); /// ^ Checks for any invalid input statements from user.


        check_for_mine(row_selection , col_selection);   /// Checks for nearby mines at every direction from user input location.
                                                            ///  Assigns that location the number of mines found nearby, updating the plot.
        if(lost == 1)
        return 1;

    nearbymines = check_for_nearby_mines(row_selection , col_selection );
    game_plot[row_selection ][col_selection ] = (char)('0' + nearbymines );   ///Assign the value of number of mine surrounding
                                                                                            ///the entered row and column to game plot
                                                                                            ///type cast int constant to char type.
    if(check_win_game() == TRUE)
    {
        display_full_plot();
        printf("\n\nYou've won the game!! Congrats!!\n\n");
        play_again();
    }

    return 0;
}


/**Display Plot Function */
void display_plot()
{
    int row, col;

    system("cls");

    printf("     ");
    for(col = 1; col < 10; col++)
        printf("%d ", col );

    printf("\n\n");
        for(row = 1; row < 10; row++)
    {
         printf(" %d   ", row );
        for(col = 1; col < 10; col++)
        {
            printf("%c ", game_plot[row][col]);
        }

        printf("\n");
    }
}

/**Display full plot Function**/
void display_full_plot()                ///Print the full plot showing mines
{
    int row, col;

    system("cls");
    printf("    ");
    for(col = 1; col < 10; col++)
        printf("%d ", col );

    printf("\n\n");
        for(row = 1; row < 10; row++)
    {
        printf(" %d  ", row );
        for(col = 1; col < 10; col++)
        {
            printf("%c ", plot[row][col]);
        }

        printf("\n");
    }
}


/**Check for Mine Function**/
void check_for_mine(int row_select, int col_select)         ///Check whether user input has selected a mine
{
    if(plot[row_select][col_select] == '*')
    {
        printf("\nYou've hit a mine!\n\nYou lose!\n\n");
        getchar();
        getchar();
        lost = 1;
    }
}

/**Check For Near By Function**/
int check_for_nearby_mines(int row_select, int col_select)     /// Checks for nearby mines at every direction from user input location.
{
    int nearby_mine_count = 0;
    if(plot[row_select][col_select] == '*')
    {
        return 1;
    }
    /// Check for mines to the possible eight sides.
    if(row_select>0 && row_select<10 && col_select < 10 && col_select>0)
    {

        if(plot[row_select + 1][col_select] == '*')     ///Check for mine below
            nearby_mine_count++;

        if(plot[row_select - 1][col_select] == '*')     ///check above
            nearby_mine_count++;

        if(plot[row_select][col_select+1] == '*')       /// check right
            nearby_mine_count++;

        if(plot[row_select][col_select-1] == '*')       ///check left
            nearby_mine_count++;

        if(plot[row_select + 1][col_select-1] == '*')   /// check  below left
            nearby_mine_count++;

        if(plot[row_select + 1][col_select=1] == '*')   /// check  below right
            nearby_mine_count++;

        if(plot[row_select - 1][col_select - 1] == '*') /// check  upper left
            nearby_mine_count++;

        if(plot[row_select - 1][col_select+1] == '*')   ///check upper right
            nearby_mine_count++;
    }

    //printf("\n p %d\n",nearby_mine_count);

    return nearby_mine_count;
}

/** Check Win Game Function**/
int check_win_game()
{
    int row, col;

    for(row = 1; row < 10; row++)
        for(col = 1; col < 10; col++)
        {
            if(game_plot[row][col] == '.' && plot[row][col] != '*')
                return FALSE;
        }

    return TRUE;
}

/**Play Again Function**/
void play_again()                           /// Ask user if they wish to play again.
{
    char ans;

    printf("\n\nWould you like to play again? (y/n) --> ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')     ///toupper converts lowercase letter to uppercase.
    {
        system("cls");
        open_game();
    }

    else
    {
        printf("\n\n\t\tThanks for playing! Bye.\n\n\n");
        (void) getchar();
        exit(EXIT_SUCCESS); ///Exit Program with EXIT_SUCCESS function.
    }
}


