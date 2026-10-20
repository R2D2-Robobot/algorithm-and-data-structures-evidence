#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


//Esta function permite reutilizar la posibilidad de ingresar una fecha, se reconoce que falta la comprobacion del input ingresado. Puesto que permite
//ingresar numeros grandes.
long long escribirCodigoFecha(){
    long long codeinput;
    string texto_mes;
    int numero_mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
    char separador;
    
    cout << "Los meses se escriben con las primeras tres letras, comenzando por mayuscula, excepto por enero que es en minuscula" << endl;
    cout << "Ingresa la fecha a buscar, con el siguiente formato mes dia hora:minuto:segundo" << endl;
    cin >> texto_mes >> dia >> hora >> separador >> minuto >> separador >> segundo;

      if (texto_mes=="ene" ){numero_mes=1;}
      else if (texto_mes=="Feb" ){numero_mes=2;}
      else if (texto_mes=="Mar" ){numero_mes=3;}
      else if (texto_mes=="Abr" ){numero_mes=4;}
      else if (texto_mes=="May" ){numero_mes=5;}
      else if (texto_mes=="Jun" ){numero_mes=6;}
      else if (texto_mes=="Jul" ){numero_mes=7;}
      else if (texto_mes=="Ago" ){numero_mes=8;}
      else if (texto_mes=="Sep" ){numero_mes=9;}
      else if (texto_mes=="Oct" ){numero_mes=10;}
      else if (texto_mes=="Nov" ){numero_mes=11;}
      else if (texto_mes=="Dic" ){numero_mes=12;}
    //Las fechas se transforman en digitos numericos de multiplos de 10, esto permite una comparacion directa y eficiente evitando realizar o sobre
    //cargar operadores.
    codeinput = (numero_mes *100000000)+(dia*1000000)+(hora*10000)+(minuto*100)+segundo;
    cout << "Fecha Guardada con exito ;)" << endl;
    cout << "--------------------------------------" << endl;
    return codeinput;
}

// Esta funcion escribe el archivo de salida con las variables ya ordenadas, fuciona utilizando el arreglo de objetos A que y el arreglo de objetos 
//filtrados paraa escribir todas las lineas utilizando el respectivo indice.
void escribirArchivo(string A[], int filtrados[], int n){
    ofstream archivoSalida("salida.txt");

    for (int i = 0; i < n; i++){
        archivoSalida << A[filtrados[i]] << "\n";
    }
    archivoSalida.close();
}


/*Durante la iteracion anterior de este codigo ocurrio un bug, en donde los dias de 1 solo digito causaban un
desacomodo en la forma en la que nuestro codigo esperaba recibir cada pieza del string, despues de leer mas a fondo el problema
me encontre con la solucion. Usando la clase istrinstream podemos separar automaticamente cada pieza de la linea de acuerdo con el tipo
de variable que nuestro codigo espera, de esta forma hacemos el parseo de los datos mas flexible. */

//Esta funcion se encarga de recibir el archivo como parametro, un tamano de los arreglos e ir guardando las fechas transformadas en 
//codigos con numeros long. Estos numeros long se guardan en un arrelo B, seran los utiilizados para arreglar los indices de los datos.
void LectorYTraductor(ifstream &archivo, int &n, string A[], long long B[]) {
    string linea;
    int mesint = 0;
    string dup;

    //Variables de pieza del archivo (usados por istringstream)
    string mes;
    int dia;
    int hora;
    char sep; //Separador usado para recibir los dobles puntos
    int minuto;
    int segundo;
    while (getline(archivo, linea)) {
        size_t posicionR = linea.find("R:");
        if (posicionR != string::npos) {
            
            // 1. Guardamos la LÍNEA COMPLETA en A
            A[n] = linea; 
            istringstream stream_linea(linea);
            stream_linea >> mes >> dia >> hora >> sep >> minuto >> sep >> segundo;

            if (mes == "ene" )      {mesint = 1; }
            else if (mes == "Feb" ) { mesint = 2; }
            else if (mes == "Mar" ) { mesint = 3; }
            else if (mes == "Abr" ) { mesint = 4; }
            else if (mes == "May" ) { mesint = 5; }
            else if (mes == "Jun" ) { mesint = 6; }
            else if (mes == "Jul" ) { mesint = 7; }
            else if (mes == "Ago" ){ mesint = 8; }
            else if (mes == "Sep" ) { mesint = 9; }
            else if (mes == "Oct" ) { mesint = 10; }
            else if (mes == "Nov" ) { mesint = 11; }
            else if (mes == "Dic") { mesint = 12 ; }




            long long code=(mesint *100000000)+(dia*1000000)+(hora*10000)+(minuto*100)+segundo;
//code envez, de ser stoi debe ser stoll porque el codigo va a ser muy largo
//también cambiar la lsita b a que reciba stoll en todo el codigo para evitar errores
            B[n]=code;
            n++;
        }
    }
}

//Esta funcion se utiliza para comprobar queel valor de codigos long, se encuentra e un rango determinado, su utilidad principal
//era para funcionar como condicional de la busqueda. Despues de una actualizacion, ahora actua como poco mas que una condicional regular
bool isInRange(long long l, long long r, long long v){
    if (v >=l && v <= r){
        return true;
    }
    else{
        return false;
    }
}

