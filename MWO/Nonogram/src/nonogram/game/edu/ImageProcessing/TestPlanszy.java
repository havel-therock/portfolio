package nonogram.game.edu.ImageProcessing;

/**
 *
 * @author MD
 */
public class TestPlanszy {

    /*public static void main(String[] args){

      Plansza plansza = new Plansza(12);
      plansza.testowaPlansza("rozgwiazda");
      //System.out.println(plansza.rozmiar);
      //pokazInfo(plansza);
      Plansza plansza2 = plansza.zwrocInfo(plansza);
      pokazInfo(plansza2);
      //sprawdzInfo(plansza, plansza2);
      //System.out.println(plansza2.poprawneInfo());
    }*/

    public static void pokazInfo(Plansza plansza)
    {
      for (int i=0; i<2*plansza.rozmiar; i++){
        int z = 1;
        System.out.print((i+1)+": ["+plansza.info[i][0]);
        while(plansza.info[i][z] > 0){
          System.out.print(" "+plansza.info[i][z]);
          z++;
        }
        System.out.print("]\n");
      }
    }

    public static void sprawdzInfo(Plansza plansza, Plansza plansza2)
    {
      for (int i=0; i<2*plansza.rozmiar; i++){
        int z = 1;
        System.out.print((i+1)+": ["+(plansza.info[i][0] - plansza2.info[i][0]));
        while(plansza.info[i][z] > 0){
          System.out.print(" "+(plansza.info[i][z] - plansza2.info[i][z]));
          z++;
        }
        System.out.print("]\n");
      }
    }

}
