#include<fstream>
#include <iostream>
#include<Array>
#include<string>
#include<fcntl.h>
#include <io.h>
#include "Card.h"
#include "Stack.h"
#include "DrawPile.h"
#include "AceStack.h"
#include "BoardStack.h"
#include "Menu.h"
#include "BST.h"
constexpr int G_ROWSTART{ 13 }; //11
constexpr int G_TOPROWSTART{ 2 }; //2
constexpr int G_BOARDWIDTH{ 100 }; //100
constexpr int G_BOARDLENGTH{ 60 }; //60


void resetBoard(std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& board)
{
    for (int r{0}; r < board.size(); ++r)
    {
        for (int c{ 0 }; c < board[r].size(); ++c)
        {
            board[r][c] = ' ';
        }
    }
}

void printMatrix(const std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& boardMatrix)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int r{ 0 }; r < boardMatrix.size(); ++r)
    {
        for (int c{ 0 }; c < boardMatrix[r].size(); ++c)
        {
            if (boardMatrix[r][c] == 'D' || boardMatrix[r][c] == 'H')
                SetConsoleTextAttribute(hConsole, 12); //set console color to red
            std::cout << boardMatrix[r][c];
            SetConsoleTextAttribute(hConsole, 15); //set it back to white
        }
        std::cout << '\n';
    }
}

//void printMatrix(const std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& boardMatrix)
//{
//    system("CLS");
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    for (int r{ 0 }; r < boardMatrix.size(); ++r)
//    {
//        for (int c{ 0 }; c < boardMatrix[r].size(); ++c)
//        {
//            if (isalpha(boardMatrix[r][c]))
//            {
//                if (boardMatrix[r][c] == 'D' || boardMatrix[r][c] == 'H')
//                    SetConsoleTextAttribute(hConsole, 12); //set console color to red
//                if (boardMatrix[r][c] == 'C')
//                {
//                    wprintf(L"\x2664");
//                }
//                if (boardMatrix[r][c] == 'H')
//                {
//                    wprintf(L"\x2665");
//                }
//                if (boardMatrix[r][c] == 'S')
//                {
//                    wprintf(L"\x2663");
//                }
//                if (boardMatrix[r][c] == 'D')
//                {
//                    wprintf(L"\x2666");
//                }
//            }
//            else
//                std::wcout << static_cast<wchar_t>(boardMatrix[r][c]);
//            SetConsoleTextAttribute(hConsole, 15); //set it back to white
//        }
//        std::cout << '\n';
//    }
//}

void writeAceStack(std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& render, AceStack& aceStack, int col)
{
    int row = G_TOPROWSTART;
    if (aceStack.empty())
    {
        for (int r{ row }; r < row + 7; ++r)
        {
            for (int c{ col }; c < col + 8; ++c)
            {
                if (r == row || r == row + 6)
                {
                    if (c == col + 1 || c == col + 6)
                        render[r][c] = '_';
                }
                if (r == row + 1 || r == row + 6)
                {
                    if (c == col || c == col + 7)
                        render[r][c] = '|';
                }
                /******************  IMPLEMENT SUIT VAR FOR ACE STACK  *************************/
                // if (r == row + && c == col + )
                //     render[r][c] = 
            }
        }
    }
    else
    {
        for (int r{ row }; r < row + 7; ++r)
        {
            for (int c{ col }; c < col + 8; ++c)
            {
                if (r == row || r == row + 6)
                    if (c >= col + 1 && c < col + 7)
                        render[r][c] = '_';
                if (r != row)
                    if (c == col || c == col + 7)
                        render[r][c] = '|';
                if (r == row + 1 && c == col + 1)
                    render[r][c] = aceStack.peek().rankString();
                else if (r == row + 6 && c == col + 6)
                    render[r][c] = aceStack.peek().rankString();
                if (r == row + 2 && c == col + 1)
                    render[r][c] = aceStack.peek().suitString();
                else if (r == row + 5 && c == col + 6)
                    render[r][c] = aceStack.peek().suitString();
            }
        }
    }
}
void writeTop(std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& render, std::array<AceStack, 4>& aceStacks, const DrawPile& deck)
{
    //print each ace stack
    for (int i{0}; i < aceStacks.size(); ++i)
    {
        writeAceStack(render, aceStacks[i], 19 + 12 * i);
    }
    //print the deck
    int row = G_TOPROWSTART;
    int col = 67;
    if (!deck.m_drawn.empty())
    {
        //print the shown card
        for (int r{ row }; r < row + 7; ++r)
        {
            for (int c{ col }; c < col + 8; ++c)
            {
                if (r == row || r == row + 6)
                    if (c >= col + 1 && c < col + 7)
                        render[r][c] = '_';
                if (r != row)
                    if (c == col || c == col + 7)
                        render[r][c] = '|';
                if (r == row + 1 && c == col + 1)
                    render[r][c] = deck.peek().rankString();
                else if (r == row + 6 && c == col + 6)
                    render[r][c] = deck.peek().rankString();
                if (r == row + 2 && c == col + 1)
                    render[r][c] = deck.peek().suitString();
                else if (r == row + 5 && c == col + 6)
                    render[r][c] = deck.peek().suitString();
            }
        }
    }
    col = 78;
    if (!deck.m_toDraw.empty())
    {
        for (int r{ row }; r < row + 7; ++r)
        {
            for (int c{ col }; c < col + 8; ++c)
            {
                if (r == row || r == row + 6)
                    if (c >= col + 1 && c < col + 7)
                        render[r][c] = '_';
                if (r != row)
                    if (c == col || c == col + 7)
                        render[r][c] = '|';
            }
        }
    }
}



