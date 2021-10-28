#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
using namespace std;

/*ESTRUCTURAS*/
struct incidente
{
    int codInciden;
    char fecHora[19];
    int i_DniAseg;
    char i_DniOtro[10];
    int i_NumPoliza;
    string calle;
    char altura[5];
};

struct polizaAsegurado
{
    int nroPoliza;
    int dni;
    char nombre[20];
    char apellido[20];
    char cuota;
    char patente[8];
    char activa;
    int cantIncidentes = 0;
};

/*FUNCIONES*/

int CargarPoliza(char ruta[], int opcion)
{
    FILE *f;
    polizaAsegurado p;
    int n;
    if (opcion == 0)
    {
        f = fopen (ruta,"wb");
        if(!f)
        {
            cout << "No se pudo crear el archivo" << endl;
            return 1;
        }
        cout << "\nIngrese la cantidad de polizas en el nuevo archivo:" << endl;
    }
    else
    {
        f = fopen (ruta,"ab");
        if(!f)
        {
            cout << "No se encontro el archivo" << endl;
            return 1;
        }
        cout << "\nIngrese la cantidad de polizas:" << endl;
    }
    cin >> n;
    for (int j = 1; j <= n ; j++)
    {
        cout << endl;
        cout << "Ingrese numero de poliza:" << endl;
        cin >> p.nroPoliza;
        cout << "Ingrese DNI:" << endl;
        cin >> p.dni;
        cout << "Ingrese nombre:" << endl;
        cin >> p.nombre;
        cout << "Ingrese apellido:" << endl;
        cin >> p.apellido;
        cout << "Ingrese el estado de la cuota (V si esta al dia/ F si no lo esta):" << endl;
        cin >> p.cuota;
        cout << "Ingrese patente:" << endl;
        cin >> p.patente;
        cout << "Ingrese estado de actividad (V si esta activa/ F si no lo esta) :" << endl;
        cin >> p.activa;
        cout << "Ingrese cantidad de incidentes:" << endl;
        cin >> p.cantIncidentes;
        fwrite(&p, sizeof(polizaAsegurado),1, f);
    }
    fclose(f);
    return 0;
}

int MostPoliza(char ruta[])
{
    FILE *f;
    polizaAsegurado p;

    if (f = fopen(ruta,"rb"))
    {
        fread(&p,sizeof(polizaAsegurado),1,f);
        for (int i = 1; !feof(f) ; i++)
        {
            cout << "\n---------- REGISTRO NRO :" << i << " ----------" << endl;
            cout << "Numero de poliza: " << p.nroPoliza << endl;
            cout << "DNI: " << p.dni << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Apellido: " << p.apellido << endl;
            cout << "Cuota al dia: " << p.cuota << endl;
            cout << "Patente: " << p.patente << endl;
            cout << "Estado de Poliza: " << p.activa << endl;
            cout << "Cantidad de incidentes: " << p.cantIncidentes << endl;
            fread(&p,sizeof(polizaAsegurado),1,f);
        }
        cout << endl;
        fclose(f);
        return 0;
    }
    else
        return 1;
}

int DesPoliza(char ruta[])
{
    FILE *f;
    int presencia = 0;
    polizaAsegurado p;
    int num;

    cout << "\nNro de poliza que desea desactivar:" << endl;
    cin >> num;
    cout << endl;
    if (f = fopen(ruta,"rb+"))
    {
        fread(&p,sizeof(polizaAsegurado),1,f);
        while(!feof(f) && presencia == 0)
        {
            if (num == p.nroPoliza)
            {
                presencia = 1;
                p.activa = 'F';
                fseek(f,(-1)*sizeof(polizaAsegurado), SEEK_CUR);
                fwrite(&p,sizeof(polizaAsegurado),1,f);
                fseek(f,sizeof(polizaAsegurado), SEEK_CUR);
                cout << "\n---------Poliza desactivada---------\n" << endl;
            }
            fread(&p,sizeof(polizaAsegurado),1,f);
        }

        if (presencia == 0)
            cout << "No se encontro la poliza ingresada." << endl;
        fclose(f);
        return 0;
    }
    else
        return 1;

}

