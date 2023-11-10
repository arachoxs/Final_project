#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

struct
{
    char name[20];
    char password[20];
    bool votaciones_abiertas;
}admin;

struct candidatos
{
    int cedula;
    char nombre[50];
    int numero_candidato;
    int numero_votos;
    bool ganador;

}candidato;

struct
{
    char tipo_usario[30];
    int cedula;
    char nombre[50];
    bool verificacion_voto;

}usuario;

char login_admin(); //donde se analiza el inicio de sesion del admin

void registro_usuario();

void registro_candidato();

void votacion();

void mostrar_candidatos();

void mostrar_usuarios();

void resetear();

void limpiar_archivos();

void eleccion_rector();

//main------------
bool validacion_votaciones_abiertas=true;


int main(){

FILE *archivo_admin;

archivo_admin=fopen("user_admin.txt","r");

fread(&admin,sizeof(admin),1,archivo_admin);

validacion_votaciones_abiertas=admin.votaciones_abiertas; //este es un bool que determina si las votaciones estan abiertas

fclose(archivo_admin);

int opcion_menu_1;

do 
{
    system("cls");
    printf("\n-----menu usuarios-----\n\n");
    printf("1.Admin\n2.usuario\n0.salir\n\n");
    printf("seleccione la opcion a acceder: "); scanf("%i",&opcion_menu_1);

    switch (opcion_menu_1)
    {
    case 1:
        char login_succesful=login_admin();
        int menu_admin;

        while (login_succesful=='t')
        {
            system("cls");
            printf("\n-----menu admin-----\n\n");
            printf("1.registrar candidato\n2.registrar usuario\n3.mostrar listado candidatos\n4.mostrar listado usuarios\n5.Resetear votos y verifiaciones\n6.Resetear archivos\n7.eleccion_rector\n0.salir\n\n");
            printf("seleccione la opcion a acceder: "); scanf("%i",&menu_admin);

            switch (menu_admin)
            {
            case 0:
                login_succesful='f';
                break;
            case 1:
                system("cls");
                registro_candidato();
                break;
            case 2:
                system("cls");
                registro_usuario();
                break;
            case 3:
                system("cls");
                mostrar_candidatos();
                break;
            case 4:
                system("cls");
                mostrar_usuarios();
                break;
            case 5:
                system("cls");
                resetear();
                break;
            case 6:
                system("cls");
                limpiar_archivos();
                break;
            case 7:
                system("cls");
                eleccion_rector();
                break;
            default:
                break;
            }
        }
        
        break;
    case 2:
        if (validacion_votaciones_abiertas)
        {
            system("cls");
            votacion();
        }
        else
        {
            system("cls");
            printf("\n\tEl sistema esta cerrado!\n\n");
            system("pause");
        }
        
        
        break;
    
    default:
        break;
    }
} while (opcion_menu_1!=0);



    return 0;
}



char login_admin(){
    char band='f';
    FILE *admin_user;
    admin_user=fopen("user_admin.txt","r");
    int n=1;
    
    char try_admin[20];
    char try_password[20];

    do
    {
        system("cls");
        printf("\n\tinicio de sesion\n\n");
        printf("Digite el usuario: "); scanf("%s",&try_admin);
        printf("Digite la contraseña: "); scanf("%s",&try_password);

        fread(&admin,sizeof(admin),1,admin_user);

        if ((strcmp(admin.name,try_admin)==0)&&(strcmp(admin.password,try_password)==0))
        {
            printf("\nSesion iniciada!\n");
            band='t';
            system("pause");
            break;
        }
        else
        {
            printf("\nUsuario o contraseña incorrecta\n");
            printf("Intente de nuevo\n");
            printf("numero de intentos restantes: %i\n",5-n);
            n++;
            system("pause");
            
        }
        
    } while (n<=5);

    fclose(admin_user);

    system("cls");

    return band;
    

}

void registro_usuario(){
    FILE *archivo;

    archivo=fopen("usuario.txt","a+");

    int tipo_usuario;

    do{
        system("cls");
        printf("Defina El tipo de usuario: \n1.Docente\n2.Estudiante\n3.Administrativo\n4.Egresado\n"); 
        printf("\n\nSeleccione su opcion: "); scanf("%i",&tipo_usuario);

        switch (tipo_usuario)
        {
        case 1:
            strcpy(usuario.tipo_usario,"Docente");
            break;
        case 2:
            strcpy(usuario.tipo_usario,"Estudiante");
            break;
        case 3:
            strcpy(usuario.tipo_usario,"Administrativo");
            break;
        case 4:
            strcpy(usuario.tipo_usario,"Egresado");
            break;
        default:
            break;
        }
    }while(tipo_usuario<1||tipo_usuario>4);

    system("cls");
 
    printf("Defina su cedula: "); scanf("%i",&usuario.cedula);

    getchar();
    printf("Defina su nombre: "); fgets(usuario.nombre, 50, stdin);
    usuario.nombre[strcspn(usuario.nombre, "\n")] = '\0';

    usuario.verificacion_voto=true; //true significa que no ha votado

    fwrite(&usuario,sizeof(usuario),1,archivo);

    fclose(archivo);

    system("cls");

    printf("\n\tUsuario agregado\n\n");

    system("pause");
    

}

