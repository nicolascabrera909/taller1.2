#include "archivo.h"
#include "listaString.h"
#include "listaExpre.h"

const char E = 'e';

int main()
{
    boolean salir = FALSE;
    string str;
    strCrear(str);
    listaString lis;
    crearListaString(lis);
    listaExpre lexpre;
    crearListaExpre(lexpre);

    do
    {
        printf("\nIngrese comando: ");
        cargarString(str);
        if(!stringVacio(str))
        {
            partirString(str, lis);
            string comando = obtenerStringPos(lis,0);
            if (comparoString(comando, "create"))
            {
                //declaro variables
                arbolExpre arb;
                crearArbol(arb);
                tipoExpresion tipoExpre;
                expresionR expR;
                identificador id;

                if (contarNodos(lis) != 2)
                    printf("Se esperaba un parametro luego del comando\n");
                else
                {
                    int contador=0;
                    if (esVariable(obtenerStringPos(lis,1)))
                        contador++;
                    if (esNumero(obtenerStringPos(lis,1)))
                        contador++;
                    if(contador!=1)
                        printf("Se esperaba una x o un numero entero\n");
                    else
                    {
                        crearIdent(E,(maxId(lexpre)+1),id);
                        str = obtenerStringPos(lis,1);
                        if(esVariable(str))
                        {
                            crearTipoExpresionVariable('x',tipoExpre);
                            cargarArbolAtomico(arb,tipoExpre);
                            cargarExpresionR(id,arb,expR);
                            guardarExpreAlFinal(expR,lexpre);
                            mostrarExpresionR(expR,TRUE);
                            printf("\n");
                            limpiarListaString(lis);
                        }
                        else
                        {
                            if (strlar(str) > 10)
                                printf ("Error: numero demasiado largo\n");
                            else if (!esNumero(str))
                                printf ("Error: se esperaba un numero mayor que cero");
                            else
                            {
                                int conversion = convertirString(str);
                                crearTipoExpresionNumero(conversion,tipoExpre);
                                cargarArbolAtomico(arb,tipoExpre);
                                cargarExpresionR(id,arb,expR);
                                guardarExpreAlFinal(expR,lexpre);
                                mostrarExpresionR(expR,TRUE);
                                printf("\n");
                                limpiarListaString(lis);
                            }
                        }
                    }
                }
                limpiarListaString(lis);
            }
            else if (comparoString(comando, "sum"))
            {
                //declaro variables
                arbolExpre arb;
                crearArbol(arb);
                tipoExpresion tipoExpre;
                expresionR expR, expR2;
                identificador id,id2;
                if (contarNodos(lis) != 3)
                    printf("Se esperaban dos parametros\n");
                else
                {
                    if(esVacia(lexpre))
                        printf("No existen expresiones creadas\n");
                    else
                    {
                        if(!esNumero(cortoNumeroDeExpresion(obtenerStringPos(lis,1))))
                            printf("Error: La primera expresion no existe en la lista de expresiones\n");
                        else
                        {
                            if(!esNumero(cortoNumeroDeExpresion(obtenerStringPos(lis,2))))
                                printf("Error: La segunda expresion no existe en la lista de expresiones\n");
                            else
                            {
                                crearIdent(obtenerStringPos(lis,1)[0],convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,1))),id);
                                crearIdent(obtenerStringPos(lis,2)[0],convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,2))),id2);
                                int bandera=0;
                                if(existeIdent(id,lexpre))
                                    bandera=bandera+1;
                                if(existeIdent(id2,lexpre))
                                    bandera=bandera+2;
                                switch(bandera)
                                {
                                case 0:
                                    printf("Error: las expresiones no existen\n");
                                    break;
                                case 1:
                                    printf("Error: la segunda expresion no existe\n");
                                    break;
                                case 2:
                                    printf("Error: la primera expresion no existe\n");
                                    break;
                                }
                                if(bandera==3)
                                {
                                    obtenerExpresionRDeLista(id,lexpre,expR);
                                    obtenerExpresionRDeLista(id2,lexpre,expR2);
                                    crearTipoExpresionOperador('+',tipoExpre);
                                    arbolExpre newArbol1, newArbol2;
                                    crearArbol(newArbol1);
                                    crearArbol(newArbol2);
                                    copiarTodosLosNodos(obtenerArbol(expR),newArbol1);
                                    copiarTodosLosNodos(obtenerArbol(expR2),newArbol2);
                                    cargarArbolNoAtomico(arb,tipoExpre,newArbol1,newArbol2);
                                    //creo la expre resultante, el nuevo identificador, la expresion y lo  agregoa la lista
                                    identificador id3;
                                    crearIdent(E,(maxId(lexpre)+1),id3);
                                    tipoExpresion parIzq, parDer;
                                    crearTipoExpresionParentesis('(',parIzq);
                                    crearTipoExpresionParentesis(')',parDer);
                                    cargarParentesis(arb, parIzq, parDer);
                                    expresionR expSuma;
                                    cargarExpresionR (id3, arb, expSuma);
                                    guardarExpreAlFinal(expSuma,lexpre);
                                    mostrarExpresionR(expSuma,TRUE);
                                    printf("\n");
                                }
                            }
                        }
                    }
                }
                limpiarListaString(lis);
            }
            else if (comparoString(comando, "product"))
            {
                //declaro variables
                arbolExpre arb;
                crearArbol(arb);
                tipoExpresion tipoExpre;
                expresionR expR, expR2;
                identificador id,id2;
                if (contarNodos(lis) != 3)
                    printf("Se esperaban dos parametros\n");
                else
                {
                    if(esVacia(lexpre))
                        printf("No existen expresiones creadas\n");
                    else
                    {
                        if(!esNumero(cortoNumeroDeExpresion(obtenerStringPos(lis,1))))
                            printf("Error: la primera expresion no es correcta\n");
                        else
                        {
                            if(!esNumero(cortoNumeroDeExpresion(obtenerStringPos(lis,2))))
                                printf("Error: la segunda expresion no es correcta\n");
                            else
                            {
                                crearIdent(obtenerStringPos(lis,1)[0],convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,1))),id);
                                crearIdent(obtenerStringPos(lis,2)[0],convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,2))),id2);
                                int bandera=0;
                                if(existeIdent(id,lexpre))
                                    bandera=bandera+1;
                                if(existeIdent(id2,lexpre))
                                    bandera=bandera+2;
                                switch(bandera)
                                {
                                case 0:
                                    printf("Error: las expresiones no existen\n");
                                    break;
                                case 1:
                                    printf("Error: la segunda expresion no existe\n");
                                    break;
                                case 2:
                                    printf("Error: la primera expresion no existe\n");
                                    break;
                                }
                                if(bandera==3)
                                {
                                    obtenerExpresionRDeLista(id,lexpre,expR);
                                    obtenerExpresionRDeLista(id2,lexpre,expR2);
                                    crearTipoExpresionOperador('*',tipoExpre);
                                    arbolExpre newArbol1, newArbol2;
                                    crearArbol(newArbol1);
                                    crearArbol(newArbol2);
                                    copiarTodosLosNodos(obtenerArbol(expR),newArbol1);
                                    copiarTodosLosNodos(obtenerArbol(expR2),newArbol2);
                                    cargarArbolNoAtomico(arb,tipoExpre,newArbol1,newArbol2);
                                    //creo la expre resultante, el nuevo identificador, la expresion y lo  agregoa la lista
                                    identificador id3;
                                    crearIdent(E,(maxId(lexpre)+1),id3);
                                    tipoExpresion parIzq, parDer;
                                    crearTipoExpresionParentesis('(',parIzq);
                                    crearTipoExpresionParentesis(')',parDer);
                                    cargarParentesis(arb, parIzq, parDer);
                                    expresionR expSuma;
                                    cargarExpresionR (id3, arb, expSuma);
                                    guardarExpreAlFinal(expSuma,lexpre);
                                    mostrarExpresionR(expSuma,TRUE);
                                    printf("\n");
                                    limpiarListaString(lis);
                                }

                            }
                        }

                    }
                }
            }
            else if (comparoString(comando, "equals"))
            {
                //declaro variables
                expresionR expR, expR2;
                identificador idaux1, idaux2;
                arbolExpre arbaux1,arbaux2;
                crearArbol(arbaux1);
                crearArbol(arbaux2);

                if (contarNodos(lis) != 3)
                    printf("Error: Se esperaban dos parametros\n");
                else
                {
                    if(esVacia(lexpre))
                        printf("No existen expresiones creadas\n");
                    else
                    {
                        int numExp1 = convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,1)));
                        crearIdent(E,numExp1,idaux1);
                        int numExp2 = convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,2)));
                        crearIdent(E,numExp2,idaux2);
                        if (!existeIdent(idaux1, lexpre))
                            printf("Error: El primer parametro no existe en la lista de expresiones\n");
                        else
                        {
                            if (!existeIdent(idaux2, lexpre))
                                printf("Error: El segundo parametro no existe en la lista de expresiones\n");
                            else
                            {
                                obtenerExpresionRDeLista(idaux1, lexpre, expR);
                                obtenerExpresionRDeLista(idaux2, lexpre, expR2);
                                arbaux1 = obtenerArbol(expR);
                                arbaux2 = obtenerArbol(expR2);
                                if (!comparoArbol(arbaux1, arbaux2))
                                    printf("Resultado: Las expresiones no son iguales\n");
                                else
                                    printf("Resultado: Las expresiones son iguales\n");
                                limpiarListaString(lis);
                            }
                        }
                    }
                }
            }
            else if (comparoString(comando, "show"))
            {
                if (contarNodos(lis) != 1)
                    printf("No se esperaban parametros en este comando\n");
                else if (esVacia(lexpre))
                    printf ("No hay expresiones que mostrar\n");
                else
                {
                    printf("\nResultado:\n");
                    mostrarListaExpre(lexpre,FALSE);
                    limpiarListaString(lis);
                }
            }
            else if (comparoString(comando, "eval"))
            {
                //declaro variables
                expresionR expR;
                identificador id;

                if (contarNodos(lis) != 3)
                    printf("Error: Se esperaban dos parametros\n");
                else
                {
                    int numExp1 = convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,1)));
                    crearIdent(E,numExp1,id);
                    if (!idValido(id))
                        printf("Error: La expresion no es valida\n");
                    else
                    {
                        if (!existeIdent(id, lexpre))
                            printf("Error: La expresion no existe en la lista de expresiones\n");
                        else
                        {
                            string numEval = obtenerStringPos(lis,2);
                            if (!esNumero(numEval))
                                printf("Error: Se esperaba un numero mayor a cero como segundo parametro\n");
                            else
                            {
                                obtenerExpresionRDeLista(id,lexpre,expR);
                                printf ("Resultado: %d\n", evaluoArbol(obtenerArbol(expR), convertirString (numEval)));
                                limpiarListaString(lis);
                            }
                        }
                    }
                }
            }
            else if (comparoString(comando, "save"))
            {
                //declaro variables
                expresionR expR;

                if (contarNodos(lis) != 3)
                    printf("Error: Se esperaban dos parametros\n");
                else
                {
                    identificador aux1;
                    crearIdent(obtenerStringPos(lis,1)[0],convertirString(cortoNumeroDeExpresion(obtenerStringPos(lis,1))),aux1);
                    if (!idValido(aux1))
                        printf("Error: Numero de identificador del primer parametro no es valido\n");
                    else
                    {
                        if (!existeIdent(aux1, lexpre))
                            printf("Error: La expresion no existe en la lista de expresiones\n");
                        else
                        {
                            //lis = lis->sig->sig;
                            //str = lis->info;
                            str = obtenerStringPos(lis,2);
                            if (!contarPuntos(str))
                                printf ("\nError: nombre de archivo no valido");
                            else if (!esAlfanumerico(str))
                                printf("Error: El nombre de archivo no es valido\n");
                            else
                            {
                                if (!extensionValida(str))
                                    printf ("\nFormato de archivo no valido\n");
                                else
                                {
                                    if (existeArchivo(str))
                                    {
                                        printf ("\nEl archivo ya existe, desea sobrescribirlo (S/N)? ");
                                        char opc;
                                        scanf ("%c",&opc);
                                        fflush (stdin);
                                        if (cargarBooleano(opc))
                                        {
                                            obtenerExpresionRDeLista(aux1,lexpre,expR);
                                            arbolExpre auxArbol=obtenerArbol(expR);
                                            int n=0;
                                            numerarNodos(auxArbol,n);
                                            FILE * f = fopen (str, "wb");
                                            bajarExpR(expR, f);
                                            mostrarIdentificador (aux1);
                                            printf (" almacenada correctamente en ");
                                            mostrarString (str);
                                            printf("\n");
                                            limpiarListaString(lis);
                                            fclose(f);
                                        }
                                        else
                                            printf ("No se sobresribira el archivo\n");
                                    }
                                    else
                                    {
                                        obtenerExpresionRDeLista(aux1,lexpre,expR);
                                        arbolExpre auxArbol=obtenerArbol(expR);
                                        int n=0;
                                        numerarNodos(auxArbol,n);
                                        FILE * f = fopen (str, "wb");
                                        bajarExpR(expR, f);
                                        //sobrescribirArchivo (str, expR);
                                        mostrarIdentificador (aux1);
                                        printf (" almacenada correctamente en ");
                                        mostrarString (str);
                                        printf("\n");
                                        limpiarListaString(lis);
                                        fclose(f);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(comparoString(comando, "load"))
            {
                //declaro variables
                expresionR expR;
                identificador id;

                if (contarNodos(lis) != 2)
                    printf("Error: Se esperaba un nombre de archivo\n");
                else
                {
                    string str = obtenerStringPos(lis,1);
                    //str = lis->info;
                    if (!esAlfanumerico(str))
                        printf("Error: El nombre de archivo no es valido\n");
                    else
                    {
                        if (!extensionValida(str))
                            printf ("\nFormato de archivo no valido\n");
                        else
                        {
                            if (existeArchivo(str))
                            {
                                arbolExpre auxArbol;
                                crearArbol(auxArbol);
                                crearIdent(E,(maxId(lexpre)+1),id);
                                FILE * f=fopen(str,"rb");
                                subirExpR(f,auxArbol);
                                //subirExpR(f,arb);
                                //cargarExpresionR(id, arb, expR);
                                cargarExpresionR(id, auxArbol, expR);
                                mostrarExpresionR(expR,TRUE);
                                printf("\n");
                                guardarExpreAlFinal(expR,lexpre);
                                limpiarListaString(lis);
                                fclose(f);
                            }
                            else
                            {
                                printf ("Error: el archivo no existe\n");
                                limpiarListaString(lis);
                            }
                        }
                    }
                }
                limpiarListaString(lis);
            }
            else if (comparoString(comando, "quit"))
            {
                if (contarNodos(lis) != 1)
                    printf ("No se esperaba ningun parametro\n");
                else
                {
                    char opcion;
                    printf ("Desea salir del programa? S/N: ");
                    scanf ("%c",&opcion);
                    if (cargarBooleano(opcion))
                    {
                        if(!esVacia(lexpre))
                            borrarListaExpre(lexpre);
                        printf("Resultado: hasta la proxima!");
                        salir = TRUE;
                    }
                }
                limpiarListaString(lis);
            }
            else if (comparoString(comando, "help"))
            {
                printf ("\n\nComandos disponibles:");
                printf ("\n\n-create parametro - crea nuevas expresiones: \n  ejemplo create 2 ");
                printf ("\n\n-sum ident1 ident2 - suma dos expresiones \nexistentes generando una nueva expresion: \n  ejemplo sum e1 e2");
                printf ("\n\n-product ident1 ident2 - realiza el producto\n de dos expresiones existentes generando una nueva expresion:\n  ejemplo product e1 e2");
                printf ("\n\n-equals ident1 ident2 - verifica si dos \nexpresiones existentes son iguales:\n  ejemplo equals e1 e2");
                printf ("\n\n-show - muestra por pantalla las expresiones\n existentes en el sistema");
                printf ("\n\n-eval ident valor - calcula el valor de la\n expresión:\n  ejemplo: eval e2 5");
                printf ("\n\n-create parámetro - crea nuevas expresiones: \n  ejemplo create 2 ");
                printf ("\n\n-save ident nombreArchivo.dat - guarda la \nexpresión que pasamos por parámetro en un archivo:\n  ejemplo save e1 miexpresion.dat");
                printf ("\n\n-load nombreArchivo.dat - carga en memoria\n los datos contenidos en el archivo elegido:\n  ejemplo load miexpresion.dat");
                printf ("\n\n-quit - salir del programa\n\n");
            }
            else
                printf ("No es un comando valido, digite nuevamente\n");
            limpiarListaString(lis);
        }
        else
            printf ("\nNo ah digitado ningun comando, por favor ingrese un parametro. \nPor mas informacion digite help");
    }
    while (!salir);
}
