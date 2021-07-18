#include<SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Buddhichal 
{
  private:
    sf::Vector2f viewSize;
    sf::RenderWindow window;
    float x,y;//position of first rectangle of board (used for navigation)
    const float w,h;//width and height of small box of board
    sf::CircleShape* dragCir;
    sf::Sprite* dragCross;
    bool gameOver;
    bool isDragging;
    bool isDraw;
    bool noMarkLeft;
    char winner;
    char currPlayer;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape board;
    sf::RectangleShape line;
    sf::Vector2i mousePosition;
    sf::Vector2i initDragPosition;
    sf::CircleShape cir[3];
    sf::Texture mCross;
    sf::Texture boardTexture;
    sf::Texture titleTexture;
    sf::Texture restartTexture;
    sf::Sprite restartSprite;
    sf::Sprite titlesprite;
    sf::Texture bgTexture;
    sf::Sprite cross[3];
    sf::Sprite bgSprite;
    static int cirCount;
    static int crossCount;
    void drawBoard();
    void drawRect(float x,float y);
    void setPlayer(float x, float y);
    void drawPlayer();
    void drawLine(int,int,int);
    void processEvents();
    void placeMark();
    void selectMark();
    void moveMark();
    void checkWin();
    void checkDraw();
    void restartGame();
    void render();

  public:
    Buddhichal();
    void run();
};
