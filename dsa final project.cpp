#include <SFML/Graphics.hpp>
#include<iostream>
#include <windows.h>
#include <conio.h>
#include<ctime>
using namespace std;
void border(int** a, int size, bool& gameOver);
class Node
{
public:
    int row, col;
    Node* next;
};

class List
{
private:
    Node* head;
    Node* tail;

public:
    List()
    {
        head = NULL;
        tail = NULL;
    }

    bool isempty()
    {
        if (head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void traverse()
    {
        if (isempty())
        {
            cout << "empty list" << endl;
        }
        else
        {
            Node* p = head;
            while (p != NULL)
            {
                cout << "* ";
                p = p->next;
            }
        }
    }
    //========================================
    void insert_begin(int r, int c)
    {
        Node* p = new Node;
        p->row = r;
        p->col = c;
        p->next = NULL;

        if (isempty())
        {
            head = p;
            tail = p;
        }
        else
        {
            p->next = head;
            head = p;
        }
    }

    void insert_end(int r, int c)
    {
        Node* p = new Node;
        p->row = r;
        p->col = c;
        p->next = NULL;

        if (isempty())
        {
            head = p;
            tail = p;
        }
        else
        {
            tail->next = p;
            tail = p;
        }
    }

    void delete_begin()
    {
        if (isempty())
        {
            cout << "deletion not possible as list is empty" << endl;
        }
        else
        {
            Node* p = head;
            head = head->next;
            delete p;
        }
    }

    void delete_end()
    {
        if (isempty())
        {
            cout << "deletion not possible as list is empty" << endl;
        }
        else if (head->next == NULL)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
        else
        {
            Node* p = head;
            Node* prev = NULL;
            while (p->next != NULL)
            {
                prev = p;
                p = p->next;
            }
            delete p;
            prev->next = NULL;
            tail = prev;
        }
    }

    int get_head_row()
    {
        return head->row;
    }

    int get_head_col()
    {
        return head->col;
    }
};

void setCursorPosition(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void border(int** a, int size, bool& gameOver)
{
    List snake;
    //   int no = 2;
    int score = 0;
    char input = 'D';
    //   int result;
    int foodRow = 10; // Initial food position
    int foodCol = 10;
    int snakebody = 1;
    // Initialize the snake with initial positions
    snake.insert_begin(10, 5);
    snake.insert_end(10, 6);


    hideCursor();
    while (!gameOver && score <= 10)
    {

        // Draw the border and snake
        for (int row = 1; row <= 20; row++)
        {
            for (int col = 1; col <= 40; col++)
            {
                if (col == 1 || row == 1 || col == 40 || row == 20)
                {
                    setCursorPosition(col, row);
                    cout << "#";
                }
                else if (row == foodRow && col == foodCol)
                {
                    setCursorPosition(col, row);
                    cout << "$";
                }
                else if (row == snake.get_head_row() && col == snake.get_head_col())
                {
                    setCursorPosition(col, row);
                    for (int j = 1;j <= snakebody;j++)
                    {
                        cout << "*";
                    }
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        // Check if the snake collides with the wall
        if (snake.get_head_row() <= 1 || snake.get_head_row() >= size || snake.get_head_col() + (snakebody - 1) <= 1 || snake.get_head_col() + (snakebody - 1) >= 40)
        {
            gameOver = true; // Set gameOver to true
            break; // Exit the game loop
        }

        // Check if the snake eats the food
        if (snake.get_head_row() == foodRow && snake.get_head_col() + (snakebody - 1) == foodCol)
        {
            score++;
            if (foodRow == 19 || foodCol == 39)
            {
                snake.insert_begin(foodRow, foodCol - 1);
            }
            else
            {
                snake.insert_begin(foodRow, foodCol + 1);
            }
            snakebody++;
            foodRow = 1 + (rand() % 16); // Generate new food position
            foodCol = 10 + (rand() % 30);
        }
        else
        {
            // Move the snake
            snake.delete_end();
        }

        // Get user input for snake direction
        if (_kbhit())
        {
            input = _getch();
        }

        // Update snake direction based on user input
        if ((input == 'D' || input == 'd') && snake.get_head_col() <= 39)
        {
            snake.insert_begin(snake.get_head_row(), snake.get_head_col() + 1);
        }
        else if ((input == 'A' || input == 'a') && snake.get_head_col() >= 2)
        {
            snake.insert_begin(snake.get_head_row(), snake.get_head_col() - 1);
        }
        else if ((input == 'W' || input == 'w') && snake.get_head_row() >= 2)
        {
            snake.insert_begin(snake.get_head_row() - 1, snake.get_head_col());
        }
        else if ((input == 'S' || input == 's') && snake.get_head_row() <= 19)
        {
            snake.insert_begin(snake.get_head_row() + 1, snake.get_head_col());
        }

        Sleep(350); // Delay the game loop
    }

    setCursorPosition(0, 22);
    cout << "Game over" << endl;
    cout << "Your score is " << score << endl;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::Texture ss, t, fo;
    ss.loadFromFile("snake.png");
    sf::Sprite sd;
    sd.setTexture(ss);
    sd.setPosition(400, 1);

    t.loadFromFile("text.png");
    sf::Sprite tex;
    tex.setTexture(t);
    tex.setPosition(310, 170);
    tex.setScale(sf::Vector2f(1.1f, 1.1f));

    sf::Font font1, font2;
    if (!font1.loadFromFile("ChrustyRock.ttf"))
    {
        // error...
    }
    sf::Text text1, text2, text3, text4, text5;

    // select the font
    text1.setFont(font1); // font is a sf::Font
    text1.setPosition(10.f, 350.f);
    text1.move(5.f, 5.f);
    sf::Vector2f position = text1.getPosition();
    // set the string to display
    text1.setString("Instructions");

    // set the character size
    text1.setCharacterSize(60); // in pixels, not points!

    // set the color
    text1.setFillColor(sf::Color::Green);

    // set the text style
    text1.setStyle(sf::Text::Bold);


    if (!font2.loadFromFile("Simple.ttf"))
    {
        // error...
    }

    // select the font
    text2.setFont(font2); // font is a sf::Font
    text2.setPosition(10.f, 450.f);
    text2.move(5.f, 5.f);
    //    sf::Vector2f position = text2.getPosition();
    text2.setString(">> Use W,A,S,D keys to move the snake .");
    text2.setCharacterSize(35);

    text2.setFillColor(sf::Color::Yellow);



    text3.setFont(font2); // font is a sf::Font
    text3.setPosition(10.f, 520.f);
    text3.move(5.f, 5.f);
    text3.setString(">> $ is the food.Once it eats the food it gets bigger.");
    text3.setCharacterSize(35);
    text3.setFillColor(sf::Color::Yellow);

    text4.setFont(font2); // font is a sf::Font
    text4.setPosition(10.f, 590.f);
    text4.move(5.f, 5.f);
    text4.setString(">> You score a point.");
    text4.setCharacterSize(35);
    text4.setFillColor(sf::Color::Yellow);

    text5.setFont(font2); // font is a sf::Font
    text5.setPosition(10.f, 660.f);
    text5.move(5.f, 5.f);
    text5.setString(">> You need to score 10 points to win the game.");
    text5.setCharacterSize(35);
    text5.setFillColor(sf::Color::Yellow);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(tex);
        window.draw(sd);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.display();
    }
    //==========================================
    HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);
    int P = 36;
    SetConsoleTextAttribute(
        console_color, P);
    //-----------------------------
//    srand(time(0));
    int size = 20;

    // Dynamically allocate 2D array
    int** a = new int* [size];
    for (int i = 0; i < size; i++)
    {
        a[i] = new int[size];
    }

    // Initialize the array with 0
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            a[i][j] = 0;
        }
    }

    bool isGameOver = false;
    border(a, size, isGameOver);

    // Deallocate the memory
    for (int i = 0; i < size; i++)
    {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}


