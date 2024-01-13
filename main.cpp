#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>
#include <unistd.h>
std::mt19937 mt(time(nullptr));

//TODO: Fix variable names
std::vector<unsigned int> patternFinderFunction(std::vector<unsigned int> testedVector,unsigned int confidenceBareLimit,unsigned int patternBreaker)
{

    int i,c,p,checkAgain,t;
    bool searchBool = false;
    i = 1;
    p = 0;
    std::vector<unsigned int> foundPattern;

    for(i; i<testedVector.size(); i++)
    {
        searchBool = false;
        checkAgain = 1;
        for(c=i-1; c>1; c--)
        {
            if(searchBool)
            {
                break;
            }

            while(testedVector[c]==testedVector[i])
            {

                searchBool = true;
                p++;
                if(i-c-p==0)
                {
                    if(checkAgain<confidenceBareLimit)
                    {
                        checkAgain++;
                        t = c;
                        c = i;
                        i = 2*i - t;
                        p = 0;
                    }
                    else
                    {
                        p = 0;
                        for (p; i - c - p > 0; p++)
                        {
                            foundPattern.push_back(testedVector[i + p]);
                        }
                        return foundPattern;
                    }
                }

                if(testedVector[c+p]!=testedVector[i+p] || i-c>patternBreaker)
                {
                    p = 0;
                    break;
                }
            }
        }
    }

    return foundPattern;
}

class Cell
{
public:
    int numberOfAliveNei;
    bool alive;
    unsigned int xCoord;
    unsigned int yCoord;


    Cell(int xCoord, int yCoord, bool isAlive)
    {
        this->xCoord = xCoord;
        this->yCoord = yCoord;
        this->alive = isAlive;
    }

    void calcNumberOfAliveNei(const std::vector<std::vector<Cell>>& currentGrid,const unsigned int width, const unsigned int height)
    {

        int neiCounter = 0;

        //left
        if(xCoord!=0 && currentGrid[yCoord][xCoord-1].alive)
        {
            neiCounter++;
        }
        //right
        if(xCoord+1<width && currentGrid[yCoord][xCoord+1].alive)
        {
            neiCounter++;
        }
        //up
        if(yCoord+1<height && currentGrid[yCoord+1][xCoord].alive)
        {
            neiCounter++;
        }
        //down
        if(yCoord!=0 && currentGrid[yCoord-1][xCoord].alive)
        {
            neiCounter++;
        }
        //left-down
        if(xCoord!=0 && yCoord!=0 && currentGrid[yCoord-1][xCoord-1].alive)
        {
            neiCounter++;
        }
        //left-up
        if(xCoord!=0 && yCoord+1<height && currentGrid[yCoord+1][xCoord-1].alive)
        {
            neiCounter++;
        }
        //right-down
        if(xCoord+1<width && yCoord!=0 && currentGrid[yCoord-1][xCoord+1].alive)
        {
            neiCounter++;
        }
        //right-up
        if(xCoord+1<width && yCoord+1<height && currentGrid[yCoord+1][xCoord+1].alive)
        {
            neiCounter++;
        }
        this->numberOfAliveNei = neiCounter;
    }

    bool judge(const std::vector<std::vector<Cell>>& currentGrid,const unsigned int width, const unsigned int height)
    {
        calcNumberOfAliveNei(currentGrid,width,height);

        if((alive&&((numberOfAliveNei==2)||numberOfAliveNei==3))||(!alive&&(numberOfAliveNei==3)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

class Grid
{
    unsigned int delay;
    unsigned int generation = 0;
    unsigned int width;
    unsigned int height;
    unsigned int patternSearchLimit;
    unsigned int confidenceBareLimit;
    std::vector<unsigned int> aliveCellVector;

    //3 dimension: x, y and time
    std::vector< std::vector<std::vector<Cell>> > theGrid;



public:
    Grid(unsigned int width, unsigned height, unsigned int sleep,unsigned int patternSearchLimit, unsigned int confidenceBareLimit)
    {
        this->width = width;
        this->height = height;
        this->delay = sleep;
        this->patternSearchLimit = patternSearchLimit;
        this->confidenceBareLimit = confidenceBareLimit;

        //fill the cells
        bool alive;
        std::vector<Cell> tempSmallVector;
        std::vector<std::vector<Cell>> tempBigVector;
        for(int i=0; i<height; i++)
        {

            for(int k=0; k<width; k++)
            {
                if(mt()%2==0)
                {
                    alive = true;
                }
                else
                {
                    alive = false;
                }
                Cell tempCell(k,i,alive);
                tempSmallVector.push_back(tempCell);
            }
            tempBigVector.push_back(tempSmallVector);
            tempSmallVector.clear();
        }
        //inital and swap grid will take turns forever
        theGrid.push_back(tempBigVector);
        theGrid.push_back(tempBigVector);

    }

    void printGrid()
    {
        for(int i=0; i<height; i++)
        {
            for(int k=0; k<width; k++)
            {
                if(theGrid[generation%2][i][k].alive)
                {
                    std::cout<<1<<" ";
                }
                else
                {
                    std::cout<<0<<" ";
                }
            }
            std::cout<<"\n";
        }
        std::cout<<"\n";
    }

    bool checkForRepetition()
    {
        std::vector<unsigned int> potentialPattern = patternFinderFunction(aliveCellVector,patternSearchLimit,confidenceBareLimit);
        if(!potentialPattern.empty())
        {
            std::cout<<"Pattern found:"<<"\n";
            for(int i=0; i<potentialPattern.size(); i++)
            {
                std::cout<<potentialPattern[i]<<" ";
            }
            std::cout<<"\n";
            return true;
        }
        else
        {
            return false;
        }
    }

    void calcNextGen()
    {
        bool judgement;
        unsigned int numberOfAliveCells = 0;
        for(int i=0; i<height; i++)
        {
            for(int k=0; k<width; k++)
            {

                judgement = theGrid[generation%2][i][k].judge(theGrid[generation%2],width,height);

                if(judgement)
                {
                    numberOfAliveCells++;
                    theGrid[!(generation%2)][i][k].alive=true;
                }
                else
                {
                    theGrid[!(generation%2)][i][k].alive=false;
                }
            }
        }

        aliveCellVector.push_back(numberOfAliveCells);
        generation++;
    }

    void startTheLoop()
    {
        while(true)
        {
            printGrid();
            calcNextGen();
            if(checkForRepetition())
            {
                break;
            }
            sleep(delay);
        }

    }

};

int main()
{

    Grid testGrid(10,8,1,6,2);

    testGrid.startTheLoop();

    return 0;
}