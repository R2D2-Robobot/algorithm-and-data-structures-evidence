#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//========================== Declaracion Clase DOuble Linked List =========================
// clase Node: un valor 
// y punteros a nodo previo y siguente 
// ======= Begggining of node class ========
template <typename T>
class Node
{	public:
		T dato;		        //	valor almacenado
		Node<T> *next;		//	puntero a nodo siguente
        Node<T> *prev;     // puntero a nodo previo
	
		Node(T dato)
		{	this->dato = dato;
			this->next = NULL;
			this->prev = NULL;
		}
};

//==== End of Node class ======

//===== Begginning of listDouble class =======
template <typename T>
class ListDouble
{	Node<T> *first;   // Puntero al nodo inicial 
    Node<T> *last;    // Puntero al nodo final
	int current_size;      //Numero de elementos totales
	private:
	Node<T>* lookAtIndex(int indx); // This function was made to add some modularity, it looks for a pointer at specific index, kept in private to avoid malfunction

	public:
		ListDouble() 
		{	this->first = NULL;  //  puntero al nodo inicial
            this->last = NULL;
            this->current_size = 0;
           
		}

		int getSize(){ return current_size; } 	// Devuelve cuantos elementos hay
		void showList(); 				// Imprime los elementos
		void showListReverse();
		
		void insertLast(T);		//	Agregua valor al inicio
		void insertFirst(T);		//	Agrega valor al fianl
		void insertAtIndex(int, T) ; // Agrega valor en un indice

		void deleteFirst();         // Elimina del inicio
		void deleteLast();			// Elimina al final
		void deleteAtIndex(int indx);       //elimina un valor en el indice expecificado	
		bool isEmpty() {return current_size == 0;}
		Node<T>* find(T value, int indx); // Busca un valor en la lista

		void update(int, T); // Actualiza el valor en un indice
		

    
};

template <typename T>
void ListDouble<T>::showList()
{    
    Node<T> *current = first; 
    cout << "Size " << this->current_size << endl;
    for(int i = 0; i < current_size; i++)
    {   
		cout << current->dato << "->\t" ;
        current = current->next;
    }
}

template <typename T>
void ListDouble<T>::showListReverse()
{    
    Node<T> *current = last; 
    cout << "Size " << this->current_size << endl;
    for(int i = 0; i < current_size; i++)
    {   
		cout << current->dato << "->\t" ;
        current = current->prev;
    }
}

template <typename T>
void ListDouble<T>::insertLast(T value) {
	Node<T> *nuevo = new Node<T>(value);
	if (isEmpty()){
		first = nuevo;
		last = nuevo;
		nuevo->next = nuevo;
		nuevo->prev = nuevo;
		
	}
	else{
		last->next = nuevo;
		first->prev = nuevo;
		nuevo->prev = last;
		nuevo->next = first;
		last = nuevo;

	}
	this->current_size++;
}

template<typename T>
void ListDouble<T>::insertFirst(T value){
	Node<T>*nuevo = new Node<T>(value);
	if (isEmpty()){
		first = nuevo;
		last = nuevo;
		nuevo->next = nuevo;
		nuevo->prev = nuevo;	
	}
	else{
		first->prev = nuevo;
		last->next = nuevo;
		nuevo->next = first;
		nuevo->prev = last;
		first = nuevo;
	}
	this->current_size++;
}

template<typename T>
void ListDouble<T>::insertAtIndex(int indx, T value){
	if (indx > this->current_size || indx < 0){
		cout << "ERROR Index is not valid!! try again" << endl; 
	}
	else if (indx == 0){
		insertFirst(value);
	}
	else if (indx == this->current_size){
		insertLast(value);
	}
	else{
		Node<T>* current = lookAtIndex(indx - 1);
		Node<T>* nuevo = new Node<T>(value);
		Node<T>* aux = current->next;
		current->next = nuevo;
		nuevo->next = aux;
		aux->prev = nuevo;
		nuevo->prev = current;
		current_size++;
		}
}

template<typename T>
Node<T>* ListDouble<T>::lookAtIndex(int indx){
	if (indx <= (current_size/2)) {
		Node<T>* current = this->first;
		for (int i = 0; i < indx; i++){
			current = current->next;
		} 
		return current;
	}
	else {
		Node<T>* current = this->last;
		for (int i = current_size - 1; i > indx; i--){
			current = current->prev;
		}
		return current;
	}
}

template<typename T>
void ListDouble<T>::deleteFirst(){
	if (current_size == 0) {
		cout << "Error, they are not elements in the list!!!!" << endl;
	}
	else{
		Node<T>* aux = this->first;
		this->first = aux->next;
		delete aux;
		current_size--;
	}
}

template<typename T>
void ListDouble<T>::deleteLast(){
	if (current_size == 0) {
		cout << "Error, they are not elements in the list!!!!" << endl;
	}
	else{
		Node<T>* aux = this->last;
		this->last = aux->prev;
		delete aux;
		this->current_size--;
	}
}

template<typename T>
void ListDouble<T>::deleteAtIndex(int indx){
	if (current_size == 0){
		cout << "ERROR list has no nodes!!" << endl; 
	}
	else if (indx == 0){
		deleteFirst();
	}
	else if (indx == this->current_size){
		deleteLast();
	}
	else{
		Node<T>* current = lookAtIndex(indx);
		Node<T>* aux1 = current->next;
		Node<T>* aux2 = current->prev;
		aux1->prev = aux2;
		aux2->next =aux1;
		delete current;
		current_size--;
		}
}
template<typename T> 
void ListDouble<T>::update(int indx, T value){
	if (indx < 0 || indx >= current_size){
		cout << "ERROR index is not valid!!" << endl;
	}
	else{
		deleteAtIndex(indx);
		insertAtIndex(indx, value);
	}
}

