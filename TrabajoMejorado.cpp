#include <iostream>
#include <vector>
#include <string>

using namespace std;
//----------------------------------------------------------------------------------------------------------------------
class Taxonomia {
private:
    int tipotaxonomia;                          // variable donde se almacenara el tipo taxonomia  ya que 1) crear 2) evaluar ....... etc
    string palabrasclaves;                     // Alacenar las variables para la funcion de guardar palabras claves
public:
    Taxonomia( int tipotaxonomia, const string& palabrasclaves );
    ~Taxonomia();                                //Destruct Para liberar memoria
    int getTipotaxonomia();
    void setTipotaxonomia(int tipotaxonomia);
    string getPalabrasclaves();
    void setPalabrasclaves( string palabrasclaves );
};
Taxonomia::Taxonomia(int tipotaxonomia, const string& palabrasclaves) {
    this->tipotaxonomia = tipotaxonomia;
    this->palabrasclaves = palabrasclaves;
}
int Taxonomia::getTipotaxonomia() {
    return this->tipotaxonomia;
}
void Taxonomia::setTipotaxonomia(int tipotaxonomia) {
    this->tipotaxonomia = tipotaxonomia;
};


// Metodos de taxonomia -----------------------------------------------------------------------------------------------
// Estructura Base de la Clase pregunta--------------------------------------------------------------------------------
class Pregunta:public Taxonomia{   // llamando a la herencia de Taxonomia
private:
    string verdaderofalso;
    string opcionmultiple;
    int respuestas;
public:
    Pregunta(int tipotaxonomia, const string& palabrasclaves, string verdaderofalso, string opcionmultiple, int respuestas);
    ~Pregunta();
    string getVerdaderofalso();
    void setVerdaderofalso(string verdaderofalso);
    string getOpcionmultiple();
    void setOpcionmultiple(string opcionmultiple);
    int getRespuestas();
    void setRespuestas(int respuestas);
};
// Metodos preguntas --------------------------------------------------------------------------------------------------

class profesor {
    private:
        string nombre;
        string asignatura;
    public:
        profesor(string nombre, string asignatura);
        ~profesor();
        string getNombre();
        void setNombre(string nombre);
        string getAsignatura();
        void setAsignatura(string asignatura);
};

// metodos profesor ---------------------------------------------------------------------------------------------------

class Items : public Pregunta, public Taxonomia {

      string SeleccionItems;
    public:
      Items(int tipotaxonomia, const string& palabrasclaves, string verdaderofalso, string opcionmultiple, int respuestas, string seleccionitems);
      ~Items();
      string getSeleccionItems();
      void setSeleccionItems(string seleccionitems);
};
//metodos items -------------------------------------------------------------------------------------------------------

class Examen:public Taxonomia,public Pregunta,public profesor {
private:
    float ponderacion;
    struct timezone;
    string titulo;                    //titulo de que es el examen
public:
    Examen(int tipotaxonomia, const string& palabrasclaves, string verdaderofalso, string opcionmultiple, int respuestas, string nombre, string asignatura, float ponderacion, string titulo);
    ~Examen();
    float getPonderacion();
    void setPonderacion(float ponderacion);
    string getTitulo();
    void setTitulo(string titulo);
};


//la clase menu debe heredar lo que contenga la clase examen, para ser usado en la opcion de crear, borrar, actualizar, buscar información del item
// ¡¡ACTUALIZACION DE IMPLEMENTACION: EL SISTEMA DEBE INCORPORAR UNA CLASE ITEM QUE GUARDARA TODO LO RELACIONADO A LAS PREGUNTAS, ESTA LUEGO SERA LLAMADA A PRUEBA
// ESTO PARA CUMPLIR CON LA CONDICION DE BUSCAR INFORMACION POR ITEM EN LA EVALUACION!!

class Menu : public Examen {
public:

