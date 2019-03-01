import java.util.*;
import java.io.Writer;
import java.io.FileWriter;
import java.io.File;
import java.io.IOException;
import java.lang.Math;

public class generator{
	public static void main(String args[]){
		Writer write=null;
		String figure=args[0];
		StringBuilder sb=new StringBuilder();
		File file=null; FileWriter writer=null;
		double x=0.0,y=0.0,z=0.0,radius=0.0,radius2=0.0,slices=0.0,stacks=0.0,height=0.0,alfa=0.0,beta=0.0,varAlfa=0.0,varBeta=0.0;
		switch(figure){
			case "plane":
				try{
					x=(Double.parseDouble(args[1]))/2.0;
				}catch(NumberFormatException e){
					System.out.println("Invalid Number");
				}
				sb.append(x+" 0 "+x+"\n");
				sb.append(x+" 0 -"+x+"\n");
				sb.append("-"+x+" 0 -"+x+"\n");
				sb.append("-"+x+" 0 -"+x+"\n");
				sb.append("-"+x+" 0 "+x+"\n");
				sb.append(x+" 0 "+x+"\n");
				file=new File(args[2]);
				try{
					file.delete();
					file.createNewFile();
					writer=new FileWriter(file);
					writer.write(sb.toString());
					writer.close();
				}catch(IOException e){
					System.out.println("Error creating file");
				};
				break;	
			case "box":
				if(args.length==4){
					try{
						x=(Double.parseDouble(args[1]))/2.0;
						y=(Double.parseDouble(args[2]))/2.0;
						z=(Double.parseDouble(args[3]))/2.0;
					}catch(NumberFormatException e){
						System.out.println("Invalid Number");
					}
					sb.append(x+" "+y+" "+z+"\n");
					sb.append(x+" "+y+" -"+z+"\n");
					sb.append("-"+x+" "+y+" -"+z+"\n");
					sb.append("-"+x+" "+y+" -"+z+"\n");
					sb.append("-"+x+" "+y+" "+z+"\n");
					sb.append(x+" "+y+" "+z+"\n");
					sb.append(x+" -"+y+" "+z+"\n");
					sb.append("-"+x+" -"+y+" "+z+"\n");
					sb.append("-"+x+" -"+y+" -"+z+"\n");
					sb.append("-"+x+" -"+y+" -"+z+"\n");
					sb.append(x+" -"+y+" -"+z+"\n");
					sb.append(x+" -"+y+" "+z+"\n");
					sb.append("-"+x+" -"+y+" "+z+"\n");
					sb.append("-"+x+" "+y+" "+z+"\n");
					sb.append("-"+x+" -"+y+" -"+z+"\n");
					sb.append("-"+x+" -"+y+" -"+z+"\n");
					sb.append("-"+x+" "+y+" "+z+"\n");
					sb.append("-"+x+" "+y+" -"+z+"\n");
					sb.append(x+" -"+y+" -"+z+"\n");
					sb.append(x+" "+y+" "+z+"\n");
					sb.append(x+" -"+y+" "+z+"\n");
					sb.append(x+" -"+y+" -"+z+"\n");
					sb.append(x+" "+y+" -"+z+"\n");
					sb.append(x+" "+y+" "+z+"\n");
					sb.append(x+" -"+y+" "+z+"\n");
					sb.append(" -"+x+" "+y+" "+z+"\n");
					sb.append(" -"+x+" -"+y+" "+z+"\n");
					sb.append(x+" -"+y+" "+z+"\n");
					sb.append(x+" "+y+" "+z+"\n");
					sb.append(" -"+x+" "+y+" "+z+"\n");
					sb.append(x+" -"+y+" -"+z+"\n");
					sb.append(" -"+x+" "+y+" -"+z+"\n");
					sb.append(x+" "+y+" -"+z+"\n");
					sb.append(x+" -"+y+" -"+z+"\n");
					sb.append(" -"+x+" -"+y+" -"+z+"\n");
					sb.append(" -"+x+" "+y+" -"+z+"\n");
					file=new File(args[4]);
					try{
						file.delete();
						file.createNewFile();
						writer=new FileWriter(file);
						writer.write(sb.toString());
						writer.close();
					}catch(IOException e){
						System.out.println("Error creating file");
					};
				}else{
					Double division=0.0;
					try{
						x=(Double.parseDouble(args[1]));
						y=(Double.parseDouble(args[2]));
						z=(Double.parseDouble(args[3]));
						 division=(Double.parseDouble(args[4]));
					}catch(NumberFormatException e){
						System.out.println("Invalid Number");
					}
					Double varX=x/division, varY=y/division, varZ=z/division;
					Double tmpx=0.0, tmpy=0.0, tmpz=0.0;
					for(Double auxY=0.0;auxY<=y;auxY+=varY)
						for(Double auxX=0.0;auxX<=x;auxX+=varX)
							for(Double auxZ=0.0;auxZ<=z;auxZ+=varZ){
								tmpx=(auxX+varX);
								tmpy=(auxY+varY);
								tmpz=(auxZ+varZ);
								sb.append(tmpx+" "+tmpy+" "+tmpz+"\n");
								sb.append(tmpx+" "+tmpy+" "+auxZ+"\n");
								sb.append(auxX+" "+tmpy+" "+auxZ+"\n");
								sb.append(auxX+" "+tmpy+" "+auxZ+"\n");
								sb.append(auxX+" "+tmpy+" "+tmpz+"\n");
								sb.append(tmpx+" "+tmpy+" "+tmpz+"\n");
								sb.append(tmpx+" "+auxY+" "+tmpz+"\n");
								sb.append(auxX+" "+auxY+" "+tmpz+"\n");
								sb.append(auxX+" "+auxY+" "+auxZ+"\n");
								sb.append(auxX+" "+auxY+" "+auxZ+"\n");
								sb.append(tmpx+" "+auxY+" "+auxZ+"\n");
								sb.append(tmpx+" "+auxY+" "+tmpz+"\n");
								sb.append(auxX+" "+auxY+" "+tmpz+"\n");
								sb.append(auxX+" "+tmpy+" "+tmpz+"\n");
								sb.append(auxX+" "+auxY+" "+auxZ+"\n");
								sb.append(auxX+" "+auxY+" "+auxZ+"\n");
								sb.append(auxX+" "+tmpy+" "+tmpz+"\n");
								sb.append(auxX+" "+tmpy+" "+auxZ+"\n");
								sb.append(tmpx+" "+auxY+" "+auxZ+"\n");
								sb.append(tmpx+" "+tmpy+" "+tmpz+"\n");
								sb.append(tmpx+" "+auxY+" "+tmpz+"\n");
								sb.append(tmpx+" "+auxY+" "+auxZ+"\n");
								sb.append(tmpx+" "+tmpy+" "+auxZ+"\n");
								sb.append(tmpx+" "+tmpy+" "+tmpz+"\n");
								sb.append(tmpx+" "+auxY+" "+tmpz+"\n");
								sb.append(auxX+" "+tmpy+" "+tmpz+"\n");
								sb.append(auxX+" "+auxY+" "+tmpz+"\n");
								sb.append(tmpx+" "+auxY+" "+tmpz+"\n");
								sb.append(tmpx+" "+tmpy+" "+tmpz+"\n");
								sb.append(auxX+" "+tmpy+" "+tmpz+"\n");
								sb.append(tmpx+" "+auxY+" "+auxZ+"\n");
								sb.append(auxX+" "+tmpy+" "+auxZ+"\n");
								sb.append(tmpx+" "+tmpy+" "+auxZ+"\n");
								sb.append(tmpx+" "+auxY+" "+auxZ+"\n");
								sb.append(auxX+" "+auxY+" "+auxZ+"\n");
								sb.append(auxX+" "+tmpy+" "+auxZ+"\n");
							}
					file=new File(args[5]);
					try{
						file.delete();
						file.createNewFile();
						writer=new FileWriter(file);
						writer.write(sb.toString());
						writer.close();
					}catch(IOException e){
						System.out.println("Error creating file");
					};
				}
				break;
			case "sphere":
				try{
					radius=Double.parseDouble(args[1]);
					slices=Double.parseDouble(args[2]);
					stacks=Double.parseDouble(args[3]);
				}catch(NumberFormatException e){
					System.out.println("Invalid Number");
				}
				alfa=0.0; beta=-Math.PI/2; varAlfa=2*Math.PI/slices; varBeta=Math.PI/stacks;
				for(double st=0.0;st<=stacks;st++){
					beta=-Math.PI/2 + varBeta*st;
					for(double sl=0;sl<=slices;sl++){
						alfa=varAlfa*sl;
						sb.append(radius*Math.cos(beta)*Math.sin(alfa)+" "+radius*Math.sin(beta)+" "+radius*Math.cos(beta)*Math.cos(alfa)+"\n");
						sb.append(radius*Math.cos(beta+varBeta)*Math.sin(alfa+varAlfa)+" "+radius*Math.sin(beta+varBeta)+" "+radius*Math.cos(beta+varBeta)*Math.cos(alfa+varAlfa)+"\n");
						sb.append(radius*Math.cos(beta+varBeta)*Math.sin(alfa)+" "+radius*Math.sin(beta+varBeta)+" "+radius*Math.cos(beta+varBeta)*Math.cos(alfa)+"\n");
						sb.append(radius*Math.cos(beta)*Math.sin(alfa)+" "+radius*Math.sin(beta)+" "+radius*Math.cos(beta)*Math.cos(alfa)+"\n");
						sb.append(radius*Math.cos(beta)*Math.sin(alfa+varAlfa)+" "+radius*Math.sin(beta)+" "+radius*Math.cos(beta)*Math.cos(alfa+varAlfa)+"\n");
						sb.append(radius*Math.cos(beta+varBeta)*Math.sin(alfa+varAlfa)+" "+radius*Math.sin(beta+varBeta)+" "+radius*Math.cos(beta+varBeta)*Math.cos(alfa+varAlfa)+"\n");
					}
				}
				file=new File(args[4]);
  				try{
					file.delete();
					file.createNewFile();
  					writer=new FileWriter(file);
					writer.write(sb.toString());
					writer.close();
				}catch(IOException e){};
				break;
			case "cone":
				try{
					radius=Double.parseDouble(args[1]);
					height=Double.parseDouble(args[2]);
					slices=Double.parseDouble(args[3]);
					stacks=Double.parseDouble(args[4]);
				}catch(NumberFormatException e){
					System.out.println("Invalid Number");
				}
				alfa=0.0;
				radius2=radius;
				double cheight=0.0;
				double varHeight=height/stacks;
				double varRadius=radius/stacks;
				double varAngle=2*Math.PI/slices;
				for(double ch=0;(ch<height&&radius2>0);ch+=varHeight){
					for(double ca=0;ca<=2*Math.PI;ca+=varAngle){
						alfa+=ca*varAngle;
						sb.append((radius2-varRadius)*Math.sin(ca)+" "+(cheight+varHeight)+" "+(radius2-varRadius)*Math.cos(ca)+"\n");
						sb.append(radius2*Math.sin(ca)+" "+(cheight)+" "+radius2*Math.cos(ca)+"\n");
						sb.append((radius2-varRadius)*Math.sin(ca+varAngle)+" "+(cheight+varHeight)+" "+(radius2-varRadius)*Math.cos(ca+varAngle)+"\n");
						sb.append(radius2*Math.sin(ca+varAngle)+" "+(cheight)+" "+radius2*Math.cos(ca+varAngle)+"\n");
						sb.append((radius2-varRadius)*Math.sin(ca+varAngle)+" "+(cheight+varHeight)+" "+(radius2-varRadius)*Math.cos(ca+varAngle)+"\n");
						sb.append(radius2*Math.sin(ca)+" "+(cheight)+" "+radius2*Math.cos(ca)+"\n");
					}
					cheight+=varHeight;
					radius2-=varRadius;
					alfa=0.0;
				}
				double baseRad=radius;
				double baseheight=0.0;
				for(double baseAng=0;baseAng<2*Math.PI;baseAng+=varAngle){
					sb.append("0.0 0.0 0.0\n");
					sb.append(baseRad*Math.sin(baseAng+varAngle)+" "+baseheight+" "+baseRad*Math.cos(baseAng+varAngle)+"\n");
					sb.append(baseRad*Math.sin(baseAng)+" "+baseheight+" "+baseRad*Math.cos(baseAng)+"\n");
				}
				file=new File(args[5]);
  				try{
  					file.delete();
  					file.createNewFile();
  					writer=new FileWriter(file);
					writer.write(sb.toString());
					writer.close();
				}catch(IOException e){
					System.out.println("Error creating file");
				};
				break;
			case "ring":
				try{
					radius=Double.parseDouble(args[1]);
					radius2=Double.parseDouble(args[2]);
					slices=Double.parseDouble(args[3]);
				}catch(NumberFormatException e){
					System.out.println("Invalid Number");
				}
				varAlfa=(2*Math.PI)/slices;
				for(alfa=0.0;alfa<2*Math.PI;alfa+=varAlfa){
					beta=alfa+varAlfa;
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");
					sb.append(radius*Math.cos(alfa)+" "+0.0+" "+radius*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(beta)+" "+0.0+" "+radius2*Math.sin(beta)+"\n");
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");
					sb.append(radius2*Math.cos(beta)+" "+0.0+" "+radius2*Math.sin(beta)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius*Math.cos(alfa)+" "+0.0+" "+radius*Math.sin(alfa)+"\n");
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");					
				}
				file=new File(args[4]);
  				try{
  					file.delete();
  					file.createNewFile();
  					writer=new FileWriter(file);
					writer.write(sb.toString());
					writer.close();
				}catch(IOException e){
					System.out.println("Error creating file");
				}
				break;
			case "belt":
				try{
					radius=Double.parseDouble(args[1]);
					radius2=Double.parseDouble(args[2]);
					slices=Double.parseDouble(args[3]);
				}catch(NumberFormatException e){
					System.out.println("Invalid Number");
				}
				varAlfa=(2*Math.PI)/slices;
				for(alfa=0.0;alfa<2*Math.PI;alfa+=varAlfa){
					beta=alfa+varAlfa;
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");
					sb.append(radius*Math.cos(alfa)+" "+0.0+" "+radius*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(beta)+" "+0.0+" "+radius2*Math.sin(beta)+"\n");
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");
					sb.append(radius2*Math.cos(beta)+" "+0.0+" "+radius2*Math.sin(beta)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius2*Math.cos(alfa)+" "+0.0+" "+radius2*Math.sin(alfa)+"\n");
					sb.append(radius*Math.cos(alfa)+" "+0.0+" "+radius*Math.sin(alfa)+"\n");
					sb.append(radius*Math.cos(beta)+" "+0.0+" "+radius*Math.sin(beta)+"\n");					
				}
				file=new File(args[4]);
  				try{
  					file.delete();
  					file.createNewFile();
  					writer=new FileWriter(file);
					writer.write(sb.toString());
					writer.close();
				}catch(IOException e){
					System.out.println("Error creating file");
				}
				break;
			default:
				System.out.println("Figure doesn't exist");
		}
	}
}