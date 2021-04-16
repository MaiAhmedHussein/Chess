#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>



//A function to store the eaten white and black pieces after each turn to be used by in the redo and undo parts.
void undoeat(char eatenb[20000][16], char eatenw[20000][16], char eatenB[16],char eatenW[16],int U){

    //Storing the eating pieces in each turn during the game.
    for(int i=0;i<16;i++){
        eatenb[U][i]=eatenB[i];
        eatenw[U][i]=eatenW[i];
    }

    return;
}



//A function to store the chess board after each turn to be used in the redo and undo parts.
void undo(char chessboard[8][8],char undoboard[20000][8][8],int U){

    //Storing the chess board in each turn during the game.
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            undoboard[U][i][j]=chessboard[i][j];
        }
    }

    return;
}



//A function to save the game (save the last chess board contents, the eaten pieces,and the next turn player) if the players want to save it and load it in other time to continue their game.
void save(char chessboard[8][8],bool gamer,char eatenB[16],char eatenW[16]){

    printf("Please, Enter File Name: \n");
    char file_name[100],M;
    scanf("%c",&M);
    gets(file_name);

    //Making a file with name entered by the user. Then opening it.
    FILE*f;
    f=fopen(file_name,"w");

    //Saving the chessboard at that desired time that he wanted to save.
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            putc(chessboard[i][j],f);

        }
    }

  //Saving the eaten pieces.
  for(int i=0;i<16;i++){
    putc(eatenB[i],f);
  }

  for(int i=0;i<16;i++){
    putc(eatenW[i],f);
  }


  //Saving the next turn's player.
  if(gamer==false){
       int k=0;
       putw(k,f);

  }else{
       int j=1;
       putw(j,f);
  }


   //Closing the file.
    fclose(f);

    return;

}



//A function to load a previous game played by the players to continue it, it gets from a saved file 3 things:(the last chess board contents, the eaten pieces, and the next turn player).
bool load(char chessboard[8][8],char eatenB[16],char eatenW[16]){

    char File_Name[100],y,x;
    scanf("%c",&x);

    FILE*f;

    //Checking if the file name entered by the user is found or not. Then opening that file if it is found.
    while(1){
        printf("\nEnter File Name: ");
        gets(File_Name);

        f=fopen(File_Name,"r");

        if(f){
            break;

        }else{
            printf("\nNot Found\n");
        }
    }

    //Getting the chess board contents and positions of each pieces.
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
               y=getc(f);
            chessboard[i][j]=y;
        }
    }


   //Getting the eaten pieces.
   char z,r;
   for(int i=0;i<16;i++){
    z=getc(f);
    eatenB[i]=z;
  }

  for(int i=0;i<16;i++){
    r=getc(f);
    eatenW[i]=r;
  }


  //Getting the next turn's player. It will return true if it's black's turn and it will return false if it's white's turn.
    if(getw(f)==0){
        fclose(f);
        return true;

    }else{
        fclose(f);
        return false;
    }



}



//A function to check if there is a dead position (k vs k) or (k vs k&b)or (k vs k&n) or (k&b vs k&b of same color squares bishops) and vice versa.
//If it is a dead position it return true if not it return false.
bool drawstate(char chessboard[8][8]){

   int p1=0,p2=0,p3=0,p4=0,p5=0,p6=0,p7=0,p8=0,p9=0,p10=0;

   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        switch(chessboard[i][j]){
            case 'q':{ p1++; break;}
            case 'Q':{ p2++; break;}
            case 'r':{ p3++; break;}
            case 'R':{ p4++; break;}
            case 'n':{ p5++; break;}
            case 'N':{ p6++; break;}
            case 'b':{ p7++; break;}
            case 'B':{ p8++; break;}
            case 'p':{ p9++; break;}
            case 'P':{ p10++;break;}

        }
    }
   }

   if(p1==0 && p2==0 && p3==0 && p4==0 && p9==0 && p10==0){

      //k vs K:
      if(p5==0 && p6==0 && p7==0 && p8==0){
        return true;

      //k vs K&N  or k&n vs K :
      }else if((p5==1 && p6==0 && p7==0 && p8==0) || (p5==0 && p6==1 && p7==0 && p8==0)){
        return true;

      //k vs K&B or k&b vs K:
      }else if((p5==0 && p6==0 && p7==1 && p8==0) || (p5==0 && p6==0 && p7==0 && p8==1)){
          return true;

      //k&b vs K&B and the bishops are on the same color squares.
      }else if((p5==0 && p6==0 && p7==1 && p8==1)){
          int f,g,h,n,k,o;

           for(int i=0;i<8;i++){
             for(int j=0;j<8;j++){
               if(chessboard[i][j]=='b'){
                   f=i;
                   g=j;
               }
             }
           }


            for(int i=0;i<8;i++){
             for(int j=0;j<8;j++){
               if(chessboard[i][j]=='B'){
                   h=i;
                   n=j;
               }
             }
           }


        if((f%2==0 && g%2==0)||(f%2!=0 && g%2!=0)){
            k=1;

        }else{
            k=0;
        }

        if((h%2==0 && n%2==0)||(h%2!=0 && n%2!=0)){

            o=1;
        }else{
            o=0;
        }


        if((k==1 && o==1) || (k==0 && o==0)){
            return true;
        }else{
            return false;
        }

    }else{
          return false;
    }


   }else{
     return false;
   }

}



