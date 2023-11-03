/*
    menu:

    1.Admin(aca se van a registrar los candidatos y los usuarios)

    2.usuarios(aca es donde los usuarios van a votar , para poder acceder se tiene que verificar que los votantes esten ya registrados
    y como segunda opcion que no hayan ejercid su voto)


*/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

struct
{
    char name[20];
    char password[20];
}admin;

struct
{
    int cedula;
    char nombre[30];
    int numero_candidato;
    int numero_votos;

}candidato;

struct
{
    char tipo_usario[30];
    int cedula;
    char nombre[30];
    bool verificacion_voto;

}usuario;

char login_admin(); //donde se analiza el inicio de sesion del admin

void registro_usuario();

void registro_candidato();

void votacion();

int main(){

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
            printf("1.registrar candidato\n2.registrar usuario\n0.salir\n\n");
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
            default:
                break;
            }
        }
        
        break;
    case 2:
        system("cls");
        votacion();
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

    printf("Defina su cedula: "); scanf("%i",&usuario.cedula);

    printf("Defina su nombre: "); scanf("%s",&usuario.nombre);

    usuario.verificacion_voto=true; //true significa que no ha votado

    fwrite(&usuario,sizeof(usuario),1,archivo);

    fclose(archivo);

}

void registro_candidato(){
    FILE *archivo;

    archivo=fopen("candidatos.txt","a");

    printf("Digite su cedula: "); scanf("%i",&candidato.cedula);
    printf("Digite su nombre: "); scanf("%s",&candidato.nombre);
    printf("Digite su numero de registro: "); scanf("%i",&candidato.numero_candidato);
    candidato.numero_votos=0;

    fwrite(&candidato,sizeof(candidato),1,archivo);

    fclose(archivo);
}

void votacion(){
    FILE *archivo_candidato;
    FILE *archivo_usuario;

    char verifiacion_usuario_encontrado='f';

    archivo_usuario=fopen("usuario.txt","r");

    int numero_cedula;

    printf("Digite su numero de cedula: "); scanf("%i",&numero_cedula);

    while (fread(&usuario,sizeof(usuario),1,archivo_usuario)==1)
    {
        if (numero_cedula==usuario.cedula)
        {
            verifiacion_usuario_encontrado='t';
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

                printf("\nDigite el numeral del candidato a seleccionar: "); scanf("%i",&seleccion_voto);
                //Establecer un bucle donde se siga haciendo la pregunta hasta que se ponga un numero que sea referente a un candidato.
                //hacer el procedimiento donde se agrega uno a la cantidad de votos del candidato y se le setea false a la verificacion de voto del usuario

                break;
            }
            else
            {
                system("cls");
                printf("\n\tEl usuario ya ejercio su derecho al voto\n\n");
                system("pause");
            }
            
            
        }        
    }

    if (verifiacion_usuario_encontrado=='f')
    {
        system("cls");
        printf("\n\tUsuario no registrado en la base de datos!\n\n");
        system("pause");
    }
    
    
    
}