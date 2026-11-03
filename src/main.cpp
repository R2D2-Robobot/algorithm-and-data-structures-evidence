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
        Node<T>* getFirst(){  return this->first; }//nodo necesari o para el funcionamiento de partitionDL y QuickDl

        Node<T>* getLast(){  return this->last; }//nodo necesari o para el funcionamiento de partitionDL y QuickDl



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


};

template<typename T>

//Esta funcion es O(1) dado que el pointer last ya se encuentra como dato en el sistema
void Stack<T>::push(T value){
    data->insertLast(value);
    ++current_size;
}

//Esta operacion es O(1) onsite dado que ya se tiene e puntero hacia la ultima pocision
template<typename T>
T Stack<T>::pop(){

    T elemento = data->getLast()->dato;
    data->deleteLast();
    --current_size;
    return elemento;

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
    string fecha_original;
    int price;
    string order_name;


    public:

    LogEntry(long long tsmp, string f_orig, string rn, int p, string on){
        timestamp = tsmp;
        fecha_original = f_orig;
        restaurant_name = rn;
        price = p;
        order_name = on;

    }
    LogEntry() {
        timestamp = 0;
        fecha_original = "";
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
    out << entry.fecha_original << " " << entry.getRestaurantName()
        << " " << entry.getOrderName() << " (" << entry.getPrice() << ")";
    return out;
    }
    bool operator<(const LogEntry &other) const {
    // 1. Primero compara por el nombre del restaurante (orden alfabético)
    if (this->restaurant_name != other.restaurant_name) {
        return this->restaurant_name < other.restaurant_name;
    }
    // 2. Si el restaurante es el mismo, entonces compara por el timestamp (fecha)
    return this->timestamp < other.timestamp;
}

};


// Esta funcion escribe el archivo de salida con las variables ya ordenadas, fuciona utilizando el arreglo de objetos A que y el arreglo de objetos
//filtrados paraa escribir todas las lineas utilizando el respectivo indice.


/*Durante la iteracion anterior de este codigo ocurrio un bug, en donde los dias de 1 solo digito causaban un
desacomodo en la forma en la que nuestro codigo esperaba recibir cada pieza del string, despues de leer mas a fondo el problema
me encontre con la solucion. Usando la clase istrinstream podemos separar automaticamente cada pieza de la linea de acuerdo con el tipo
de variable que nuestro codigo espera, de esta forma hacemos el parseo de los datos mas flexible. */

