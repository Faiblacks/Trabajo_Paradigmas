#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

//----------------------------------------------------------------------------------------------
//clase para ayudar en la clasificacion taxonomica de las preguntas en base a las palabras clave
//----------------------------------------------------------------------------------------------

class Clasificacion {
private:
    string nombre;
    vector<string> palabrasClave;

public:
    Clasificacion(const string& nombre, const vector<string>& palabrasClave)
        : nombre(nombre), palabrasClave(palabrasClave) {}

    string getNombre() const {
        return nombre;
    }

    const vector<string>& getPalabrasClave() const {
        return palabrasClave;
    }
};

//-------------------------------------------------------------------------
//clase para asignar el nivel de taxonomia a las preguntas
//-------------------------------------------------------------------------

class Taxonomia {
private:
    vector<Clasificacion> clasificaciones;
    string clasificacionActual;

public:
    Taxonomia() : clasificacionActual("No encontrada") {
        clasificaciones.emplace_back("Recordar", vector<string>{"identificar", "nombrar", "listar", "definir", "repetir", "enumerar", "etiquetar", "reconocer"});
        clasificaciones.emplace_back("Entender", vector<string>{"explicar", "resumir", "describir", "interpretar", "clasificar", "comparar", "parafrasear"});
        clasificaciones.emplace_back("Aplicar", vector<string>{"usar", "resolver", "demostrar", "implementar", "ejecutar", "calcular", "construir"});
        clasificaciones.emplace_back("Analizar", vector<string>{"diferenciar", "organizar", "examinar", "categorizar", "contrastar", "encontrar errores"});
        clasificaciones.emplace_back("Evaluar", vector<string>{"justificar", "juzgar", "defender", "criticar", "valorar", "argumentar", "priorizar"});
        clasificaciones.emplace_back("Crear", vector<string>{"diseñar", "crear", "formular", "proponer", "inventar", "planificar"});
    }

    virtual ~Taxonomia() {}

    string ClasificarPregunta(const string& pregunta) {
        string preguntaMin = toLowerCase(pregunta);

        for (const auto& clasificacion : clasificaciones) {
            for (const auto& palabraClave : clasificacion.getPalabrasClave()) {
                if (preguntaMin.find(palabraClave) != string::npos) {
                    return clasificacion.getNombre();
                }
            }
        }
        return "No encontrada";
    }

    string toLowerCase(const string& texto) {
        string resultado = texto;
        for (size_t i = 0; i < resultado.size(); ++i) {
            resultado[i] = tolower(resultado[i]);
        }
        return resultado;
    }
};

//---------------------------------------------------------------------------------
//clase para almacenar nombre del profesor junto al ramo que imparte
//---------------------------------------------------------------------------------

class profesor {                                                            //[IDEA]--> AÑADIR VARIABLE QUE ALMACENE LA CLASE QUE IMPARTE
private:
    string nombre;
    string ramo;

public:
    profesor(const string& nombre) : nombre(nombre) {}
    ~profesor() {}

    string getNombre() {
        return nombre;
    }
    string getRamo() {
      return ramo;
    }
};

//---------------------------------------------------------------------------------
//Clase para crear una prueba
//---------------------------------------------------------------------------------

class Solemne : public profesor, public Taxonomia {
private:
    string titulo_prueba;
    string tipo_pregunta;
    string titulo_pregunta;
    string fecha_creacion;
    string materia;
    string fecha;
    int cantidad_preguntas;
    int cantidad_items;
    float ponderacion;

public:
    Solemne(const string& titulo_prueba, const string& fecha, float ponderacion, const string& nombreProfesor)
        : profesor(nombreProfesor), titulo_prueba(titulo_prueba), fecha(fecha), ponderacion(ponderacion),
          cantidad_preguntas(0), cantidad_items(0) {}

    void asignarNivelTaxonomia() {
        string nivelTaxonomia = ClasificarPregunta(titulo_pregunta);
        cout << "El nivel de taxonomía asignado al ítem \"" << titulo_pregunta << "\" es: " << nivelTaxonomia << endl;
    }

