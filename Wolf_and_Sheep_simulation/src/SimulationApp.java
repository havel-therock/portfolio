import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;


/**
 * 
 * @author kacper
 * Application shows a simulation of wolf eating sheep on a pasture.
 * If there is no sheep left, application ends action.
 * Wolf - black square
 * Sheep - white square
 * Pasture - green square 
 */


/**
 * 
 * Main class which holds whole simulation
 *
 */
public class SimulationApp{
	
	public static void main(String[] args){		
		SimulationApp launch = new SimulationApp();
		launch.runSimulation();
	}
	
	/**
	 * This turn on GUI
	 */
	public void runSimulation(){
		GUI turn_on = new GUI();
		turn_on.appear();
	}
}

/**
 * 
 * @author kacper
 * simulation 
 */
class Simulation {
	/**
	 * This constructor put randomly sheep in the pasture of given size
	 * @param width of the pasture
	 * @param height of the pasture
	 * @param sheep_number in the pasture
	 */
	public Simulation(int width, int height, int sheep_number){
		GlobalInfo.EWES = new ArrayList<Animal>();
		Sheep first_sheep = new Sheep(GlobalInfo.generator.nextInt(width) * GlobalInfo.ANIMAL_SIZE, GlobalInfo.generator.nextInt(height) * GlobalInfo.ANIMAL_SIZE);
		GlobalInfo.EWES.add(first_sheep);
		for(int i = 1; i < sheep_number; i++){
			Sheep test_object;
			do{
				int position_x = GlobalInfo.generator.nextInt(width) * GlobalInfo.ANIMAL_SIZE;
				int position_y = GlobalInfo.generator.nextInt(height) * GlobalInfo.ANIMAL_SIZE;
				System.out.println("Nowe losowanie");
				test_object = new Sheep(position_x, position_y);
			}while(GlobalInfo.EWES.contains(test_object));
			GlobalInfo.EWES.add(test_object);
			System.out.println("DODANO OBIEKT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		}
		Sheep covered_wolf;
		do{
			int position_x = GlobalInfo.generator.nextInt(width) * GlobalInfo.ANIMAL_SIZE;
			int position_y = GlobalInfo.generator.nextInt(height) * GlobalInfo.ANIMAL_SIZE;
			System.out.println("Nowe losowanie");
			covered_wolf = new Sheep(position_x, position_y);
			
		}while(GlobalInfo.EWES.contains(covered_wolf));
		GlobalInfo.EWES.add(new Wolf(covered_wolf.x, covered_wolf.y));
		System.out.println("Simulation launched");
		GlobalInfo.WIDTH = width * GlobalInfo.ANIMAL_SIZE;
		GlobalInfo.HEIGHT = height * GlobalInfo.ANIMAL_SIZE;
		this.width = GlobalInfo.WIDTH - 1;
		this.height = GlobalInfo.HEIGHT - 1;
		GlobalInfo.pasture = new MyPanel();
		GlobalInfo.pasture.setSize(this.width, this.height);
	}
	
	/**
	 * This method show JFrame with simulation
	 */
	public void show(){
		GlobalInfo.simulation = new JFrame("Simulation");
		GlobalInfo.simulation.getContentPane().add(BorderLayout.CENTER, GlobalInfo.pasture);
		GlobalInfo.simulation.setSize(width, GlobalInfo.HEIGHT_OF_THE_JFRAME_BAR + height);
		GlobalInfo.simulation.setVisible(true);
		GlobalInfo.simulation.setResizable(false);
		this.hunting();
	}
	
	/**
	 * This method moving animals using threads
	 */
	public void hunting(){
		try{
				for(int i = 0; i < GlobalInfo.EWES.size(); i++){
					Thread hunt = new Thread(GlobalInfo.EWES.get(i));
					hunt.start();
				}	
		} catch (NullPointerException ex){
			ex.printStackTrace();
		}
	}
	
	private int width;
	private int height;
	//private MyPanel pasture;
	//private JFrame simulation;
	
	/**
	 * 
	 * @author kacper
	 *Panel which display moves of the sheep and wolf
	 */
	class MyPanel extends JPanel{
		@Override
		protected void paintComponent(Graphics g) {
			g.setColor(Color.GREEN);
			g.fillRect(0, 0, width, height);
			for(int i = 0; i < GlobalInfo.EWES.size() ; i++){
				g.setColor(GlobalInfo.EWES.get(i).getColor());
				g.fillRect(GlobalInfo.EWES.get(i).x , GlobalInfo.EWES.get(i).y, GlobalInfo.ANIMAL_SIZE, GlobalInfo.ANIMAL_SIZE);
			}
		}
	}
}

/**
 * 
 * @author kacper
 * class contains GUI 
 */
class GUI implements ActionListener{
	JFrame mainMenu = new JFrame("MainMenu");
	JButton start = new JButton("Start");
	JLabel size_description = new JLabel("Here you can type, how big a field of simulation will be");
	JLabel width_description = new JLabel("WIDTH: ");
	JLabel height_description = new JLabel("HEIGHT: ");
	JTextField width = new JTextField("10", 3);
	JTextField height = new JTextField("10", 3);
	JLabel sheep_description = new JLabel("Here you can type, how much sheep you want on a pasture");
	JLabel sheep_number_label = new JLabel("SHEEP: ");
	JTextField sheep_number = new JTextField("10", 3);
	JTextArea errors_alert = new JTextArea("Here some messages from application can appear...", 5, 30);
	
	/**
	 * Displays GUI
	 */
	public void appear(){
		mainMenu.setSize(400, 300);
		mainMenu.setResizable(false);
		mainMenu.setLayout(new FlowLayout());
		start.addActionListener(this);
		mainMenu.getContentPane().add(start);
		mainMenu.getContentPane().add(size_description);
		mainMenu.getContentPane().add(width_description);
		mainMenu.getContentPane().add(width);
		mainMenu.getContentPane().add(height_description);
		mainMenu.getContentPane().add(height);
		mainMenu.getContentPane().add(sheep_description);
		mainMenu.getContentPane().add(sheep_number_label);
		mainMenu.getContentPane().add(sheep_number);
		mainMenu.getContentPane().add(errors_alert);
		mainMenu.setVisible(true);
		mainMenu.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	
	/**
	 * Action which is happening after button start is clicked
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		int WIDTH, HEIGHT, SHEEP;
		try {
			WIDTH = Integer.parseInt(width.getText());
			HEIGHT = Integer.parseInt(height.getText());
			SHEEP = Integer.parseInt(sheep_number.getText());
			if(Math.min(Math.min(WIDTH, HEIGHT), SHEEP) < 1){
				throw new WrongData();
			}
			if(SHEEP >= WIDTH*HEIGHT){
				throw new TooManySheep();
			}
			if(WIDTH > 100 || HEIGHT > 70){
				throw new TooBigPasture();
			}
			Simulation go = new Simulation(WIDTH, HEIGHT, SHEEP);
			go.show();
		} catch (NumberFormatException ex) {
			width.setText("");
			height.setText("");
			sheep_number.setText("");
			errors_alert.setText("Wrong data, please give an integer numbers");
		} catch (WrongData ex){
			width.setText("");
			height.setText("");
			sheep_number.setText("");
			errors_alert.setText("Wrong data, please give a positive numbers");  
		} catch (TooManySheep ex){
			width.setText("");
			height.setText("");
			sheep_number.setText("");
			errors_alert.setText("Wrong data, You want toooo much sheep in pasture"); 
		} catch(TooBigPasture ex){
			width.setText("");
			height.setText("");
			sheep_number.setText("");
			errors_alert.setText("Wrong data, You want toooo big pasture"); 
		}
		
	}
}
/**
 * 
 * @author kacper
 * Exception of too many sheep
 */
class TooManySheep extends Exception{}
/**
 * 
 * @author kacper
 * Exception of
 * numbers below 1 and words
 */

class WrongData extends Exception{}
/**
 * 
 * @author kacper
 * exception of too big pasture
 */
class TooBigPasture extends Exception{}

/**
 * 
 * @author kacper
 * Abstract Class Animal extends Rectangle
 */
abstract class Animal extends Rectangle implements Runnable{
	public Animal(int x, int y){
		this.x = x;
		this.y = y;
		this.width = GlobalInfo.ANIMAL_SIZE;
		this.height = GlobalInfo.ANIMAL_SIZE;
	}
	
	
//	protected Boolean live = true;
	
	
	//public void killAnimal(Sheep sheep){
	//	sheep.live = false;
	//}
	
	/**
	 * Field {@code color} holds color of square. 
	 * Wolf - black square.
	 * Sheep - white square.
	 */
	private Color color;
	
	/**
	 * get the color of animal
	 */
	public Color getColor(){
		return this.color;
	}
	
	/**
	 * This method set new color of animal
	 * @param color new color of animal
	 */
	public void setColor(Color color){
		this.color = color;
	}
	
	/**
	 * This abstract method moves an animal in to a new position.
	 */
	 abstract public void changePosition();
}

class Wolf extends Animal{
	
	/**
	 * This method take care of proper rest of the Wolf
	 */
	public synchronized void restChange(){
		this.rest--;
	}
	
	private int rest = 0;
	
	public Wolf(int x, int y) {
		super(x, y);
		this.setColor(Color.BLACK);
	}
	
	/**
	 * here sleeping and working of wolf happens
	 */
	@Override
	public void run() {
		while(GlobalInfo.EWES.size() > 1){
			if(this.rest <= 0){
				try {
					System.out.println("wilk zaczyna spac");
					double randomization_interval = ((double)GlobalInfo.generator.nextInt(10) + 5)/10;
					Thread.sleep((long)(GlobalInfo.K *randomization_interval));
					System.out.println("wilk skonczyl spac !!! Do ROBOTYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY");
					this.changePosition();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}else{
				restChange();
			}
		}
		JLabel end = new JLabel("End of simulation");
		GlobalInfo.pasture.add(end);
		GlobalInfo.simulation.dispose(); // tutaj zamyka ekraaaaaaaaaaaan
	}
	
	/**
	 * This method moves Wolf actually
	 */
	@Override
	public synchronized void changePosition() {
		int min_distance = Math.max(GlobalInfo.HEIGHT, GlobalInfo.WIDTH);
		int wolfX = GlobalInfo.EWES.get(GlobalInfo.EWES.size() - 1).x;
		int wolfY = GlobalInfo.EWES.get(GlobalInfo.EWES.size() - 1).y;
		for(int i = 0; i < GlobalInfo.EWES.size() - 1; i++){
		//	System.out.println("minimalny dystyans %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% wilka od owiec " + min_distance);
			int if_min = Math.max(Math.abs(wolfX - GlobalInfo.EWES.get(i).x), Math.abs(wolfY- GlobalInfo.EWES.get(i).y));
			min_distance = Math.min(min_distance, if_min);
		}
		ArrayList<Point> nearest_sheep = new ArrayList<Point>();
		for(int i = 0; i < GlobalInfo.EWES.size() - 1; i++){
			if(Math.max(Math.abs(wolfX - GlobalInfo.EWES.get(i).x), Math.abs(wolfY- GlobalInfo.EWES.get(i).y)) == min_distance){
				Point point = new Point(GlobalInfo.EWES.get(i).x, GlobalInfo.EWES.get(i).y);
				nearest_sheep.add(point);
			}
		}
		if(min_distance == GlobalInfo.ANIMAL_SIZE){
			int  new_position = GlobalInfo.generator.nextInt(nearest_sheep.size());
			Sheep killed = new Sheep(nearest_sheep.get(new_position).x, nearest_sheep.get(new_position).y);
			GlobalInfo.EWES.remove(killed);
			this.setLocation(nearest_sheep.get(new_position).x, nearest_sheep.get(new_position).y);
			this.rest = 5;
		}else{
			ArrayList<Point> possible_movement = new ArrayList<Point>(); 
			Point new_pos = new Point(this.x - GlobalInfo.ANIMAL_SIZE, this.y);
			possible_movement.add(new_pos);
			new_pos = new Point(this.x - GlobalInfo.ANIMAL_SIZE, this.y + GlobalInfo.ANIMAL_SIZE);
			possible_movement.add(new_pos);
			new_pos = new Point(this.x, this.y + GlobalInfo.ANIMAL_SIZE);
			possible_movement.add(new_pos);
			new_pos = new Point(this.x + GlobalInfo.ANIMAL_SIZE, this.y + GlobalInfo.ANIMAL_SIZE);
			possible_movement.add(new_pos);
			new_pos = new Point(this.x + GlobalInfo.ANIMAL_SIZE, this.y);
			possible_movement.add(new_pos);
			new_pos = new Point(this.x + GlobalInfo.ANIMAL_SIZE, this.y - GlobalInfo.ANIMAL_SIZE);
			possible_movement.add(new_pos);
		    new_pos = new Point(this.x, this.y - GlobalInfo.ANIMAL_SIZE);
			possible_movement.add(new_pos);
			new_pos = new Point(this.x - GlobalInfo.ANIMAL_SIZE, this.y - GlobalInfo.ANIMAL_SIZE);
			possible_movement.add(new_pos);
			for(int i = 0; i < possible_movement.size(); i++){
				boolean good_move = false;
				for(int j  = 0; j < nearest_sheep.size(); j++){
					int disX = Math.abs(nearest_sheep.get(j).x - possible_movement.get(i).x);
					int disY = Math.abs(nearest_sheep.get(j).y - possible_movement.get(i).y);
					if(min_distance > Math.max(disY, disX)){
						good_move = true;
					}
				}
				if(good_move == false){
					possible_movement.remove(possible_movement.get(i));
					i--;
				}
			}
			for(int i = 0; i < possible_movement.size(); i++){
				if(possible_movement.get(i).x < 0 || possible_movement.get(i).x > GlobalInfo.WIDTH - GlobalInfo.ANIMAL_SIZE || possible_movement.get(i).y < 0 || possible_movement.get(i).y > GlobalInfo.HEIGHT - GlobalInfo.ANIMAL_SIZE){
					possible_movement.remove(possible_movement.get(i));
					i--;
				//	System.out.println("USUNIETA ruch wychodzacy za ramke @@@@@@@@@@@@@@@@@@@@@@@@@");
				}
			}
			int  new_position = GlobalInfo.generator.nextInt(possible_movement.size());
			this.setLocation(possible_movement.get(new_position).x, possible_movement.get(new_position).y); 
		}
		
	}

}

class Sheep extends Animal{
	public Sheep(int x, int y) {
		super(x, y);
		this.setColor(Color.WHITE);
	}

	/**
	 * This method sleeps and wakes up sheep
	 */
	@Override
	public void run() {
		while(GlobalInfo.EWES.size() > 1){
			try {
				System.out.println("Nowy owiec spi");
				double randomization_interval = ((double)GlobalInfo.generator.nextInt(10) + 5)/10;
				Thread.sleep((long)(GlobalInfo.K *randomization_interval)); 
				System.out.println("Owiec skonczyl spac !!! Do ROBOTY");
				this.changePosition();
				GlobalInfo.simulation.repaint();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * This method moves sheep
	 * 
	 */
	@Override
	public synchronized void changePosition() {
		ArrayList<Point> possible_movement = new ArrayList<Point>(); 
		Point new_pos = new Point(this.x - GlobalInfo.ANIMAL_SIZE, this.y);
		possible_movement.add(new_pos);
		new_pos = new Point(this.x - GlobalInfo.ANIMAL_SIZE, this.y + GlobalInfo.ANIMAL_SIZE);
		possible_movement.add(new_pos);
		new_pos = new Point(this.x, this.y + GlobalInfo.ANIMAL_SIZE);
		possible_movement.add(new_pos);
		new_pos = new Point(this.x + GlobalInfo.ANIMAL_SIZE, this.y + GlobalInfo.ANIMAL_SIZE);
		possible_movement.add(new_pos);
		new_pos = new Point(this.x + GlobalInfo.ANIMAL_SIZE, this.y);
		possible_movement.add(new_pos);
		new_pos = new Point(this.x + GlobalInfo.ANIMAL_SIZE, this.y - GlobalInfo.ANIMAL_SIZE);
		possible_movement.add(new_pos);
	    new_pos = new Point(this.x, this.y - GlobalInfo.ANIMAL_SIZE);
		possible_movement.add(new_pos);
		new_pos = new Point(this.x - GlobalInfo.ANIMAL_SIZE, this.y - GlobalInfo.ANIMAL_SIZE);
		possible_movement.add(new_pos);
		//System.out.println("Size of points ************************************" + possible_movement.size());
		
	/*	
		if(possible_movement.size() > 0){
			for(int i = 0; i < possible_movement.size(); i++){
				if(GlobalInfo.pasture.contains(possible_movement.get(i)) == false){
					possible_movement.remove(possible_movement.get(i));
					i--;
					System.out.println("Size of points %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" + possible_movement.size());
				}
			}
		}
		*/
		// to ponizej dziala dobrze 
		for(int i = 0; i < possible_movement.size(); i++){
			if(possible_movement.get(i).x < 0 || possible_movement.get(i).x > GlobalInfo.WIDTH - GlobalInfo.ANIMAL_SIZE || possible_movement.get(i).y < 0 || possible_movement.get(i).y > GlobalInfo.HEIGHT - GlobalInfo.ANIMAL_SIZE){
				possible_movement.remove(possible_movement.get(i));
				i--;
			//	System.out.println("USUNIETA ruch wychodzacy za ramke @@@@@@@@@@@@@@@@@@@@@@@@@");
			}
		}
		
		for(int i = 0; i < possible_movement.size(); i++){
			if(GlobalInfo.EWES.contains(new Sheep(possible_movement.get(i).x, possible_movement.get(i).y))){
				possible_movement.remove(possible_movement.get(i));
				i--;
			}
		}
		/*
		for(int i = 0; i < GlobalInfo.EWES.size(); i++){
			int distanceX = Math.abs(this.x - GlobalInfo.EWES.get(i).x);
			int distanceY = Math.abs(this.y - GlobalInfo.EWES.get(i).y);
			if(distanceX + distanceY <= 2 && Math.abs(distanceX * distanceY) == 1){
				Point remove_point = new Point (GlobalInfo.EWES.get(i).x, GlobalInfo.EWES.get(i).y);
				possible_movement.remove(remove_point);
				i--;
				System.out.println("Size of points ************************************" + possible_movement.size());
			}
		}
				/*else
				if(GlobalInfo.EWES.contains(possible_movement.get(i)))
					possible_movement.remove(possible_movement.get(i));	
		} */
		if(possible_movement.size() > 0){
			int WolfX = GlobalInfo.EWES.get(GlobalInfo.EWES.size() - 1).x;
			int WolfY = GlobalInfo.EWES.get(GlobalInfo.EWES.size() - 1).y;
			int distance = Math.max(Math.abs(possible_movement.get(0).x - WolfX), Math.abs(possible_movement.get(0).y - WolfY));
			//int distanceY = Math.abs(possible_movement.get(0).y - WolfY);
			for(int i = 1; i < possible_movement.size(); i++){
				distance = Math.max(distance, Math.max(Math.abs(possible_movement.get(i).x - WolfX), Math.abs(possible_movement.get(i).y - WolfY)));
				}
			//if(distance != 0){
				for(int i = 0; i < possible_movement.size(); i++){
					if(Math.max(Math.abs(possible_movement.get(i).x - WolfX), Math.abs(possible_movement.get(i).y - WolfY)) < distance){
						possible_movement.remove(possible_movement.get(i));
						i--;
					//	System.out.println("Size of points @@@@@@@@@@@@@@@@@@@@@@@@@@@@@" + possible_movement.size());
					}
				}
	
				int  new_position = GlobalInfo.generator.nextInt(possible_movement.size());
				this.setLocation(possible_movement.get(new_position).x, possible_movement.get(new_position).y);  
				System.out.println("New X: " + this.x);
				System.out.println("New Y: " + this.y);
			//}
		}
	}	
}

/**
 * 
 * @author kacper
 * class which handle most important info
 * which need to be shared 
 */
class GlobalInfo {
	final static long K = 500; // 500 dzial ok 
	static Random generator = new Random();
	final static int HEIGHT_OF_THE_JFRAME_BAR = 22;
	final static int ANIMAL_SIZE = 10; 
	static ArrayList <Animal> EWES;
    static int WIDTH;
	static int HEIGHT;
	static JFrame simulation;
	static JPanel pasture;
}