    void mostrarMenu();
    void crear_prueba();
    void actualizarItem();
    void consultarInformacion();
    void borrarItem();
};

void Menu::crear_prueba() {
    int cantidadItems;
    string nombre, asignatura, titulo;

    cout << "Ingrese título de la prueba: ";
    getline(cin, titulo);
    cout << "Ingrese nombre del profesor: ";
    getline(cin, nombre);
    cout << "Ingrese asignatura: ";
    getline(cin, asignatura);

    cout << "¿Cuántos items desea agregar al examen? ";
    cin >> cantidadItems;
    cin.ignore();
                                                                        //solicitud de usuario para añadir una cantidad X de items a
    for (int i = 0; i < cantidadItems; i++) {
        int tipopregunta;
        cout << "\nItem [" << (i + 1) << "]" << endl;
        cout << "Seleccione el tipo de pregunta: \n";
        cout << "[1] Verdadero/Falso\n[2] Opción Múltiple\nOpción: ";
        cin >> tipopregunta;
        cin.ignore();

        int cantidadPreguntasItem;
        cout << "¿Cuántas preguntas desea añadir a este item?: ";
        cin >> cantidadPreguntasItem;
        cin.ignore();

        for (int j = 0; j < cantidadPreguntasItem; j++) {
            string pregunta;
            cout << "\nPregunta [" << (j + 1) << "]" << endl;
            cout << "Ingrese la pregunta: ";
            getline(cin, pregunta);

            // Convertir todo a minúscula
            for (char& c : pregunta) {
                c = tolower(c);
            }

        }

            if (tipopregunta == 1) {
                string respuestaVerdadera, respuestaFalsa;
                cout << "Ingrese la respuesta verdadera: ";
                getline(cin, respuestaVerdadera);
                cout << "Ingrese la respuesta falsa: ";
                getline(cin, respuestaFalsa);

                // Aquí podrías guardar la pregunta con sus respuestas en una lista/vectores/objetos
                // Ejemplo: crearObjetoVerdaderoFalso(pregunta, respuestaVerdadera, respuestaFalsa);
            }
            else if (tipopregunta == 2) {
                int cantidadOpciones;
                cout << "¿Cuántas opciones desea ingresar para esta pregunta?: ";
                cin >> cantidadOpciones;
                cin.ignore();

                for (int k = 0; k < cantidadOpciones; k++) {
                    string opcion;
                    cout << "Ingrese la opción [" << (k + 1) << "]: ";
                    getline(cin, opcion);
                    // Guardar cada opción en un vector/lista asociada a la pregunta
                }

                int respuestaCorrecta;
                cout << "¿Cuál opción es la correcta? (número de opción): ";
                cin >> respuestaCorrecta;
                cin.ignore();

                // Aquí podrías guardar la pregunta y cuál opción es la correcta
                // Ejemplo: crearObjetoOpcionMultiple(pregunta, opciones, respuestaCorrecta);
            }
            else {
                cout << "Tipo de pregunta inválido.\n";
                break;
            }
        }
    }
};


void Menu::mostrarMenu() {
    int opcion;
    bool bucle = true;

    while (bucle) {
        cout << "Bienvenido al sistema de evaluacion 1.0\n"
             << "Por favor, seleccione una de las siguientes opciones:\n"
             << "[1] Crear prueba\n"
             << "[2] Actualizar Item de la prueba\n"
             << "[3] Consultar informacion de la prueba\n"
             << "[4] Borrar Item de la prueba\n"
             << "[5] Salir\n"
             << endl;

        cin >> opcion;

        switch (opcion) {
            case 1:
                crear_prueba();
            break;
            case 2:
                actualizarItem();
            break;
            case 3:
                consultarInformacion();
            break;
            case 4:
                borrarItem();
            break;
            case 5:
                cout << "Saliendo del sistema. ¡Hasta luego!" << endl;
            bucle = false;
            break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n" << endl;
            break;
        }
    }
}

