#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // para ocupar std::transform

using namespace std;

class Clasificacion {
private:
    string nombre;
    vector<string> palabrasClave;

public:
    Clasificacion(const string& nombre, const vector<string>& palabrasClave)
        : nombre(nombre), palabrasClave(palabrasClave) {}

    ~Clasificacion() {}

    string getNombre() const {
        return nombre;
    }

    const vector<string>& getPalabrasClave() const {
        return palabrasClave;
    }

    bool contienePalabraClave(const string& palabra) const {
        return find(palabrasClave.begin(), palabrasClave.end(), palabra) != palabrasClave.end();
    }   
};


class Taxonomia {
private:
  string clasificacion;                    //clasificaciones actuales
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

    // Getter de la clasificación
    string getClasificacion() const {
    return clasificacion;
    }

     // Método para clasificar una pregunta basándonos en sus palabras clave
    void clasificarPregunta(const string& tituloPregunta) {
    // Convertir el título a minúsculas
       string tituloMin = tituloPregunta;
       transform(tituloMin.begin(), tituloMin.end(), tituloMin.begin(), ::tolower);

       // Dividir el título en palabras y buscar palabras clave
       for (const auto& categoria : clasificaciones) {
           for (const string& palabraClave : categoria.getPalabrasClave()) {
               if (tituloMin.find(palabraClave) != string::npos) {
                  clasificacion = categoria.getNombre(); // Asignar la clasificación
                  return;
            }
        }
    }

    clasificacion = "No encontrada"; // Si no hay coincidencias
  }
};
class RegistroPreguntas {
private:
    vector<pair<strin, time_t>preguntasPrevias;
public:
   registroPreguntas() {}

   ~registroPreguntas() {}

   bool verificarPreguntaRepetida(const string& pregunta) {
     time_t HoraActual = time(nullptr);

     for (const auto& registro : preguntasPrevias) {
         if (par.first == pregunta) {
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
     preguntasPrevias.emplace_back(pregunta, time(nullptr));
   }
};

class pregunta : public Taxonomia {
private:
    string Pregunta;
    string TipoPregunta;
    int tiempo; // tiempo predeterminado segun la taxonomia
    int calcularTiempoSegunClasficiacion () const{
      if (clasificacion == "recordar") return 1;
      if (clasificacion == "entender") return 2;
      if (clasificacion == "aplicar") return 3;
      if (clasificacion == "analizar") return 4;
      if (clasificacion == "evaluar") return 5;
      if (clasificacion == "crear") return 6;
      return 0; // Clasificación no válida
    }
};

public:
  pregunta(const string& titulo, const string& tipoPregunta)
      :titulo(titulo), tipoPregunta(tipoPregunta) {
    clasificarPregunta(titulo);
    tiempo = calcularTiempoSegunClasificacion();
  }

  virtual ~pregunta() {}

  string getTitulo() const {
    return titulo;
  }

    string getTipoPregunta() const {
        return tipoPregunta;
  }

  int getTiempo() const {
    return tiempo;
  }
};

class item : public pregunta {
private:
     vector<pregunta> preguntas; //donde se almacenan las preguntas

public:
  Item(const string& titulo, const string& tipoPregunta) : pregunta(titulo, tipoPregunta){}

   virtual ~Item() {}

    void agregarPregunta(const string& nuevaPregunta, const string& tipoPregunta , RegistroPreguntas& registro) {
      if (registro.VerificarPreguntaRepetida(nuevaPregunta)) {
          cout << "[Error] La pregunta \"" << nuevaPregunta << "\" no puede ser utilizada durante 2 años" << endl;
          return
         }
      registro.registrarPreguntas(nuevaPregunta);
      preguntas.emplace_back(nuevaPregunta, tipoPregunta);
    }
    void mostrarPreguntas()const{
      cout << "\nPreguntas del item \n";
      for ( const auto& pregunta : preguntas) {
          cout << "Pregunta: " << pregunta.getTitulo() << endl;
          cout << "Tipo de pregunta: " << pregunta.getTipoPregunta() << endl;
          cout << "Clasificacion: " << pregunta.getClasificacion() << endl;
          cout << "Tiempo estimado: " << pregunta.getTiempo() << " minutos" << endl;
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
        string fecha;
        float ponderacion;
        string materia;
public:
  solemne(const string& titulo, const string& fecha, float ponderacion, const string& nombreProfesor, string & materia)
      : Item(titulo, "Solemne"), profesor(nombreProfesor), fecha(fecha), ponderacion(ponderacion), materia(materia) {}
    }
};
    virtual ~Solemne() {}

    void mostrarInformacion() const {
        cout << "Título: " << getTitulo() << endl;
        cout << "Fecha de creación: " << fecha << endl;
        cout << "Ponderación: " << ponderacion << "%" << endl;
        cout << "Materia: " << materia << endl;
        cout << "Profesor(a): " << getNombre() << endl;
    }

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
    string titulo , fecha , nombreProfesor, materia;
    float ponderacion;

    cout << "Ingrese el título de la prueba: ";
    cin.ignore();
    getline(cin, titulo);

    cout << "Ingrese la fecha de creación (DD/MM/AAAA): ";
    getline(cin, fecha);

    cout << "Ingrese la ponderación de la prueba: ";
    cin >> ponderacion;

    materia = SelecionarMateria();

    cout << "Ingrese el nombre del profesor(a): ";
    cin >> ponderacion;

    solemne nuevaPrueba(titulo, fecha, ponderacion, nombreProfesor, materia);

    int cantidadItems;
    cout << "Ingrese la cantidad de items: ";
    cin >> cantidadItems;

    for (int i = 0; i < cantidadItems; ++i) {
        string tituloItem;
        cout << "Ingrese el título del item " << i + 1 << ": ";
        cin.ignore();
        getline(cin, tituloItem);

        Item nuevoItem(tituloItem, "Solemne");

        int cantidadPreguntas;
        cout << "Ingrese la cantidad de preguntas para el item " << i + 1 << ": ";
        cin >> cantidadPreguntas;

        for (int j = 0; j < cantidadPreguntas; ++j) {
           cin.ignore();
           string tituloPregunta , tipoPregunta;
           cout<<"Ingrese el título de la pregunta " << j + 1 << ": ";
           getline(cin, tituloPregunta);
           cout << "Ingrese el tipo de pregunta (Verdadero/Falso, Opcion Multiple, etc.): ";
           getline(cin, tipoPregunta);

           pregunta nuevaPregunta(tituloPregunta, tipoPregunta);
           nuevoItem.agregarPregunta(tituloPregunta, tipoPregunta);
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