int BuscarPorDni(char ruta[])
{
    FILE *f;
    polizaAsegurado p;
    int dni, presencia = 0;

    cout << "\nIngrese DNI:" << endl;
    cin >> dni;
    cout << endl;

    if (f = fopen(ruta,"rb"))
    {
        fread(&p,sizeof(struct polizaAsegurado),1,f);
        while (!feof(f))
        {
            if (dni == p.dni)
            {
                cout << "Numero de poliza: " << p.nroPoliza << endl;
                cout << "Nombre: " << p.nombre << endl;
                cout << "Apellido: " << p.apellido << endl;
                cout << "Cuota al dia: " << p.cuota << endl;
                cout << "Patente: " << p.patente << endl;
                cout << "Estado de Poliza: " << p.activa << endl;
                cout << "Cantidad de incidentes: " << p.cantIncidentes << endl;
                cout << endl;
                presencia = 1;
            }
            fread(&p,sizeof(struct polizaAsegurado),1,f);
        }
        if (presencia != 1)
            cout << "El DNI " << dni << " no posee poliza" << endl;
        fclose(f);
        cout << endl;
        return 0;
    }
    else
        return 1;
}

int BuscarPoliza (char ruta[])
{
    FILE *f;
    polizaAsegurado p;
    int nro, presencia;

    cout << "\nIngrese nro de poliza:" << endl;
    cin >> nro;

    if (f = fopen(ruta,"rb"))
    {
        fread(&p,sizeof(struct polizaAsegurado),1,f);
        while(!feof(f) && presencia == 0)
        {
            if (nro == p.nroPoliza)
            {
                cout << "DNI: " << p.dni << endl;
                cout << "Nombre: " << p.nombre << endl;
                cout << "Apellido: " << p.apellido << endl;
                cout << "Cuota al dia: " << p.cuota << endl;
                cout << "Patente: " << p.patente << endl;
                cout << "Estado de Poliza: " << p.activa << endl;
                cout << "Cantidad de incidentes: " << p.cantIncidentes << endl;
                presencia = 1;
            }
            fread(&p,sizeof(struct polizaAsegurado),1,f);
        }
        if (presencia != 1)
            cout << "No se ha encontrado el nro de poliza " << nro << endl;
        fclose(f);
        cout << endl;
        return 0;
    }
    else
        return 1;
}

int CargarLoteInc(char ruta[], int opcion)
{
    FILE *f;
    incidente i;
    int n;
    if (opcion == 0)
    {
        f = fopen(ruta,"wb");
        if(!f)
        {
            cout << "No se pudo crear el archivo" << endl;
            return 1;
        }
        cout << "\nIngrese la cantidad de incidentes en el nuevo archivo:" << endl;
    }
    else
    {
        f = fopen(ruta,"ab");
        if(!f)
        {
            cout << "No se encontro el archivo" << endl;
            return 1;
        }
        cout << "\nIngrese la cantidad de incidentes: " << endl;
    }
    cin >> n;
    for (int j = 1; j <= n ; j++)
    {
        cout << endl;
        cout << "Ingrese codigo de incidente:" << endl;
        cin >> i.codInciden;
        cout << "Ingrese fecha/hora de incidente en formato AAAAMMDDHH:MM:" << endl;
        cin >> i.fecHora;
        cout << "Ingrese DNI del asegurado:" << endl;
        cin >> i.i_DniAseg;
        cout << "Ingrese DNI del otro conductor:" << endl;
        cin >> i.i_DniOtro;
        cout << "Ingrese numero de poliza:" << endl;
        cin >> i.i_NumPoliza;
        cout << "Ingrese calle:" << endl;
        cin >> i.calle;
        cout << "Ingrese altura:" << endl;
        cin >> i.altura;
        cout << endl;
        fwrite(&i, sizeof(incidente), 1, f);
    }
    fclose(f);
    return 0;
}

int MostInc(char ruta[])
{
    FILE *f;
    incidente p;

    if (f = fopen(ruta,"rb"))
    {
        fread(&p,sizeof(incidente),1,f);
        for (int i = 1; !feof(f) ; i++)
        {
            cout << "\n---------- REGISTRO NRO :" << i << " ----------" << endl;
            cout << "Codigo de incidente: " << p.codInciden << endl;
            cout << "Fecha y hora: " << p.fecHora << endl;
            cout << "DNI del asegurado: " << p.i_DniAseg << endl;
            cout << "DNI del otro conductor: " << p.i_DniOtro << endl;
            cout << "Numero de poliza: " << p.i_NumPoliza << endl;
            cout << "Calle: " << p.calle << endl;
            cout << "Altura: " << p.altura << endl;
            fread(&p,sizeof(incidente),1,f);
        }
        cout << endl;
        fclose(f);
        return 0;
    }
    else
        return 1;
}

