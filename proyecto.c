#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODUCTOS 50
#define MAX_DESCRIPCION 30
#define MAX_CODIGO 5
#define MAX_TICKETS 100
#define MAX_LINEAS 10

//Establecer la Fecha del ticket
typedef struct{
    int year;
    int month;
    int day;
} Tfecha;

typedef struct{
    int hora;
    int minuto;
} Thora;


//Propiedades del producto en venta
typedef struct{
    char codigoProducto[MAX_CODIGO];
    char descripcion[MAX_DESCRIPCION];
    int stock;
    int minStock;
    float precioUnidad;
    float descuento;
} Tproducto;

//Propiedades de la Linea de Ticket
typedef struct{
    char codigoProducto[MAX_CODIGO];
    Tproducto producto;
    float precioUnidad;
    int unidadesVendidas;
    float descuentoAplicado;

} TLineaTicket;

//Propiedades del ticket a rellenar
typedef struct{
    char codigo[MAX_CODIGO];
    TLineaTicket lineasTicket[10];
    int cantidadLineas;
    float importeTotal;
    Tfecha fecha;
    Thora hora;

} Tticket;


void establecerFecha(int *year, int *month, int *day){

    printf("\nEn que año se realiza la compra?");
    scanf("%d", year);

    do{
        printf("\nEn que mes se realiza la compra?");
        scanf("%d", month);
    }while(*month < 0 || *month > 12);

   if(*month == 8 || *month == 10 || *month == 12 || (*month % 2 != 0 && *month < 9)){
        do{
            printf("\nEn que dia se realiza la compra?");
            scanf("%d", day);
        }while(*day < 0 || *day > 31);
    }
    else if(*month == 2){
        if(*year % 4 == 0){
            do{
                printf("\nEn que dia se realiza la compra?");
                scanf("%d", day);
            }while(*day < 0 || *day > 29);
        }
        else{
            do{
                printf("\nEn que dia se realiza la compra?");
                scanf("%d", day);
            }while(*day < 0 || *day > 28);
        }
        
    }
    else{
        do{
            printf("\nEn que dia se realiza la compra?");
            scanf("%d", &*day);
        }while(*day < 0 || *day > 30);
    }

   


}


int buscarCodigoTicket(Tticket tickets[MAX_TICKETS], int numTickets, char codigo[MAX_CODIGO]){

    int i = 0;
    bool encontrado = false;


    for(i=0; i < numTickets && !encontrado; i++){
        if(strcmp(tickets[i].codigo, codigo) == 0){
            encontrado = true;

        }
    }
    
    if(!encontrado){
        i=-1;
    }
    else{
        i -= 1;
    }

    return i;
}


//Busca si existe o no el codigo y te devuelve el indice si existe
int buscarCodigo(Tproducto productos[MAX_PRODUCTOS], int numProductos, char codigo[MAX_CODIGO]){

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
    else{
        i -= 1;
    }

    return i;
}

//Busca si existe o no la descripcion y te devuelve el indice si existe
int buscarDescripcion(Tproducto productos[MAX_PRODUCTOS], int numProductos, char descripcion[MAX_DESCRIPCION]){

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
    else{
        i -= 1;
    }

    return i;
}


//Modulo que da de alta un producto nuevo en la lista
void altaProducto(Tproducto productos[MAX_PRODUCTOS], int *numProductos){

    if(*numProductos < MAX_PRODUCTOS){

        Tproducto nuevoProducto;



        do{

            printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): ");
            scanf(" %[^\n]", nuevoProducto.codigoProducto);

        }while(buscarCodigo(productos, *numProductos, nuevoProducto.codigoProducto) != -1 || strlen(nuevoProducto.codigoProducto) != 4);
    

  

    
        do{

            printf("\nIntroduce la descripcion del producto (30 caracteres maximo): ");
            scanf(" %[^\n]", nuevoProducto.descripcion);

        }while(buscarDescripcion(productos, *numProductos, nuevoProducto.descripcion) != -1);
    
    
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
    else{
        printf("\nNo se pueden añadir mas productos, primero da de baja algun producto!");
    }

   
    

}