void writeBoardStack(std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& render, const BoardStack& board, int col)
{
    int row = G_ROWSTART;

    //print the hidden cards first
    for (int i{ 0 }; i < board.hidden.size(); ++i)
    {

        for (int r{ row }; r < row + 3; ++r)
        {
            for (int c{ col }; c < col + 8; ++c)
            {
                if (r == row)
                {
                    if (c >= col + 1 && c < col + 7)
                        render[r][c] = '_';
                }
                else
                {
                    if (c == col || c == col + 7)
                        render[r][c] = '|';
                }
            }
        }
        //move the cursor down a card after printing each hidden card
        /******WARNING MIGHT NEED CHANGE!!!!!!!********************/
        row += 2;
    }

    //print the shown cards
    for (int i{ 0 }; i < board.shown.size(); ++i)
    {
        //the front shown card
        if (i == board.shown.size() - 1)
        {
            for (int r{row}; r < row + 7; ++r) 
            {
                for (int c{col}; c < col + 8; ++c) 
                {
                    if ((r == row + 2) && (c == col + 1) && (i != 0))
                    {
                        //CHANGED HERE
                        render[r - 2][c] = board.shown[i - 1].suitString();
                    }
                    if (r == row || r == row + 6)
                        if (c >= col + 1 && c < col + 7) 
                            render[r][c] = '_';
                    if (r != row) 
                        if (c == col || c == col + 7)
                            render[r][c] = '|';
                    if (r == row + 1 && c == col + 1)
                        render[r][c] = board.shown.back().rankString();
                    else if (r == row + 6 && c == col + 6)
                        render[r][c] = board.shown.back().rankString();
                    if (r == row + 2 && c == col + 1)
                        render[r][c] = board.shown.back().suitString();
                    else if (r == row + 5 && c == col + 6)
                        render[r][c] = board.shown.back().suitString();
                }
            }
        }
        else
        {
            for (int r{ row }; r < row + 3; ++r)
            {
                for (int c{ col }; c < col + 8; ++c)
                {
                    //number
                    if (r == row + 1 && c == col + 1)
                    {
                        render[r][c] = board.shown[i].rankString();
                    }

                    //suit
                    if ((r == row + 2) && (c == col + 1) && (i != 0))
                    {
                        //CHANGED HERE
                        render[r - 2][c] = board.shown[i - 1].suitString();
                    }

                    //card skeleton
                    if (r == row)
                    {
                        if (c >= col + 1 && c < col + 7)
                            render[r][c] = '_';
                    }
                    else
                    {
                        if (c == col || c == col + 7)
                            render[r][c] = '|';
                    }
                }

            }
        }

        //move the cursor down a card after printing each hidden card
        /******WARNING MIGHT NEED CHANGE!!!!!!!********************/
        row += 2;
    }
}

void writeAllBoardStacks(std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH>& render, std::array<BoardStack, 7>& board)
{
    for (int i{ 0 }; i < board.size(); ++i)
    {
        writeBoardStack(render, board[i], i * 10 + 5);
    }
}

void printBoard1(std::array<BoardStack, 7> board, std::array<AceStack, 4>& aceStacks, BoardStack draw)
{
	if (draw.hidden.empty())
		std::cout << "  ";
	else
		std::cout << "X ";
	if (draw.shown.empty())
		std::cout << "  ";
	else
		std::cout << draw.shown.back();
	std::cout << "\n\n";
	for (const auto& b : board)
		std::cout << b << '\n';
}

