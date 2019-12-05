#include <QCoreApplication>
#include "estructuras.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

static int pasos=1;
static int turno=0;
Nodo::Nodo(int id){
    this->id=id;

    this->siguiente=NULL;
}
NodoP::NodoP(int id){
    this->carretaId=id;
    this->siguiente=NULL;
}
Nodo::Nodo(int id,int carreta){
    this->id=id;
    this->carretaId=carreta;
    this->siguiente=NULL;
}
//codigo de la pila comienzo
Pila::Pila(){
    this->cabeza=NULL;
}

int Pila::size(){
    int tam=0;
    NodoP *aux=cabeza;
    while(aux!=NULL){
        tam++;
        aux=aux->siguiente;
    }
    return tam;
}
void Pila::push(int id){
    if(size()<tam){
    NodoP *nuevo=new NodoP(id);
    if(cabeza==NULL){
        cabeza=fin=nuevo;
    }else{

       fin->siguiente=nuevo;
       fin=nuevo;
    }
}else{
        cout<<"Pila LLena";
}
}


bool Pila::isEmpty(){
    if(size()==0){
        return true;
    }
    return false;
}
string Pila::Graficar(string nombre){
 string var="subgraph "+nombre+"{";

 if(cabeza!=NULL){var+="A"+nombre+"[shape=box label=<<TABLE border=\"3\" cellspacing=\"3\" cellpadding=\"10\" style=\"rounded\">";

        NodoP *aux=cabeza;
        while(aux!=NULL){
            var+="<TR>";
           var+="<TD border=\"3\"> Carreta Id: "+to_string((*aux).carretaId)+"</TD>";
           var+="</TR>";
           aux= aux->siguiente;
        }
        var+="</TABLE>>];";
    }
 var+="label=\""+nombre+"\";}";
 return var;
}
int Pila::pop(){
    int retornar=NULL;
    if(!isEmpty()){
        if(cabeza==fin){
            retornar=(*cabeza).carretaId;
            cabeza=fin=NULL;
        }else{
            NodoP *aux=cabeza;
            while(aux->siguiente!=NULL){
                NodoP* actual=aux->siguiente;
                if(actual==fin){
                    retornar=(*actual).carretaId;
                    aux->siguiente=NULL;
                    fin=aux;
                    delete(actual);
                    break;
                }
 aux=aux->siguiente;
                }


        }


    }else{
        cout<<"Pila Vacía \n";
    }
    return retornar;
}
//fin del codigo pila

//comienzo del codido de la Cola
Cola::Cola(){
    fin=cabeza=NULL;
}
int Cola::size(){
    int tam=0;
    Nodo *aux=cabeza;
    while(aux!=NULL){
        tam++;
        aux=aux->siguiente;
    }
    return tam;
}
void Cola::Encolar(int id){

    Nodo *nuevo=new Nodo(id);
    if(cabeza==NULL){
        cabeza=fin=nuevo;
    }else{
        if(cabeza==fin){
            cabeza->siguiente=nuevo;
            fin=nuevo;
        }else{
       fin->siguiente=nuevo;
       fin=nuevo;
        }
}

}
void Cola::EncolarPagos(int id, int carreta){
    Nodo *nuevo=new Nodo(id,carreta);
    if(cabeza==NULL){
        cabeza=fin=nuevo;
    }else{

       fin->siguiente=nuevo;
       fin=nuevo;
}
 }
