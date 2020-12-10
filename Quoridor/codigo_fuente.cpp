// Quoridor
// By Milton Yair Lenis Mesias && Nicolas Hoyos Pedraza

// Librerias Incluidas
#include <iostream>
#include <cstdlib>
#include <conio.h>

// Constantes
#define alto 19  // Filas de la matriz.
#define ancho 19 // Columnas de la matriz.
#define bV '1'   // Bloque Vertical.
#define bH '2'   // Bloque Horizontal.

// Teclas direccionales.
const char UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;

// Teclas de salto diagonal.
const char L  = '1'; // Saltar diagonalmente a la izquierda del oponente.
const char R  = '3'; // Saltar diagonalmente a la derecha del oponente.

// Teclas de manipulación de bloques.
const char Blo = 'p'; // Activa los bloques.
const char Gir = 'o'; // Hace girar a un bloque.
const char Ent = 'l'; // Ancla un bloque.

// Caracteres
const char P1 = '\2';   // Player 1.
const char P2 = '\1';   // Pkayer 2.
const char b0 = '\0';   // Bloque Invisible.
const char bC = '\333'; // Bloque Caracter .
const char bS = '\260'; // Bloque Superpuesto.

// Variables globales
char Blok = '\0';   // Guarda el tipo de colindancia que hay con otro bloque.
char tecla = '\0';  // Guarda el caracter de la tecla que presionemos.
char SaltoD = '\0'; // Guarda el tipo de salto diagonal que puede hacer un jugador.
bool Salida = true; // True si los jugadores tienen al menos un camino para ganar.

//                                   (1)           (2)           (3)           (4)          (5)           (6)           (7)           (8)           (9)
// Matriz.                    0.     1.     2.     3.     4.     5.     6.     7.     8.    9.     10.    11.    12.    13.    14.    15.    16.    17.    18.
char matriz[alto][ancho] = {{'\332','\304','\302','\304','\302','\304','\302','\304','\302','\304','\302','\304','\302','\304','\302','\304','\302','\304','\277'},
/*              (1)  1.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                   2.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (2)  3.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                   4.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (3)  5.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                   6.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (4)  7.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                   8.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (5)  9.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                  10.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (6) 11.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                  12.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (7) 13.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                  14.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (8) 15.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                  16.*/   {'\303','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\305','\304','\264'},
/*              (9) 17.*/   {'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263','\0'  ,'\263'},
/*                  18.*/   {'\300','\304','\301','\304','\301','\304','\301','\304','\301','\304','\301','\304','\301','\304','\301','\304','\301','\304','\331'}};

// Posición de los jugadores.
struct Jugador
{
   char cod; // Caracter que representa al jugador.
   int posX; // Posición horinzontal.
   int posY; // Posición vertical.
   int Bloq; // Número de bloques a su disposición.
}
//            Cod   PosX  PosY   Bloq
Jugador_1 = {  P1  ,  9  ,  17  ,  10  }, // Pos incial del jugador de arriba.
Jugador_2 = {  P2  ,  9  ,  1   ,  10  }; // Pos inicial del jugador de abajo.

// Posición de cada bloque.
struct Bloquear
{
   char Orientacion;
   int posX1; // Posiciones
   int posX2; // Horizontales
   int posX3; //
   int posY1; // Posiciones
   int posY2; // Verticales
   int posY3; //
}
//        Orientacion   posX1   posX2   posX3   posY1   posY2   posY3
Bloque = {     b0     ,   0   ,   0   ,   0   ,   9   ,   0   ,   0  };

// Prototipos de Función
void Posicionar_jugadores();
void Posicionar_bloques();
void Orientar_bloques();
void Cambiar_Orientacion();
void Dibujar_matriz(int turno);
void Mostrar_el_turno(int turno);
void Limpiar_posiciones();
void Limpiar_bloques();
void Siguiente_turno(int& i);
void Leer_teclado(Jugador& Player, char& UNA_TECLA);
void Avance_Recto(Jugador& Player, Jugador& Oponente, int& Pos_Player, char Dir, int Borde, int& i);
void Avance_Diagonal(Jugador& Player, Jugador& Oponente, int& i);
void Mover_Jugadores(Jugador& Player, Jugador& Oponente, int& i);
void Mover_bloque(Jugador& Player, Jugador& Oponente, int& i);
void Pantalla_del_ganador();
void Aparecer_bloque();
void Reiniciar_bloque();
void Caracter_bloque(char& a, char& b, char& c);
void Blo_Colindante(char Key);
void Borrar_remanente();
void Hallar_salida();
char Tipo_De_BloColindante(char Key);
char Determinar_diagonal(Jugador& Player, Jugador& Oponente);
bool Ju_Colindante(Jugador& Player, Jugador& Oponente, char Dir);
bool Bloque_Superpuesto();
bool Sin_ganadores();
bool hay_salida(char matrizAUX[alto][ancho], int posX, int posY, int posXaux, int posYaux, int meta, char jugador);

using namespace std;

int main()
{
   for(int i=0; Sin_ganadores(); i++){ // El ciclo continua mientras no hayan ganadores.

      Posicionar_jugadores(); // Inserta las fichas de los jugadores en la matriz.
      system("cls");          // Limpia la pantalla.
      Dibujar_matriz(i);      // Dibuja la nueva matriz.
      Limpiar_posiciones();   // Las fichas de los jugadores desaparecen de la matriz.
      Siguiente_turno(i);     // Cambia las posiciones de las fichas con el teclado según el turno.
      Posicionar_bloques();   // Inserta los bloques en la matriz.
      Hallar_salida();        // Determinar si los jugadores tienen al menos un camino para ganar.
   }
   Pantalla_del_ganador(); // Muestra un mensaje señalando al ganador de la partida.
   return 0;
}