void printBoard(std::array<BoardStack, 7>& board, std::array<AceStack, 4>& aceStacks, DrawPile& draw)
{
    std::array<std::array<char, G_BOARDWIDTH>, G_BOARDLENGTH> boardMatrix{};
    resetBoard(boardMatrix);
    writeTop(boardMatrix, aceStacks, draw);
    writeAllBoardStacks(boardMatrix, board);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printMatrix(boardMatrix);

}

int Solitaire()
{
    int score{ 0 };
	//instantiate a deck of cards
	Stack<Card> deck(52);
	for (int s{ 0 }; s < 4; ++s)
	{
		for (int r{ 1 }; r <= 13; ++r)
		{
			deck.push(Card(static_cast<SUIT>(s), r));
		}
	}
	deck.shuffle();
	//instantiate 8 CardStacks and 4 AceStacks and a draw pile
	std::array<BoardStack, 7> boardStacks{};
	std::array<AceStack, 4> aceStacks = { AceStack(SUIT::CLUB), AceStack(SUIT::HEART), AceStack(SUIT::SPADE), AceStack(SUIT::DIAMOND)};
	for (int i{ 0 }; i < 7 ; ++i)
	{
		std::vector<Card> hiddenStack(0);
		std::vector<Card> shown(0);
		//deal i amount of hidden cards in the stack, and then give it a shown card
		for (int j{ 0 }; j < i; ++j)
		{
			hiddenStack.push_back(deck.pop());
		}
		shown.push_back(deck.pop());
		boardStacks[i] = BoardStack(hiddenStack, shown);
	}

	//place the rest of the cards in the draw pile
    DrawPile drawPile;
    drawPile.peek();
	while (!deck.empty())
	{
        drawPile.m_toDraw.push(deck.pop());
	}
    while (true)
    {
        system("CLS");
        std::cout << "Score: " << score << '\n';
        printBoard(boardStacks, aceStacks, drawPile);

        /* Inputs go as follows:
         * Inputting "d" draws a card from the pile
         * The rest of the commands follow a "move x y" pattern,
         *      where x is where to pull from, and y is where to put it to
         * a = ace pile --> xy (but if x, must specify the suit (0, 1, 2, 3))
         * DIGIT (ex, 2) = move to the 2nd pile --> y
         * DIGIT#1DIGIT#2 (ex, 52) = move 2 cards from the 5th pile --> x
         * d = draw pile --> x
         *
         */
        std::vector<std::string> input(0);
        std::string temp;
        std::getline(std::cin >> std::ws, temp);
        for (char& c : temp)
            c = std::tolower(c);
        while (temp.find(' ') != std::string::npos)
        {
            input.push_back(temp.substr(0, temp.find(' ')));
            temp = temp.substr(temp.find(' ') + 1);
        }
        input.push_back(temp);
        if (input[0] == "q")
            return -1;
        if (input[0] == "d")
        {
            if (drawPile.m_toDraw.empty())
            {
                score -= 100;
                if (score < 0)
                    score = 0;
            }
            drawPile.draw();
        }
        if (input[0] == "r")
        {
            return Solitaire();
        }
        else if (input[0] == "move")
        {
            if (input.size() >= 3)
            {
                if (input[1] == "d")
                {
                    //move a card from the draw pile to an ace pile
                    if (input[2] == "a")
                    {
                        if (!drawPile.m_drawn.empty())
                        {
                            if (aceStacks[static_cast<int>(drawPile.m_drawn.peek().suit())].canAdd(drawPile.m_drawn.peek()))
                            {
                                Card temp{ drawPile.pull() };
                                aceStacks[static_cast<int>(temp.suit())].add(temp);
                                score += 10;
                            }
                        }
                    }
                    //move a card from the draw pile to a stack
                    else if (isdigit(input[2][0]) && isdigit(input[1][0]) >= 0 && isdigit(input[1][0]) <= 6)
                    {
                        BoardStack& stack{ boardStacks[input[2][0] - '0'] };
                        if (!drawPile.m_drawn.empty() && stack.canAdd(drawPile.m_drawn.peek()))
                        {
                            stack.add(drawPile.pull());
                            score += 5;
                        }
                    }
                }
                else if(input[1][0] == 'a')
                {
                    //move a card from the ace pile to the stack
                    if (isdigit(input[2][0]))
                    {
                        //if the user properly inputted a specific aceStack and it can be added to the board stack, add it
                        if (input[1].length() > 1 && isdigit(input[1][1]) && (input[1][1] - '0') >= 0 && (input[1][1] - '0') <= 3
                            && boardStacks[input[2][0] - '0'].canAdd(aceStacks[input[1][0] - '0'].peek()))
                        {
                            boardStacks[input[2][0] - '0'].add(aceStacks[input[1][1] - '0'].m_stack.pop());
                            score -= 15;
                            if (score < 0)
                                score = 0;
                        }
                    }
                }
                else if (isdigit(input[1][0]) && input[1][0] - '0' >= 0 && input[1][0] - '0' <= 6)
                {
                    //move a pile from the board to an ace pile 
                    if (input[2] == "a")
                    {
                        BoardStack& stack{ boardStacks[input[1][0] - '0'] };
                        if (!stack.shown.empty())
                        {
                            if (aceStacks[static_cast<int>(stack.shown.back().suit())].canAdd(stack.shown.back()))
                            {
                                if (stack.shown.size() == 1) //there will be a new card turned faced up
                                    score += 5;
                                Card temp{ stack.pop() };
                                aceStacks[static_cast<int>(temp.suit())].add(temp);
                                score += 10;
                            }
                        }
                    }
                    //move a pile from the board to another part of the board (input[1][0] is the board to pull from, [1][1] is how many cards, [2][0] is destination)
                    else if (input[1].length() > 1 && isdigit(input[1][1]) && isdigit(input[2][0]) && input[2][0] - '0' >= 0 && input[2][0] - '0' <= 6)
                    {
                        if (input[1].length() >= 3)
                            input[1][1] = input[1][2] + 10;
                        BoardStack& boardToPull{ boardStacks[input[1][0] - '0'] };
                        BoardStack& boardDestination{ boardStacks[input[2][0] - '0'] };
                        //if there is enough cards to pull from and the first card can be added to the destination, follow through
                        if (boardToPull.shown.size() >= input[1][1] - '0' 
                            && boardDestination.canAdd(boardToPull.shown[boardToPull.shown.size() - (input[1][1] - '0')]))
                        {
                            if (boardToPull.shown.size() == (input[1][1] - '0')) //there will be a new card turned faced up
                                score += 5;
                            std::vector<Card> popped(boardToPull.pop(input[1][1] - '0') );
                            boardDestination.add(popped);
                            score += (input[1][1] - '0') * 3;
                        }
                    }
                }
            }
        }
        //then we've won the game
        if (aceStacks[0].m_stack.size() == 13 && aceStacks[1].m_stack.size() == 13 && aceStacks[2].m_stack.size() == 13 && aceStacks[3].m_stack.size() == 13)
        {
            printBoard(boardStacks, aceStacks, drawPile);
            std::ifstream WinStreen{ "WinScreen.txt" };
            // If we couldn't open the input file stream for reading
            if (!WinStreen)
            {
                // Print an error and exit
                std::cerr << "Uh oh, WinStreen.txt could not be opened for reading!\n";
                return score;
            }

            // While there's still stuff left to read
            while (WinStreen)
            {
                // read stuff from the file into a string and print it
                std::string strInput;
                std::getline(WinStreen, strInput);
                std::cout << strInput << '\n';
            }
            break;

        }
    }
    std::ofstream scoreFile{ "Scores.txt", std::ios::app};
    if (!scoreFile)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Scores.txt could not be opened for writing!\n";
        return -1;
    }
    scoreFile << score << '\n';
    return score;

}

