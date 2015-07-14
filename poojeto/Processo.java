
package poojeto;
import java.util.*;
import java.io.*;
/**
 *
 * @author nelson
 */
public class Processo{

    private String nome;
    private String pid;
    private String cpu;
    private String mem;
    private String user;
    private int mode;
    private String decisao;

    public Processo(String nome,String pid, String cpu,String mem, String user,int mode){
       this.nome=nome;
        this.pid=pid;
        this.cpu=cpu;
        this.mem=mem;
        this.user=user;
        this.mode=mode;
        this.decisao=null;
    }

    public String getNome(){return nome;}
    public String getPid(){return pid;}
    public String getCpu(){return cpu;}
    public String getMem(){return mem;}
    public String getUser(){return user;}
    public int getMode(){return mode;}
    public String getDecisao(){return decisao;}
    public void setDecisao(String s){this.decisao=s;}
    public boolean equals(Object o){
        if(this == o) return true;
        if((o == null) || (this.getClass() != o.getClass())) return false;
        Processo p = (Processo) o;
        return(this.nome.equals(p.getNome()) &&
        this.pid.equals(p.getPid())); 
    }


}
    

    
    

