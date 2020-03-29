package nonogram.game.edu.Menu;
import javafx.scene.paint.Color;
import javafx.application.*;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.stage.*;
import javafx.scene.*;
import javafx.scene.layout.*;
import javafx.geometry.Insets;
import javafx.scene.image.Image;
import nonogram.game.edu.Gameplay.GameScene;
import nonogram.game.edu.Gameplay.GameSettings;
import nonogram.game.edu.ImageProcessing.Plansza;

import org.json.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileSystemView;


public class MainMenu extends Application {


    Stage window;
    Scene MenuScene, scene2, scene3, scene4, scene5, scene6,scene7, scene8;
    GameSettings gs;
    JFileChooser jfc;
	File selectedFile;
	String path;
    public static void main(String[] args) {
    	
        launch(args);

    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        gs = new GameSettings();
        window = primaryStage;
        Parent fxml = FXMLLoader.load(getClass().getResource("MainMenuLayout.fxml"));

        //Layout 1 - Menu
        VBox Menu = new VBox();

        Menu.setAlignment(Pos.CENTER);
        Button buttonNowaGra = new Button("Nowa Gra");
        buttonNowaGra.setOnAction(e -> {


            gs = new GameSettings();
            window.setScene(scene2);
        });
        Button buttonWczytajGre = new Button("Wczytaj Gre");
        buttonWczytajGre.setOnAction(e -> {
            InputStream is = null;
            try {
                is = new FileInputStream("last_game.txt");
            } catch (FileNotFoundException ex) {
                ex.printStackTrace();
            }
            BufferedReader buf = new BufferedReader(new InputStreamReader(is));
            String line = null;
            try {
                line = buf.readLine();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
            StringBuilder sb = new StringBuilder();

            while(line != null){
                sb.append(line).append("\n");
                try {
                    line = buf.readLine();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }

            String fileAsString = sb.toString();
            JSONObject gameSettings = new JSONObject(fileAsString);
            System.out.println(gameSettings);

            String[] arg = {"plansza"};
            JSONObject plansza = new JSONObject(gameSettings, arg);
            String[] arg2 = {"rozmiar"};
            JSONObject rozmiar = new JSONObject(plansza, arg2);
            //System.out.println(plansza);
            int size = plansza.getJSONObject("plansza").getInt("rozmiar");
            //System.out.println(gameSettings.getString("netColor"));
            gs = new GameSettings();

            gs.p.rozmiar = plansza.getJSONObject("plansza").getInt("rozmiar");
            for (int i=0; i<2*gs.p.rozmiar; i++)
                for (int j=0; j<(gs.p.rozmiar)/2; j++)
                    gs.p.info[i][j] = plansza.getJSONObject("plansza").getJSONArray("info").getJSONArray(i).getInt(j);
            for (int i=0; i<gs.p.rozmiar; i++)
                for (int j=0; j<gs.p.rozmiar; j++)
                    gs.p.fillState[i][j] = plansza.getJSONObject("plansza").getJSONArray("fillState").getJSONArray(i).getInt(j);
            for (int i=0; i<gs.p.rozmiar; i++)
                for (int j=0; j<gs.p.rozmiar; j++)
                    gs.p.wypelnienie[i][j] = plansza.getJSONObject("plansza").getJSONArray("wypelnienie").getJSONArray(i).getBoolean(j);
            gs.netColor = Color.PINK;
            gs.squareColor = Color.BLACK;
            gs.bgColor = Color.WHITE;
            gs.crossColor = Color.BLACK;
            gs.infoColor = Color.BLACK;
            gs.netWidth = gameSettings.getDouble("netWidth");
            gs.crossWidth = gameSettings.getDouble("crossWidth");
            //System.out.println(plansza.getJSONObject("plansza").getJSONArray("fillState"));

            try {
                gs.p.ustawInfo();
                new GameScene(window, gs, MenuScene);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        Button buttonStatystyki = new Button("Statystyki");
        buttonStatystyki.setOnAction(e -> window.setScene(scene7));
        Button buttonSzybkaGra = new Button("Szybka gra");
        buttonSzybkaGra.setOnAction(e -> {
            try {

                new GameScene(window, new GameSettings(), MenuScene);
            }catch (Exception ex){

            }
        });
        Menu.getChildren().addAll(buttonNowaGra,buttonWczytajGre,buttonStatystyki,  buttonSzybkaGra);
        Menu.setPadding(new Insets(10, 0, 0, 0));
        Menu.setSpacing(15);
        primaryStage.setMinHeight(600);
        primaryStage.setMinWidth(800);
        Menu.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");
        MenuScene = new Scene(Menu, 800, 600);


        // Layout 2 Nowa gra
        VBox NowaGra = new VBox();
        NowaGra.setAlignment(Pos.CENTER);
        Button buttonPowrotdoMenu1 = new Button("Powrót do Menu");
        buttonPowrotdoMenu1.setOnAction(e -> window.setScene(MenuScene));
        Button buttonOpcjeRozgrywki = new Button("Opcje rozgrywki");
        buttonOpcjeRozgrywki.setOnAction(e -> window.setScene(scene8));
        Button buttonWyborRozmiaru = new Button("Wybór obrazka");

        buttonWyborRozmiaru.setOnAction(e -> {
            try {
            	new OpenL();
            	int sizeBoard = 5; // change for bigger jpg image
            	int ton = 80;
            	int board[][];
            	
            	while(true)
        		{
        			nonogram.game.edu.ImageProcessing.ImageToBoard imgtb = new nonogram.game.edu.ImageProcessing.ImageToBoard(path, sizeBoard, ton);
        			
        			if(imgtb.checkBoard())
        			{
        				System.out.println("x");
        				board = imgtb.board;
        				break;
        			}
        			else
        			{
        				System.out.println("y");
        				ton += 10;
        			}
        		}

            	
                Plansza ps  = new Plansza(sizeBoard);
                for(int i = 0; i < sizeBoard; i++)
                {
                	for(int j = 0; j < sizeBoard; j++)
                	{
                		if(board[i][j] == 0)
                		{
                			ps.wypelnienie[j][i] = true;
                		}
                	}
                }
                ps.ustawInfo();

                GameSettings gs = new GameSettings();
                gs.p = ps;
                new GameScene(window, gs, MenuScene);
            }catch (Exception ex){

            }

        });
        Button buttonStartujRozgrywke = new Button("Start!");
        buttonStartujRozgrywke.setOnAction(e -> {
            try {
                Plansza ptest = new Plansza(15);
                gs.p = ptest;
                gs.p.getRandomBoard();
                gs.p.ustawInfo();
                new GameScene(window, gs, MenuScene);
            }catch (Exception ex){

            }
        });
        NowaGra.getChildren().addAll(buttonPowrotdoMenu1,buttonWyborRozmiaru,buttonOpcjeRozgrywki,buttonStartujRozgrywke);
        NowaGra.setPadding(new Insets(10, 0, 0, 0));
        NowaGra.setSpacing(15);
        NowaGra.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");
        scene2 = new Scene(NowaGra, 800, 600);

        //Layout 3 Wczytaj gre
        VBox WczytajGre = new VBox();
        WczytajGre.setAlignment(Pos.TOP_CENTER);
        Button buttonPowrotdoMenu2 = new Button("Powrót do Menu");
        buttonPowrotdoMenu2.setOnAction(e -> {
            try {
                /// GameSettings gs /// MIKOLAJ wczytanie!!!!!!
                new GameScene(window, gs, MenuScene);
            }catch (Exception ex){

            }
        });
        WczytajGre.getChildren().addAll(buttonPowrotdoMenu2);
        WczytajGre.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");
        WczytajGre.setPadding(new Insets(10, 0, 0, 0));
        scene3 = new Scene(WczytajGre, 800, 600);


        //Layout 4 Statystyki
        HBox Statystyki = new HBox(20);
        Statystyki.setAlignment(Pos.TOP_CENTER);
        Button buttonPowrotdoMenu3 = new Button("Powrót do Menu");
        buttonPowrotdoMenu3.setOnAction(e -> window.setScene(MenuScene));
        Statystyki.getChildren().addAll(buttonPowrotdoMenu3);
        Statystyki.setPadding(new Insets(10, 0, 0, 0));
        Statystyki.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");

        scene7 = new Scene(Statystyki, 800, 600);

        //Layout 5 Opcje rozgrywki
        HBox OpcjeRozgrywki = new HBox(20);
        OpcjeRozgrywki.setAlignment(Pos.TOP_CENTER);
        Button buttonPowrotdoMenu4 = new Button("Powrót do Menu");
        buttonPowrotdoMenu4.setOnAction(e -> window.setScene(MenuScene));
        Button red = new Button("Red"); 
        red.setOnAction(e ->{

            GameSettings gs = new GameSettings();
            gs.squareColor = Color.RED;
            
        	
        });



        OpcjeRozgrywki.getChildren().addAll(buttonPowrotdoMenu4,red);
        OpcjeRozgrywki.setPadding(new Insets(10, 0, 0, 0));
        scene8 = new Scene(OpcjeRozgrywki, 800, 600);
        OpcjeRozgrywki.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");

        //Layout 6 Wybór rozmiaru planszy
        VBox WyborRozmiaru = new VBox();
        WyborRozmiaru.setAlignment(Pos.CENTER);
        Button buttonWczytanieObrazka = new Button("Wczytanie obrazka");
        buttonWczytanieObrazka.setOnAction(e -> {
        window.setScene(scene6);
        });
        Button buttonLosowanieObrazka = new Button("Losowanie obrazka");
        buttonLosowanieObrazka.setOnAction(e -> window.setScene(scene6));
        Button buttonPowrotdoMenu5 = new Button("Powrót do Menu");
        buttonPowrotdoMenu5.setOnAction(e -> window.setScene(MenuScene));
        WyborRozmiaru.getChildren().addAll(buttonWczytanieObrazka, buttonLosowanieObrazka, buttonPowrotdoMenu5);
        WyborRozmiaru.setPadding(new Insets(10, 100, 10, 100));
        WyborRozmiaru.setSpacing(15);
        WyborRozmiaru.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");
        scene4 = new Scene(WyborRozmiaru, 800, 600);

        //Layout 7 Wczytaj obrazek
        HBox WczytajObrazek = new HBox();
        Button buttonPowrotdoMenu6 = new Button("Powrót do Menu");
        buttonPowrotdoMenu6.setOnAction(e -> window.setScene(MenuScene));
        WczytajObrazek.getChildren().addAll(buttonPowrotdoMenu6);
        WczytajObrazek.setPadding(new Insets(10, 10, 10, 200));
        scene6 = new Scene(WczytajObrazek, 500, 500);
        //Layout 8 Losuj Obrazek
        HBox LosujObrazek = new HBox(20);
        Button buttonPowrotdoMenu7 = new Button("Powrót do Menu");
        buttonPowrotdoMenu7.setOnAction(e -> window.setScene(MenuScene));
        LosujObrazek.setPadding(new Insets(10, 10, 10, 200));
        scene6 = new Scene(LosujObrazek, 800, 600);


        //Display scene 1 at first
        window.setScene(MenuScene);
        window.setTitle("Nonogram designed to make you happy");

        window.getIcons().add(new Image(getClass().getResourceAsStream("logo.jpg")));
        window.show();
    }
    
    class OpenL //implements ActionListener
	{
		//public void actionPerformed(ActionEvent e)
		OpenL(){
			jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
			int returnValue = jfc.showOpenDialog(null);

			if (returnValue == JFileChooser.APPROVE_OPTION)
			{
				selectedFile = jfc.getSelectedFile();
				System.out.println(selectedFile.getAbsolutePath());
				path = selectedFile.getAbsolutePath();
			}
		}
	}

}
