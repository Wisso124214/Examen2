//Luis Bustos. CI: 30.642.944. Laboratorio de Programacion II.
//Programa generador de Facturas.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>

struct datos_unicos_factura{  //Cada factura no requiere estos datos
	
	int dia;
	int mes;
	int anio;
	char direccion_negocio[90];
	int nro_facturas;
	int items;
}datosf;

struct lista_articulos_{
	
	int cant;
	char descripcion[72];
	int precio_unitario;
	int importe;
};

struct clientes_{
	
	char nombre[15];
	unsigned long int CI;
	char direccion[90];
	int numero_telefonoI[11];
	char numero_telefonoC[11];
};

struct facturas{
	
	struct clientes_ clientes;
	struct lista_articulos_ lista_articulos [30];
	float subtotal;
	float total;

} factura[15];


char c, v;
int contadorfacturas, artFacturas[15], cuantas, desde, coincidencias, Textos[15][3], Descripciones[30], long_[15][30];
unsigned long int ran;
const float IVA = 0.21;

char buscarC[90], copia_descripcion_lista_articulos[72];
long int buscarN;
int buscarNI[11];

void Ingresar_Datos();
int Imprimir_Facturas(int cuantas,int desde);
void Mostrar();
void Buscar();
void menu();
void salir();
int cmpinstr(int izq, int in, int caso, int fact);

char vacio[15];
int flag[15];

char Nombres[19][15]={"Luis","Alejandro","Maria","Sarai","Jose","Andres","Mario","Elena","Hugo","Sergio","Grecia","Karen","Luz","Irene","Graciela","Marcial","Alejandro","Vanessa","Santiago"};
char Direcciones[15][90]={"Av. prolongacion michelena c.c. thema local 19 frente a protinal, Maracaibo,Venezuela","Edif. Fricalor Iruna PB Local 80, Maracaibo,Venezuela","Torre A Piso 9 Ofic. 905, Maracaibo,Venezuela","Ed Ctro Solano Plaza P-5 Of 5-C, Maracaibo,Venezuela","C. C. Siglo XXI PB Local A40, Maracaibo,Venezuela","Centro G Piso 1, Maracaibo,Venezuela","Res. Plaza 1 PB Ofic. 10, Maracaibo,Venezuela","Urb. San Ignacio Nvel. Jardin Loc. LV-15, Maracaibo,Venezuela","Parcelamiento Ind. Lebrun Ca. Secundaria Edf. Pacentro, Maracaibo,Venezuela","Av. 13a entre 69a Y 70 Casa Favinca Sector Tierra Negra, Maracaibo,Venezuela","Piso 2 Ofic. 2C Zona A-1, Maracaibo,Venezuela","Av Fco de Mda Edif. Tecoteca Piso 1, Maracaibo,Venezuela","Edif. Lion Piso 2 Ofic. 202, Maracaibo,Venezuela","9na. Transv. e/4ta. y 5ta. Av. Qta. Unifedo, Maracaibo,Venezuela","Zona Industrial Care, Maracaibo,Venezuela"};
char nombres_articulos[14][12]={"frutas","verduras","queso","huevos","galletas","cereales","helado","azucar","harina","jamon","arroz","pasta","pollo","carne"};

//MAIN

int main(){
	
	srand(time(NULL));
	menu();
	
	return 0;
}

//INGRESAR DATOS

