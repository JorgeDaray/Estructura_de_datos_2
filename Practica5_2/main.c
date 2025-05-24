#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "../extras/Arches.h"
#include "../extras/Tomarc.h"
#include "../extras/Funscads.h"
#include "../extras/Hazllave.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define salto "\n"
#define salto_deli 'n'
#define LONG_key 20
#define LONG_REG 64
#define campo_a_buffreg(br,cad) strcat(br,cad); strcat(br,DELIM_CAD);

//Para acomodarlo de manera ordenada agregar una bandera si existe info en el struct tal
//y acomodar el registro en el mismo numero de participantes
//Lo de arriba es para mandar ordenado el archivo 2, de la llave principal

static char *solicitud[] = {"	  Nombre: ",
							"  Direccion: ",
							"	  Ciudad: ",
						   "Nacionalidad: ",
				"Tiempo de clasificacion: ",
							""};

static int fd;
static struct{
	short cont_reg; //short son 2 bytes
	char relleno[30]; //esto son 30 bytes
}encabezado;

int parti_total=-1;

struct principal
{
	int num_ord;
	char num_par[5];
	char nom_atle[20];
	char direccion[30];
	char ciudad[30];
	char nacionalidad[20];
	char tiempo[20];
	int existe;
	char nrrchar[20];
	int nrr;
	char tiempo_real[20];
}participante[2000];

struct llave_num
{
	int numero_ordenar;
	char num_key[5];
	int nrr_buscar;
	char nrr_letra[20];
	char tiempo_realkey[20];
	int existe;
}numerokey[2000];

struct duplicado
{
	char numero_du[5];
	int num_du;
	int existe;
}dupli[2000];

struct nombre_key
{
	char nombre_canon[20];
	char key_num[5];
	int key;
}nom_k[2000];

struct city_key
{
	char city_canon[20];
	char key_num[5];
	int key;
}city_k[2000];

struct nac_key
{
	char nac_canon[20];
	char key_num[5];
	int key;
}nac_k[2000];

void canon()
{
	int i;
	for(i=0; i<=parti_total;i++)
	{
		hazllave(nom_k[i].nombre_canon,nom_k[i].nombre_canon);
		hazllave(city_k[i].city_canon,city_k[i].city_canon);
		hazllave(nac_k[i].nac_canon,nac_k[i].nac_canon);
	}
}

void ordenar_nombre()
{
	int i,j;
	struct nombre_key aux;
	for(i=0; i<=parti_total;i++)
	{
		for(j=0; j<=parti_total-1; j++)
		{
			if(nom_k[j].nombre_canon[0]>nom_k[i].nombre_canon[0])
			{
				aux=nom_k[i];
				nom_k[i]=nom_k[j];
				nom_k[j]=aux;
			}
		}
	}
}

void ordenar_city()
{
	int i,j;
	struct city_key aux;
	for(i=0; i<=parti_total;i++)
	{
		for(j=0; j<=parti_total-1; j++)
		{
			if(city_k[j].city_canon[0]>city_k[i].city_canon[0])
			{
				aux=city_k[i];
				city_k[i]=city_k[j];
				city_k[j]=aux;
			}
		}
	}
}

void ordenar_nac()
{
	int i,j;
	struct nac_key aux;
	for(i=0; i<=parti_total;i++)
	{
		for(j=0; j<=parti_total-1; j++)
		{
			if(nac_k[j].nac_canon[0]>nac_k[i].nac_canon[0])
			{
				aux=nac_k[i];
				nac_k[i]=nac_k[j];
				nac_k[j]=aux;
			}
		}
	}
}

void ordenar_structs()
{
	canon();
	ordenar_nombre();
	ordenar_city();
	ordenar_nac();
}

void escribe_nomk(int nomk)
{
	char buffreg[TAM_MAX_REG + 1];
	int i,j;
	int primer=0;
	char nom_aux[20];
	int nums[parti_total+1];

	for(i=0; i<TAM_MAX_REG-1; buffreg[i++]='\0');

	for(i=0;i<=parti_total+1;i++)
	{
		if(primer==0)
		{
			campo_a_buffreg(buffreg,nom_k[i].nombre_canon);
			campo_a_buffreg(buffreg,nom_k[i].key_num);
			primer++;
		}
		else
		{
			if(strcmp(nom_k[i-1].nombre_canon,nom_k[i].nombre_canon)==0)
			{
				campo_a_buffreg(buffreg,nom_k[i].key_num);
			}
			else
			{
				strcat(buffreg,salto);
				write(nomk,buffreg,strlen(buffreg));
				for(j=0; j<TAM_MAX_REG-1; buffreg[j++]='\0');
				campo_a_buffreg(buffreg,nom_k[i].nombre_canon);
				campo_a_buffreg(buffreg,nom_k[i].key_num);
			}
		}
	}
}

