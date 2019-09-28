#include<iostream>
#include<string.h>
//#include <bits/stdc++.h>
#include <ctime>
#define ll long long int
//#define overs 5
using namespace std;

int overs=5;
int target=0;
enum teamorder{first=1,second};
teamorder ord=first;

class match;

struct player{
        int runs_scored;
        int balls_faced;
        int boundaries_scored;
        int wickets_taken;
};

struct scorecard{
        int runs;
        int overs;
        int balls;
        int boundaries;
        int wickets;
};

class team{
        player players[11];
        scorecard team_scorecard;
        public:
        team(){team_scorecard={0,0,0,0,0};/*players[11]={ {0,0,0,0},{0,0,0,0},{0,0,0,0},
        {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };*/
        for(int i=0;i<11;i++){
            players[i].runs_scored=0;
            players[i].balls_faced=0;
            players[i].boundaries_scored=0;
            players[i].wickets_taken=0;
        }
    }
    void generate_player_score(player &p,int counter);
    void generate_team_scorecard();
    friend void playmatch(team inn,match m,int chase);
    friend bool chech_win(int runs,int wickets);
};
void team::generate_player_score(player &p,int counter){
        cout<<"PLAYER "<<counter-1<<": \t\t";
        cout<<p.runs_scored<<" ("<<p. balls_faced<<") "<<"(4's/6's: "<<p.boundaries_scored<<" )"<<endl;
}
void team::generate_team_scorecard(){
        cout<<"Runs :  "<<team_scorecard.runs<<"\tOvers :  "<<team_scorecard.overs<<"."<<team_scorecard.balls%6<<
        "\tBoundaries :  "<<team_scorecard.boundaries<<"\tWickets :  "<<team_scorecard.wickets<<"\n"<<endl;
        cout<<"**************************************************************************"<<endl;
}
class match:public team{
        int currentplayer1,currentplayer2;
        int counter;
        public:
        match(){  currentplayer1=1; currentplayer2=2; counter=2;}
        friend void playmatch(team inn,match m,int chase);
        friend bool chech_win(int runs,int wickets);
};
bool chech_win(int runs,int wickets){
        return( (runs>target && wickets<10)?true:false);
}
void playmatch(team inn,match m,int chase){
        int flag1=0,flag2=0,flag3=0;
        for(int j=0;j<overs;j++){                                               //INNINGS
                int r,w,flag=0,count=0;
                int exchange_turns=0;
                //if(inn.team_scorecard.wickets==10) break;                     //All OUT
                /**************
                OVER STARTED
                **************/
                for(int i=0;i<6;i++){
                        if(inn.team_scorecard.wickets==10)  break;              //All OUT
                        //srand(time(NULL));
                        r=rand()%7;  w=rand()%10;                               //r=runs scored on each ball
                        /**************
                        WICKET FALLEN
                        **************/
                        if(w==7){                                               //generate wicket at w==7
                           if(flag==0){                                         //batsman 1 out on random ball
                                inn.players[ m.currentplayer1 ].balls_faced++;  //players ball faced incremented
                                inn.generate_player_score( inn.players[ m.currentplayer1 ] , m.counter );       //print score of batsman out
                                m.currentplayer1 = ++m.counter;                 //increment current batsman
                           }
                           else {                                               //batsman 2 out on random ball
                                inn.players[ m.currentplayer2 ].balls_faced++;  //players ball faced incremented
                                inn.generate_player_score( inn.players[ m.currentplayer2 ] , m.counter );       //print score of batsman out
                                m.currentplayer2 = ++m.counter;                 //increment current batsman
                           }
                           inn.team_scorecard.wickets++;                        //increment wickets of team
                           inn.team_scorecard.balls++;                          //increment ball count of team
                           if(inn.team_scorecard.wickets==10){
                                flag2=1 ; break;
                           }
                           continue;
                        }
                        //count++;
                        /******************
                        RUNNING THE INNINGS
                        *******************/
                        if( exchange_turns==0 ){                                 //First player plays
                                inn.players[ m.currentplayer1 ].runs_scored += r;//run of individual ball added to players account
                                inn.players[ m.currentplayer1 ].balls_faced++;   //run of individual ball added to players account
                                inn.team_scorecard.runs += r;                   //increment runs of team
                                /*****************
                                BOUNDARIES SCORED
                                *****************/
                                if ( r==4 || r==6 ){
                                        inn.players[ m.currentplayer1 ].boundaries_scored++;
                                        inn.team_scorecard.boundaries++;
                                }
                                //flag=0;
                                if( r%2!=0 )   exchange_turns=1;
                                if(chase==1 && chech_win(inn.team_scorecard.runs,inn.team_scorecard.wickets)){
                                        flag3=1;
                                        break;
                                        cout<<"Team"<<ord<<"Won the match by chasing with "<<10-inn.team_scorecard.wickets<<
                                        " wickets and" <<overs*6-inn.team_scorecard.balls<<" balls remaining"<<endl;
                                }
                                if(inn.team_scorecard.wickets==10 && inn.team_scorecard.runs==target){
                                        inn.team_scorecard.balls++;
                                        flag1=1; break;
                                }
                        }
                        else{                                                    //First player plays
                                inn.players[ m.currentplayer2 ].runs_scored += r;//run of individual ball added to players account
                                inn.players[ m.currentplayer2 ].balls_faced++;   //run of individual ball added to players account
                                inn.team_scorecard.runs += r;                    //increment runs of team
                                /****************
                                BOUNDARIES SCORED
                                *****************/
                                if( r==4 || r==6 ){
                                inn.players[ m.currentplayer2 ].boundaries_scored++;
                                inn.team_scorecard.boundaries++;
                                }
                                //flag=1;
                                if( r%2!=0 )   exchange_turns=0;                //turns exchanged after scoring odd no of runs
                                if(chase==1 && chech_win(inn.team_scorecard.runs,inn.team_scorecard.wickets)){
                                        flag3=1;
                                        break;
                                }
                                if(inn.team_scorecard.wickets==10 && inn.team_scorecard.runs==target){
                                        inn.team_scorecard.balls++;
                                        flag1=1;  break;
                                }
                        }
                        inn.team_scorecard.balls++;                             //increment balls of team
                        exchange_turns=1;                                       //turns exchanged after over ended
                }
                if( flag1==1 || flag2==1 || flag3==1 ){break;}
                inn.team_scorecard.overs++;                                             //increment overs of team
        }
        /**************
        INNINGS OVER
        **************/
        cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer1 ] , m.counter);
        cout<<"*";inn.generate_player_score( inn.players[ m.currentplayer2 ] , ++m.counter);
        cout<<"\n\n******************    INNINGS OVER    ******************\n"<<endl;
        cout<<"TEAM "<< ord << " SCORE :\t";
        ord=(ord==first)?second:first;
        inn.generate_team_scorecard();                                          //Team scorecard display
        if(flag1==1){
                inn.team_scorecard.balls++;
                cout<<"\n\n\n******************     SCORES LEVEL     ******************"<<endl;}
        if(inn.team_scorecard.runs<target){
                cout<<"Team"<<ord<<" successfully defended the target of "<<target<<" runs & WON THE MATCH."<<endl;
        }
        if(flag3==1){
                inn.team_scorecard.balls++;
                cout<<"Team"<<ord<<"Won the match by chasing with "<<10-inn.team_scorecard.wickets<<
                        " wickets and" <<overs*6-inn.team_scorecard.balls<<" balls remaining"<<endl;
        }
        target=inn.team_scorecard.runs;
}
int main(int argc,char *argv[]){
        /**************
        MATCH STARTED
        **************/

        /*FILE *fp;
        if(argc!=2){    cout<<"No file name"<<endl;exit(1);     }
        if((fp=fopen(argv[1],"w"))==NULL){
                cout<<"Cannot open file."<<endl;
        exit(1);}*/

        cout<<"******************    CRICKET MATCH SCORECARD    ******************\n\n"<<endl;
        match inning1,inning2;                                   //Generating objects of match class
        team team1,team2;                                        //Generating objects of team class
        srand(time(NULL));                                       //seeding random function with time

        /**************
        TOSS
        **************/
        int toss=0;
        toss=rand()%4;
        if(toss==0){   cout<<"TEAM 1 WON THE TOSS AND ELECTED TO BAT FIRST.\n\n"<<endl;
                ord=first; }
        else if(toss==1){  cout<<"TEAM 1 WON THE TOSS AND ELECTED TO BOWL FIRST.\n\n"<<endl;
                ord=second; }
        else if(toss==2){   cout<<"TEAM 2 WON THE TOSS AND ELECTED TO BAT FIRST.\n\n"<<endl;
                ord=second; }
        else if(toss==3){   cout<<"TEAM 2 WON THE TOSS AND ELECTED TO BOWL FIRST.\n\n"<<endl;
                ord=first; }

        /**************
        INNINGS STARTED
        **************/
        int chase=0;
        playmatch(team1,inning1,chase);
        chase=1;
        playmatch(team2,inning2,chase);
        //fclose(fp);
        return 0;
}
