/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


package poojeto;
import java.util.*;
import java.io.*;
import java.util.concurrent.*;
import java.nio.charset.*;
/**
 *
 * @author nelson
 */
public class Poojeto {
    /**
     * @param args the command line arguments
     */
    private class PopupThread extends Thread{
        String s;
        ConcurrentHashMap <String,Processo> lista;
        Processo p;

        public PopupThread(String x, ConcurrentHashMap<String,Processo> lista,Processo p){
            s=x;
            this.lista=lista;
            this.p=p;
        }
        public void run(){
            popup(s,lista,p);
        }
    }

    public native void dupc(String s);
    
    public static void main(String[] args) {
        try{
            Poojeto a = new Poojeto();
            a.run();
        }catch (Exception e){;}

    }

    public void run() throws Exception{
        String str;
        String[] token=new String[6];
        StringTokenizer del;
        ConcurrentHashMap<String, Processo> mapa = new ConcurrentHashMap<String, Processo>(); 
        Processo p;
        PopupThread a;
        int i;

        BufferedReader in;
        InputStream fin;
        InputStreamReader isr; 

        File f;
        try{
            str = identificar();
            ProcessBuilder pb = new ProcessBuilder("bash","-c","mkfifo "+str+"toM.txt");
            pb.start();
            
            Thread.sleep(1000);
            
            fin=new FileInputStream(str+"toM.txt");
            isr=new InputStreamReader(fin, Charset.forName("UTF-8"));
            in=new BufferedReader(isr);
            
            pb = new ProcessBuilder("bash","-c","mkfifo "+"Mto"+str+".txt");
            pb.start();
            
            Thread.sleep(1000);    
            f= new File("Mto"+str+".txt");
            System.setOut(new PrintStream(new FileOutputStream(f)));
            while(true) {
                while ((str=in.readLine()) != null && str.length()>0 ){
                    del= new StringTokenizer(str,"$");
                    for(i=0;i<6 && del.hasMoreTokens();i++){
                        token[i]=del.nextToken();
                        }
                    if(i==6){
                        i=Integer.parseInt(token[5]);
                        p = new Processo(token[0],token[1],token[2],token[3],token[4],i);
                        if (!mapa.containsValue(p)){
                            mapa.put(p.getPid(),p);
                            a = new PopupThread(str,mapa,p);
                            a.run();
                            }
                        else {
                            if(p.getDecisao()!=null){
                                System.out.println(p.getDecisao());
                                }
                            }
                        str=null;
                        }
                    }
                    
                }   
            }catch(IOException e){System.out.println(e);}        
        }


        private String identificar()throws Exception{
            String str;
            int r=0;
            char[] buf = new char[500];
            ProcessBuilder pb = new ProcessBuilder("whoami");
            File dummy = new File("dummy.txt");
            FileReader fileread;
            FileWriter filewrite;
            pb.redirectOutput(dummy);
            pb.start();
            fileread = new FileReader(dummy);
            r=fileread.read(buf,0,500);
            buf[r-1]='\0';
            str= new String(buf,0,r-1);
            System.setOut(new PrintStream(new FileOutputStream(new File("id.txt"))));
            System.out.println("id$"+str+"\n");

            return str;
        }

       public static void  popup(String str,ConcurrentHashMap<String,Processo> lista,Processo processo){
        Popup p;
        StringTokenizer del= new StringTokenizer(str,"$");
        javax.swing.JFrame f =new javax.swing.JFrame();
        p = new Popup(f, true,processo,lista);
        java.awt.EventQueue.invokeLater(p);
        }

}
    

    
    

