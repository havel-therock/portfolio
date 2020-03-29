package nonogram.game.edu.ImageProcessing;
/**
 * @author MD
 */

import java.util.Random;

public class Plansza {

    public int rozmiar;
    public int info[][];
    public boolean wypelnienie[][];
    public int fillState[][]; // 0 - bg 1 - square 2 - cross
    Random generator;

    public Plansza(int size) {
        generator = new Random();
        this.rozmiar = size;
        this.info = new int [2*size][(size+1)/2];
        this.wypelnienie = new boolean [size][size];
        this.fillState = new int [size][size];
    }

    public Plansza zwrocInfo(Plansza p)
    {
      Plansza i = new Plansza(p.rozmiar);

      // generowanie dla pierwszej (pionowej) po�owy
      for (int x = 0; x < p.rozmiar; x++){
        int z = 0;
        for (int y = 0; y < p.rozmiar; y++){
          if (p.wypelnienie[x][y] && i.info[x][0] == 0) i.info[x][0]++;
          else if (p.wypelnienie[x][y]) i.info[x][z]++;
          else if (!p.wypelnienie[x][y] && i.info[x][0] != 0 && p.wypelnienie[x][y] != p.wypelnienie[x][y-1]) z++;
        }}

      // generowanie dla drugiej (poziomej) po�owy
      for (int y = 0; y < p.rozmiar; y++){
        int z = 0;
        for (int x = 0; x < p.rozmiar; x++){
          if (p.wypelnienie[x][y] && i.info[15+y][0] == 0) i.info[15+y][0]++;
          else if (p.wypelnienie[x][y]) i.info[15+y][z]++;
          else if (!p.wypelnienie[x][y] && i.info[15+y][0] != 0 && p.wypelnienie[x][y] != p.wypelnienie[x-1][y]) z++;
        }}

      return i;
    }

  public void ustawInfo()
  {

    for(int i = 0; i < 2*rozmiar; i++){
      for(int j = 0; j < (rozmiar+1)/2; j++){
        this.info[i][j] = 0;
      }
    }
    // generowanie dla pierwszej (pionowej) po�owy
    for (int x = 0; x < this.rozmiar; x++){
      int z = 0;
      for (int y = 0; y < this.rozmiar; y++){
        if (this.wypelnienie[x][y] && this.info[x][0] == 0) this.info[x][0]++;
        else if (this.wypelnienie[x][y]) this.info[x][z]++;
        else if (!this.wypelnienie[x][y] && this.info[x][0] != 0 && this.wypelnienie[x][y] != this.wypelnienie[x][y-1]) z++;
      }}

    // generowanie dla drugiej (poziomej) po�owy
    for (int y = 0; y < this.rozmiar; y++){
      int z = 0;
      for (int x = 0; x < this.rozmiar; x++){
       if (this.wypelnienie[x][y] && this.info[rozmiar+y][0] == 0) this.info[rozmiar+y][0]++;
        else if (this.wypelnienie[x][y]) this.info[rozmiar+y][z]++;
        else if (!this.wypelnienie[x][y] && x != 0 && this.wypelnienie[x][y] != this.wypelnienie[x-1][y]) z++;
      }}

    // generowanie dla pierwszej (pionowej) po�owy
/*    for(int i = 0; i < 2*rozmiar; i++){
      for(int j = 0; j < (rozmiar+1)/2; j++){
        this.info[i][j] = 0;
      }
    }

    for (int x = 0; x < this.rozmiar; x++){
      int z = 0;
      for (int y = this.rozmiar - 1; y >= 0; y--){
          if (this.wypelnienie[x][y] && this.info[x][0] == 0)
              this.info[x][0]++;
          else if (this.wypelnienie[x][y]) this.info[x][z]++;
          else if (!this.wypelnienie[x][y] && this.info[x][0] != 0 && this.wypelnienie[x][y] != this.wypelnienie[x][y+1]) z++;
      }}

    // generowanie dla drugiej (poziomej) po�owy
    for (int y = 0; y < this.rozmiar; y++){
      int z = 0;
      for (int x = this.rozmiar - 1; x >= 0; x--){
        if (this.wypelnienie[x][y] && this.info[this.rozmiar+y][0] == 0) this.info[rozmiar+y][0]++;
        else if (this.wypelnienie[x][y]) this.info[rozmiar+y][z]++;
        else if (!this.wypelnienie[x][y] && this.info[rozmiar+y][0] != 0 && this.wypelnienie[x][y] != this.wypelnienie[x+1][y]) z++;
      }}*/
  }