// Agrega los caracteres que representan a cada jugador en la matriz.
void Posicionar_jugadores()
{
   matriz[Jugador_1.posY][Jugador_1.posX] = P1;
   matriz[Jugador_2.posY][Jugador_2.posX] = P2;
}

// Agrega los caracteres que representan a cada jugador en la matriz.
void Posicionar_bloques()
{
   char _1, _2, _3;
   Orientar_bloques();
   Caracter_bloque(_1,_2,_3);
   matriz[Bloque.posY1][Bloque.posX1] = _1;
   matriz[Bloque.posY2][Bloque.posX2] = _2;
   matriz[Bloque.posY3][Bloque.posX3] = _3;
}

// Agrega espacios vacios en las posiciones de los jugadores.
void Limpiar_posiciones()
{
   matriz[Jugador_1.posY][Jugador_1.posX] = '\0';
   matriz[Jugador_2.posY][Jugador_2.posX] = '\0';
}

// Hace aparecer un bloque de la nada.
void Aparecer_bloque()
{
   SaltoD = '\0'; // Inhabilita el Salto diagonal desde que aparece el bloque.
   Bloque.Orientacion = bV;
   Blo_Colindante('d');
   Bloque.posX1 = 3;
   Bloque.posY1 = 8;
}

// Hace que Blok sea igual al tipo de remanete que Limpiar_bloques() debe borrar.
void Borrar_remanente()
{
   Bloque.posX1+=2;
   Orientar_bloques();
   Blo_Colindante('a');
   Bloque.posX1-=2;
}

// Desaparece el bloque que aún no ha sido anclado en el tablero.
void Reiniciar_bloque()
{
   Bloque.Orientacion = b0;
   Bloque.posX1 = 1;
   Bloque.posY1 = 8;
}

// Sirve para girar un bloque según su orientación.
void Orientar_bloques()
{
   if(Bloque.Orientacion == bV || Bloque.Orientacion == b0) // Si la orientacion es vertical.
   {
      if(Bloque.posY1 % 2 == 0) // Si es impar...
      {
         Bloque.posX1--;
         Bloque.posY1--;
      }
      Bloque.posX2 = Bloque.posX1;
      Bloque.posX3 = Bloque.posX1;
      Bloque.posY2 = Bloque.posY1+1;
      Bloque.posY3 = Bloque.posY1+2;
   }
   else // Bloque.Orientacion == bH
   {
      if(Bloque.posY1 % 2 != 0) // Si es par...
      {
         Bloque.posX1++;
         Bloque.posY1++;
      }
      Bloque.posX2 = Bloque.posX1+1;
      Bloque.posX3 = Bloque.posX1+2;
      Bloque.posY2 = Bloque.posY1;
      Bloque.posY3 = Bloque.posY1;
   }
}

// Borra la remanente del bloque que estamos manipulando.
void Limpiar_bloques()
{
   char pared;
   if(Bloque.Orientacion == bV)
   {
      pared = '\263'; // Solo pinta paredes verticales.
   }
   else // Bloque.Orientacion == bH
   {
      pared = '\304'; // Solo pinta paredes horizontales.
   }
   switch(Blok) // Según el tipo de colindancia.
   {
      case '1' : matriz[Bloque.posY1][Bloque.posX1] = pared;
                 matriz[Bloque.posY2][Bloque.posX2] = '\305';
                 matriz[Bloque.posY3][Bloque.posX3] = bC;
                 break;
      case '2' : matriz[Bloque.posY1][Bloque.posX1] = bC;
                 matriz[Bloque.posY2][Bloque.posX2] = bC;
                 matriz[Bloque.posY3][Bloque.posX3] = bC;
                 break;
      case '3' : matriz[Bloque.posY1][Bloque.posX1] = bC;
                 matriz[Bloque.posY2][Bloque.posX2] = '\305';
                 matriz[Bloque.posY3][Bloque.posX3] = pared;
                 break;
      case '4' : matriz[Bloque.posY1][Bloque.posX1] = pared;
                 matriz[Bloque.posY2][Bloque.posX2] = bC;
                 matriz[Bloque.posY3][Bloque.posX3] = pared;
                 break;
      case '5' : matriz[Bloque.posY1][Bloque.posX1] = bC;
                 matriz[Bloque.posY2][Bloque.posX2] = bC;
                 matriz[Bloque.posY3][Bloque.posX3] = pared;
                 break;
      case '6' : matriz[Bloque.posY1][Bloque.posX1] = pared;
                 matriz[Bloque.posY2][Bloque.posX2] = bC;
                 matriz[Bloque.posY3][Bloque.posX3] = bC;
                 break;
      case '7' : matriz[Bloque.posY1][Bloque.posX1] = bC;
                 matriz[Bloque.posY2][Bloque.posX2] = '\305';
                 matriz[Bloque.posY3][Bloque.posX3] = bC;
                 break;
      default  : matriz[Bloque.posY1][Bloque.posX1] = pared;
                 matriz[Bloque.posY2][Bloque.posX2] = '\305';
                 matriz[Bloque.posY3][Bloque.posX3] = pared;
                 break;
   }
}