void escribe_nack(int nack)
{
	char buffreg[TAM_MAX_REG + 1];
	int i,j;
	int primer=0;

	for(i=0; i<TAM_MAX_REG-1; buffreg[i++]='\0');

	for(i=0;i<=parti_total+1;i++)
	{
		if(primer==0)
		{
			campo_a_buffreg(buffreg,nac_k[i].nac_canon);
			campo_a_buffreg(buffreg,nac_k[i].key_num);
			primer++;
		}
		else
		{
			if(strcmp(nac_k[i-1].nac_canon,nac_k[i].nac_canon)==0)
			{
				campo_a_buffreg(buffreg,nac_k[i].key_num);
			}
			else
			{
				strcat(buffreg,salto);
				write(nack,buffreg,strlen(buffreg));
				for(j=0; j<TAM_MAX_REG-1; buffreg[j++]='\0');
				campo_a_buffreg(buffreg,nac_k[i].nac_canon);
				campo_a_buffreg(buffreg,nac_k[i].key_num);
			}
		}
	}
}

void escribe_cityk(int cityk)
{
	char buffreg[TAM_MAX_REG + 1];
	int i,j;
	int primer=0;

	for(i=0; i<TAM_MAX_REG-1; buffreg[i++]='\0');

	for(i=0;i<=parti_total+1;i++)
	{
		if(primer==0)
		{
			campo_a_buffreg(buffreg,city_k[i].city_canon);
			campo_a_buffreg(buffreg,city_k[i].key_num);
			primer++;
		}
		else
		{
			if(strcmp(city_k[i-1].city_canon,city_k[i].city_canon)==0)
			{
				campo_a_buffreg(buffreg,city_k[i].key_num);
			}
			else
			{
				strcat(buffreg,salto);
				write(cityk,buffreg,strlen(buffreg));
				for(j=0; j<TAM_MAX_REG-1; buffreg[j++]='\0');
				campo_a_buffreg(buffreg,city_k[i].city_canon);
				campo_a_buffreg(buffreg,city_k[i].key_num);
			}
		}
	}
}

void exis_cero()
{
	int i;
	for(i=0; i<2000; i++) participante[i].existe=0;
}

/*int registro(char buffreg[])
{
	int numpar=0, i=0;
	char respuesta[50];

	for(i=0; i<LONG_REG; buffreg[i++]='\0');

	printf("Ingrese su numero de participacion: ");
	gets(respuesta);
	numpar=atoi(respuesta);
	fflush(stdin);

	if(numpar>2000||numpar<0)
	{
		printf("Numero de participacion invalido, volviendo al menu");
		system("pause");
		system("cls");
		return -1;
	}
	if(dupli[numpar].existe==1)
	{
		printf("Numero de participacion existente, volviendo al menu");
		system("pause");
		system("cls");
		return -1;
	}

	parti_total++;
	participante[numpar].num_ord=numpar;
	strcpy(participante[numpar].num_par,respuesta);
	campo_a_buffreg(buffreg,participante[numpar].num_par);
	participante[numpar].existe=1;

	for(i=0; *solicitud[i]!='\0'; i++)
	{
		printf("%s",solicitud[i]);
		gets(respuesta);
		if(i==0)
		{
			strcpy(participante[numpar].nom_atle,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].nom_atle);
		}

		if(i==1)
		{
			strcpy(participante[numpar].direccion,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].direccion);
		}

		if(i==2)
		{
			strcpy(participante[numpar].ciudad,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].ciudad);
		}

		if(i==3)
		{
			strcpy(participante[numpar].nacionalidad,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].nacionalidad);
		}

		if(i==4)
		{
			strcpy(participante[numpar].tiempo,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].tiempo);
		}
	}
	participante[numpar].nrr=parti_total;
	return numpar;
}*/