//=========================== Fin de la declaracion de la clase Double Linked List =========================

//=================== Stack Class ====================

template <typename T>
class Stack {
    private:
    ListDouble<T>* data;
    int max_size;
    int current_size;

    public:

    Stack(){
        data = new ListDouble<T>();
        this-> current_size = 0;
        this-> max_size = 1000;
    }

    Stack(T value){
        data = new ListDouble<T>();
        data->insertLast(value);
        this->current_size++;
        this->max_size = 1000;

    }   
    void push(T value);
    T pop();
    void show();
    bool isEmpty(){return (current_size == 0);}
    int getSize(){return current_size;}
    T getTop() {return data->retrieveLast();}

};

template<typename T>

//Esta funcion es O(1) dado que el pointer last ya se encuentra como dato en el sistema
void Stack<T>::push(T value){
    data->insertLast(value);
}

//Esta operacion es O(1) onsite dado que ya se tiene e puntero hacia la ultima pocision
template<typename T>
T Stack<T>::pop(){
    T aux = data->retrieveLast();
    data->deleteLast();
    return aux;
}

//Esta operacion es O(n), ya que la funcion pasa por cada uno de los elementos de manera iterativa para imprimirlo
template<typename T>
void Stack<T>::show(){
    data->showList();
}

//======================================================
class LogEntry {
    private:
    long long timestamp;
    string restaurant_name;
    int price;
    string order_name;

    public:

    LogEntry(long long tsmp, string rn, int p, string on){
        timestamp = tsmp;
        restaurant_name = rn;
        price = p;
        order_name = on;
    }
    LogEntry() {
        timestamp = 0;
        restaurant_name = "";
        price = 0;
        order_name = "";
    }

    long long getTimeStamp(){return timestamp;}
    string getRestaurantName(){return restaurant_name;}
    int getPrice(){return price;}
    string getOrderName(){return order_name;}

    // I had to overload the cout operator for showList() to work correctly, although it is not very optimal
    // to print a few thousand entrys...
    friend ostream& operator<<(ostream &out, LogEntry &entry) {
    out << entry.getTimeStamp() << " " << entry.getRestaurantName()
        << " " << entry.getOrderName() << " (" << entry.getPrice() << ")";
    return out; 
    }
    
};



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
void LectorYTraductor(ifstream &archivo, int &n, string A[], long long B[], ListDouble<LogEntry> &lista) {
    string linea;
    int mesint = 0;
    string dup;


    //Variables de pieza del archivo (usados por istringstream)
    string mes;
    int dia;
    int hora;
    string restaurant_name;
    string order;
    int price;


    char sep; //Separador usado para recibir los dobles puntos
    char padding;
    int minuto;
    int segundo;

    while (getline(archivo, linea)) {
        size_t posicionR = linea.find("R:");
        if (posicionR != string::npos) {
            
            // 1. Guardamos la LÍNEA COMPLETA en A
            A[n] = linea; 
            istringstream stream_linea(linea);
            stream_linea >> mes >> dia >> hora >> sep >> minuto >> sep >> segundo >> padding >> padding;
            //Leemos la linea hasta encontrarnos con :, lo que nos dejaria una entrada asi:
            //Jun 24 19:39:45 R:La Terraza del Mar O
            //Asi que eliminamos los dos ultimos caracteres
            getline(stream_linea, restaurant_name, ':');
            restaurant_name.erase(restaurant_name.size() - 2);
            getline(stream_linea, order, '(');
            //Anadimos la ultima variable que falta
            stream_linea >> price;

            
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
            LogEntry entry(code, restaurant_name, price, order);
            lista.insertLast(entry);
            n++;

            //--------
            
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


////////////////////quicksort en lista//////////////////////////////

template <class T>
Node<T>* partitionDL( ListDouble<T> datos, Node<T>* L , Node<T>* R)
{   Node<T> *pivot = R;
    Node<T> *j = L;
    Node<T> *i = NULL;

    T aux; 
    //for (j = L ; j < R ; j++)
    while ( j != R)
    {   if ( j->dato < pivot->dato )
        {   if (i == NULL )
            { i = L; }
            else
            { i = i->next; }
            
            aux = i->dato ;
            i->dato = j->dato;
            j->dato = aux; 
        }
        j = j->next;
    }
    if (i == NULL )
    { i = L; }
    else
    { i = i->next; }

    aux = i->dato; 
    i->dato = pivot->dato;
    pivot->dato = aux;
    
    return i;
}

template <class T>
void quicksortDL(  ListDouble<T> datos )
{   Node<T>* L = datos.getFirst();
    Node<T>* R = datos.getLast();

    Stack< Node<T>* > stack;
    stack.push(L);
    stack.push(R);

    Node<T>* pivot; 
    while ( ! stack.isEmpty() )
    {   R = stack.pop();
        L = stack.pop();
        pivot = partition(datos, L, R);

        if ( L != pivot && L != pivot->prev )
        {   stack.push(L);
            stack.push(pivot->prev); // aqui se me habia quedado privot-1
        }
        if ( R != pivot && R != pivot->next )
        {   stack.push(pivot->next); // y aqui privot+1
            stack.push(R);
        }
    }
}

int main() {
    ifstream archivo("./lib/orders.txt");
    string linea;
    ListDouble<LogEntry> orders_without_order;
    int n=0;
    int i=0;
    string  A[10000];
    long long B[10000];
    string  mes; 
    int index_range[10000];
    int index_range_size = 0;
    LectorYTraductor(archivo,n,A,B, orders_without_order);

    

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

    //orders_without_order.showList(); 
    return 0;
}