int ActArch (char ruta1[], char ruta2[])
{
    FILE *f, *r, *s;
    polizaAsegurado p;
    incidente i;

    f = fopen(ruta1,"rb");
    if (!f)
        return 1;

    s = fopen(ruta2,"rb");
    if (!s)
        return 1;

    r = fopen("auxiliar.bak","wb");
    if (!r)
        return 1;

    fread(&p,sizeof(polizaAsegurado),1,f);
    fread(&i,sizeof(incidente),1,s);
    while (!feof(f))
    {
        if (p.activa == 'V')
        {
            while (!feof(s))
            {
                if (i.i_NumPoliza == p.nroPoliza)
                {
                    p.cantIncidentes++;
                }
                fread(&i,sizeof(incidente),1,s);
            }
            fseek(s,0,SEEK_SET);
            fwrite(&p,sizeof(polizaAsegurado),1,r);
        }
        fread(&p,sizeof(polizaAsegurado),1,f);
        fread(&i,sizeof(incidente),1,s);
    }

    fclose(f);
    fclose(s);
    fclose(r);
    remove ("asegurados.bak");
    rename ("auxiliar.bak", "asegurados.bak");
    cout << "\n---------Actualizacion realizada---------\n" << endl;
    return 0;
}

bool compararPol(int poliza, int polizaVec[],int tam)
{
    bool estado = false;
    for(int i = 0; i < tam; i++)
    {
        if(polizaVec[i] == poliza)
        {
            estado = true;
        }
    }
    return estado;
}

int OrdDes (char ruta1[])
{
    FILE *f;
    polizaAsegurado p;
    int cantPol = 0;

    f = fopen(ruta1,"rb");
    fread(&p,sizeof(polizaAsegurado),1,f);
    while(!feof(f))
    {
        if (p.activa == 'V')
        {
            cantPol++;
        }
        fread(&p,sizeof(polizaAsegurado),1,f);
    }
    fclose(f);

    int dim = cantPol;
    int contenedor[dim];
    int momentocap = 0;
    int i = 0;
    int a;
    int b;
    int aux;
    int npol= 0;
    char momentobool;

    if(f=fopen(ruta1,"rb"))
    {
        fread(&p,sizeof(polizaAsegurado),1,f);
        while(!feof(f))
        {
            momentobool = p.activa;
            momentocap = p.cantIncidentes;
            if (momentobool == 'V')
            {
                contenedor[i] = momentocap;
                i = i+1;
            }
            fread(&p,sizeof(polizaAsegurado),1,f);
        }
        fclose(f);

        for (a=0; a < cantPol ; a++)
        {
            for (b =0 ; b < cantPol -1; b++)
            {
                if(contenedor[b] < contenedor[b + 1])
                {
                    aux = contenedor[b];
                    contenedor[b] = contenedor[b+1];
                    contenedor[b+1] = aux;
                }
            }
        }

        int pol_leida[cantPol];
        i = 0;

        for (int pe = 0; pe < cantPol ; pe++)
        {
            if (f=fopen(ruta1,"rb"))
            {
                fread(&p,sizeof(polizaAsegurado),1,f);
                while(!feof(f))
                {
                    if (contenedor[npol] == p.cantIncidentes && compararPol(p.nroPoliza,pol_leida,cantPol) == false)
                    {
                        cout << endl;
                        cout << "Numero de poliza: " << p.nroPoliza << endl;
                        cout << "DNI: " << p.dni << endl;
                        cout << "Nombre: " << p.nombre << endl;
                        cout << "Apellido: " << p.apellido << endl;
                        cout << "Cuota al dia: " << p.cuota << endl;
                        cout << "Patente: " << p.patente << endl;
                        cout << "Estado de Poliza: " << p.activa << endl;
                        cout << "Cantidad de incidentes: " << p.cantIncidentes << endl;
                        pol_leida[i] = p.nroPoliza;
                        i++;
                    }
                    fread(&p,sizeof(struct polizaAsegurado),1,f);
                }
                fclose(f);
            }
            npol++;
        }
        return 1;
    }
    return 0;
}