    public void generujPlansze()
    {
      int size = 8 + Math.abs(generator.nextInt()%17);
      System.out.println(size);
      this.rozmiar = size;
      this.info = new int [2*size][(size+1)/2];
      this.wypelnienie = new boolean [size][size];
      this.fillState = new int [size][size];

      for (int i=0; i<size; i++)
        for (int j=0; j<size; j++)
        {
          Random gen = new Random();
          int v = gen.nextInt(7);
          //System.out.println(v);
          if(v < 4)
            this.wypelnienie[i][j] = true;
          else
            this.wypelnienie[i][j] = false;
        }
      this.ustawInfo();
    }

    public boolean poprawneInfo()
    {
      int sum_pion = 0;
      int sum_poziom = 0;

      for (int i=0; i<this.rozmiar; i++){
        int z = 1;
        sum_pion += this.info[i][0];
        while(this.info[i][z] > 0){
          sum_pion += this.info[i][z];
          z++;
        }
      }

      for (int i=this.rozmiar; i<2*this.rozmiar; i++){
        int z = 1;
        sum_poziom += this.info[i][0];
        while(this.info[i][z] > 0){
          sum_poziom += this.info[i][z];
          z++;
        }
      }
      return (sum_poziom == sum_pion);
    }

    public int zwrocDlugosc()
    {
      System.out.println("zaczynam funckje");
      int dl = 0;
      for (int i=0; i<this.rozmiar*2; i++) {
        int max_dl = 0;
        while (this.info[i][max_dl] != 0) max_dl++;
        if (max_dl - 1 > dl) dl = max_dl - 1;
      }
      System.out.println(dl);
      return dl;
    }

    public void odwrocInfo()
    {
      for (int i=0; i<2*this.rozmiar; i++) {
        for (int j = 0; j < (this.rozmiar + 1) / 2; j++)
          System.out.print(this.info[i][j] + " ");
        System.out.println();
      }

      int tab[] = new int[2*this.rozmiar];
      for (int i=0; i<2*this.rozmiar; i++)
        for (int j = 0; j < (this.rozmiar + 1) / 2; j++){
          if (this.info[i][j] > 0) tab[i]++;
          else break;
        }
      for (int i=0; i<2*this.rozmiar; i++)
        for (int j=0; j<(tab[i]+1)/2; j++){
           int temp = this.info[i][j];
           this.info[i][j] = this.info[i][tab[i]/2 - j];
           this.info[i][tab[i]/2 - j] = temp;
        }

      System.out.println("\nPO:\n");

      for (int i=0; i<2*this.rozmiar; i++) {
        for (int j = 0; j < (this.rozmiar + 1) / 2; j++)
          System.out.print(this.info[i][j] + " ");
        System.out.println();
      }
    }

    public void getRandomBoard(){
      testowaPlansza(generator.nextInt(3));

    }