void registro_candidato(){
    FILE *archivo;

    archivo=fopen("candidatos.txt","a");

    printf("Digite su cedula: "); scanf("%i",&candidato.cedula);
    getchar();
    printf("Digite su nombre: "); fgets(candidato.nombre, 50, stdin);
    candidato.nombre[strcspn(candidato.nombre, "\n")] = '\0';
    printf("Digite su numero de registro: "); scanf("%i",&candidato.numero_candidato);
    candidato.numero_votos=0;
    candidato.ganador=false;
    
    fwrite(&candidato,sizeof(candidato),1,archivo);

    fclose(archivo);

    system("cls");

    printf("\n\tCandidato agregado\n\n");

    system("pause");
}

void votacion(){
    FILE *archivo_candidato;
    FILE *temporal_candidato;

    FILE *archivo_usuario;
    FILE *temporal_usuario;

    char verificacion_usuario_encontrado='f';

    char verificacion_voto_correcto='f';

    archivo_usuario=fopen("usuario.txt","r");

    int numero_cedula;

    printf("Digite su numero de cedula: "); scanf("%i",&numero_cedula);

    while (fread(&usuario,sizeof(usuario),1,archivo_usuario)==1)
    {
        if (numero_cedula==usuario.cedula)
        {
            verificacion_usuario_encontrado='t';
            system("cls");
            printf("\n\tBienvenido %s!!\n\n",usuario.nombre);
            printf("Recuerde ejercer su voto a conciencia por una mejor UTP!\n\n");
            system("pause");
            if (usuario.verificacion_voto)
            {
                system("cls");
                int seleccion_voto;

                archivo_candidato=fopen("candidatos.txt","r");

                printf("\n\tCandidatos con su numeral: \n\n");


                while((fread(&candidato,sizeof(candidato),1,archivo_candidato))==1){
                    printf("%i %s\n",candidato.numero_candidato,candidato.nombre);
                }

                fclose(archivo_candidato);

                do
                {
                    temporal_candidato=fopen("candidatos_temporal.txt","w");
                    archivo_candidato=fopen("candidatos.txt","r");

                    printf("\nDigite el numeral del candidato a seleccionar: "); scanf("%i",&seleccion_voto);

                    while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
                    {
                        if (candidato.numero_candidato==seleccion_voto)
                        {   
                            verificacion_voto_correcto='t';
                            candidato.numero_votos+=1;
                            fwrite(&candidato,sizeof(candidato),1,temporal_candidato);
                        }
                        else
                        {
                            fwrite(&candidato,sizeof(candidato),1,temporal_candidato);
                        }
                        
                        
                    }

                    fclose(archivo_candidato);
                    fclose(temporal_candidato);
                    remove("candidatos.txt");
                    rename("candidatos_temporal.txt","candidatos.txt");
                    
                } while (verificacion_voto_correcto=='f');
            
            }
            else
            {
                system("cls");
                printf("\n\tEl usuario ya ejercio su derecho al voto\n\n");
                system("pause");
            }
            
            
        }        
    }

    fclose(archivo_usuario);


    if (verificacion_usuario_encontrado=='f')
    {
        system("cls");
        printf("\n\tUsuario no registrado en la base de datos!\n\n");
        system("pause");
    }
    else
    {
        archivo_usuario=fopen("usuario.txt","r");
        temporal_usuario=fopen("usuario_temporal.txt","w");

        while (fread(&usuario,sizeof(usuario),1,archivo_usuario)==1)
        {
            if (usuario.cedula==numero_cedula)
            {
                usuario.verificacion_voto=false;
                fwrite(&usuario,sizeof(usuario),1,temporal_usuario);
            }
            else
            {
                fwrite(&usuario,sizeof(usuario),1,temporal_usuario);
            }
        }


        fclose(archivo_usuario);
        fclose(temporal_usuario);

        remove("usuario.txt");
        rename("usuario_temporal.txt","usuario.txt");
    }
    
        
}

void mostrar_candidatos(){
    FILE *archivo_candidato;

    archivo_candidato=fopen("candidatos.txt","r");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
    {
        printf("%i %s %i\n",candidato.cedula,candidato.nombre,candidato.numero_votos);
    }
    
    fclose(archivo_candidato);

    system("pause");

}

void mostrar_usuarios(){
    FILE *archivo_usuario;

    archivo_usuario=fopen("usuario.txt","r");

    while (fread(&usuario,sizeof(usuario),1,archivo_usuario)==1)
    {
        printf("%i %s %s %i\n",usuario.cedula,usuario.nombre,usuario.tipo_usario,usuario.verificacion_voto);
    }
    
    fclose(archivo_usuario);

    system("pause");
}