int main() {
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //char h{ '_'};
    //std::wstring hello{ L"hello" };
    //std::wcout << hello;
    //std::cout << "normal cout";
    //Solitaire();
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hConsole, 12);
    //std::wcout << L"\x2665";



    Menu* main = new Menu("main", "Main Menu.txt");
    Menu* tut = new Menu("how to play", "Tutorial.txt", main);
    Menu* scoremenu = new Menu("score", "Scores.txt", main);
    main->m_subMenus.push_back(tut);
    main->m_subMenus.push_back(scoremenu);
    Menu* curMenu{ tut };
    std::string menuInput{""};
    while (menuInput != "exit" && curMenu != nullptr)
    {
        curMenu->printMenu();
        if (curMenu->m_name == "score")
        {
            BST scores;
            std::ifstream scoresFile{ "Scores.txt" };
            while (scoresFile)
            {
                std::string s;
                std::getline(scoresFile, s);
                if (std::isdigit(s[0]))
                    scores.insert(std::stoi(s));
            }
            std::vector<int> BSTVect{ scores.toVector() };
            std::cout << "\nSorted Scores : ";
            for (const auto& i : BSTVect)
                std::cout << i << ' ';
            std::cout << "\n\n";
        }
        std::cout << "Enter Option: ";
        std::getline(std::cin, menuInput);
        for (auto& c : menuInput)
            c = std::tolower(c);
        if (curMenu->m_name == "main" && menuInput == "start")
            Solitaire();
        else if (menuInput == "back")
            curMenu = curMenu->m_parent;
        else if(curMenu->hasSub(menuInput))
            curMenu = curMenu->sub(menuInput);
    }

	return 0;
}