//Modulo que da de baja un producto si ese producto existe
void bajaProducto(Tproducto productos[MAX_PRODUCTOS], int *numProductos){

    if(*numProductos == 0){
        printf("No hay ningun producto disponible para dar de baja. Primero da de alta un producto");
    }
    else{

        int indice = 0;
        char confirmacion;
        char codigo[MAX_CODIGO];

        do{
            printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): \n");
            scanf(" %[^\n]", codigo);
        }while(strlen(codigo) != 4);

        indice = buscarCodigo(productos, *numProductos, codigo);

        if(indice != -1){
            printf("\nLas propiedades del producto a eliminar son las siguientes: ");
            printf("\nDescripcion: %s", productos[indice].descripcion);
            printf("\nStock Disponible: %d", productos[indice].stock);
            printf("\nStock Minimo: %d", productos[indice].minStock);
            printf("\nPrecio por unidad: %.2f€", productos[indice].precioUnidad);
            printf("\nDescuento aplicado: %.2f%%\n\n", productos[indice].descuento);

            do{
                printf("\nESTAS SEGURO QUE QUIERES ELIMINAR EL PRODUCTO(s/n): ");
                scanf(" %c", &confirmacion);
            }while(confirmacion != 's' && confirmacion != 'n');

            if(confirmacion == 'n'){
                printf("\nOPERACION CANCELADA\n");
            }
            else{
                
                int i = 0;
                for(i=indice; i < *numProductos-1; i++){
                    productos[i] = productos[i+1];
                }
                (*numProductos)--;
                
            }

        }
    }
}


