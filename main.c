#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTOS 50
#define MAX_CODIGO 5
#define MAX_DESCRIPCION 30
#define MAX_TICKET 100
#define MAX_LINEAS_TICKET 10

typedef struct {
        int dia;
        int mes;
        int ano;
        int hora;
	int minuto;
} TFecha;

typedef struct {
	char codigo[MAX_CODIGO];
	char descripcion[MAX_DESCRIPCION];
	int stock;
	int stock_minimo;
	float precio;
	int descuento;
} TProducto;

typedef struct {
	TProducto *producto;
	int unidades_vendidas;
} TLineas;

typedef struct {
	int codigo_ticket[MAX_TICKET];
	TFecha fecha;
	float importe_total;
	int lineas_ticket[MAX_LINEAS_TICKET];
} TTicket;

int verificarCodigo(const char *codigo); //Verifica el input del usuario, NO si el codigo existe. De eso se ocupa esCodigo.
			   
int esCodigo(TProducto productos[], int num_productos, const char *codigo);

void posicionProducto(TProducto productos[], int num_productos, int *posicion, const char *codigo); 

int esDescripcion(TProducto productos[], int num_productos, const char *descripcion);

void buscarProducto(TProducto productos[], int num_productos, const char *codigo);

void altaProducto(TProducto productos[], int *num_productos);

void eliminarProducto(TProducto productos[], int *num_productos, int posicion);

void bajaProducto(TProducto productos[], int *num_productos);

//void modificarProducto(TProducto, int, char);

//void crearTicket(TProducto, char);

//void buscarTicket(TProducto, char);	

//void comprobarStock(TProducto);

int main() {
	int eleccion;
        int num_productos = 0;
        int salir = 0;

        TProducto productos[MAX_PRODUCTOS];

        do {
                printf("Seleccione una opcion:\n");
                printf("1 - Dar alta producto:\n");
                printf("2 - Dar baja producto:\n");
                printf("3 - Modificar producto:\n");
                printf("4 - Crear tique:\n");
                printf("5 - Buscar tique:\n");
                printf("6 - Comprobar stock:\n");
                printf("Introduzca otra tecla para salir\n");
                scanf(" %d", &eleccion);

                switch (eleccion) {
                        case (1):
                                altaProducto(productos, &num_productos);
                                break;
                        case (2):
                                bajaProducto(productos, &num_productos);
                                break;
                        case (3):
                                break;
                        case (4):
                                break;
                        case (5):
                                break;
                        case (6):
                                break;
                        default:
                                printf("Hasta la proxima!\n");
                                salir = 1;
                }
        } while(!salir);
	
	return 0;
}

int verificarCodigo(const char *codigo) {
	int es_valido = 1;
	int letras = 0;
	int digitos = 0;
	
	if (strlen(codigo) != 4) {
		es_valido = 0;
	}

	for (int i = 0; codigo[i] != '\0'; i++) {
		if (isalpha(codigo[i])) {
			letras++;
		} else if (isdigit(codigo[i])) {
			digitos++;
		} else {
			es_valido = 0;
		}
	}

	if (letras != 3 || digitos != 1) {
		es_valido = 0;
	}

	return es_valido;
}

int esCodigo(TProducto productos[], int num_productos, const char *codigo) {
	int es_codigo = 1;
	
	for (int i = 0; i < num_productos; i++) {
		if (strcmp(productos[i].codigo, codigo) == 0) {
			es_codigo = 0;
		}
	}	

	return es_codigo;
}

void posicionProducto(TProducto productos[], int num_productos, int *posicion, const char *codigo) {
        for (int i = 0; i < num_productos; i++) {
                if (strcmp(productos[i].codigo, codigo) == 0) {
                        *posicion = i;
                }
        }
}