//Esta funcion se encarga de recibir el archivo como parametro, un tamano de los arreglos e ir guardando las fechas transformadas en
//codigos con numeros long. Estos numeros long se guardan en un arrelo B, seran los utiilizados para arreglar los indices de los datos.
void LectorYTraductor(ifstream &archivo, ListDouble<LogEntry> &lista) {
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

            istringstream stream_linea(linea);
            stream_linea >> mes >> dia >> hora >> sep >> minuto >> sep >> segundo >> padding >> padding;
            //Leemos la linea hasta encontrarnos con :, lo que nos dejaria una entrada asi:
            //Jun 24 19:39:45 R:La Terraza del Mar O
            //Asi que eliminamos los dos ultimos caracteres
            getline(stream_linea, restaurant_name, ':');
            restaurant_name.erase(restaurant_name.size() - 2);
            getline(stream_linea, order,'(');
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

            string fecha_str = mes + " " + to_string(dia) + " " + to_string(hora) + ":" + to_string(minuto) + ":" + to_string(segundo);

            long long code=(mesint *100000000)+(dia*1000000)+(hora*10000)+(minuto*100)+segundo;
//code envez, de ser stoi debe ser stoll porque el codigo va a ser muy largo
//también cambiar la lsita b a que reciba stoll en todo el codigo para evitar errores

            LogEntry entry(code, fecha_str, restaurant_name, price, order);
            lista.insertLast(entry);


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



////////////////////quicksort en lista//////////////////////////////

template <class T>
Node<T>* partitionDL( ListDouble<T> &datos, Node<T>* L , Node<T>* R)
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
void quicksortDL(  ListDouble<T> &datos )
{   Node<T>* L = datos.getFirst();
    Node<T>* R = datos.getLast();

    Stack< Node<T>* > stack;
    stack.push(L);
    stack.push(R);

    Node<T>* pivot;
    while ( ! stack.isEmpty() )
    {   R = stack.pop();
        L = stack.pop();
        pivot = partitionDL(datos, L, R);

        if ( L != pivot && L != pivot->prev && pivot != NULL)
        {   stack.push(L);
            stack.push(pivot->prev); // aqui se me habia quedado privot-1
        }
        if ( R != pivot && R != pivot->next && pivot != NULL )
        {   stack.push(pivot->next); // y aqui privot+1
            stack.push(R);
        }
    }
}

void buscarPorRestaurante(ListDouble<LogEntry> &datos, bool guardarArchivo) {
    string restauranteBuscado;
    cout << "Ingresa el nombre del restaurante a buscar: ";
    getline(cin, restauranteBuscado);

    Node<LogEntry>* current = datos.getFirst();
    int contador = 0;
    bool encontrado = false;

    // Declaramos el objeto para crear/escribir el archivo
    ofstream archivoSalida;
    if (guardarArchivo) {
        // Si no existe, lo crea. Si existe, lo sobreescribe.
        archivoSalida.open("resultados_busqueda.txt");
    }

    cout << "\n--- Resultados para el restaurante: " << restauranteBuscado << " ---" << endl;

    for (int i = 0; i < datos.getSize(); ++i) {
        if (current->dato.getRestaurantName() == restauranteBuscado) {
            // Imprime en la consola
            cout << current->dato << endl;

            // Escribe en el archivo de texto usando el mismo formato
            if (guardarArchivo && archivoSalida.is_open()) {
                archivoSalida << current->dato << "\n";
            }

            contador++;
            encontrado = true;
        }
        else if (encontrado) {
            break; // Optimización: si ya encontró y dejó de coincidir, termina.
        }
        current = current->next;
    }

    if (!encontrado) {
        cout << "No se encontraron registros para ese restaurante." << endl;
    } else {
        cout << "--------------------------------------" << endl;
        cout << "Total de registros encontrados: " << contador << endl;

        if (guardarArchivo) {
            cout << "Los resultados se han guardado con exito en 'resultados_busqueda.txt'" << endl;
        }
    }

    // Cerramos el archivo al terminar
    if (guardarArchivo) {
        archivoSalida.close();
    }
}

int main() {
    ifstream archivo("ordenes.txt");
    string linea;
    ListDouble<LogEntry> orders_without_order;
    int n=0;
    int i=0;
    string  A[10000];
    long long B[10000];
    string  mes;
    int index_range[10000];
    int index_range_size = 0;
    string bsuqRES;
    LectorYTraductor(archivo,orders_without_order);



    int filtrados[10000];
    int cuantos = 0;

    for (i = 0; i< n; i++)
    { // cout <<i << " " << A[i] << endl;
        filtrados[cuantos] = i;
        cuantos++;
    }


    quicksortDL(orders_without_order); // Ascendente
    //cout << "\nVALORES ORDENADOS POR QUICK SORT (ASCENDENTE)" << endl;
    //Se puede cambiar libremente para debuggeo para imprimir todos, aunque el archivo ya lo hace.

    //Imprime los primeros 10



    //buscarPorRestaurante(orders_without_order);




char respuesta;
    cout << "\n¿Quieres guardar los resultados de la busqueda en un archivo .txt? (y/n): ";
    cin >> respuesta;

    // MUY IMPORTANTE: Como usamos 'cin >>' antes de un 'getline',
    // necesitamos limpiar el buffer para que no se salte la pregunta del restaurante.
    cin.ignore();

    bool guardar = (respuesta == 'y' || respuesta == 'Y');

    // Llamamos a la función pasándole la lista y la decisión del usuario
    buscarPorRestaurante(orders_without_order, guardar);

    return 0;
}
