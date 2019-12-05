#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <time.h>
#include <ctime>
#include <iostream>
using namespace std;
struct Nodo {

    int id;
    int carretaId;
   Nodo * siguiente;
   Nodo(int id);
   Nodo(int id,int carreta);


};
struct NodoP {


    int carretaId;
   NodoP * siguiente;
   NodoP(int id);



};
struct Pila{
    NodoP *cabeza;
    NodoP* fin;
    Pila();
    bool isEmpty();
    void push(int id);
    int pop();
    int size();

    int tam;
    void Clear();
    string Graficar(string nombre);
};
struct Cola{
    Nodo *cabeza,*fin;
    Cola();

    bool isEmpty();
    void Encolar(int id);
    Nodo* Desencolar();
    int size();

    int tam;
    void EncolarPagos(int idCl, int carreta);
    void Clear();
    string Graficar(string nombre);
    string GraficarPagos(string nombre);
    void deleteAll();

};

struct NodoC{
    int idCl;
    int  idCa;
    NodoC* siguiente,*anterior;
    NodoC(int id,int carreta);


};

struct ListaCircular{
  NodoC * Inicio,*fin;
  int tam;
  ListaCircular();
  int size();
  string  Graficar(string nombre);
       void insertar(int idCl,int idCarreta);
       NodoC * eliminar();
       void Clear();
       void deleteAll();

};
typedef int Caja;
typedef time_t Tiempo;
struct NodoDoble{
    Caja id;
   Tiempo start,end;
  const char* estado="Libre";
   Nodo *cliente;
   NodoDoble *siguiente,*anterior;
   NodoDoble(Caja id,const char* estado);

};
struct ListaDoble{
  NodoDoble * Inicio,*fin;
  int tam;
  ListaDoble();

  bool Disponible();
  string Graficar(string nombre);
  void Modificar(Nodo * client);
  void insertar(Caja id,const char* estado);
  NodoDoble eliminar(Caja id);
  Nodo *TiempoServicio(NodoDoble * aux);
  void Clear();
};


#endif // ESTRUCTURAS_H
