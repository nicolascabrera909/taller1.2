#include "archivo.h"


// Determina si existe o no un archivo con el nombre recibido por parámetro
boolean existeArchivo(string nomArch)
{
    boolean resu=FALSE;
    FILE * f=fopen(nomArch, "rb");
    if(f!=NULL)
        resu=TRUE;
    fclose(f);
    return resu;
}

