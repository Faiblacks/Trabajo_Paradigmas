#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// Clase para manejar la categoría y sus palabras clave
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

class Taxonomia {
private:
    vector<Clasificacion> clasificaciones; // Lista de categorías o palabras clave
    string clasificacionActual; // Clasificación actual encontrada

public:
    Taxonomia() : clasificacionActual("No encontrada") {
        // Crear las categorías y sus palabras clave
        clasificaciones.emplace_back("Recordar", vector<string>{"identificar", "nombrar", "listar", "definir", "repetir", "enumerar", "etiquetar", "reconocer"});
        clasificaciones.emplace_back("Entender", vector<string>{"explicar", "resumir", "describir", "interpretar", "clasificar", "comparar", "parafrasear"});
        clasificaciones.emplace_back("Aplicar", vector<string>{"usar", "resolver", "demostrar", "implementar", "ejecutar", "calcular", "construir"});
        clasificaciones.emplace_back("Analizar", vector<string>{"diferenciar", "organizar", "examinar", "categorizar", "contrastar", "encontrar errores"});
        clasificaciones.emplace_back("Evaluar", vector<string>{"justificar", "juzgar", "defender", "criticar", "valorar", "argumentar", "priorizar"});
        clasificaciones.emplace_back("Crear", vector<string>{"diseñar", "crear", "formular", "proponer", "inventar", "planificar"});
    }

    // Destructor virtual para evitar problemas de herencia
    virtual ~Taxonomia() {}

    string ClasificarPregunta(const string& pregunta) {
        // Convertir el título de la pregunta a minúsculas sin usar transform
        string preguntaMin = toLowerCase(pregunta);

        // Buscar coincidencias y devolver la taxonomía clasificada
        for (const auto& clasificacion : clasificaciones) {
            for (const auto& palabraClave : clasificacion.getPalabrasClave()) {
                if (preguntaMin.find(palabraClave) != string::npos) {
                    return clasificacion.getNombre();
                }
            }
        }
        return "No encontrada";
    }

    // Método auxiliar para convertir una cadena a minúsculas sin usar transform
    string toLowerCase(const string& texto) {
        string resultado = texto; // Copiamos el texto original
        for (size_t i = 0; i < resultado.size(); ++i) {
            resultado[i] = tolower(resultado[i]); // Convertimos cada carácter a minúscula
        }
        return resultado;
    }
};


class profesor {
private:
    string nombre;
public:
    profesor(const string& nombre) : nombre(nombre) {}
    ~profesor() {}

    string getNombre() {
        return nombre;
    }
};

class Solemne : public profesor, Taxonomia {
private:
    string titulo_prueba;
    string titulo_item;
    string tipo_pregunta;
    string fecha_creacion;
    string materia;
    string fecha;
    int cantidad_preguntas;
    int cantidad_items;
    float ponderacion;

public:
    Solemne(const string& titulo_prueba, const string& fecha, float ponderacion, const string& nombreProfesor)
        : profesor(nombreProfesor), titulo_prueba(titulo_prueba), fecha(fecha), ponderacion(ponderacion) {}

    ~Solemne() {}

    bool esFechaValida(const string& fecha) {
        if (fecha.length() != 10) return false;
        if (fecha[2] != '/' || fecha[5] != '/') return false;
        try {
            int dia = stoi(fecha.substr(0, 2));
            int mes = stoi(fecha.substr(3, 2));
            int anio = stoi(fecha.substr(6, 4));
            return dia > 0 && dia <= 31 && mes > 0 && mes <= 12 && anio > 0;
        } catch (...) {
            return false;
        }
    }

    void crearPrueba() {
        cout << "Ingrese el título de la prueba: ";
        cin.ignore();
        getline(cin, titulo_prueba);
        cout << "Ingrese la fecha de creación (DD/MM/AAAA): ";
        getline(cin, fecha_creacion);
        if (!esFechaValida(fecha_creacion)) {
            cout << "Fecha inválida. Debe tener el formato DD/MM/AAAA." << endl;
            return;
        }
        cout << "Ingrese la materia: ";
        getline(cin, materia);

        cout << "Ingrese la cantidad de ítems: ";
        cin >> cantidad_items;
        for (int i = 0; i < cantidad_items; i++) {
            cout << "Ingrese el título del ítem: ";
                cin.ignore();
            getline(cin, titulo_item);
            if (titulo_item.length() > 50 || titulo_item.length() < 5 || titulo_item.empty()) {
                cout << "titulo invalido" << endl;
                return;
            }
            cout << "Ingrese el tipo de pregunta (1. Verdadero/Falso, 2. Opción Múltiple): ";
            int tipo;
            cin >> tipo;
            cout << "Ingrese la cantidad de preguntas: ";
            cin >> cantidad_preguntas;

            for (int j = 0; j < cantidad_preguntas; j++) {
                cout << "Ingrese el título de la pregunta: ";
                cin.ignore();
                string pregunta;
                getline(cin, pregunta);

                if (tipo == 1) {
                    cout << "Ingrese la cantidad de respuestas: ";
                    int cantidad_respuestas;
                    cin >> cantidad_respuestas;
                    vector<string> respuestas;

                    for (int k = 0; k < cantidad_respuestas; k++) {
                        cout << "Ingrese la respuesta: ";
                        cin.ignore();
                        string respuesta;
                        getline(cin, respuesta);
                        respuestas.push_back(respuesta);
                    }

                    cout << "Seleccione la respuesta correcta (ingrese el número):" << endl;
                    for (int k = 0; k < respuestas.size(); k++) {
                        cout << k + 1 << ". " << respuestas[k] << endl; // Mostrar las opciones
                    }
                    int indice_correcto;
                    cin >> indice_correcto;

                    while(indice_correcto < 1 || indice_correcto > respuestas.size()) {
                        cout << "Índice incorrecto. Seleccione nuevamente: ";
                        cin >> indice_correcto;
                    }
                    string respuesta_correcta = respuestas[indice_correcto - 1];
                    cout << "Respuesta correcta: " << respuesta_correcta << endl;
            }
        }
        cout << "Ingrese la ponderación de la prueba: ";
        cin >> ponderacion;

    void mostrarInformacion(){
        cout << "Título: " << titulo_prueba << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Ponderación: " << ponderacion << "%" << endl;
        cout << "Profesor(a): " << getNombre() << endl;
        }
};