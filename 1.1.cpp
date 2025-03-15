#include <stdio.h>
#include <iostream>

using namespace std;

struct State
{
    int monkeyPos;      //Monkey at: A=-1,B=0,C=1
    int boxPos;         //Box at: A=-1,B=0,C=1
    int banana;         /*Banana at B,Banana=0*/
    int monkeyOnBox;    //On the box: 1
};
struct State States [150];
string routeSave[150];

// Monkey Move
void MonkeyGoesTo(int destination, int step)
{
    if (destination==-1)
    {
        routeSave[step]="Monkey goes to A";
        States[step + 1]=States[step];
        States[step + 1].monkeyPos=-1;
    }
    else if(destination==0)
    {
        routeSave[step]="Monkey goes to B";
        States[step + 1]=States[step];
        States[step + 1].monkeyPos=0;
    }
    else if(destination==1)
    {
        routeSave[step]="Monkey goes to C";
        States[step + 1]=States[step];
        States[step + 1].monkeyPos=1;
    }
    else
    {
        printf("Parameter is wrong");
    }
}
// Monkey move the box
void moveBox(int boxDestination, int step)
{
    if(boxDestination == -1)
    {
        routeSave[step]="Monkey move the box to A";
        States[step + 1]=States[step];
        States[step + 1].monkeyPos=-1;
        States[step + 1].boxPos=-1;
    }
    else if(boxDestination == 0)
    {
        routeSave[step] = "Monkey move the box to B";
        States[step + 1]=States[step];
        States[step + 1].monkeyPos=0;
        States[step + 1].boxPos=0;
    }
    else if(boxDestination == 1)
    {
        routeSave[step] = "Monkey move the box to C";
        States[step + 1]=States[step];
        States[step + 1].monkeyPos=1;
        States[step + 1].boxPos=1;
    }
    else
    {
        printf("parameter is wrong");
    }
}
// Monkey climb up the box
void climbUp(int step)
{
    routeSave[step]="Monkey climb onto the box";
    States[step + 1]=States[step];
    States[step + 1].monkeyOnBox=1;
}
// Monkey climb down the box
void climbDown(int step)
{
    routeSave[step]="Monkey climb down from the box";
    States[step + 1]=States[step];
    States[step + 1].monkeyOnBox=-1;
}
// Monkey reach the banana
void reach(int step)
{
    routeSave[step]="Monkey reaches the banana";
}
// Show the solution
void showSolution(int step)
{
    cout << "The solution is: " << endl;
    for(int timer=0; timer < step + 1; timer++)
    {
        cout << "Step "<< timer + 1 << " is: " << routeSave[timer] << endl;
    }
}
// Perform next step
void nextStep(int step)
{
    int j;
    if(step >= 150)
    {
        cout << "Step reached 150, no solution. Consider error." << endl;
        return;
    }
    for (int timer = 0; timer < step; timer++)
    {   // Check if the state is repeated
        if(States[timer].monkeyPos == States[step].monkeyPos && States[timer].boxPos == States[step].boxPos && States[timer].banana == States[step].banana && States[timer].monkeyOnBox == States[step].monkeyOnBox)
        {
            return;
        }
    }
    if(States[step].monkeyOnBox == 1 && States[step].monkeyPos == 0 && States[step].banana == 0 && States[step].boxPos == 0)
    {
        showSolution(step);
        printf("Press any key to continue \n");
        getchar();  // Freeze the screen to show the solution
        exit(0);
    }
    j= step + 1;
    if(States[step].monkeyPos == 0)
    {
        if(States[step].boxPos == 0)
        {
            if(States[step].monkeyOnBox == -1)  // Monkey B, Box B, Monkey not on box
            {
                climbUp(step);
                reach(step + 1);
                nextStep(j);
            }
            else    // Monkey B, Box B, Monkey on box
            {
                reach(step + 1);
                nextStep(j);
            }
        }
        else if(States[step].boxPos == 1)   // Monkey B, Box C
        {
            MonkeyGoesTo(1, step);
            nextStep(j);
            moveBox(0, step);
            nextStep(j);
            climbUp(step);
            reach(step + 1);
            nextStep(j);
        }
        else    // Monkey B, Box A
        {
            MonkeyGoesTo(-1, step);
            nextStep(j);
            moveBox(0, step);
            nextStep(j);
            climbUp(step);
            reach(step + 1);
            nextStep(j);
        }
    }

    if(States[step].monkeyPos == -1)
    {
        if(States[step].boxPos == -1)
        {
            if(States[step].monkeyOnBox == -1)  // Monkey A, Box A, Monkey not on box
            {
                moveBox(0, step);
                nextStep(j);
                climbUp(step);
                reach(step + 1);
                nextStep(j);
            }
            else    // Monkey A, Box A, Monkey on box
            {
                climbDown(step);
                nextStep(j);
                moveBox(0, step);
                nextStep(j);
                climbUp(step);
                reach(step + 1);
                nextStep(j);
            }
        }
        else if(States[step].boxPos == 0)   // Monkey A, Box B
        {
            MonkeyGoesTo(0, step);
            nextStep(j);
            climbUp(step);
            reach(step + 1);
            nextStep(j);
        }
        else    // Monkey A, Box C
        {
            MonkeyGoesTo(1, step);
            nextStep(j);
            moveBox(0, step);
            nextStep(j);
            climbUp(step);
            reach(step + 1);
            nextStep(j);
        }
    }

    if(States[step].monkeyPos == 1)
    {
        if (States[step].boxPos == 1)
        {
            if(States[step].monkeyOnBox == -1)  // Monkey C, Box C, Monkey not on box
            {
                moveBox(0, step);
                nextStep(j);
                climbUp(step);
                reach(step + 1);
                nextStep(j);
            }
            else    // Monkey C, Box C, Monkey on box
            {
                climbDown(step);
                nextStep(j);
                moveBox(0, step);
                nextStep(j);
                climbUp(step);
                reach(step + 1);
                nextStep(j);
            }
        }
        else if(States[step].boxPos == -1)  // Monkey C, Box A
        {
            MonkeyGoesTo(-1, step);
            nextStep(j);
            moveBox(0, step);
            nextStep(j);
            moveBox(0, step);
            nextStep(j);
            climbUp(step);
            reach(step + 1);
            nextStep(j);
        }
        else    // Monkey C, Box B
        {
            MonkeyGoesTo(0, step);
            nextStep(j);
            moveBox(0, step);
            nextStep(j);
            climbUp(step);
            reach(step + 1);
            nextStep(j);
        }
    }
}
int main()
{
    States[0].monkeyPos=1;
    States[0].boxPos=0;
    States[0].banana=0;
    States[0].monkeyOnBox=-1;
    nextStep(0);
}