bool Cola::isEmpty(){
    if(size()==0){
        return true;
    }
    return false;
}
string Cola::Graficar(string nombre){
   string var="subgraph "+nombre+" { ";
   string relacion="";
       if(cabeza!=NULL){
           var+="rankdir=BT;";
           Nodo *aux=cabeza;
           while(aux->siguiente!=NULL){
               Nodo* actual=aux->siguiente;
               var+="n"+to_string((*aux).id)+"[ shape=box label=\"ID Cliente: "+to_string((*aux).id)+"\"];";
               relacion+="n"+to_string((*aux).id)+"->n"+to_string((*actual).id)+";";
                       if(actual->siguiente==NULL){
                           var+="n"+to_string((*actual).id)+"[ shape=box label=\"ID Cliente: "+to_string((*actual).id)+"\"];";
                        }

              aux= aux->siguiente;
           }
           if(cabeza==fin){
                var+="n"+to_string((*cabeza).id)+"[ shape=box label=\"ID Cliente: "+to_string((*cabeza).id)+"\"];";
           }


       }
       var+=relacion+"label=\""+nombre+"\";}";
       return var;
}
string Cola::GraficarPagos(string nombre){
    string var="subgraph "+nombre+" {";
    string relacion="";
        if(cabeza!=NULL){
            var+=" rankdir=BT;";
            Nodo *aux=cabeza;
            while(aux->siguiente!=NULL){
                Nodo* actual=aux->siguiente;
                var+="nod"+to_string((*aux).id)+"[ shape=box label=\"ID Cliente: "+to_string((*aux).id)+"\n ID carreta: "+to_string((*aux).carretaId)+"\"];";
                relacion+="nod"+to_string((*aux).id)+"->nod"+to_string((*actual).id)+";";
                        if(actual->siguiente==NULL){
                            var+="nod"+to_string((*actual).id)+"[ shape=box label=\"ID Cliente: "+to_string((*actual).id)+"\n ID carreta: "+to_string((*actual).carretaId)+"\"];";
                         }

               aux= aux->siguiente;
            }


        }
       var+=relacion+"label=\""+nombre+"\"};";
        return var;
}
Nodo*  Cola::Desencolar(){
    Nodo* retornar=NULL;
    if(!isEmpty()){
        if(cabeza==fin){
            retornar=cabeza;
            cabeza=fin=NULL;
        }else{
            retornar=cabeza;

            cabeza=cabeza->siguiente;


        }
    }
    return retornar;
}
void Cola::deleteAll(){
    while(cabeza!=NULL){
        Desencolar();
    }
}
//fin de cola