// Elije el caracter del que están hechos los bloques.
void Caracter_bloque(char& a, char& b, char& c)
{
   if(Bloque.Orientacion == bV || Bloque.Orientacion == bH)
   {
      switch(Blok) // Dibuja el bloque según su tipo de superposicion.
      {
         case '1' : a = bC; // No Superpuesto.
                    b = bC; // No Superpuesto.
                    c = bS; // Superpuesto.
                    break;
         case '2' : a = bS; // Superpuesto.
                    b = bS; // Superpuesto.
                    c = bS; // Superpuesto.
                    break;
         case '3' : a = bS; // Superpuesto.
                    b = bC; // No Superpuesto.
                    c = bC; // No Superpuesto.
                    break;
         case '4' : a = bC; // No Superpuesto.
                    b = bS; // Superpuesto.
                    c = bC; // No Superpuesto.
                    break;
         case '5' : a = bS; // Superpuesto.
                    b = bS; // Superpuesto.
                    c = bC; // No Superpuesto.
                    break;
         case '6' : a = bC; // No Superpuesto.
                    b = bS; // Superpuesto.
                    c = bS; // Superpuesto.
                    break;
         case '7' : a = bS; // Superpuesto.
                    b = bC; // No Superpuesto.
                    c = bS; // Superpuesto.
                    break;
         default  : a = bC; // No Superpuesto.
                    b = bC; // No Superpuesto.
                    c = bC; // No Superpuesto.
                    break;
      }
   }
   else // El bloque queda escondido en una esquina del tablero.
   {
      a = '\263'; // Pared vertical.
      b = '\303'; // Pared en cruz.
      c = '\263'; // Pared vertical.
   }
}

// Muestra la matriz en la consola.
void Dibujar_matriz(int turno)
{
   cout << "/(" << Jugador_2.Bloq << ")\n" ;
   for(int i=0; i<alto; i++) // i = posición y.
   {
      for(int j=0; j<ancho; j++) // j = posición x.
      {
         cout << matriz[i][j] ;
      }
      cout << '\n' ; // Imprime la siguiente fila un renglón abajo.
   }
   cout << "\t      /(" << Jugador_1.Bloq << ")\n" ;
   Mostrar_el_turno(turno); // El mensaje debajo de la matriz con el turno.
}

// Muestra a quién le sigue el turno y las teclas que debe usar debajo del tablero.
void Mostrar_el_turno(int turno)
{
   cout << "\n\nTurno de: ";
   if(turno % 2 == 0) // Si i es par...
   {
      cout << P1 << "\tTeclas: ";
      if(SaltoD == '\0') // Si el salto diagonal NO está habilitado...
      {
         cout <<"  w\n\t\t\ta s d\n";
      }
      else
      {
         switch(SaltoD) // Según el tipo de salto diagonal que puede hacer un jugador P1.
         {
            case 'A' : cout <<L<<" w "<<R<<"\n\t\t\ta s d\n";            break;
            case 'B' : cout <<"  w\n\t\t\ta s d\n\t\t\t"<<L<<"   "<<R<<"\n"; break;
            case 'C' : cout <<L<<" w\n\t\t\ta s d\n\t\t\t"<<R<<"\n";     break;
            case 'D' : cout <<"  w 1\n\t\t\ta s d\n\t\t\t    "<<R<<"\n";     break;
            case 'E' : cout <<"  w "<<R<<"\n\t\t\ta s d\n"; break;
            case 'F' : cout <<L<<" w\n\t\t\ta s d\n";   break;
            case 'G' : cout <<"  w\n\t\t\ta s d\n\t\t\t"<<L<<"\n"; break;
            case 'H' : cout <<"  w\n\t\t\ta s d\n\t\t\t    "<<R<<"\n"; break;
            case 'I' : cout <<L<<" w  \n\t\t\ta s d\n"; break;
            case 'J' : cout <<"  w "<<R<<"\n\t\t\ta s d\n";   break;
         }
      }
   }
   else
   {
      cout << P2 << "\tTeclas:  ";
      if(SaltoD == '\0') // Si el salto diagonal NO está habilitado...
      {
      cout <<"  \30\n\t\t\t<- \31 ->\n";
      }
      else
      {
         switch(SaltoD) // Según el tipo de salto diagonal que puede hacer un jugador P2.
         {
            case 'A' : cout <<L<<" \30 "<<R<<"\n\t\t\t<- \31 ->\n";               break;
            case 'B' : cout <<"  \30\n\t\t\t<- \31 ->\n\t\t\t "<<L<<"   "<<R<<"\n";   break;
            case 'C' : cout <<L<<" \30\n\t\t\t<- \31 ->\n\t\t\t "<<R<<"\n";       break;
            case 'D' : cout <<"  \30 "<<L<<"\n\t\t\t<- \31 ->\n\t\t\t     "<<R<<"\n"; break;
            case 'E' : cout <<"  \30 "<<R<<"\n\t\t\t<- \31 ->\n"; break;
            case 'F' : cout <<L<<" \30\n\t\t\t<- \31 ->\n";   break;
            case 'G' : cout <<"  \30\n\t\t\t<- \31 ->\n\t\t\t "<<L<<"    \n"; break;
            case 'H' : cout <<"  \30\n\t\t\t<- \31 ->\n\t\t\t     "<<R<<"\n"; break;
            case 'I' : cout <<L<<" \30  \n\t\t\t<- \31 ->\n";  break;
            case 'J' : cout <<"  \30 "<<R<<"\n\t\t\t<- \31 ->\n";  break;
         }
      }
   }
   if(tecla != Blo) // Si no se ha presionado la tecla que activa los bloques...
   {
      cout << "\nPresione " << Blo << " para mover un bloque.\n";
   }
   else
   {
      if(Blok == '\0')
      {
         if(Salida)
         {
            cout << "\nPresione " << Gir << " para girar el bloque."
                    "\nPresione " << Ent << " para anclar el bloque."
                    "\nPresione " << Blo << " para mover su ficha.\n";
         }
         else
         {
            cout << "\nPresione " << Gir << " para girar el bloque."
                    "\nPresione " << Blo << " para mover su ficha.\n";
         }
      }
      else
      {
         cout << "\nPresione " << Gir << " para girar el bloque."
                 "\nPresione " << Blo << " para mover su ficha.\n";
      }
   }
}