// wow es el super mega codigo porque aui bsucamos en B, luego B va a buscar en la lista 
//con todo los nombres y eso. 

//La busqueda Binaria se utiliza parae encontrar el primer elemento ordenado dentro de un rango especiffico, apartir del cual
//empezar a enumaerar iterar los objetos que se encuentran en el rango. Funciona en base al arreglo de todos los numeros largos de fecha.
//Una variable l y una variable r.
int busquedaBinaria(long long B[], int n, long long l, long long r, int filtrados[]) {

    int izquierda = 0;
    int derecha = n - 1;
    int centro;
    int resultado = -1;

    while (izquierda <= derecha) {

        centro = izquierda + ((derecha - izquierda) / 2);

        if (B[filtrados[centro]] >= l) {

            resultado = centro;

            // Intentamos encontrar uno todavía más a la izquierda
            derecha = centro - 1;
        }
        else {
            izquierda = centro + 1;
        }
    }

    // Verificamos que el valor encontrado también esté debajo de r
    if (resultado != -1 && isInRange(l, r, B[filtrados[resultado]])) {
        return resultado;
    }

    return -1;
}

//Esta funcion recibe 2 fechas, decide cual de las dos es el lado izquierdo y cual el derecho, luego utiliza la funcion de busqueda binaria
//para encontrar el registro mas cercano a la fecha de inicio. Luego itera hasta que un registro se encuentre fuera del rango.

void busquedaRango(long long B[], int n, long long date1, long long date2, int filtrados[], string  A[], int index_range[], int &index_range_size) {
    //Inicia variables y decide cual de los dos numeros es menor y cual mayor con el objetivo de hacer una busqueda binaria
    long long date_lowervalue, date_uppervalue;
    if (date1 < date2){
        date_lowervalue = date1;
        date_uppervalue = date2;
    }
    else{
        date_lowervalue = date2;
        date_uppervalue = date1;
    }
    int first_date_index = busquedaBinaria(B, n, date_lowervalue, date_uppervalue, filtrados);
    
    while (isInRange(date_lowervalue, date_uppervalue, B[filtrados[first_date_index]])) {
        cout << "Found: " << A[filtrados[first_date_index]] << endl;
        index_range[index_range_size]= filtrados[first_date_index];
        index_range_size++;
        first_date_index++;

    }

}

//Es el algoritmo de quicjsr, en este caso utilizamos una funcion modular para poder ordenar mejor
int partition(long long  B[], int l, int r,int filtrados[]){
    int pivot=filtrados[r];
    int i=l-1;
    int j,aux;
    for (j = l;j < r; j++ ){
        if (B[filtrados[j]] < B[pivot]){
            i++;
            aux=filtrados[i];
            filtrados[i]=filtrados[j];
            filtrados[j]=aux;
            
        }

    }
    aux=filtrados[i+1];
    filtrados[i+1]=filtrados[r];
    filtrados[r]=aux;
    return i + 1;
    }
    



//Funcion de quicksort, recibe el arreglo de numeros longs, un indice izquierdo y un indice derecho
void quicksort( long long  B[],int l,int r,int filtrados[]){
    if (l<r){
        int pivot=partition(B,l,r,filtrados);
        quicksort(B,l,pivot-1,filtrados);
        quicksort(B, pivot+1 ,r,filtrados);
    }
}



int main() {
    ifstream archivo("./lib/orders.txt");
    string linea;
    int n=0;
    int i=0;
    string  A[10000];
    long long B[10000];
    string  mes; 
    int index_range[10000];
    int index_range_size = 0;
    LectorYTraductor(archivo,n,A,B);

    int filtrados[10000];
    int cuantos = 0;
 
    for (i = 0; i< n; i++)
    { // cout <<i << " " << A[i] << endl;
        filtrados[cuantos] = i;
        cuantos++;
    }


    quicksort(B, 0, n - 1, filtrados); // Ascendente
    cout << "\nVALORES ORDENADOS POR QUICK SORT (ASCENDENTE)" << endl;
    //Se puede cambiar libremente para debuggeo para imprimir todos, aunque el archivo ya lo hace.

    //Imprime los primeros 10
    for (i = 0; i < 10; i++) {   
        int pos = filtrados[i];
        
        cout<<"|"<<B[pos]<<"| "<<",";
        cout << A[pos] << " (Clave: " << B[pos] << ")" << endl;
    }
    escribirArchivo(A, filtrados, n);

    long long codeinput1 = escribirCodigoFecha();
    long long codeinput2 = escribirCodigoFecha();
    
    busquedaRango(B, n, codeinput1, codeinput2, filtrados, A, index_range, index_range_size);

    cout << "Quieres guardar las lineas filtradas en un archivo? (y/n)" << endl;
    char respuesta;
    cin >> respuesta;

    if (respuesta == 'y' || respuesta == 'Y'){
        ofstream archivoSalida("resultados_busqueda.txt");
        for (int i = 0; i < index_range_size; i++){
            archivoSalida << A[index_range[i]] << "\n";
        }
        archivoSalida.close();
    }
    
    return 0;
}