    void crearPrueba() {
        cin.ignore(); // Limpiar posibles restos en el buffer
        cout << "Ingrese el título de la prueba: ";
        getline(cin, titulo_prueba);

        cout << "Ingrese la fecha de creación (DD/MM/AAAA): ";
        getline(cin, fecha_creacion);

        cout << "Ingrese la materia: ";
        getline(cin, materia);

        cout << "Ingrese la cantidad de ítems: ";
        while (!(cin >> cantidad_items) || cantidad_items <= 0) {
            cout << "Cantidad inválida. Intente nuevamente: ";
            cin.clear();
            cin.ignore();
        }

        for (int i = 0; i < cantidad_items; i++) {
            cout << "Ingrese el tipo de pregunta ([1] Verdadero/Falso, [2] Opción Múltiple): ";
            int tipo;
            while (!(cin >> tipo) || (tipo != 1 && tipo != 2)) {
                cout << "Entrada inválida. Intente nuevamente ([1] o [2]): ";
                cin.clear();
                cin.ignore();
            }

            cout << "Ingrese la cantidad de preguntas: ";
            while (!(cin >> cantidad_preguntas) || cantidad_preguntas <= 0) {
                cout << "Cantidad inválida. Intente nuevamente: ";
                cin.clear();
                cin.ignore();
            }

            cin.ignore(); // Limpiar buffer
            for (int j = 0; j < cantidad_preguntas; j++) {
                cout << "Ingrese el título de la pregunta: ";
                getline(cin, titulo_pregunta);

                asignarNivelTaxonomia();

                if (tipo == 1) {
                    cout << "Ingrese la cantidad de respuestas: ";
                    int cantidad_respuestas;
                    while (!(cin >> cantidad_respuestas) || cantidad_respuestas <= 0) {
                        cout << "Cantidad inválida. Intente nuevamente: ";
                        cin.clear();
                        cin.ignore();
                    }

                    vector<string> respuestas;
                    cin.ignore(); // Limpiar buffer
                    for (int k = 0; k < cantidad_respuestas; k++) {
                        cout << "Ingrese la respuesta: ";
                        string respuesta;
                        getline(cin, respuesta);
                        respuestas.push_back(respuesta);
                    }

                    cout << "Seleccione la respuesta correcta (ingrese el número):" << endl;
                    for (int k = 0; k < respuestas.size(); k++) {
                        cout << k + 1 << ". " << respuestas[k] << endl;
                    }

                    int indice_correcto;
                    while (!(cin >> indice_correcto) || indice_correcto < 1 || indice_correcto > respuestas.size()) {
                        cout << "Índice incorrecto. Seleccione nuevamente: ";
                        cin.clear();
                        cin.ignore();
                    }

                    cout << "Respuesta correcta: " << respuestas[indice_correcto - 1] << endl;
                } else if (tipo == 2) {
                    cout << "Ingrese la cantidad de opciones: ";
                    int cantidad_opciones;
                    while (!(cin >> cantidad_opciones) || cantidad_opciones <= 0) {
                        cout << "Cantidad inválida. Intente nuevamente: ";
                        cin.clear();
                        cin.ignore();
                    }

                    vector<string> opciones;
                    cin.ignore();
                    for (int k = 0; k < cantidad_opciones; k++) {
                        cout << "Ingrese la opción: ";
                        string opcion;
                        getline(cin, opcion);
                        opciones.push_back(opcion);
                    }

                    cout << "Seleccione la opción correcta (ingrese el número):" << endl;
                    for (int k = 0; k < opciones.size(); k++) {
                        cout << k + 1 << ". " << opciones[k] << endl;
                    }

                    int indice_correcto;
                    while (!(cin >> indice_correcto) || indice_correcto < 1 || indice_correcto > opciones.size()) {
                        cout << "Índice incorrecto. Seleccione nuevamente: ";
                        cin.clear();
                        cin.ignore();
                    }

                    cout << "Respuesta correcta: " << opciones[indice_correcto - 1] << endl;
                }
            }
        }
    }

    void mostrarInformacion() {
        cout << "Título: " << titulo_prueba << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Ponderación: " << ponderacion << "%" << endl;
        cout << "Profesor(a): " << getNombre() << endl;
    }
};

class Menu : public Solemne{
  cout<<"--------------------------------------"<<endl;
  cout<<"---Bienvenido al sistema de pruebas---"<<endl;
  cout<<"--------------------------------------"<<endl;

  cout<<"Ingrese alguna de las siguientes opciones:"<<endl;
  cout<<"[1] Crear prueba"<<endl;
  cout<<"[2] actualizar prueba"<<endl;
  cout<<"[3] eliminar prueba"<<endl;
  cout<<"[4] buscar por fecha"<<endl;



};

int main() {}