#include <iostream>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <cstdio>
#include <stdlib.h>
#include <random>
#include <cctype>


using namespace std;

char click;

class Login{
    private:
        char User[20];
        char Password[30];

    public: 

    char usuario[100];
    char contra[100];
    char *save;
    string usuarioAdmin;
    string contraAdmin;
    unsigned int CodigoUsuario; 
    int idUsuario;
    int IDUSER;
    char USERNAME[100];
    char USERPASSWORD[100];

    void GenerarCodigoUsuario(){
        random_device rd; // Se utiliza para obtener una semilla verdaderamente aleatoria
        mt19937 gen(rd()); // Mersenne Twister 19937 como generador

        // Definir el rango para los números aleatorios (en este caso, de 1 a 100)
        uniform_int_distribution<> distribucion(1, 10000);

        // Generar el número aleatorio y asignarlo a la propiedad
        CodigoUsuario = distribucion(gen);
    }
    

        void Registrar(){

            FILE *fp;
            fp = fopen( "Login.txt" , "a+" );

            GenerarCodigoUsuario();
        
            cout << "Ingresa nombre a registrar: ";
            cin >> User;

            cout << "Ingresa Contrasena a registrar: ";
            cin >> Password;

            const char *Separador = " | ";
            char IDAletorio[100];

            itoa(CodigoUsuario,IDAletorio,10);

            fputs(IDAletorio,fp);
            fputs(Separador, fp);
            fputs(User, fp);
            fputs(Separador, fp);
            fputs(Password, fp);
            fputs("\n",fp);

            

            fclose(fp);

        }


        bool login(char *user, char *password) {
            FILE *fp;
            char buffer[1000];
            bool usuarioEncontrado = false;

            fp = fopen("Login.txt", "r");

            if (fp == NULL) {
                cout << "Error al abrir el archivo" << endl;
                return false;
            }

            while (fgets(buffer, 1000, fp)) {

                if (sscanf(buffer, "%d | %99s | %99s |", &idUsuario, USERNAME, USERPASSWORD) == 3) {
                    if (strcmp(USERNAME, user) == 0 && strcmp(USERPASSWORD, password) == 0) {
                        usuarioEncontrado = true;
                        cout << "\nBienvenido " << user << " " << password << endl;
                        IDUSER = idUsuario;
                        break;
                    }
                }
            }

            fclose(fp);

            if (!usuarioEncontrado) {
                cout << "\nUsuario no encontrado" << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }

            return usuarioEncontrado;
}


};


const int FILAS = 6;
const int COLUMNAS = 6;
char asientos[FILAS][COLUMNAS];
int numeroPasajeroAsiento;

class tickets
{
    private:
    Login lo;

    bool ticketSeleccionado;

    int IdFechaSalida;
    int DiaFechaSalida;
    char MesFechaSalida[100];
    int AñoFechaSalida;

    int IdFechaRetorno;
    int DiaFechaRetorno;
    char MesFechaRetorno[100];
    int AñoFechaRetorno;


    int IdOrigenVuelo;
    char OrigenVuelo[200];

    int IdDestinoVuelo;
    char DestinoVuelo[200];

    char pais[500];
    int PrecioBasico;
    int PrecioIntermedio;
    int PrecioPremiun;

    int pasajero;

    

    // -------------- var resultados --------------------

    int dFechaSalida;
    char *mFechaSalida;
    int aFechaSalida;

    int dFechaRetorno;
    char *mFechaRetorno;
    int aFechaRetorno;

    int OrigenVueloID;
    char *separadorORI;
    char *OrigenVueloP;

    int DestinoVueloID;
    char *separadorDEST;
    char *DestinoVueloP;

    int PrecioPlanVueloRES;

    int pasajeroRES;

    char *punteroPlan;


    public:

        string NombrePlanVuelo;
        string asientosAlmacenados;
        char *asientosAlmacenadosRES = asientosAlmacenados.data();
        unsigned int CodigoTickets;
        
        // Método para generar el código aleatorio
        void generarCodigo() {
            random_device rd; // Se utiliza para obtener una semilla verdaderamente aleatoria
            mt19937 gen(rd()); // Mersenne Twister 19937 como generador

            // Definir el rango para los números aleatorios (en este caso, de 1 a 100)
            uniform_int_distribution<> distribucion2(0, 100000);

            // Generar el número aleatorio y asignarlo a la propiedad
            CodigoTickets = distribucion2(gen);
        }



                // -------------- Fecha De Salida --------------------

        void AgregarFechaSalida(){
            FILE *fp;
            fp = fopen("FechaSalida.txt" , "a+");

            cout << "Ingrese ID de la fecha de salida del vuelo: ";
            cin >> IdFechaSalida;
            cout << "Ingresa el DIA de salida del vuelo (numero): ";
            cin >> DiaFechaSalida;
            cout << "Ingresa el MES de salida del vuelo (Letra): ";
            cin >> MesFechaSalida;
            cout << "Ingresa el AÑO de salida del vuelo (numero): ";
            cin >> AñoFechaSalida;

            const char *SeparadorFecha = "-------------------";

            char idStr[20];
            char diaStr[20];
            char AñoStr[20];

            itoa(IdFechaSalida,idStr,10);
            itoa(DiaFechaSalida,diaStr,10);
            itoa(AñoFechaSalida,AñoStr,10);

            fputs(idStr,fp);
            fputs("\n",fp);
            fputs(diaStr,fp);
            fputs("\n",fp);
            fputs(MesFechaSalida,fp);
            fputs("\n",fp);
            fputs(AñoStr,fp);
            fputs(SeparadorFecha,fp);


            fclose(fp);

        }

        void CargarFechaSalida(){
            FILE *fp;
            fp = fopen("FechaSalida.txt", "r");


            while (fscanf(fp, "%d\n%d\n%s\n%d\n", &IdFechaSalida, &DiaFechaSalida, MesFechaSalida, &AñoFechaSalida) != EOF) {
                cout << "ID: " << IdFechaSalida << endl;
                cout << "Dia: " << DiaFechaSalida << endl;
                cout << "Mes: " << MesFechaSalida << endl;
                cout << "Anio: " << AñoFechaSalida << endl;

                // Leer el separador
                char separador[20];
                fscanf(fp, "%s\n", separador);
                cout << "-------------------" << endl;
            }

            fclose(fp);
            
        }


