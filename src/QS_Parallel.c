#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <mpi.h>
#include <stdbool.h>


// Funció quicksort
// int pointer *val: Punter que apunta a un vector de dades compartit en memoria. 
// int ne: Indica la quantitat de dades que podem modificar del nostre vector apuntat per *val.
// per tant l'índex màxim per a accedir al vector *val és ne - 1 
void qs(int *val, int ne)
{
	int i, f;  // i es l'index per l'esquerra, f index per la dreta 
	int pivot, vtmp, vfi;  // valor pivot contra el que ordenarem, vtmp valor que estem ordenant, vfi variable auxiliar que conté el valor a ordenar
	//quan acabem de colocar un valor DESPRÉS del pivot, ja que no tenim espais buits i la necessitem.

	pivot = val[0];  // Inicialment escollim arbitrariament el valor de la primera posicio com a pivot
	i = 1;  // índex mínim per a accedir al vector (comencem a i = 1 perquè a i = 0 ja hi tenim al pivot)
	f = ne - 1;  // índex màxim per a accedir al nostre vector global
	vtmp = val[i];  // emmagatzemmem de manera temporal el valor a la posició val[1] per a tenir el primer valor a col·locar

	while (i <= f)  // mentre el índex inicial no superi a l'índex final
	{
		if (vtmp < pivot)  // Si el valor temporal (el que estem ordenant) és més petit que el pivot...
		{
			val[i - 1] = vtmp;  // Movem el valor temporal a la posició que acabem de deixar lliure (a la primera iteració al lloc on estava el pivot)
			i++;  // passem al següent element 
			vtmp = val[i];  // Ara que hem colocat el vtmp carreguem el següent valor a ordenar
		}
		else  // si es mes gran
		{
			vfi = val[f];  // guardem un valor a la dreta del pivot per a fer lloc per al nou valor
			val[f] = vtmp;  // guardem el valor que estavem ordenant
			f--;  // passem al següent element
			vtmp = vfi;  // emmagatzemmem el valor temporal com a nou valor a ordenar
		}
	}
	val[i - 1] = pivot;  // Un cop els dos índexos es creuen (i > f, i - 1 = f) coloquem el pivot a la posició i - 1 per a que els dos 
	// sub vectors es trobin ordenats
 
 	// En principi aquests dos ifs s'activen i porten dues trucades recursives que reordenen els dos subvectors
 	// Si no es aixi, vol dir que el pivot escollit era major o menor que la resta d'elements en l'array (es el pitjor cas al escollir un pivot) 
 	// Després repartim els dos subvectors en dues crides recursives, recalculant els indexos que passem a la funció
	if (f > 1) qs(val, f);  
	if (i < ne - 1) qs(&val[i], ne - f - 1);
}

// Funció merge reescrita
// 
int merge2_different(int* in1, int n_in1, int* in2, int n_in2, int *vo)
{
	int i, posi = 0, posj = 0; 
 
	for (i = 0; i < n_in1 + n_in2; i++)  // recorrem el conjunt dels dos vectors
		// si hem acabat amb el vector j o no hem acabat el vector i & el valor al vector i es menor o igual que el valor al vector j 
		if ( ((posi < n_in1) && (in1[posi] <= in2[posj])) || (posj >= n_in2)) 
			vo[i] = in1[posi++];
		else 
			vo[i] = in2[posj++];
	return n_in2 + n_in1;
}

int main(int nargs,char* args[])
{
	//printf("rili");
	int closest_powerof2 = 0, ideal_num_processos, total_processos, id, ndades = atoi(args[1]), parts = atoi(args[2]);
	for (ideal_num_processos = 1; ideal_num_processos <= parts; ideal_num_processos *= 2) closest_powerof2++; 
	
	MPI_Init(&nargs, &args);	// Inicialitzem entorn paralel
	MPI_Comm_rank(MPI_COMM_WORLD, &id); 	// Obtenim nombre de processos 
	MPI_Comm_size(MPI_COMM_WORLD, &total_processos); 	// Obtenim el numero total de processos 

	int num_received_values, i, counter = 0, proces_objectiu, porcio = ndades / parts, residu = ndades % parts, acumulador = 0;
	int *vin, *vout, *vtmp, *vin2;
	printf("Caco %d, porcio %d \n", id, porcio);	
	fflush(stdout);
	int * valors=malloc((ndades+1)*sizeof(int));  
	printf("Caca %d \n", id);	
	fflush(stdout);
	long long sum = 0;
	MPI_Status estat;
	MPI_Request request;
	int *num_elements = malloc(sizeof(int) * parts);
	int *offsets = malloc(sizeof(int) * parts);
	int a=0;
	// Vector initialization
        for (i = 0; i < ndades; i++){
		if((i/porcio)==id){
        		valors[i%porcio] = rand();
		}
		else{
			a = rand();
		}
	}
	qs(&valors[0], porcio);
        MPI_Finalize();
	return 0;
}
