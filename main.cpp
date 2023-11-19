#include <bits/stdc++.h>
#include <cstdlib>
#include <conio.h>
#include <random>
#include <Windows.h>
#include "Memoria.h"
#include <cmath>
#include "Proceso.h"
#include <ctime>
using namespace std;
proceso ingresar_datos(Memoria& memoria, int contador, int opers) {
    //cout << "Vamos a llenar tus operaciones" << endl;
    proceso t_oper;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> peso(6, 26);
    int t_peso=peso(gen);
    char t_op;
    int t_id, t_tme, t_num1, t_num2;
    int aux = 0;
    int id_auto = contador+1;
    cout<<id_auto;
    int tme_auto, num1_auto, num2_auto;
    char op_auto = ' ';
    double t_res;
    srand(static_cast<unsigned>(time(nullptr)));


    int aleatorizar = rand() % 1000 + ((contador - 1) * 5);
    srand(aleatorizar);
    //ID AUTO

    t_id = id_auto;
    id_auto++;

    aux++;

    t_oper.set_id(t_id);

    //TME AUTO
    do {
        tme_auto = rand() % 13 + 6; //  6 - 18
        t_tme = tme_auto;
    } while (t_tme <= 0);
    t_oper.set_tme(t_tme);

    //OPERACION Y NUMEROS AUTO
    do {
        num1_auto = rand() % 15 + 1; // 1 - 15
        t_num1 = num1_auto;
        num2_auto = rand() % 15 + 1; // 1 - 15
        t_num2 = num2_auto;

        do {
            int op_aux;
            op_aux = rand() % 5 + 1;
            switch (op_aux)
            {
                case 1:
                    op_auto = '+';
                    t_res = t_num1 + t_num2;
                    break;
                case 2:
                    op_auto = '-';
                    t_res = t_num1 - t_num2;

                    break;
                case 3:
                    op_auto = '*';
                    t_res = t_num1 * t_num2;

                    break;
                case 4:
                    op_auto = '/';
                    t_res = static_cast<double>(t_num1) / t_num2;

                    break;
                case 5:
                    op_auto = '%';
                    t_res = t_num1 % t_num2;

                    break;
            }
            t_op = op_auto;
        } while (t_op != '+' && t_op != '-' && t_op != '*' && t_op != '/' && t_op != '%');

    } while ((t_op == '/' || t_op == '%') && t_num2 == 0);
    t_oper.set_num1(t_num1);
    t_oper.set_num2(t_num2);
    t_oper.set_operacion(t_op);
    t_oper.set_resultado(t_res);
    t_oper.set_peso(t_peso);


    return t_oper;
}
void imprimir(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void actualizar_global(int& segundos) {
    imprimir(70, 1);
    cout << "CONTADOR GLOBAL: " << segundos << endl;
}
void imprimir_op_actual(int izq, int der, int i, int j, Memoria& memoria) {
    imprimir(izq, 9);
    cout << "|";
    imprimir(40, 9);
    cout << "--------------------";
    imprimir(der, 9);
    cout << "|";
    imprimir(der, 10);
    cout << "|";
    imprimir(40, 10);
    cout << "ID: " << memoria.get_proceso(j).get_id() << "  " << endl;
    imprimir(izq, 10);
    cout << "|";
    imprimir(izq, 11);
    cout << "|";
    imprimir(40, 11);
    cout << "Peso: " << memoria.get_proceso(j).get_peso() << "  " << endl;
    imprimir(der, 11);
    cout << "|";
    imprimir(izq, 12);
    cout << "|";
    imprimir(40, 12);
    cout << "Quantum: " << memoria.get_proceso(j).get_quantum()<<"  ";
    imprimir(der, 12);
    cout << "|";
    imprimir(izq, 13);
    cout << "|";
    imprimir(40, 13);
    cout << "TME: " << memoria.get_proceso(j).get_tme() << "  "<<endl;
    imprimir(der, 13);
    cout << "|";
    imprimir(izq, 14);
    cout << "|";
    imprimir(40, 14);
    cout << "Operacion: " << memoria.get_proceso(j).get_oper() << endl;
    imprimir(der, 14);
    cout << "|";
    imprimir(izq, 15);
    cout << "|";
    imprimir(40, 15);
    cout << "Numero 1: " << memoria.get_proceso(j).get_num1() << endl;
    imprimir(der, 15);
    cout << "|";
    imprimir(izq, 16);
    cout << "|";
    imprimir(40, 16);
    cout << "Numero 2: " << memoria.get_proceso(j).get_num2() << endl;
    imprimir(der, 16);
    cout << "|";

    imprimir(izq, 17);
    cout << "|";
    imprimir(40, 17);
    cout << "Transcurrido: " << memoria.get_proceso(j).get_transcurrido() <<"  "<< endl;
    imprimir(der, 17);
    cout << "|";

    imprimir(izq, 18);
    cout << "|";
    imprimir(40, 18);
    cout << "Restante: " << memoria.get_proceso(j).get_tme()-memoria.get_proceso(j).get_transcurrido() << "  "<<endl;
    imprimir(der, 18);
    cout << "|";

    imprimir(izq, 19);
    cout << "|";
    imprimir(40, 19);
    cout << "--------------------";
    imprimir(der, 19);
    cout << "|";

}
void imprimir_finalizados(int& segundos, int i, int j, proceso proceso, int& cont, int& aux, int procesos) {
    if (cont == 5) {
        system("cls");
        cont = 0;
        aux = 0;
    }
    cont++;



    imprimir(0, 0);
    cout << "FINALIZADOS";
    actualizar_global(segundos);

    aux++;
    imprimir(0, aux);
    cout << " Proceso: " << procesos + 1 << endl;
    imprimir(38, aux);
    cout << "|";

    aux++;
    imprimir(0, aux);
    cout << "ID: " << proceso.get_id() << endl; //PROBLEMA ID
    imprimir(38, aux);
    cout << "|";
    aux++;
    imprimir(0, aux);
    cout << "TME: " << proceso.get_tme() << endl;
    imprimir(38, aux);
    cout << "|";
    aux++;
    imprimir(0, aux);
    cout << "Proceso: " << proceso.get_num1() << proceso.get_oper() << proceso.get_num2() << " = ";
    if (!proceso.get_terminado()) {
        cout << proceso.get_resultado() << endl;

    }
    else { cout << "ERROR" << endl; }

    imprimir(38, aux);
    cout << "|";
    aux++;
    imprimir(0, aux);
    cout << "--------------------------------------" << endl;
    imprimir(38, aux);
    cout << "|";
}
bool actualizar_bloqueo(vector<proceso>&bloqueados, int &segundos, int i, int j,Memoria& memoria){

}
void imprimir_tabla_temp(Memoria& memoria, vector<proceso>&listos, vector<proceso>& bloqueados, vector<proceso>& finalizados, int& segundos) {
    system("cls");
    int tecla;
    cout << "TABLA TEMPORAL" << endl;
    cout << "En ejecucion " << endl;
    int id_anterior=-1;
    for (int i = 0; i <= memoria.size()/5; i++) {
        if(id_anterior==memoria.get_proceso(i).get_id()){

            continue;
        }
        id_anterior=memoria.get_proceso(i).get_id();
        cout << "ID: " << memoria.get_proceso(i).get_id() << " Resultado: En espera" << endl;
        cout << "Llegada: " << memoria.get_proceso(i).get_llegada() << " Finalizacion: |No aplica|" << " Retorno:"<<segundos-memoria.get_proceso(i).get_llegada()<< " Respuesta: ";
        if (memoria.get_proceso(i).get_respuesta() < 0) {
            cout << ("|No aplica|");
        }
        else {
            cout<<memoria.get_proceso(i).get_respuesta();
        }
        cout << " Espera: " << (segundos - memoria.get_proceso(i).get_llegada() - memoria.get_proceso(i).get_transcurrido()) << " Servicio: " << memoria.get_proceso(i).get_transcurrido() << endl;

    }
    for (int i = 0; i < bloqueados.size(); i++) {
        cout << "ID: " << bloqueados[i].get_id() << " Resultado: En espera" << endl;
        cout << "Llegada: " << bloqueados[i].get_llegada() << " Finalizacion: |No aplica|" << " Retorno: |No aplica|" << " Respuesta: ";
        if (bloqueados[i].get_respuesta() < 0) {
            cout << "|No aplica|";
        }
        else {
            cout << bloqueados[i].get_respuesta();
        }
        cout << " Espera: " << (segundos - bloqueados[i].get_llegada() - bloqueados[i].get_transcurrido()) << " Servicio: " << bloqueados[i].get_transcurrido() << endl;

    }
    cout << "En espera: " << endl;
    for (int i = 0; i < listos.size(); i++) {
        cout << "ID: " << listos[i].get_id() << " |No aplica|" << endl;
    }
    cout << "Finalizados: " << endl;
    for (int i = 1; i <= finalizados.size(); i++) {
        cout << finalizados[i];
    }


    imprimir(30, 30);
    cout << "Presiona C para continuar con el programa";
    do {
        if (_kbhit()) {
            tecla = _getch();
            if (tecla == 'C' || tecla == 'c') {
                break;
            }
        }
    } while (true);

}
void espera_cpu(vector<proceso>&bloqueados, Memoria& memoria,int &segundos, int i, int j) {

    do {

        //imprimir_nada(39, 60, i, j, memoria);
        if (actualizar_bloqueo(bloqueados, segundos, i, j, memoria)) {

            break;
        }
        segundos++;
        actualizar_global(segundos);
        Sleep(1000);
    } while (true);
}

void add_proceso(Memoria& memoria, vector<proceso>& bloqueados, vector<proceso>& listos, vector<proceso>& finalizados, int& segundos, int& quantum) {
    proceso t_proceso = ingresar_datos(memoria, memoria.get_cantidad()+listos.size()+finalizados.size(), 0);

    t_proceso.set_llegada(segundos);
    t_proceso.set_inicio();
    t_proceso.set_quantum(quantum);
    if(!memoria.set_proceso(t_proceso)){
        listos.push_back(t_proceso);
    }



}
bool interact_teclado(int& segundos, int i, int j, Memoria& memoria,vector<proceso>&bloqueados, vector<proceso>& listos, vector<proceso>& finalizados, int& auxx, int& cont, int& quantum) {
    int aux = 1, tecla;

    tecla = _getch();
    switch (tecla) {
        case 'b':
        case 'B':
            imprimir_tabla_temp(memoria, listos, bloqueados, finalizados,segundos);
            cont = 0;
            auxx = 0;
            system("cls");

            if(!finalizados.empty())
                imprimir_finalizados(segundos, 0, 0, finalizados[finalizados.size()-1], cont, auxx, finalizados.size()-1);
            imprimir_op_actual(39, 60, i, j, memoria);
            //imprimir_lote_actual(i, 39, 60, memoria);
            break;
        case 'n':
        case 'N':
            add_proceso(memoria, bloqueados, listos ,finalizados,segundos,quantum);
            break;
        case 112:
        case 80:

            imprimir(70, 20);
            cout << "EN PAUSE";

            do {
                if (_kbhit()) {
                    tecla = _getch();
                    if (tecla == 67 || tecla == 99) {
                        break;
                    }
                }
                actualizar_global(segundos);

                Sleep(100);
                aux++;
                if (aux == 10) {
                    segundos++;
                    aux = 1;
                }
            } while (true);

            imprimir(70, 20);
            cout << "            ";
            break;

        case 101:
        case 69:
            memoria.modificar_terminado(j);
            break;

        case 105:
        case 73://I

            memoria.marcar_bloqueado(true);

            memoria.set_ejecucion(memoria.siguiente(memoria.get_ejecucion()));

            break;
    }
    return false;
}
void imprimir_fin(vector<proceso>&finalizados, int &segundos) {
    system("cls");
    cout << "FINALIZADOS" << endl;
    cout << "Reloj global: " << segundos<<endl;
    for (int i = 0; i < finalizados.size(); i++) {
        cout <<finalizados[i] <<endl;
    }
}
void imprimir_disponible(Memoria& memoria){
    imprimir(80,0);
    cout<<"La memoria disponible es: "<<memoria.get_disponible();
    imprimir(80,1);
    cout<<"La memoria ocupada es: "<<memoria.get_ocupado();

}
void imprimir_inicio(Memoria &memoria, int total_oper, int cant_lotes, vector<proceso>& listos, int quantum) {
    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    SMALL_RECT windowSize = { 0, 0, 1200, 1200 };
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    //vector<proceso>finalizados;
    vector<proceso>bloqueados;
    vector<proceso>finalizados;
    int segundos = 0;
    int cont = 0, aux = 0;
    imprimir(0, 0);
    int izq = 39, der = 60;
    cout << "FINALIZADOS";

    int i = 0;
    int j = 0, procesos = 0;
    int tiempo=1;
    int en_ejecucion=0;
    memoria.set_ejecucion(en_ejecucion);
    do {
        en_ejecucion=memoria.get_ejecucion();
        if(!memoria.get_proceso(memoria.get_ejecucion()).get_inicio()){
            memoria.set_respuesta(segundos);
        }
        imprimir(20,15);
        cout<<"MEMORIA "<<memoria.get_ejecucion()<<" ";
        imprimir(20,16);
        cout<<"PROGRAMA "<<en_ejecucion<<" ";
        imprimir_disponible(memoria);
        imprimir_op_actual(izq, der, i, en_ejecucion, memoria);//IMPRIME EL APARTADO DEL ACTUAL
        imprimir(70, 0);
        cout << "NUEVOS: " << listos.size();

        if(_kbhit()){
            interact_teclado(segundos,0,0,memoria,bloqueados,listos,finalizados,aux,total_oper,quantum);
        }

        cout<<memoria;
        if(tiempo%10==0){
            segundos++;
            if(memoria.restar()){
                memoria.set_tiempos(segundos);
                //cout<<memoria.get_proceso(memoria.get_ejecucion());
                //system("pause");
                finalizados.push_back(memoria.get_proceso(memoria.get_ejecucion()));
                memoria.terminado(memoria.get_ejecucion());
            }
            if(memoria.get_proceso(en_ejecucion).get_quantum()<1){
                memoria.fin_quantum(en_ejecucion,quantum);

            }
        }
        imprimir(0,25);
        cout<<"FRAMES RESTANTES: "<<memoria.get_frames()<<" ";
        if(!listos.empty() ){
            //if()
            if((memoria.get_frames() >= ceil(listos[0].get_peso()/5))){
                listos[0].set_llegada(segundos);
                memoria.buscar(listos[0]);
                listos.erase(listos.begin());
                if(!listos.empty()){
                    if((ceil(listos[0].get_peso())/5)<=memoria.get_frames()){
                        memoria.set_llena(true);
                        //system("pause");
                    }
                }
            }

        }

        Sleep(100);


        tiempo++;

    } while (memoria.get_ocupado()>0);
    //system("pause");

    //} while ();
    imprimir_fin(finalizados,segundos);
    imprimir(50, 50);
    system("pause");
}

int main() {
    cout << "Hello, World!" << endl;
    int cant_opera, cant_lotes, aux;
    cout << "Ingresa la cantidad de procesos deseados: " << endl;
    cin >> cant_opera;
    cout<<"Ingresa la cantidad del quantum"<<endl;
    int quantum;cin>>quantum;
    Memoria memoria;
    vector<proceso>listos;
    system("cls");
    for (int i = 0; i < cant_opera; i++) {
        proceso t = ingresar_datos(memoria, i,cant_opera);
        t.set_quantum(quantum);
        if(!memoria.set_proceso(t)){
            (listos.push_back(t));
        }

    }
    system("cls");
    imprimir_inicio(memoria,cant_opera,cant_lotes,listos,quantum);
    return 0;
}
