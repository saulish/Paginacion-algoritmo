#ifndef PAGINACION_MEMORIA_H
#define PAGINACION_MEMORIA_H
#include <iostream>
#include <map>
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
    int tamanio = 220;
    int disponible;
    int ocupado;
    int ps = 0;
    int ejecucion=0;
    map<int, proceso>memoria;
public:
    Memoria() {
        disponible = tamanio;
        ocupado = 0;
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

    void set_proceso(proceso& pr) {
        if (pr.get_peso() > disponible) {
            cout << "Sin espacio" << endl;
            return;
        }
        vector<int>pos;
        disponible -= pr.get_peso();
        ocupado+=pr.get_peso();
        for (int i = 0; i < pr.get_peso() / 5; i++) {
            memoria[ps] = pr;
            pos.push_back(ps);
            ps++;
        }
        for(int p : pos){
            memoria[p].set_posicion(pos);
        }
    }
    proceso get_proceso(int ps) {
        return memoria[ps];
    }
    void modificar_terminado(int i){
        memoria[i].set_terminado(true);
    }

    int siguiente(int x){
        for(int i=x;i<memoria.size();i++){
            if(memoria[i].get_id()!=-1 && memoria[i].get_id()!= memoria[ejecucion].get_id())
                return i;
        }
        for(int i=0;i<x;i++){
            if(memoria[i].get_id()!=-1 && memoria[i].get_id()!= memoria[ejecucion].get_id())
                return i;
        }
        return x;

    }
    void set_ejecucion(int x){
        ejecucion=x;
    }
    int get_ejecucion(){
        return ejecucion;
    }
    void fin_quantum(int x, int quantum){
        memoria[x].set_quantum(quantum);
        vector<int>t_pos=memoria[x].get_vector();
        if(ocupado>0){
            int next=siguiente(ejecucion);
            ejecucion=next;
        }

    }
    void terminado(int x){
        vector<int>t_pos=memoria[x].get_vector();
        proceso p;
        disponible+=memoria[x].get_peso();
        ocupado-=memoria[x].get_peso();
        int next=t_pos[t_pos.size()-1];
        for(int t_po : t_pos){
            memoria[t_po]=p;

        }
        if(ocupado>0){
            next=siguiente(next);
            ejecucion=next;
        }

    }
    void restar(){
        vector<int>t_pos=memoria[ejecucion].get_vector();
        memoria[ejecucion].aumentar_transcurrido();
        if(memoria[ejecucion].get_tme()== memoria[ejecucion].get_transcurrido()){
            terminado(ejecucion);
        }
        proceso p;
        for(int i=0;i<t_pos.size();i++){
            memoria[t_pos[i]].restar_quantum();

        }

    }
    friend ostream& operator <<(ostream& salida, Memoria& memoria) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int cont_espacio=0,aux=0,auxx=0;
        for (int i = 0; i < memoria.size(); i++) {
            if(cont_espacio==5) {
                salida<<endl;
                cont_espacio=0;
                aux++;
                auxx=0;
            }
            if (memoria.get_proceso(i).get_id() == -1) {
                imprimir_tabla(100+auxx,10+aux);
                salida << "|0|";
            }
            else {
                imprimir_tabla(100+auxx,10+aux);
                salida <<"|";
                if(memoria.get_proceso(memoria.get_ejecucion()).get_id()==memoria.get_proceso(i).get_id())
                    SetConsoleTextAttribute(hConsole, BLUE);

                salida<<memoria.get_proceso(i).get_id();
                SetConsoleTextAttribute(hConsole, DEFAULT);
                salida<<"|" ;
            }
            cont_espacio++;
            auxx+=5;

        }
        return salida;
    }
};
#endif //PAGINACION_MEMORIA_H
