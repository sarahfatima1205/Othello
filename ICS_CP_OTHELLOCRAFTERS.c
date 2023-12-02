#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int declare_result(char (*a)[8]){  //declares result, counts the scores
    int count_x=0;
    int count_o=0;


    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(a[i][j]=='X'){
                count_x++;
            }
            if(a[i][j]=='O'){
                count_o++;
            }
        }

    }
    if(count_x+count_o==64){
    char winner;
    if(count_o>count_x){
        winner='O';
    }
     if(count_x>count_o){
        winner='X';
    }
    if(count_x==count_o){
        winner='T';
    }

 printf("\033[5;31m");  //changes colour to red whose code is 31
   printf("GAME OVER\n");
   printf("\033[0m");   //reverts the colour back to white
   printf("\033[5;32m");
   printf("X has %d points\n", count_x);
   printf("\033[0m");
   printf("\033[5;32m");
   printf("O has %d points\n", count_o);
   printf("\033[0m");
   printf("\033[33m");
   printf("WINNER IS %c\n", winner);
   printf("\033[0m");
   return 1;
    }
    printf("\033[5;33m");  //colour change
printf("\nSCORES: X = %d  O = %d",count_x,count_o);  //prints scores
 printf("\033[37m");
    return 0;
}

int endgame(char (*a)[8],int turn){  //checks and declares result when the entire board is occupied by only X or O

    int count_x=0;
    int count_o=0;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(a[i][j]=='X'){
                count_x++;
            }
            if(a[i][j]=='O'){
                count_o++;
            }
        }

    }
    if(turn>2){  //initial condition, as board is unfilled
    if(count_x==0){
        printf("\033[36m");
        printf("O is the winner.");
        printf("\033[0m");
        return 0;
    }
    if(count_o==0){
        printf("\033[36m");
        printf("X is the winner.");
        printf("\033[0m");
        return 0;
    }
    }
}

void flip(char *x ){  //performs the function of changing the X to O or vice versa
    if(*x=='X'){
        *x='O';
    }
    else if(*x=='O'){
        *x='X';
     }
}
int check_valid(char (*arr)[8], char x, int row, int col) {  //checks sandwich conditions and flips accordingly
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && arr[row][col] != ' ' && arr[row][col] != x) {
        return 1;
    }
    return 0;
}

int func(char (*arr)[8],char x,int row,int col,int m,int n,int k){
  int j=col+n;
  int i=row+m;
          if((i+m)>=0&&(i+m)<8&&(j+n)>=0&&(j+n)<8){
          if (check_valid(arr,x,i,j) == 0) {
          return 0;
          }
          if(arr[i+m][j+n]!=' '){
            if(arr[i+m][j+n]==x){
            if(k==0){
            flip(&arr[i][j]);
             }
            return 1;
            }
          else if(arr[i+m][j+n]!=x){
            if(func(arr,x,i,j,m,n,k)==1){
            if(k==0){
            flip(&arr[i][j]);
          }
            return 1;
          }
           }
}
        }
return 0;
}


