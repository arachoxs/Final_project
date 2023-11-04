/*
    menu:

    

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

void mostrar_candidatos();

void mostrar_usuarios();

void resetear();

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
            printf("1.registrar candidato\n2.registrar usuario\n3.mostrar listado candidatos\n4.mostrar listado usuarios\n5.resetear votos y verifiaciones\n0.salir\n\n");
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
                

                //Establecer un bucle donde se siga haciendo la pregunta hasta que se ponga un numero que sea referente a un candidato.
                //se puede crear una bandera que en medio del bucle donde recorre todo el archivo y si se encuentra el numero se vuelve true 
                //hacer el procedimiento donde se agrega uno a la cantidad de votos del candidato y se le setea false a la verificacion de voto del usuario

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

//hazme una funcion que muestre el archivo candidatos.txt y todo su contenido

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

//hazme una funcion que muestre el archivo usuarios.txt y todo su contenido

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
}