int registro(char buffreg[])
{
	int numpar=0, i=0;
	char respuesta[50];

	for(i=0; i<LONG_REG; buffreg[i++]='\0');

	printf("Ingrese su numero de participacion: ");
	gets(respuesta);
	numpar=atoi(respuesta);
	fflush(stdin);

	if(numpar>2000||numpar<0)
	{
		printf("Numero de participacion invalido, volviendo al menu");
		system("pause");
		system("cls");
		return -1;
	}

	parti_total++;
	participante[numpar].num_ord=numpar;

	nom_k[parti_total].key=numpar;
	city_k[parti_total].key=numpar;
	nac_k[parti_total].key=numpar;

	strcpy(participante[numpar].num_par,respuesta);

	strcpy(nom_k[parti_total].key_num,respuesta);
	strcpy(city_k[parti_total].key_num,respuesta);
	strcpy(nac_k[parti_total].key_num,respuesta);

	campo_a_buffreg(buffreg,participante[numpar].num_par);
	participante[numpar].existe=1;



	for(i=0; *solicitud[i]!='\0'; i++)
	{
		printf("%s",solicitud[i]);
		gets(respuesta);
		if(i==0)
		{
			strcpy(participante[numpar].nom_atle,respuesta);
			strcpy(nom_k[parti_total].nombre_canon,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].nom_atle);
		}

		if(i==1)
		{
			strcpy(participante[numpar].direccion,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].direccion);
		}

		if(i==2)
		{
			strcpy(participante[numpar].ciudad,respuesta);
			strcpy(city_k[parti_total].city_canon,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].ciudad);
		}

		if(i==3)
		{
			strcpy(participante[numpar].nacionalidad,respuesta);
			strcpy(nac_k[parti_total].nac_canon,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].nacionalidad);
		}

		if(i==4)
		{
			strcpy(participante[numpar].tiempo,respuesta);
			campo_a_buffreg(buffreg,participante[numpar].tiempo);
		}
	}
	participante[numpar].nrr=parti_total;
	return numpar;
}

void leepar()
{
	int byte_pos,numO;
	char buffreg[TAM_MAX_REG+1],campo[TAM_MAX_REG+1];
	int pos_bus,long_datos;
	int vuelta;
	int ordenar;

	read(fd,buffreg,LONG_REG);
	buffreg[LONG_REG]='\0';
	int i;
	for(i=0;i<parti_total;i++)
	{
		vuelta=0;
		byte_pos=i*LONG_REG+sizeof(encabezado);//lo calcula en el nrr
		lseek(fd,(long)byte_pos,0);//coloca

		read(fd,buffreg,LONG_REG);
		buffreg[LONG_REG]='\0';
		long_datos=strlen(buffreg);
		while((pos_bus=toma_campo(campo,buffreg,pos_bus,long_datos))>0)
		{
			if(vuelta==0)
				strcpy(participante[i].num_par,campo);
			if(vuelta==1)
				strcpy(participante[i].nom_atle,campo);
			if(vuelta==2)
				strcpy(participante[i].direccion,campo);
			if(vuelta==3)
				strcpy(participante[i].ciudad,campo);
			if(vuelta==4)
				strcpy(participante[i].nacionalidad,campo);
			if(vuelta==5)
				strcpy(participante[i].tiempo,campo);
			participante[i].existe=1;
			participante[i].nrr=i;
			numO=atoi(participante[i].num_par);
			participante[i].num_ord=numO;
			vuelta++;
		}

		read(fd,buffreg,LONG_REG);
		buffreg[LONG_REG]='\0';
		printf("\n");
	}
}

void guardarfd2(int fd2,char buffreg[])
{
	int byte_pos;
	long lseek();
	char prueba[50]="77:77:77";
	int exitosos=0;
	int i,j;
	for(j=0; j<LONG_REG; buffreg[j++]='\0');

	for(i=0;i<2000;i++)
	{
		if(participante[i].existe==1)
		{

			strcpy(participante[i].tiempo_real,prueba);
			campo_a_buffreg(buffreg,participante[i].num_par);
			sprintf(participante[i].nrrchar, "%d", participante[i].nrr);//Esto es de int a char
			campo_a_buffreg(buffreg,participante[i].nrrchar);
			campo_a_buffreg(buffreg,participante[i].tiempo_real);

			byte_pos=exitosos*LONG_key;
			lseek(fd2,(long)byte_pos,0);
			write(fd2,buffreg,LONG_key);
			exitosos++;
			for(j=0; j<LONG_REG; buffreg[j++]='\0');
		}
	}
}

