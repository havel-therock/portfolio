package nonogram.game.edu.Gameplay;

import javafx.beans.value.ChangeListener;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;

import org.json.*;

import java.io.*;


public class GameScene{

    Stage window;
    Scene scene, menu;
    Canvas canvas;
    GraphicsContext gc;
    GameSettings gs;


    public GameScene(Stage window, GameSettings gs, Scene menu) throws Exception {
        this.menu = menu;
        this.window = window;
        this.gs = gs;
        FXMLLoader Loader = new FXMLLoader();
        Loader.setLocation(this.getClass().getResource("GameplaySceneLayout.fxml"));

        BorderPane root = Loader.load();
        root.getStylesheets().add("nonogram/game/edu/Menu/Viper.css");
        boardInit(root);
        buttonsInit(Loader);
        resizeBoard();
        updateBoard();
    }

    private void boardInit(BorderPane root){
        canvas = new Canvas();
        gc = canvas.getGraphicsContext2D();
        root.setCenter(canvas);
        scene = new Scene(root);
        window.setScene(scene);

        setBoardSize();
        plainBoard();
        drawCurrentSate(); // for read play (continue option)
        drawInfo();
    }

    private void buttonsInit(FXMLLoader Loader) throws IOException{
        Button save = (Button)Loader.getNamespace().get("save");
        Button exit = (Button)Loader.getNamespace().get("exit");
        exit.setOnAction(e -> window.setScene(menu));
        save.setOnAction(e -> {
            //serializacja obiektu GameSettings
            JSONObject plansza = new JSONObject();
            try {
                 plansza.put("rozmiar", gs.p.rozmiar);
            	 plansza.put("info", gs.p.info);
                 plansza.put("wypelnienie", gs.p.wypelnienie);
                 plansza.put("fillState", gs.p.fillState);
                 JSONObject gameSettings = new JSONObject();
                 gameSettings.put("netColor", gs.netColor);
                 gameSettings.put("squareColor", gs.squareColor);
                 gameSettings.put("bgColor", gs.bgColor);
                 gameSettings.put("crossColor", gs.crossColor);
                 gameSettings.put("infoColor", gs.infoColor);
                 gameSettings.put("netWidth", gs.netWidth);
                 gameSettings.put("crossWidth", gs.crossWidth);
                 gameSettings.put("BLOCK_SIZE", gs.BLOCK_SIZE);
                 gameSettings.put("plansza", plansza);

                 System.out.println(gameSettings.toString());
                 try (FileWriter file = new FileWriter("last_game.txt")) {
                     file.write(gameSettings.toString());
                 } 
			} catch (JSONException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
            catch (IOException ex) {
                ex.printStackTrace();
            }

            

        });
    }



    private void setBoardSize(){
        int min  = (int) Math.min(window.getWidth() - 50, window.getHeight() - 150); //offset 50 to not put canvas over buttons
        //calculate offset for info
        // get max of two offsets = maxoff
        //offset == number in row?
        int blockInCanvas = gs.p.rozmiar + 12;//gs.p.zwrocDlugosc();//maxoff;
        gs.BLOCK_SIZE =  min/blockInCanvas;//gs.p.rozmiar; // divide over maxoff + gs.p.rozmiar
        canvas.setWidth(gs.BLOCK_SIZE * blockInCanvas);//gs.p.rozmiar); // + width offset for numbers with informations
        canvas.setHeight(gs.BLOCK_SIZE * blockInCanvas);//gs.p.rozmiar); // + height offset for numbers with informations
    }

    private void plainBoard(){
        gc.setFill(gs.bgColor);
        gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
        net();
    }

    private void resizeBoard(){
        ChangeListener<Number> stageSizeListener = ((observable, oldValue, newValue) ->{
            setBoardSize();
            plainBoard();
            drawCurrentSate();
            drawInfo();
        });
        window.widthProperty().addListener(stageSizeListener);
        window.heightProperty().addListener(stageSizeListener);

    }

    private void drawCurrentSate(){
        for(int i = 0; i < gs.p.rozmiar; i++){
            for(int j = 0; j < gs.p.rozmiar; j++){
                drawSquare(i, j); //inverted cords
            }
        }
        net();
    }


    private void updateBoard(){
        canvas.setOnMouseClicked(e -> {
            int x = (int) e.getX();
            int y = (int) e.getY();
            int countX = 0, countY = 0;
            while ( x > 0 || y > 0){
                x = x - gs.BLOCK_SIZE;
                if(x > 0){
                    countX++;
                }
                y = y - gs.BLOCK_SIZE;
                if(y > 0){
                    countY++;
                }
            }

            updateSquare(countX, countY);
            for (int i=0; i<gs.p.rozmiar; i++) {
                for (int j = 0; j < gs.p.rozmiar; j++)
                    System.out.print(gs.p.fillState[i][j] + " ");
                System.out.println();
            }
            net();
            System.out.println(e.getX() + " " + e.getY());

            if(checkWin()){
                System.out.println("Gratulacje wygrałeś");
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Nonogram");
                alert.setHeaderText("Gratulacje wygrałeś!!!");
                alert.setContentText("Dziękujemy za udział w naszej grze.");
                alert.showAndWait();
                window.setScene(menu);
            }
        });
    }

    private boolean checkWin(){
        for(int i = 0; i < gs.p.rozmiar; i++){
            for (int j = 0; j < gs.p.rozmiar; j++){
                if(gs.p.wypelnienie[i][j]){
                    if(gs.p.fillState[i][j] != 1){
                        System.out.println(gs.p.fillState[0][7] + "    " + "i: " + i +" j: " + j + "true");
                        return false;
                    }
                }else{
                    if(gs.p.fillState[i][j] == 1){
                        System.out.println(gs.p.fillState[0][7] + "    " +"i: " + i +" j: " + j + "false");
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private void net(){
        gc.setStroke(gs.netColor);
        gc.setLineWidth(gs.netWidth);
        for(int i = 0; i <= gs.p.rozmiar; i++){
            gc.strokeLine(0, i*gs.BLOCK_SIZE, canvas.getWidth(), i*gs.BLOCK_SIZE);
            gc.strokeLine(i*gs.BLOCK_SIZE, 0, i*gs.BLOCK_SIZE, canvas.getHeight());
        }
    }

    private void updateSquare(int countX, int countY){
        if(!(countX >= gs.p.rozmiar || countY >= gs.p.rozmiar)){
            switch (gs.p.fillState[countY][countX]){
                case 0:
                    gc.setFill(gs.squareColor);
                    gc.fillRect(countX*gs.BLOCK_SIZE, countY*gs.BLOCK_SIZE, gs.BLOCK_SIZE, gs.BLOCK_SIZE);
                    gs.p.fillState[countY][countX] = 1; //inverted cords
                    break;
                case 1:
                    double x1 = countX*gs.BLOCK_SIZE, y1 =countY*gs.BLOCK_SIZE;
                    gc.setFill(gs.bgColor);
                    gc.fillRect(x1, y1, gs.BLOCK_SIZE, gs.BLOCK_SIZE);

                    gc.setStroke(gs.crossColor);
                    gc.setLineWidth(gs.crossWidth);
                    gc.strokeLine(x1 + gs.crossWidth, y1 + gs.crossWidth, x1 + gs.BLOCK_SIZE - gs.crossWidth, y1 + gs.BLOCK_SIZE - gs.crossWidth);
                    gc.strokeLine(x1 + gs.BLOCK_SIZE - gs.crossWidth, y1 + gs.crossWidth, x1 + gs.crossWidth, y1 + gs.BLOCK_SIZE - gs.crossWidth);
                    gs.p.fillState[countY][countX] = 2; //inverted cords
                    break;
                case 2:
                    gc.setFill(gs.bgColor);
                    gc.fillRect(countX*gs.BLOCK_SIZE, countY*gs.BLOCK_SIZE, gs.BLOCK_SIZE, gs.BLOCK_SIZE);
                    gs.p.fillState[countY][countX] = 0; //inverted cords
                    break;

                default:
                    break;
            }
        }
    }

    private void drawSquare(int countX, int countY){
        int readY = countY;
        int readX = countX;
        countX = readY;
        countY = readX;
        switch (gs.p.fillState[readX][readY]){ //inverted
            case 1:
                gc.setFill(gs.squareColor);
                gc.fillRect(countX*gs.BLOCK_SIZE, countY*gs.BLOCK_SIZE, gs.BLOCK_SIZE, gs.BLOCK_SIZE);
                break;
            case 2:
                double x1 = countX*gs.BLOCK_SIZE, y1 = countY*gs.BLOCK_SIZE;
                gc.setFill(gs.bgColor);
                gc.fillRect(x1, y1, gs.BLOCK_SIZE, gs.BLOCK_SIZE);

                gc.setStroke(gs.crossColor);
                gc.setLineWidth(gs.crossWidth);
                gc.strokeLine(x1 + gs.crossWidth, y1 + gs.crossWidth, x1 + gs.BLOCK_SIZE - gs.crossWidth, y1 + gs.BLOCK_SIZE - gs.crossWidth);
                gc.strokeLine(x1 + gs.BLOCK_SIZE - gs.crossWidth, y1 + gs.crossWidth, x1 + gs.crossWidth, y1 + gs.BLOCK_SIZE - gs.crossWidth);
                break;
            case 0:
                gc.setFill(gs.bgColor);
                gc.fillRect(countX*gs.BLOCK_SIZE, countY*gs.BLOCK_SIZE, gs.BLOCK_SIZE, gs.BLOCK_SIZE);
                break;

            default:
                break;
        }
    }

    private void drawInfo(){
        gc.setFill(gs.infoColor);
        gc.setFont(new Font("Verdana", gs.BLOCK_SIZE*0.5)); //0.75
        for(int i = 0; i < gs.p.rozmiar; i++){
            for(int j = 0; j < gs.p.info[i].length; j++){
                if(gs.p.info[i][j] == 0){
                    break;
                }else{
                    gc.fillText(String.valueOf(gs.p.info[i][j]), gs.BLOCK_SIZE * (gs.p.rozmiar + j), (gs.BLOCK_SIZE * i) + gs.BLOCK_SIZE*0.75);
                }
            }
        }
        for(int i = gs.p.rozmiar; i < 2*gs.p.rozmiar; i++){
            for(int j = 0; j < gs.p.info[i].length; j++){
                if(gs.p.info[i][j] == 0){
                    break;
                }else{
                    gc.fillText(String.valueOf(gs.p.info[i][j]), gs.BLOCK_SIZE * (i - gs.p.rozmiar) + gs.BLOCK_SIZE*0.25, gs.BLOCK_SIZE * (gs.p.rozmiar + j + 1));
                }
            }
        }
    }

}