//inicio lista simple circular de Compras
NodoC::NodoC(int id, int idC){
    idCl=id;
    idCa=idC;
    siguiente=NULL;
}
ListaCircular::ListaCircular(){
    Inicio=fin=NULL;
    tam=0;
}
void ListaCircular::insertar(int id, int idC){
    if(Inicio==NULL){
        Inicio=fin=new NodoC(id,idC);
        Inicio->siguiente=Inicio;
        Inicio->anterior=Inicio;
        fin->siguiente=Inicio;
        fin->anterior=Inicio;



    }else{
        NodoC* nuevo=new NodoC(id,idC);
        if(Inicio==fin){

            Inicio->siguiente=nuevo;
            Inicio->anterior=nuevo;
            nuevo->anterior=Inicio;
            nuevo->siguiente=Inicio;
            fin=nuevo;


        }else{

         fin->siguiente=nuevo;
         nuevo->anterior=fin;
         nuevo->siguiente=Inicio;
         Inicio->anterior=nuevo;
         fin=nuevo;



        }
    }
}
int ListaCircular::size(){
    int tam=0;
    NodoC*aux=Inicio;

    if(Inicio!=NULL){
    do{
        tam++;
        aux=aux->siguiente;
    }while(aux!=Inicio);
    }
    return tam;
}
NodoC* ListaCircular::eliminar(){
    NodoC *retornar=NULL;
    if(Inicio!=NULL){
        int inicio=0,end=2;



    while(end!=inicio){
        int num=rand()%101;
        int n=0;
     if(num<ListaCircular::size()){
         NodoC *aux=Inicio;
         while(aux!=NULL){
         if(n==num){
         if( Inicio==fin && aux==Inicio){
             retornar=aux;
             Inicio=fin=NULL;

             break;
         }else if(aux==Inicio){
             fin->siguiente=Inicio->siguiente;
             retornar=Inicio;
             Inicio=Inicio->siguiente;


             break;

         }else if(aux==fin){
             retornar=fin;
             fin->anterior->siguiente=Inicio;
             fin=fin->anterior;
             Inicio->anterior=fin;

             break;
         }else{
             aux->anterior->siguiente=aux->siguiente;
             aux->siguiente->anterior=aux->anterior;
             retornar=aux;

             break;
         }
         }
         n++;
         aux=aux->siguiente;
     }

          break;
        }
     inicio++;
    }
    }
    return retornar;
}
string ListaCircular::Graficar(string nombre){
    string var="subgraph "+nombre+" { ";
    string relacion="";
    if(Inicio!=NULL){
        var+="rankdir=TB;";
        NodoC * aux=Inicio;
       while(aux->siguiente!=Inicio){
            NodoC * actual=aux->siguiente;
            var+="nodo"+to_string((*aux).idCl)+"[shape=box label=\" ID cliente: "+to_string((*aux).idCl)+" \n ID carreta: "+to_string((*aux).idCa)+"\"];";
            relacion+="nodo"+to_string((*aux).idCl)+"->nodo"+to_string((*actual).idCl)+";";
            relacion+="nodo"+to_string((*actual).idCl)+"->nodo"+to_string((*aux).idCl)+";";
            if(actual->siguiente==Inicio){
                var+="nodo"+to_string((*fin).idCl)+"[shape=box label=\" ID cliente: "+to_string((*fin).idCl)+" \n ID carreta: "+to_string((*fin).idCa)+"\"];";
                relacion+="nodo"+to_string((*fin).idCl)+"->nodo"+to_string((*Inicio).idCl)+";";
                relacion+="nodo"+to_string((*Inicio).idCl)+"->nodo"+to_string((*fin).idCl)+";";
            }
            aux=aux->siguiente;
        }
       if(Inicio==fin){
           var+="nodo"+to_string((*Inicio).idCl)+"[shape=box label=\" ID cliente: "+to_string((*Inicio).idCl)+" \n ID carreta: "+to_string((*Inicio).idCa)+"\"];";

        relacion+=relacion+="nodo"+to_string((*Inicio).idCl)+"->nodo"+to_string((*Inicio).idCl)+";";
         relacion+=relacion+="nodo"+to_string((*Inicio).idCl)+"->nodo"+to_string((*Inicio).idCl)+";";

       }

} var+=relacion+"label=\""+nombre+"\";}";
    return var;
}
void ListaCircular::deleteAll(){
    if(Inicio!=NULL){
        NodoC* aux=Inicio;
       while(aux==Inicio){
           if(Inicio==fin){
                Inicio=fin=NULL;
            }else if(aux==Inicio){
                fin->siguiente=Inicio->siguiente;
                Inicio->siguiente->anterior=fin;
                Inicio=Inicio->siguiente;
            }
            aux=aux->siguiente;
        };

    }
}
//fin lista de compras

