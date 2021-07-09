#include<SFML/Graphics.hpp>

class Buddhichal 
{
  private:
    sf::Vector2f viewSize = sf::Vector2f(640,640);
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape board;
    sf::RectangleShape line;
    sf::Vector2i mousePosition;
    sf::CircleShape cir[10];
    sf::Texture mCross;
    sf::Texture boardTexture;
    sf::Texture titleTexture;
    sf::Texture restartTexture;
    sf::Sprite restartSprite;
    sf::Sprite titlesprite;
    sf::Texture bgTexture;
    sf::Sprite cross[10];
    sf::Sprite bgSprite;
    float x,y;//position of first rectangle of board (used for navigation)
    const float w,h;//width and height of small box of board
    bool gameOver;
    bool isDraw;
    char winner;
    static int cirCount;
    static int crossCount;
    char currPlayer;
    void drawBoard();
    void drawRect(float x,float y);
    void setPlayer(float x, float y);
    void drawPlayer();
    void drawLine(int,int,int);
    void processEvents();
    void updateGameBoard();
    void checkWin();
    void checkDraw();
    void restartGame();
    void render();

  public:
    Buddhichal();
    void run();
};