// El turno de los jugadores cambia basandose en si i es par.
void Siguiente_turno(int& i)
{
   if(i % 2 == 0) // Si i es par...
   {
      return Mover_Jugadores(Jugador_1, Jugador_2, i);
   }
   else
   {
      return Mover_Jugadores(Jugador_2, Jugador_1, i);
   }
}

// Cambia los valores de las posiciones de los jugadores con el teclado
void Mover_Jugadores(Jugador& Player, Jugador& Oponente, int& i)
{
   if(tecla == Blo)
   {
      return Mover_bloque(Player, Oponente, i);
   }
   else
   {
      Leer_teclado(Player, tecla); // Lee lo que ingresaremos por el teclado.
      switch(tecla)
      {  //                                      Eje que cambia        Pared
         case 'w' : Avance_Recto(Player, Oponente, Player.posY , UP    , -1 , i) ; break; // Arriba

         case 's' : Avance_Recto(Player, Oponente, Player.posY , DOWN  , 19 , i) ; break; // Abajo

         case 'a' : Avance_Recto(Player, Oponente, Player.posX , LEFT  , -1 , i) ; break; // Izquierda

         case 'd' : Avance_Recto(Player, Oponente, Player.posX , RIGHT , 19 , i) ; break; // Derecha

         case Blo : if(Player.Bloq > 0)
                    {
                       i--;
                       return Aparecer_bloque();
                    }
                    else
                    {
                       tecla = '\0';
                       return Mover_Jugadores(Player, Oponente, i);
                    }

         case  L  : if(SaltoD != '\0') // SI el salto diagonal NO está desabilitado...
                    {
                       Avance_Diagonal(Player, Oponente, i); // Avance diagonal a la izquierda.
                    }
                    else
                    {
                       return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
                    }
                    break;

         case  R  : if(SaltoD != '\0') // SI el salto diagonal NO está desabilitado...
                    {
                       Avance_Diagonal(Player, Oponente, i); // Avance diagonal a la derecha.
                    }
                    else
                    {
                       return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
                    }
                    break;

         default  : return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
      }
      SaltoD = Determinar_diagonal(Player,Oponente); // Determinar el tipo de anvace diagonal que puede hacer el siguiente
                                                   // jugador o desabilitarle la posibilidad de hacerlo.
   }
}

// Permite que los jugadores jueguen con diferentes comandos.
void Leer_teclado(Jugador& Player, char& UNA_TECLA)
{
   UNA_TECLA = getch(); // Primer lectura.

   if(UNA_TECLA == 'à') // Si detecta una tecla especial hace una segunda lectura.
   {
      UNA_TECLA = getch();
   }
   if(Player.cod == Jugador_2.cod)
   {
      switch(UNA_TECLA) // Reemplaza el caracter especial por uno de los que el programa puede leer.
      {
         case UP    : UNA_TECLA = 'w'; break;
         case DOWN  : UNA_TECLA = 's'; break;
         case LEFT  : UNA_TECLA = 'a'; break;
         case RIGHT : UNA_TECLA = 'd'; break;
         case L     : break; // Aquí
         case R     : break; // no
         case Blo   : break; // reemplaza
         case Gir   : break; // ninguno.
         case Ent   : break; //
         default    : UNA_TECLA = '\0';
      }
   }
}

// Cambia la orientacion de un bloque.
void Cambiar_Orientacion()
{
   if(Bloque.Orientacion == bV)
   {
      Bloque.Orientacion = bH;
   }
   else // Bloque.Orientacion == bH
   {
      Bloque.Orientacion = bV;
   }
}