void leerfd2(int fd2)
{
	int byte_pos,numO;
	char buffreg[TAM_MAX_REG+1],campo[TAM_MAX_REG+1];
	int pos_bus,long_datos;
	int vuelta;

	read(fd,buffreg,LONG_key);
	buffreg[LONG_key]='\0';
	int i;

	for(i=0;i<=parti_total;i++)
	{
		vuelta=0;
		byte_pos=i*LONG_key;//lo calcula en el nrr
		lseek(fd2,(long)byte_pos,0);//coloca

		read(fd2,buffreg,LONG_key);
		buffreg[LONG_key]='\0';
		long_datos=strlen(buffreg);
		while((pos_bus=toma_campo(campo,buffreg,pos_bus,long_datos))>0)
		{
			if(vuelta==0)
				strcpy(numerokey[i].num_key,campo);
			if(vuelta==1)
				strcpy(numerokey[i].nrr_letra,campo);
			if(vuelta==2)
				strcpy(numerokey[i].tiempo_realkey,campo);
			numerokey[i].existe=1;
			numO=atoi(numerokey[i].num_key);
			numerokey[i].numero_ordenar=numO;
			vuelta++;
		}

		read(fd2,buffreg,LONG_key);
		buffreg[LONG_key]='\0';
		printf("\n");
	}
}

void duplicados(int fd)
{
	int byte_pos,numO;
	char buffreg[TAM_MAX_REG+1],campo[TAM_MAX_REG+1];
	int pos_bus,long_datos;
	int vuelta;
	int ordenar;

	read(fd,buffreg,LONG_REG);
	buffreg[LONG_REG]='\0';
		int i;

	for(i=0;i<parti_total;i++)
	{
		vuelta=0;
		byte_pos=i*LONG_REG+sizeof(encabezado);//lo calcula en el nrr
		lseek(fd,(long)byte_pos,0);//coloca

		read(fd,buffreg,LONG_REG);
		buffreg[LONG_REG]='\0';
		long_datos=strlen(buffreg);
		while((pos_bus=toma_campo(campo,buffreg,pos_bus,long_datos))>0)
		{
				if(vuelta==0)
				{
					ordenar=atoi(campo);
					strcpy(dupli[ordenar].numero_du,campo);
					dupli[ordenar].num_du=atoi(dupli[ordenar].numero_du);
					dupli[ordenar].existe=1;
				}
				vuelta++;
		}

		read(fd,buffreg,LONG_REG);
		buffreg[LONG_REG]='\0';
		printf("\n");
	}
}

int leecampo(int fd,char cad[])
{
int i;
char c;
i=0;
while(read(fd,&c,1)>0 && c!=DELIM_CAR && c!=salto_deli)
cad[i++]=c;

if(c==salto_deli)
{
	return 777;
}
cad[i]='\0';

return (i);
}

/*while((n=leecampo(fd,cad))>0){
//++cont_campos;

nuevo=(cont_campos%8);
if(nuevo==0)
{
printf("Cliente %d: %s\n",++cliente,cad);
}
else
printf("\t\t-%s\n",cad);
++cont_campos;
}*/

void leernomk(int fd)
{
	int byte_pos,numO;
	char buffreg[TAM_MAX_REG+1],campo[TAM_MAX_REG+1];
	int pos_bus,long_datos;
	int vuelta=0;
	int i=0,n;
	char cad[20];
	int nuevo=0;

	read(fd,buffreg,LONG_key);
	buffreg[LONG_key]='\0';

	lseek(fd,0L,0);//coloca al inicio

	while((n=leecampo(fd,cad))>0)
	{
		if(vuelta!=0)
		{
			if(n==777)
			{
				nuevo=0;
			}
		}

		if(nuevo==0)
		{
			strcpy(nom_k[i].nombre_canon,cad);
			nuevo++;
		}
		else
		{
			strcpy(nom_k[i].key_num,cad);
			i++;
			strcpy(nom_k[i].nombre_canon,nom_k[i].nombre_canon);
		}
		vuelta++;
	}
}

