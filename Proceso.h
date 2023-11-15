#ifndef PAGINACION_PROCESO_H
#define PAGINACION_PROCESO_H
#include <iostream>
using namespace std;

class proceso {
private:
    int id;
    char operacion;
    int tme;
    int num1;
    int num2;
    double resultado=0;
    bool terminado=false;
    bool bloqueado=false;
    vector<int>pos_memoria;
    int peso;
    int t_transcurrido = 0;
    int t_bloqueado = 8;
    int llegada=0;//LLEGADA XD
    int finalizacion; //FINALIZACION XD
    int retorno;//DESDE QUE LLEGA HASTA QUE TERMINA
    int respuesta=-1;//DESDE QUE LLEGA HASTA QUE ES ATENTIDO
    int espera;//TIEMPO QUE ESPERO
    int servicio;//si termino normal, tme si no el transcurrido
    int quantum;
    bool inicio = false;
public:
    void set_num1(int t_num) {
        num1 = t_num;
    }
    void set_num2(int t_num) {
        num2 = t_num;
    }
    void set_id(int t_id) {
        id = t_id;
    }
    int get_peso() {
        return peso;
    }
    void set_peso(int x){
        peso=x;
    }
    void set_bloqueado() {
        t_bloqueado = 8;
    }
    int get_t_bloqueado() {
        return t_bloqueado;
    }
    void restar_bloqueado() {
        t_bloqueado--;
    }
    void set_quantum(int n) {
        quantum = n;
    }
    void marcar_bloqueado(bool x){
        bloqueado=x;
    }
    bool get_bloqueado(){
        return bloqueado;
    }
    void restar_quantum() {
        quantum--;
    }
    void restaurar_quantum(int n) {
        quantum = n;
    }
    int get_quantum() {
        return quantum;
    }
    void set_operacion(char t_oper) {
        operacion = t_oper;
    }
    void set_tme(int t_tme) {
        tme = t_tme;

    }
    void set_resultado(double t_res)  {
        resultado = t_res;
    }
    void aumentar_transcurrido() {
        t_transcurrido++;
    }
    int get_transcurrido() {
        return t_transcurrido;
    }
    double get_resultado() {
        return resultado;
    }
    int get_id() {
        return id;
    }
    int get_num1() {
        return num1;
    }
    int get_num2() {
        return num2;
    }
    char get_oper() {
        return operacion;
    }
    int get_llegada() {
        return llegada;
    }
    int get_respuesta() {
        return respuesta;
    }
    int get_tme() {
        return tme;
    }
    bool get_terminado() {
        return terminado;
    }

    bool get_inicio() {
        return inicio;
    }
    void set_posicion(vector<int>& x){
        pos_memoria=x;
    }
    vector<int> get_vector(){
        return pos_memoria;
    }
    int get_posiciones(){
        return pos_memoria.size();
    }
    void set_inicio() {
        inicio = false;
    }
    void set_finalizado(int &segundos) {
        finalizacion = segundos;
    }
    void set_respuesta(int &seg) {
        respuesta = seg-llegada;
        inicio = true;
    }
    void set_terminado(bool x) {
        terminado = x;
    }
    void set_llegada(int &segundos) {
        llegada = segundos;
    }
    void set_tiempos(int& segundos) {
        servicio = t_transcurrido;
        retorno = finalizacion - llegada;
        espera = retorno - servicio;
    }
    ~proceso() {
    }
    proceso() {
        //nombre = "FIN                       ";
        id = -1;
        operacion = ' ';
        tme = 0;
        num1 = 0;
        num2 = 0;
    }
    proceso(const int& t_id, const int& t_num1, const int& t_num2, const char& t_oper, const int& t_tme) {
        id = t_id;
        operacion = t_oper;
        tme = t_tme;
        num1 = t_num1;
        num2 = t_num2;
    }
    proceso(int& t_id, int& t_num1, int& t_num2, char& t_oper, int& t_tme) {
        id = t_id;
        operacion = t_oper;
        tme = t_tme;
        num1 = t_num1;
        num2 = t_num2;
    }
    proceso(int&& t_id, int&& t_num1, int&& t_num2, char&& t_oper, int&& t_tme) {
        id = t_id;
        operacion = t_oper;
        tme = t_tme;
        num1 = t_num1;
        num2 = t_num2;
    }

    friend std::ostream& operator<<(std::ostream& salida, const proceso& p) {
        salida << "ID: " << p.id << "   Resultado: " ;
        if (!p.terminado) {
            salida << p.resultado<<endl;
        }
        else {
            salida<<"ERROR"<<endl;
        }
        salida << "Llegada: " << p.llegada << " Finalizacion: " << p.finalizacion<<" Retorno: "<<p.retorno<< " Respuesta: "<<p.respuesta<<" Espera: "<<p.espera<<" Servicio: "<<p.servicio;

        salida << endl;
        return salida;
    }
};



#endif //PAGINACION_PROCESO_H