int main() {
    int p=0;
    char a[8][8],y;
    int row, col;

    char play1[100], play2[100];

    printf("\033[5;36m");
    printf("welcome to this othello adventure:\n");
    printf("Please enter player-1: ");
    scanf("%s",play1);
    printf("\nPlease enter player-2: ");
    scanf("%s",play2);
    printf("\033[0m");

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            a[i][j]=' ';  //fills each cell with a space

        }
    }

    a[3][3]='O';
    a[4][4]='O';
    a[3][4]='X';
    a[4][3]='X';
    int turn=1;
    char x;
    while(turn<=100){
        if(turn%2==1){
            x='X';
            printf("\033[5;36m");
            printf("\n\n%s's Turn (X)\n",play1);
        }else{
          x='O';
          printf("\n\n%s's Turn (O)\n",play2);
          printf("\033[0m");
        }
         printf("\033[0m");  //part which prints the box
         printf("     1    2    3    4    5    6    7    8   \n");
         printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
         for(int i=0;i<8;i++){
            printf("%d ",i+1);
            for(int j=0;j<8;j++){
                printf("| %c  ",a[i][j]);
                }
            printf("|\n");
             printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");

        }
        printf("\033[32m");
        printf("Enter your input (row col): ");   //input part which takes the place where x or o will be chosen to be placed
        printf("\033[0m");
        scanf("%d %d",&row,&col);
         row--;
         col--;



        if (row>=0&&row<8&&col>=0&&col<8&&a[row][col]==' '){   //condition to increase turn
            a[row][col] = x;
            turn++;

        } else {         //incase of invalid move which is a move which is already occupied
          printf("\033[31m");
          printf("invalid!!!!\n");
          printf("\033[0m");
                  continue;
                   } //eight conditions to check sandwich and flip if possible
        int A=func(a,x,row,col,1,0,0),    //row check direction in right
            B=func(a,x,row,col,-1,0,0),//row check direction in left
            C=func(a,x,row,col,0,1,0), //column check in direction of positive y
            D=func(a,x,row,col,0,-1,0),//column check in direction of negative y
            E=func(a,x,row,col,1,1,0), //diagonally northeast
            F=func(a,x,row,col,-1,-1,0), //diagonally south-west
            G=func(a,x,row,col,1,-1,0), //diagonally south-east
            H=func(a,x,row,col,-1,1,0); //diagonally north-west
            if((A==0&&B==0&&C==0&&D==0&&E==0&&F==0&&G==0&&H==0)){  //when all these conditions are returning 0, means no sandwich occurs and hence no flipping occurs
                                                                 //makes the move invalid
            printf("\033[31m");
            printf("\nPLAYER HAS ENTERED INVALID MOVE\nENTER AGAIN.\n");
            printf("\033[0m");
                    a[row][col]=' ';
                  turn--; //reduces the turn as we are keeping a count of only valid turns
                  continue; //continues
            }

        if(declare_result(a)==1){  //when declare result returns 1 means game has ended
            printf("\033[0m");
             printf("     1    2    3    4    5    6    7    8   \n");  //prints the final board
         printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
         for(int i=0;i<8;i++){
            printf("%d ",i+1);
        for(int j=0;j<8;j++){
            printf("| %c  ",a[i][j]);
            }
            printf("|\n");
             printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
        }
            printf("\033[33m");
            printf("Would you like to end the game or restart?\n To RESTART press '1' to exit press '0': "); //for restart and exit
            int option;

            scanf("%d",&option);
            if(option==1){ //restart
                main(); //returns back to main
            }
            if(option==0){ //exits
                printf("\033[36m");
                printf("GAME OVER. BYE!"); //game ends and exits
                 printf("\033[0m");
                exit(0);
            }

            else{
                printf("\033[31m");
                printf("you've entered a wrong input. try again.\n restart='1' and exit='0' : "); //incase an invalid number is entered then scanfs goes again
                scanf("%d",&option);
                if(option==1){
                    main();
                }
                if(option==0){
                    printf("\033[36m");
                    printf("GAME OVER.\n");
                     printf("\033[0m");
                    exit(0);
                }
            }
        }
        if(!endgame(a,turn)){  //when the function endgame implements which means when all the boxes are occupied by either x or o
            printf("\033[0m");
              printf("     1    2    3    4    5    6    7    8   \n");
         printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
         for(int i=0;i<8;i++){
            printf("%d ",i+1);
        for(int j=0;j<8;j++){
            printf("| %c  ",a[i][j]);
            }
            printf("|\n");
             printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
        }
            printf("\033[33m");
            printf("There is no possible chance for them to play. Therefore, the game ends.\n would you like to end the game or restart?\n To RESTART press '1' to exit press '0' : ");
            int option;

            scanf("%d",&option);
            if(option==1){
                main();
            }
            if(option==0){
                printf("\033[36m");
                printf("GAME OVER. BYE!"); //bye bye
                 printf("\033[0m");
                exit(0);
            }

            else{
                printf("\033[31m");
                printf("you've entered a wrong input. try again.\n restart='1' and exit='0' : ");  //incase none of 0 or 1 is entered
                scanf("%d",&option);
                if(option==1){
                    main();
                }
                if(option==0){
                    printf("\033[36m");
                    printf("GAME OVER.\n"); //game ends
                     printf("\033[0m");
                    exit(0);
                }
            }
        }
 if(turn%2==1){   //code which checks when the turn should be passed to next player
            x='X';

        }else{
          x='O';

        }
      int s=0,t=0; //t=0 is when ohas no chance to flip x and vice versa with s and o
        for(int m=0;m<8;m++){
            for(int n=0;n<8;n++){
            if(a[m][n]==' '){
            if(func(a,x,m,n,1,0,1)==1||func(a,x,m,n,-1,0,1)==1||func(a,x,m,n,0,1,1)==1||func(a,x,m,n,0,-1,1)==1||func(a,x,m,n,1,1,1)==1||
            func(a,x,m,n,1,-1,1)==1||func(a,x,m,n,-1,-1,1)==1||func(a,x,m,n,-1,1,1)==1){
                  s=1;
                  break;
            }
            }
            }
        }
        if(x=='x'){ //flips
            y='O';
        }
        else if(x=='O'){ //flips
            y='X';
        }
        for(int m=0;m<8;m++){  //checks if there is no nearby surrounding slots which can be occupied to flip the other
            for(int n=0;n<8;n++){
            if(a[m][n]==' '){
            if(func(a,y,m,n,1,0,1)==1||func(a,y,m,n,-1,0,1)==1||func(a,y,m,n,0,1,1)==1||func(a,y,m,n,0,-1,1)==1||func(a,y,m,n,1,1,1)==1||
            func(a,y,m,n,1,-1,1)==1||func(a,y,m,n,-1,-1,1)==1||func(a,y,m,n,-1,1,1)==1){
                  t=1;
                  break;
            }
            }
            }
        }
        if(s==0&&t==0){ //neither of them is able to sandwich anything, game ends
            printf("\033[0m");
            printf("     1    2    3    4    5    6    7    8   \n");
         printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
         for(int i=0;i<8;i++){
            printf("%d ",i+1);
        for(int j=0;j<8;j++){
            printf("| %c  ",a[i][j]);
            }
            printf("|\n");
             printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
        }
            printf("\033[33m");
            printf("There is no possible chance for them to play. Therefore, the game ends.\n would you like to end the game or restart?\n To RESTART press '1' to exit press '0': ");
            int option;//option is for restart or exit

            scanf("%d",&option);
            if(option==1){
                main();//return to main to restart
            }
            if(option==0){
                printf("\033[36m");
                printf("GAME OVER. BYE!");
                 printf("\033[0m");
                exit(0); //exits when 0
            }
        }
        else if(s==0){ //when s==0 then the respective has no move to paly and hence needs to pass his turn
            printf("\033[33m");
                printf("\nPlayer %c has no valid moves and needs to pass \n",x);
                 printf("\033[0m");
                 printf("     1    2    3    4    5    6    7    8   \n");
         printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
         for(int i=0;i<8;i++){
            printf("%d ",i+1);
        for(int j=0;j<8;j++){
            printf("| %c  ",a[i][j]);
            }
            printf("|\n");
             printf("   ---- ---- ---- ---- ---- ---- ---- ----  \n");
        }
         printf("Press 1 to pass : "); //2 passes the turn to next player
        int pass;
        scanf("%d",&pass );
        if(pass==1){
            p++;
           turn++;
           continue;
        }
        else{
             printf("\033[31m");
            printf("Wrong input\n Press 1 to pass : ");
             printf("\033[0m");
         scanf("%d",&pass );
        if(pass==1){
            p++;
           turn++;
           continue;
        }
        }
        }
    }


    return 0;
}