/*void leernomk(int fd2)
{
	int byte_pos,numO;
	char buffreg[TAM_MAX_REG+1],campo[TAM_MAX_REG+1];
	int pos_bus,long_datos;
	int vuelta;

	read(fd,buffreg,LONG_key);
	buffreg[LONG_key]='\0';

	for(int i=0;i<=parti_total;i++)
	{
		vuelta=0;
		byte_pos=i*LONG_key;//lo calcula en el nrr
		lseek(fd2,(long)byte_pos,0);//coloca

		read(fd2,buffreg,LONG_key);
		buffreg[LONG_key]='\0';
		long_datos=strlen(buffreg);
		while((pos_bus=toma_campo(campo,buffreg,pos_bus,long_datos))>0)
		{
			if(vuelta==0)
				strcpy(numerokey[i].num_key,campo);
			if(vuelta==1)
				strcpy(numerokey[i].nrr_letra,campo);
			if(vuelta==2)
				strcpy(numerokey[i].tiempo_realkey,campo);
			numerokey[i].existe=1;
			numO=atoi(numerokey[i].num_key);
			numerokey[i].numero_ordenar=numO;
			vuelta++;
		}

		read(fd2,buffreg,LONG_key);
		buffreg[LONG_key]='\0';
		printf("\n");
	}
}*/

int main()
{
	int fd2,nomk,cityk,nack;
	int i,menu_elec,nrr;
	int par_pos,elen;
	int byte_pos;
	char nomarch[15],ele[3];
	long lseek();
	char buffreg[TAM_MAX_REG + 1];
	char fd2n[15]="llave_primaria3";
	char archnomk[15]="llave_nombre";
	char archcityk[15]="llave_city";
	char archnack[15]="llave_nacion";
	int primera_vez=0;

	printf("Proporcione el nombre del archivo: ");
	gets(nomarch);

	if((fd=open(nomarch,LECTESCRIT))<0)
	{
		fd=creat(nomarch,PMODE);
		encabezado.cont_reg=0;
		write(fd,&encabezado,sizeof(encabezado));
		primera_vez=1;
	}
	else
	{
		read(fd,&encabezado,sizeof(encabezado));
		parti_total=encabezado.cont_reg;
		duplicados(fd);
		//leepar();
	}

	if((fd2=open(fd2n,LECTESCRIT))<0)
	{
		fd2=creat(fd2n,PMODE);
	}
	else
	{
		leerfd2(fd2);
	}

	if((nomk=open(archnomk,LECTESCRIT))<0)
	{
		nomk=creat(archnomk,PMODE);
	}
	else
	{
		leernomk(nomk);
	}

	if((cityk=open(archcityk,LECTESCRIT))<0)
	{
		cityk=creat(archcityk,PMODE);
	}
	else
	{
		//leerfd2(cityk);
	}

	if((nack=open(archnack,LECTESCRIT))<0)
	{
		nack=creat(archnack,PMODE);
	}
	else
	{
		//leerfd2(nack);
	}

	int eleccion,veri_du;
	char respuesta[10];

	do
	{
		printf("%d",parti_total);
		printf("\tMENU PRINCIPAL\n");
		printf("\n1) Registro");
		printf("\n2) Tiempo");
		printf("\n3) Consultas");
		printf("\n4) Salir");
		gets(ele);
		elen=atoi(ele);

		switch(elen)
		{
			case 1:
				par_pos=registro(buffreg);
				if(par_pos==-1)
					break;
				byte_pos=encabezado.cont_reg * LONG_REG + sizeof(encabezado);
				lseek(fd,(long) byte_pos,0);//Ubica la posicion bytepos desde el inicio //El long es porque la funcion usa enteros largos
				write(fd,buffreg,LONG_REG);
				encabezado.cont_reg++;
				break;
			case 2:
					for(i=0; i<=parti_total;i++)
					printf("\n%s",nom_k[i].nombre_canon);
					printf("\n%s",nom_k[i].key_num);
					printf("\n%d",nom_k[i].key);
				break;
			case 3:
				for(i=0; i<=parti_total;i++)
					printf("\n%s",nom_k[i].nombre_canon);
				for(i=0; i<=parti_total;i++)
					printf("\n%s",city_k[i].city_canon);
				for(i=0; i<=parti_total;i++)
					printf("\n%s",nac_k[i].nac_canon);
				break;
			case 4:
				break;
			default:
				break;
		}
	}while(elen!=4);

	ordenar_structs();
	//printf("%s",participante[0].nom_atle);
	lseek(fd,0L,0);//El 0L es significa que es un entero largo
	write(fd,&encabezado,sizeof(encabezado));
	if(primera_vez==1)
	{
		guardarfd2(fd2,buffreg);
		escribe_nomk(nomk);
		escribe_cityk(cityk);
		escribe_nack(nack);
	}
	close(fd);
	close(fd2);
	close(nomk);
	close(cityk);
	close(nack);

	return 0;
}