void Ingresar_Datos(){
	
	int i, j, opc, y, z, cond;
	
	do{
		system("cls");
		printf("Digite cuantas facturas desea registrar (maximo 15, minimo 1): ");
		scanf("%d",&datosf.nro_facturas);
		
	}while(datosf.nro_facturas>15 || datosf.nro_facturas<1);
	
	do{
		system("cls");
		printf("Digite cuantas facturas desea registrar (maximo 15, minimo 1): %d",datosf.nro_facturas);
		printf("\n\nDecida si desea registrar las facturas aleatoriamente (0) o manualmente (1): ");
		scanf("%d",&opc);
		
	}while(opc!=1 && opc!=0);
		
	contadorfacturas=0;
	
	switch(opc){
		
		case 0:
			
			printf("Decide ahorrar tiempo autogenerando las facturas. Entiendo\n\n");
			system("pause");
						
			datosf.dia=rand()%31+1;
			datosf.mes=rand()%12+1;
			datosf.anio=rand()%20+2010;
			
			for(i=0; i<datosf.nro_facturas; i++){
				
				flag[i]=1;
				
				Textos[i][0]=rand()%15;							//Direccion negocio
				Textos[i][1]=rand()%19;							//Nombre
				Textos[i][2]=rand()%15;							//Direccion cliente
				
				factura[i].clientes.CI=rand()%15000000+20000000;
				
				factura[i].clientes.numero_telefonoI[1]=4;
				factura[i].clientes.numero_telefonoI[2]=2;
				factura[i].clientes.numero_telefonoI[3]=4;
				
				for(z=4; z<11; z++){
					
					factura[i].clientes.numero_telefonoI[z]=rand()%10;
				}
				
				datosf.items=rand()%15;
				artFacturas[i]=datosf.items;
				
				for(y=0; y<datosf.items; y++){
					
					factura[i].lista_articulos[y].cant=rand()%30;
					
					c=v;												//El caracter "v" es un caracter que uso para vaciar o eliminar la cadena, puesto que no funciona "\0"
					for(z=0; z<72; z++){
						factura[i].lista_articulos[y].descripcion[z]=v;
					}
					
					Descripciones[y]=rand()%14;
					
					factura[i].lista_articulos[y].precio_unitario=rand()%500;
				}
				contadorfacturas++;
				i=Imprimir_Facturas(1,i+1);
			}
			
			break;
			
		case 1:
			
			system("cls");
			printf("Excelente. Aca tiene la disponibilidad de registrar manualmente los datos de las facturas. Comencemos");
			
			for(i=0; i<15; i++){
				flag[i]=0;
			}
			
			printf("\n\nDATOS DE LA FACTURA\n\n");
			printf("Ingrese el dia actual: ");
			scanf("%d",&datosf.dia);
			
			printf("Ingrese el mes vigente (numero): ");
			scanf("%d",&datosf.mes);
			
			printf("Ingrese el anio en curso: ");
			scanf("%d",&datosf.anio);
			
			printf("Ingrese la direccion del negocio: ");
			
			fflush(stdin);
			
			c=v;
			for(i=0; i<90; i++){
				datosf.direccion_negocio[i]=v;
			}
			
			i=0;
			do{
				scanf("%c",&c);
				
				if(c!=' ')
					datosf.direccion_negocio[i]=c;
				else
					datosf.direccion_negocio[i]=' ';
				i++;

			}while(c!='\n' && i<90);
			
			fflush(stdin);
				
			for(i=contadorfacturas; i<datosf.nro_facturas; i++){
				
				printf("\tINGRESE LOS DATOS DE LA FACTURA # %d",i+1);
				
				printf("\n\nDATOS DEL CLIENTE\n\n");
				
				printf("Ingrese el nombre del cliente: ");
				
				fflush(stdin);
				
				c=v;
				for(j=0; j<15; j++){
					factura[i].clientes.nombre[j]=v;              
				}
				
				j=0;
				do{
					scanf("%c",&c);
					
					if(c!=' ')
						factura[i].clientes.nombre[j]=c;
					else
						factura[i].clientes.nombre[j]=' ';
					j++;
	
				}while(c!='\n' && j<15);
				
				fflush(stdin);

				printf("Ingrese el documento de identidad del cliente (sin puntos por favor): ");
				scanf("%d",&factura[i].clientes.CI);
				
				printf("Ingrese la direccion del cliente: ");
				
				fflush(stdin);
				
				c=v;
				for(j=0; j<90; j++){
					factura[i].clientes.direccion[j]=v;              
				}
				
				j=0;
				do{
					scanf("%c",&c);
					
					if(c!=' ')
						factura[i].clientes.direccion[j]=c;
					else
						factura[i].clientes.direccion[j]=' ';
					j++;
	
				}while(c!='\n' && j<90);
				
				fflush(stdin);
				
				printf("Ingrese el numero de celular del cliente: ");
				scanf("%s",&factura[i].clientes.numero_telefonoC);
				
				printf("\n\nLISTA DE ARTICULOS\n\n");
				printf("Ingrese la cantidad de items: ");
				scanf("%d",&datosf.items);
				
				artFacturas[i]=datosf.items;
				
				for(j=0; j<datosf.items; j++){
					
					printf("\nIngrese la cantidad de articulos del item %d: ",j+1);
					scanf("%d",&factura[i].lista_articulos[j].cant);
					
					printf("Ingrese la descripcion del item %d: ",j+1);
					
				fflush(stdin);
					c=v;
					for(z=0; z<72; z++){
						factura[i].lista_articulos[j].descripcion[z]=v;
					}
					
					z=0;
					do{
						scanf("%c",&c);
						
						if(c!=' ')
							factura[i].lista_articulos[j].descripcion[z]=c;
						else
							factura[i].lista_articulos[j].descripcion[z]=' ';
						z++;
		
					}while(c!='\n' && z<72);
					
					long_[i][j]=z-1;
					
					copia_descripcion_lista_articulos[i]=factura[i].lista_articulos[j].descripcion;
					
					fflush(stdin);
					
					printf("Ingrese el precio unitario del item %d: ",j+1);
					scanf("%d",&factura[i].lista_articulos[j].precio_unitario);
				}
				
				contadorfacturas++;
				i=Imprimir_Facturas(1,i+1);
			}
			
			break;	
	}
	return;
}