        void ActualizarFechaSalida(int idModificar) {
            FILE *fp, *tempFile;
            fp = fopen("FechaSalida.txt", "r");
            tempFile = fopen("TempFechaSalida.txt", "w");

            int idActual, diaActual, añoActual;
            char mesActual[20], separador[20];

            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%s\n%d\n%s\n", &idActual, &diaActual, mesActual, &añoActual, separador) != EOF) {
                if (idActual == idModificar) {
                    encontrado = true;

                    // Mostrar los detalles actuales
                    cout << "Detalles actuales del registro ID " << idModificar << ":" << endl;
                    cout << "ID: " << idActual << endl;
                    cout << "Dia: " << diaActual << endl;
                    cout << "Mes: " << mesActual << endl;
                    cout << "Anio: " << añoActual << endl;
                    cout << "-------------------" << endl;

                    // Solicitar la modificación
                    int nuevoDia, nuevoAño;
                    char nuevoMes[20];

                    cout << "Ingresa el nuevo DIA de salida del vuelo (numero): ";
                    cin >> nuevoDia;
                    cout << "Ingresa el nuevo MES de salida del vuelo (Letra): ";
                    cin >> nuevoMes;
                    cout << "Ingresa el nuevo AÑO de salida del vuelo (numero): ";
                    cin >> nuevoAño;

                    // Escribir la modificación en el archivo temporal
                    fprintf(tempFile, "%d\n%d\n%s\n%d\n%s\n", idModificar, nuevoDia, nuevoMes, nuevoAño, separador);
                    cout << "Registro ID " << idModificar << " modificado correctamente." << endl;
                    cout << "-------------------" << endl;
                } else {
                    // Escribir los registros sin modificar en el archivo temporal
                    fprintf(tempFile, "%d\n%d\n%s\n%d\n%s\n", idActual, diaActual, mesActual, añoActual, separador);
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("FechaSalida.txt"); // Eliminar el archivo original
            rename("TempFechaSalida.txt", "FechaSalida.txt"); // Renombrar el archivo temporal
            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void EliminarFechaSalida(int idEliminar) {
            FILE *fp, *tempFile;
            fp = fopen("FechaSalida.txt", "r");
            tempFile = fopen("TempFechaSalida.txt", "w");

            int idActual, diaActual, añoActual;
            char mesActual[20], separador[20];

            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%s\n%d\n%s\n", &idActual, &diaActual, mesActual, &añoActual, separador) != EOF) {
                if (idActual == idEliminar) {
                    encontrado = true;
                    cout << "Registro ID " << idEliminar << " eliminado correctamente." << endl;
                    cout << "-------------------" << endl;
                } else {
                    // Escribir los registros que no se deben eliminar en el archivo temporal
                    fprintf(tempFile, "%d\n%d\n%s\n%d\n%s\n", idActual, diaActual, mesActual, añoActual, separador);
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("FechaSalida.txt"); // Eliminar el archivo original
            rename("TempFechaSalida.txt", "FechaSalida.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void SeleccionarFechaSalida(){

                CargarFechaSalida();

        int idSeleccion;
        cout<< "\nSelecciona una fecha de salida(ID): ";
        cin >> idSeleccion;

        FILE *fp;
        fp = fopen("FechaSalida.txt", "r");

        if (fp != NULL) {
            

            bool encontrado = false;

            while (fscanf(fp, "%d%d%s%d", &IdFechaSalida, &DiaFechaSalida, MesFechaSalida, &AñoFechaSalida) != EOF) {
                if (IdFechaSalida == idSeleccion) {
                    encontrado = true;
                    
                    dFechaSalida =DiaFechaSalida;
                    mFechaSalida = MesFechaSalida;
                    aFechaSalida = AñoFechaSalida;
                    
                    ticketSeleccionado = true;
                    break;
                }
            }

            if (!encontrado) {
                cout << "Fecha no encontrada.";
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }

            fclose(fp);
        } else {
            cout << "No se pudo abrir el archivo.";
            cout << "\n\nDale click para volver al menu";
                click = getch();
        }

        }

        






                // -------------- Fecha De Retorno --------------------

        void AgregarFechaRetorno(){
            FILE *fp;
            fp = fopen("FechaRetorno.txt" , "a+");

            cout << "Ingrese ID de la fecha de retorno del vuelo: ";
            cin >> IdFechaRetorno;
            cout << "Ingresa el DIA de retorno del vuelo (numero): ";
            cin >> DiaFechaRetorno;
            cout << "Ingresa el MES de retorno del vuelo (Letra): ";
            cin >> MesFechaRetorno;
            cout << "Ingresa el AÑO de retorno del vuelo (numero): ";
            cin >> AñoFechaRetorno;

            const char *SeparadorFecha = "-------------------";

            char idStr[20];
            char diaStr[20];
            char AñoStr[20];

            itoa(IdFechaSalida,idStr,10);
            itoa(DiaFechaRetorno,diaStr,10);
            itoa(AñoFechaRetorno,AñoStr,10);

            fputs(idStr,fp);
            fputs("\n",fp);
            fputs(diaStr,fp);
            fputs("\n",fp);
            fputs(MesFechaRetorno,fp);
            fputs("\n",fp);
            fputs(AñoStr,fp);
            fputs(SeparadorFecha,fp);

            fclose(fp);
        }

        void CargarFechaRetorno(){
            FILE *fp;
            fp = fopen("FechaRetorno.txt", "r");


            while (fscanf(fp, "%d\n%d\n%s\n%d\n", &IdFechaRetorno, &DiaFechaRetorno, MesFechaRetorno, &AñoFechaRetorno) != EOF) {
                cout << "ID: " << IdFechaRetorno << endl;
                cout << "Dia: " << DiaFechaRetorno << endl;
                cout << "Mes: " << MesFechaRetorno << endl;
                cout << "Anio: " << AñoFechaRetorno << endl;

                // Leer el separador
                char separador[20];
                fscanf(fp, "%s\n", separador);
                cout << "-------------------" << endl;
            }

            fclose(fp);
        }
        
        void ModificarFechaRetorno(int idModificar) {
            FILE *fp, *tempFile;
            fp = fopen("FechaRetorno.txt", "r");
            tempFile = fopen("TempFechaRetorno.txt", "w");

            int idActual, diaActual, añoActual;
            char mesActual[20], separador[20];

            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%s\n%d\n%s\n", &idActual, &diaActual, mesActual, &añoActual, separador) != EOF) {
                if (idActual == idModificar) {
                    encontrado = true;

                    // Mostrar los detalles actuales
                    cout << "Detalles actuales del registro ID " << idModificar << ":" << endl;
                    cout << "ID: " << idActual << endl;
                    cout << "Dia: " << diaActual << endl;
                    cout << "Mes: " << mesActual << endl;
                    cout << "Anio: " << añoActual << endl;
                    cout << "-------------------" << endl;

                    // Solicitar la modificación
                    int nuevoDia, nuevoAño;
                    char nuevoMes[20];

                    cout << "Ingresa el nuevo DIA de retorno del vuelo (numero): ";
                    cin >> nuevoDia;
                    cout << "Ingresa el nuevo MES de retorno del vuelo (Letra): ";
                    cin >> nuevoMes;
                    cout << "Ingresa el nuevo AÑO de retorno del vuelo (numero): ";
                    cin >> nuevoAño;

                    // Escribir la modificación en el archivo temporal
                    fprintf(tempFile, "%d\n%d\n%s\n%d\n%s\n", idModificar, nuevoDia, nuevoMes, nuevoAño, separador);
                    cout << "Registro ID " << idModificar << " modificado correctamente." << endl;
                    cout << "-------------------" << endl;
                } else {
                    // Escribir los registros sin modificar en el archivo temporal
                    fprintf(tempFile, "%d\n%d\n%s\n%d\n%s\n", idActual, diaActual, mesActual, añoActual, separador);
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("FechaRetorno.txt"); // Eliminar el archivo original
            rename("TempFechaRetorno.txt", "FechaRetorno.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void EliminarFechaRetorno(int idEliminar) {
            FILE *fp, *tempFile;
            fp = fopen("FechaRetorno.txt", "r");
            tempFile = fopen("TempFechaRetorno.txt", "w");

            int idActual, diaActual, añoActual;
            char mesActual[20], separador[20];

            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%s\n%d\n%s\n", &idActual, &diaActual, mesActual, &añoActual, separador) != EOF) {
                if (idActual == idEliminar) {
                    encontrado = true;
                    cout << "Registro ID " << idEliminar << " eliminado correctamente." << endl;
                    cout << "-------------------" << endl;
                } else {
                    // Escribir los registros que no se deben eliminar en el archivo temporal
                    fprintf(tempFile, "%d\n%d\n%s\n%d\n%s\n", idActual, diaActual, mesActual, añoActual, separador);
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("FechaRetorno.txt"); // Eliminar el archivo original
            rename("TempFechaRetorno.txt", "FechaRetorno.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void SeleccionarFechaRetorno(){

            CargarFechaRetorno();
        
        int IdSeleccionFechaRetorno;
        cout<< "\nSelecciona una fecha de salida(ID): ";
        cin >> IdSeleccionFechaRetorno;

        FILE *fp;
        fp = fopen("FechaRetorno.txt", "r");

        if (fp != NULL) {
            

            bool encontrado = false;

            while (fscanf(fp, "%d%d%s%d", &IdFechaRetorno, &DiaFechaRetorno, MesFechaRetorno, &AñoFechaRetorno) != EOF) {
                if (IdFechaRetorno == IdSeleccionFechaRetorno) {
                    encontrado = true;
                    
                    dFechaRetorno =DiaFechaRetorno;
                    mFechaRetorno = MesFechaRetorno;
                    aFechaRetorno = AñoFechaRetorno;

                    ticketSeleccionado = true;
                    break;
                }
            }

            if (!encontrado) {
                cout << "Fecha no encontrada.";
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }

            fclose(fp);
        } else {
            cout << "No se pudo abrir el archivo.";
            cout << "\n\nDale click para volver al menu";
                click = getch();
        }
        }







                // -------------- Origen vuelo --------------------

        void AgregarOrigenVuelo(){
            FILE *fp;
            fp = fopen("OrigenVuelo.txt" , "a+");

            cout << "Ingrese el ID del pais de ORIGEN del vuelo: ";
            cin >> IdOrigenVuelo;
            cout << "Ingrese pais de ORIGEN de vuelos: ";
            cin >> OrigenVuelo;

            const char *SeparadorID = "- ";

            char idStrOrigen[20];

            itoa(IdOrigenVuelo,idStrOrigen,10);

            fputs(idStrOrigen,fp);
            fputs(SeparadorID,fp);
            fputs(OrigenVuelo,fp);

            fclose(fp);

        }        

        void CargarOrigenVuelo(){
            FILE *fp;
            fp = fopen("OrigenVuelo.txt", "r");
            char buffer[1000];

            while (!feof(fp))
            {
                if (fgets(buffer,1000,fp))
                {
                    cout << buffer;
                }
                
            }

            fclose(fp);
        }


        void ModificarOrigenVuelo(int idModificar) {
            FILE *fp, *tempFile;
            fp = fopen("OrigenVuelo.txt", "r");
            tempFile = fopen("TempOrigenVuelo.txt", "w");

            int idActual;
            char buffer[1000];

            bool encontrado = false;

            while (!feof(fp)) {
                if (fgets(buffer, 1000, fp)) {
                    sscanf(buffer, "%d", &idActual);
                    if (idActual == idModificar) {
                        encontrado = true;

                        // Mostrar detalles actuales
                        cout << "Detalle actual del registro con ID " << idModificar << ": ";
                        cout << buffer << endl;
                        cout << "-------------------" << endl;

                        // Solicitar modificación
                        char nuevoOrigen[1000];
                        cout << "Ingrese el nuevo país de origen: ";
                        cin.ignore(); // Limpiar el buffer de entrada
                        cin.getline(nuevoOrigen, 1000);

                        // Escribir la modificación en el archivo temporal
                        fprintf(tempFile, "%d - %s\n", idModificar, nuevoOrigen);
                        cout << "Registro ID " << idModificar << " modificado correctamente." << endl;
                        cout << "-------------------" << endl;
                    } else {
                        // Escribir los registros sin modificar en el archivo temporal
                        fputs(buffer, tempFile);
                    }
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("OrigenVuelo.txt"); // Eliminar el archivo original
            rename("TempOrigenVuelo.txt", "OrigenVuelo.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void EliminarOrigenVuelo(int idEliminar) {
            FILE *fp, *tempFile;
            fp = fopen("OrigenVuelo.txt", "r");
            tempFile = fopen("TempOrigenVuelo.txt", "w");

            int idActual;
            char buffer[1000];

            bool encontrado = false;

            while (!feof(fp)) {
                if (fgets(buffer, 1000, fp)) {
                    sscanf(buffer, "%d", &idActual);
                    if (idActual == idEliminar) {
                        encontrado = true;
                        cout << "Registro ID " << idEliminar << " eliminado correctamente." << endl;
                        cout << "-------------------" << endl;
                    } else {
                        // Escribir los registros que no se deben eliminar en el archivo temporal
                        fputs(buffer, tempFile);
                    }
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("OrigenVuelo.txt"); // Eliminar el archivo original
            rename("TempOrigenVuelo.txt", "OrigenVuelo.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void SeleccionarOrigenVuelo(){

            CargarOrigenVuelo();
            
        int IdSeleccionOrigenVuelo;
        cout<< "\nSelecciona El origen de vuelo(ID): ";
        cin >> IdSeleccionOrigenVuelo;

        FILE *fp;
        fp = fopen("OrigenVuelo.txt", "r");

        if (fp != NULL) {
            

            bool encontrado = false;
            while (fscanf(fp, "%d%*[- ]%[^\n]", &IdOrigenVuelo,OrigenVuelo) != EOF) {
                if (IdOrigenVuelo == IdSeleccionOrigenVuelo) {
                    encontrado = true;
                    
                    OrigenVueloP = OrigenVuelo;

                    ticketSeleccionado = true;
                    break;
                }
            }

            if (!encontrado) {
                cout << "Fecha no encontrada.";
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }

            fclose(fp);
        } else {
            cout << "No se pudo abrir el archivo.";
            cout << "\n\nDale click para volver al menu";
            click = getch();
        }
        }




                // -------------- Destinacion vuelo --------------------

        void AgregarDestinoVuelo(){
            FILE *fp;
            fp = fopen("DestinoVuelo.txt" , "a+");

            cout << "Ingrese el ID del pais de DESTINO del vuelo";
            cin >> IdDestinoVuelo;
            cout << "Ingrese pais de DESTINO de vuelos";
            cin >> DestinoVuelo;

            const char *SeparadorID = "- ";

            char idStrDestino[20];

            itoa(IdDestinoVuelo,idStrDestino,10);

            fputs(idStrDestino,fp);
            fputs(SeparadorID,fp);
            fputs(DestinoVuelo,fp);

            fclose(fp);
        }

        void CargarDestinoVuelo(){
            FILE *fp;
            fp = fopen("DestinoVuelo.txt", "r");
            char buffer[1000];

            while (!feof(fp))
            {
                if (fgets(buffer,1000,fp))
                {
                    cout << buffer;
                }
                
            }

            fclose(fp);
        }


        void ModificarDestinoVuelo(int idModificar) {
            FILE *fp, *tempFile;
            fp = fopen("DestinoVuelo.txt", "r");
            tempFile = fopen("TempDestinoVuelo.txt", "w");

            int idActual;
            char buffer[1000];

            bool encontrado = false;

            while (!feof(fp)) {
                if (fgets(buffer, 1000, fp)) {
                    sscanf(buffer, "%d", &idActual);
                    if (idActual == idModificar) {
                        encontrado = true;

                        // Mostrar detalles actuales
                        cout << "Detalle actual del registro con ID " << idModificar << ": ";
                        cout << buffer << endl;
                        cout << "-------------------" << endl;

                        // Solicitar modificación
                        char nuevoDestino[1000];
                        cout << "Ingrese el nuevo país de destino: ";
                        cin.ignore(); // Limpiar el buffer de entrada
                        cin.getline(nuevoDestino, 1000);

                        // Escribir la modificación en el archivo temporal
                        fprintf(tempFile, "%d - %s\n", idModificar, nuevoDestino);
                        cout << "Registro ID " << idModificar << " modificado correctamente." << endl;
                        cout << "-------------------" << endl;
                    } else {
                        // Escribir los registros sin modificar en el archivo temporal
                        fputs(buffer, tempFile);
                    }
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("DestinoVuelo.txt"); // Eliminar el archivo original
            rename("TempDestinoVuelo.txt", "DestinoVuelo.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void EliminarDestinoVuelo(int idEliminar) {
            FILE *fp, *tempFile;
            fp = fopen("DestinoVuelo.txt", "r");
            tempFile = fopen("TempDestinoVuelo.txt", "w");

            int idActual;
            char buffer[1000];

            bool encontrado = false;

            while (!feof(fp)) {
                if (fgets(buffer, 1000, fp)) {
                    sscanf(buffer, "%d", &idActual);
                    if (idActual == idEliminar) {
                        encontrado = true;
                        cout << "Registro ID " << idEliminar << " eliminado correctamente." << endl;
                        cout << "-------------------" << endl;
                    } else {
                        // Escribir los registros que no se deben eliminar en el archivo temporal
                        fputs(buffer, tempFile);
                    }
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("DestinoVuelo.txt"); // Eliminar el archivo original
            rename("TempDestinoVuelo.txt", "DestinoVuelo.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el registro con el ID especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void SeleccionarDestinoVuelo(){

            CargarDestinoVuelo();
            
            int IdSeleccionDestinoVuelo;
            cout<< "\nSelecciona El Destino de vuelo(ID): ";
            cin >> IdSeleccionDestinoVuelo;

            FILE *fp;
            fp = fopen("DestinoVuelo.txt", "r");

            if (fp != NULL) {
                

                bool encontrado = false;
              
                while (fscanf(fp, "%d%*[- ]%[^\n]", &IdDestinoVuelo,DestinoVuelo) != EOF) {
                    if (IdDestinoVuelo == IdSeleccionDestinoVuelo) {
                        encontrado = true;
                        
                        DestinoVueloP = DestinoVuelo;

                        ticketSeleccionado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Fecha no encontrada.";
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }

                fclose(fp);
            } else {
                cout << "No se pudo abrir el archivo.";
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }





            // -------------- Plan de vuelo --------------------

        void AgregarPlanVuelo(){
            FILE *fp;
            fp = fopen("PlanVuelo.txt" , "a+");

            cout << "Ingrese el pais del plan de vuelo que digitaras: ";
            cin >> pais;
            cout << "Ingrese el plan Basico de vuelo: ";
            cin >> PrecioBasico;
            cout << "Ingrese el plan intermedio de vuelo: ";
            cin >> PrecioIntermedio;
            cout << "Ingrese el plan premiun de vuelo: ";
            cin >> PrecioPremiun;
            

            const char *separator = "------------------------------";

            char precioBasicoStr[100];
            char precioIntermedioStr[100];
            char precioPremiunStr[100];

            itoa(PrecioBasico,precioBasicoStr,10);
            itoa(PrecioIntermedio,precioIntermedioStr,10);
            itoa(PrecioPremiun,precioPremiunStr,10);


            fputs(pais,fp);
            fputs("\n",fp);
            fputs(precioBasicoStr,fp);
            fputs("\n",fp);
            fputs(precioIntermedioStr,fp);
            fputs("\n",fp);
            fputs(precioPremiunStr,fp);
            fputs("\n",fp);
            fputs(separator,fp);
            fputs("\n",fp);

            fclose(fp);
        } 

        void CargarPlanVuelo(){
            FILE *fp;
            fp = fopen("PlanVuelo.txt", "r");
            char buffer[1000];

            while (!feof(fp))
            {
                if (fgets(buffer,1000,fp))
                {
                    
                    cout << buffer;
                }
                
            }

            fclose(fp);
        }


        void ModificarPlanVuelo(const char* paisModificar) {
            FILE *fp, *tempFile;
            fp = fopen("PlanVuelo.txt", "r");
            tempFile = fopen("TempPlanVuelo.txt", "w");

            char pais[100];
            int precioBasico, precioIntermedio, precioPremiun;
            bool encontrado = false;

            while (fscanf(fp, "%s\n%d\n%d\n%d\n------------------------------\n", pais, &precioBasico, &precioIntermedio, &precioPremiun) != EOF) {
                if (strcmp(pais, paisModificar) == 0) {
                    encontrado = true;

                    cout << "Detalles actuales del plan de vuelo para " << paisModificar << ": ";
                    cout << pais << endl;
                    cout << precioBasico << endl;
                    cout << precioIntermedio << endl;
                    cout << precioPremiun << endl;
                    cout << "-------------------" << endl;

                    // Solicitar modificación
                    int nuevoPrecioBasico, nuevoPrecioIntermedio, nuevoPrecioPremiun;
                    cout << "Ingrese el nuevo precio básico: ";
                    cin >> nuevoPrecioBasico;
                    cout << "Ingrese el nuevo precio intermedio: ";
                    cin >> nuevoPrecioIntermedio;
                    cout << "Ingrese el nuevo precio premium: ";
                    cin >> nuevoPrecioPremiun;

                    // Escribir la modificación en el archivo temporal
                    fprintf(tempFile, "%s\n%d\n%d\n%d\n------------------------------\n", pais, nuevoPrecioBasico, nuevoPrecioIntermedio, nuevoPrecioPremiun);
                    cout << "Plan de vuelo para " << paisModificar << " modificado correctamente." << endl;
                    cout << "-------------------" << endl;
                } else {
                    // Escribir los registros sin modificar en el archivo temporal
                    fprintf(tempFile, "%s\n%d\n%d\n%d\n------------------------------\n", pais, precioBasico, precioIntermedio, precioPremiun);
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("PlanVuelo.txt");
            rename("TempPlanVuelo.txt", "PlanVuelo.txt"); 

            if (!encontrado) {
                cout << "No se encontró el plan de vuelo para el país especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }
        

        void EliminarPlanVuelo(const char* paisEliminar) {
            FILE *fp, *tempFile;
            fp = fopen("PlanVuelo.txt", "r");
            tempFile = fopen("TempPlanVuelo.txt", "w");

            char pais[100];
            int precioBasico, precioIntermedio, precioPremiun;
            bool encontrado = false;

            while (fscanf(fp, "%s\n%d\n%d\n%d\n------------------------------\n", pais, &precioBasico, &precioIntermedio, &precioPremiun) != EOF) {
                if (strcmp(pais, paisEliminar) == 0) {
                    encontrado = true;
                    cout << "Plan de vuelo para " << paisEliminar << " eliminado correctamente." << endl;
                    cout << "-------------------" << endl;
                } else {
                    // Escribir los registros que no se deben eliminar en el archivo temporal
                    fprintf(tempFile, "%s\n%d\n%d\n%d\n------------------------------\n", pais, precioBasico, precioIntermedio, precioPremiun);
                }
            }

            fclose(fp);
            fclose(tempFile);

            remove("PlanVuelo.txt"); // Eliminar el archivo original
            rename("TempPlanVuelo.txt", "PlanVuelo.txt"); // Renombrar el archivo temporal

            if (!encontrado) {
                cout << "No se encontró el plan de vuelo para el país especificado." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void CargarPlanVueloPorID(){
            FILE *fp;
            fp = fopen("PlanVuelo.txt", "r");


            while (fscanf(fp, "%s\n%d\n%d\n%d\n", pais, &PrecioBasico, &PrecioIntermedio, &PrecioPremiun) != EOF) {

                if (strcmp(pais, DestinoVueloP) == 0)
                {
                    cout << "Pais: " << pais << "\n\n";
                    cout << "1- Plan Basico - " << PrecioBasico << "$" << "\n\n";
                    cout << "2- Plan Intermedio - " << PrecioIntermedio << "$" << "\n\n";
                    cout << "3- Plan Premiun - " << PrecioPremiun << "$" << "\n\n";
                
                    break;
                }
                
            }

            fclose(fp);
        }


        void SeleccionarPlanVuelo(){

            CargarPlanVueloPorID();

            int IdSeleccionPlanVuelo;
            cout<< "\nSelecciona El plan de vuelo(ID): ";
            cin >> IdSeleccionPlanVuelo;

            FILE *fp;
            fp = fopen("PlanVuelo.txt", "r");

            if (fp != NULL) {
                

                bool encontrado = false;
                while (fscanf(fp, "%s\n%d\n%d\n%d\n", pais, &PrecioBasico, &PrecioIntermedio, &PrecioPremiun) != EOF) {
                    if (IdSeleccionPlanVuelo == 1) {
                        encontrado = true;
                        
                        NombrePlanVuelo = "Basico";
                        punteroPlan = NombrePlanVuelo.data();
                        PrecioPlanVueloRES = PrecioBasico;

                        ticketSeleccionado = true;
                        break;
                    }
                    else if (IdSeleccionPlanVuelo == 2)
                    {
                        encontrado = true;

                        NombrePlanVuelo = "Intermedio";
                        punteroPlan = NombrePlanVuelo.data();
                        PrecioPlanVueloRES = PrecioIntermedio;

                        ticketSeleccionado = true;
                        break;
                    }
                    else if (IdSeleccionPlanVuelo == 3)
                    {
                        encontrado = true;

                        NombrePlanVuelo = "Premiun";
                        punteroPlan = NombrePlanVuelo.data();
                        PrecioPlanVueloRES = PrecioPremiun;

                        ticketSeleccionado = true;
                        break;
                    }
                    
                }

                if (!encontrado) {
                    cout << "Plan no encontrada.";
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }

                fclose(fp);
            } else {
                cout << "No se pudo abrir el archivo.";
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }

        }



            // -------------- Pasajeros --------------------

        void agregarPasajeros(){         

            cout << "Ingrese la cantidad de pasajeros, LIMITE: 9 pasajeros: ";
            cin >> pasajero;

            pasajeroRES = pasajero;
            numeroPasajeroAsiento = pasajero;

        }

            // -------------- Inicializar asientos disponibles --------------------

            void inicializarAsientos() {
            for (int i = 0; i < FILAS; ++i) {
                for (int j = 0; j < COLUMNAS; ++j) {
                    asientos[i][j] = 'O'; // 'O' indica que el asiento está disponible
                    }
                }
            }


            // -------------- Asientos Plan Basico --------------------

            void mostrarAsientosBasico() {
                cout << "Mapa de asientos:" << endl;
                char fila_letra = 'a';
                for (int i = 0; i < FILAS; ++i) {
                    cout << "(" << fila_letra << ")" << "   ";
                    fila_letra++;
                    for (int j = 0; j < COLUMNAS; ++j) {
                        if (j == 3)
                        {
                            cout << "     ";
                        }          
                        cout << asientos[i][j] << " ";
                    }
                    cout << endl;
                }
            }


            void guardarAsientosEnArchivoBasicos() {
                FILE* fp;
                fp = fopen("Basico.txt", "w");
                if (fp != NULL) {
                    for (int i = 0; i < FILAS; ++i) {
                        for (int j = 0; j < COLUMNAS; ++j) {
                            fprintf(fp, "%c ", asientos[i][j]);
                        }
                        fprintf(fp, "\n");
                    }
                    fclose(fp);
                    cout << "Datos de asientos guardados en archivo 'asientos.txt'" << endl;
                } else {
                    cout << "No se pudo abrir el archivo." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            void cargarAsientosDesdeArchivoBasicos() {
                FILE* fp;
                fp = fopen("Basico.txt", "r");
                if (fp != NULL) {
                    for (int i = 0; i < FILAS; ++i) {
                        for (int j = 0; j < COLUMNAS; ++j) {
                            fscanf(fp, " %c", &asientos[i][j]);
                        }
                    }
                    fclose(fp);
                    cout << "Datos de asientos cargados desde archivo 'asientos.txt'" << endl;
                } else {
                    cout << "No se pudo abrir el archivo." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            bool reservarAsientoBasicos(int fila, int columna) {
                if (asientos[fila - 'a'][columna - 1] == 'O') {
                    asientos[fila - 'a'][columna - 1] = 'X'; // 'X' indica que el asiento está reservado
                    return true;
                } else {
                    cout << "El asiento seleccionado no está disponible." << endl;
                    return false;
                }
            }


            void modificarAsientoBasico(char fila, int columna, char nuevoEstado) {
                int filaInd = fila - 'a'; 
                if (filaInd >= 0 && filaInd < FILAS && columna >= 1 && columna <= COLUMNAS) {
                    asientos[filaInd][columna - 1] = nuevoEstado;
                    cout << "Asiento en la fila " << fila << " columna " << columna << " modificado a '" << nuevoEstado << "'." << endl;
                    guardarAsientosEnArchivoBasicos();
                } else {
                    cout << "Fila o columna fuera de rango." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            void modificarAsientosPendientesPorIDBasico(int ID) {
            FILE* fp;
            FILE* tempFile;
            fp = fopen("Tickets.txt", "r");
            tempFile = fopen("tempTickets.txt", "w");

            char fila_char2;
            int columna2;
            int IDTicket, idval, dFechaSalidaR, aFechaSalidaR, dFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR;
            char mFechaSalidaR[20], mFechaRetornoR[20], OrigenVueloCargarR[100], DestinoVueloPCargarR[100], PlanR[100], PriceR[100], asientoCargarR[100];
            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", &IDTicket, &idval, &dFechaSalidaR, mFechaSalidaR, &aFechaSalidaR, &dFechaRetornoR, mFechaRetornoR, &aFechaRetornoR, &PrecioPlanVueloR, &pasajeroR, OrigenVueloCargarR, DestinoVueloPCargarR, PlanR, PriceR, asientoCargarR) != EOF) {

                if (IDTicket == ID && strcmp(PlanR, "Basico") == 0) {
                    encontrado = true;

                    cargarAsientosDesdeArchivoBasicos();
                    for (int i = 1; i <= pasajeroR; i++) {
                        bool asientoDisp = false;
                        mostrarAsientosBasico();
                        while (!asientoDisp) {
                            cout << "Ingrese la fila y columna del asiento a reservar para cliente " << i << " (ejemplo: a 2): ";
                            cin >> fila_char2 >> columna2;
                            if (fila_char2 >= 'a' && fila_char2 < 'a' + FILAS) {
                                if (asientos[fila_char2 - 'a'][columna2 - 1] == 'O') {
                                    reservarAsientoBasicos(fila_char2, columna2);
                                    asientosAlmacenados += fila_char2 + to_string(columna2);
                                    guardarAsientosEnArchivoBasicos();
                                    asientoDisp = true;
                                } else {
                                cout << "El asiento seleccionado no está disponible." << endl;
                                }
                            } else {
                            cout << "Fila inválida." << endl;
                            
                            }
                        }
                    }

                    strcpy(asientoCargarR, asientosAlmacenados.data()); 
                }

                fprintf(tempFile, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", IDTicket, idval, dFechaSalidaR, mFechaSalidaR, aFechaSalidaR, dFechaRetornoR, mFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR, OrigenVueloCargarR, DestinoVueloPCargarR, PlanR, PriceR, asientoCargarR);

                char separador[20];
                fscanf(fp, "%s\n", separador);
                fprintf(tempFile, "%s\n", separador);
            }

            fclose(fp);
            fclose(tempFile);

            remove("Tickets.txt");
            rename("tempTickets.txt", "Tickets.txt");

            if (!encontrado) {
                cout << "No se encontró ningún ticket con el ID especificado y asientos pendientes." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            } else {
                cout << "Asientos de tickets pendientes con el ID especificado actualizados exitosamente." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


            // -------------- Asientos Plan intermedio --------------------

            void mostrarAsientosIntermedio() {
                cout << "Mapa de asientos:" << endl;
                char fila_letra = 'g';
                for (int i = 0; i < FILAS; ++i) {
                    cout << "(" << fila_letra << ")" << "   ";
                    fila_letra++;
                    for (int j = 0; j < COLUMNAS; ++j) {
                        if (j == 3)
                        {
                            cout << "     ";
                        }          
                        cout << asientos[i][j] << " ";
                    }
                    cout << endl;
                }
            }


            void guardarAsientosEnArchivoIntermedio() {
                FILE* fp;
                fp = fopen("Intermedio.txt", "w");
                if (fp != NULL) {
                    for (int i = 0; i < FILAS; ++i) {
                        for (int j = 0; j < COLUMNAS; ++j) {
                            fprintf(fp, "%c ", asientos[i][j]);
                        }
                        fprintf(fp, "\n");
                    }
                    fclose(fp);
                    cout << "Datos de asientos guardados en archivo 'asientos.txt'" << endl;
                } else {
                    cout << "No se pudo abrir el archivo." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            void cargarAsientosDesdeArchivoIntermedio() {
                FILE* fp;
                fp = fopen("Intermedio.txt", "r");
                if (fp != NULL) {
                    for (int i = 0; i < FILAS; ++i) {
                        for (int j = 0; j < COLUMNAS; ++j) {
                            fscanf(fp, " %c", &asientos[i][j]);
                        }
                    }
                    fclose(fp);
                    cout << "Datos de asientos cargados desde archivo 'asientos.txt'" << endl;
                } else {
                    cout << "No se pudo abrir el archivo." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            bool reservarAsientoIntermedio(int fila, int columna) {
                if (asientos[fila - 'g'][columna - 1] == 'O') {
                    asientos[fila - 'g'][columna - 1] = 'X'; // 'X' indica que el asiento está reservado
                    return true;
                } else {
                    cout << "El asiento seleccionado no está disponible." << endl;
                    return false;
                    
                }
            }

            
            void modificarAsientoIntermedio(char fila, int columna, char nuevoEstado) {
                int filaInd = fila - 'g'; 
                if (filaInd >= 0 && filaInd < FILAS && columna >= 1 && columna <= COLUMNAS) {
                    asientos[filaInd][columna - 1] = nuevoEstado;
                    cout << "Asiento en la fila " << fila << " columna " << columna << " modificado a '" << nuevoEstado << "'." << endl;
                    guardarAsientosEnArchivoIntermedio();
                } else {
                    cout << "Fila o columna fuera de rango." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            void modificarAsientosPendientesPorIDIntermedio(int ID) {
            FILE* fp;
            FILE* tempFile;
            fp = fopen("Tickets.txt", "r");
            tempFile = fopen("tempTickets.txt", "w");

            char fila_char2;
            int columna2;
            int IDTicket, idval, dFechaSalidaR, aFechaSalidaR, dFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR;
            char mFechaSalidaR[20], mFechaRetornoR[20], OrigenVueloCargarR[100], DestinoVueloPCargarR[100], PlanR[100], PriceR[100], asientoCargarR[100];
            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", &IDTicket, &idval, &dFechaSalidaR, mFechaSalidaR, &aFechaSalidaR, &dFechaRetornoR, mFechaRetornoR, &aFechaRetornoR, &PrecioPlanVueloR, &pasajeroR, OrigenVueloCargarR, DestinoVueloPCargarR, PlanR, PriceR, asientoCargarR) != EOF) {

                if (IDTicket == ID && strcmp(PlanR, "Intermedio") == 0) {
                    encontrado = true;

                    cargarAsientosDesdeArchivoIntermedio();
                    for (int i = 1; i <= pasajeroR; i++) {
                        bool asientoDisp = false;
                        mostrarAsientosIntermedio();
                        while (!asientoDisp) {
                            cout << "Ingrese la fila y columna del asiento a reservar para cliente " << i << " (ejemplo: g 2): ";
                            cin >> fila_char2 >> columna2;
                            if (fila_char2 >= 'g' && fila_char2 < 'g' + FILAS) {
                                if (asientos[fila_char2 - 'g'][columna2 - 1] == 'O') {
                                    reservarAsientoIntermedio(fila_char2, columna2);
                                    asientosAlmacenados += fila_char2 + to_string(columna2);
                                    guardarAsientosEnArchivoIntermedio();
                                    asientoDisp = true;
                                } else {
                                cout << "El asiento seleccionado no está disponible." << endl;
                                
                                }
                            } else {
                            cout << "Fila inválida." << endl;
                            
                            }
                        }
                    }

                    strcpy(asientoCargarR, asientosAlmacenados.data()); 
                }

                fprintf(tempFile, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", IDTicket, idval, dFechaSalidaR, mFechaSalidaR, aFechaSalidaR, dFechaRetornoR, mFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR, OrigenVueloCargarR, DestinoVueloPCargarR, PlanR, PriceR, asientoCargarR);

                char separador[20];
                fscanf(fp, "%s\n", separador);
                fprintf(tempFile, "%s\n", separador);
            }

            fclose(fp);
            fclose(tempFile);

            remove("Tickets.txt");
            rename("tempTickets.txt", "Tickets.txt");

            if (!encontrado) {
                cout << "No se encontró ningún ticket con el ID especificado y asientos pendientes." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            } else {
                cout << "Asientos de tickets pendientes con el ID especificado actualizados exitosamente." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }



            // -------------- Asientos Plan Premiun --------------------

            
            void mostrarAsientosPremiun() {
                cout << "Mapa de asientos:" << endl;
                char fila_letra = 'm';
                for (int i = 0; i < FILAS; ++i) {
                    cout << "(" << fila_letra << ")" << "   ";
                    fila_letra++;
                    for (int j = 0; j < COLUMNAS; ++j) {
                        if (j == 3)
                        {
                            cout << "     ";
                        }          
                        cout << asientos[i][j] << " ";
                    }
                    cout << endl;
                }
            }


            void guardarAsientosEnArchivoPremiun() {
                FILE* fp;
                fp = fopen("Premiun.txt", "w");
                if (fp != NULL) {
                    for (int i = 0; i < FILAS; ++i) {
                        for (int j = 0; j < COLUMNAS; ++j) {
                            fprintf(fp, "%c ", asientos[i][j]);
                        }
                        fprintf(fp, "\n");
                    }
                    fclose(fp);
                    cout << "Datos de asientos guardados en archivo 'asientos.txt'" << endl;
                } else {
                    cout << "No se pudo abrir el archivo." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            void cargarAsientosDesdeArchivoPremiun() {
                FILE* fp;
                fp = fopen("Premiun.txt", "r");
                if (fp != NULL) {
                    for (int i = 0; i < FILAS; ++i) {
                        for (int j = 0; j < COLUMNAS; ++j) {
                            fscanf(fp, " %c", &asientos[i][j]);
                        }
                    }
                    fclose(fp);
                    cout << "Datos de asientos cargados desde archivo 'asientos.txt'" << endl;
                } else {
                    cout << "No se pudo abrir el archivo." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            bool reservarAsientoPremiun(int fila, int columna) {
                if (asientos[fila - 'm'][columna - 1] == 'O') {
                    asientos[fila - 'm'][columna - 1] = 'X'; // 'X' indica que el asiento está reservado
                    return true;
                } else {
                    cout << "El asiento seleccionado no está disponible." << endl;
                    return false;
                    
                }
            }


            void modificarAsientoPremiun(char fila, int columna, char nuevoEstado) {
                int filaInd = fila - 'm'; 
                if (filaInd >= 0 && filaInd < FILAS && columna >= 1 && columna <= COLUMNAS) {
                    asientos[filaInd][columna - 1] = nuevoEstado;
                    cout << "Asiento en la fila " << fila << " columna " << columna << " modificado a '" << nuevoEstado << "'." << endl;
                    guardarAsientosEnArchivoPremiun();
                } else {
                    cout << "Fila o columna fuera de rango." << endl;
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                }
            }


            void modificarAsientosPendientesPorIDPremiun(int ID) {
            FILE* fp;
            FILE* tempFile;
            fp = fopen("Tickets.txt", "r");
            tempFile = fopen("tempTickets.txt", "w");

            char fila_char2;
            int columna2;
            int IDTicket, idval, dFechaSalidaR, aFechaSalidaR, dFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR;
            char mFechaSalidaR[20], mFechaRetornoR[20], OrigenVueloCargarR[100], DestinoVueloPCargarR[100], PlanR[100], PriceR[100], asientoCargarR[100];
            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", &IDTicket, &idval, &dFechaSalidaR, mFechaSalidaR, &aFechaSalidaR, &dFechaRetornoR, mFechaRetornoR, &aFechaRetornoR, &PrecioPlanVueloR, &pasajeroR, OrigenVueloCargarR, DestinoVueloPCargarR, PlanR, PriceR, asientoCargarR) != EOF) {

                if (IDTicket == ID && strcmp(PlanR, "Premiun") == 0) {
                    encontrado = true;

                    cargarAsientosDesdeArchivoPremiun();
                    for (int i = 1; i <= pasajeroR; i++) {
                        bool asientoDisp = false;
                        mostrarAsientosPremiun();
                        while (!asientoDisp) {
                            cout << "Ingrese la fila y columna del asiento a reservar para cliente " << i << " (ejemplo: m 2): ";
                            cin >> fila_char2 >> columna2;
                            if (fila_char2 >= 'm' && fila_char2 < 'm' + FILAS) {
                                if (asientos[fila_char2 - 'm'][columna2 - 1] == 'O') {
                                    reservarAsientoPremiun(fila_char2, columna2);
                                    asientosAlmacenados += fila_char2 + to_string(columna2);
                                    guardarAsientosEnArchivoPremiun();
                                    asientoDisp = true;
                                } else {
                                cout << "El asiento seleccionado no está disponible." << endl;
                                
                                }
                            } else {
                            cout << "Fila inválida." << endl;
                            
                            }
                        }
                    }

                    strcpy(asientoCargarR, asientosAlmacenados.data()); 
                }

                fprintf(tempFile, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", IDTicket, idval, dFechaSalidaR, mFechaSalidaR, aFechaSalidaR, dFechaRetornoR, mFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR, OrigenVueloCargarR, DestinoVueloPCargarR, PlanR, PriceR, asientoCargarR);

                char separador[20];
                fscanf(fp, "%s\n", separador);
                fprintf(tempFile, "%s\n", separador);
            }

            fclose(fp);
            fclose(tempFile);

            remove("Tickets.txt");
            rename("tempTickets.txt", "Tickets.txt");

            if (!encontrado) {
                cout << "No se encontró ningún ticket con el ID especificado y asientos pendientes." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            } else {
                cout << "Asientos de tickets pendientes con el ID especificado actualizados exitosamente." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


            // -------------- Ticket --------------------

        void agregarTicket(int ID){
            FILE *fp;
            fp = fopen("Tickets.txt" , "a+");
            generarCodigo();

            const char *SeparadorID = "------------------------";

            int TotalPrice = pasajeroRES * PrecioPlanVueloRES;

            char DaySalida[20];
            char YearSalida[20];
            char DayRetorno[20];
            char YearRetorno[20];
            char PrecioPlan[20];
            char PasajeroSTR[20];
            char IDSTR[20];
            char TotalPriceSTR[20];
            char CodigoTicketsSTR[20];

            itoa(dFechaSalida,DaySalida,10);
            itoa(aFechaSalida,YearSalida,10);
            itoa(dFechaRetorno,DayRetorno,10);
            itoa(aFechaRetorno,YearRetorno,10);
            itoa(PrecioPlanVueloRES,PrecioPlan,10);
            itoa(pasajeroRES,PasajeroSTR,10);
            itoa(ID,IDSTR,10);
            itoa(TotalPrice,TotalPriceSTR,10);
            itoa(CodigoTickets,CodigoTicketsSTR,10);
            
            fputs(CodigoTicketsSTR,fp);
            fputs("\n",fp);

            fputs(IDSTR,fp);
            fputs("\n",fp);

            fputs(DaySalida,fp);
            fputs("\n",fp);
            fputs(mFechaSalida,fp);
            fputs("\n",fp);
            fputs(YearSalida,fp);
            fputs("\n",fp);

            fputs(DayRetorno,fp);
            fputs("\n",fp);
            fputs(mFechaRetorno,fp);
            fputs("\n",fp);
            fputs(YearRetorno,fp);
            fputs("\n",fp);

            fputs(PrecioPlan,fp);
            fputs("\n",fp);

            fputs(PasajeroSTR,fp);
            fputs("\n",fp);

            fputs(OrigenVueloP,fp);
            fputs("\n",fp);
            fputs(DestinoVueloP,fp);
            fputs("\n",fp);

            fputs(punteroPlan,fp);
            fputs("\n",fp);

            fputs(TotalPriceSTR,fp);
            fputs("\n",fp);

            fputs(asientosAlmacenadosRES,fp);
            fputs("\n",fp);

            fputs(SeparadorID,fp);
             fputs("\n",fp);
            fclose(fp);
        }    


        void cargarTicket(){
            FILE *fp;
            fp = fopen("Tickets.txt", "r");
            int IDTicket, idval, dFechaSalidaR, aFechaSalidaR, dFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR;
            char mFechaSalidaR[20], mFechaRetornoR[20], OrigenVueloCargarR[100], DestinoVueloPCargarR[100], PlanR[100], PriceR[100], asientoCargarR[100];
            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", &IDTicket, &idval, &dFechaSalidaR, mFechaSalidaR, &aFechaSalidaR, &dFechaRetornoR, mFechaRetornoR, &aFechaRetornoR, &PrecioPlanVueloR, &pasajeroR,OrigenVueloCargarR,DestinoVueloPCargarR,PlanR, PriceR, asientoCargarR) != EOF) {

                
                    encontrado = true;
                    cout << "-----------------------------------" << endl;
                    cout << "          TICKET DE VUELO          " << endl;
                    cout << "-----------------------------------" << endl;
                    cout << "Codigo: " << IDTicket << endl;
                    cout << "Fecha de salida: " << dFechaSalidaR << "/" << mFechaSalidaR << "/" << aFechaSalidaR << endl;
                    cout << "Fecha de Retorno: " << dFechaRetornoR << "/" << mFechaRetornoR << "/" << aFechaRetornoR << endl;
                    cout << "Desde: " << OrigenVueloCargarR << endl;
                    cout << "Hasta: " << DestinoVueloPCargarR << endl;
                    cout << "Plan de vuelo: " << PlanR << " - " << PrecioPlanVueloR << "$" << endl;
                    cout << "Cantidad de pasajeros: " << pasajeroR << endl;
                    cout << "Precio Total: " << PriceR << "$" << endl;
                    cout << "Asientos: " << asientoCargarR << endl;
                    cout << "-----------------------------------" << endl;

                

                        char separador[20];
                        fscanf(fp, "%s\n", separador);
                        cout << "-------------------" << endl;
            }

            fclose(fp);

            if (!encontrado) {
                cout << "No se encontraron tickets asociados al usuario." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }


        void cargarTicketUser(int ID){
            FILE *fp;
            fp = fopen("Tickets.txt", "r");
            int IDTicket, idval, dFechaSalidaR, aFechaSalidaR, dFechaRetornoR, aFechaRetornoR, PrecioPlanVueloR, pasajeroR;
            char mFechaSalidaR[20], mFechaRetornoR[20], OrigenVueloCargarR[100], DestinoVueloPCargarR[100], PlanR[100], PriceR[100], asientoCargarR[100];
            bool encontrado = false;

            while (fscanf(fp, "%d\n%d\n%d\n%s\n%d\n%d\n%s\n%d\n%d\n%d\n%s\n%s\n%s\n%s\n%s\n", &IDTicket, &idval, &dFechaSalidaR, mFechaSalidaR, &aFechaSalidaR, &dFechaRetornoR, mFechaRetornoR, &aFechaRetornoR, &PrecioPlanVueloR, &pasajeroR,OrigenVueloCargarR,DestinoVueloPCargarR,PlanR, PriceR, asientoCargarR) != EOF) {

                if (idval == ID) {
                    encontrado = true;
                    cout << "-----------------------------------" << endl;
                    cout << "          TICKET DE VUELO          " << endl;
                    cout << "-----------------------------------" << endl;
                    cout << "Codigo: " << IDTicket << endl;
                    cout << "Fecha de salida: " << dFechaSalidaR << "/" << mFechaSalidaR << "/" << aFechaSalidaR << endl;
                    cout << "Fecha de Retorno: " << dFechaRetornoR << "/" << mFechaRetornoR << "/" << aFechaRetornoR << endl;
                    cout << "Desde: " << OrigenVueloCargarR << endl;
                    cout << "Hasta: " << DestinoVueloPCargarR << endl;
                    cout << "Plan de vuelo: " << PlanR << " - " << PrecioPlanVueloR << "$" << endl;
                    cout << "Cantidad de pasajeros: " << pasajeroR << endl;
                    cout << "Precio Total: " << PriceR << "$" << endl;
                    cout << "Asientos: " << asientoCargarR << endl;
                    cout << "-----------------------------------" << endl;

                }

                        char separador[20];
                        fscanf(fp, "%s\n", separador);
                        cout << "-------------------" << endl;
            }

            fclose(fp);

            if (!encontrado) {
                cout << "No se encontraron tickets asociados al usuario." << endl;
                cout << "\n\nDale click para volver al menu";
                click = getch();
            }
        }



        void ImprimirTicket(){

            if (ticketSeleccionado)
            {
            cout << "Codigo: " << CodigoTickets << endl;
            cout << "Fecha de salida:" << dFechaSalida << "/" << mFechaSalida << "/" <<aFechaSalida <<"\n";
            cout << "Fecha de Retorno:" << dFechaRetorno << "/" << mFechaRetorno << "/" <<aFechaRetorno <<"\n";
            cout << "Desde: " << OrigenVueloP <<"\n";
            cout << "hasta: " << DestinoVueloP <<"\n";
            cout << NombrePlanVuelo << " - "<< PrecioPlanVueloRES << "$" <<"\n";
            cout << "pasajeros: " << pasajeroRES <<"\n";
            cout << "PrecioTotal: " << pasajeroRES * PrecioPlanVueloRES << "$" <<"\n";
            cout << "asientos: " << asientosAlmacenadosRES;
            
               
            }else {
            cout << "Ningun ticket seleccionada." << endl;
            cout << "\n\nDale click para volver al menu";
            click = getch();
        }

            
        }   
    
};



int main()
{
    tickets ti;
    Login lo;
    int opcion1;
    int opcion2;
    int opcionRol;
    string decision;
    char fila_char;
    int columna;
    ti.inicializarAsientos();
    


            do
            {
                system("cls");
                cout<<"\nBIENVENIDO a STARCOMPANY AEROLINE";
                cout << "\n\n1- Iniciar sesion";
                cout << "\n\n2- Registrarse";
                cout << "\n\n3- salir";
                cout << "\n\nOpcion: ";
                cin >> opcion1;

                switch (opcion1)
                {

                case 1:

                        do
                        {
                            system("cls");
                            cout<<"\nBIENVENIDO a STARCOMPANY AEROLINE";
                            cout << "\n\n1- Usuario";
                            cout << "\n\n2- Admin";
                            cout << "\n\n3- salir";
                            cout << "\n\nOpcion: ";
                            cin >> opcionRol;
                        
                            switch (opcionRol)
                            {
                            case 1:
                                
                                cout << "\nIngrese su usuario: ";
                                cin >> lo.usuario;

                                cout << "\nIngrese su contra: ";
                                cin >> lo.contra;
                                
                            
                                if (lo.login(lo.usuario, lo.contra))
                                {
                            
                                    do
                                    {
                                        system("cls");
                                        cout<<"\nBIENVENIDO a STARCOMPANY AEROLINE "<< lo.USERNAME << lo.IDUSER;
                                        cout << "\n\n1- Comprar vuelo";
                                        cout << "\n\n2- Cargar ticket Vuelo";
                                        cout << "\n\n3- salir";
                                        cout << "\n\nOpcion: ";
                                        cin >> opcion2;

                                        switch (opcion2)
                                        {
                                        case 1:
                                            system("cls");
                                            ti.SeleccionarFechaSalida();
                                            system("cls");
                                            ti.SeleccionarFechaRetorno();
                                            system("cls");
                                            ti.SeleccionarOrigenVuelo();
                                            system("cls");
                                            ti.SeleccionarDestinoVuelo();
                                            system("cls");
                                            ti.SeleccionarPlanVuelo();
                                            system("cls");
                                            ti.agregarPasajeros();
                                            system("cls");

                                            if (ti.NombrePlanVuelo == "Basico")
                                            {
                                                cout << "En la recepcion se le asignara el asiento";
                                                ti.asientosAlmacenados = "Recepcion";
                                            }
                                            

                                            if (ti.NombrePlanVuelo == "Intermedio")
                                            {
                                                
                                                ti.cargarAsientosDesdeArchivoIntermedio();
                                                for (int i = 1; i <= numeroPasajeroAsiento; i++) {
                                                    bool asientoDisp = false;
                                                ti.mostrarAsientosIntermedio();
                                                    while (!asientoDisp) {
                                                        cout << "Ingrese la fila y columna del asiento a reservar para cliente " << i << " (ejemplo: g 2): ";
                                                        cin >> fila_char >> columna;

                                                        if (fila_char >= 'g' && fila_char < 'g' + FILAS) {
                                                            if (asientos[fila_char - 'g'][columna - 1] == 'O') {
                                                                ti.reservarAsientoIntermedio(fila_char, columna);
                                                                ti.asientosAlmacenados += fila_char + to_string(columna);
                                                                asientoDisp = true;
                                                            } else {
                                                                cout << "El asiento seleccionado no está disponible." << endl;
                                                                
                                                            }
                                                        } else {
                                                            cout << "Fila inválida." << endl;
                                                            
                                                        }
                                                    }
                                                }

                                            }


                                            if (ti.NombrePlanVuelo == "Premiun")
                                            {
                                                
                                                ti.cargarAsientosDesdeArchivoPremiun();
                                                for (int i = 1; i <= numeroPasajeroAsiento; i++) {
                                                    bool asientoDisp = false;
                                                ti.mostrarAsientosPremiun();
                                                    while (!asientoDisp) {
                                                        cout << "Ingrese la fila y columna del asiento a reservar para cliente " << i << " (ejemplo: m 2): ";
                                                        cin >> fila_char >> columna;

                                                        if (fila_char >= 'm' && fila_char < 'm' + FILAS) {
                                                            if (asientos[fila_char - 'm'][columna - 1] == 'O') {
                                                                ti.reservarAsientoPremiun(fila_char, columna);
                                                                ti.asientosAlmacenados += fila_char + to_string(columna);
                                                                asientoDisp = true;
                                                            } else {
                                                                cout << "El asiento seleccionado no está disponible." << endl;
                                                                
                                                            }
                                                        } else {
                                                            cout << "Fila inválida." << endl;
                                                            
                                                        }
                                                    }
                                                }

                                            }

                                            
                                            system("cls");
                                            ti.ImprimirTicket();

                                            cout << "\n\nDeseas Registrar el ticket? Ingresa y/n: ";
                                            cin >> decision;

                                                if (decision == "y" && ti.NombrePlanVuelo == "Intermedio")
                                                {
                                                    ti.agregarTicket(lo.IDUSER);
                                                    ti.guardarAsientosEnArchivoIntermedio();
                                                    cout << "El ticket ha sido registrado Correctamente I";
                                                }
                                                else if (decision == "y" && ti.NombrePlanVuelo == "Premiun"){
                                                    ti.agregarTicket(lo.IDUSER);
                                                    ti.guardarAsientosEnArchivoPremiun();
                                                    cout << "El ticket ha sido registrado Correctamente P";
                                                }
                                                else if (decision == "n"){
                                                    cout << "No se registro el ticket ";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                }
                                                else{
                                                    cout << "No existe esta opcion. ingrese y o n";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                }
                                            
                                            break;


                                        case 2:
                                            ti.cargarTicketUser(lo.IDUSER);
                                            cout << "\n\nDale click para volver al menu";
                                            click = getch();
                                            break;

                                        case 3:
                                            cout << "saliste";
                                                break;
   
                                        
                                        default:
                                            cout << "Esa opcion no existe";
                                            cout << "\n\nDale click para volver al menu";
                                            click = getch();
                                            break;
                                        }

                                        
                                    } while (opcion2 != 3);

                                }
                                

                                break;

                            case 2:
                               
                                cout << "\nIngrese su usuarioAdmin: ";
                                cin >> lo.usuarioAdmin;

                                cout << "\nIngrese su contraAdmin: ";
                                cin >> lo.contraAdmin;
                            
                                if (lo.usuarioAdmin == "admin" && lo.contraAdmin == "admin")
                                {
                                    
                                    do
                                    {
                                         system("cls");
                                        cout<<"\nBIENVENIDO a STARCOMPANY AEROLINE - ADMIN";
                                        cout << "\n\n1- Fecha de Salida";
                                        cout << "\n\n2- Fecha de retorno";
                                        cout << "\n\n3- Origen de los vuelos";
                                        cout << "\n\n4- Destinacion de los vuelos";
                                        cout << "\n\n5- Planes de vuelos";
                                        cout << "\n\n6- Asiento Plan basico";
                                        cout << "\n\n7- Asiento Plan Intermedio";
                                        cout << "\n\n8- Asiento Plan Premiun";
                                        cout << "\n\n9- Salir";
                                        cout << "\n\nOpcion: ";
                                        cin >> opcion2;

                                        switch (opcion2)
                                        {
                                        case 1:
                                                 system("cls");
                                                int opc1;
                                                cout << "\n\n1- Agregar";
                                                cout << "\n\n2- Cargar";
                                                cout << "\n\n3- Modificar";
                                                cout << "\n\n4- Eliminar";
                                                cout << "\n\n5- Salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc1;

                                                switch (opc1)
                                                {
                                                case 1:
                                                    ti.AgregarFechaSalida();
                                                    break;

                                                case 2:
                                                    ti.CargarFechaSalida();
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                ti.CargarFechaSalida();
                                                    int idUpdate;
                                                    cout << "Ingrese el id del registro que vas actualizar: ";
                                                    cin >> idUpdate;

                                                    ti.ActualizarFechaSalida(idUpdate);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();

                                                    break;

                                                case 4:
                                                ti.CargarFechaSalida();
                                                    int idEliminate;
                                                    cout << "Ingrese el id del registro que vas Eliminar: ";
                                                    cin >> idEliminate;

                                                    ti.EliminarFechaSalida(idEliminate);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break; 

                                                case 5:
                                                    cout << "saliste";
                                                    break;                 
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                            
                                            break;

                                        case 2:

                                                system("cls");
                                                int opc2;
                                                cout << "\n\n1- Agregar";
                                                cout << "\n\n2- Cargar";
                                                cout << "\n\n3- Modificar";
                                                cout << "\n\n4- Eliminar";
                                                cout << "\n\n5- Salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc2;

                                                switch (opc2)
                                                {
                                                case 1:
                                                    ti.AgregarFechaRetorno();
                                                    break;

                                                case 2:
                                                    ti.CargarFechaRetorno();
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                ti.CargarFechaRetorno();
                                                    int idUpdate2;
                                                    cout << "Ingrese el id del registro que vas actualizar: ";
                                                    cin >> idUpdate2;
                                                    
                                                    ti.ModificarFechaRetorno(idUpdate2);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 4:
                                                ti.CargarFechaRetorno();
                                                    int idEliminate2;
                                                    cout << "Ingrese el id del registro que vas Eliminar: ";
                                                    cin >> idEliminate2;

                                                    ti.EliminarFechaRetorno(idEliminate2);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;  

                                                case 5:
                                                    cout << "saliste";
                                                    break;                
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                            
                                            break;

                                        case 3:
                                                 system("cls");
                                                int opc3;
                                                cout << "\n\n1- Agregar";
                                                cout << "\n\n2- Cargar";
                                                cout << "\n\n3- Modificar";
                                                cout << "\n\n4- Eliminar";
                                                cout << "\n\n5- Salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc3;

                                                switch (opc3)
                                                {
                                                case 1:
                                                    ti.AgregarOrigenVuelo();
                                                    break;

                                                case 2:
                                                    ti.CargarOrigenVuelo();
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                ti.CargarOrigenVuelo();
                                                    int idUpdate3;
                                                    cout << "Ingrese el id del registro que vas actualizar: ";
                                                    cin >> idUpdate3;
                                                    ti.ModificarOrigenVuelo(idUpdate3);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 4:
                                                ti.CargarOrigenVuelo();
                                                    int idEliminate3;
                                                    cout << "Ingrese el id del registro que vas eliminar: ";
                                                    cin >> idEliminate3;
                                                    ti.EliminarOrigenVuelo(idEliminate3);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;   

                                                case 5:
                                                    cout << "saliste";
                                                    break;               
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                            
                                            break;

                                        case 4:

                                                 system("cls");
                                                int opc4;
                                                cout << "\n\n1- Agregar";
                                                cout << "\n\n2- Cargar";
                                                cout << "\n\n3- Modificar";
                                                cout << "\n\n4- Eliminar";
                                                cout << "\n\n5- Salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc4;

                                                switch (opc4)
                                                {
                                                case 1:
                                                    ti.AgregarDestinoVuelo();
                                                    break;

                                                case 2:
                                                    ti.CargarDestinoVuelo();
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                ti.CargarDestinoVuelo();
                                                    int idUpdate4;
                                                    cout << "Ingrese el id del registro que vas actualizar: ";
                                                    cin >> idUpdate4;
                                                    ti.ModificarDestinoVuelo(idUpdate4);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 4:
                                                ti.CargarDestinoVuelo();
                                                    int idEliminate4;
                                                    cout << "Ingrese el id del registro que vas eliminar: ";
                                                    cin >> idEliminate4;
                                                    ti.EliminarDestinoVuelo(idEliminate4);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 5:
                                                    cout << "saliste";
                                                    break;                  
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                            
                                            break;

                                        case 5:
                                                 system("cls");
                                                int opc5;
                                                cout << "\n\n1- Agregar";
                                                cout << "\n\n2- Cargar";
                                                cout << "\n\n3- Modificar";
                                                cout << "\n\n4- Eliminar";
                                                cout << "\n\n5- Salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc5;

                                                switch (opc5)
                                                {
                                                case 1:
                                                    ti.AgregarPlanVuelo();
                                                    break;

                                                case 2:
                                                    ti.CargarPlanVuelo();
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                    char PaisUpdate5[100];
                                                    cout << "Ingrese el Pais del Plan de vuelo que vas actualizar: ";
                                                    cin >> PaisUpdate5;
                                                    ti.ModificarPlanVuelo(PaisUpdate5);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 4:
                                                    char PaisEliminate5[100];
                                                    cout << "Ingrese el Pais del Plan de vuelo que vas eliminar: ";
                                                    cin >> PaisEliminate5;
                                                    ti.EliminarPlanVuelo(PaisEliminate5);
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 5:
                                                    cout << "saliste";
                                                    break;                  
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                            
                                            break;

                                        case 6:
                                                system("cls");
                                                int opc6;
                                                cout << "\n\n1- Asignar asiento B";
                                                cout << "\n\n2- Reestablecer asiento en especifico B";
                                                cout << "\n\n3- Reestablecer asientos B";
                                                cout << "\n\n4- salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc6;

                                                

                                                switch (opc6)
                                                {
                                                case 1:

                                                    int IDMOD;
                                                    int IDUS;

                                                    cout << "Ingrese el id del usuario que va a asignar los asientos";
                                                    cin >> IDUS;
                                                    ti.cargarTicketUser(IDUS);
                                                    
                                                    cout << "Ingrese el id del ticket que va a asignar los asientos";
                                                    cin >> IDMOD;

                                                    ti.modificarAsientosPendientesPorIDBasico(IDMOD);
                                                 
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 2:
                                                    char filaMod;
                                                    int columnaMod;

                                                    ti.cargarAsientosDesdeArchivoBasicos();
                                                    ti.mostrarAsientosBasico();
                                                    cout << "Ingrese la fila y columna del asiento a reservar para cliente (ejemplo: a 2): ";
                                                    cin >> filaMod >> columnaMod;
                                                        
                                                    ti.modificarAsientoBasico(filaMod,columnaMod,'O');

                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                    ti.inicializarAsientos();
                                                    ti.guardarAsientosEnArchivoBasicos();
                                                  
                                                    break;

                                                case 4:
                                                    cout << "saliste";
                                                    break;            
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    break;
                                                }
                                                    
                                                
                                                
                                            
                                            break;

                                        case 7:

                                                system("cls");
                                                int opc7;
                                                cout << "\n\n1- Asignar asiento I";
                                                cout << "\n\n2- Reestablecer asiento en especifico I";
                                                cout << "\n\n3- Reestablecer asientos I";
                                                cout << "\n\n4- salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc7;

                                                

                                                switch (opc7)
                                                {
                                                case 1:

                                                    int IDMOD;
                                                    int IDUS;

                                                    cout << "Ingrese el id del usuario que va a asignar los asientos";
                                                    cin >> IDUS;
                                                    ti.cargarTicketUser(IDUS);
                                                    
                                                    cout << "Ingrese el id del ticket que va a asignar los asientos";
                                                    cin >> IDMOD;

                                                    ti.modificarAsientosPendientesPorIDIntermedio(IDMOD);

                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                 

                                                    break;

                                                case 2:
                                                    char filaMod;
                                                    int columnaMod;

                                                    ti.cargarAsientosDesdeArchivoIntermedio();
                                                    ti.mostrarAsientosIntermedio();
                                                    cout << "Ingrese la fila y columna del asiento a reservar para cliente (ejemplo: a 2): ";
                                                    cin >> filaMod >> columnaMod;
                                                        
                                                    ti.modificarAsientoIntermedio(filaMod,columnaMod,'O');

                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                    ti.inicializarAsientos();
                                                    ti.guardarAsientosEnArchivoIntermedio();
                                                  
                                                    break;

                                                case 4:
                                                    cout << "saliste";
                                                    break;            
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                                    
                                                
                                            
                                            break;

                                        case 8:

                                                system("cls");
                                                int opc8;
                                                cout << "\n\n1- Asignar asiento P";
                                                cout << "\n\n2- Reestablecer asiento en especifico P";
                                                cout << "\n\n3- Reestablecer asientos P";
                                                cout << "\n\n4- salir";
                                                cout << "\n\nOpcion: ";
                                                cin >> opc8;

                                                

                                                switch (opc8)
                                                {
                                                case 1:

                                                    int IDMOD;
                                                    int IDUS;

                                                    cout << "Ingrese el id del usuario que va a asignar los asientos";
                                                    cin >> IDUS;
                                                    ti.cargarTicketUser(IDUS);
                                                    
                                                    cout << "Ingrese el id del ticket que va a asignar los asientos";
                                                    cin >> IDMOD;

                                                    ti.modificarAsientosPendientesPorIDPremiun(IDMOD);
                                                 
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();

                                                    break;

                                                case 2:
                                                    char filaMod;
                                                    int columnaMod;

                                                    ti.cargarAsientosDesdeArchivoPremiun();
                                                    ti.mostrarAsientosPremiun();
                                                    cout << "Ingrese la fila y columna del asiento a reservar para cliente (ejemplo: a 2): ";
                                                    cin >> filaMod >> columnaMod;
                                                        
                                                    ti.modificarAsientoPremiun(filaMod,columnaMod,'O');

                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;

                                                case 3:
                                                    ti.inicializarAsientos();
                                                    ti.guardarAsientosEnArchivoPremiun();
                                                  
                                                    break;

                                                case 4:
                                                    cout << "saliste";
                                                    break;            
                                                
                                                default:
                                                    cout << "Esa opcion no existe";
                                                    cout << "\n\nDale click para volver al menu";
                                                    click = getch();
                                                    break;
                                                }
                                                                                                

                                            
                                            break;

                                        case 9:
                                            cout << "saliste";
                                            break;
                                        
                                        default:
                                            cout << "Esa opcion no existe";
                                            cout << "\n\nDale click para volver al menu";
                                            click = getch();
                                            break;
                                        }

                                        
                                    } while (opcion2 != 9);

                                }

                                break;    
                            
                            default:
                                cout << "Esa opcion no existe";
                                cout << "\n\nDale click para volver al menu";
                                click = getch();
                                break;
                            }     


                        } while (opcionRol != 3);

                        break;

                case 2:
                    lo.Registrar();
                    break;

                case 3:
                    cout << "Saliendo....";
                    break;    
                
                default:
                    cout << "Esa opcion no existe";
                    cout << "\n\nDale click para volver al menu";
                    click = getch();
                    break;
                }

            } while (opcion1 != 3);
    
        

       
    return 0;
}