int CantInc (int nro,char ruta2[])
{
    incidente c;
    char anio[5];
    int cont = 0;
    FILE *f;
    f = fopen(ruta2,"rb");

    fread(&c,sizeof(incidente),1,f);
    for(int i=0; i<4; i++)
    {
        anio[i] = c.fecHora[i];
    }
    while (!feof(f))
    {
        if (c.i_NumPoliza == nro && strcmp(anio,"2020") == 0)
        {
            cont++;
        }
        fread(&c,sizeof(incidente),1,f);
        for(int i=0; i<4; i++)
        {
            anio[i] = c.fecHora[i];
        }
    }
    fclose(f);
    return cont;
}

void escribirReporteHTML(int nro, char ruta1[])
{
    FILE *f, *s;
    polizaAsegurado p;
    s = fopen(ruta1,"rb");
    f = fopen("salidahtml.html", "wt");
    fprintf(f,"<html><body>\n");
    fprintf(f,"<h1>Poliza de asegurados</h1>\n");
    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Poliza</th><th>DNI</th><th>Nombres</th><th>Apellidos</th><th>Cuota</th><th>Patente</th><th>Estado</th><th>Cantidad de incidentes</th>\n");
    fread(&p,sizeof(polizaAsegurado),1,s);
    while (!feof(s))
    {
        if (nro == p.nroPoliza)
        {
            fprintf(f,"<tr>\n");
            fprintf(f,"<td>%d</td><td>%d</td><td>%s</td><td>%s</td><td>%c</td><td>%s</td><td>%c</td><td>%d</td>\n",p.nroPoliza,p.dni,p.apellido,p.nombre,p.cuota,p.patente,p.activa,p.cantIncidentes);
            fprintf(f,"</tr>\n");
        }
        fread(&p,sizeof(polizaAsegurado),1,s);
    }

    fprintf(f, "</table>");
    fprintf(f, "</body>");
    fprintf(f, "</html>");
    fclose(f);
    fclose(s);
    return;
}

void escribirReporteCSV(int nro, char ruta1[])
{
    FILE *f, *s;
    polizaAsegurado p;
    s = fopen(ruta1,"rb");
    f = fopen("salidaexcel.csv", "wt");
    fprintf(f,"Poliza;DNI;Apellidos;Nombres;Cuota;Patente;Estado;Cantidad de incidentes\n");
    fread(&p,sizeof(polizaAsegurado),1,s);
    while (!feof(s))
    {
        if (nro == p.nroPoliza)
        {
            fprintf(f,"%d;%d;%s;%s;%c;%s;%c;%d\n",p.nroPoliza,p.dni,p.apellido,p.nombre,p.cuota,p.patente,p.activa,p.cantIncidentes);
        }
        fread(&p,sizeof(polizaAsegurado),1,s);
    }
    fclose(f);
    fclose(s);
    return;
}

void Reporte (char ruta1[], char ruta2[], int cod)
{
    incidente c;
    char anio[5];

    FILE *f;
    f = fopen(ruta1,"rb");
    fseek(f,0,SEEK_END);
    int numpoli = ftell(f)/sizeof(polizaAsegurado);
    fclose(f);

    int pol_may5[numpoli];
    int contarr = 0;
    bool estado = false;

    f = fopen(ruta2,"rb");
    fread(&c,sizeof(incidente),1,f);
    for(int i=0; i<4; i++)
    {
        anio[i] = c.fecHora[i];
    }
    while(!feof(f))
    {
        if (strcmp(anio,"2020") == 0)
        {
            if (CantInc(c.i_NumPoliza,ruta2) > 5)
            {
                estado = compararPol(c.i_NumPoliza,pol_may5, contarr);
                if(estado == false)
                {
                    pol_may5[contarr] = c.i_NumPoliza;
                    contarr++;
                    if (cod == 0)
                    {
                        escribirReporteHTML(c.i_NumPoliza,ruta1);
                        cout << "\nReporte HTML realizado\n" << endl;
                    }
                    else
                    {
                        escribirReporteCSV(c.i_NumPoliza,ruta1);
                        cout << "\nReporte CSV realizado\n" << endl;
                    }
                }
            }
        }
        fread(&c,sizeof(incidente),1,f);
        for(int i=0; i<4; i++)
        {
            anio[i] = c.fecHora[i];
        }
        estado = false;
    }

    fclose(f);
    return;
}

