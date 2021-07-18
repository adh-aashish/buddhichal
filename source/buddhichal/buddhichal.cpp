#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <iostream>
#include "../../include/buddhichal/Buddhichal.hpp"

char gameBoard[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
}; 

int Buddhichal::cirCount = 0;
int Buddhichal::crossCount= 0;

Buddhichal::Buddhichal():
    viewSize(sf::Vector2f(640,640)),
    window(sf::VideoMode(viewSize.x,viewSize.y),"Buddhichal"),
    x(viewSize.x/4),
    y(viewSize.y/4),
    w(100),
    h(100),
    dragCir(NULL),
    dragCross(NULL),
    gameOver(false),
    isDragging(false),
    isDraw(false),
    noMarkLeft(false),
    winner(' '),
    currPlayer('X')
{
    if(!mCross.loadFromFile("../assets/buddhichal/textures/cross.jpg"))
    {
        //error message
        std::cout << "Couldnot load the file" << std::endl;
    }

/*    if(!font.loadFromFile("../../assets/buddhichal/Font/Hack.ttf"))
    {
        //error message
    }
*/
    if(!bgTexture.loadFromFile("../assets/buddhichal/textures/wallpaper.jpg"))
    {
        //error message
    }

    if(!boardTexture.loadFromFile("../assets/buddhichal/textures/boardTexture.jpg"))
    {
        //error message
    }
    
    if(!titleTexture.loadFromFile("../assets/buddhichal/textures/tictactoe.png"))
    {
        //error message
    }

    if(!restartTexture.loadFromFile("../assets/buddhichal/textures/restart.png"))
    {
        //error message
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0,0);
    bgSprite.setScale(1.95,1.95);
    titlesprite.setTexture(titleTexture);
    titlesprite.setPosition(viewSize.x/5,10);
    restartSprite.setTexture(restartTexture);
    restartSprite.setPosition(x+w/2,viewSize.y-100);
    text.setFont(font);

}

void::Buddhichal::run()
{
 	while(window.isOpen())
	{
    processEvents();
    checkWin();
    checkDraw();
    render();
	}

  for(int i=0; i<3; i++)
  {
      for(int j=0; j<3; j++)
      {
          std::cout << gameBoard[i][j] <<  "\t";
      }
      std::cout << std::endl;
  }
}

void Buddhichal::drawBoard()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            drawRect(x+i*(h+6),y+j*(w+6));
        }
    }
}

void Buddhichal::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) //event takes 1 type at a time 
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

      case sf::Event::MouseButtonPressed:
        /*if(event.mouseButton.button == sf::Mouse::Button::Left)
        {
            mousePressed = (mousePressed)? false : true;
        }
        */
				if(event.mouseButton.button == sf::Mouse::Button::Left && !isDragging)
        {
            mousePosition = sf::Mouse::getPosition(window);
            if(mousePosition.x >= x && mousePosition.x <= (x+(3*w)+12) && 
                    !gameOver && mousePosition.y >= y && mousePosition.y 
                    <= (y+(3*h)+12))
            {
                if(noMarkLeft and !isDragging)
                {
                    std::cout << "Im calling selectMark" << std::endl;
                    selectMark();
                    std::cout << "Im came from selectMark" << std::endl;
                    //move mark here
                }
                else if(!noMarkLeft) 
                {
                    //checkMoves();
                    placeMark();
                }
            }
            if(cirCount>2 && crossCount >2)
            {
                noMarkLeft = true;
            }

            if(gameOver && restartSprite.getGlobalBounds().contains(
                        mousePosition.x,mousePosition.y))
            {
                restartGame();
            }
        }
        break;
			default:
				break;
		}	 
	}
}

void Buddhichal::placeMark()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(mousePosition.x>= x+i*(h+6) && mousePosition.x <= x+i*(h+6)+w)
            {
                if(mousePosition.y >= y+j*(w+6) && mousePosition.y <= 
                        y+j*(w+6)+h)
                {
                    if(gameBoard[j][i] == ' ')
                    {
                        gameBoard[j][i] = currPlayer;
                        setPlayer(x+i*(h+6)+w/2,y+j*(h+6)+h/2);
                    }
                    else
                    {
                        processEvents();
                    }
                }
            }
        }
    }
}

void Buddhichal::moveMark()
{
    if(isDragging)
    {
        if(currPlayer == 'X')
        {
            std::cout << "Moving X" << std::endl;
            dragCross->setPosition(sf::Mouse::getPosition(window).x,
                    sf::Mouse::getPosition(window).y);
            window.draw(*dragCross);
        }

        if(currPlayer == 'O')
        {
            dragCir->setPosition(sf::Mouse::getPosition(window).x,
                    sf::Mouse::getPosition(window).y);
            window.draw(*dragCir);
        }
    }

}

void Buddhichal::selectMark()
{
    if(currPlayer == 'X')
    {
        std::cout << "here?" << std::endl;
        for(int i=0; i<3; i++)
        {
            if(cross[i].getGlobalBounds().contains(mousePosition.x,
                        mousePosition.y))
            {
                isDragging = true;
                std::cout << "isDragging :  "<< isDragging << std::endl;
                std::cout << "which is cross "<< i << std::endl;
                dragCross = &cross[i];
                std::cout << "assigned" << std::endl;
                break;
               // dragMe(cross[i]);
            }
        }
    }

    if(currPlayer == 'O')
    {
        std::cout << "o here?" << std::endl;
        for(int i=0; i<3; i++)
        {
            if(cir[i].getGlobalBounds().contains(mousePosition.x,
                        mousePosition.y))
            {
                isDragging = true;
                dragCir = &cir[i];
                std::cout << "I'm here inside O player selcetion" << std::endl;
                //dragMe(cir[i]);
                break;
            }
        }
    }
}
    //get the current mouse postion 
    //get the sprite selected
    //put the sprite where the mouse is kept