//IMPRIMIR FACTURAS

int Imprimir_Facturas(int cuantas,int desde){
	
	int i, j, y, val_i, z;
	
	val_i=desde-1;
	
	system("cls");
	
	if(contadorfacturas==0){
		
		printf("Lo sentimos, aun no hay ninguna factura registrada para imprimir. Ingrese alguna factura para poder visualizarlas. Gracias.\n\n");
		system("pause");
		return -1;
	}
	
	if(cuantas==0 && desde==0){
	
		do{
			
			if(cuantas>contadorfacturas){
				system("cls");
				printf("El numero de facturas registradas en esta sesion es de %d\n",contadorfacturas);
			}
			
			printf("Cuantas facturas desea imprimir?: ");
			scanf("%d",&cuantas);
			
			if(cuantas==-1){
				return -1;
				break;
			}
		}while(cuantas>contadorfacturas || cuantas<1);
		
		do{
			
			printf("\nIngrese la factura por la cual desea comenzar a imprimir: ");
			scanf("%d",&desde);
		}while(desde>contadorfacturas+1 || desde<1);
	}
	
	for(i=desde-1; i<15 && i<(desde-1+cuantas); i++){

		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                    FACTURA # %d\n",i+1);
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		
		printf("Negocio: ");
		if(flag[i]==1){
			printf("%s",Direcciones[Textos[i][0]]);
			
		}else{
			for(j=0; j<90; j++){
				printf("%c",datosf.direccion_negocio[j]);
			}
		}

		printf("\n%d/%d/%d",datosf.dia,datosf.mes,datosf.anio);
		
		fflush(stdin);
		
		printf("\n\nNombre: ");
		if(flag[i]==1){
			printf("%s",Nombres[Textos[i][1]]);
			
		}else{
			for(j=0; j<90; j++){
				printf("%c",factura[i].clientes.nombre[j]);
			}
		}
				
		printf("\nCI: %d",factura[i].clientes.CI);
		
		printf("\nDireccion: ");
		if(flag[i]==1){
			printf("%s",Direcciones[Textos[i][2]]);
			
		}else{
			for(j=0; j<90; j++){
				printf("%c",factura[i].clientes.direccion[j]);
			}
		}

		printf("\nTelefono: ");
		
		ran=0;
		for(y=0;y<11;y++){
			ran+=factura[i].clientes.numero_telefonoI[y];
		}
		
		if(ran>0){
			for(y=0;y<11;y++){
				printf("%d",factura[i].clientes.numero_telefonoI[y]);
			}
		}else{
			
			printf("%s",factura[i].clientes.numero_telefonoC);
		}
		
		printf("\n\n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf("                                                 LISTA DE ARTICULOS\n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf(" Cantidad |                              Descripcion                               |  Precio unitario  | Importe \n");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		
		factura[i].subtotal=0;
		
		for(j=0; j<artFacturas[i]; j++){
			
			factura[i].lista_articulos[j].importe=factura[i].lista_articulos[j].precio_unitario*factura[i].lista_articulos[j].cant;
			
			if(factura[i].lista_articulos[j].cant<10)
				printf("   0%d\t  |",factura[i].lista_articulos[j].cant);
			else
				printf("   %d\t  |",factura[i].lista_articulos[j].cant);
			
			if(flag[i]==1){
				ran=(floor(72-(strlen(nombres_articulos[Descripciones[j]])))/2);
				for(y=0; y<ran; y++){printf(" ");}
					printf("%s",nombres_articulos[Descripciones[j]]);
				for(y=0; y<(72-ran-(strlen(nombres_articulos[Descripciones[j]]))); y++){printf(" ");}
				
			}else{
				ran=(floor(72-(long_[i][j]))/2);
				for(y=0; y<ran; y++){printf(" ");}
								
					for(z=0; z<(long_[i][j]); z++){
							printf("%c",factura[i].lista_articulos[j].descripcion[z]);
						}
				for(y=0; y<(72-ran-(long_[i][j])); y++){printf(" ");}
			}
			
			printf("|        %d\t       |   %d ",factura[i].lista_articulos[j].precio_unitario,factura[i].lista_articulos[j].importe);
			
			factura[i].subtotal+=factura[i].lista_articulos[j].importe;
			printf("\n");
		}

		factura[i].total=factura[i].subtotal+(factura[i].subtotal*IVA);
		
		printf("\n");
		
		if(artFacturas[i]<10){
			printf("  Items(0%d)                                                                        |      Subtotal   \t%.2f\n",artFacturas[i],factura[i].subtotal);
		}else{
			printf("  Items(%d)                                                                        |      Subtotal   \t%.2f\n",artFacturas[i],factura[i].subtotal);
		}
		
		printf("                                                                                   |      IVA (21%%) \t%.2f\n\n",factura[i].subtotal*IVA);
		printf("                                                                                   |      TOTAL      \t%.2f\n",factura[i].total);
		printf("\n\n\n");
		system("pause");
	}
	return val_i;
}

//BUSCAR

void Buscar(){
	
	int opc, i, j, x, y, z, w;
		
	if(contadorfacturas==0){
		
		system("cls");
		printf("Lo sentimos, aun no hay ninguna factura registrada para buscar un dato. Ingrese alguna factura para poder buscar un dato. Gracias.\n\n");
		system("pause");
		return;
	}
	coincidencias=0;
	
	do{
		system("cls");
		printf("Que desea buscar?: ");
		printf("\n1. CI del cliente\n2. Direccion del cliente\n3. Nombre del cliente\n4. Numero de telefono del cliente\n5. Cantidad de items totales en una factura\n6. Descripcion de un item en la factura\n7. Total de la factura\n\n>>");
		scanf("%d",&opc);
	}while(opc>8 || opc<0);
	
	printf("\nIngrese: ");
	fflush(stdin);
	
	if(opc==1 || opc==5 || opc==7){
		
		scanf("%d",&buscarN);
		fflush(stdin);
	}
	
	if(opc==2 || opc==3 || opc==6 || opc==4){
		
		c=v;
		for(j=0; j<90; j++){
			buscarC[j]=v;              
		}
		
		j=0;
		do{
			scanf("%c",&c);
			
			if(c!=' ')
				buscarC[j]=c;
			else
				buscarC[j]=' ';
			j++;

		}while(c!='\n' && j<90);
		
		fflush(stdin);
	}
	
	switch(opc){
		
		case 1:
			for(i=0; i<contadorfacturas; i++){
				
				if(buscarN==factura[i].clientes.CI){
										
					printf("Se ha encontrado una coincidencia\n\n\n");
					system("pause");
					coincidencias++;
					i=Imprimir_Facturas(1,i+1);
				}
			}
			break;

		case 2:
					
			for(i=0; i<contadorfacturas; i++){
				if(flag[i]==1){
					
					y=(strlen(buscarC)-1);
					
					x=90-y;
					
					for(z=0; z<x; z++){
						
							ran=0;
						for(j=0; j<y; j++){
														
							if(cmpinstr(z,j,0,i)==1){
								ran++;
							}else{
								j=y;
							}
							
							if(ran==y){
								
								printf("Se ha encontrado una coincidencia\n\n\n");
								system("pause");
								coincidencias++;
								i=Imprimir_Facturas(1,i+1);
							}
						}
					}
				}else{
					
					y=(strlen(buscarC)-1);
					
					x=90-y;
					
					for(z=0; z<x; z++){
						
							ran=0;
						for(j=0; j<y; j++){
							
							if(cmpinstr(z,j,1,i)==1){
								ran++;
							}else{
								j=y;
							}
							
							if(ran==y){
								
								printf("Se ha encontrado una coincidencia\n\n\n");
								system("pause");
								coincidencias++;
								i=Imprimir_Facturas(1,i+1);
							}
						}
					}

				}
			}
			break;

		case 3:
					
			for(i=0; i<contadorfacturas; i++){
				if(flag[i]==1){
					
					y=(strlen(buscarC)-1);
					
					x=15-y;
					
					for(z=0; z<x; z++){
							
							ran=0;
						for(j=0; j<y; j++){
							
							if(cmpinstr(z,j,2,i)==1){
								ran++;
							}else{
								j=y;
							}
								
							if(ran==y){
								
								printf("Se ha encontrado una coincidencia\n\n\n");
								system("pause");
								coincidencias++;
								i=Imprimir_Facturas(1,i+1);
							}
						}
					}


				}else{
					
					y=(strlen(buscarC)-1);
					
					x=15-y;
					
					for(z=0; z<x; z++){
						
							ran=0;
						for(j=0; j<y; j++){
							
							if(cmpinstr(z,j,3,i)==1){
								ran++;
							}else{
								j=y;
							}
					
							if(ran==y){
								
								printf("Se ha encontrado una coincidencia\n\n\n");
								system("pause");
								coincidencias++;
								i=Imprimir_Facturas(1,i+1);
							}
						}
					}
				}
			}
			break;

		case 4:
			for(i=0; i<contadorfacturas; i++){
			
				ran=0;
				for(j=0; j<11; j++){
					
					ran+=factura[i].clientes.numero_telefonoI[j];
				}
				
				if(ran==0){
					
					for(j=0; j<11; j++){
											
						buscarNI[j]=buscarC[j]-48;
					}
					
					ran=0;
					
					for(j=0; j<11; j++){
						
						if(buscarNI[j]==factura[i].clientes.numero_telefonoI[j]){
							ran++;	
						}
						
						if(ran==11){
						
							printf("Se ha encontrado una coincidencia\n\n\n");
							system("pause");
							coincidencias++;
							i=Imprimir_Facturas(1,i+1);
						}
					}
				}else{
					
					y=(strlen(buscarC)-1);
					
					x=11-y;
					
					for(z=0; z<x; z++){
						
							ran=0;
						for(j=0; j<y; j++){
							
							if(cmpinstr(z,j,4,i)==1){
								ran++;
							}else{
								j=y;
							}
							
							if(ran==y){
								
								printf("Se ha encontrado una coincidencia\n\n\n");
								system("pause");
								coincidencias++;
								i=Imprimir_Facturas(1,i+1);
							}
						}
					}

				}
			}
			break;

		case 5:	
		
			for(i=0; i<contadorfacturas; i++){
				
				if(buscarN==artFacturas[i]){
					
					printf("Se ha encontrado una coincidencia\n\n\n");
					system("pause");
					coincidencias++;
					i=Imprimir_Facturas(1,i+1);
				}				
			}
			break;

		case 6:
			
			for(i=0; i<contadorfacturas; i++){
				
				if(flag[i]==1){
					
					y=(strlen(buscarC)-1);
					
					x=12-y;
					
					for(z=0; z<x; z++){
							
							ran=0;
						for(j=0; j<y; j++){
							
							if(cmpinstr(z,j,5,i)==1){
								ran++;
							}else{
								j=y;
							}
							
							if(ran==y){
								
								printf("Se ha encontrado una coincidencia\n\n\n");
								system("pause");
								coincidencias++;
								i=Imprimir_Facturas(1,i+1);
							}
						}
					}
					

				}else{
					
					for(w=0; w<artFacturas[i]; w++){
					
						y=(strlen(buscarC)-1);
						
						x=72-y;
						
						for(z=0; z<x; z++){
								
								ran=0;
							for(j=0; j<y; j++){
								
								if(cmpinstr(z,j,2,i)==1){
									ran++;
								}else{
									j=y;
								}
								
								if(ran==y){
									
									printf("Se ha encontrado una coincidencia\n\n\n");
									system("pause");
									coincidencias++;
									i=Imprimir_Facturas(1,i+1);
								}
							}
						}


					}
				}
			}
			break;

		case 7:
			
			for(i=0; i<contadorfacturas; i++){
			
				if(buscarN==(int)factura[i].total){
					
					printf("Se ha encontrado una coincidencia\n\n\n");
					system("pause");
					coincidencias++;
					i=Imprimir_Facturas(1,i+1);
				}
			}
			break;
	}
	
	if(coincidencias==0){
		
		printf("\n\nLa variable ingresada fue buscada y no se encontro ninguna coincidencia...\n\n");
		system("pause");
	}
	return;
}

//MENU

void menu(){
	
	int opc;
	
	do{
		system("cls");
		printf("MENU: \n\n1. Ingresar Datos de la factura\n2. Imprimir facturas\n3. Buscar en la base de datos\n4. Salir\n\n>>");
		scanf("%d",&opc);
		
		switch(opc){
			
			case 1: Ingresar_Datos(); break;
			case 2: Imprimir_Facturas(0,0); break;
			case 3: Buscar(); break;
			case 4: salir(); break;
		}
	}while(opc!=4);	
	
	return;
}

//SALIR

void salir(){
	
	system("cls");
	printf("\n\n\nMUCHAS GRACIAS POR USAR ESTE PROGRAMA!!! Espero que haya sido de utilidad\n\n\n");
	system("pause");
	return;
}

int cmpinstr(int izq, int in, int caso, int fact){
	
	switch(caso){
		
		case 0:{
			
			if(buscarC[in]==Direcciones[Textos[fact][2]][in+izq])
				return 1;
			else
				return 0;
			
			break;
		}

		case 1:{
			
			if(buscarC[in]==factura[fact].clientes.direccion[in+izq])
				return 1;
			else
				return 0;
			
			break;
		}

		case 2:{
			
			if(buscarC[in]==Nombres[Textos[fact][1]][in+izq])
				return 1;
			else
				return 0;
			
			break;
		}

		case 3:{
			
			if(buscarC[in]==factura[fact].clientes.nombre[in+izq])
				return 1;
			else
				return 0;
			
			break;
		}

		case 4:{
			
			if(buscarC[in]==factura[fact].clientes.numero_telefonoC[in+izq])
				return 1;
			else
				return 0;
			
			break;
		}
		
		case 5:{
			
			if(buscarC[in]==nombres_articulos[Descripciones[fact]][in+izq])
				return 1;
			else
				return 0;
			
			break;
		}
		
		case 6:{
			
			if(buscarC[in]==copia_descripcion_lista_articulos[in+izq])
				return 1;
			else
				return 0;
			
			break;
		}
	}
}