void resetear(){
    int confirmacion_reset;
    do
    {
        system("cls");
        printf("\n\tEsta seguro?\n\n");
        printf("1.si\t2.no\n\n");
        printf("digite opcion:"); scanf("%i",&confirmacion_reset);
        switch (confirmacion_reset)
        {
        case 1:
            FILE *archivo_candidato;
            FILE *temporal_candidato;

            archivo_candidato=fopen("candidatos.txt","r");
            temporal_candidato=fopen("candidatos_temporal.txt","w");

            while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
            {
                candidato.numero_votos=0;
                fwrite(&candidato,sizeof(candidato),1,temporal_candidato);
            }

            fclose(archivo_candidato);
            fclose(temporal_candidato);

            remove("candidatos.txt");
            rename("candidatos_temporal.txt","candidatos.txt");

            FILE *archivo_usuario;
            FILE *temporal_usuario;

            archivo_usuario=fopen("usuario.txt","r");
            temporal_usuario=fopen("usuario_temporal.txt","w");

            while (fread(&usuario,sizeof(usuario),1,archivo_usuario)==1)
            {
                usuario.verificacion_voto=true;
                fwrite(&usuario,sizeof(usuario),1,temporal_usuario);
            }

            fclose(archivo_usuario);
            fclose(temporal_usuario);

            remove("usuario.txt");
            rename("usuario_temporal.txt","usuario.txt");

            system("cls");
            printf("\n\tSe han reseteado los votos y la verificacion de votos de los usuarios\n\n");
            system("pause");
            break;
        case 2:
            system("cls");
            printf("\n\tReseteo cancelado\n\n");
            system("pause");
            break;
        default:
            break;
        }
        
    } while (confirmacion_reset<0||confirmacion_reset>2);
    
    
}

void limpiar_archivos(){
    int opcion;
    FILE *archivo_candidatos;
    FILE *archivo_usuarios;

    do
    {
        system("cls");
        printf("\n\tQue desea hacer?\n\n1.resetar lista candidatos\n2.resetear lista usuarios\n3.resetear ambas\n0.cancelar\n");
        printf("\nseleccione opcion: "); scanf("%i",&opcion);

        switch (opcion)
        {
        case 1:
            archivo_candidatos=fopen("candidatos.txt","w");
            fclose(archivo_candidatos);
            system("cls");
            printf("\n\tarchivo reseteado!\n\n");
            system("pause");
            break;
        case 2:
            archivo_usuarios=fopen("usuario.txt","w");
            fclose(archivo_usuarios);
            system("cls");
            printf("\n\tarchivo reseteado!\n\n");
            system("pause");
            break;
        case 3:
            archivo_candidatos=fopen("candidatos.txt","w");
            archivo_usuarios=fopen("usuario.txt","w");
            fclose(archivo_candidatos);
            fclose(archivo_usuarios);
            system("cls");
            printf("\n\tarchivos reseteado!\n\n");
            system("pause");
            break;
        default:
            break;
        }
        
    } while (opcion<0||opcion>3);
}

void eleccion_rector(){

    int numero_candidatos;

    int candidato_ganador;

    printf("Confirme el numero de candidatos: ");  scanf("%i",&numero_candidatos);

    struct candidatos lista_candidatos[numero_candidatos];

    float numero_total_votos=0;

    int posicion_lista=0;

    FILE *archivo_candidato;

    archivo_candidato=fopen("candidatos.txt","r");


    while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
    {
        lista_candidatos[posicion_lista]=candidato;
        numero_total_votos+=candidato.numero_votos;
        posicion_lista++;
    }
    
    fclose(archivo_candidato);


    //se ordena la lista de mayor a menor segun los votos y luego se pasan solo los 3 primeros mayores de la lista a el archivo candidatos
    //luego de hacer esto se pone en false la variable sistema_funcionando porque ya se cierran las elecciones y luego se pone un menu donde 
    //un superior inicie sesion y se elija un rector 

    for (int i = 0; i < numero_candidatos-1; i++)
    {
        for (int a = 1; a < numero_candidatos; a++)
        {
            if (lista_candidatos[a-1].numero_votos<lista_candidatos[a].numero_votos)
            {
                struct candidatos temporal=lista_candidatos[a-1];
                lista_candidatos[a-1]=lista_candidatos[a];
                lista_candidatos[a]=temporal;

            }
            
        }
        
    }
    do
    {
        system("cls");

        printf("\t\t\tCandidatos con mas votos\n\n\n");

        printf("Nro\tNombre\t\t\t\t\tNumero de votos\t\tporcentaje\t\n\n");

        //aca ya se ordenaron los candidatos de mayor a menor en la lista
        for (int i = 0; i < 3; i++)
        {
            
            double porcentaje=lista_candidatos[i].numero_votos/numero_total_votos;

            printf("%i\t%s\t\t%i\t\t\t%.2f%%",lista_candidatos[i].numero_candidato,lista_candidatos[i].nombre,lista_candidatos[i].numero_votos,porcentaje*100);

            printf("\n\n");

        }

        printf("\n\nSenor Superior seleccione el candidato ganador: "); scanf("%i",&candidato_ganador);
    } while ((candidato_ganador!=lista_candidatos[0].numero_candidato)&&(candidato_ganador!=lista_candidatos[1].numero_candidato)&&(candidato_ganador!=lista_candidatos[2].numero_candidato));


    
      


    
}