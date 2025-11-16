#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short roundNumbers;
    enGameChoice playerChoice;
    enGameChoice computerChoice;
    enWinner winner;
    string winnerName;
};

struct stGameResult
{
    short gameRound;
    short playerWinTimes;
    short computerWinTimes;
    short drawTimes;
    enWinner whoWin;
    string winnerName;
};

int randomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short howManyRounds()
{
    short rounds = 1;
    do
    {
        cout << "How many rounds? ";
        cin >> rounds;

    } while (rounds < 1 || rounds > 10);

    return rounds;
}

void winnerScreen(enWinner winner)
{
    switch (winner)
    {
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    case enWinner::Player:
        system("color 2F");
        break;

    case enWinner::Draw:
        system("color 6F");
        break;
    }
}

enGameChoice readPlayerChoice()
{
    short choice = 1;
    do
    {
        cout << "Enter your choice: [1] Stone , [2] Paper , [3] Scissor: ";
        cin >> choice;

    } while (choice < 1 || choice > 3);

    return (enGameChoice)choice;
}

enGameChoice getComputerChoice()
{
    return (enGameChoice)randomNumber(1, 3);
}

enWinner whoWonTheRound(stRoundInfo roundInfo)
{
    if (roundInfo.playerChoice == roundInfo.computerChoice)
        return enWinner::Draw;

    switch (roundInfo.playerChoice)
    {
    case enGameChoice::Stone:
        if (roundInfo.computerChoice == enGameChoice::Paper)
            return enWinner::Computer;
        break;

    case enGameChoice::Paper:
        if (roundInfo.computerChoice == enGameChoice::Scissor)
            return enWinner::Computer;
        break;

    case enGameChoice::Scissor:
        if (roundInfo.computerChoice == enGameChoice::Stone)
            return enWinner::Computer;
        break;
    }

    return enWinner::Player;
}

string winnerName(enWinner winner)
{
    string arrWinner[3] = { "Player" , "Computer" , "Draw" };
    return arrWinner[winner - 1];
}

string choiceName(enGameChoice choice)
{
    string arrGameChoice[3] = { "Stone" , "Paper" , "Scissor" };
    return arrGameChoice[choice - 1];
}

void printRoundResults(stRoundInfo roundInfo)
{
    cout << "\n--------- Round [" << roundInfo.roundNumbers << "] ---------\n";
    cout << "Player Choice:   " << choiceName(roundInfo.playerChoice) << endl;
    cout << "Computer Choice: " << choiceName(roundInfo.computerChoice) << endl;
    cout << "Winner:          " << roundInfo.winnerName << "\n\n";
}

enWinner whoWonTheGame(short playerWinTimes, short computerWinTimes)
{
    if (playerWinTimes > computerWinTimes)
        return enWinner::Player;

    if (computerWinTimes > playerWinTimes)
        return enWinner::Computer;

    return enWinner::Draw;
}

stGameResult fillGameResults(short gameRounds, short playerWinTimes, short ComputerWinTimes, short drawTimes)
{
    stGameResult gameResult;

    gameResult.gameRound = gameRounds;
    gameResult.playerWinTimes = playerWinTimes;
    gameResult.computerWinTimes = ComputerWinTimes;
    gameResult.drawTimes = drawTimes;
    gameResult.whoWin = whoWonTheGame(playerWinTimes, ComputerWinTimes);
    gameResult.winnerName = winnerName(gameResult.whoWin);

    return gameResult;
}

string Tabs(short numberOfTabs)
{
    string t = "";
    for (int i = 1; i <= numberOfTabs; i++)
        t += "\t";
    return t;
}

void showGameOver()
{
    cout << Tabs(2) << "---------------------------------------------\n";
    cout << Tabs(2) << "               G A M E  O V E R              \n";
    cout << Tabs(2) << "---------------------------------------------\n";
}

void showFinalResults(stGameResult gameResult)
{
    cout << Tabs(2) << "----------- Final Game Results ---------------\n";
    cout << Tabs(2) << "Rounds played:          " << gameResult.gameRound << "\n";
    cout << Tabs(2) << "Player wins:            " << gameResult.playerWinTimes << "\n";
    cout << Tabs(2) << "Computer wins:          " << gameResult.computerWinTimes << "\n";
    cout << Tabs(2) << "Draws:                  " << gameResult.drawTimes << "\n";
    cout << Tabs(2) << "Game Winner:            " << gameResult.winnerName << "\n";

    winnerScreen(gameResult.whoWin);
}

void resetScreen()
{
    system("cls");
    system("color 0F");
}

stGameResult playGame(short roundsCount)
{
    stRoundInfo roundInfo;

    short playerWinTimes = 0, computerWinTimes = 0, drawTimes = 0;

    for (int gameRound = 1; gameRound <= roundsCount; gameRound++)
    {
        roundInfo.roundNumbers = gameRound;
        roundInfo.playerChoice = readPlayerChoice();
        roundInfo.computerChoice = getComputerChoice();
        roundInfo.winner = whoWonTheRound(roundInfo);
        roundInfo.winnerName = winnerName(roundInfo.winner);

        if (roundInfo.winner == enWinner::Draw)
            drawTimes++;
        else if (roundInfo.winner == enWinner::Computer)
            computerWinTimes++;
        else
            playerWinTimes++;

        printRoundResults(roundInfo);

        
        winnerScreen(roundInfo.winner);
        
    }

    return fillGameResults(roundsCount, playerWinTimes, computerWinTimes, drawTimes);
}

void StartGame()
{
    char playAgain = 'Y';

    do
    {
        resetScreen();
        stGameResult gameResult = playGame(howManyRounds());
        showGameOver();
        showFinalResults(gameResult);

        cout << "\n\nDo you want to play again? Y/N: ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