// Desplaza un bloque o lo gira de acuedo a las teclas que se presionen.
void Mover_bloque(Jugador& Player, Jugador& Oponente, int& i)
{
   char Key;
   Leer_teclado(Player, Key);

   if(Key == Blo) // Si presionó Blo de nuevo para desactivar los bloques sin perder turno...
   {
      Limpiar_bloques();
      Reiniciar_bloque();
      tecla = '\0'; // La condición if(tecla == Blo) en Mover_Jugadores dejará de cumplirse.
      i--; // El turno no se pierde.
      SaltoD = Determinar_diagonal(Oponente,Player); // Si el actual jugador estaba en una posición que
                                                     // le permitía hacer un salto diagonal, aún podrá hacerlo.
   }
   else
   {
      if(Key == Ent)
      {
         if(!Bloque_Superpuesto()) // Mientras el bloque no esté superpuesto...
         {
            if(Salida) // Si el bloque no encierra al jugador...
            {
               Player.Bloq--;
               tecla = '\0'; // La condición if(tecla == Blo) en Mover_Jugadores dejará de cumplirse.
               Reiniciar_bloque();
               SaltoD = Determinar_diagonal(Player,Oponente); // Si el otro jugador estaba en una posición que
            }                                                 // le permitía hacer un salto diagonal, aún podrá hacerlo.
            else
            {
               return Mover_bloque(Player, Oponente, i);
            }
         }
         else
         {
            return Mover_bloque(Player, Oponente, i);
         }
      }
      else
      {
         {
            // Se borran los bloques de la matriz.
            if(Key == Gir) //  Si Key es igual a la tecla que gira el bloque...
            {
               if((Bloque.Orientacion == bV && Bloque.posX1 == 16) // Si es un bloque vertival en la columna 17
                  ||
                  (Bloque.Orientacion == bH && Bloque.posX1 == 1)) // o horizontal en la columna 2...
               {
                  return Mover_bloque(Player, Oponente, i);      // No puede girar el bloque.
               }
               else // De lo contrario sí puede girarlo.
               {
                  Limpiar_bloques();
                  Cambiar_Orientacion();
                  Borrar_remanente();
               }
            }
            else
            {
               Limpiar_bloques();
               switch(Key) // Desplazar bloque.
               {
                  case 'w' : if(Bloque.posY1 - 2 < 1) // Si presionar w generaría que el bloque se salga de la matriz...
                             {
                                return Mover_bloque(Player, Oponente, i); // El movimiento debería ser invalido y presionar de nuevo.
                             }
                             else // Si no es así la posición del bloque debería cambiar.
                             {
                                Blo_Colindante(Key);
                                Bloque.posY1 -= 2; break;
                             }
                  case 's' : if(Bloque.posY1 + 2 > 16)
                             {
                                return Mover_bloque(Player, Oponente, i);
                             }
                             else
                             {
                                Blo_Colindante(Key);
                                Bloque.posY1 += 2; break;
                             }
                  case 'a' : if(Bloque.posX1 - 2 < 1)
                             {
                                return Mover_bloque(Player, Oponente, i);
                             }
                             else
                             {
                                Blo_Colindante(Key);
                                Bloque.posX1 -= 2; break;
                             }
                  case 'd' : if(Bloque.posX1 + 2 > 16)
                             {
                                return Mover_bloque(Player, Oponente, i);
                             }
                             else
                             {
                                Blo_Colindante(Key);
                                Bloque.posX1 += 2; break;
                             }
                  default  : return Mover_bloque(Player, Oponente, i);
               }
            }
            i--; // El jugador no perderá el turno cuando la matriz se vuelva a pintar.
         }
      }
   }
}

// Retorna el tipo de bloque colindante a otro bloque.
char Tipo_De_BloColindante(char Key)
{
   int _1, _2, _3, _4, _5, _6, pared;
   if(Bloque.Orientacion == bV)
   {
      pared = '\263';
   }
   else // Bloque.Orientacion == bH
   {
      pared = '\304';
   }
   if(Key == 'w' || Key == 's')
   {
      if(Key == 'w')
      {
         _1 = Bloque.posY1-2;
         _2 = Bloque.posY2-2;
         _3 = Bloque.posY3-2;
         _4 = Bloque.posX1;
         _5 = Bloque.posX2;
         _6 = Bloque.posX3;
      }
      else // Key == s
      {
         _1 = Bloque.posY1+2;
         _2 = Bloque.posY2+2;
         _3 = Bloque.posY3+2;
         _4 = Bloque.posX1;
         _5 = Bloque.posX2;
         _6 = Bloque.posX3;
      }
   }
   else // key == 'a' || key == 'd'
   {
      if(Key == 'a')
      {
         _1 = Bloque.posY1;
         _2 = Bloque.posY2;
         _3 = Bloque.posY3;
         _4 = Bloque.posX1-2;
         _5 = Bloque.posX2-2;
         _6 = Bloque.posX3-2;
      }
      else // Key == d
      {
         _1 = Bloque.posY1;
         _2 = Bloque.posY2;
         _3 = Bloque.posY3;
         _4 = Bloque.posX1+2;
         _5 = Bloque.posX2+2;
         _6 = Bloque.posX3+2;
      }
   }
   if(matriz[_1][_4] == pared
      &&
      matriz[_2][_5] == '\305'
      &&
      matriz[_3][_6] == bC)
   {
      return '1'; // borrar, borrar, bloque
   }
   else
   {
      if(matriz[_1][_4] == bC
         &&
         matriz[_2][_5] == bC
         &&
         matriz[_3][_6] == bC)
      {
         return '2'; // no borrar nada
      }
      else
      {
         if(matriz[_1][_4] == bC
            &&
            matriz[_2][_5] == '\305'
            &&
            matriz[_3][_6] == pared)
         {
            return '3'; // bloque, borrar, borrar
         }
         else
         {
            if(matriz[_1][_4] == pared
               &&
               matriz[_2][_5] == bC
               &&
               matriz[_3][_6] == pared)
            {
               return '4'; // borrar, bloque, borrar
            }
            else // bV , '\305' , bV
            {
               if(matriz[_1][_4] == bC
                  &&
                  matriz[_2][_5] == bC
                  &&
                  matriz[_3][_6] == pared)
               {
                  return '5'; // bloque, bloque, borrar
               }
               else
               {
                  if(matriz[_1][_4] == pared
                     &&
                     matriz[_2][_5] == bC
                     &&
                     matriz[_3][_6] == bC)
                  {
                     return '6'; // blorrar, bloque, bloque
                  }
                  else // pared, pared, pared.
                  {
                     if(matriz[_1][_4] == bC
                        &&
                        matriz[_2][_5] == '\305'
                        &&
                        matriz[_3][_6] == bC)
                     {
                        return '7'; // bloque, borrar, bloque
                     }
                     else
                     {
                        return '\0'; // Borrar todo el bloque
                     }
                  }
               }
            }
         }
      }
   }
}

