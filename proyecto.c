#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUCTOS 50

//Establecer la Fecha del ticket
typedef struct{
    int year;
    int month;
    int day;
} Tfecha;

//Propiedades del producto en venta
typedef struct{
    char codigoProducto[5];
    char descripcion[30];
    int stock;
    int minStock;
    float precioUnidad;
    float descuento;
} Tproducto;

//Propiedades de la Linea de Ticket
typedef struct{
    char codigoProducto[5];
    Tproducto producto;
    int unidadesVendidas;
    int descuentoAplicado;

} TLineaTicket;

//Propiedades del ticket a rellenar
typedef struct{
    int codigoTicket;
    float importeTotal;
    int lineasTicket;
    Tfecha fecha;
    int hora;

} Tticket;

int buscarCodigo(Tproducto productos[MAX_PRODUCTOS], int numProductos, char codigo[5]){

    int i = 0;
    bool encontrado = false;


    for(i=0; i < numProductos && !encontrado; i++){
        if(strcmp(productos[i].codigoProducto, codigo) == 0){
            encontrado = true;

        }
    }
    if(!encontrado){
        i=-1;
    }
    return i;
}

int buscarDescripcion(Tproducto productos[MAX_PRODUCTOS], int numProductos, char descripcion[30]){

    int i = 0;
    bool encontrado = false;

    for(i=0; i < numProductos && !encontrado; i++){
        if(strcmp(productos[i].descripcion, descripcion) == 0){
            encontrado = true;
        }
    }

    if(!encontrado){
        i=-1;
    }
    return i;
}

void altaProducto(Tproducto productos[MAX_PRODUCTOS], int *numProductos){

    Tproducto nuevoProducto;



    do{

        printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): ");
        scanf(" %[^\n]", nuevoProducto.codigoProducto);

    }while(buscarCodigo(productos, *numProductos, nuevoProducto.codigoProducto) != -1 || strlen(nuevoProducto.codigoProducto) != 4);
    

    printf("\nIntroduce la descripcion del producto (30 caracteres maximo): ");
    scanf(" %[^\n]", nuevoProducto.descripcion);

    if(buscarDescripcion(productos, *numProductos, nuevoProducto.descripcion) != -1){
        do{

            printf("\nIntroduce la descripcion del producto (30 caracteres maximo): ");
            scanf(" %[^\n]", nuevoProducto.descripcion);

        }while(buscarCodigo(productos, *numProductos, nuevoProducto.codigoProducto) != -1);
    }

    
    printf("\nIntroduce la cantidad de Stock: ");
    scanf("%d", &nuevoProducto.stock);

    printf("\nIntroduce el stock minimo: ");
    scanf("%d", &nuevoProducto.minStock);

    printf("\nIntroduce el precio por unidad: ");
    scanf("%f", &nuevoProducto.precioUnidad);

    printf("\nIntroduce el descuente que quiera aplicarle: ");
    scanf("%f", &nuevoProducto.descuento);

    productos[*numProductos] = nuevoProducto;
    ++(*numProductos);
    

}


void modificarProducto(Tproducto productos[MAX_PRODUCTOS], int numProductos){

    char codigo[5];

    do{

        printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): ");
        scanf(" %[^\n]", codigo);

    }while(strlen(codigo) != 4);

    int indice = buscarCodigo(productos, numProductos, codigo);

    if(buscarCodigo(productos, numProductos, codigo) != -1){
        printf("\nLas propiedades de este producto son: ");
        printf("\nDescripcion: %s", productos[indice].descripcion);
        printf("\nStock Disponible: %d", productos[indice].stock);
        printf("\nStock Minimo: %d", productos[indice].minStock);
        printf("\nPrecio por unidad: %f", productos[indice].precioUnidad);
        printf("\nDescuento aplicado: %f", productos[indice].descuento);
    }
    else{
        printf("Este producto no existe, primero dalo de alta");
    }
    

}



int main(){


    Tproducto productos[MAX_PRODUCTOS];
    Tproducto producto1;
    strcpy(producto1.codigoProducto, "123A");
    strcpy(producto1.descripcion, "boligrafo azul");
    productos[0] = producto1;
    int numProductos = 1;

    altaProducto(productos, &numProductos);
    modificarProducto(productos, numProductos);

    return 0;

   
}  