//Modulo que permite modificar las propiedades de un producto
void modificarProducto(Tproducto productos[MAX_PRODUCTOS], int numProductos){

    char codigo[MAX_CODIGO];
    int seleccion;
    int indice;

    do{

        printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): \n");
        scanf(" %[^\n]", codigo);

    }while(strlen(codigo) != 4);

    indice = buscarCodigo(productos, numProductos, codigo);

    if(indice != -1){
        printf("\nLas propiedades de este producto son: ");
        printf("\nDescripcion: %s", productos[indice].descripcion);
        printf("\nStock Disponible: %d", productos[indice].stock);
        printf("\nStock Minimo: %d", productos[indice].minStock);
        printf("\nPrecio por unidad: %.2f€", productos[indice].precioUnidad);
        printf("\nDescuento aplicado: %.2f%%\n\n", productos[indice].descuento);


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


//Modulo que permite ver las propiedades de un producto que existe sin poder modificarlo
void buscarProducto(Tproducto productos[MAX_PRODUCTOS], int numProductos){

    char codigo[MAX_CODIGO];
    int indice = 0;

    do{

        printf("\nIntroduce el codigo del producto (3 numeros y 1 letra): \n");
        scanf(" %[^\n]", codigo);

    }while(strlen(codigo) != 4);

    indice = buscarCodigo(productos, numProductos, codigo);

    if(indice != -1){
        printf("\nLas propiedades de este producto son: ");
        printf("\nDescripcion: %s", productos[indice].descripcion);
        printf("\nStock Disponible: %d", productos[indice].stock);
        printf("\nStock Minimo: %d", productos[indice].minStock);
        printf("\nPrecio por unidad: %.2f€", productos[indice].precioUnidad);
        printf("\nDescuento aplicado: %.2f%%\n\n", productos[indice].descuento);
        printf("\n\nPulsa ENTER para volver al menu\n");
        getchar(); getchar();
    }
    else{
        printf("\nEste producto no existe!");
    }

}

void crearTicket(Tticket tickets[MAX_TICKETS], Tproducto productos[MAX_PRODUCTOS], int *numTickets, int numProductos){

    if((*numTickets) >= 100){
        printf("\nYa hay 100 tickets creados, primero elimine alguno para crear uno nuevo");
    }
    else{

        Tticket ticketNuevo;
        int numLineas = 0;
        bool addLines = true;
        char confirmacion;
        char codigoTicket[MAX_CODIGO];


         
        do{

            printf("\nIntroduce el codigo del ticket (3 numeros y 1 letra): ");
            scanf(" %[^\n]", codigoTicket);

        }while(buscarCodigoTicket(tickets, *numTickets, codigoTicket) != -1 || strlen(codigoTicket) != 4);


        while(addLines && numLineas <= MAX_LINEAS){
            
            TLineaTicket nuevaLinea;
            char codigoProducto[MAX_CODIGO];
            int indice = 0;
            
            do{
                printf("\nIntroduce el codigo del producto a añadir (3 numeros y 1 letra): \n");
                scanf(" %[^\n]", codigoProducto);
            }while(strlen(codigoProducto) != 4);

            indice = buscarCodigo(productos, numProductos, codigoProducto);

            if(indice != -1){

                strcpy(nuevaLinea.codigoProducto, codigoProducto);
                nuevaLinea.producto = productos[indice];
                nuevaLinea.precioUnidad = productos[indice].precioUnidad;

               do{
                    printf("\nCuantas unidades se quieren vender (para cancelar introduzca 0): ");
                    scanf("%d", &nuevaLinea.unidadesVendidas);
               }while(nuevaLinea.unidadesVendidas > productos[indice].stock);

               if(nuevaLinea.unidadesVendidas != 0){

                    strcpy(ticketNuevo.codigo, codigoTicket);
                    productos[indice].stock -= nuevaLinea.unidadesVendidas;
 
                    if(productos[indice].descuento <= 0){
                        nuevaLinea.descuentoAplicado = productos[indice].precioUnidad * nuevaLinea.unidadesVendidas;
                        ticketNuevo.importeTotal += productos[indice].precioUnidad * nuevaLinea.unidadesVendidas;

                    }
                    else{
                        nuevaLinea.descuentoAplicado = (productos[indice].precioUnidad * nuevaLinea.unidadesVendidas) * (productos[indice].descuento/100);
                        ticketNuevo.importeTotal += (productos[indice].precioUnidad * nuevaLinea.unidadesVendidas) * (productos[indice].descuento/100);

                    }

                    ticketNuevo.lineasTicket[numLineas] = nuevaLinea;

                    
                   
                    numLineas++;


                    if(numLineas < 10){
                    do{
                        printf("\nQuiere crear otra linea? (s/n)");
                        scanf(" %c", &confirmacion);
                    }while(confirmacion != 's' && confirmacion != 'n');

                        if(confirmacion == 'n'){
                            addLines = false;
                            do{
                                establecerFecha(&ticketNuevo.fecha.year, &ticketNuevo.fecha.month, &ticketNuevo.fecha.day);
                                printf("\nIntroduce hora y minuto de compra (cada dato espaciado):");
                                scanf("%d %d", &ticketNuevo.hora.hora, &ticketNuevo.hora.minuto);
                            }while((ticketNuevo.hora.hora > 23 || ticketNuevo.hora.hora < 0) || (ticketNuevo.hora.minuto > 60 || ticketNuevo.hora.minuto < 0));
                            
                            ticketNuevo.cantidadLineas = numLineas;
                            tickets[*numTickets] = ticketNuevo;
                            (*numTickets)++;
                            
                        }
                    }
               }
               else{
                    if(numLineas < 10){
                    do{
                        printf("\nQuiere crear una linea nueva? (s/n)");
                        scanf(" %c", &confirmacion);
                    }while(confirmacion != 's' && confirmacion != 'n');

                        if(confirmacion == 'n'){
                            addLines = false;
                            if(numLineas > 0){
                                do{
                                    establecerFecha(&ticketNuevo.fecha.year, &ticketNuevo.fecha.month, &ticketNuevo.fecha.day);
                                    printf("\nIntroduce hora y minuto de compra (cada dato espaciado):");
                                    scanf("%d %d", &ticketNuevo.hora.hora, &ticketNuevo.hora.minuto);
                                }while((ticketNuevo.hora.hora > 23 || ticketNuevo.hora.hora < 0) || (ticketNuevo.hora.minuto > 60 || ticketNuevo.hora.minuto < 0));
                                ticketNuevo.cantidadLineas = numLineas;
                                tickets[*numTickets] = ticketNuevo;
                                (*numTickets)++;
                        
                            }
                        }
                    }
               }           
            }
        }        
    }
}

void buscarEliminarTicket(Tticket tickets[MAX_TICKETS], int *numTickets){
    
    char codigoTicket[MAX_CODIGO];
    char eleccion;
    int indice, i, j = 0;

    do{

        printf("\nIntroduce el codigo del ticket (3 numeros y 1 letra): ");
        scanf(" %[^\n]", codigoTicket);

    }while(strlen(codigoTicket) != 4);

    indice = buscarCodigoTicket(tickets, *numTickets, codigoTicket);

    if(indice != -1){
        printf("\nTICKET %s\n", tickets[indice].codigo);
        printf("\nFECHA: %d-%d-%d", tickets[indice].fecha.day, tickets[indice].fecha.month, tickets[indice].fecha.year);
        printf("\nHORA DE COMPRA  %d:%d", tickets[indice].hora.hora, tickets[indice].hora.minuto);
        printf("\n---------------------------");

        for(i=0; i < tickets[indice].cantidadLineas; i++){
            printf("\n\"%s\"-%s | Precio Ud: %.2f€ | Descuento: %.2f%% | Uds. Vendidas: %d",tickets[indice].lineasTicket[i].codigoProducto, tickets[indice].lineasTicket[i].producto.descripcion, tickets[indice].lineasTicket[i].precioUnidad, tickets[indice].lineasTicket[i].producto.descuento, tickets[indice].lineasTicket[i].unidadesVendidas);
        }

        printf("\nIMPORTE TOTAL: %.2f€\n\n", tickets[indice].importeTotal);

        
        do{
            printf("\n\nQUE DESEA HACER:");
            printf("\nM-Volver Al Menu");
            printf("\nE-Eliminar Ticket");
            scanf(" %c", &eleccion);
        }while(eleccion != 'M' && eleccion != 'E');

        if(eleccion == 'E'){
            for(j = indice; j<*numTickets-1; j++){
                tickets[j] = tickets[j+1];
            }
            (*numTickets)--;
            
            printf("\nTicket Eliminado con exito!\n\n");
        }


    }
    else{
        printf("\nEste ticket no existe!\n");
    }
       
}

void comprobarStock(Tproducto productos[MAX_PRODUCTOS], int numProductos){
    int i, count = 0;

    for(i=0; i < numProductos; i++){
        if(productos[i].stock <= productos[i].minStock){
            printf("\n------------------------------------------");
            printf("\n\"%s\", %s", productos[i].codigoProducto, productos[i].descripcion);
            printf("\nStock Disponible: %d", productos[i].stock);
            printf("\nStock Minimo Indispensable: %d", productos[i].minStock);
            printf("\nPrecio Unitario: %.2f€", productos[i].precioUnidad);
            printf("\nDescuento Aplicable: %.2f%%", productos[i].descuento);
            printf("\n------------------------------------------");
            count++;
        }
        printf("\n");
    }
    if(count == 0){
        printf("\nTienes suficiente Stock para todos los productos que tienes\n\n");
    }
    else{
        printf("\nLos productos pendientes de pedido al proveedor son %d\n\n", count);
    }


}

int main(){

    int seleccion;
    bool isExit = false;
    int numProductos, numTickets = 0;

    Tproducto productos[MAX_PRODUCTOS] = {0};
    Tticket tickets[MAX_TICKETS] = {0};

    
    

    while(!isExit){
        printf("\n------------------------------");
        printf("\nSelecciona una opcion: ");
        printf("\n1-Dar de Alta un Producto: ");
        printf("\n2-Dar de Baja un Producto");
        printf("\n3-Modificar Producto");
        printf("\n4-Buscar Producto por Codigo");
        printf("\n5-Crear Ticket Nuevo");
        printf("\n6-Buscar o Eliminar Ticket");
        printf("\n7-Comprobar Stock Productos");
        printf("\n0-Salir Del Programa");
        printf("\n------------------------------\n");
        scanf("%d", &seleccion);

        switch(seleccion){
            case(1):
                altaProducto(productos, &numProductos);
                break;
            case(2):
                bajaProducto(productos, &numProductos);
                break;
            case(3):
                modificarProducto(productos, numProductos);
                break;
            case(4):
                buscarProducto(productos, numProductos);
                break;
            case(5):
                crearTicket(tickets, productos, &numTickets, numProductos);
                break;
            case(6):
                buscarEliminarTicket(tickets, &numTickets);
                break;
            case(7):
                comprobarStock(productos, numProductos);
                break;
            default:
                printf("\nHasta la proxima!\n");
                isExit = true;
    }
    }

    return 0;
   
}  



