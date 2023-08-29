


//only chunk of code I copied from internet was the SetConsoleTextAttribute function (which isn't crucial anyway, entirely for aesthetics purpose)

#include <iostream>

//for using sleep() function
#include <unistd.h>

//for using vector
#include<vector>

//for using color
#include <windows.h>

//for using randomnes
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> patternFinderFunction(vector<int> testedVector)
{

    int i,c,p,checkAgain,t;
    bool searchBool = false;

    i = 1;
    p = 0;
    checkAgain = 1;

    vector<int> foundPattern;

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
                    if(checkAgain<2)
                    {
                        checkAgain++;
                        t = c;
                        c = i;
                        i = 2*i - t;
                        p = 0;
                    }
                    else{
                        p = 0;
                        for (p; i - c - p > 0; p++)
                        {
                            foundPattern.push_back(testedVector[i + p]);
                        }
                        return foundPattern;
                    }
                }

                //pattern with period of above 8 are not possible within a 30x30 grid, hence the i-c>8
                if(testedVector[c+p]!=testedVector[i+p] || i-c>8)
                {
                    p = 0;
                    break;
                }
            }
        }
    }

    return foundPattern;
}


int main()
{

    srand(time(0));

    int question;
    cout<<"if you want to know what game of life is about, type 420. if not, type any other number"<<endl;
    cin>>question;
    if(question==420)
    {
        cout<<"Suprise! Game of life isn't actually a game, it's a cellular automata program written by John Conway in 1970"<<endl;
        cout<<"It has a grid with infinite length (but in my program user decide how big it is) with alive or dead cells."<<endl;
        cout<<"These cells are determined dead or alive in next generation judged by 3 rules:"<<endl<<endl;
        cout<<"If an alive cell has 2 or 3 alive neighbours, it is still alive in the next generation."<<endl;
        cout<<"If a dead cell has 3 alive neighbours, it is born in next generation"<<endl;
        cout<<"Every other cells are DEAD in next generation."<<endl;
        cout<<"User decides the first generation composition and program runs until (I added this feature):"<<endl;
        cout<<"Either all cells are dead or a repeating pattern (no less than 3 repetition) is found"<<endl;
        cout<<" (which is always an indicator of a stable or ever-repeating pattern)"<<endl<<endl;
        cout<<"You might be thinking: What's so special about this damn program?!"<<endl;
        cout<<"If that's the case and you want to know even more, type 420 again and let me show you how deep the rabbit hole goes"<<endl;
        cout<<"Or if you want to start the program, type any other number"<<endl;

        int question2;
        cin>>question2;
        cout<<"\n"<<endl;
        if(question2 == 420)
        {
            int done;
            cout<<"You took the redpill, I see?"<<endl<<endl;
            cout<<"This program is Turing complete, which is fascinating given just these simple 3 rules"<<endl;
            cout<<"That means that this program is able to recognize or decide other data-manipulation rule sets"<<endl;
            cout<<"More simply put: This program can program a program"<<endl;
            cout<<"You can create a working clock with logic gates, you can create a game of life INSIDE of game of life"<<endl;
            cout<<"Of course, it is incredibly complex to do so given the nature of logical circuts and even more hard replicating it inside game of life"<<endl;
            cout<<"If you want solid evidence or visual example, search for (epic conway's game of life) or (life in life inside game of life) on youtube"<<endl<<endl;
            cout<<"Another fascinating thing is that NO algorithm can decide if the first generation composition is going to live forever or die"<<endl;
            cout<<"It is a very chaotic system, which means that it is very sensitive to to inital conditions."<<endl<<endl;
            cout<<"Fun fact: John Conway said that he used to hate his creation, because he thought it was overrated and overshadowed his other work because"<<endl;
            cout<<"when the name John Conway was the talk topic, everyone knew just about his game of life not a single thing about his math career which annoyed him"<<endl<<endl;

            cout<<"If you are done with reading, type any number other"<<endl;
            cin>>done;

        }
    }

/*x for x spectrum, y for y spectrum, delay for sleeping the program for a specific amount of seconds, aliveCells for counting alive cells in
a generation, peakAliveCell for knowing the max amount of alive cells and peakGeneration for knowing which generation peaked in terms of alive cell count
*/
    int x,y,g,swap,delay,aliveCells,peakAliveCell,peakGeneration;


    //for using color, nothing really special again
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

    //11 means bright cyan, it looks cool
    SetConsoleTextAttribute(h,11);


    cout<<"type how big you want grid to be (fe: if you type 6 a grid of 6x6 will generate)"<<endl;
    cout<<"(please don't type more than 26, program usually can't handle that much and crash)"<<endl;
    cout<<"\n";
    cin>>x;
    y = x;
    swap = 0;
    g = 0;
    aliveCells = 0;
    peakAliveCell = 0;
    peakGeneration = 0;
    vector<int> aliveCellsVector;
    vector<int> pattern;
    int gridArray[x+1][y+1][2];

    cout<<"type how many seconds of delay you want between generations"<<endl;
    cin>>delay;


    cout<<"If you want a random generated first generation, type 1488. If you want to manually choose alive cells, type any other number"<<endl;

    int question3;
    cin>>question3;
    cout<<"\n";
    bool randomFirstGeneration;

    if(question3==1488)
    {
        randomFirstGeneration = true;
    }



//mark dead

    for(int i=0; x>=i; i++)
    {
        for(int k=0; y>=k; k++)
        {
            gridArray[k][i][swap]=0;
        }
    }
    cout<<"select the cells that you want alive in the first generation, all the others will be counted as dead"<<endl;

    if(!randomFirstGeneration) {
        while (true) {
            SetConsoleTextAttribute(h, 11);
            int a, b;
            cout << "type -420 on x value if you are done with marking the alive cells" << endl;
            cout << "type x coordinate of alive cell" << endl;
            cin >> a;
            if (a == -420) {
                break;
            }
            cout << "type y coordinate of alive cell" << endl;
            cin >> b;
            if (a > x || b > x || a < 0 || b < 0) {
                SetConsoleTextAttribute(h, 4);
                cout << "your grid doesn't have these coordinates, try again and with caution this time please!"
                     << endl;
                continue;
            }
            cout << "x" << a << ",y" << b << " will be alive in first generation" << endl;
            gridArray[a][b][swap] = 1;

            cout << "\n";

        }
    }


    if(randomFirstGeneration) {
        for (int i = 0; x >= i; i++) {
            for (int k = 0; y >= k; k++) {
                if (rand() % 2 == 0) {
                    gridArray[k][i][swap] = 0;
                } else {
                    gridArray[k][i][swap] = 1;
                }
            }

        }
    }


//write the first generation
    for(int i=0; x>=i; i++)
    {
        for(int k=0; y>=k; k++)
        {
            if(gridArray[k][i][swap]==1)
            {
                SetConsoleTextAttribute(h,10);
                cout<<"  "<<gridArray[k][i][swap];
            }
            else
            {
                SetConsoleTextAttribute(h,4);
                cout<<"  "<<gridArray[k][i][swap];
            }
        }
        cout<<"\n";
    }




    while(true){
//scan every array value and decide if they are alive or not in the next generation

//we need to know how many alive neighbours a cell has so we can determine whether it's alive in the next gen or not (note: in all 8 directions)
        int neiCounter =0;

        for(int i=0; i<=x; i++)
        {

            for(int k=0; k<=y; k++)
            {

                //lets count the alive neighbour cell for every cell

                //every if statement has at least one safety precaution (like k!0=0 or i+1<=y) so that program doesn't look for an array value that doesn't exist.
                //one more important thing is that we need to put the safety precaution first inside the statement
                neiCounter=
                        (k!=0 && gridArray[k-1][i][swap]==1) +
                        (k+1<=x && gridArray[k+1][i][swap]==1) +
                        (i+1<=y && gridArray[k][i+1][swap]==1) +
                        (i!=0 && gridArray[k][i-1][swap]==1) +
                        (i+1<=y && k!=0 && gridArray[k-1][i+1][swap]==1) +
                        (k!=0 && i!=0 && gridArray[k-1][i-1][swap]==1) +
                        (k+1<=x && i!=0 && gridArray[k+1][i-1][swap]==1) +
                        (k+1<=x && i+1<=y && gridArray[k+1][i+1][swap]==1);
                //lets judge if he is alive or not

                if((neiCounter == 2 && gridArray[k][i][swap]==1) || (neiCounter == 3 && gridArray[k][i][swap] == 1) || (neiCounter == 3 && gridArray[k][i][swap] == 0)){

                    gridArray[k][i][!swap] = 1;
                } else{
                    gridArray[k][i][!swap] = 0;
                }

                //we need to reset the counter so that it doesn't add up constantly
                neiCounter = 0;
            }

        }


//now we are gonna operate for next generation
        swap = !swap;
        g++;

        SetConsoleTextAttribute(h,11);
        cout<<"\n"<<"\n";
        cout<<"generation: "<<g<<endl;

//count the alive cells
        for(int i=0; x>=i; i++)
        {

            for(int k=0; y>=k; k++)
            {

                if(gridArray[k][i][swap]==1)
                {
                    aliveCells++;
                }

            }

        }

        if(aliveCells>peakAliveCell)
        {
            peakAliveCell=aliveCells;
            peakGeneration = g;
        }

        cout<<"alive cells :"<<aliveCells<<endl;
        if(aliveCells==0)
        {
            int endOfLine2;
            cout<<"All cells are dead. This place once thrived with life, now it's a wasteland because of your composition."<<endl;
            cout<<"peak number of alive cells was: "<<peakAliveCell<<" in generation: "<<peakGeneration<<endl;
            cin>>endOfLine2;
            break;
        }


//lets write down the next generation
        for(int i=0; x>=i; i++)
        {
            for(int k=0; y>=k; k++)
            {
                if(gridArray[k][i][swap]==1)
                {
                    SetConsoleTextAttribute(h,10);
                    cout<<"  "<<gridArray[k][i][swap];
                }
                else
                {
                    SetConsoleTextAttribute(h,4);
                    cout<<"  "<<gridArray[k][i][swap];
                }

            }
            cout<<"\n";
        }

        //we sometimes need to examine generations so there should be some breathing time (also it looks ugly as hell otherwise)
        sleep(delay);


        aliveCellsVector.push_back(aliveCells);

        pattern = patternFinderFunction(aliveCellsVector);
        if(pattern.size()!=0)
        {
            cout<<"\n"<<endl;
            SetConsoleTextAttribute(h,5);
            cout<<"Pattern period is: "<<pattern.size()<<" and pattern itself is: "<<endl;

            for(int i=0; i<pattern.size(); i++)
            {
                cout<<pattern[i]<<" ";
            }
            return 0;
        }

        aliveCells = 0;



    }

    return 0;
}