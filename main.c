#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 8
#define COLUMNAS 8

char tablero[FILAS][COLUMNAS];

void inicializar_tablero() {
  int i,j;

  for(i=0;i<FILAS;i++)
    for(j=0;j<COLUMNAS;j++)
      tablero[i][j]=' ';
}

int jugada_correcta(int fila, int col) {//funcion con error
  int jugada_correcta; //Guarda un 1 ó un 0 para indicar si la jugada es correcta o no. 1-Jugada correcta. 0-Jugada errónea: La fila y/o columna no son válidas. Se sale del tablero la jugada.
  jugada_correcta=1;
  if (fila>=FILAS || fila<0 || col>=COLUMNAS || col<0) jugada_correcta=0;
  if (jugada_correcta==1) {
    if (tablero[fila][col]=='0' || tablero[fila][col]=='X') jugada_correcta=0;
  }

  if (jugada_correcta==1) {
    if (fila!=FILAS-1 && tablero[fila+1][col]==' ') jugada_correcta=0;
  }

  return jugada_correcta;
}

int hacer_jugada(int jug) {
srand(time(NULL));
  
  int fila,col; //Para guardar la fila y columna en la que se introduce la ficha.
  int i; //Para el contador.
  char ficha; //Para guardar la ficha del jugador actual. 0- Para humano, X- Para la máquina.
  int resultado_jugada;
  resultado_jugada=1;

  if (jug==0) {
    ficha='0';
    printf("El usuario coloca ficha.\n");
    do {
      if (resultado_jugada==0) printf("Jugada incorrecta.\n");
      printf("Introduce la columna en la que quieres colocar tu ficha: ");
      scanf("%d",&col);
        
      i=FILAS-1;
      if (tablero[FILAS-1][col]!=' ') {
        while(i<FILAS && (tablero[i][col]=='X' || tablero[i][col]=='0'))
          i--;
      }
      fila=i;
      resultado_jugada=jugada_correcta(fila,col);//operacion logica=1 error en funcion jugada_correcta
    } while(resultado_jugada==0);
  } else {
    ficha='X';
    do {
      col=rand() % COLUMNAS;
      i=FILAS-1;
      if (tablero[FILAS-1][col]!=' ') {
        while(i<FILAS && (tablero[i][col]=='X' || tablero[i][col]=='0'))
          i--;
      }
      fila=i;
      resultado_jugada=jugada_correcta(fila,col);
    } while(resultado_jugada==0);
  }

  if (resultado_jugada==1) tablero[fila][col]=ficha;
  return resultado_jugada;
}


void mostrar_tablero() {
  int i,j;
  int ficha;

  system("clear");
  printf("\n");
  for(j=0;j<COLUMNAS*5/2;j++) printf(" ");

  printf("CONECTA 4");
  printf("\n F -");
  for(j=0;j<COLUMNAS+1;j++) printf("----");
  printf("\n");

  for(i=0;i<FILAS;i++) {
    printf(" ");
    if (i==0)
      printf("I");
    else if (i==1)
      printf("A");
    else
      printf(" ");
     
    printf(" %d |",i);
   
    for(j=0;j<COLUMNAS;j++) {
      printf(" ");
      printf("%c",tablero[i][j]);
      printf(" |");
    }
    printf(" ");
    if (i==0) printf("\n L");
    else if (i==1) printf("\n S");
    else printf("\n  ");
   
    printf(" -");
    for(j=0;j<COLUMNAS+1;j++) printf("----");
    printf("\n");
  }
  printf("       ");
  for(j=0;j<COLUMNAS;j++) printf("%d   ",j);
  printf(" COLUMNAS\n");
  printf("\n");
}

int comprobar_fin() {
  int i,j; //Para el for, para recorrer el tablero
  int ganador; // -1: no gana nadie, 1: gana humano, 0: gana máquina
  ganador=-1;

  //Comprobar si hay cuatro en línea en horizontal
  for(i=0;i<FILAS;i++) {
    for(j=0;j<COLUMNAS-3;j++) {
      if (tablero[i][j]=='X' && tablero[i][j+1]=='X' && tablero[i][j+2]=='X' && tablero[i][j+3]=='X')
        ganador=0;
      else if (tablero[i][j]=='0' && tablero[i][j+1]=='0' && tablero[i][j+2]=='0' && tablero[i][j+3]=='0')
        ganador=1;
    }
  }
  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en vertical
    for(i=0;i<FILAS-3;i++) {
      for(j=0;j<COLUMNAS;j++) {
        if (tablero[i][j]=='X' && tablero[i+1][j]=='X' && tablero[i+2][j]=='X' && tablero[i+3][j]=='X')
          ganador=0;
        else if (tablero[i][j]=='0' && tablero[i+1][j]=='0' && tablero[i+2][j]=='0' && tablero[i+3][j]=='0')
          ganador=1;
      }
    }
  }

  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en diagonal 1
    for(i=0;i<FILAS;i++) {
      for(j=0;j<COLUMNAS;j++) {
        if (i+3<FILAS && j+3<COLUMNAS) {
          if (tablero[i][j]=='X' && tablero[i+1][j+1]=='X' && tablero[i+2][j+2]=='X' && tablero[i+3][j+3]=='X')
            ganador=0;
          else if (tablero[i][j]=='0' && tablero[i+1][j+1]=='0' && tablero[i+2][j+2]=='0' && tablero[i+3][j+3]=='0')
            ganador=1;
        }
      }
    }
  }

  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en diagonal 2
    for(i=0;i<FILAS;i++) {
      for(j=0;j<COLUMNAS;j++) {
        if (i+3<FILAS && j-3>=0) {
          if (tablero[i][j]=='X' && tablero[i+1][j-1]=='X' && tablero[i+2][j-2]=='X' && tablero[i+3][j-3]=='X')
            ganador=0;
          else if (tablero[i][j]=='0' && tablero[i+1][j-1]=='0' && tablero[i+2][j-2]=='0' && tablero[i+3][j-3]=='0')
            ganador=1;
        }
      }
    }
  }
  return ganador;
}

int main (int argc,char **argv) {
  int jugador; //Indica el jugador al que le toca jugar. 0-Juega humano 1-Juega máquina
  int total_jugadas; //Indica el total de jugadas que se están haciendo. En las jugadas pares juega el humano, en las impares la máquina.
  total_jugadas=0;

  inicializar_tablero();

  do {
    if (total_jugadas % 2 == 0)
      jugador=0;
    else
      jugador=1;
   
    total_jugadas++;
    mostrar_tablero();
   
    if (hacer_jugada(jugador)==0) {
      printf("Jugada incorrecta.\n\n");
      system("pause");
    }
  } while(comprobar_fin()==-1);

  mostrar_tablero();
  if (comprobar_fin()==1)
    printf("Enhorabuena!! Has ganado!!\n\n");
  else
  printf("El ordenador ha ganado la partida!!\n\n");
  getchar();
}
