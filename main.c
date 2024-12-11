#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTOS 50
#define MAX_CODIGO 4
#define MAX_DESCRIPCION 30
#define MAX_TICKETS 100
#define MAX_LINEAS_TICKET 10

typedef struct {
        int dia;
        int mes;
        int ano;
        int hora;
	int minuto;
} TFecha;

typedef struct {
	char codigo[MAX_CODIGO + 1];
	char descripcion[MAX_DESCRIPCION + 1];
	int stock;
	int stock_minimo;
	float precio;
	int descuento;
} TProducto;

typedef struct {
	TProducto producto[MAX_PRODUCTOS];
	int unidades_vendidas;
} TLineas;

typedef struct {
	int codigo_ticket;
	TFecha fecha;
	float importe_total;
	int lineas_ticket;
	TLineas lineas[MAX_LINEAS_TICKET];
} TTicket;

int verificarCodigo(const char *codigo); //Verifica el input del usuario, NO si el codigo existe. De eso se ocupa esCodigo.
			   
int esCodigo(TProducto productos[], int num_productos, const char *codigo);

int esTicket(TTicket tickets[], int num_tickets, int codigo);

void posicionProducto(TProducto productos[], int num_productos, int *posicion, const char *codigo); 

int posicionTicket(TTicket tickets[], int num_tickets, int codigo);

int esDescripcion(TProducto productos[], int num_productos, const char *descripcion);

void buscarProducto(TProducto productos[], int num_productos, const char *codigo);

void mostrarTicket(TTicket tickets[], int num_tickets, int codigo);

void altaProducto(TProducto productos[], int *num_productos);

void eliminarProducto(TProducto productos[], int *num_productos, int posicion);

void eliminarTicket(TTicket tickets[], int *num_ticket, int posicion);

void bajaProducto(TProducto productos[], int *num_productos);

void modificarProducto(TProducto productos[], int num_productos);

void crearTicket(TProducto productos[], int num_productos, TTicket tickets[], int *num_tickets);

void buscarTicket(TTicket tickets[], int *num_tickets);	

void comprobarStock(TProducto productos[], int num_productos);