//This function checks if the turn player's king is in check or not.
//If any other piece attacks the king and makes it in check, the function will return 1 if not the function will return 0.
int movecheck(char chessboard[8][8],bool gamer){

  int x=9,y=9;
  if(gamer==false){


   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        if(chessboard[i][j]=='k'){
            x=i;
            y=j;
        }
    }
   }


   if(x==9 && y==9){
    return 0;
   }

   //Checking if there is check by any white rook or white queen.
   for(int k=y-1;k>=0;k--){
     if(chessboard[x][k]=='R' || chessboard[x][k]=='Q'){
        return 1;
     }else if(chessboard[x][k]!='Q' && chessboard[x][k]!='R' && chessboard[x][k]!='-' && chessboard[x][k]!='.'){
         break;
     }
   }


   for(int k=y+1;k<=7;k++){
     if(chessboard[x][k]=='R' || chessboard[x][k]=='Q'){
        return 1;
     }else if(chessboard[x][k]!='Q' && chessboard[x][k]!='R' && chessboard[x][k]!='-' && chessboard[x][k]!='.'){
         break;
     }
   }


   for(int k=x-1;k>=0;k--){
     if(chessboard[k][y]=='R' || chessboard[k][y]=='Q'){
        return 1;
     }else if(chessboard[k][y]!='Q' && chessboard[k][y]!='R' && chessboard[k][y]!='-' && chessboard[k][y]!='.'){
         break;
     }
   }


   for(int k=x+1;k<=7;k++){
     if(chessboard[k][y]=='R' || chessboard[k][y]=='Q'){
                return 1;
     }else if(chessboard[k][y]!='Q' && chessboard[k][y]!='R' && chessboard[k][y]!='-' && chessboard[k][y]!='.'){
         break;
     }
   }


   //Checking if there is any check by any white queen or white bishop.
   if(y>=x){
    for(int k=1;k<=x;k++){
     if(chessboard[x-k][y-k]=='Q' || chessboard[x-k][y-k]=='B'){
             return 1;
     }else if(chessboard[x-k][y-k]!='Q' && chessboard[x-k][y-k]!='B' && chessboard[x-k][y-k]!='-' && chessboard[x-k][y-k]!='.'){
         break;
     }

    }


    for(int k=1;k<=7-y;k++){
     if(chessboard[x+k][y+k]=='Q' || chessboard[x+k][y+k]=='B'){
        return 1;
     }else if(chessboard[x+k][y+k]!='Q' && chessboard[x+k][y+k]!='B' && chessboard[x+k][y+k]!='-' && chessboard[x+k][y+k]!='.'){
         break;
     }
    }


   }else if(y<x){

     for(int k=1;k<=y;k++){
      if(chessboard[x-k][y-k]=='Q' || chessboard[x-k][y-k]=='B'){
        return 1;
      }else if(chessboard[x-k][y-k]!='Q' && chessboard[x-k][y-k]!='B' && chessboard[x-k][y-k]!='-' && chessboard[x-k][y-k]!='.'){
         break;
     }
    }


    for(int k=1;k<=7-x;k++){
     if(chessboard[x+k][y+k]=='Q' || chessboard[x+k][y+k]=='B'){
        return 1;
     }else if(chessboard[x+k][y+k]!='Q' && chessboard[x+k][y+k]!='B' && chessboard[x+k][y+k]!='-' && chessboard[x+k][y+k]!='.'){
         break;
     }
    }

   }


 if(x<=(7-y)){

      for(int k=1;k<=x;k++){
      if(chessboard[x-k][y+k]=='Q' || chessboard[x-k][y+k]=='B'){
        return 1;
      }else if(chessboard[x-k][y+k]!='Q' && chessboard[x-k][y+k]!='B' && chessboard[x-k][y+k]!='-' && chessboard[x-k][y+k]!='.'){
         break;
     }

    }


    for(int k=1;k<=y;k++){
     if(chessboard[x+k][y-k]=='Q' || chessboard[x+k][y-k]=='B'){
        return 1;
     }else if(chessboard[x+k][y-k]!='Q' && chessboard[x+k][y-k]!='B' && chessboard[x+k][y-k]!='-' && chessboard[x+k][y-k]!='.'){
         break;
     }
    }


   }else if(x>(7-y)){

    for(int k=1;k<=(7-y);k++){
      if(chessboard[x-k][y+k]=='Q' || chessboard[x-k][y+k]=='B'){
           return 1;
      }else if(chessboard[x-k][y+k]!='Q' && chessboard[x-k][y+k]!='B' && chessboard[x-k][y+k]!='-' && chessboard[x-k][y+k]!='.'){
         break;
     }

    }


    for(int k=1;k<=7-x;k++){
     if(chessboard[x+k][y-k]=='Q' || chessboard[x+k][y-k]=='B'){
        return 1;
     }else if(chessboard[x+k][y-k]!='Q' && chessboard[x+k][y-k]!='B' && chessboard[x+k][y-k]!='-' && chessboard[x+k][y-k]!='.'){
         break;
     }
    }

   }



   //Checking if there is any check by any white knight.
   if((chessboard[x+1][y+2]=='N' && x<7 && y<6) || (chessboard[x+1][y-2]=='N' && x<7 && y>1) || (chessboard[x-1][y+2]=='N' && x>0 && y<6) || (chessboard[x-1][y-2]=='N' && x>0 && y>1) || (chessboard[x+2][y+1]=='N' && x<6 && y<7) || (chessboard[x+2][y-1]=='N' && x<6 && y>0) || (chessboard[x-2][y+1]=='N' && x>1 && y<7) || (chessboard[x-2][y-1]=='N' && x>1 && y>0)){

     return 1;
   }


   //Checking if there is any check by any white pawn.
   if((chessboard[x+1][y-1]=='P' && x<7 && y>0) || (chessboard[x+1][y+1]=='P' && x<7 && y<7)){

    return 1;
   }


    //Checking if there is any check by the white king.
    if((chessboard[x+1][y]=='K' && x<7) || (chessboard[x-1][y]=='K' && x>0) || (chessboard[x][y+1]=='K' && y<7) || (chessboard[x][y-1]=='K' && y>0) || (chessboard[x+1][y+1]=='K' && x<7 && y<7) || (chessboard[x-1][y-1]=='K' && x>0 && y>0) || (chessboard[x+1][y-1]=='K' && x<7 && y>0) || (chessboard[x-1][y+1]=='K' && x>0 && y<7)){

     return 1;
   }




 }else{

   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        if(chessboard[i][j]=='K'){
            x=i;
            y=j;
        }
    }
   }


   if(x==9 && y==9){
    return 0;
   }


   //Checking if there is any check by any black rook or black queen.
   for(int k=y-1;k>=0;k--){
     if(chessboard[x][k]=='r' || chessboard[x][k]=='q'){
        return 1;
     }else if(chessboard[x][k]!='q' && chessboard[x][k]!='r' && chessboard[x][k]!='-' && chessboard[x][k]!='.'){
         break;
     }
   }


   for(int k=y+1;k<=7;k++){
     if(chessboard[x][k]=='r' || chessboard[x][k]=='q'){
        return 1;
     }else if(chessboard[x][k]!='q' && chessboard[x][k]!='r' && chessboard[x][k]!='-' && chessboard[x][k]!='.'){
         break;
     }
   }


   for(int k=x-1;k>=0;k--){
     if(chessboard[k][y]=='r' || chessboard[k][y]=='q'){
        return 1;
     }else if(chessboard[k][y]!='q' && chessboard[k][y]!='r' && chessboard[k][y]!='-' && chessboard[k][y]!='.'){
         break;
     }
   }


   for(int k=x+1;k<=7;k++){
     if(chessboard[k][y]=='r' || chessboard[k][y]=='q'){
        return 1;
     }else if(chessboard[k][y]!='q' && chessboard[k][y]!='r' && chessboard[k][y]!='-' && chessboard[k][y]!='.'){
         break;
     }
   }



   //Checking if there is any check by any black queen or black bishop.
   if(y>=x){
    for(int k=1;k<=x;k++){
     if(chessboard[x-k][y-k]=='q' || chessboard[x-k][y-k]=='b'){
         return 1;
     }else if(chessboard[x-k][y-k]!='q' && chessboard[x-k][y-k]!='b' && chessboard[x-k][y-k]!='-' && chessboard[x-k][y-k]!='.'){
         break;
     }

    }

    for(int k=1;k<=7-y;k++){
     if(chessboard[x+k][y+k]=='q' || chessboard[x+k][y+k]=='b'){
          return 1;
     }else if(chessboard[x+k][y+k]!='q' && chessboard[x+k][y+k]!='b' && chessboard[x+k][y+k]!='-' && chessboard[x+k][y+k]!='.'){
         break;
     }
    }


   }else if(y<x){


     for(int k=1;k<=y;k++){
      if(chessboard[x-k][y-k]=='q' || chessboard[x-k][y-k]=='b'){
             return 1;
      }else if(chessboard[x-k][y-k]!='q' && chessboard[x-k][y-k]!='b' && chessboard[x-k][y-k]!='-' && chessboard[x-k][y-k]!='.'){
         break;
     }

    }


    for(int k=1;k<=7-x;k++){
     if(chessboard[x+k][y+k]=='q' || chessboard[x+k][y+k]=='b'){
        return 1;
     }else if(chessboard[x+k][y+k]!='q' && chessboard[x+k][y+k]!='b' && chessboard[x+k][y+k]!='-' && chessboard[x+k][y+k]!='.'){
         break;
     }
    }

   }


   if(x<=(7-y)){
      for(int k=1;k<=x;k++){
      if(chessboard[x-k][y+k]=='q' || chessboard[x-k][y+k]=='b'){
           return 1;
      }else if(chessboard[x-k][y+k]!='q' && chessboard[x-k][y+k]!='b' && chessboard[x-k][y+k]!='-' && chessboard[x-k][y+k]!='.'){
         break;
     }

    }


    for(int k=1;k<=y;k++){
     if(chessboard[x+k][y-k]=='q' || chessboard[x+k][y-k]=='b'){
           return 1;
     }else if(chessboard[x+k][y-k]!='q' && chessboard[x+k][y-k]!='b' && chessboard[x+k][y-k]!='-' && chessboard[x+k][y-k]!='.'){
         break;
     }
    }


   }else if(x>(7-y)){

    for(int k=1;k<=(7-y);k++){
      if(chessboard[x-k][y+k]=='q' || chessboard[x-k][y+k]=='b'){
              return 1;
      }else if(chessboard[x-k][y+k]!='q' && chessboard[x-k][y+k]!='b' && chessboard[x-k][y+k]!='-' && chessboard[x-k][y+k]!='.'){
         break;
     }

    }

    for(int k=1;k<=7-x;k++){
     if(chessboard[x+k][y-k]=='q' || chessboard[x+k][y-k]=='b'){
            return 1;
     }else if(chessboard[x+k][y-k]!='q' && chessboard[x+k][y-k]!='b' && chessboard[x+k][y-k]!='-' && chessboard[x+k][y-k]!='.'){
         break;
     }
    }

   }



   //Checking if there is any check by any black knight.
   if((chessboard[x+1][y+2]=='n' && x<7 && y<6) || (chessboard[x+1][y-2]=='n' && x<7 && y>1) || (chessboard[x-1][y+2]=='n' && x>0 && y<6) || (chessboard[x-1][y-2]=='n' && x>0 && y>1) || (chessboard[x+2][y+1]=='n' && x<6 && y<7) || (chessboard[x+2][y-1]=='n' && x<6 && y>0) || (chessboard[x-2][y+1]=='n' && x>1 && y<7) || (chessboard[x-2][y-1]=='n' && x>1 && y>0)){

     return 1;
   }


   //Checking if there is any check by any black pawn.
   if((chessboard[x-1][y+1]=='p' && x>0 && y<7) || (chessboard[x-1][y-1]=='p' && x>0 && y>0 )){

    return 1;
   }


   //Checking if there is any check by the black king.
   if((chessboard[x+1][y]=='k' && x<7) || (chessboard[x-1][y]=='k' && x>0) || (chessboard[x][y+1]=='k' && y<7) || (chessboard[x][y-1]=='k' && y>0) || (chessboard[x+1][y+1]=='k' && x<7 && y<7) || (chessboard[x-1][y-1]=='k' && x>0 && y>0) || (chessboard[x+1][y-1]=='k' && x<7 && y>0) || (chessboard[x-1][y+1]=='k' && x>0 && y<7)){

     return 1;
   }


   }

   return 0;
}