void Buddhichal::drawPlayer()
{
    int cirTempCount=0;
    int crossTempCount=0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(gameBoard[i][j]=='O')
            {
                window.draw(cir[cirTempCount]);
                cirTempCount++;
            }
            if(gameBoard[i][j]=='X')
            {
                window.draw(cross[crossTempCount]);
                crossTempCount++;
            }
        }
    }
}

void Buddhichal::setPlayer(float x,float y)
{
    switch (currPlayer)
    {
        case 'X':
            cross[crossCount].setTexture(mCross);
            cross[crossCount].setScale(0.1,0.1);
            cross[crossCount].setPosition(x,y);
            cross[crossCount].setOrigin(mCross.getSize().x/2.f,
                    mCross.getSize().y/2.f);
            currPlayer = 'O';
            crossCount++;
            break; 
        case 'O':
        {
           cir[cirCount].setRadius(38);
           cir[cirCount].setPosition(x,y);
           cir[cirCount].setOrigin(cir[0].getRadius(),cir[0].getRadius());
           cir[cirCount].setFillColor(sf::Color::Transparent);
           cir[cirCount].setOutlineThickness(6.f);
           cir[cirCount].setOutlineColor(sf::Color::Red);
           currPlayer = 'X';
           cirCount++;
           break; 
        }
        default:
           break;
    }
}   

void Buddhichal::drawLine(int x,int y, int angle)
{
    line.setSize(sf::Vector2f(3*w+12,6));
    line.setPosition(x,y);
    line.setOrigin(0,line.getSize().y/2);
    line.setFillColor(sf::Color::Blue);
    line.setRotation(angle);

    if(angle == 45 || angle == 135)
    {
        line.setSize(sf::Vector2f(441.23,6));
    }
}

void Buddhichal::checkWin()
{
    for(int i=0; i<3; i++)
    {
        if(gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][0] == 
                gameBoard[i][2] && gameBoard[i][0] !=' ')
        {
            winner = gameBoard[i][0];
            gameOver = true;
            drawLine(x,y+i*(h+6)+h/2,0);
            break;
        }
        if(gameBoard[0][i] == gameBoard[1][i] && gameBoard[0][i] == 
                gameBoard[2][i] && gameBoard[0][i] !=' ')
        {
            winner = gameBoard[0][i];
            gameOver = true;
            drawLine(x+i*(w+6)+w/2,y,90);
            break;
        }
    }
    if(gameBoard[0][0] == gameBoard[1][1] && gameBoard[0][0] == 
            gameBoard[2][2] && gameBoard[0][0] !=' ')
    {
        winner = gameBoard[0][0];
        gameOver = true;
        drawLine(x,y,45);
    }
    if(gameBoard[0][2] == gameBoard[1][1] && gameBoard[0][2] == 
            gameBoard[2][0] && gameBoard[0][2] !=' ')
    {
        winner = gameBoard[0][2];
        gameOver = true;
        drawLine(x+3*w+12,y,135);
    }
}

void Buddhichal::checkDraw()
{
    if((cirCount+crossCount)==9 && !(winner == 'X' || winner =='O'))
    {
        isDraw = true;
        gameOver = true;
    }
}

void Buddhichal::restartGame()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3;j++)
        {
            gameBoard[i][j] = ' ';
        }
    }
    gameOver = false;
    noMarkLeft = false;
    winner = ' ';
    cirCount = 0;
    crossCount =0;
    currPlayer = 'X';
    line.setSize(sf::Vector2f(0,0));
}

void Buddhichal::render()
{
    window.clear();
    window.draw(bgSprite);
    window.draw(titlesprite);
    drawBoard();
    if(isDragging && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(currPlayer == 'X' && dragCross != NULL)
        {
            dragCross->setPosition(sf::Mouse::getPosition(window).x,
                    sf::Mouse::getPosition(window).y);
            window.draw(*dragCross);
        }

        if(currPlayer == 'O' && dragCir !=NULL)
        {
            dragCir->setPosition(sf::Mouse::getPosition(window).x,
                    sf::Mouse::getPosition(window).y);
            window.draw(*dragCir);
        }
    }else if(isDragging && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        isDragging = false;
        currPlayer = (currPlayer == 'X')? 'O':'X';
        dragCir = NULL;
        dragCross = NULL;
    }
    
    drawPlayer();
    if(gameOver)
    {
        std::ostringstream oss;
        if(winner!=' ')
        {
            oss << winner << " Won The Game!!!";
        }
        else if(isDraw)
        {
            oss<<"Its a Draw  ¯\\_(ツ)_/¯";

        }
        text.setString(oss.str());
        text.setFillColor(sf::Color::Green);
        text.setCharacterSize(44);
        //window.draw(text);
        window.draw(line);
        window.draw(restartSprite);
    }
    window.display();
}

void Buddhichal::drawRect(float x, float y)
{
    sf::RectangleShape rect(sf::Vector2f(100,100));
    rect.setPosition(x,y);
    rect.setTexture(&boardTexture);
    window.draw(rect);
}