    public void testowaPlansza(int c) {

      int size;
      switch(c)
      {

        case 0:
        	   // Plansza(15);
            size = 15;
            this.rozmiar = size;
            this.info = new int [2*size][(size+1)/2];
            this.wypelnienie = new boolean [size][size];

          this.wypelnienie[0][7] = true;

          this.wypelnienie[1][6] = true;
          this.wypelnienie[1][7] = true;
          this.wypelnienie[1][8] = true;

          this.wypelnienie[2][5] = true;
          this.wypelnienie[2][6] = true;
          this.wypelnienie[2][7] = true;
          this.wypelnienie[2][8] = true;
          this.wypelnienie[2][9] = true;

          this.wypelnienie[3][5] = true;
          this.wypelnienie[3][6] = true;

          this.wypelnienie[3][8] = true;
          this.wypelnienie[3][9] = true;

          this.wypelnienie[4][4] = true;
          this.wypelnienie[4][5] = true;

          this.wypelnienie[4][8] = true;
          this.wypelnienie[4][9] = true;
          this.wypelnienie[4][10] = true;

          this.wypelnienie[5][0] = true;
          this.wypelnienie[5][1] = true;
          this.wypelnienie[5][2] = true;
          this.wypelnienie[5][3] = true;
          this.wypelnienie[5][4] = true;
          this.wypelnienie[5][5] = true;

          this.wypelnienie[5][8] = true;
          this.wypelnienie[5][9] = true;
          this.wypelnienie[5][10] = true;
          this.wypelnienie[5][11] = true;
          this.wypelnienie[5][12] = true;
          this.wypelnienie[5][13] = true;
          this.wypelnienie[5][14] = true;

          this.wypelnienie[6][0] = true;
          this.wypelnienie[6][1] = true;
          this.wypelnienie[6][2] = true;
          this.wypelnienie[6][3] = true;
          this.wypelnienie[6][4] = true;
          this.wypelnienie[6][5] = true;
          this.wypelnienie[6][6] = true;

          this.wypelnienie[6][8] = true;
          this.wypelnienie[6][9] = true;

          this.wypelnienie[6][13] = true;
          this.wypelnienie[6][14] = true;

          this.wypelnienie[7][1] = true;
          this.wypelnienie[7][2] = true;

          this.wypelnienie[7][8] = true;

          this.wypelnienie[7][11] = true;
          this.wypelnienie[7][12] = true;
          this.wypelnienie[7][13] = true;

          this.wypelnienie[8][2] = true;
          this.wypelnienie[8][3] = true;
          this.wypelnienie[8][4] = true;
          this.wypelnienie[8][5] = true;
          this.wypelnienie[8][6] = true;

          this.wypelnienie[8][9] = true;
          this.wypelnienie[8][10] = true;
          this.wypelnienie[8][11] = true;
          this.wypelnienie[8][12] = true;

          this.wypelnienie[9][3] = true;
          this.wypelnienie[9][4] = true;
          this.wypelnienie[9][5] = true;

          this.wypelnienie[9][10] = true;
          this.wypelnienie[9][11] = true;

          this.wypelnienie[10][2] = true;
          this.wypelnienie[10][3] = true;
          this.wypelnienie[10][4] = true;

          this.wypelnienie[10][8] = true;

          this.wypelnienie[10][11] = true;
          this.wypelnienie[10][12] = true;

          this.wypelnienie[11][2] = true;
          this.wypelnienie[11][3] = true;
          this.wypelnienie[11][4] = true;

          this.wypelnienie[11][7] = true;
          this.wypelnienie[11][8] = true;
          this.wypelnienie[11][9] = true;

          this.wypelnienie[11][11] = true;
          this.wypelnienie[11][12] = true;

          this.wypelnienie[12][1] = true;
          this.wypelnienie[12][2] = true;
          this.wypelnienie[12][3] = true;

          this.wypelnienie[12][5] = true;
          this.wypelnienie[12][6] = true;
          this.wypelnienie[12][7] = true;
          this.wypelnienie[12][8] = true;
          this.wypelnienie[12][9] = true;
          this.wypelnienie[12][10] = true;

          this.wypelnienie[12][12] = true;
          this.wypelnienie[12][13] = true;

          this.wypelnienie[13][1] = true;
          this.wypelnienie[13][2] = true;
          this.wypelnienie[13][3] = true;
          this.wypelnienie[13][4] = true;
          this.wypelnienie[13][5] = true;

          this.wypelnienie[13][9] = true;
          this.wypelnienie[13][10] = true;
          this.wypelnienie[13][11] = true;
          this.wypelnienie[13][12] = true;
          this.wypelnienie[13][13] = true;

          this.wypelnienie[14][1] = true;
          this.wypelnienie[14][2] = true;
          this.wypelnienie[14][3] = true;
          this.wypelnienie[14][4] = true;

          this.wypelnienie[14][10] = true;
          this.wypelnienie[14][11] = true;
          this.wypelnienie[14][12] = true;
          this.wypelnienie[14][13] = true;

          // poziomo
          this.info[0][0] = 1;
          this.info[1][0] = 3;
          this.info[2][0] = 5;
          this.info[3][0] = 2;
          this.info[3][1] = 2;
          this.info[4][0] = 2;
          this.info[4][1] = 3;

          this.info[5][0] = 6;
          this.info[5][1] = 7;
          this.info[6][0] = 7;
          this.info[6][1] = 2;
          this.info[6][2] = 2;
          this.info[7][0] = 2;
          this.info[7][1] = 1;
          this.info[7][2] = 3;
          this.info[8][0] = 5;
          this.info[8][1] = 4;
          this.info[9][0] = 3;
          this.info[9][1] = 2;

          this.info[10][0] = 3;
          this.info[10][1] = 1;
          this.info[10][2] = 2;
          this.info[11][0] = 3;
          this.info[11][1] = 3;
          this.info[11][2] = 2;
          this.info[12][0] = 3;
          this.info[12][1] = 6;
          this.info[12][2] = 2;
          this.info[13][0] = 5;
          this.info[13][1] = 5;
          this.info[14][0] = 4;
          this.info[14][1] = 4;

          // pionowo
          this.info[15][0] = 2;
          this.info[16][0] = 3;
          this.info[16][1] = 3;
          this.info[17][0] = 4;
          this.info[17][1] = 5;
          this.info[18][0] = 2;
          this.info[18][1] = 7;
          this.info[19][0] = 3;
          this.info[19][1] = 4;
          this.info[19][2] = 2;

          this.info[20][0] = 5;
          this.info[20][1] = 2;
          this.info[20][2] = 2;
          this.info[21][0] = 3;
          this.info[21][1] = 1;
          this.info[21][2] = 1;
          this.info[21][3] = 1;
          this.info[22][0] = 3;
          this.info[22][1] = 2;
          this.info[23][0] = 7;
          this.info[23][1] = 3;
          this.info[24][0] = 5;
          this.info[24][1] = 1;
          this.info[24][2] = 3;

          this.info[25][0] = 2;
          this.info[25][1] = 2;
          this.info[25][2] = 3;
          this.info[26][0] = 1;
          this.info[26][1] = 5;
          this.info[26][2] = 2;
          this.info[27][0] = 1;
          this.info[27][1] = 2;
          this.info[27][2] = 5;
          this.info[28][0] = 3;
          this.info[28][1] = 3;
          this.info[29][0] = 2;

        break;

    case 1:

      size = 15;
      this.rozmiar = size;
      this.info = new int [2*size][(size+1)/2];
      this.wypelnienie = new boolean [size][size];


//-------------------------------------------//
        this.wypelnienie[0][2] = true;
        this.wypelnienie[0][3] = true;
        this.wypelnienie[0][4] = true;
        this.wypelnienie[0][9] = true;
        this.wypelnienie[0][10] = true;
//-------------------------------------------//
        this.wypelnienie[1][1] = true;

        this.wypelnienie[1][4] = true;

        this.wypelnienie[1][8] = true;

        this.wypelnienie[1][11] = true;
//-------------------------------------------//
        this.wypelnienie[2][0] = true;

        this.wypelnienie[2][3] = true;
        this.wypelnienie[2][4] = true;

        this.wypelnienie[2][7] = true;

        this.wypelnienie[2][11] = true;
        this.wypelnienie[2][12] = true;
//-------------------------------------------//
        this.wypelnienie[3][0] = true;

        this.wypelnienie[3][2] = true;
        this.wypelnienie[3][3] = true;

        this.wypelnienie[3][7] = true;

        this.wypelnienie[3][10] = true;

        this.wypelnienie[3][12] = true;
        this.wypelnienie[3][13] = true;
        this.wypelnienie[3][14] = true;
//-------------------------------------------//
        this.wypelnienie[4][0] = true;

        this.wypelnienie[4][2] = true;

        this.wypelnienie[4][8] = true;
        this.wypelnienie[4][9] = true;

        this.wypelnienie[4][14] = true;
//-------------------------------------------//
        this.wypelnienie[5][0] = true;
        this.wypelnienie[5][1] = true;

        this.wypelnienie[5][3] = true;
        this.wypelnienie[5][4] = true;
        this.wypelnienie[5][5] = true;

        this.wypelnienie[5][9] = true;

        this.wypelnienie[5][13] = true;
        this.wypelnienie[5][14] = true;
//-------------------------------------------//
        this.wypelnienie[6][1] = true;
        this.wypelnienie[6][2] = true;
        this.wypelnienie[6][3] = true;
        this.wypelnienie[6][4] = true;
        this.wypelnienie[6][5] = true;
        this.wypelnienie[6][6] = true;
        this.wypelnienie[6][7] = true;
        this.wypelnienie[6][8] = true;
        this.wypelnienie[6][9] = true;

        this.wypelnienie[6][11] = true;
        this.wypelnienie[6][12] = true;
        this.wypelnienie[6][13] = true;
//-------------------------------------------//
        this.wypelnienie[7][1] = true;
        this.wypelnienie[7][2] = true;

        this.wypelnienie[7][9] = true;
        this.wypelnienie[7][10] = true;
        this.wypelnienie[7][11] = true;
//-------------------------------------------//
        this.wypelnienie[8][1] = true;

        this.wypelnienie[8][10] = true;
        this.wypelnienie[8][11] = true;
//-------------------------------------------//
        this.wypelnienie[9][1] = true;

        this.wypelnienie[9][4] = true;

        this.wypelnienie[9][7] = true;

        this.wypelnienie[9][11] = true;
//-------------------------------------------//
        this.wypelnienie[10][1] = true;

        this.wypelnienie[10][4] = true;
        this.wypelnienie[10][5] = true;
        this.wypelnienie[10][6] = true;
        this.wypelnienie[10][7] = true;

        this.wypelnienie[10][11] = true;
//-------------------------------------------//
        this.wypelnienie[11][0] = true;

        this.wypelnienie[11][3] = true;
        this.wypelnienie[11][4] = true;

        this.wypelnienie[11][7] = true;
        this.wypelnienie[11][8] = true;

        this.wypelnienie[11][11] = true;
        this.wypelnienie[11][12] = true;
//-------------------------------------------//
        this.wypelnienie[12][0] = true;


        this.wypelnienie[12][2] = true;

        this.wypelnienie[12][5] = true;

        this.wypelnienie[12][7] = true;
        this.wypelnienie[12][9] = true;

        this.wypelnienie[12][11] = true;

        this.wypelnienie[12][13] = true;
        this.wypelnienie[12][14] = true;
//-------------------------------------------//
        this.wypelnienie[13][0] = true;
        this.wypelnienie[13][1] = true;

        this.wypelnienie[13][3] = true;

        this.wypelnienie[13][5] = true;

        this.wypelnienie[13][8] = true;
        this.wypelnienie[13][9] = true;

        this.wypelnienie[13][12] = true;

        this.wypelnienie[13][14] = true;
//-------------------------------------------//
        this.wypelnienie[14][1] = true;
        this.wypelnienie[14][2] = true;
        this.wypelnienie[14][3] = true;

        this.wypelnienie[14][5] = true;
        this.wypelnienie[14][6] = true;
        this.wypelnienie[14][7] = true;
        this.wypelnienie[14][8] = true;

        this.wypelnienie[14][10] = true;
        this.wypelnienie[14][11] = true;
        this.wypelnienie[14][12] = true;

        this.wypelnienie[14][14] = true;

        // poziomo
        this.info[0][0] = 3;
        this.info[0][1] = 2;

        this.info[1][0] = 1;
        this.info[1][1] = 1;
        this.info[1][2] = 1;
        this.info[1][3] = 1;

        this.info[2][0] = 1;
        this.info[2][1] = 2;
        this.info[2][2] = 1;
        this.info[2][3] = 2;

        this.info[3][0] = 1;
        this.info[3][1] = 2;
        this.info[3][2] = 1;
        this.info[3][3] = 1;
        this.info[3][4] = 3;

        this.info[4][0] = 1;
        this.info[4][1] = 1;
        this.info[4][2] = 2;
        this.info[4][3] = 1;

        this.info[5][0] = 2;
        this.info[5][1] = 3;
        this.info[5][2] = 1;
        this.info[5][3] = 2;

        this.info[6][0] = 9;
        this.info[6][1] = 3;

        this.info[7][0] = 2;
        this.info[7][1] = 3;

        this.info[8][0] = 1;
        this.info[8][1] = 2;


        this.info[9][0] = 1;
        this.info[9][1] = 1;
        this.info[9][2] = 1;
        this.info[9][3] = 1;

        this.info[10][0] = 1;
        this.info[10][1] = 4;
        this.info[10][2] = 1;

        this.info[11][0] = 1;
        this.info[11][1] = 2;
        this.info[11][2] = 2;
        this.info[11][3] = 2;

        this.info[12][0] = 1;
        this.info[12][1] = 1;
        this.info[12][2] = 1;
        this.info[12][3] = 1;
        this.info[12][4] = 1;
        this.info[12][5] = 1;
        this.info[12][6] = 2;

        this.info[13][0] = 2;
        this.info[13][1] = 1;
        this.info[13][2] = 1;
        this.info[13][3] = 2;
        this.info[13][4] = 1;
        this.info[13][5] = 1;

        this.info[14][0] = 3;
        this.info[14][1] = 4;
        this.info[14][2] = 3;
        this.info[14][3] = 1;
        // pionowo
        this.info[15][0] = 4;
        this.info[15][1] = 3;

        this.info[16][0] = 1;
        this.info[16][1] = 6;
        this.info[16][2] = 2;

        this.info[17][0] = 1;
        this.info[17][1] = 2;
        this.info[17][2] = 2;
        this.info[17][3] = 1;
        this.info[17][4] = 1;

        this.info[18][0] = 1;
        this.info[18][1] = 2;
        this.info[18][2] = 2;
        this.info[18][3] = 1;
        this.info[18][4] = 2;

        this.info[19][0] = 3;
        this.info[19][1] = 2;
        this.info[19][2] = 3;


        this.info[20][0] = 2;
        this.info[20][1] = 1;
        this.info[20][2] = 3;

        this.info[21][0] = 1;
        this.info[21][1] = 1;
        this.info[21][2] = 1;

        this.info[22][0] = 2;
        this.info[22][1] = 1;
        this.info[22][2] = 4;
        this.info[22][3] = 1;

        this.info[23][0] = 1;
        this.info[23][1] = 1;
        this.info[23][2] = 1;
        this.info[23][3] = 1;
        this.info[23][4] = 2;


        this.info[24][0] = 1;
        this.info[24][1] = 4;
        this.info[24][2] = 2;

        this.info[25][0] = 1;
        this.info[25][1] = 1;
        this.info[25][2] = 2;
        this.info[25][3] = 1;

        this.info[26][0] = 2;
        this.info[26][1] = 7;
        this.info[26][2] = 1;

        this.info[27][0] = 2;
        this.info[27][1] = 1;
        this.info[27][2] = 1;
        this.info[27][3] = 2;

        this.info[28][0] = 1;
        this.info[28][1] = 2;
        this.info[28][2] = 1;

        this.info[29][0] = 3;
        this.info[29][1] = 3;


      break;
        case 2:
          // Plansza(15);
          size = 4;
          this.rozmiar = size;
          this.info = new int [2*size][(size+1)/2];
          this.wypelnienie = new boolean [size][size];
          this.wypelnienie[0][0] = true;
          this.wypelnienie[0][1] = true;
          this.wypelnienie[0][3] = true;
          this.wypelnienie[1][0] = true;
          this.wypelnienie[3][0] = true;
          this.wypelnienie[1][2] = true;

          break;
      default:
      break;

    }
    }

}
