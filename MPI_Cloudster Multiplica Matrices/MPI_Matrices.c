#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>	//Libreria que ocuparemos para medir el tiempo

int main (int argc, char *argv []){
	int rank, size;
	char hostname[MPI_MAX_PROCESSOR_NAME];  /*Nombre de cada uno de nuestros nodos*/
	int lenhostname;  /*Longitud del hostname*/
	int *MatrizA=NULL;	 /*Matriz a multiplicar numero 1*/
	int *MatrizB=NULL;  /*Matriz a multiplicar numero 2*/
	int *MatrizR=NULL;  /*Matriz en donde guardamos los resultados*/
	int *resultrow=NULL;
	int *resultado=NULL;
	int *resultadof=NULL;
	int MatrizAx[100][100];
	int MatrizBx[100][100];
	int MatrizNA[100][100];
	int MatrizNB[100][100];
	int MatrizNR[100][100];
	int recorre=0;
	int contador=0;
	int contador2=0;
	int i, j, m, n;		/*Variables enteras para los ciclos de lectura*/
	int rv; 	/* Bandera de envio para el broadcast*/
	int aux=0;
	int aux2=0;
	int aux3=0;
	int recostruir;
	MPI_Status status;
	
/*Procedemos a iniciar MPI*/
	MPI_Init(&argc, &argv);
/*Inicializaremos la variable apartir de clock*/ 	
clock_t inicio = clock();
 /*Procedemos a determinar el numero total de procesos y 
 de cual somos como tambien a que nodo pertenece*/
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(hostname, &lenhostname);

	printf("Soy el proceso %d de %d en %s\n",rank, size, hostname);
/*Procedemos a leer las matrices de los archivos*/
/*Sabemos que rank 0 pertenece a el proceso padre por lo cual haremos uso de un if para identificarlo*/
	if (rank==0) /*Aqui inica el proceso PADRE*/
	{
		printf("Proceso Maestro en linea...\n");
		FILE *Arc=fopen("/media/Share/MatrizA.txt","r");
		FILE *Brc=fopen("/media/Share/MatrizB.txt","r");
		MatrizA=malloc(900*sizeof(int));
		MatrizB=malloc(900*sizeof(int));
			
			for(i=0;i<30;i++){
				for(j=0;j<30;j++){
					fscanf(Arc, "%d", &MatrizAx[i][j]);
					MatrizA[recorre]=MatrizAx[i][j];
					recorre++;
				}
			}
			fclose(Arc);		
			recorre=0;
			for(m=0;m<30;m++){
				for(n=0;n<30;n++){
					fscanf(Brc, "%d", &MatrizBx[m][n]);
					MatrizB[recorre]=MatrizBx[m][n];
					recorre++;
				}
			}
			fclose(Brc);
		recorre=0;
		/*Transmitimos las matrices a todos los nodos para la solucion*/
		rv=MPI_Bcast(MatrizA, 900, MPI_INT, 0, MPI_COMM_WORLD);
		printf("La matriz uno a sida enviada con exito %d\n",rv);
		rv=MPI_Bcast(MatrizA, 900, MPI_INT, 0, MPI_COMM_WORLD);
		printf("La matriz dos a sido envida con exito %d\n",rv);
		resultrow=malloc(1*sizeof(int));
		resultado=malloc(300*sizeof(int));
		resultadof=malloc(900*sizeof(int));
		
		while(recorre<3){
			MPI_Recv(resultrow, 1, MPI_INT,MPI_ANY_SOURCE,1, MPI_COMM_WORLD, &status);
			MPI_Recv(resultado, 300, MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD, &status);
			recorre++;
			printf("El resultado es el siguiente %d\n", resultrow[0]);
				if(resultrow[0] == 1)  recostruir=0;
				else if(resultrow[0] ==2)	recostruir=300;
				else if(resultrow[0] ==3)	recostruir=600;
						
					for(i=recostruir;i<(recostruir+300);i++){
						resultadof[i]=resultado[i - recostruir];
					}
				
			printf("%d\n",recorre);
		}
		printf("LA MATRIZ RESULTADO ES LA SIGUIENTE\n");
			for(j=0; j<30;j++){
				for(i=0; i<30;i++){
					printf("%d ",resultadof[aux3]);
					aux3++;
				}
			printf("\n");
			}
		
	}else
	{	/*Aqui iniciaran los demas procesos llamados HIJOS*/
		printf("Nodos\n");
		MatrizA=malloc(900*sizeof(int));
		MatrizB=malloc(900*sizeof(int));
		rv=MPI_Bcast(MatrizA,900,MPI_INT, 0, MPI_COMM_WORLD);
		rv=MPI_Bcast(MatrizB,900,MPI_INT, 0, MPI_COMM_WORLD);
		
			for(i=0; i<30; i++){
				for(j=0; j<30; j++){
					MatrizNA[i][j]=MatrizA[aux];
					MatrizNB[i][j]=MatrizB[aux];
					//printf("%d ",MatrizNA[i][j]);
					aux++;
				}
			//printf("\n");
			}
		/*Ahora tenemos que separar la matriz en 3 secciones para que la resuelva cada uno de los nodos*/
		/*Como sabemos que son 3 nodos hijos entonces divirdiremos la matriz en 3*/
		resultado=malloc(300*sizeof(int));
		contador=rank;
		if(contador==1){
			contador2=0;
		}else if(contador==2){
			contador2=10;
		}else if(contador==3){
			contador2=20;
		}
		printf("El contador tiene valor de %d",contador);

			for(n=contador2;n<contador2+10;n++){
				for(m=0;m<30;m++){
				MatrizNR[n][m]=MatrizNA[n][0]*MatrizNB[0][m]+MatrizNA[n][1]*MatrizNB[1][m]+MatrizNA[n][2]*MatrizNB[2][m]+MatrizNA[n][3]*MatrizNB[3][m]+MatrizNA[n][4]*MatrizNB[4][m]+MatrizNA[n][5]*MatrizNB[5][m]
						+MatrizNA[n][6]*MatrizNB[6][m]+MatrizNA[n][7]*MatrizNB[7][n]+MatrizNA[n][8]*MatrizNB[8][m]+MatrizNA[n][9]*MatrizNA[9][m]+MatrizNA[n][10]*MatrizNB[10][m]
						+MatrizNA[n][11]*MatrizNB[11][m]+MatrizNA[n][12]*MatrizNB[12][m]+MatrizNA[n][13]*MatrizNB[13][m]+MatrizNA[n][14]*MatrizNB[14][m]+MatrizNA[n][15]*MatrizNB[15][m]
						+MatrizNA[n][16]*MatrizNB[16][m]+MatrizNA[n][17]*MatrizNB[17][n]+MatrizNA[n][18]*MatrizNB[18][m]+MatrizNA[n][19]*MatrizNA[19][m]+MatrizNA[n][20]*MatrizNB[20][m]
						+MatrizNA[n][21]*MatrizNB[21][m]+MatrizNA[n][22]*MatrizNB[22][m]+MatrizNA[n][23]*MatrizNB[23][m]+MatrizNA[n][24]*MatrizNB[24][m]+MatrizNA[n][25]*MatrizNB[25][m]
						+MatrizNA[n][26]*MatrizNB[26][m]+MatrizNA[n][27]*MatrizNB[27][n]+MatrizNA[n][28]*MatrizNB[28][m]+MatrizNA[n][29]*MatrizNA[29][m];
				resultado[aux2]=MatrizNR[n][m];
				aux2++;
				}
			}
		aux2=0;
		resultrow=malloc(1*sizeof(int));
		resultrow[0]=contador;
		MPI_Send(resultrow,1,MPI_INT, 0, 1, MPI_COMM_WORLD);
		MPI_Send(resultado,300, MPI_INT, 0, 1, MPI_COMM_WORLD);
		if (resultrow != NULL) free(resultrow);
		if (MatrizA != NULL) free(MatrizA);
		if (MatrizB != NULL) free(MatrizB);
		if (resultado != NULL) free(resultado);
	}

/*Imprimimos el tiempo*/
        printf("\nEl tiempo transcurrido es %f \n\n",((double)clock()-inicio)/CLOCKS_PER_SEC);
/*Funcion que Finaliza el MPI*/
	MPI_Finalize();
	return 0;
}

