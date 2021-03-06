#include <stdio.h>
#include <pthread.h>
#include <time.h>

void *suma();
void *resta();
void *multi();
void *trans();
void *inver();
void *imp();

int main(void){
	clock_t start=clock();
	pthread_t id_hilo[6];
	int i=0;
	pthread_create (&id_hilo[0],NULL,(void*)suma,NULL);
	pthread_create (&id_hilo[1],NULL,(void*)resta,NULL);
	pthread_create (&id_hilo[2],NULL,(void*)multi,NULL);
	pthread_create (&id_hilo[3],NULL,(void*)trans,NULL);
	pthread_create (&id_hilo[4],NULL,(void*)inver,NULL);
	for(i=0;i<5;i++) pthread_join(id_hilo[i],NULL);
	pthread_create (&id_hilo[5],NULL,(void*)imp,NULL);
	pthread_join(id_hilo[5],NULL);
	printf("Tiempo transcurrido es: %f\n", ((double)clock()-start)/CLOCKS_PER_SEC);
}

void *suma(){
	int m1[12][12];
	int m2[12][12];
	int i=0;
	int j=0;
	FILE *fin = fopen("datos.out","r");
	//Se leen los datos en la matriz 1
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin, "%d",&m1[i][j]);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin,"%d",&m2[i][j]);
	fclose(fin);
	//Se imprimen en archivo los resultados
	FILE *fout = fopen("suma.out", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%d ",m1[i][j]+m2[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
}
void *resta(){
	int m1[12][12];
	int m2[12][12];
	int i=0;
	int j=0;
	FILE *fin = fopen("datos.out","r");
	//Se leen los datos en la matriz 1
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin, "%d",&m1[i][j]);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin,"%d",&m2[i][j]);
	fclose(fin);
	//Se imprimen en archivo los resultados
	FILE *fout = fopen("resta.out", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%d ",m1[i][j]-m2[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
}
void *multi(){
	int m1[12][12];
	int m2[12][12];
	int mr1[12][12];
	int i=0;
	int j=0;
	FILE *fin = fopen("datos.out","r");
	//Se leen los datos en la matriz 1
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin, "%d",&m1[i][j]);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin,"%d",&m2[i][j]);
	fclose(fin);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			mr1[i][j]=m1[i][0]*m2[0][j] + m1[i][1]*m2[1][j]  + m1[i][2]*m2[2][j]  
			+ m1[i][3]*m2[3][j]  + m1[i][4]*m2[4][j]  + m1[i][5]*m2[5][j]  + m1[i][6]*m2[6][j]  
			+ m1[i][7]*m2[7][j]  + m1[i][8]*m2[8][j]  + m1[i][9]*m2[9][j];
	//Se imprimen en archivo los resultados
	FILE *fout = fopen("multi.out", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%d ",mr1[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
}
void *trans(){
	int m1[12][12];
	int m2[12][12];
	int mr1[12][12];
	int mr2[12][12];
	int i=0;
	int j=0;
	FILE *fin = fopen("datos.out","r");
	//Se leen los datos en la matriz 1
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin, "%d",&m1[i][j]);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin,"%d",&m2[i][j]);
	fclose(fin);
	//Transpuesta 1
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			mr1[i][j]=m1[j][i];
	//Transpuesta 2
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			mr2[i][j]=m2[j][i];
	//Se imprimen en archivo los resultados
	FILE *fout = fopen("transpuesta.out", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%d ",mr1[i][j]);
		}
		fprintf(fout,"\n");
	}
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%d ",mr2[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
}
void *inver(){
	FILE *fin = fopen("datos.out","r");
	int i,j;
	float mf1[12][12];
	float mf2[12][12];
	float mfr1[12][12];
	float mfr2[12][12];
	//Se leen los datos en la matriz 1
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin, "%f",&mf1[i][j]);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin,"%f",&mf2[i][j]);
	fclose(fin);
	//Se crea la matriz diagonal
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(i==j) mfr1[i][j]=mfr2[i][j]=1;
			else mfr1[i][j]=mfr2[i][j]=0;
		}
	}
	for(i=0;i<10;i++){
		float divi=mf1[i][i];
		float divi2=mf2[i][i];
		j=i;
		for(j=i;j<10;j++){
			mf1[i][j]/=divi;
			mfr1[i][j]/=divi;
			mf2[i][j]/=divi2;
			mfr2[i][j]/=divi2;
		}
		//imprimirM();
		int k=0;
		for(k=i+1;k<10;k++){
			float num=mf1[k][i];
			float num2=mf2[k][i];
			//printf("El numero %f\n",num);
			for(j=i;j<10;j++){
				//printf("El valor %f\n",(mf1[i][j]*num));
				mf1[k][j]-=(mf1[i][j]*num);
				mfr1[k][j]-=(mf1[i][j]*num);
				mf2[k][j]-=(mf2[i][j]*num2);
				mfr2[k][j]-=(mf2[i][j]*num2);
			}
		}
	}
	for(i=0;i<10;i++){
		for(j=i+1;j<10;j++){
			mfr1[i][j]-=mf1[i][j];
			mfr2[i][j]-=mf2[i][j];
		}
	}
	//Se imprimen los resultados
	FILE *fout = fopen("inversa.out", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%.2f ",mfr1[i][j]);
		}
		fprintf(fout,"\n");
	}
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%.2f ",mfr2[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
}
void *imp(){
	int i,j;
	FILE *fin = fopen("suma.out","r");
	printf("El resultado de la suma es: \n" );
	int aux;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%d",&aux);
			printf("%d ",aux);
		}
		printf("\n");
	}
	printf("\n");
	fclose(fin);
	fin = fopen("resta.out","r");
	printf("El resultado de la resta es: \n" );
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%d",&aux);
			printf("%d ",aux);
		}
		printf("\n");
	}
	printf("\n");
	fclose(fin);
	fin = fopen("multi.out","r");
	printf("El resultado de la multiplicacion es: \n" );
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%d",&aux);
			printf("%d ",aux);
		}
		printf("\n");
	}
	printf("\n");
	fclose(fin);
	fin = fopen("transpuesta.out","r");
	printf("Los resultados de las transpuestas son: \nPrimer matriz: \n" );
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%d",&aux);
			printf("%d ",aux);
		}
		printf("\n");
	}
	printf("\n");
	printf("Segunda matriz\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%d",&aux);
			printf("%d ",aux);
		}
		printf("\n");
	}
	printf("\n");
	fclose(fin);
	fin = fopen("inversa.out","r");
	printf("Los resultados de las inversiones son: \nPrimer Matriz:\n" );
	float aux1;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%f",&aux1);
			printf("%.2f ",aux1);
		}
		printf("\n");
	}
	printf("\n");
	printf("Segunda Matriz:\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fscanf(fin, "%f",&aux1);
			printf("%.2f ",aux1);
		}
		printf("\n");
	}
	printf("\n");
	fclose(fin);
}