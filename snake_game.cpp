#include <bits/stdc++.h>
#include <windows.h>
#include<conio.h>
using namespace std;

class snake
{
    private:
        int width,height;
        int targetx,targety,score;
        bool gameover=false;
        int headx, heady;
        enum direction{
            up, down, left,right,stop
        }dir;
        deque<pair<int,int>> mysnake;
        int prevx,prevy;
    public:
        int getscore(){
            return score;
        }
        snake(int w, int h){
            dir =up;
            width=w;
            height=h;
            score=0;
            targetx= rand()%(w-2)+1;
            targety= rand()% (h-2)+1;
            gameover=false;
            headx=width/2;
            heady=height/2;
            mysnake.push_back({headx,heady});
        }
        bool gamecondition(){
            return gameover;
        }
        void draw()
        {
            system("cls");
            
            for (int i = 0; i < width; i++)
            {
                cout << "#";
            }
            cout << "\n";
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    if (col == 0 || col == width - 1)
                    {
                        cout << "#";
                        continue;
                    }

                    pair<int,int> xx={col,row};
                    auto iter=find(mysnake.begin(),mysnake.end(),xx);
                    if(iter!=mysnake.end())
                    {
                        if(headx==col && heady==row){
                            cout<<"H";
                        }    
                        else{
                            cout<<"O";
                        }
                    }
                    else if(row==targety && col==targetx){
                        cout<<"X";
                    }
                    else{
                        cout<<" ";
                    }
                }
                cout << "\n";
            }
            for (int i = 0; i < width; i++)
            {
                cout << "#";
            }
        }
        void input(){
            if(_kbhit()){     //in conio.h
                switch(_getch()){
                    case 'w':{
                        if(dir!=down){
                            dir=up;
                        }
                        break;
                    }
                    case 's':{
                        if(dir!=up){
                            dir=down;
                        }
                        break;
                    }
                    case 'a':{
                        if(dir!=right){
                            dir=left;
                        }
                        break;
                    }
                    case 'd':{
                        if(dir!=left){
                            dir=right;
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
            
        }
        void changedirection(){
            switch(dir){
                case up:{
                    heady--;
                    mysnake.push_front({headx,heady});
                    auto x=mysnake.back();
                    prevx=x.first;
                    prevy=x.second;
                    mysnake.pop_back();
                    break;
                }
                case down:{
                    heady++;
                    mysnake.push_front({headx,heady});
                    auto x=mysnake.back();
                    prevx=x.first;
                    prevy=x.second;
                    mysnake.pop_back();
                    break;
                }
                case left:{
                    headx--;
                    mysnake.push_front({headx,heady});
                    auto x=mysnake.back();
                    prevx=x.first;
                    prevy=x.second;
                    mysnake.pop_back();
                    break;
                }
                case right:{
                    headx++;
                    mysnake.push_front({headx,heady});
                    auto x=mysnake.back();
                    prevx=x.first;
                    prevy=x.second;
                    mysnake.pop_back();
                    break;
                }
                default:{
                    break;
                }
            }
            //if out the boundary
            if(headx<0 || headx>=width || heady<0 || heady>=height){
                dir=stop;
                gameover=true;
                return;
            }
            //if step on its own tail
            pair<int,int> temphead={headx,heady};
            auto iter=find(mysnake.begin()+1,mysnake.end(),temphead);
            if(iter!=mysnake.end()){
                dir=stop;
                gameover=true;
                return;
            }
            if(headx==targetx && heady==targety){
                targetx= rand()%(width-2)+1;
                targety= rand()% (height-2)+1;
                mysnake.push_back({prevx,prevy});
                score+=10;
            }
        }
};

int main()
{
    srand( time(NULL) );
    snake s(20,20);
    while(s.gamecondition()==false){
        s.draw();
        s.input();
        s.changedirection();
        Sleep(100);
    }
    cout<<"\ngame is over";
    cout<<"\nyour score is : "<<s.getscore();
    getch();


}