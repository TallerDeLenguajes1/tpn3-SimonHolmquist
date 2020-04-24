#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define forn(i,n) for(int i=0;i<n;i++)

using namespace std;

char *TiposProductos[] = {"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

struct Producto {
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
};

struct Cliente {
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    Producto *Productos; //El tamaño de este arreglo depende de la variable
    // "CantidadProductosAPedir"
};
/*
3. A medida que se dé de alta cada cliente, Generar aleatoriamente la cantidad de
productos asociados al cliente y sus características. Ej: producto cargado nro. 2
Producto
{
 ProductoID=2
 Cantidad = 1;
 *TipoProducto = “Snack”;
PrecioUnitario = 100;
}
4. Implemente una función que calcule el costo total de un producto. Esta función
debe recibir como parámetro el producto y devolver el resultado de calcular la
Cantidad por el PrecioUnitario.
5. Mostrar por pantalla todo lo cargado. Incluyendo un total a pagar por cliente
(sumatoria del costo de todos los productos)
*/
void imprimirTitulo(char *s){
    int n = strlen(s)+4;
    forn(i,n) cout<<'*';
    cout<<"\n* "<<s<<" *\n";
    forn(i,n) cout<<'*';
    cout<<"\n\n";
}

void cargarProductos(Producto *producto, int cant){
    forn(i,cant)
    {
        (producto+i)->ProductoID = i+1;
        (producto+i)->Cantidad = rand()%11 + 1;
        (producto+i)->PrecioUnitario = rand()%101 + 10;
        (producto+i)->TipoProducto = TiposProductos[rand()%6];
    }
}

void cargarClientes(Cliente * cliente, int cant){
    forn(i,cant)
    {
        char s[100];//String auxiliar
        
        cliente[i].ClienteID = i + 1;

        cout<<"Ingrese el nombre del cliente N°"<<i+1<<": ";
        
        cin>>s;

        (cliente[i].NombreCliente)=(char *)malloc(sizeof(s)*strlen(s));
        strcpy((cliente[i].NombreCliente),s);

        cliente[i].CantidadProductosAPedir = rand()%5 + 1;
        cliente[i].Productos=(Producto *)malloc(sizeof(Producto)*cliente[i].CantidadProductosAPedir);
        cargarProductos(cliente[i].Productos,cliente[i].CantidadProductosAPedir);
    }
}

float precioProducto(Producto *producto){
    return (*producto).Cantidad*(*producto).PrecioUnitario;
}

float mostrarProductos(Producto *producto, int cant){
    float suma = 0;
    forn(i,cant)
    {
        cout<<"\n\nID del producto: "<<producto[i].ProductoID
            <<"\nCantidad: "<<producto[i].Cantidad
            <<"\nTipo: "<<producto[i].TipoProducto;
        cout<<fixed<<"\nPrecio unitario: $"<<producto[i].PrecioUnitario;
        suma+=precioProducto(&producto[i]);
    }
    return suma;
}

void mostrarClientes(Cliente *cliente, int cant){
    float Total_cliente;
    forn(i, cant)
    {
        cout<<"\nID del Cliente: "<<cliente[i].ClienteID
            <<"\nNombre: "<<cliente[i].NombreCliente
            <<"\nCandidad de productos a pedir: "<<cliente[i].CantidadProductosAPedir;
        Total_cliente = mostrarProductos(cliente[i].Productos,cliente[i].CantidadProductosAPedir);
        cout<<fixed<<"\nTotal: $"<<Total_cliente;
        cout<<'\n';
    }
}

int main(int argc, char const *argv[]){
    int cantidadClientes;
    cout.precision(2);
    imprimirTitulo("Carga de productos de preventistas");
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", &cantidadClientes);
    printf("\n");
    while(cantidadClientes<0){
        printf("La cantidad de clientes ingresada es incorrecta. Por favor ingrese nuevamente: ");
        scanf("%d", &cantidadClientes);
        printf("\n");
    }
    Cliente *pClientes;
    pClientes = (Cliente *)malloc(sizeof(Cliente)*cantidadClientes);
    cargarClientes(pClientes, cantidadClientes);
    mostrarClientes(pClientes, cantidadClientes);
    free(pClientes);
    getchar();
    return 0;
}