//inicio de lista de cajas
NodoDoble::NodoDoble(Caja id1,const char* estado1){
   id=id1;
   estado=estado1;
   cliente=NULL;

   siguiente=anterior=NULL;
}
ListaDoble::ListaDoble(){
    Inicio=fin=NULL;
}
void ListaDoble::insertar(Caja id1,const char* estado1){
    if(Inicio!=NULL){
        NodoDoble *nuevo=new NodoDoble(id1,estado1);

        if(Inicio==fin){
            if(id1<Inicio->id){
                nuevo->siguiente=fin;
                fin->anterior=nuevo;
                Inicio=nuevo;
            }else{
                Inicio->siguiente=nuevo;
                nuevo->anterior=Inicio;
                fin=nuevo;
            }

        }else{
            if(id1>fin->id){
                fin->siguiente=nuevo;
                nuevo->anterior=fin;
                fin=nuevo;
            }else{
            NodoDoble *aux=Inicio;
            while(aux->siguiente!=NULL){
                NodoDoble *actual=aux->siguiente;
                if(id1>aux->id && id1<actual->id){
                    aux->siguiente=nuevo;
                    nuevo->anterior=aux;
                    nuevo->siguiente=actual;
                    actual->anterior=nuevo;
                    break;
                }
                aux=aux->siguiente;
            }
            }

        }



    }else{
        Inicio=fin=new NodoDoble(id1,estado1);
    }
}
bool ListaDoble::Disponible(){

    NodoDoble *aux=Inicio;
    while(aux!=NULL){
        if(strcmp(aux->estado,"Libre")==0){
          return true;
        }
        aux=aux->siguiente;
    }
   return false;

}
void ListaDoble::Modificar(Nodo *cl){
    NodoDoble *aux=Inicio;
    while(aux!=NULL){
        if(strcmp(aux->estado,"Libre")==0){
          aux->cliente=cl;
          aux->estado="Ocupado";
          aux->start=time(0);
          cout<<"-------------------Paso "<<pasos<< "---------------------------"<<endl;
          pasos++;
          cout<<"El cliente "<<(*(*aux).cliente).id<<" con carreta numero "<<(*(*aux).cliente).carretaId<<" esta siendo atendido por la caja "<<aux->id<<"."
             <<endl<<endl;
          break;
        }
        aux=aux->siguiente;
    }

}
bool CarretaDisponible(Pila pila1, Pila pila2){
    if(pila1.size()!=0){
        return true;

    }else if(pila2.size()!=0){
        return true;
    }
   return false;
}
Nodo* ListaDoble::TiempoServicio(NodoDoble * aux){
    Nodo * retornar=NULL;


        if(strcmp(aux->estado,"Ocupado")==0){
            aux->end=time(0);
            //se mantiene en el ciclo media vez no hayan pasado 60 segundos
            while((aux->end-aux->start)<60){
                aux->end=time(0);
            }
            retornar=aux->cliente;
            aux->cliente=NULL;
            aux->estado="Libre";

        }

    return retornar;
}
string ListaDoble::Graficar(string nombre){
    string var="subgraph "+nombre+" {";
    string relacion="";
    if(Inicio!=NULL){
        var+="rankdir=TB;";
        NodoDoble * aux=Inicio;
        while(aux->siguiente!=NULL){

            NodoDoble *actual=aux->siguiente;
            if(aux->cliente!=NULL){
                var+="node"+to_string((*aux).id)+"[ shape=box label=\"ID Caja: "+to_string((*aux).id)+"\n Estado: "+(*aux).estado+"\n ID cliente: "+to_string((*(*aux).cliente).id)+
                        "\n ID Carreta: "+to_string((*(*aux).cliente).carretaId)+"\"];";

            }else{
                var+="node"+to_string((*aux).id)+"[ shape=box label=\"ID Caja: "+to_string((*aux).id)+"\n Estado: "+(*aux).estado+"\n ID cliente:ninguno \n ID Carreta: ninguno \"];";
            }
            relacion+="node"+to_string((*aux).id)+"->node"+to_string((*actual).id)+";";
            relacion+="node"+to_string((*actual).id)+"->node"+to_string((*aux).id)+";";
            aux=aux->siguiente;
        }
        if(Inicio==fin){
            if(aux->cliente!=NULL){
                var+="node"+to_string((*Inicio).id)+"[ shape=box label=\"ID Caja: "+to_string((*Inicio).id)+"\n Estado: "+(*Inicio).estado+"\n ID cliente: "+to_string((*(*Inicio).cliente).id)+
                        "\n ID Carreta: "+to_string((*(*Inicio).cliente).carretaId)+"\"];";

            }else{
                var+="node"+to_string((*Inicio).id)+"[ shape=box label=\"ID Caja: "+to_string((*Inicio).id)+"\n Estado: "+(*Inicio).estado+"\n ID cliente:ninguno \n ID Carreta: ninguno \"];";
            }

        }else{
            if(aux->cliente!=NULL){
                var+="node"+to_string((*fin).id)+"[ shape=box label=\"ID Caja: "+to_string((*fin).id)+"\n Estado: "+(*fin).estado+"\n ID cliente: "+to_string((*(*fin).cliente).id)+
                        "\n ID Carreta: "+to_string((*(*fin).cliente).carretaId)+"\"];";

            }else{
                var+="node"+to_string((*fin).id)+"[ shape=box label=\"ID Caja: "+to_string((*fin).id)+"\n Estado: "+(*fin).estado+"\n ID cliente:ninguno \n ID Carreta: ninguno \"];";
            }
        }

    } var+=relacion+"label=\""+nombre+"\";}";
    return var;
}
/*const char* Proceso(Pila car1,Pila car2,Cola espera,Cola pago){
   const char* grafico="";

}*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Pila  pila1,pila2;
    Cola Espera,pagos;
    ListaCircular compras;
    ListaDoble Listacaja;
    //predefiniendo parametros iniciales
    cout<<"*********************Bienvenido al MiniMarket*****************************"<<endl<<endl;

   int numEspera;
printf( "Ingrese la cantidad de clientes en cola:\n " );
cin>>numEspera;
Espera.tam=numEspera;
printf( "Has tecleado el numero %i\n", numEspera );
printf("\n");

int cantidad1;
 printf("Ingrese la cantidad de carretas que desea en cada pila:\n");
     cin>>cantidad1;
     pila1.tam=cantidad1;
     pila2.tam=cantidad1;
     printf( "Has tecleado el numero %i\n", cantidad1 );
     printf("\n");
int turnos;
printf("Ingrese un numero para saber cada cuantos turnos quiere que se muestre la parte gráfica:\n");
cin>>turnos;
 cout<<"Ha ingresado el numero "<<turnos<<endl<<endl;


    int clienteCompra;
         cout<<"Ingrese la cantidad de clientes comprando:\n";
        cin>>clienteCompra;
        compras.tam=clienteCompra;
        printf( "Has tecleado el numero %i\n", clienteCompra );
        printf("\n");

     int cantpago;
         cout<<"Ingrese la cantidad de clientes en cola de pagos:\n";
        cin>>cantpago;

        printf( "Has tecleado el numero %i\n", cantpago );
        printf("\n");

        int cajas;
            cout<<"Ingrese la cantidad de cajas:\n";
           cin>>cajas;
           Listacaja.tam=cajas;
           printf( "Has tecleado el numero %i\n", cajas );
           printf("\n");




           //se llenan las cajas
           for(int i=0;i<Listacaja.tam;i++){
               Listacaja.insertar(i,"Libre");
           }
//se llenan las pilas de carretas
           for (int i=0;i<pila1.tam;i++) {
               pila1.push(i);
           }
           for(int i=pila1.tam;i<(pila1.tam+pila2.tam);i++){
               pila2.push(i);
           }


           while(numEspera!=0){

               int numClientes=101;
               while(numClientes!=(clienteCompra+101)){

                   compras.insertar(numClientes,numClientes+1);
                   if(!Listacaja.Disponible()){
         //insertar en cola de pagos
                       NodoC* aux=compras.eliminar();

                       if(aux!=NULL){
                           cout<<"----------------------Paso "<<pasos<<"-----------------------------"<<endl<<endl;
                           pasos++;
                       pagos.EncolarPagos((*aux).idCl,(*aux).idCa);
                       cout<<"El cliente "<<(*aux).idCl<<" y carreta con numero "<<(*aux).idCa<<" ingresa a cola de pagos."<<endl<<endl;
                           }
                   }else{
         //proceso de cajas
                   if(Listacaja.Disponible()){
                       NodoC* aux=compras.eliminar();
                       if(aux!=NULL){
                       Nodo * temp=new Nodo((*aux).idCl,(*aux).idCa);
                       Listacaja.Modificar(temp);
                       }
                   }
                   }
                   numClientes++;
               }
               int numpago=numClientes;
               while(numpago!=(cantpago+numClientes)){

                   compras.insertar(numpago,numpago+1);
                   numpago++;
               }
               //se llena la cola de espera
           for (int i=0;i<Espera.tam;i++) {
               Espera.Encolar(i);
           }
           while(Espera.cabeza!=NULL){
               cout<<"----------------------Paso "<<pasos<<"-----------------------------"<<endl<<endl;
                pasos++;
//llenar lista circular de compras
           while(CarretaDisponible(pila1,pila2)){

               if(Espera.cabeza!=NULL){

     int temp=1+rand()%(3-1);
               if(temp==1 && !pila1.isEmpty()){
int aux=(*Espera.Desencolar()).id;

                   int aux2=pila1.pop();
                   compras.insertar(aux,aux2);
                   cout<<"El cliente "<<aux<<" y carreta numero "<<aux2<<" esta comprando."<<endl<<endl;

               }else if(temp==2 && !pila2.isEmpty()){
                   int aux=(*Espera.Desencolar()).id;
                          int aux2=pila2.pop();
                    compras.insertar(aux,aux2);
                    cout<<"El cliente "<<aux<<" y carreta numero "<<aux2<<" esta comprando."<<endl<<endl;

               }
               //se trata de sacar un cliente de la lista de compras


               if(!Listacaja.Disponible()){
     //insertar en cola de pagos
                   NodoC* aux=compras.eliminar();

                   if(aux!=NULL){
                       cout<<"----------------------Paso "<<pasos<<"-----------------------------"<<endl<<endl;
                       pasos++;
                   pagos.EncolarPagos((*aux).idCl,(*aux).idCa);
                   cout<<"El cliente "<<(*aux).idCl<<" y carreta con numero "<<(*aux).idCa<<" ingresa a cola de pagos."<<endl<<endl;
                       }
               }else{
     //proceso de cajas
               if(Listacaja.Disponible()){
                   NodoC* aux=compras.eliminar();
                   if(aux!=NULL){
                   Nodo * temp=new Nodo((*aux).idCl,(*aux).idCa);
                   Listacaja.Modificar(temp);
                   }
               }
               }
}else{
           break;
               }


           }



           if(pagos.size()==0){
           //cliente siendo atendido
           NodoDoble *aux=Listacaja.Inicio;
           //aqui se encicla

          while(aux!=NULL){
             Nodo* nodo= Listacaja.TiempoServicio(aux);



             if(nodo!=NULL)
             {//el cliente fue atendido
                 cout<<"----------------------Paso "<<pasos<<"-----------------------------"<<endl<<endl;
                pasos++;
                 cout<<"El cliente "<<(*nodo).id<<" ha sido atendido"<<endl<<endl;

                 //colocar en pila las carretas
              int r=1+rand()%(3-1);
              if(r==1){

                  cout<<"La carreta con id: "<<(*nodo).carretaId<<" ha sido dejada en la pila 1"<<endl<<endl;
                  pila1.push((*nodo).carretaId);
              }else{

                  cout<<"La carreta con id: "<<(*nodo).carretaId<<" ha sido dejada en la pila 2"<<endl<<endl;
                  pila2.push((*nodo).carretaId);
              }
              cout<<"El cliente con id: "<<(*nodo).id<<" ha salido del sistema."<<endl<<endl;

              turno++;
             }
             if(turnos==turno){
                 turno=0;
                 //funciones para generar la imagen con los graficos
                 string TextoGraph="digraph{";
                TextoGraph+=pila1.Graficar("Pila1")+pila2.Graficar("Pila2")+Espera.Graficar("ColaEspera")+compras.Graficar("Compras")+pagos.GraficarPagos("Pagos")+Listacaja.Graficar("Cajas")+"}";
                 ofstream archivo("grafica.txt",ios::trunc);
                 archivo<<TextoGraph;
                 archivo.close();
                 system("dot -Tpng grafica.txt -o grafica.png");
                 system("grafica.png");

             }
               aux=aux->siguiente;
           }


          }else {


           if(pagos.size()!=0){
           while(Listacaja.Disponible()){

                  if(pagos.cabeza!=NULL){
                      Nodo* aux=pagos.Desencolar();

               Listacaja.Modificar(aux);
                  }else{
                      break;
                  }
           }
           //cliente siendo atendido
           NodoDoble *aux=Listacaja.Inicio;

           while(aux!=NULL){
             Nodo* nodo= Listacaja.TiempoServicio(aux);
             if(nodo!=NULL){
             //el cliente fue atentido
 cout<<"--------------------------Paso "<<pasos<<"-------------------"<<endl<<endl;
             cout<<"El cliente "<<(*nodo).id<<" ha sido atendido"<<endl<<endl;
              //colocar en pila las carretas
              int r=1+rand()%(3-1);
              if(r==1){

                  cout<<"La carreta con id: "<<(*nodo).carretaId<<" ha sido dejada en la pila 1"<<endl<<endl;
                  pila1.push((*nodo).carretaId);
              }else{

                  cout<<"La carreta con id: "<<(*nodo).carretaId<<" ha sido dejada en la pila 2"<<endl<<endl;
                  pila2.push((*nodo).carretaId);
              }
              cout<<"El cliente con id: "<<(*nodo).id<<" ha salido del sistema."<<endl<<endl;

              turno++;
             }
             pasos++;
             if(turnos==turno){
                 turno=0;
                 //funciones para generar la imagen con los graficos
                 string TextoGraph="Digraph d{";
                 TextoGraph+=pila1.Graficar("Pila1")+pila2.Graficar("Pila2")+Espera.Graficar("ColaEspera")+compras.Graficar("Compras")+pagos.GraficarPagos("Pagos")+Listacaja.Graficar("Cajas")+"}";
                 ofstream archivo("grafica.txt",ios::trunc);
                 archivo<<TextoGraph;
                 archivo.close();
                 system("dot -Tpng grafica.txt -o grafica.png");
                 system("grafica.png  ");




             }
               aux=aux->siguiente;
           }
           }
           }

}

           //volver a pedir clientes
           int opcion=0;
           printf( "Ingrese cualquiera de las opciones:\n" );
           cout<<"1. Agregar clientes a cola de espera."<<endl;
           cout<<"2. Graficar."<<endl;
           cout<<"Oprima cualquier otro numero para finalizar la ejecución del programa."<<endl;
           cin>>opcion;
           if(opcion==1){
               cout<<"Ingresa la cantidad de clientes que quiere agregar a la cola de espera."<<endl;
               cin>>numEspera;
               Espera.tam=numEspera;
               printf( "Has tecleado el numero %i\n", numEspera );
               printf("\n");
           }else if(opcion==2){
               string TextoGraph="Digraph d{";
               TextoGraph+=pila1.Graficar("Pila1")+pila2.Graficar("Pila2")+Espera.Graficar("ColaEspera")+compras.Graficar("Compras")+pagos.GraficarPagos("Pagos")+Listacaja.Graficar("Cajas")+"}";
               ofstream archivo("grafica.txt",ios::trunc);
               archivo<<TextoGraph;
               archivo.close();
               system("dot -Tpng grafica.txt -o grafica.png");
               system("grafica.png  ");

               cout<<"Si desea continuar, ingrese la cantidad de clientes que quiere agregar a la cola de espera."<<endl<<"Oprima 0 en caso contrario."<<endl;
               cin>>numEspera;
               Espera.tam=numEspera;
               printf( "Has tecleado el numero %i\n", numEspera );
               printf("\n");
               if(numEspera==0){
                   break;
               }
           }else{
               break;
           }
           if(!pagos.isEmpty()){
               pagos.deleteAll();
           }
           if(compras.Inicio!=NULL){
               compras.deleteAll();
           }


           }
    return a.exec();
}
