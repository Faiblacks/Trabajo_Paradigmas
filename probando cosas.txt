#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // para ocupar std::transform

using namespace std;

class Taxonomia {
private:
   std::string clasificacion;           // Alacenar las variables para la funcion de guardar palabras claves
public:
    taxonomia (); clasificacion("no encontradad) {}
    virtual ~Taxonomia() {} // Destructor virtual

    string getClasificacion() const {
        return clasificacion;
    }

    void setClasificacion(const string& clasificacion) {
        clasificacion = nuevasclasificaciones;
    }
    static map<string, string> clasificaciones; // Mapa para almacenar las clasificaciones
                  map<string, string> palabrasClaves = {
            {"identificar", "Recordar"}, {"nombrar", "Recordar"}, {"listar", "Recordar"},
            {"definir", "Recordar"}, {"repetir", "Recordar"}, {"enumerar", "Recordar"},
            {"etiquetar", "Recordar"}, {"reconocer", "Recordar"},

            {"explicar", "Entender"}, {"resumir", "Entender"}, {"describir", "Entender"},
            {"interpretar", "Entender"}, {"clasificar", "Entender"}, {"comparar", "Entender"},
            {"parafrasear", "Entender"},

            {"usar", "Aplicar"}, {"resolver", "Aplicar"}, {"demostrar", "Aplicar"},
            {"implementar", "Aplicar"}, {"ejecutar", "Aplicar"}, {"calcular", "Aplicar"},
            {"construir", "Aplicar"},

            {"diferenciar", "Analizar"}, {"organizar", "Analizar"}, {"examinar", "Analizar"},
            {"categorizar", "Analizar"}, {"encontrar errores", "Analizar"}, {"contrastar", "Analizar"},

            {"justificar", "Evaluar"}, {"juzgar", "Evaluar"}, {"defender", "Evaluar"},
            {"criticar", "Evaluar"}, {"valorar", "Evaluar"}, {"argumentar", "Evaluar"},
            {"priorizar", "Evaluar"},

            {"diseñar", "Crear"}, {"construir", "Crear"}, {"desarrollar", "Crear"},
            {"formular", "Crear"}, {"proponer", "Crear"}, {"inventar", "Crear"},
            {"planificar", "Crear"}
        };

        // convertir titulo de la pregunta a minscula
        string tituloenminsuculas = TituloPregunta;
        transform(tituloenminsuculas.begin(), tituloenminsuculas.end(), tituloenminsuculas.begin(), ::tolower);

        //buscar la coincidencias y devolver la taxonomia clasificada
        for (const auto& palabraClave : palabrasClaves) {
            if (tituloenminsuculas.find(palabraClave.first) != string::npos) {
                return { { "Taxonomia", palabraClave.first }};
            }
        }
        return { { "Taxonomia", "no encontrada" } };
};

class pregunta : public Taxonomia {
private:
    string Pregunta;
    string TipoPregunta;
public:
  pregunta(const string titulo, const string& tipoPregunta) : titulo(titulo), tipoPregunta(tipoPregunta) {
    map<string, string> result = Taxonomia::clasficacion(titulo);
    setClasificacion(result["Taxonomia"]);
  }

  ~pregunta() {}

  string getTitulo() const {
    return titulo;
  }

    string getTipoPregunta() const {
        return tipoPregunta;
    }
};

class item : public pregunta {
private:
     vector<pregunta> preguntas; //donde se almacenan las preguntas
public:
  Item(const string& titulo, const string& tipoPregunta) : pregunta(titulo, tipoPregunta{}

   ~Item() {}

    void agregarPregunta(const pregunta& nuevaPregunta) {
        preguntas.push_back(nuevaPregunta);
    }
    void mostrarPreguntas() const {
         cout << "Preguntas del Item: ";
         for (const auto& pregunta : preguntas) {
            cout << "" << pregunta.getTitulo()
                 << "" << pregunta.getTipoPregunta()
                 << "" << pregunta.getClasificacion()  <<endl;
         }
    }
};

class profesor {
 private:
   string nombre;

 public:
    profesor(const string& nombre) : nombre(nombre) {}

    ~profesor() {}

    string getNombre() const {
         return nombre;
    }
};

class Solemne : public Item,public prfesor{
private:
        string titulo;
        string fecha;
        float ponderacion;
public:
  Solemne(const string& titulo, const string& fecha, float ponderacion, const string& nombreProfesor)
      : Item(titulo), profesor(nombreProfesor), fecha(fecha), ponderacion(ponderacion) {}
    ~Solemne() {}

    void mostrarInformacion() const {
      cout <<"" << titulo <<endl;
      cout << "Fecha de creacion" << fecha <<endl;
      cout << "Profesor(a): " << getNombre() <<endl;
      cout << "Ponderacion del: " << ponderacion <<endl;
    }
};

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
    cout << "Ingrese fecha de creación (DD/MM/AAAA): ";
    getline(cin, fechaCreacion);
    cout << "Ingrese nombre del profesor: ";
    getline(cin, nombre);
    cout << "Ingrese asignatura: ";
    getline(cin, asignatura);


    //¿será necesario crear más items? cuando solo existen dos V/F y SM
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
            cout << "Ingrese la pregunta: ()";
            getline(cin, pregunta);

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
cout<<"Prueba creada con éxito.\n";
   cout << "Título de la prueba: " << titulo << endl;
   cout << "Profesor(a): " << nombre << endl;
   cout << "Asignatura: " << asignatura << endl;
   cout << "Cantidad de items: " << cantidadItems << endl;
   cout << "Fecha de creación: " << fechaCreacion << endl;
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
