#ifndef PAGINACION_MEMORIA_H
#define PAGINACION_MEMORIA_H
#include <iostream>
#include <map>
#include <cmath>
#include "proceso.h"
#include <Windows.h>
#define BLUE            1
#define RED             4
#define DEFAULT         7
using namespace std;
void imprimir_tabla(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
class Memoria {
private:
    int cant;
    int bloqueados;
    bool llena;
    int tamanio = 200;
    int disponible;
    int ocupado;
    int ps = 0;
    int frames;
    int ejecucion=0;
    map<int, proceso>memoria;
public:
    Memoria() {
        disponible = tamanio;
        llena=false;
        ocupado = 0;
        cant=0;
        frames=tamanio/5;//40
        for (int i = 0; i < tamanio / 5; i++) {
            proceso pr;
            memoria[i] = pr;
        }
    }
    int get_disponible() {
        return disponible;
    }
    int get_ocupado(){
        return ocupado;
    }
    int size() {
        return memoria.size();
    }
    int get_frames(){
        return frames;
    }
    bool set_proceso(proceso& pr) {
        if(llena) return false;
        if ((frames -1-(pr.get_peso())/5) <=0  ) {
            llena =true;
            return false;
        }
        cant++;
        vector<int>pos;
        disponible -= pr.get_peso();
        ocupado+=pr.get_peso();
        int cant=ceil(pr.get_peso()/5);
        if(pr.get_peso()%5>0){
            cant++;
        }
        for (int i = 0; i < cant; i++) {
            memoria[ps] = pr;
            frames--;
            pos.push_back(ps);
            ps++;

        }
        for(int p : pos){
            memoria[p].set_posicion(pos);
        }
        return true;
    }
    proceso get_proceso(int ps) {
        return memoria[ps];
    }
    bool get_llena(){
        return llena;
    }
    void modificar_terminado(int i){
        memoria[i].set_terminado(true);
    }
    void aumentar_bloqueados(){
        bloqueados++;
    }
    int get_bloqueados(){
        return bloqueados;
    }
    int primer_bloqueado(){
        int primero=0;
        for(int i=0;i<memoria.size();i++){
            if(memoria[i].get_t_bloqueado()<memoria[primero].get_t_bloqueado()){
                primero=i;
            }
        }
        return primero;
    }
    int siguiente(int x){
        for(int i=x;i<memoria.size();i++){
            if(memoria[i].get_id()!=-1 && memoria[i].get_id()!= memoria[ejecucion].get_id() && !memoria[i].get_bloqueado())
                return i;
        }
        for(int i=0;i<x;i++){
            if(memoria[i].get_id()!=-1 && memoria[i].get_id()!= memoria[ejecucion].get_id() && !memoria[i].get_bloqueado())
                return i;
        }
        return x;

    }
    int get_cantidad(){
        return cant;
    }
    void set_ejecucion(int x){
        ejecucion=x;
    }
    int get_ejecucion(){
        return ejecucion;
    }
    void set_llena(bool x){
        llena=x;
    }
    void set_buscado(proceso pr){
        disponible -= pr.get_peso();
        ocupado+=pr.get_peso();
        cant++;
        vector<int> ps = pr.get_vector();
        for(int i=0;i<ps.size();i++){
            memoria[ps[i]]=pr;
            frames--;

        }

    }
    void buscar(proceso& pr){
        vector<int>posiciones;
        int ocupa=ceil(pr.get_peso()/5);
        if(pr.get_peso()%5>0){
            ocupa++;
        }

        for(int i=ejecucion;i<tamanio/5;i++){
            imprimir_tabla(0,30);
            if (memoria[i].get_id()==-1){
                posiciones.push_back(i);
                ocupa--;
            }

            if(ocupa==0)
                break;
        }
        for(int i=0;i<ejecucion;i++){
            if(ocupa==0){
                break;
            }
            if (memoria[i].get_id()==-1){
                posiciones.push_back(i);
                ocupa--;
            }
        }

        pr.set_posicion(posiciones);
        set_buscado(pr);


    }
    void set_quantum(int quantum){
        vector<int>t_pos=memoria[ejecucion].get_vector();
        for(int x : t_pos){
            memoria[x].set_quantum(quantum);
        }
    }
    void fin_quantum(int x, int quantum){
        memoria[x].set_quantum(quantum);
        if(ocupado>0){
            int next=siguiente(ejecucion);
            ejecucion=next;
        }

    }
    void terminado(int x){
        vector<int>t_pos=memoria[x].get_vector();
        proceso p;
        p.set_id(-1);
        cant--;
        llena =false;
        disponible+=memoria[x].get_peso();
        ocupado-=memoria[x].get_peso();
        int next=t_pos[t_pos.size()-1];
        for(int t_po : t_pos){
            memoria[t_po]=p;
            frames++;

        }
        if(ocupado>0){
            next=siguiente(next);
            ejecucion=next;
        }

    }
    void set_tiempos(int& segundos){
        memoria[ejecucion].set_finalizado(segundos);
        memoria[ejecucion].set_tiempos(segundos);
    }
    void marcar_bloqueado(bool x){
        vector<int>t_pos=memoria[ejecucion].get_vector();
        for(int i=0;i<t_pos.size();i++){
            memoria[t_pos[i]].marcar_bloqueado(x);
        }
    }
    void fin_bloqueado(int i){
        if(memoria[i].get_t_bloqueado()==0){
            vector<int>t_ps=memoria[i].get_vector();
            bloqueados--;

            for(int x: t_ps){
                memoria[x].set_bloqueado();
                memoria[x].marcar_bloqueado(false);
            }
        }
    }
    void restar_bloqueados(int i){
        if(memoria[i].get_bloqueado()){
            memoria[i].restar_bloqueado();

        }

    }
    bool anterior(){

        for(int i=0;i<tamanio/5;i++){
            if(memoria[i].get_id()==memoria[ejecucion].get_id()){
                if(memoria[i].get_transcurrido()>memoria[ejecucion].get_transcurrido()){
                    return true;
                }
            }
        }
        return false;
    }
    void set_respuesta(int segundos){
        memoria[ejecucion].set_respuesta(segundos);
    }
    bool restar(){
        if (anterior()){
            siguiente(ejecucion);
            return false;
        }
        vector<int>t_pos=memoria[ejecucion].get_vector();
        memoria[ejecucion].aumentar_transcurrido();
        if(memoria[ejecucion].get_tme()== memoria[ejecucion].get_transcurrido()){
            return true;
        }
        for(int i=0;i<t_pos.size();i++){
            memoria[t_pos[i]].restar_quantum();

        }
        return false;
    }
    friend ostream& operator <<(ostream& salida, Memoria& memoria) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int cont_espacio=0,aux=0,auxx=0,ultimox,ultimoy;
        for (int i = 0; i < memoria.size(); i++) {
            if(cont_espacio==5) {
                salida<<endl;
                cont_espacio=0;
                aux++;
                auxx=0;
            }
            if (memoria.get_proceso(i).get_id() == -1) {
                imprimir_tabla(100+auxx,10+aux);
                salida << "|#|";
            }
            else {
                imprimir_tabla(100+auxx,10+aux);
                salida <<"|";
                if(memoria.get_proceso(memoria.get_ejecucion()).get_id()==memoria.get_proceso(i).get_id())
                    SetConsoleTextAttribute(hConsole, BLUE);
                else if(memoria.get_proceso(i).get_bloqueado()){
                    SetConsoleTextAttribute(hConsole, RED);
                }
                salida<<memoria.get_proceso(i).get_id();
                SetConsoleTextAttribute(hConsole, DEFAULT);
                salida<<"|" ;
            }
            cont_espacio++;
            auxx+=5;

        }
        aux++;
        auxx=0;
        for (int i=3;i<7;i++){
            imprimir_tabla(100+auxx,10+aux);
            salida << "|SO|";
            auxx+=5;
        }



        return salida;
    }
};
#endif //PAGINACION_MEMORIA_H