// Asigna a Blok el tipo de bloque colindante a otro bloque.
void Blo_Colindante(char Key)
{
   switch(Key)
   {  // Player y Oponente se sobreponen si...
      case 'w'  : Blok = Tipo_De_BloColindante(Key);
                  break;

      case 's'  : Blok = Tipo_De_BloColindante(Key);
                  break;

      case 'a'  : Blok = Tipo_De_BloColindante(Key);
                  break;

      case 'd'  : Blok = Tipo_De_BloColindante(Key);
                  break;
   }
}

// Mueve al jugador según su cercanía a una pared o a otro jugador.
void Avance_Recto(Jugador& Player, Jugador& Oponente, int& Pos_Player, char Dir, int Borde, int& i)
{
   // Esta parte ayuda a hacer el código polimorfico.
   int Un_Paso, Dos_Pasos;
   char bloque, PasoBl;
   if(Dir == DOWN || Dir == RIGHT)
   {
      Un_Paso   = Pos_Player + 2;
      Dos_Pasos = Pos_Player + 4;
      if(Dir == DOWN)
      {
         bloque = matriz[Player.posY + 1][Player.posX];
         PasoBl = matriz[Player.posY + 3][Player.posX];
      }
      else // RIGHT
      {
         bloque = matriz[Player.posY][Player.posX + 1];
         PasoBl = matriz[Player.posY][Player.posX + 3];
      }
   }
   else
   {
      Un_Paso   = Pos_Player - 2;
      Dos_Pasos = Pos_Player - 4;
      if(Dir == UP)
      {
         bloque = matriz[Player.posY - 1][Player.posX];
         PasoBl = matriz[Player.posY - 3][Player.posX];
      }
      else // RIGHT
      {
         bloque = matriz[Player.posY][Player.posX - 1];
         PasoBl = matriz[Player.posY][Player.posX - 3];
      }
   }

   if(bloque != bC) // Si delante no haya un bloque...
   {
      if(Un_Paso != Borde) // Si no hay ninguna pared en frente...
      {
         if(Ju_Colindante(Player, Oponente, Dir)) // Si hay jugadores juntos...
         {
            if(Dos_Pasos == Borde) // ¿Al frente del jugador colindante hay una pared?
            {
               return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
            }
            else
            {
               if(PasoBl != bC) // Si delante del oponente no hay un bloque...
               {
                  Pos_Player = Dos_Pasos; // Dar un salto de dos pasos.
               }
               else
               {
                  return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
               }
            }
         }
         else
         {
            Pos_Player = Un_Paso; // Dar un salto de un paso.
         }
      }
      else
      {
         return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
      }
   }
   else
   {
      return Mover_Jugadores(Player, Oponente, i); // Tecla invalida, presione otra.
   }

}

// Mueve al jugador según el tipo de avance diagonal que puede hacer.
void Avance_Diagonal(Jugador& Player, Jugador& Oponente, int& i)
{
   if(SaltoD == 'A' || SaltoD == 'B') // Salto diagonal a la izquierda y derecha del oponente.
   {
      if(tecla == L) // Ir al lado izquierdo del oponente.
      {
         Player.posX = Oponente.posX - 2;
         Player.posY = Oponente.posY;
      }
      else // (tecla == R) Ir al lado derecho del oponente.
      {
         Player.posX = Oponente.posX + 2;
         Player.posY = Oponente.posY;
      }
   }
   else
   {
      if(SaltoD == 'C' || SaltoD == 'D') // Salto diagonal hacia arriba y abajo del oponente.
      {
         if(tecla == L) // Ir al lado izquierdo del oponente.
         {
            Player.posX = Oponente.posX;
            Player.posY = Oponente.posY - 2;
         }
         else // (tecla == R) Ir al lado derecho del oponente.
         {
            Player.posX = Oponente.posX;
            Player.posY = Oponente.posY + 2;
         }
      }
      else
      {
         switch(SaltoD)
         {
            case'E': if(tecla == R) // Salto diagonal a la derecha del oponente.
                     {
                        Player.posX = Oponente.posX + 2;
                        Player.posY = Oponente.posY; break;
                     }
                     else // (tecla == L)
                     {
                        return Mover_Jugadores(Player, Oponente, i); // Volver a intentarlo.
                     }
            case'F': if(tecla == L) // Salto diagonal a la izquierda del oponente.
                     {
                        Player.posX = Oponente.posX - 2;
                        Player.posY = Oponente.posY; break;
                     }
                     else // (tecla == R)
                     {
                        return Mover_Jugadores(Player, Oponente, i); // Volver a intentarlo.
                     }
            case'G': if(tecla == L) // Salto diagonal hacía abajo del oponente
                     {
                        Player.posX = Oponente.posX;
                        Player.posY = Oponente.posY + 2; break;
                     }
                     else // (tecla == R)
                     {
                        return Mover_Jugadores(Player, Oponente, i); // Volver a intentarlo.
                     }
            case'H': if(tecla == R) // Salto diagonal hacia abajo del oponente
                     {
                        Player.posX = Oponente.posX;
                        Player.posY = Oponente.posY + 2; break;
                     }
                     else // (tecla == L)
                     {
                        return Mover_Jugadores(Player, Oponente, i); // Volver a intentarlo.
                     }
            case'I': if(tecla == L) // Salto diagonal hacia arriba del oponente
                     {
                        Player.posX = Oponente.posX;
                        Player.posY = Oponente.posY - 2; break;
                     }
                     else // (tecla == R)
                     {
                        return Mover_Jugadores(Player, Oponente, i); // Volver a intentarlo.
                     }
            case'J': if(tecla == R) // Salto diagonal hacia arriba del oponente
                     {
                        Player.posX = Oponente.posX;
                        Player.posY = Oponente.posY - 2; break;
                     }
                     else // (tecla == L)
                     {
                        return Mover_Jugadores(Player, Oponente, i); // Volver a intentarlo.
                     }
         }
      }
   }
}