int main() {
	int eleccion;
	int num_productos = 0;
	int num_tickets = 0;
	int salir = 0;

	TProducto productos[MAX_PRODUCTOS];
	TTicket tickets[MAX_TICKETS];
	
	do {
		printf("Seleccione una opcion:\n");
		printf("1 - Dar alta producto:\n");
		printf("2 - Dar baja producto:\n");
		printf("3 - Modificar producto:\n");
		printf("4 - Crear tique:\n");
		printf("5 - Buscar tique:\n");
		printf("6 - Comprobar stock:\n");
		printf("0 - Salir\n");

		if (scanf(" %d", &eleccion) == 1) {
			switch (eleccion) {
				case (1):
					altaProducto(productos, &num_productos);
					break;
				case (2):	
					bajaProducto(productos, &num_productos);
					break;
				case (3):
					modificarProducto(productos, num_productos);
					break;
				case (4):
					crearTicket(productos, num_productos, tickets, &num_tickets);
					break;
				case (5):
					buscarTicket(tickets, &num_tickets);
					break;
				case (6):
					comprobarStock(productos, num_productos);
					break;
				case (0): 
					printf("Hasta la proxima!\n");
					salir = 1;
			}
		} else {
			printf("Introduce un valor valido.\n");
			while(getchar() != '\n');
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

int esTicket(TTicket tickets[], int num_tickets, int codigo) {
        int es_ticket = 1;

        for (int i = 0; i < num_tickets; i++) {
                if (tickets[i].codigo_ticket == codigo) {
                        es_ticket = 0;
                }
        }

        return es_ticket;
}

void posicionProducto(TProducto productos[], int num_productos, int *posicion, const char *codigo) {
        for (int i = 0; i < num_productos; i++) {
                if (strcmp(productos[i].codigo, codigo) == 0) {
                        *posicion = i;
                }
        }
}

int posicionTicket(TTicket tickets[], int num_tickets, int codigo) {
        int posicion_ticket = 0;
	
	for (int i = 0; i < num_tickets; i++) {
                if (tickets[i].codigo_ticket == codigo) {
                        posicion_ticket = i;
                }
        }

	return posicion_ticket;
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

void mostrarTicket(TTicket tickets[], int num_tickets, int codigo) {
        for (int i = 0; i < num_tickets; i++) {
                if (tickets[i].codigo_ticket == codigo) {
                        printf("Código: %d\n", tickets[i].codigo_ticket);
                        printf("Fecha: %s\n", "en_proceso");
                        printf("Importe total: %.2f\n", tickets[i].importe_total);
                        printf("Lineas ticket:  %d\n", tickets[i].lineas_ticket);
                }
        }
}

void altaProducto(TProducto productos[], int *num_productos) {
	if (*num_productos < MAX_PRODUCTOS) {
		TProducto nuevo_producto;
		
		int codigo_correcto, codigo_existe, descripcion_correcta;

		do {
			printf("Ingrese el codigo del producto (3 letras, 1 numero): ");
			scanf("%s", nuevo_producto.codigo);	

			codigo_existe = esCodigo(productos, *num_productos, nuevo_producto.codigo); 
			codigo_correcto = verificarCodigo(nuevo_producto.codigo);

			if (!codigo_existe) {
				printf("El codigo ya existe.\n");
			} else if (!codigo_correcto) {
				printf("El codigo no tiene el formato correcto, recuerde, tres letras y un numero.\n");
			}
		} while(!codigo_existe || !codigo_correcto); 

		do {
                        printf("Ingrese la descripcion del producto: ");
			scanf(" %[^\n]", nuevo_producto.descripcion);

                        descripcion_correcta = esDescripcion(productos, *num_productos, nuevo_producto.descripcion);
                        if (!descripcion_correcta) {
                                printf("La descripcion ya existe.\n");
                        }
                } while(!descripcion_correcta);

		printf("Ingrese las unidades existentes: ");
		scanf("%d", &nuevo_producto.stock);

		printf("Ingrese la cantidad minima de existencias: ");
		scanf("%d", &nuevo_producto.stock_minimo);

		printf("Ingrese el precio unitario: ");
		scanf("%f", &nuevo_producto.precio);

		printf("Ingrese el descuento: ");
		scanf("%d", &nuevo_producto.descuento);

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

void eliminarTicket(TTicket tickets[], int *num_tickets, int posicion) {
        if (posicion == *num_tickets - 1) {
                (*num_tickets)--;
                printf("Producto eliminado con exito.\n");
        } else {
                for (int i = posicion; i < *num_tickets - 1; i++) {
                        tickets[i] = tickets[i + 1];
                }
                (*num_tickets)--;
                printf("Producto eliminado con exito.\n");
        }
}

void bajaProducto(TProducto productos[], int *num_productos) {
	TProducto producto;

	printf("Ingrese el codigo del producto a eliminar: ");
	scanf("%s", producto.codigo);
	
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

void modificarProducto(TProducto productos[], int num_productos) {
	TProducto producto;

	printf("Ingrese el codigo del producto a modificar: ");
	scanf("%s", producto.codigo);

	int es_codigo = esCodigo(productos, num_productos, producto.codigo);

	if(es_codigo) {
		printf("El producto de codigo %s no existe.\n", producto.codigo);
	} else {
		int eleccion, posicion;

		buscarProducto(productos, num_productos, producto.codigo);
		posicionProducto(productos, num_productos, &posicion, producto.codigo);
		
		printf("Que elemento desea modificar?\n");
		printf("1 - Descripcion\n");
		printf("2 - Stock\n");
		printf("3 - Stock minimo\n");
		printf("4 - Precio unitario\n");
		printf("5 - Descuento\n");
		printf("Introduzca otra tecla para salir\n");
		scanf(" %d", &eleccion);

		switch (eleccion) {
			case (1): 
				printf("Introduce la nueva descripcion: ");
				scanf(" %[^\n]", productos[posicion].descripcion);
				break;
			case (2):
				printf("Ingrese el nuevo numero de unidades existentes: ");
				scanf("%d", &productos[posicion].stock);
				break;
			case (3):
				printf("Ingrese la nueva cantidad minima de existencias: ");
				scanf("%d", &productos[posicion].stock_minimo);
				break;
			case (4):
				printf("Ingrese el nuevo precio unitario: ");
				scanf("%f", &productos[posicion].precio);
				break;
			case (5):
				printf("Introduzca el nuevo descuento a aplicar: ");
				scanf("%d", &productos[posicion].descuento);
				break;
			default:
				printf("\n");
		}
	}
}

void crearTicket(TProducto productos[], int num_productos, TTicket tickets[], int *num_tickets) {
	if (*num_tickets == MAX_TICKETS) {
		printf("El numero de tickets no puede ser superior a %d, borre uno antes.\n", MAX_TICKETS);
	} else {
		TTicket nuevo_ticket;
		nuevo_ticket.codigo_ticket = *num_tickets + 1;
		nuevo_ticket.importe_total = 0.0;
		nuevo_ticket.lineas_ticket = 0;
		char eleccion;
		char codigo[MAX_CODIGO + 1] = {};
		int posicion = 0;
		posicionProducto(productos, num_productos, &posicion, codigo);
		int stock_disponible = productos[posicion].stock;

		do {
			printf("Ingrese el codigo del producto: ");
        		scanf("%s", codigo);

        		int es_codigo = esCodigo(productos, num_productos, codigo);

        		if(es_codigo) {
                		printf("El producto de codigo %s no existe.\n", codigo);
				eleccion = 'n';
        		} else if (nuevo_ticket.lineas_ticket < 10) {
				buscarProducto(productos, num_productos, codigo);
				float precio_oferta = productos[posicion].precio - productos[posicion].precio * productos[posicion].descuento/100;
				
				printf("El precio de oferta es: %.2f\n", precio_oferta);
				
				int error_stock, ventas;

				do {
					printf("Ingrese las unidades a vender: ");
					scanf("%d", &ventas);
						
					error_stock = ventas > stock_disponible;

					if (error_stock) {
						printf("No hay tantas unidades en stock, introduzca otra cantidad.\n");	
					}

				} while(error_stock);
					
				printf("Desea introducir otra linea? (S/s para introducir otra linea, 0 para cancelar la linea, pulse otra tecla para continuar)\n");
				scanf(" %c", &eleccion);

				if (eleccion != 0) {
					ventas = nuevo_ticket.lineas[nuevo_ticket.lineas_ticket].unidades_vendidas;
					nuevo_ticket.lineas_ticket++;
					stock_disponible -= ventas;
				}

			} else {
				printf("Ha llegado al maximo de lineas posibles.");
				eleccion = 'n';
			}
	
		} while(eleccion == 'S' || eleccion == 's');

		tickets[*num_tickets] = nuevo_ticket;
		(*num_tickets)++;
		productos[posicion].stock = stock_disponible;

	}
}

void buscarTicket(TTicket tickets[], int *num_tickets) {
	int codigo, posicion;
	char eleccion;

	printf("Introduzca el codigo del ticket: ");
	scanf("%d", &codigo);

	posicion = posicionTicket(tickets, *num_tickets, codigo);

	if (esTicket(tickets, *num_tickets, codigo)) {
		printf("El codigo introducido no existe.");
	} else {
		mostrarTicket(tickets, *num_tickets, codigo);

		printf("M - Volver al menu principal || E - Eliminar ticket\n");
		scanf(" %c", &eleccion);

		if (eleccion == 'E') {
			eliminarTicket(tickets, num_tickets, posicion);	
		}
	}
}

void comprobarStock(TProducto productos[], int num_productos) {
	for (int i = 0; i < num_productos; i++) {
		if (productos[i].stock <= productos[i].stock_minimo) {
			buscarProducto(productos, num_productos, productos[i].codigo);
		}
	}
}
