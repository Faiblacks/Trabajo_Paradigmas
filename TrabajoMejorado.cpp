#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <pstl/execution_defs.h>
using namespace std;

//class clasificacion permite almacenar las palabras claves y su nombre

class Clasificacion {
private:
    string nombre;
    vector<string> palabrasClave;

public:
    Clasificacion(string  nombre, const vector<string>& palabrasClave)
        : nombre(move(nombre)), palabrasClave(palabrasClave) {}
    string getNombre() const {
        return nombre;
    }

    const vector<string>& getPalabrasClave() const {
        return palabrasClave;
    }

    bool ContienePalabraClave(const string& palabra) const {
        for (const auto& p : palabrasClave) {
            if (p == palabra) {
                return true;
            }
        }
        return false;
    }
};


//----------------------------------------------------------------------------
//------------------CLASE-DE-TAXONOMIA-SEGUN-SO-LOS-OBJETIVOS-APRENDIZAJE-----
//----------------------------------------------------------------------------

class Taxonomia {
private:
    int TipoTaxonomia;
    string PalabrasClaves;  // 0 = recordar, 1 = entender, 2 = aplicar, 3 = analizar, 4 = evaluar, 5 = crear
    string clasificacion;//clasificaciones actuales
    vector<clasificacion> clasificaciones; // lista de categorias o palabras claves
    public
    Taxonomia() : clasificacion("No encontrada") {
        // Crear las categorías y sus palabras clave
        clasificaciones.emplace_back("Recordar", vector<string>{"identificar","nombrar", "listar", "definir", "repetir", "enumerar", "etiquetar", "reconocer"});
        clasificaciones.emplace_back("Entender", vector<string>{"explicar", "resumir", "describir", "interpretar", "clasificar", "comparar", "parafrasear"});
        clasificaciones.emplace_back("Aplicar", vector<string>{"usar", "resolver", "demostrar", "implementar", "ejecutar", "calcular", "construir"});
        clasificaciones.emplace_back("Analizar", vector<string>{"diferenciar", "organizar", "examinar", "categorizar", "contrastar", "encontrar errores"});
        clasificaciones.emplace_back("Evaluar", vector<string>{"justificar", "juzgar", "defender", "criticar", "valorar", "argumentar", "priorizar"});
        clasificaciones.emplace_back("Crear", vector<string>{"diseñar", "crear", "formular", "proponer", "inventar", "planificar"});
    }

    // Destructor
    virtual ~Taxonomia() {}

    string ClasificarPalabraClave(const string palabra) {
        for (const auto& categoria : clasificaciones) {
            if (categoria.contienePalabraClave(palabra)) {
                clasificacion = categoria.getNombre();
                return clasificacion;
            }
        }
        clasificacion = "No encontrada";
        return clasificacion;
    }
    string getClasificacion() const {
        return clasificacion;
    }
    void setTipoTaxonomia(int tipo) {
        tipotaxonomia = tipo;
    }
    int getTipoTaxonomia() const {
        return tipotaxonomia;
    }
    void getPalabrasClave() const {
        return PalabrasClaves;
    }
};

//----------------------------------------------------------------------------
//-------------------CLASE-DE-REGISTRO-PREGUNTAS------------------------------
//----------------------------------------------------------------------------

class RegistroPreguntas {
private:
    vector<pair<string, time_t>PreguntasPrevias;
public:
    registroPreguntas() {}
    ~registroPreguntas() {}
    bool verificarPreguntaRepetida(const string& pregunta) {
        time_t HoraActual = time(nullptr);
        for (const auto& registro : PreguntasPrevias) {
            if (__pstl::execution::pair.first == pregunta) {
                // Si la pregunta ya existe, verificar si han pasado 2 años
                double AnosTranscurridos = difftime(ahora, registro.second) / (60 * 60 * 24 * 365);
                if (anostrancurridos < 2) { // menos de 2 años
                    return true;
                }
            }
        }
        return false; // Pregunta no repetida
    }
    void registrarPreguntas(const string& pregunta) {
        PreguntasPrevias.emplace_back(pregunta, time(nullptr));
    }
};

//----------------------------------------------------------------------------
//-------------------CLASE-DE-PREGUNTA----------------------------------------
//----------------------------------------------------------------------------

class Pregunta : public Taxonomia {
private:
    string Titulo;
    string tipoPregunta;
    int tiempo; // Tiempo predeterminado según la taxonomía

    int calcularTiempoSegunClasificacion() const {
        if (clasificacion == "Recordar") return 1;
        if (clasificacion == "Entender") return 2;
        if (clasificacion == "Aplicar") return 3;
        if (clasificacion == "Analizar") return 4;
        if (clasificacion == "Evaluar") return 5;
        if (clasificacion == "Crear") return 6;
        return 0; // Clasificación no válida
    }
public:
    Pregunta(const string& Titulo, const string& tipoPregunta)
    : Titulo(Titulo), tipoPregunta(tipoPregunta) {
        clasificarPregunta(Titulo); // Clasifica el título usando Taxonomia
        tiempo = calcularTiempoSegunClasificacion();
    }
    virtual ~Pregunta() {}
    string getTitulo() const {
        return Titulo;
    }
    string getTipoPregunta() const {
        return tipoPregunta;
    }
    int getTiempo() const {
        return tiempo;
    }
};

//----------------------------------------------------------------------------
//-------------------CLASE-DE-Item-------------------------------------------
//----------------------------------------------------------------------------