// Determina el tipo de anvace diagonal que puede hacer el siguiente jugador.
char Determinar_diagonal(Jugador& Player, Jugador& Oponente)
{
   if(Player.posY == 1 || matriz[Player.posY-1][Player.posX] == bC) // Si hay un bloque encima, o está en fila 1..
   {
      if(Ju_Colindante(Player, Oponente, DOWN)) // Si hay un jugador colindante abajo...
      {
         if(matriz[Player.posY+1][Player.posX] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if((matriz[Player.posY][Player.posX-1] == bC || matriz[Player.posY+1][Player.posX-2] == bC || matriz[Player.posY+2][Player.posX-1] == bC)
               &&
               (matriz[Player.posY][Player.posX+1] == bC || matriz[Player.posY+1][Player.posX+2] == bC || matriz[Player.posY+2][Player.posX+1] == bC))
            {
               return '\0'; // Si a los lados de los jugadores hay bloques, no se puede hace salto diagonal.
            }                                                                                                       // Si está en una esquina superior izquierda...
            if(Player.posX-2 == -1 || matriz[Player.posY][Player.posX-1] == bC || matriz[Player.posY+1][Player.posX-2] == bC || matriz[Player.posY+2][Player.posX-1] == bC)
            {
               if(matriz[Player.posY][Player.posX+1] == bC)
               {
                  return '\0';
               }
               else
               {
                  return 'E'; // Activar salto diagonal a la derecha del oponente.
               }
            }                                                                                                       // Si está en una esquina superior derecha...
            if(Player.posX+2 == 19 || matriz[Player.posY][Player.posX+1] == bC || matriz[Player.posY+1][Player.posX+2] == bC || matriz[Player.posY+2][Player.posX+1] == bC)
            {
               if(matriz[Player.posY][Player.posX-1] == bC)
               {
                  return '\0';
               }
               else
               {
                  return 'F'; // Activar salto diagonal a la izquierda del oponente.
               }
            }
            else
            {
               return 'A'; // Activar salto diagonal a la izquierda y derecha del oponente.
            }
         }
         return '\0'; // No activar salto diagonal.
      }
      if(Ju_Colindante(Player, Oponente, RIGHT)) // Si hay un jugador colindante a la derecha...
      {
         if(matriz[Player.posY][Player.posX+1] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if(matriz[Player.posY][Player.posX-1] == bC) // Si está en una esquina superior izquierda...
            {
               return 'G'; // Activar salto diagonal hacía abajo del oponente
            }
         }
         return '\0';
      }
      if(Ju_Colindante(Player, Oponente, LEFT)) // Si hay un jugador colindante a la izquierda...
      {
         if(matriz[Player.posY][Player.posX-1] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if(matriz[Player.posY][Player.posX+1] == bC) // Si está en una esquina superior derecha...
            {
               return 'H'; // Activar salto diagonal hacia abajo del oponente
            }
         }
      }
      return '\0'; // No activar salto diagonal.
   }
   if(Player.posY == 17 || matriz[Player.posY+1][Player.posX] == bC) // Si hay un bloque abajo, o está en fila 17...
   {
      if(Ju_Colindante(Player, Oponente, UP)) // Si hay un jugador colindante arriba...
      {
         if(matriz[Player.posY-1][Player.posX] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if((matriz[Player.posY][Player.posX-1] == bC || matriz[Player.posY-1][Player.posX-2] == bC || matriz[Player.posY-2][Player.posX-1] == bC)
               &&
               (matriz[Player.posY][Player.posX+1] == bC || matriz[Player.posY-1][Player.posX+2] == bC || matriz[Player.posY-2][Player.posX+1] == bC))
            {
               return '\0'; // No activar salto diagonal.
            }                                                                                                       // Si está en la esquina inferior izquierda...
            if(Player.posX-2 == -1 || matriz[Player.posY][Player.posX-1] == bC || matriz[Player.posY-1][Player.posX-2] == bC || matriz[Player.posY-2][Player.posX-1] == bC)
            {
               if(matriz[Player.posY][Player.posX+1] == bC)
               {
                  return '\0';
               }
               else
               {
                  return 'E'; // Activar salto diagonal a la derecha del oponente.
               }
            }                                                                                                       // Si está en la esquina inferior derecha...
            if(Player.posX+2 == 19 || matriz[Player.posY][Player.posX+1] == bC || matriz[Player.posY-1][Player.posX+2] == bC || matriz[Player.posY-2][Player.posX+1] == bC)
            {
               if(matriz[Player.posY][Player.posX-1] == bC)
               {
                  return '\0';
               }
               else
               {
                  return 'F'; // Activar salto diagonal a la izquierda del oponente.
               }
            }
            else
            {
               return 'B'; // Activar salto diagonal a la izquierda y derecha del oponente.
            }
         }
         return '\0'; // No activar salto diagonal.
      }
      if(Ju_Colindante(Player, Oponente, RIGHT)) // Si hay un jugador colindante a la derecha...
      {
         if(matriz[Player.posY][Player.posX+1] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if(matriz[Player.posY][Player.posX-1] == bC) // Si hay bloque a la izquierda...
            {
               return 'I'; // Activar salto diagonal hacia arriba del oponente
            }
         }
         return '\0'; // No activar salto diagonal.
      }
      if(Ju_Colindante(Player, Oponente, LEFT)) // Si hay un jugador colindante a la izquierda...
      {
         if(matriz[Player.posY][Player.posX-1] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if(matriz[Player.posY][Player.posX+1] == bC) // Si hay bloque a la derecha...
            {
               return 'J'; // Activar salto diagonal hacia arriba del oponente.
            }
         }
      }
      return '\0'; // No activar salto diagonal.
   }
   if(Player.posX == 1 || matriz[Player.posY][Player.posX-1] == bC) // Si hay un bloque a la izquierda o está en columna 1...
   {
      if(Ju_Colindante(Player, Oponente, RIGHT)) // Si hay un jugador colindante a la derecha...
      {
         if(matriz[Player.posY][Player.posX+1] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if(matriz[Player.posY+1][Player.posX+2] == bC || matriz[Player.posY+2][Player.posX+1] == bC)
            {
               return 'I'; // Activar salto diagonal hacia arriba del oponente.
            }
            if(matriz[Player.posY-1][Player.posX+2] == bC || matriz[Player.posY-2][Player.posX+1] == bC)
            {
               return 'G'; // Activar salto diagonal hacía abajo del oponente.
            }
            return 'C'; // Activar salto diagonal hacia arriba y abajo del oponente.
         }
      }
      return '\0'; // No activar salto diagonal.
   }
   if(Player.posX == 17 || matriz[Player.posY][Player.posX+1] == bC) // Si hay un bloque a la derecha o está en columna 17...
   {
      if(Ju_Colindante(Player, Oponente, LEFT)) // Si hay un jugador colindante a la izquierda...
      {
         if(matriz[Player.posY][Player.posX-1] != bC) // Si entre ambos jugadores no hay un bloque...
         {
            if(matriz[Player.posY+1][Player.posX-2] == bC || matriz[Player.posY+2][Player.posX-1] == bC)
            {
               return 'J'; // Activar salto diagonal hacia arriba del oponente.
            }
            if(matriz[Player.posY-1][Player.posX-2] == bC || matriz[Player.posY-2][Player.posX-1] == bC)
            {
               return 'H'; // Activar salto diagonal hacia abajo del oponente.
            }
            return 'D'; // Activar salto diagonal hacia arriba y abajo del oponente.
         }
      }
   }
   return '\0'; // No activar salto diagonal.
}

