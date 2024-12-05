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
    return i-1;
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
    return i-1;
}

void altaProducto(Tproducto productos[MAX_PRODUCTOS], int *numProductos){

    Tproducto nuevoProducto;



    do{

        printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): ");
        scanf(" %[^\n]", nuevoProducto.codigoProducto);

    }while(buscarCodigo(productos, *numProductos, nuevoProducto.codigoProducto) != -2 || strlen(nuevoProducto.codigoProducto) != 4);
    

  

    
    do{

        printf("\nIntroduce la descripcion del producto (30 caracteres maximo): ");
        scanf(" %[^\n]", nuevoProducto.descripcion);

    }while(buscarDescripcion(productos, *numProductos, nuevoProducto.descripcion) != -2);
    
    
    printf("\nIntroduce la cantidad de Stock: ");
    scanf("%d", &nuevoProducto.stock);

    printf("\nIntroduce el stock minimo: ");
    scanf("%d", &nuevoProducto.minStock);

    printf("\nIntroduce el precio por unidad: ");
    scanf("%f", &nuevoProducto.precioUnidad);

    printf("\nIntroduce el descuento que quiera aplicarle: ");
    scanf("%f", &nuevoProducto.descuento);

    productos[*numProductos] = nuevoProducto;
    (*numProductos)++;
    

}


void modificarProducto(Tproducto productos[MAX_PRODUCTOS], int numProductos){

    char codigo[5];
    int seleccion;

    do{

        printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): \n");
        scanf(" %[^\n]", codigo);

    }while(strlen(codigo) != 4);

    int indice = buscarCodigo(productos, numProductos, codigo);

    if(buscarCodigo(productos, numProductos, codigo) != -2){
        printf("\nLas propiedades de este producto son: ");
        printf("\nDescripcion: %s", productos[indice].descripcion);
        printf("\nStock Disponible: %d", productos[indice].stock);
        printf("\nStock Minimo: %d", productos[indice].minStock);
        printf("\nPrecio por unidad: %f", productos[indice].precioUnidad);
        printf("\nDescuento aplicado: %f\n\n", productos[indice].descuento);


        printf("\nQue elemento quieres modificar: ");
        printf("\n1-Descripcion");
        printf("\n2-Stock Disponible");
        printf("\n3-Stock Minimo:");
        printf("\n4-Precio");
        printf("\n5-Descuento aplicado");
        printf("\n0-Salir al menú");

        scanf("%d", &seleccion);

        switch(seleccion){
            case(1):
                printf("\nIntroduce la descripcion del producto (30 caracteres maximo): ");
                scanf(" %[^\n]", productos[indice].descripcion);
                break;
            case(2):
                printf("\nIntroduce la cantidad de Stock: ");
                scanf("%d", &productos[indice].stock);
                break;
            case(3):
                printf("\nIntroduce el stock minimo: ");
                scanf("%d", &productos[indice].minStock);
                break;
            case(4):
                printf("\nIntroduce el precio por unidad: ");
                scanf("%f", &productos[indice].precioUnidad);
                break;
            case(5):
                printf("\nIntroduce el descuento que quiera aplicarle: ");
                scanf("%f", &productos[indice].descuento);
                break;
            default:
                printf("\n");
                
                

        }
    }
    else{
        printf("Este producto no existe, primero dalo de alta\n");
    }
    

}



int main(){

    int seleccion;
    bool isExit = false;

    Tproducto productos[MAX_PRODUCTOS];
    Tproducto producto1;
    strcpy(producto1.codigoProducto, "123A");
    strcpy(producto1.descripcion, "boligrafo azul");
    productos[0] = producto1;
    int numProductos = 1;

    while(!isExit){
        printf("\nSelecciona una opcion: ");
        printf("\n1-Dar Alta Producto: ");
        printf("\n2-Modificar Producto");
        printf("\n0-Salir Del Programa\n");
        scanf("%d", &seleccion);

        switch(seleccion){
            case(1):
                altaProducto(productos, &numProductos);
                break;
            
            case(2):
                modificarProducto(productos, numProductos);
                break;

            default:
                printf("\nHasta la proxima!");
                isExit = true;
    }
    }

    


    return 0;

   
}  