/*MENU*/
int main()
{
    char opcion;
    char ruta1[] = "asegurados.bak", ruta2[] = "procesados.bak";
    do
    {
        cout << "---------- MENU ----------" << endl;
        cout << "Seleccione una opcion:" << endl;
        cout << "1 - Crear el archivo Asegurados.bak y cargarle polizas" << endl;
        cout << "2 - Cargar nuevas polizas" << endl;
        cout << "3 - Desactivar poliza" << endl;
        cout << "4 - Buscar una poliza" << endl;
        cout << "5 - Crear el archivo Procesados.bak y cargarle lote de incidentes" << endl;
        cout << "6 - Cargar nuevo lote de incidentes" << endl;
        cout << "7 - Ordenar polizas activas por saldo descendente" << endl;
        cout << "8 - Polizas con mas de 5 incidentes en 2020" << endl;
        cout << "9 - Actualizar archivo Asegurados.bak" << endl;
        cout << "0 - Mostrar archivos" << endl;
        cout << "Esc - Salir" << endl;

        do
        {
            opcion = getch();
        }
        while(opcion!= '0' && opcion!= '1' && opcion!= '2' && opcion!='3' && opcion!='4' && opcion!='5' && opcion!='6' && opcion!='7' && opcion!='8' && opcion!='9' && opcion!= 27);
        switch (opcion)
        {
        case '0':
            cout << endl;
            cout << "\ta) Mostrar archivo Asegurados.bak" <<endl;
            cout << "\tb) Mostrar archivo Procesados.bak" <<endl;
            cout << "\tc) Volver al menu principal" << endl;

            do
            {
                opcion = getch();
            }
            while (!(opcion >= 'a' && opcion <= 'c') && !(opcion >= 'A' && opcion <= 'C'));
            switch (opcion)
            {
            case 'a' :
            case 'A' :
                MostPoliza(ruta1);
                break;
            case 'b':
            case 'B':
                MostInc(ruta2);
                break;
            case 'c':
            case 'C':
                cout << endl;
                break;
            }
            break;
        case '1':
            CargarPoliza(ruta1,0);
            break;
        case '2':
            CargarPoliza(ruta1,1);
            break;
        case '3':
            DesPoliza(ruta1);
            break;
        case '4':
            cout << endl;
            cout << "\ta) Buscar por DNI" <<endl;
            cout << "\tb) Buscar por numero de poliza" <<endl;
            cout << "\tc) Volver al menu principal" << endl;
            do
            {
                opcion = getch();
            }
            while (!(opcion >= 'a' && opcion <= 'c') && !(opcion >= 'A' && opcion <= 'C'));
            switch (opcion)
            {
            case 'a' :
            case 'A' :
                BuscarPorDni(ruta1);
                break;
            case 'b':
            case 'B':
                BuscarPoliza(ruta1);
                break;
            case 'c':
            case 'C':
                cout << endl;
                break;
            }
            break;
        case '5':
            CargarLoteInc(ruta2,0);
            break;
        case '6':
            CargarLoteInc(ruta2,1);
            break;
        case '7':
            OrdDes(ruta1);
            break;
        case '8':
            cout << endl;
            cout << "\ta) Hacer un reporte en formato HTML" <<endl;
            cout << "\tb) Hacer un reporte en formato CSV" <<endl;
            cout << "\tc) Volver al menu principal" << endl;
            do
            {
                opcion = getch();
            }
            while (!(opcion >= 'a' && opcion <= 'c') && !(opcion >= 'A' && opcion <= 'C'));
            switch (opcion)
            {
            case 'a' :
            case 'A' :
                Reporte(ruta1,ruta2,0);
                break;
            case 'b':
            case 'B':
                Reporte(ruta1,ruta2,1);
            case 'c':
            case 'C':
                cout << endl;
                break;
            }
            break;
        case '9':
            ActArch(ruta1,ruta2);
            break;
        }
    }
    while(opcion!=27);
    return 0;
}