//This function checks if the played move is valid for this pawn or not. The pawn can move 2 steps forward if it is the first time to move other than it can only move one step forward.
//It eats diagonally one step. The function will return true if this played move is valid if not it will return false.
bool pawnmovevalidity(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

    int v;

    if((i1==1 || i1==6)&& abs(i2-i1)==2){
       v=2;
    }else{
        v=1;
    }


    if((j1==j2 && i2-i1==v && gamer==false)||(j1==j2 && i1-i2==v && gamer==true)|| (abs(j2-j1)==1 && i2-i1==1 && gamer==false) || (abs(j2-j1)==1 && i1-i2==1 && gamer==true)){

        if((j1==j2 && i2-i1==v && gamer==false)||(j1==j2 && i1-i2==v && gamer==true)){

            if(chessboard[i2][j2]!= '.' && chessboard[i2][j2]!= '-'){
                valid=false;
            }else{
                valid=true;
            }

            if(valid==true){

            for(int i=1;i<v;i++){

            if((i2>i1 &&chessboard[i1+i][j1]=='.' ||chessboard[i1+i][j1]=='-' )||(i2<i1 && chessboard[i1-i][j1]=='.'|| chessboard[i1-i][j1]=='-')){
                valid=true;

            }else{
                valid=false;
                break;
              }
             }
            }

        }else if((abs(j2-j1)==1 && i2-i1==1 && gamer==false) || (abs(j2-j1)==1 && i1-i2==1 && gamer==true)){

            if(chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
                valid=false;
            }else{
                valid=true;
            }
        }


    if(gamer==false && valid==true){

          if(isupper(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
            valid=true;
          }else{
            valid=false;
          }

    }else if (gamer==true && valid==true){

          if(islower(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
            valid=true;
          }else{
            valid=false;
          }
    }

       return valid;

    }else{
        valid = false;
        return valid;
    }

}




//This function checks if the played move is valid for this knight or not. The knight move like L shape (2+1 or 1+2).
//The function will return true if this played move is valid if not will return false.
bool knightmovevalidity(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

    if((abs(i2-i1)==2 && abs(j2-j1)==1)|| (abs(j2-j1)==2 && abs(i2-i1)==1)){

        valid=true;

        if(gamer==false && valid==true){
          if(isupper(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
            valid=true;
          }else{
            valid=false;
          }

       }else if (gamer==true && valid==true){
          if(islower(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
            valid=true;
          }else{
            valid=false;
          }
       }

       return valid;

    }else{
        valid = false;
        return valid;
    }
}




//This function checks if the played move is valid for the king or not. The king moves one step in any direction.
//The function will return true if this played move is valid if not it will return false.
bool kingmovevalidity(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

     if((i1==i2 && abs(j2-j1)==1)|| (j1==j2 && abs(i2-i1)==1) || (abs(i1-i2)==1 && abs(j1-j2)==1)){
        valid= true;

        if(gamer==false && valid==true){

           if(isupper(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
              valid=true;
           }else{
              valid=false;
           }

        }else if(gamer==true && valid==true){

           if(islower(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
              valid=true;
           }else{
              valid=false;
           }
        }

        return valid;

    }else{

        valid=false;
        return valid;
    }
}




//This function checks if the played move is valid for this rook or not. The rook moves any number of steps to the right or to the left or forward or backward if there is nothing in it's way.
//The function will return true if this played move is valid if not it will return false.
bool rookmovevalidity(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

    if(i1==i2 || j1==j2){

      if(i1==i2){
        for(int j=1;j<abs(j1-j2);j++){
            if((j2>j1 &&chessboard[i1][j1+j]=='.' ||chessboard[i1][j1+j]=='-' )||(j2<j1 && chessboard[i1][j1-j]=='.'|| chessboard[i1][j1-j]=='-')){
                valid=true;

            }else{
                valid=false;
                break;
            }
        }

       }else if(j1==j2){

           for(int i=1;i<abs(i1-i2);i++){
            if((i2>i1 &&chessboard[i1+i][j1]=='.' ||chessboard[i1+i][j1]=='-' )||(i2<i1 && chessboard[i1-i][j1]=='.'|| chessboard[i1-i][j1]=='-')){
               valid=true;

            }else{
                valid=false;
                break;
            }
        }

       }

    if(gamer==false && valid==true){

      if(isupper(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
        valid=true;
    }else{
        valid=false;
    }

    }else if(gamer==true && valid==true){

      if(islower(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
        valid=true;
    }else{
        valid=false;
    }
    }

    return valid;

    }else{

        valid=false;
        return valid;
    }

}




//This function checks if the played move is valid for this bishop or not. The bishop moves any number of steps diagonally if there is nothing in it's way.
//The function will return true if this played move is valid if not it will return false.
bool bishopmovevalidity(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

     if(abs(i1-i2)==abs(j1-j2)){

       if(abs(i1-i2)==abs(j1-j2)){

           for(int i=1;i<abs(i1-i2);i++){

            if((i2>i1 && j2>j1 && (chessboard[i1+i][j1+i]=='.' ||chessboard[i1+i][j1+i]=='-'))||(i2<i1 && j2<j1 && (chessboard[i1-i][j1-i]=='.'|| chessboard[i1-i][j1-i]=='-')) || (i2>i1 && j2<j1 && (chessboard[i1+i][j1-i]=='.' ||chessboard[i1+i][j1-i]=='-' )) || (i2<i1 && j2>j1 && (chessboard[i1-i][j1+i]=='.' ||chessboard[i1-i][j1+i]=='-' ))){
                valid=true;

            }else{
                valid=false;
                break;
            }
         }
       }


    if(gamer==false && valid==true){

      if(isupper(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
        valid=true;
    }else{
        valid=false;
    }

    }else if(gamer==true && valid==true){

      if(islower(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
        valid=true;
    }else{
        valid=false;
    }
    }

    return valid;

    }else{

        valid=false;
        return valid;
    }

}




//This function checks if the played move is valid for this queen or not. The queen moves any number of steps in any direction if there is nothing in it's way.
//The function will return true if this played move is valid if not it will return false.
bool queenmovevalidity(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

    if(i1==i2 || j1==j2 || (abs(i1-i2)==abs(j1-j2))){

      if(i1==i2){

        for(int j=1;j<abs(j1-j2);j++){

            if((j2>j1 &&chessboard[i1][j1+j]=='.' ||chessboard[i1][j1+j]=='-' )||(j2<j1 && chessboard[i1][j1-j]=='.'|| chessboard[i1][j1-j]=='-')){
                valid=true;

            }else{
                valid=false;
                break;
            }
        }

       }else if(j1==j2){

           for(int i=1;i<abs(i1-i2);i++){

            if((i2>i1 &&chessboard[i1+i][j1]=='.' ||chessboard[i1+i][j1]=='-' )||(i2<i1 && chessboard[i1-i][j1]=='.'|| chessboard[i1-i][j1]=='-')){
               valid=true;

            }else{
                valid=false;
                break;
            }
        }

       }else if(abs(i1-i2)==abs(j1-j2)){

           for(int i=1;i<abs(i1-i2);i++){

            if((i2>i1 && j2>j1 && (chessboard[i1+i][j1+i]=='.' ||chessboard[i1+i][j1+i]=='-'))||(i2<i1 && j2<j1 && (chessboard[i1-i][j1-i]=='.'|| chessboard[i1-i][j1-i]=='-')) || (i2>i1 && j2<j1 && (chessboard[i1+i][j1-i]=='.' ||chessboard[i1+i][j1-i]=='-' )) || (i2<i1 && j2>j1 && (chessboard[i1-i][j1+i]=='.' ||chessboard[i1-i][j1+i]=='-' ))){
                valid=true;

            }else{
                valid=false;
                break;
            }
         }
       }

    if(gamer==false && valid==true){

      if(isupper(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
        valid=true;
      }else{
        valid=false;
      }

    }else if(gamer==true && valid==true){

      if(islower(chessboard[i2][j2])|| chessboard[i2][j2]=='.' || chessboard[i2][j2]=='-'){
        valid=true;
       }else{
        valid=false;
       }
    }

    return valid;

    }else{

        valid=false;
        return valid;
    }

}





//This function take the pieces to be moved and then see if this piece belong to that player or not, if it's from his pieces it will then call the function that checks the validity of that move according to this piece's type(knight, rook,...etc).
//If it's not one of his pieces it will return false which means that this move is invalid.
bool movechoose(char chessboard[8][8],int i1,int i2,int j1,int j2,bool valid,bool gamer){

     if(gamer==false){

       if(islower(chessboard[i1][j1])){
        valid=true;
       }else{
        return false;

       }

   }else{

       if(isupper(chessboard[i1][j1])){
        valid=true;
       }else{
           return false;

       }
   }


   switch(tolower(chessboard[i1][j1])){
       case 'q':{
         valid =  queenmovevalidity(chessboard,i1,i2,j1,j2,valid,gamer);
         return valid;
         break;
       }
       case 'b':{
           valid = bishopmovevalidity(chessboard,i1,i2,j1,j2,valid,gamer);
           return valid;
           break;

       }
       case 'r':{
           valid = rookmovevalidity(chessboard,i1,i2,j1,j2,valid,gamer);
           return valid;
           break;
       }
       case 'k':{
           valid = kingmovevalidity(chessboard,i1,i2,j1,j2,valid,gamer);
           return valid;
           break;
       }
       case 'n':{
           valid = knightmovevalidity(chessboard,i1,i2,j1,j2,valid,gamer);
           return valid;
           break;
       }
       case 'p':{
           valid = pawnmovevalidity(chessboard,i1,i2,j1,j2,valid,gamer);
           return valid;
           break;
       }
       case '.':{
           valid = false;
           return valid;
           break;
       }
       case '-':{
           valid = false;
           return valid;
           break;
       }


    }
}




//This function loops over the whole board and checks the validity of moving each piece of this turn's player, if he can move at least one of his pieces a valid move and without making his king in check.
//Then the function will return 0 which means that there is neither stalemate nor checkmate.
//If there is no valid moves to be played, then it will return 1 and then in boardinit function it will be either a checkmate if the king was in check already, or a stalemate if the king was not in check.
int allmovesinvalid(char chessboard[8][8],bool gamer){



    bool valid1=false;

     char chessc[8][8];
   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        chessc[i][j]=chessboard[i][j];
    }
   }


   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        for(int s=0;s<8;s++){
            for(int g=0;g<8;g++){

                  char t=chessc[i][j];
                  char z=chessc[s][g];
                  bool h=movechoose(chessc,i,s,j,g,valid1,gamer);
                  char m =chessc[i][j];

                  if((i%2==0 && j%2==0)||(i%2!=0 && j%2!=0)){
                     chessc[i][j]='.';
                     chessc[s][g]=m;

                  }else{
                     chessc[i][j]='-';
                     chessc[s][g]=m;
                  }


                  int a=movecheck(chessc,gamer);
                  if( h==true && a==0){
                    return 0;

                  }else{
                      chessc[i][j]=t;
                      chessc[s][g]=z;
                  }
               }

          }
        }
    }


   return 1;

}




//This function is the most important one it calls most of the functions and makes the moves in the board after checking their validity.
//It call itself after each move and print the chess board every turn till there is checkmate, stalemate, or dead position(i.e. till one of the 2 players win or there is a draw).
//In this function every turn it asks the player to either play, undo, redo, save, or exit.
//If there is stalemate,checkmate, or dead position, it directly printing a message either win or draw and then the program will end.
//If the pawn move to his opposite last row, it will promoted to either queen, rook, bishop, or knight according to the user desire.
void boardinit(char chessboard[8][8],bool gamer,char eatenB[16],char eatenW[16],int q,int w,char undoboard[20000][8][8],char eatenb[20000][16],char eatenw[20000][16]){


   static int U=0,X=0;

   //Storing each turn's chess board contents in undoboard array, and eaten pieaces in eatenw, eatenb arrays.
   undo(chessboard,undoboard,U);
   undoeat(eatenb,eatenw,eatenB,eatenW,U);

   U++;


   char chessb[8][8];
   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        chessb[i][j]=chessboard[i][j];
    }
   }




   if(gamer==true){

       gamer=false;
        int d = movecheck(chessboard,gamer);
        int e = allmovesinvalid(chessboard,gamer);


    //Checks if there is stalemate, checkmate, or dead position.
    if(d==1 && e==1){

        if(gamer==false){

            system("color D");
            printf("\nCHECKMATE!! WINNER IS THE WHITE PLAYER!! CONGRATULATIONS!!\n\n");
            printf("                         __ " );
            printf("\n                       ,    . ");
            printf("\n    _      .---.    _ /#     \\ ");
            printf("\n  ,' `.  ,'     `..' '.      ,--. ");
            printf("\n  |#   `/ #      (#    )    /    ) ");
            printf("\n   `.   |         )   (`.__/    / ");
            printf("\n     `. \\        (     )/'/    / ");
            printf("\n       `.\\       /)   (( /    / ");
            printf("\n          `.   .'(     )y    / ");
            printf("\n            >_<\\  `._.'(    / ");
            printf("\n            /   ) /'-`.->,-' ");
            printf("\n           (   ( (   ( ");
            printf("\n             )     )   ) ");
            printf("\n                  ( \n\n");

            return;

        }else{

            system("color D");
            printf("\nCHECKMATE!! WINNER IS THE BLACK PLAYER!! CONGRATULATIONS!!\n\n");
            printf("                         __ " );
            printf("\n                       ,    . ");
            printf("\n    _      .---.    _ /#     \\ ");
            printf("\n  ,' `.  ,'     `..' '.      ,--. ");
            printf("\n  |#   `/ #      (#    )    /    ) ");
            printf("\n   `.   |         )   (`.__/    / ");
            printf("\n     `. \\        (     )/'/    / ");
            printf("\n       `.\\       /)   (( /    / ");
            printf("\n          `.   .'(     )y    / ");
            printf("\n            >_<\\  `._.'(    / ");
            printf("\n            /   ) /'-`.->,-' ");
            printf("\n           (   ( (   ( ");
            printf("\n             )     )   ) ");
            printf("\n                  ( \n\n");

            return;

        }

    }else if(d==0 && e==1){

        system("color D");
        printf("\nSTALEMATE!!\n\n");
        printf("\n\n       ______   _______  _______ ");
        printf("\n      (  __  \\ (  ____ )(  ___  )|\\     /| ");
        printf("\n      | (  \\  )| (    )|| (   ) || )   ( | ");
        printf("\n      | |   ) || (____)|| (___) || | _ | | ");
        printf("\n      | |   | ||     __)|  ___  || |( )| | ");
        printf("\n      | |   ) || (\\ (   | (   ) || || || | ");
        printf("\n      | (__/  )| ) \\ \\__| )   ( || () () | ");
        printf("\n      (______/ |/   \\__/|/     \\|(_______) \n\n");

        return;

    }

    bool draw = drawstate(chessboard);

    if(draw==true){

        system("color D");
        printf("\nDEAD POSITION!!\n\n");
        printf("\n\n       ______   _______  _______ ");
        printf("\n      (  __  \\ (  ____ )(  ___  )|\\     /| ");
        printf("\n      | (  \\  )| (    )|| (   ) || )   ( | ");
        printf("\n      | |   ) || (____)|| (___) || | _ | | ");
        printf("\n      | |   | ||     __)|  ___  || |( )| | ");
        printf("\n      | |   ) || (\\ (   | (   ) || || || | ");
        printf("\n      | (__/  )| ) \\ \\__| )   ( || () () | ");
        printf("\n      (______/ |/   \\__/|/     \\|(_______) \n\n");

        return;

    }

    printf("-----------------Black's Turn-------------------\n\n\n");

   }else{

    gamer=true;

    int d = movecheck(chessboard,gamer);
    int e = allmovesinvalid(chessboard,gamer);

    if(d==1 && e==1){

        if(gamer==false){

             system("color D");
             printf("\nCHECKMATE!! WINNER IS THE WHITE PLAYER!! CONGRATULATIONS!!\n\n");
             printf("                         __ " );
             printf("\n                       ,    . ");
             printf("\n    _      .---.    _ /#     \\ ");
             printf("\n  ,' `.  ,'     `..' '.      ,--. ");
             printf("\n  |#   `/ #      (#    )    /    ) ");
             printf("\n   `.   |         )   (`.__/    / ");
             printf("\n     `. \\        (     )/'/    / ");
             printf("\n       `.\\       /)   (( /    / ");
             printf("\n          `.   .'(     )y    / ");
             printf("\n            >_<\\  `._.'(    / ");
             printf("\n            /   ) /'-`.->,-' ");
             printf("\n           (   ( (   ( ");
             printf("\n             )     )   ) ");
             printf("\n                  ( \n\n");


            return;

        }else{

            system("color D");
            printf("\nCHECKMATE!! WINNER IS THE BLACK PLAYER!! CONGRATULATIONS!!\n\n");
            printf("                         __ " );
            printf("\n                       ,    . ");
            printf("\n    _      .---.    _ /#     \\ ");
            printf("\n  ,' `.  ,'     `..' '.      ,--. ");
            printf("\n  |#   `/ #      (#    )    /    ) ");
            printf("\n   `.   |         )   (`.__/    / ");
            printf("\n     `. \\        (     )/'/    / ");
            printf("\n       `.\\       /)   (( /    / ");
            printf("\n          `.   .'(     )y    / ");
            printf("\n            >_<\\  `._.'(    / ");
            printf("\n            /   ) /'-`.->,-' ");
            printf("\n           (   ( (   ( ");
            printf("\n             )     )   ) ");
            printf("\n                  ( \n\n");

            return;

        }

    }else if(d==0 && e==1){

         system("color D");
         printf("\nSTALEMATE!!\n\n");
         printf("\n\n       ______   _______  _______ ");
         printf("\n      (  __  \\ (  ____ )(  ___  )|\\     /| ");
         printf("\n      | (  \\  )| (    )|| (   ) || )   ( | ");
         printf("\n      | |   ) || (____)|| (___) || | _ | | ");
         printf("\n      | |   | ||     __)|  ___  || |( )| | ");
         printf("\n      | |   ) || (\\ (   | (   ) || || || | ");
         printf("\n      | (__/  )| ) \\ \\__| )   ( || () () | ");
         printf("\n      (______/ |/   \\__/|/     \\|(_______) \n\n");

        return;

    }

    bool draw = drawstate(chessboard);

    if(draw==true){

        system("color D");
        printf("\nDEAD POSITION!!\n\n");
        printf("\n\n       ______   _______  _______ ");
        printf("\n      (  __  \\ (  ____ )(  ___  )|\\     /| ");
        printf("\n      | (  \\  )| (    )|| (   ) || )   ( | ");
        printf("\n      | |   ) || (____)|| (___) || | _ | | ");
        printf("\n      | |   | ||     __)|  ___  || |( )| | ");
        printf("\n      | |   ) || (\\ (   | (   ) || || || | ");
        printf("\n      | (__/  )| ) \\ \\__| )   ( || () () | ");
        printf("\n      (______/ |/   \\__/|/     \\|(_______) \n\n");
        return;
    }

    printf("-----------------White's Turn-------------------\n\n\n");

   }



     if(movecheck(chessboard,gamer)==1){

        printf("\nCHECK!\n\n\n");

     }




     //Printing the chess board and the eaten pieces to be displayed to the players.


     printf("Chess pieces eaten by the Black Player: ");


     for(int i=0;i<16;i++){
        printf("%c ",eatenB[i]);
     }


     printf("\n\n\n   a b c d e f g h \n  -----------------\n");


    for(int i=0;i<8;i++){

        printf("%d| ",8-i);

        for(int j=0;j<8;j++){

            printf("%c ",chessboard[i][j]);

        }

        printf("|%d",8-i);
        printf("\n");

    }

    printf("  -----------------\n");
    printf("   a b c d e f g h \n\n\n");


    printf("Chess pieces eaten by the White Player: ");

     for(int i=0;i<16;i++){
        printf("%c ",eatenW[i]);
    }

    printf("\n\nIf you want to save enter 'S' , play enter 'P',undo enter 'U', redo enter 'R',exit enter 'E' :");



    char v;
    scanf(" %c",&v);


    //Checking if the player enter his choice correctly from the 5 options only.
    while(v!='S' && v!='P' && v!='U' && v!='R' && v!='E'){

        printf("\nEnter A Correct Choice!!:");
        scanf(" %c",&v);

    }


    //Checking if the user wants to undo if it wasn't the first turn. And if he wants to redo if he did not undo first.
    while((v=='U' && U==1) || (v=='R' && X==0)){

      while(v=='U'&&U==1){

            printf("\nInvalid Undo!! It's The First Turn!! Choose another option!!\nIf you want to save enter 'S' , play enter 'P',undo enter 'U', redo enter 'R',exit enter 'E' :");
            scanf(" %c",&v);

      }


        while(v=='R' && X==0){

            printf("\nInvalid Redo!! You Didn't Undo to Redo!! Choose another option!!\nIf you want to save enter 'S' , play enter 'P',undo enter 'U', redo enter 'R',exit enter 'E' :");
            scanf(" %c",&v);

        }

    }


    while(v!='S' && v!='P' && v!='U' && v!='R' && v!='E'){

        printf("\nEnter A Correct Choice!!:");
        scanf(" %c",&v);
    }



   if(v=='S'){

   //Calling the save function in order to save the game to continue it in other time.
    save(chessboard,gamer,eatenB,eatenW);

    return;

   }else if(v=='E'){
       //exiting the game.
       return;

   }else if(v=='U'){

    //Undoing the previous move.
             X++;
            U=U-2;

         for(int i=0;i<8;i++){

            for(int j=0;j<8;j++){
                chessboard[i][j]=undoboard[U][i][j];
            }
         }


         for(int i=0;i<16;i++){
            eatenB[i]=eatenb[U][i];
            eatenW[i]=eatenw[U][i];
         }

         system("cls");

         boardinit(chessboard,gamer,eatenB,eatenW,q,w,undoboard,eatenb,eatenw);
         return;



   }else if(v=='R'){


           //Redoing the previous undone move.
                X--;

              for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                 chessboard[i][j]=undoboard[U][i][j];
                }
              }


              for(int i=0;i<16;i++){
               eatenB[i]=eatenb[U][i];
               eatenW[i]=eatenw[U][i];
              }


               system("cls");

               boardinit(chessboard,gamer,eatenB,eatenW,q,w,undoboard,eatenb,eatenw);
               return;


   }else if(v=='P'){


    //The player here will choose a move to play.

       X=0;

    printf("\n\nEnter the indices of your preferred move: ");

    int i1 , i2,j1,j2;
    char l1,l2;
    scanf(" %c%d %c%d",&l1,&i1,&l2,&i2);

    j1=l1-'a', j2=l2-'a';
    i1=8-i1, i2=8-i2;

    bool valid;


   //Calling the valid function to check if the move is valid or not.
   valid = movechoose(chessboard,i1,i2,j1,j2,valid,gamer);

    while(valid==false){

     printf("Invalid Move!!\n\nEnter a valid move!!:");

     scanf(" %c%d %c%d",&l1,&i1,&l2,&i2);
        j1=l1-'a', j2=l2-'a';
        i1=8-i1, i2=8-i2;
     valid = movechoose(chessboard,i1,i2,j1,j2,valid,gamer);

    }



     char c =chessb[i1][j1];

    if((i1%2==0 && j1%2==0)||(i1%2!=0 && j1%2!=0)){
        chessb[i1][j1]='.';
        chessb[i2][j2]=c;
    }else{
        chessb[i1][j1]='-';
        chessb[i2][j2]=c;
    }




   //Checking if that played move will make the king in check or not. If it will make it in check it will be invalid move and player has to enter another move.
   int movecheckvalid = movecheck(chessb,gamer);

    while(movecheckvalid==1 || valid==false){

      chessb[i1][j1]=chessboard[i1][j1];
      chessb[i2][j2]=chessboard[i2][j2];



     printf("Invalid Move!!\n\nEnter a valid move!!:");

     scanf(" %c%d %c%d",&l1,&i1,&l2,&i2);
        j1=l1-'a', j2=l2-'a';
        i1=8-i1, i2=8-i2;

    valid = movechoose(chessboard,i1,i2,j1,j2,valid,gamer);

    char c =chessb[i1][j1];

    if((i1%2==0 && j1%2==0)||(i1%2!=0 && j1%2!=0)){
        chessb[i1][j1]='.';
        chessb[i2][j2]=c;

    }else{
        chessb[i1][j1]='-';
        chessb[i2][j2]=c;
    }

     movecheckvalid = movecheck(chessb,gamer);

    }



    //Promotion state.
    if(i2==7 && chessboard[i1][j1]=='p' && gamer==false){

        char l;
        printf("\nWhat do you want to promote this pawn to? ");
        scanf(" %c",&l);

        l=tolower(l);


        //If the player entered any piece except q,b,r,n, it will be an invalid promotion.
        while(tolower(l)!='q' && tolower(l)!='b' && tolower(l)!='r' && tolower(l)!='n'){

            printf("\nInvalid Promotion! Select another valid one! ");

            scanf(" %c",&l);
            l=tolower(l);
        }


        chessboard[i1][j1]=l;



     }else if(i2==0 && chessboard[i1][j1]=='P' && gamer==true){

        char l;
        printf("\nWhat do you want to promote this pawn to? ");
        scanf(" %c",&l);

        l= toupper(l);


        //If the player entered any piece except q,b,r,n, it will be an invalid promotion.
        while(tolower(l)!='q' && tolower(l)!='b' && tolower(l)!='r' && tolower(l)!='n'){


            printf("\nInvalid Promotion! Select another valid one! ");

            scanf(" %c",&l);
            l=toupper(l);

        }

        chessboard[i1][j1]=l;

     }

     //Storing the eaten pieces.
     if(gamer==false && chessboard[i2][j2]!='-' && chessboard[i2][j2]!='.'){

        eatenB[q]=chessboard[i2][j2];
        q++;

     }else if(gamer==true && chessboard[i2][j2]!='-' && chessboard[i2][j2]!='.'){
         eatenW[w]=chessboard[i2][j2];
         w++;
     }


    char b =chessboard[i1][j1];

    //Making the move if it's valid one.
    if((i1%2==0 && j1%2==0)||(i1%2!=0 && j1%2!=0)){

        chessboard[i1][j1]='.';
        chessboard[i2][j2]=b;
    }else{
        chessboard[i1][j1]='-';
        chessboard[i2][j2]=b;
    }

    system("cls");


    boardinit(chessboard,gamer,eatenB,eatenW,q,w,undoboard,eatenb,eatenw);
   }


}






int main()
{
   system("color D");

 printf("                    _______           _______  _______  _______ \n");
 printf("                   (  ____ \\|\\     /|(  ____ \\(  ____ \\(  ____ \\ \n");
 printf("                   | (    \\/| )   ( || (    \\/| (    \\/| (    \\/ \n");
 printf("                   | |      | (___) || (__    | (_____ | (_____ \n");
 printf("                   | |      |  ___  ||  __)   (_____  )(_____  ) \n");
 printf("                   | |      | (   ) || (            ) |      ) | \n");
 printf("                   | (____/\\| )   ( || (____/\\/\\____) |/\\____) | \n");
 printf("                   (_______/|/     \\|(_______/\\_______)\\_______) \n");




    char undoboard[20000][8][8] , eatenb[20000][16]={}, eatenw[20000][16]={};
    char chessboard[8][8]={{'r','n','b','q','k','b','n','r'},{'p','p','p','p','p','p','p','p'},{'.','-','.','-','.','-','.','-'},
    {'-','.','-','.','-','.','-','.'},{'.','-','.','-','.','-','.','-'},{'-','.','-','.','-','.','-','.'},{'P','P','P','P','P','P','P','P'},{'R','N','B','Q','K','B','N','R'}};



  int q=0,w=0;
  char eatenB[16]={},eatenW[16]={},g;
  printf("\nWelcome To Our Chess Game!!\n\nFor a new game enter 'N', for loading a previous game enter 'L', and for exiting enter 'E' : ");
  bool gamer=false;
  scanf(" %c",&g);

   while(g!='N' && g!='L' && g!='E'){

     printf("\nEnter A Correct choice!!:");
     scanf(" %c",&g);
   }


   if(g=='L'){

   //Calling the load function to get the stored data from it.
   gamer = load(chessboard,eatenB,eatenW);
   while(eatenB[q]=='Q' || eatenB[q]=='B' || eatenB[q]=='N' || eatenB[q]=='R' || eatenB[q]=='P'){

    q++;

   }

   while(eatenW[w]=='q' || eatenW[w]=='b' || eatenW[w]=='n' || eatenW[w]=='r' || eatenW[w]=='p'){
    w++;

   }

   system("cls");
   system("color F");

   boardinit(chessboard,gamer,eatenB,eatenW,q,w,undoboard,eatenb,eatenw);

   }else if(g=='E'){

       //Exiting the game.
       return 0;

   }else if(g=='N'){

   //Starting a new game.
   system("cls");
   system("color F");

   boardinit(chessboard,gamer,eatenB,eatenW,q,w,undoboard,eatenb,eatenw);

   }

    return 0;

}