// True si hay jugadores juntos.
bool Ju_Colindante(Jugador& Player, Jugador& Oponente, char Dir)
{
   switch(Dir)
   {  // Player y Oponente se sobreponen si...
      case UP    : return Player.posX == Oponente.posX && Player.posY-2 == Oponente.posY;

      case DOWN  : return Player.posX == Oponente.posX && Player.posY+2 == Oponente.posY;

      case LEFT  : return Player.posY == Oponente.posY && Player.posX-2 == Oponente.posX;
   }
 /* Case RIGHT */  return Player.posY == Oponente.posY && Player.posX+2 == Oponente.posX;
}

void Hallar_salida()
{
   // Crear copia de matriz;
   char matrizAUX[alto][ancho];
   for(int i=0; i<alto; i++)
   {
      for(int k=0; k<ancho; k++)
      {
         matrizAUX[i][k] = matriz[i][k];
      }
   } // Asignar a sálida el valor booleano de la disyuncion de hay_salida() de los 2 jugadores.
   Salida = hay_salida(matrizAUX, Jugador_1.posX, Jugador_1.posY, Jugador_1.posX, Jugador_1.posY,  1, Jugador_1.cod)
            &&
            hay_salida(matrizAUX, Jugador_2.posX, Jugador_2.posY, Jugador_1.posX, Jugador_1.posY, 17, Jugador_2.cod);
}

// Backtracking, método para saber si un jugador a sido encerrado.
bool hay_salida(char matrizAUX[alto][ancho], int posX, int posY, int posXaux, int posYaux, int meta, char jugador)
{
   if (posY<0 || posX<0 || posY>=alto || posX>=ancho) return false;
   if (matrizAUX[posYaux][posXaux] == bC) return false;
   if (matrizAUX[posY][posX] == jugador) return false;
   if (posY == meta) return true;
   matrizAUX[posY][posX] = jugador;
   bool resp_clon1 = hay_salida(matrizAUX, posX  ,posY-2, posX  ,posY-1, meta, jugador);
   bool resp_clon2 = hay_salida(matrizAUX, posX  ,posY+2, posX  ,posY+1, meta, jugador);
   bool resp_clon3 = hay_salida(matrizAUX, posX+2,posY  , posX+1,posY  , meta, jugador);
   bool resp_clon4 = hay_salida(matrizAUX, posX-2,posY  , posX-1,posY  , meta, jugador);
   return resp_clon1 || resp_clon2 || resp_clon3 || resp_clon4;
}

// True si el bloque que controlamos está sobre otro.
bool Bloque_Superpuesto()
{
   if(matriz[Bloque.posY1][Bloque.posX1] != bC
      ||
      matriz[Bloque.posY2][Bloque.posX2] != bC
      ||
      matriz[Bloque.posY3][Bloque.posX3] != bC)
   {
      return true;
   }
   else
   {
      return false;
   }
}

// Verifica si aún no hay ganadores.
bool Sin_ganadores()
{
   if((Jugador_1.posY == 1) || (Jugador_2.posY == 17)) // Los numeros son las posiciones en las
   {                                                   // que cada jugador gana.
      return false;
   }
   return true;
}

// Muestra quién ganó el juego
void Pantalla_del_ganador()
{
   char ganador;
   if(Jugador_1.posY == 1)
   {
      ganador = P1;
   }
   else
   {
      ganador = P2;
   }
   system("cls");
   cout << "\n\n\n\n\n\n\n\n\n\tFin del juego\n\nGanador: " << ganador << endl;
   getch();
}