int esDescripcion(TProducto productos[], int num_productos, const char *descripcion) {
        int es_descripcion = 1;

        for (int i = 0; i < num_productos; i++) {
                if (strcmp(productos[i].descripcion, descripcion) == 0) {
                        es_descripcion = 0;
                }
        }

        return es_descripcion;
}

void buscarProducto(TProducto productos[], int num_productos, const char *codigo) {
	int encontrado = 0;
	
	for (int i = 0; i < num_productos; i++) {
		if (strcmp(productos[i].codigo, codigo) == 0) {
			printf("Código: %s\n", productos[i].codigo);
            		printf("Descripción: %s\n", productos[i].descripcion);
           		printf("Stock: %d\n", productos[i].stock);
            		printf("Stock mínimo: %d\n", productos[i].stock_minimo);
            		printf("Precio: %.2f\n", productos[i].precio);
            		printf("Descuento: %d%%\n", productos[i].descuento);
			encontrado = 1;
		} 
	}	
	
	if (!encontrado) {
		printf("Producto no encontrado.\n");
	}
}

void altaProducto(TProducto productos[], int *num_productos) {
	if (*num_productos < MAX_PRODUCTOS) {
		TProducto nuevo_producto;
		
		int codigo_correcto, descripcion_correcta;

		do {
			printf("Ingrese el codigo del producto: ");
			scanf(" %s", nuevo_producto.codigo);	

			codigo_existe = esCodigo(productos, *num_productos, nuevo_producto.codigo);
                        codigo_correcto = verificarCodigo(nuevo_producto.codigo);

                        if (!codigo_existe) {
                                printf("El codigo ya existe.\n");
                        } else if (!codigo_correcto) {
                                printf("El codigo no tiene el formato correcto, recuerde, tres letras y un numero.\n");
                        }
		} while(!codigo_correcto); 

		do {
                        printf("Ingrese la descripcion del producto: ");
			scanf(" %[^\n]", nuevo_producto.descripcion);

                        descripcion_correcta = esDescripcion(productos, *num_productos, nuevo_producto.descripcion);
                        if (!descripcion_correcta) {
                                printf("La descripcion ya existe.\n");
                        }
                } while(!descripcion_correcta);

		printf("Ingrese las unidades existentes: ");
		scanf(" %d", &nuevo_producto.stock);

		printf("Ingrese la cantidad minima de existencias: ");
		scanf(" %d", &nuevo_producto.stock_minimo);

		printf("Ingrese el precio unitario: ");
		scanf(" %f", &nuevo_producto.precio);

		printf("Ingrese el descuento: ");
		scanf(" %d", &nuevo_producto.descuento);

		productos[*num_productos] = nuevo_producto;

		(*num_productos)++;
	} else {
		printf("No se pueden anadir mas productos, antes elimine uno.");
	}
}

void eliminarProducto(TProducto productos[], int *num_productos, int posicion) {
	if (posicion == *num_productos - 1) {
		(*num_productos)--;
		printf("Producto eliminado con exito.\n");
	} else {
		for (int i = posicion; i < *num_productos - 1; i++) {
			productos[i] = productos[i + 1];
		}
		(*num_productos)--;
		printf("Producto eliminado con exito.\n");
	}
}

void bajaProducto(TProducto productos[], int *num_productos) {
	TProducto producto;

	printf("Ingrese el codigo del producto: ");
	scanf(" %s", producto.codigo);
	
	int es_codigo = esCodigo(productos, *num_productos, producto.codigo);
	
	if (es_codigo) {
		printf("El producto de codigo %s no existe.\n", producto.codigo);	
	} else {
		char eleccion;
		buscarProducto(productos, *num_productos, producto.codigo);
		printf("Desea eliminar este producto? (S/s para confirmar): ");
		scanf(" %c", &eleccion);

		if (eleccion == 'S' || eleccion == 's') {
			int posicion = 0;
			posicionProducto(productos, *num_productos, &posicion, producto.codigo);
			eliminarProducto(productos, num_productos, posicion);			
		} 
	}
}