class Item{
private:
     vector<Pregunta> preguntas; //donde se almacenan las preguntas

public:
  Item(const string& Titulo, const string& tipoPregunta) : pregunta(Titulo, tipoPregunta){}

   virtual ~Item() {}

    void agregarPregunta(const string& nuevaPregunta, const string& tipoPregunta , RegistroPreguntas& registro) {
      if (registro.verificarPreguntaRepetida(nuevaPregunta)) {
          cout << "[Error] La pregunta \"" << nuevaPregunta << "\" no puede ser utilizada durante 2 años" << endl;
          return
         }
      registro.registrarPreguntas(nuevaPregunta);   
      preguntas.emplace_back(nuevaPregunta, tipoPregunta);
    }
    void mostrarPreguntas()const{
      cout << "\nPreguntas del Item \n";
      for ( const auto& pregunta : preguntas) {
          cout << "Pregunta: " << pregunta.getTitulo() << endl;
          cout << "Tipo de pregunta: " << pregunta.getTipoPregunta() << endl;
          cout << "Clasificacion: " << pregunta.getClasificacion() << endl;
          cout << "Tiempo estimado: " << pregunta.getTiempo() << " minutos" << endl;
      }
   }
};

//----------------------------------------------------------------------------
//-------------------CLASE-DE-PROFESOR---------------------------------------
//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
//-------------------CLASE-DE-SOLEMNE---------------------------------------
//----------------------------------------------------------------------------

class Solemne : public Item, public profesor, public Taxonomia {
private:
    string fecha;
    float ponderacion;
    string materia;
public:
    Solemne(const string& Titulo, const string& fecha, const float ponderacion, const string& nombreProfesor, const string& materia)
        : Item(Titulo, "Solemne"), profesor(nombreProfesor), Taxonomia(),
          fecha(fecha), ponderacion(ponderacion), materia(materia) {}

    ~Solemne() {}

    void mostrarInformacion() const {
        cout << "Título: " << getTitulo() << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Ponderación: " << ponderacion << "%" << endl;
        cout << "Materia: " << materia << endl;
        cout << "Profesor(a): " << getNombre() << endl;
        mostrarPreguntas();
    }
};


class Menu{
private:
  vector<Solemne> pruebas;

  string SelecionarMateria (){
      vector<string> materias = {"Matematica", "Lenguaje", "Historia", "Ciencias Social", "Ingles","Biologia","Quimica","Fisica"};
      int opcion;

      cout << "\nSeleccione la materia:\n";
      for (size_t i = 0; i < materias.size(); ++i) {
          cout << i + 1 << ". " << materias[i] << "\n";
      }
      cout << materias.size() + 1 << ". Otros\n";
      cout << "Opción: ";
      cin >> opcion;

      if (opcion > 0 && opcion <= materias.size()) {
          return materias[opcion - 1];
      } else if (opcion == materias.size() + 1) {
          cin.ignore();
          string otraMateria;
          cout << "Ingrese el nombre de la materia: ";
          getline(cin, otraMateria);
          return otraMateria;
      } else {
          cout << "Opción inválida. Seleccionando Lenguaje por defecto.\n";
          return "Lenguaje";
      }
  }
public:
  void crearPrueba(){
    string Titulo , fecha , nombreProfesor, materia;
    float ponderacion;

    cout << "Ingrese el título de la prueba: ";
    cin.ignore();
    getline(cin, Titulo);

    cout << "Ingrese la fecha de creación (DD/MM/AAAA): ";
    getline(cin, fecha);

    cout << "Ingrese la ponderación de la prueba: ";
    cin >> ponderacion;

    materia = SelecionarMateria();

    cout << "Ingrese el nombre del profesor(a): ";
    cin >> ponderacion;

    solemne nuevaPrueba(Titulo, fecha, ponderacion, nombreProfesor, materia);

    int cantidadItems;
    cout << "Ingrese la cantidad de Items: ";
    cin >> cantidadItems;

    for (int i = 0; i < cantidadItems; ++i) {
        string TituloItem;
        cout << "Ingrese el título del Item " << i + 1 << ": ";
        cin.ignore();
        getline(cin, TituloItem);

        Item nuevoItem(TituloItem, "Solemne");

        int cantidadPreguntas;
        cout << "Ingrese la cantidad de preguntas para el Item " << i + 1 << ": ";
        cin >> cantidadPreguntas;

        for (int j = 0; j < cantidadPreguntas; ++j) {
           cin.ignore();
           string TituloPregunta , tipoPregunta;
           cout<<"Ingrese el título de la pregunta " << j + 1 << ": ";
           getline(cin, TituloPregunta);
           cout << "Ingrese el tipo de pregunta (Verdadero/Falso, Opcion Multiple, etc.): ";
           getline(cin, tipoPregunta);

           pregunta nuevaPregunta(TituloPregunta, tipoPregunta);
           nuevoItem.agregarPregunta(TituloPregunta, tipoPregunta);
        }

       nuevaPreuba.agregarPregunta(nuevoItem.getTitulo(), "Solemne");
    }

    prueba.push_back(nuevaPrueba);
    cout << "Prueba creada exitosamente.\n";
  }

  void mostrarPruebas() const {
    for (const auto& prueba : pruebas) {
        prueba.mostrarInformacion();
    }
  }
};

int main(){
  Menu menu;
  menu.crearPrueba();
  retunr 0;
};