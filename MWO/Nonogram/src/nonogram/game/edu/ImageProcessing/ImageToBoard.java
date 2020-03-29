package nonogram.game.edu.ImageProcessing;

import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Random;
import javax.imageio.ImageIO;

public class ImageToBoard
{
	private BufferedImage im=null;
    private WritableRaster raster=null;
    private BufferedImage im2=null;
    private WritableRaster raster2=null;
    private int dimension = 0;
    public int board[][] = null;
    private int width = 0;
    private int height = 0;
    private int pixels[] = new int[3];
    private int ton = 0;
    private String fileName = "";
    
    
    public ImageToBoard(String fileName, int d, int ton) throws IOException
    {
    	this.fileName = fileName;
    	this.ton = ton;
        im = ImageIO.read(new File(fileName));
        im2 = im;
        this.dimension  = d;
        raster = im.getRaster();
        raster2 = raster;
        width = raster.getWidth();
        height = raster.getHeight();
        
        createBoard();
    }
    
    public void createBoard()
    {
    	blackAndWhite(ton);
    	
    	board = new int[dimension][dimension];
    	
    	
    	int edge = (int) Math.floor(width/dimension);
    	double area = edge*edge;
    	int x = 0;
    	int y = 0;
    	
    	int sum = 0;
    	try {
			save("out3.jpg");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	//System.out.println(edge+" "+width+ " "+area);
    	for(int i=0;i<width;i++)
        {
       
            for(int j=0;j<height;j++)
            {
     
            	raster.getPixel(i, j, pixels);
                //System.out.println(pixels[0] + " " + pixels[1] + " " + pixels[2] + " " );
               if(pixels[0] == 0)
               {
            	   if((int) Math.floor(i/edge) >= dimension)
            	   {
            		   x = dimension - 1;
            	   }
            	   else
            	   {
            		   x = (int) Math.floor(i/edge);
            	   }
            	   
            	   if((int) Math.floor(j/edge) >= dimension)
            	   {
            		   y = dimension - 1;
            	   }
            	   else
            	   {
            		   y = (int) Math.floor(j/edge);
            	   }
            	   
            	   
            	   board[x][y] += 1;
               }
               
                //raster.setPixel(i, j, pixels);
               
            }
       
       }
    	
    	
    	for(int i=0;i<dimension;i++)
        {
       
            for(int j=0;j<dimension;j++)
            {
     
            	//System.out.print(board[i][j]+ " ");
            }
            //System.out.println();
        }
    	
    	for(int i=0;i<dimension;i++)
        {
       
            for(int j=0;j<dimension;j++)
            {
     
            	if((double) (board[i][j]/area) > 0.25)
            	{
            		board[i][j] = 1;
            		
            	}
            	else
            	{
            		board[i][j] = 0;
            	}
            }
        }
    	
    	for(int i=0;i<dimension;i++)
        {
       
            for(int j=0;j<dimension;j++)
            {
     
            	//System.out.print(board[i][j]+ " ");
            }
            //System.out.println();
        }
    	
    	
    	
    	
    	
		for(int i=0;i<width;i++)
        {
       
            for(int j=0;j<height;j++)
            {
     
            	raster.getPixel(i, j, pixels);
                //System.out.println(pixels[0] + " " + pixels[1] + " " + pixels[2] + " " );
               
            	   if((int) Math.floor(i/edge) >= dimension)
            	   {
            		   x = dimension - 1;
            	   }
            	   else
            	   {
            		   x = (int) Math.floor(i/edge);
            	   }
            	   
            	   if((int) Math.floor(j/edge) >= dimension)
            	   {
            		   y = dimension - 1;
            	   }
            	   else
            	   {
            		   y = (int) Math.floor(j/edge);
            	   }
            	   
            	   
            	  if(board[x][y] == 1)
            	  {
					  pixels[0] = 0;
					  pixels[1] = 0;
					  pixels[2] = 0;
					  raster.setPixel(i, j, pixels);
            	  }
            	  else
            	  {
            		  pixels[0] = 255;
					  pixels[1] = 255;
					  pixels[2] = 255;
					  raster.setPixel(i, j, pixels);
            	  }
               
               
                //raster.setPixel(i, j, pixels);
               
            }
       
       }
		

        try {
			ImageIO.write(im,"jpg",new File("out2.jpg"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        /*if(!checkBoard())
        {
        	ton += 10;
        	fileName = fileName;
            try {
				im = ImageIO.read(new File(fileName));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
            raster = im.getRaster();
        	createBoard();
        }*/
    
    }
    
    public boolean checkBoard()
    {
    	double sum = 0;
    	double all = dimension*dimension;
    	
    	for(int i=0;i<dimension;i++)
        {
       
            for(int j=0;j<dimension;j++)
            {
            	sum += board[i][j];
            }
        }
    	
    	if(sum/all <= 0.6)
    	{
    		return true;
    	}
    	
    	return false;
    }
    
    public void save(String outfile) throws IOException
    {
        ImageIO.write(im,"jpg",new File(outfile));
        //ImageIO.write(im2,"jpg",new File("out3.jpg"));
     }
    
    
    public void greyScale()
    {
        double ww[]=new double[3];
        
        for(int i=0;i<width;i++)
        {
       
            for(int j=0;j<height;j++)
            {
     
                raster.getPixel(i, j, pixels);
               
                ww[0] = 0.299*pixels[0]+0.587*pixels[1]+0.114*pixels[2];
                ww[1] = 0.299*pixels[0]+0.587*pixels[1]+0.114*pixels[2];
                ww[2] = 0.299*pixels[0]+0.587*pixels[1]+0.114*pixels[2];
               
                raster.setPixel(i, j, ww);
               
            }
       
       }
       
       
        }
	
    public void blackAndWhite(int ton)
    {
       boolean better = true;
    	double hsv[];
        double ww[];
        Random r = new Random();
        double min=-(0.15*ton);
        double max=0.15*ton;
        int ton2=0;
        this.greyScale();
        for(int i=0;i<width;i++)
        {

             for(int j=0;j<height;j++)
             {
                  raster.getPixel(i, j, pixels);
                  hsv=rgb2hsv(pixels[0], pixels[1], pixels[2]);
                  
                  if(better){
                  
                      ton2=ton+(int)(min + (int)(Math.random()  * ((max - min) + 1)));
                  
                  }
                  else
                      ton2=ton;
                  if(hsv[2]>ton2)
                  {
                  
                      ww=hsv2rgb(hsv[0], hsv[1], hsv[2]);
                      Arrays.fill(ww, 0);
                  }
                  else
                  {
                  
                      ww=hsv2rgb(hsv[0], hsv[1], hsv[2]);
                      Arrays.fill(ww, 255);
                      
                  }
                  
                   raster.setPixel(i, j, ww);  
              
              
             }

        }

    }
    
    private double[] rgb2hsv(double red, double grn, double blu)
    {
        double hue, sat, val;
        double x, f, i;
        double result[] = new double[3];

        x = Math.min(Math.min(red, grn), blu);
        val = Math.max(Math.max(red, grn), blu);
        if (x == val){
            hue = 0;
            sat = 0;
        }
        else
        {
            f = (red == x) ? grn-blu : ((grn == x) ? blu-red : red-grn);
            i = (red == x) ? 3 : ((grn == x) ? 5 : 1);
            hue = ((i-f/(val-x))*60)%360;
            sat = ((val-x)/val);
        }
        result[0] = hue;
        result[1] = sat;
        result[2] = val;
        return result;
    }
    
    private double[] hsv2rgb(double hue, double sat, double val)
    {
        double red = 0, grn = 0, blu = 0;
        double i, f, p, q, t;
        double result[] = new double[3];
 
        if(val==0)
        {
            red = 0;
            grn = 0;
            blu = 0;
        }
        else
        {
            hue/=60;
            i = Math.floor(hue);
            f = hue-i;
            p = val*(1-sat);
            q = val*(1-(sat*f));
            t = val*(1-(sat*(1-f)));
            if (i==0) {red=val; grn=t; blu=p;}
            else if (i==1) {red=q; grn=val; blu=p;}
            else if (i==2) {red=p; grn=val; blu=t;}
            else if (i==3) {red=p; grn=q; blu=val;}
            else if (i==4) {red=t; grn=p; blu=val;}
            else if (i==5) {red=val; grn=p; blu=q;}
        }
        result[0] = red;
        result[1] = grn;
        result[2] = blu;
        return result;
}

	    

}