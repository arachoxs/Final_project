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
    int numero_votos_usuarios;
    int numero_votos_superiores;
    bool ganador;

}candidato;

struct
{
    char tipo_usario[30];
    int cedula;
    char nombre[50];
    bool verificacion_voto;

}usuario;

struct
{
    char tipo_usuario[30];
    int numero_candidato_votado;

}registro_voto;

struct
{
    char tipo_usuario[30];
    char cargo[60];
    int cedula;
    char nombre[30];
    bool verificacion_voto;

}superior;

struct
{
    bool segunda_vuelta;
}segunda_votacion_superior;

char login_admin(); //donde se analiza el inicio de sesion del admin

void registro_usuario(); //registro para el usuario

void registro_candidato(); //registro para el candidato

void registro_superior(); //registro para el superior

bool verificacion_votacion_abierta(); //verifica que las votacione esten abiertas para el usuario

void menu_votacion(); //menu donde estan las mesas de eleccion

void votacion(char tipo_usuario[20]); //donde se realiza la eleccion los usuarios

void mostrar_candidatos(); //muestra el archivo de candidatos

void mostrar_usuarios(); //muestra el archivo de usuarios

void mostrar_superiores(); //muestra el archivo de superiores

void resetear(); //resetea las banderas y los numeros de votos de todas los archivos

void limpiar_archivos(); //borra los archivos y se crean de nuevo limpios

bool verificacion_segunda_vuelta();

void eleccion_rector(); //menu para los superiores 

void rector_electo(); //donde se filtra el gandor

void menu_histogramas(); //menu de los histogramas

void histrograma(int numeral_candidato); //histogramas

void menu_histograma_usuarios();

void histograma_tipo_usuario(char tipo_usuario[20]);

int total_tipo_usuario(char tipo_usuario[20]);

float tipo_usuario_formula(char tipo_usuario[20],int numeral_candidato);

int total_votos_candidato(int numeral_candidato);

float formula(int numeral_candidato);

void tabla();

void candidatos_tabla(int numeral_candidato);

void tabla();

//main------------

int main(){

int opcion_menu_1;

do 
{
    system("cls");
    printf("\n\tMENU PRINCIPAL\t\n\n");
    //histograma tabla

    printf("1.Inicio sesion del administrador\n2.Votacion de los usuarios\n3.Votacion de los superiores\n4.Datos de las votaciones\n5.Resultado Ganador\n0.Salir\n\n");
    printf("Seleccione la opcion a acceder: "); scanf("%i",&opcion_menu_1);

    switch (opcion_menu_1)
    {
    case 1:
        char login_succesful=login_admin();
        int menu_admin;

        while (login_succesful=='t')
        {
            system("cls");
            printf("\n\tMENU ADMIN\t\n\n");
            printf("1.Menu registros\n2.Control base de datos\n0.Salir\n\n");
            printf("Seleccione la opcion a acceder: "); scanf("%i",&menu_admin);

            switch (menu_admin)
            {
            case 0:
                login_succesful='f';
                break;
            case 1:
                do
                {
                    system("cls");
                    printf("\n\tMENU REGISTRO\n\n");
                    printf("1.Registrar candidato\n2.Registrar usuario\n3.Registrar superior\n0.Salir\n\n");
                    printf("Seleccione la opcion a acceder: "); scanf("%i",&menu_admin);
                    switch (menu_admin)
                    {
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
                        registro_superior();
                    break;
                    default:
                        break;
                    }
                } while (menu_admin!=0);

                menu_admin=1;
                break;
            case 2:
                system("cls");
                do
                {
                    system("cls");
                    printf("\n\tMENU BASE DE DATOS\n\n");
                    printf("1.Mostrar candidatos\n2.Mostrar usuarios\n3.Mostrar superiores\n4.Mostrar registro votos\n5.Restear datos\n6.Iniciar votaciones desde cero\n7.resetear votacion superiores\n0.salir\n\n");
                    printf("seleccione la opcion a acceder: "); scanf("%i",&menu_admin);
                    switch (menu_admin)
                    {
                        case 1:
                            system("cls");
                            mostrar_candidatos();
                        break;
                        case 2:
                            system("cls");
                            mostrar_usuarios();
                        break;
                        case 3:
                            system("cls");
                            mostrar_superiores();
                        break;
                        case 4:
                            system("cls");
                            mostrar_registro_votos();
                        break;
                        case 5:
                            system("cls");
                            limpiar_archivos();
                        break;
                        case 6:
                            system("cls");
                            resetear();
                        break;
                        case 7:
                            system("cls");
                            resetear_votaciones_superiores();
                        break;
                    }

                } while (menu_admin!=0);
                
                menu_admin=2;
            break;
            default:
            break;
            }
        }
        
        break;
    case 2:
        if (verificacion_votacion_abierta())
        {
            system("cls");
            menu_votacion();
        }
        else
        {
            system("cls");
            printf("\n\tEl sistema esta cerrado!\n\n");
            system("pause");
        }
        break;
    case 3:
        system("cls");
        eleccion_rector();
    break;
    case 4:
        do
        {
            system("cls");
            printf("\n\tDatos de votaciones\n\n");
            printf("1.Histogramas por candidato\n2.Histograma por tipo de usuario\n3.Tabla de estadisticas\n0.Salir\n\n");
            printf("seleccione la opcion a acceder: "); scanf("%i",&opcion_menu_1);
            switch (opcion_menu_1)
            {  
            case 1:
                system("cls");
                menu_histogramas();
            break;
            case 2:
                system("cls");
                menu_histograma_usuarios();
            break;
            case 3:
                system("cls");
                tabla();
            break;
            default:
                break;
            }
        } while (opcion_menu_1!=0);

        opcion_menu_1=4;
        
    break;
    case 5:
        system("cls");
        rector_electo();
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
        printf("\n\tInicio de sesion\n\n");
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
    
    int cedula_usuario_nuevo;

    printf("Defina su cedula: "); scanf("%i",&cedula_usuario_nuevo);

    archivo=fopen("usuario.txt","r");

    bool cedula_nueva=true;

    while (fread(&usuario,sizeof(usuario),1,archivo)==1)
    {
        if (usuario.cedula==cedula_usuario_nuevo)
        {
            cedula_nueva=false;
        }
        
    }

    fclose(archivo);

    archivo=fopen("usuario.txt","a");
    
    if (cedula_nueva==false)
    {
        system("cls");
        printf("\n\tUsuario registrado\n\n");
        system("pause");
    }
    else
    {
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

        usuario.cedula=cedula_usuario_nuevo;

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
    
}

void registro_candidato(){
    FILE *archivo;

    archivo=fopen("candidatos.txt","a");

    printf("Digite su cedula: "); scanf("%i",&candidato.cedula);
    getchar();
    printf("Digite su nombre: "); fgets(candidato.nombre, 50, stdin);
    candidato.nombre[strcspn(candidato.nombre, "\n")] = '\0';
    printf("Digite su numero de registro: "); scanf("%i",&candidato.numero_candidato);
    candidato.numero_votos_usuarios=0;
    candidato.numero_votos_superiores=0;
    candidato.ganador=false;
    
    fwrite(&candidato,sizeof(candidato),1,archivo);

    fclose(archivo);

    system("cls");

    printf("\n\tCandidato agregado\n\n");

    system("pause");
}

void registro_superior(){
    FILE *archivo;
    archivo=fopen("superiores.txt","r");
    int conteo_superiores=0;
    bool cedula_existente=false;

    int cedula;

    while (fread(&superior,sizeof(superior),1,archivo)==1)
    {
        conteo_superiores++;
        
    }

    fclose(archivo);
    
    if (conteo_superiores<=9)
    {
        archivo=fopen("superiores.txt","r");

        printf("Digite cedula: "); scanf("%i",&cedula);

        while (fread(&superior,sizeof(superior),1,archivo)==1)
        {

            if (cedula==superior.cedula)
            {
                cedula_existente=true;
            }
            
        }

        fclose(archivo);

        if (cedula_existente==false)
        {
            archivo=fopen("superiores.txt","a");
            strcpy(superior.tipo_usuario,"Superior");
            superior.cedula=cedula; 

            getchar();
            printf("Digite su nombre: ");  fgets(superior.nombre, 30, stdin);
            superior.nombre[strcspn(superior.nombre, "\n")] = '\0';
            
            getchar();
            printf("Digite su cargo: ");  fgets(superior.cargo, 60, stdin);
            superior.cargo[strcspn(superior.cargo, "\n")] = '\0';

            superior.verificacion_voto=true; //siginica que esta habilitado para votar

            fwrite(&superior,sizeof(superior),1,archivo);
            fclose(archivo);
        }
        else
        {
            system("cls");
            printf("\n\tCedula ya registrada\n\n");
            system("pause");
        }
        
    }
    else
    {
        system("cls");
        printf("\n\tBase de datos de superiores llena\n\n");
        system("pause"); 
    }
}

bool verificacion_votacion_abierta(){
    FILE *archivo_admin;

    archivo_admin=fopen("user_admin.txt","r");

    fread(&admin,sizeof(admin),1,archivo_admin);

    fclose(archivo_admin);

    return admin.votaciones_abiertas;

}

void menu_votacion(){
    int seleccion_urna;
    FILE *archivo_usuario;
    int cedula_usuario;
    do
    {
        system("cls");
        printf("\n\tSeleccione la urna a entrar\n\n");
        printf("1.Docente\n2.Estudiante\n3.Administrativo\n4.Egresado\n0.salir\n\n");
        printf("Digite su opcion: "); scanf("%i",&seleccion_urna);
        system("cls");
        switch (seleccion_urna)
        {
        case 1:
            votacion("Docente");
            break;
        case 2:
            votacion("Estudiante");
            break;
        case 3:
            votacion("Administrativo");
            break;
        case 4:
            votacion("Egresado");
            break;
        case 0:
            return 0;
            break;
        default:
            break;
        }
    } while (seleccion_urna>5||seleccion_urna<1);
    
}

void votacion(char tipo_usuario[20]){
    FILE *archivo_candidato;
    FILE *temporal_candidato;

    FILE *archivo_usuario;
    FILE *temporal_usuario;

    char verificacion_usuario_encontrado='f';

    char verificacion_voto_correcto='f';

    int seleccion_voto;

    archivo_usuario=fopen("usuario.txt","r");

    int numero_cedula;

    printf("Digite su numero de cedula: "); scanf("%i",&numero_cedula);

    while (fread(&usuario,sizeof(usuario),1,archivo_usuario)==1)
    {
        if (numero_cedula==usuario.cedula&&(strcmp(usuario.tipo_usario,tipo_usuario)==0))
        {
            verificacion_usuario_encontrado='t';
            system("cls");
            printf("\n\tBienvenido %s!!\n\n",usuario.nombre);
            printf("Recuerde ejercer su voto a conciencia por una mejor UTP!\n\n");
            system("pause");
            if (usuario.verificacion_voto)
            {
                do
                {
                    system("cls");

                    int confirmacion_voto;

                    archivo_candidato=fopen("candidatos.txt","r");

                    printf("\n\tCandidatos con su numeral: \n\n");


                    while((fread(&candidato,sizeof(candidato),1,archivo_candidato))==1){
                        printf("%i %s\n",candidato.numero_candidato,candidato.nombre);
                    }

                    fclose(archivo_candidato);

                    archivo_candidato=fopen("candidatos.txt","r");

                    printf("\nDigite el numeral del candidato a seleccionar: "); scanf("%i",&seleccion_voto);

                    while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
                    {
                        if (candidato.numero_candidato==seleccion_voto)
                        {   
                            verificacion_voto_correcto='t';
                            break;
                            
                        }
                    }

                    fclose(archivo_candidato);

                    do
                    {
                        system("cls");
                        printf("Esta seguro de su seleccion?\n1.si\n2.no\n\nDigite su opcion: "); scanf("%i",&confirmacion_voto);
                    } while (confirmacion_voto>2||confirmacion_voto<1);
                    
                    if (confirmacion_voto==2)
                    {
                        verificacion_voto_correcto='f';
                    }
                    
                } while (verificacion_voto_correcto=='f');


                temporal_candidato=fopen("candidatos_temporal.txt","w");
                archivo_candidato=fopen("candidatos.txt","r");

                while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
                {
                    if (candidato.numero_candidato==seleccion_voto)
                    {   
                        candidato.numero_votos_usuarios+=1;
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
        printf("\n\tUsuario no registrado en la base de datos o urna erronea\n\n");
        system("pause");
    }
    else
    {
        if (verificacion_voto_correcto=='t')
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

            FILE *archivo_registro;

            archivo_registro=fopen("registro_voto.txt","a");

            registro_voto.numero_candidato_votado=seleccion_voto;
            
            strcpy(registro_voto.tipo_usuario,tipo_usuario);

            fwrite(&registro_voto,sizeof(registro_voto),1,archivo_registro);

            fclose(archivo_registro);
        }
        
    }
    
        
}

void mostrar_candidatos(){
    FILE *archivo_candidato;

    archivo_candidato=fopen("candidatos.txt","r");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
    {
        printf("%i %s %i %i\n",candidato.cedula,candidato.nombre,candidato.numero_votos_usuarios,candidato.numero_votos_superiores);
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

void mostrar_superiores(){
    FILE *archivo_superior;

    archivo_superior=fopen("superiores.txt","r");

    while (fread(&superior,sizeof(superior),1,archivo_superior)==1)
    {
        printf("%i %s %s %i\n",superior.cedula,superior.nombre,superior.tipo_usuario,superior.verificacion_voto);
    }
    
    fclose(archivo_superior);

    system("pause");
}

void mostrar_registro_votos(){
    FILE *archivo_registro;

    archivo_registro=fopen("registro_voto.txt","r");

    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {
        printf("%i %s\n",registro_voto.numero_candidato_votado,registro_voto.tipo_usuario);
    }
    
    fclose(archivo_registro);

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

            //resetea los valores de los candidatos

            archivo_candidato=fopen("candidatos.txt","r");
            temporal_candidato=fopen("candidatos_temporal.txt","w");

            while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
            {
                candidato.numero_votos_usuarios=0;
                candidato.numero_votos_superiores=0;
                candidato.ganador=false;
                fwrite(&candidato,sizeof(candidato),1,temporal_candidato);
            }

            fclose(archivo_candidato);
            fclose(temporal_candidato);

            remove("candidatos.txt");
            rename("candidatos_temporal.txt","candidatos.txt");

            //resetea los valores de usuarios

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

            FILE *archivo_registro;

            archivo_registro=fopen("registro_voto.txt","w");
            fclose(archivo_registro);

            //resetea los valores de los superiores

            FILE *archivo_superior;
            FILE *temporal_superior;

            archivo_superior=fopen("superiores.txt","r");

            temporal_superior=fopen("superiores_temporal.txt","w");

            while (fread(&superior,sizeof(superior),1,archivo_superior)==1)
            {
                superior.verificacion_voto=true;
                fwrite(&superior,sizeof(superior),1,temporal_superior);
            }

            fclose(archivo_superior);

            fclose(temporal_superior);

            remove("superiores.txt");

            rename("superiores_temporal.txt","superiores.txt");

            FILE *temporal_administrador;
            FILE *archivo_administrador;
            
            archivo_administrador=fopen("user_admin.txt","r");
            temporal_administrador=fopen("temporal_admininistrador.txt","w");

            fread(&admin,sizeof(admin),1,archivo_administrador);

            admin.votaciones_abiertas=true;

            fwrite(&admin,sizeof(admin),1,temporal_administrador);

            fclose(archivo_administrador);
            fclose(temporal_administrador);

            remove("user_admin.txt");
            rename("temporal_admininistrador.txt","user_admin.txt");  

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
    FILE *archivo_registro;

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
            archivo_registro=fopen("registro_voto.txt","w");
            fclose(archivo_registro);
            system("cls");
            printf("\n\tarchivo reseteado!\n\n");
            system("pause");
            break;
        case 3:
            archivo_candidatos=fopen("candidatos.txt","w");
            archivo_usuarios=fopen("usuario.txt","w");
            archivo_registro=fopen("registro_voto.txt","w");
            fclose(archivo_candidatos);
            fclose(archivo_usuarios);
            fclose(archivo_registro);
            system("cls");
            printf("\n\tarchivos reseteado!\n\n");
            system("pause");
            break;
        default:
            break;
        }
        
    } while (opcion<0||opcion>3);
}

void resetear_votaciones_superiores(){
    FILE *archivo_candidatos=fopen("candidatos.txt","r");
    FILE *temporal_candidatos=fopen("temporal_candidato.txt","w");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
    {
        candidato.numero_votos_superiores=0;
        if(candidato.ganador==true){
            candidato.ganador=false;
        }
        
        fwrite(&candidato,sizeof(candidato),1,temporal_candidatos);
    }
    fclose(temporal_candidatos);
    fclose(archivo_candidatos);
    
    remove("candidatos.txt");
    rename("temporal_candidato.txt","candidatos.txt");
    //resetea las banderas de los superiores
    FILE *archivo_superiores;
    FILE *temporal_superiores;
    archivo_superiores=fopen("superiores.txt","r");
    temporal_superiores=fopen("temporal_superiores.txt","w");
    while (fread(&superior,sizeof(superior),1,archivo_superiores)==1)
    {
        superior.verificacion_voto=true;
        fwrite(&superior,sizeof(superior),1,temporal_superiores);
    }
    fclose(temporal_superiores);
    fclose(archivo_superiores);
    remove("superiores.txt");
    rename("temporal_superiores.txt","superiores.txt");

    
}

void eleccion_rector(){

    int cedula_superior; //se usa luego para modificar la bandera voto en el superior

    int seleccion_voto;

    FILE *archivo_superior;

    FILE *archivo_candidato;
    
    FILE *archivo_administrador;

    int numero_candidatos=0;

    bool verificacion_cedula_existente=false;

    bool verificacion_voto_realizado=false;

    //conteo de total candidatos

    archivo_candidato=fopen("candidatos.txt","r");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
    {
        numero_candidatos++;
    }
    
    fclose(archivo_candidato);

    bool verificacion_votos_faltantes=false;

    archivo_superior=fopen("superiores.txt","r");

    while (fread(&superior,sizeof(superior),1,archivo_superior)==1){
        if (superior.verificacion_voto==true)
        {
            verificacion_votos_faltantes=true;
        }
        
    }

    fclose(archivo_superior);

    if (verificacion_votos_faltantes==true)
    {
        archivo_superior=fopen("superiores.txt","r");

        printf("Señor Superior, por favor ingrese su cedula: "); scanf("%i",&cedula_superior);

        while (fread(&superior,sizeof(superior),1,archivo_superior)==1)
        {
            if (cedula_superior==superior.cedula)
            {
                verificacion_cedula_existente=true;
                fclose(archivo_superior);
                break;
            }
            
            
        }
    }
    else
    {
        rector_electo();
        return 0;
    }
    

    if (verificacion_cedula_existente)
    {
        if (superior.verificacion_voto==true)
        {
            struct candidatos lista_candidatos[numero_candidatos];
            float lista_formulas[numero_candidatos]; //llenar con las formulas de cada candidato
            int numero_candidato=1;

            for (int i = 0; i < numero_candidatos; i++)
            {
                lista_formulas[i]=formula(numero_candidato);
                numero_candidato++;
            }
            
            
            float numero_total_votos=0;
            int posicion_lista=0;
            FILE *archivo_candidato;
            archivo_candidato=fopen("candidatos.txt","r");
            while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
            {
                lista_candidatos[posicion_lista]=candidato;
                numero_total_votos+=candidato.numero_votos_usuarios;
                posicion_lista++;
            }
            
            fclose(archivo_candidato);
            //se ordena los candidatos segun su numero de votos de mayor a menor
            for (int i = 0; i < numero_candidatos-1; i++)
            {
                for (int a = 1; a < numero_candidatos; a++)
                {
                    if (lista_formulas[a-1]<lista_formulas[a])
                    {
                        struct candidatos temporal=lista_candidatos[a-1];
                        lista_candidatos[a-1]=lista_candidatos[a];
                        lista_candidatos[a]=temporal;

                        float formula_candidato=lista_formulas[a-1];
                        lista_formulas[a-1]=lista_formulas[a];
                        lista_formulas[a]=formula_candidato;
                    }
                    
                }
                
            }
            // se muestra los 3 con mas votos para que superior tome una desicion

            if (verificacion_segunda_vuelta()==false)
            {
                do
                {
                    system("cls");
                    printf("\t\t\tCandidatos con mas votos\n\n\n");
                    printf("Nro\tNombre\t\t\t\t\tNumero de votos\t\tporcentaje\t\n\n");
                    //aca ya se ordenaron los candidatos de mayor a menor en la lista
                    for (int i = 0; i < 3; i++)
                    {
                        
                
                        printf("%i\t%s\t\t%i\t\t\t%.2f%%",lista_candidatos[i].numero_candidato,lista_candidatos[i].nombre,lista_candidatos[i].numero_votos_usuarios,lista_formulas[i]);
                        printf("\n\n");
                    }
                    printf("\n\nSenor Superior seleccione el candidato ganador: "); scanf("%i",&seleccion_voto);
                } while ((seleccion_voto!=lista_candidatos[0].numero_candidato)&&(seleccion_voto!=lista_candidatos[1].numero_candidato)&&(seleccion_voto!=lista_candidatos[2].numero_candidato));
                //luego se suma uno a la varible votos_superiores y se pone en false el acceso a votar del superior
                verificacion_voto_realizado=true;
            }
            else
            {
                do
                {
                    system("cls");
                    printf("\t\t\tCandidatos con mas votos\n\n\n");
                    printf("Nro\tNombre\t\t\t\t\tNumero de votos\t\tporcentaje\t\n\n");
                    //aca ya se ordenaron los candidatos de mayor a menor en la lista
                    for (int i = 0; i < 2; i++)
                    {
                        
                
                        printf("%i\t%s\t\t%i\t\t\t%.2f%%",lista_candidatos[i].numero_candidato,lista_candidatos[i].nombre,lista_candidatos[i].numero_votos_usuarios,lista_formulas[i]);
                        printf("\n\n");
                    }
                    printf("\n\nSenor Superior seleccione el candidato ganador: "); scanf("%i",&seleccion_voto);
                } while ((seleccion_voto!=lista_candidatos[0].numero_candidato)&&(seleccion_voto!=lista_candidatos[1].numero_candidato));
                //luego se suma uno a la varible votos_superiores y se pone en false el acceso a votar del superior
                verificacion_voto_realizado=true;
            }   
        }
        else
        {
            system("cls");
            printf("\n\tUsted ya ha votado\n\n");
            system("pause");
        }
        
    }
    else
    {
        system("cls");
        printf("\n\tCedula incorrecta\n\n");
        system("pause");
    }

    if (verificacion_voto_realizado)
    {
        FILE *temporal_superior;
        FILE *temporal_candidato;
 
        archivo_superior=fopen("superiores.txt","r");
        temporal_superior=fopen("temporal_superior.txt","w");

        while (fread(&superior,sizeof(superior),1,archivo_superior)==1)
        {
            if (superior.cedula==cedula_superior)
            {
                superior.verificacion_voto=false;
                fwrite(&superior,sizeof(superior),1,temporal_superior);
            }
            else
            {
                fwrite(&superior,sizeof(superior),1,temporal_superior);
            }
        }

        fclose(temporal_superior);
        fclose(archivo_superior);

        remove("superiores.txt");
        rename("temporal_superior.txt","superiores.txt");

        archivo_candidato=fopen("candidatos.txt","r");
        temporal_candidato=fopen("temporal_candidato.txt","w");

        while (fread(&candidato,sizeof(candidato),1,archivo_candidato)==1)
        {
            if (candidato.numero_candidato==seleccion_voto)
            {
                candidato.numero_votos_superiores+=1;
                fwrite(&candidato,sizeof(candidato),1,temporal_candidato);
            }
            else
            {
                fwrite(&candidato,sizeof(candidato),1,temporal_candidato);
            }
        }

        fclose(temporal_candidato);
        fclose(archivo_candidato);

        remove("candidatos.txt");
        rename("temporal_candidato.txt","candidatos.txt");

        if (verificacion_votacion_abierta())
        {
            FILE *temporal_administrador;
            
            archivo_administrador=fopen("user_admin.txt","r");
            temporal_administrador=fopen("temporal_admininistrador.txt","w");

            fread(&admin,sizeof(admin),1,archivo_administrador);

            admin.votaciones_abiertas=false;

            fwrite(&admin,sizeof(admin),1,temporal_administrador);

            fclose(archivo_administrador);
            fclose(temporal_administrador);

            remove("user_admin.txt");
            rename("temporal_admininistrador.txt","user_admin.txt");  
        }
        
    }
}

bool verificacion_segunda_vuelta(){
    FILE *archivo_segunda_vuelta;

    archivo_segunda_vuelta=fopen("segunda_vuelta.txt","r");

    fread(&segunda_votacion_superior,sizeof(segunda_votacion_superior),1,archivo_segunda_vuelta);

    fclose(archivo_segunda_vuelta);

    return segunda_votacion_superior.segunda_vuelta;
}

void rector_electo(){
    FILE *archivo_candidatos;
    FILE *temporal_candidatos;

    int numero_candidatos=0;

    bool ganador_encontrado=false;

    int contador_votos_ejercidos=0;

    archivo_candidatos=fopen("candidatos.txt","r");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
    {
        if (candidato.ganador==true)
        {
            ganador_encontrado=true;
        }

        contador_votos_ejercidos+=candidato.numero_votos_superiores;
    }

    fclose(archivo_candidatos);

    if (ganador_encontrado==false)
    {
        if (contador_votos_ejercidos==10)
        {
            archivo_candidatos=fopen("candidatos.txt","r");

            while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
            {
                numero_candidatos++;
            }
            
            fclose(archivo_candidatos);


            struct candidatos lista_candidatos[numero_candidatos];

            int posicion_lista=0;

            archivo_candidatos=fopen("candidatos.txt","r");
            while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
            {
                lista_candidatos[posicion_lista]=candidato;
                posicion_lista++;
            }
            
            fclose(archivo_candidatos);
            //se ordena los candidatos segun su numero de votos de mayor a menor
            for (int i = 0; i < numero_candidatos-1; i++)
            {
                for (int a = 1; a < numero_candidatos; a++)
                {
                    if (lista_candidatos[a-1].numero_votos_superiores<lista_candidatos[a].numero_votos_superiores)
                    {
                        struct candidatos temporal=lista_candidatos[a-1];
                        lista_candidatos[a-1]=lista_candidatos[a];
                        lista_candidatos[a]=temporal;
                    }
                    
                }
                
            }
            //luego de ordenarlos el mayor queda en la posicion 0

            if(lista_candidatos[0].numero_votos_superiores>=6){
                archivo_candidatos=fopen("candidatos.txt","r");
                temporal_candidatos=fopen("temporal_candidato.txt","w");

                while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
                {
                    if (lista_candidatos[0].numero_candidato==candidato.numero_candidato)
                    {
                        candidato.ganador=true;
                        fwrite(&candidato,sizeof(candidato),1,temporal_candidatos);
                    }
                    else
                    {
                        fwrite(&candidato,sizeof(candidato),1,temporal_candidatos);
                    }
                }

                fclose(temporal_candidatos);
                fclose(archivo_candidatos);

                remove("candidatos.txt");
                rename("temporal_candidato.txt","candidatos.txt");
            }
            else
            {
                system("cls");
                printf("\n\tEl candidato con mayor votos no supero los 6 votos\n\n");

                archivo_candidatos=fopen("candidatos.txt","r");
                temporal_candidatos=fopen("temporal_candidato.txt","w");

                while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
                {
                    candidato.numero_votos_superiores=0;
                    fwrite(&candidato,sizeof(candidato),1,temporal_candidatos);
                }

                fclose(temporal_candidatos);
                fclose(archivo_candidatos);
                
                remove("candidatos.txt");
                rename("temporal_candidato.txt","candidatos.txt");

                //resetea las banderas de los superiores

                FILE *archivo_superiores;
                FILE *temporal_superiores;

                archivo_superiores=fopen("superiores.txt","r");
                temporal_superiores=fopen("temporal_superiores.txt","w");

                while (fread(&superior,sizeof(superior),1,archivo_superiores)==1)
                {
                    superior.verificacion_voto=true;
                    fwrite(&superior,sizeof(superior),1,temporal_superiores);
                }

                fclose(temporal_superiores);
                fclose(archivo_superiores);

                remove("superiores.txt");
                rename("temporal_superiores.txt","superiores.txt");

                FILE *archivo_segunda_vuelta;
                FILE *temporal_segunda_vuelta;

                archivo_segunda_vuelta=fopen("segunda_vuelta.txt","r");
                temporal_segunda_vuelta=fopen("temporal_segunda_vuelta.txt","w");

                while (fread(&segunda_votacion_superior,sizeof(segunda_votacion_superior),1,archivo_segunda_vuelta)==1)
                {
                    segunda_votacion_superior.segunda_vuelta=true;
                    fwrite(&segunda_votacion_superior,sizeof(segunda_votacion_superior),1,temporal_segunda_vuelta);
                }

                fclose(temporal_segunda_vuelta);
                fclose(archivo_segunda_vuelta);

                remove("segunda_vuelta.txt");
                rename("temporal_segunda_vuelta.txt","segunda_vuelta.txt");

                printf("\n\t\tVotos de superiores reseteados\n\n");
                system("pause");

            }
            
        }
        else
        {
            system("cls");
            printf("\n\tFaltan superiores por votar\n\n");
            system("pause");
        }
    }
    
    if (ganador_encontrado==true)
    {
        printf("\t\t\t\t\t\t\t\tCANDIDATO GANADOR\n\n");
        archivo_candidatos=fopen("candidatos.txt","r");

        while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
        {
            if (candidato.ganador==true)
            {
                printf(" ______________________________________________________________________________________________________________________________________________________________________________\n");
                printf("|\t  CANDIDATO\t\t|\tDOCENTES 40%%\t|\tESTUDIANTES 35%%\t|\tADMINISTRATIVO 10%%\t|\tEGRESADO 15%%\t|\tTOTALES\t|\tRESULTADOS\t|\n");
                candidatos_tabla(candidato.numero_candidato);
                printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

                
                system("pause");

            }
        }
        fclose(archivo_candidatos);
    
    }
    
}

void menu_histogramas(){
   
    char salir;

    do
    {
        system("cls");
        salir='f';

        FILE *archivo_candidatos;

        int seleccion_candidato;


        do
        {
            system("cls");
            archivo_candidatos=fopen("candidatos.txt","r");

            printf("\n\tCandidatos con su numeral: \n\n");

            while((fread(&candidato,sizeof(candidato),1,archivo_candidatos))==1){
                printf("%i %s\n",candidato.numero_candidato,candidato.nombre);
                }

            printf("0.salir");

            printf("\n\nSeleccione el candidato para el histograma: "); scanf("%i",&seleccion_candidato);

            if (seleccion_candidato==0)
            {
                salir='t';
            }

            fclose(archivo_candidatos);
            
        } while (seleccion_candidato<0||seleccion_candidato>7);
        
        if (salir=='f')
        {
            system("cls");
            histrograma(seleccion_candidato);
        }
        
    } while (salir=='f');
}

void asteriscos(int numero_votos){
    
    for (int i = 0; i < numero_votos; i++)
    {
        printf("%c",219);
    }

    
}

void histrograma(int numeral_candidato){
    int lista_votos_usuario[4]={0,0,0,0}; //Docente,Estudiante,Administrativo,Egresado

    float total_votos=0;

    FILE *archivo_registro;

    archivo_registro=fopen("registro_voto.txt","r");
    
    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {

        if (registro_voto.numero_candidato_votado==numeral_candidato)
        {
            if (strcmp(registro_voto.tipo_usuario,"Docente")==0)
            {
                lista_votos_usuario[0]+=1;
            }
            else if (strcmp(registro_voto.tipo_usuario,"Estudiante")==0)
            {
                lista_votos_usuario[1]+=1;
            }
            else if (strcmp(registro_voto.tipo_usuario,"Administrativo")==0)
            {
                lista_votos_usuario[2]+=1;
            }
            else if (strcmp(registro_voto.tipo_usuario,"Egresado")==0)
            {
                lista_votos_usuario[3]+=1;
            }

            total_votos+=1;
        }

    }

    fclose(archivo_registro);

    FILE *archivo_candidatos;

    archivo_candidatos=fopen("candidatos.txt","r");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
    {
        if (candidato.numero_candidato==numeral_candidato)
        {
            printf("\n\tHistograma de votos para el candidato %s\n\n\n",candidato.nombre);
            break;
        }
    }
    fclose(archivo_candidatos);

    printf("Tipo usuario\t\tPorcentaje\tNumero votos\tHistograma\n\n");
    
    printf("Docente:\t\t"); printf("%.1f %%\t\t\t%i\t",tipo_usuario_formula("Docente",numeral_candidato)*10,lista_votos_usuario[0]); asteriscos((lista_votos_usuario[0]/total_votos)*50); printf("\n\n");
    printf("Estudiante:\t\t"); printf("%.1f %%\t\t\t%i\t",tipo_usuario_formula("Estudiante",numeral_candidato)*10,lista_votos_usuario[1]); asteriscos((lista_votos_usuario[1]/total_votos)*50); printf("\n\n");
    printf("Administrativo:\t\t"); printf("%.1f %%\t\t\t%i\t",tipo_usuario_formula("Administrativo",numeral_candidato)*10,lista_votos_usuario[2]); asteriscos((lista_votos_usuario[2]/total_votos)*50); printf("\n\n");
    printf("Egresado:\t\t"); printf("%.1f %%\t\t\t%i\t",tipo_usuario_formula("Egresado",numeral_candidato)*10,lista_votos_usuario[3]); asteriscos((lista_votos_usuario[3]/total_votos)*50);  printf("\n\n");
    printf("\n\n");

    system("pause");

}

void menu_histograma_usuarios(){
    int seleccion_usuario;

    do
    {
        system("cls");
        printf("\tHISTOGRAMA USUARIOS\t\n\n");
        printf("1.Docente\n2.Estudiante\n3.Administrativo\n4.Egresado\n0.Salir\n\nSeleccione el tipo de usuario: "); scanf("%i",&seleccion_usuario);

        switch (seleccion_usuario)
        {
        case 1:
            system("cls");
            histograma_tipo_usuario("Docente");
            break;
        case 2:
            system("cls");
            histograma_tipo_usuario("Estudiante");
            break;
        case 3:
            system("cls");
            histograma_tipo_usuario("Administrativo");
            break;
        case 4:
            system("cls");
            histograma_tipo_usuario("Egresado");
            break; 
        case 0:
            break; 
        default:
            break;
        }

    } while (seleccion_usuario!=0);
    

}

void histograma_tipo_usuario(char tipo_usuario[20]){
    //funcion que muestra un histograma por el tipo de usuario dado

    int lista_votos_candidatos[7]={0,0,0,0,0,0,0}; //candidatos 1,2,3,4,5,6,7

    float total_votos=0;

    FILE *archivo_registro;

    archivo_registro=fopen("registro_voto.txt","r");

    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {
        if (strcmp(registro_voto.tipo_usuario,tipo_usuario)==0)
        {
            if (registro_voto.numero_candidato_votado==1)
            {
                lista_votos_candidatos[0]+=1;
            }
            else if (registro_voto.numero_candidato_votado==2)
            {
                lista_votos_candidatos[1]+=1;
            }
            else if (registro_voto.numero_candidato_votado==3)
            {
                lista_votos_candidatos[2]+=1;
            }
            else if (registro_voto.numero_candidato_votado==4)
            {
                lista_votos_candidatos[3]+=1;
            }
            else if (registro_voto.numero_candidato_votado==5)
            {
                lista_votos_candidatos[4]+=1;
            }
            else if (registro_voto.numero_candidato_votado==6)
            {
                lista_votos_candidatos[5]+=1;
            }
            else if (registro_voto.numero_candidato_votado==7)
            {
                lista_votos_candidatos[6]+=1;
            }

            total_votos+=1;
        }
    }

    fclose(archivo_registro);

    printf("\n\tHistrograma de votos por %s\n\n\n",tipo_usuario);

    printf("\tNombre Candidato\t\tPorcentaje\tNumero votos\tHistograma\n\n");

    printf("Luis Fernando Gaviria Trujillo:\t\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[0]/total_votos)*100,lista_votos_candidatos[0]); asteriscos((lista_votos_candidatos[0]/total_votos)*50); printf("\n\n");
    printf("Carlos Alfonso Victoria Mena:\t\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[1]/total_votos)*100,lista_votos_candidatos[1]); asteriscos((lista_votos_candidatos[1]/total_votos)*50); printf("\n\n");
    printf("Giovanni Arias:\t\t\t\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[2]/total_votos)*100,lista_votos_candidatos[2]); asteriscos((lista_votos_candidatos[2]/total_votos)*50); printf("\n\n");
    printf("Xiomara Rocio Gonzales Ordoñes:\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[3]/total_votos)*100,lista_votos_candidatos[3]); asteriscos((lista_votos_candidatos[3]/total_votos)*50); printf("\n\n");
    printf("Alexander Molina Cabrena:\t\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[4]/total_votos)*100,lista_votos_candidatos[4]); asteriscos((lista_votos_candidatos[4]/total_votos)*50); printf("\n\n");
    printf("Juan Carlos Guitierrez Arias:\t\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[5]/total_votos)*100,lista_votos_candidatos[5]); asteriscos((lista_votos_candidatos[5]/total_votos)*50); printf("\n\n");
    printf("Voto en blanco:\t\t\t\t"); printf("%.1f %%\t\t\t%i\t",(lista_votos_candidatos[6]/total_votos)*100,lista_votos_candidatos[6]); asteriscos((lista_votos_candidatos[6]/total_votos)*50); printf("\n\n");

    printf("\n\n");

    system("pause");

}

int total_tipo_usuario(char tipo_usuario[20]){
    FILE *archivo_registro;

    int total_votos=0;

    archivo_registro=fopen("registro_voto.txt","r");

    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {
        if (strcmp(registro_voto.tipo_usuario,tipo_usuario)==0)
        {
            total_votos+=1;
        }
    }

    fclose(archivo_registro);

    return total_votos;
}

float tipo_usuario_formula(char tipo_usuario[20],int numeral_candidato){
    FILE *archivo_registro;

    float total_votos=0;

    float total_tipo_candidato=0;

    archivo_registro=fopen("registro_voto.txt","r");

    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {
        if (strcmp(registro_voto.tipo_usuario,tipo_usuario)==0)
        {
            total_votos+=1;
            if (registro_voto.numero_candidato_votado==numeral_candidato)
            {
                total_tipo_candidato+=1;
            }
            
        }


    }

    fclose(archivo_registro);

    return (total_tipo_candidato/total_votos);
}

int total_votos_candidato(int numeral_candidato){
    FILE *archivo_registro;

    int total_votos=0;

    archivo_registro=fopen("registro_voto.txt","r");

    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {
        if (registro_voto.numero_candidato_votado==numeral_candidato)
        {
            total_votos+=1;
        }
    }

    fclose(archivo_registro);

    return total_votos;

}

float formula(int numeral_candidato){
    float resultado_formula=0;
    resultado_formula=((tipo_usuario_formula("Docente",numeral_candidato))*40)+((tipo_usuario_formula("Estudiante",numeral_candidato))*35)+((tipo_usuario_formula("Administrativo",numeral_candidato))*10)+((tipo_usuario_formula("Egresado",numeral_candidato))*15);
    return resultado_formula;
}

void candidatos_tabla(int numeral_candidato){
    FILE *archivo_candidatos;
    FILE *archivo_registro;

    int numero_votos_docente=0;
    int numero_votos_estudiante=0;
    int numero_votos_administrativo=0;
    int numero_votos_egresado=0;

    float porcentaje=0;


    char nombre_candidato[50];

    archivo_registro=fopen("registro_voto.txt","r");

    while (fread(&registro_voto,sizeof(registro_voto),1,archivo_registro)==1)
    {
        if (registro_voto.numero_candidato_votado==numeral_candidato)
        {
            if (strcmp(registro_voto.tipo_usuario,"Docente")==0)
            {
                numero_votos_docente+=1;
            }
            else if (strcmp(registro_voto.tipo_usuario,"Estudiante")==0)
            {
                numero_votos_estudiante+=1;
            }
            else if (strcmp(registro_voto.tipo_usuario,"Administrativo")==0)
            {
                numero_votos_administrativo+=1;
            }
            else if (strcmp(registro_voto.tipo_usuario,"Egresado")==0)
            {
                numero_votos_egresado+=1;
            }
        }
    }

    fclose(archivo_registro);    

    archivo_candidatos=fopen("candidatos.txt","r");

    while (fread(&candidato,sizeof(candidato),1,archivo_candidatos)==1)
    {
        if (candidato.numero_candidato==numeral_candidato)
        {
            strcpy(nombre_candidato,candidato.nombre);
        }
    }

    fclose(archivo_candidatos);
    printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    if (numeral_candidato==3||numeral_candidato==7)
    {
        if (numeral_candidato==3)
        {
            printf("|%s\t\t|\t%i\t\t|\t%i\t\t|\t\t%i\t\t|\t%i\t\t|\t%i\t|\t%.2f %%\t\t|\n",nombre_candidato,numero_votos_docente,numero_votos_estudiante,numero_votos_administrativo,numero_votos_egresado,numero_votos_docente+numero_votos_estudiante+numero_votos_administrativo+numero_votos_egresado,formula(numeral_candidato));   
        }
        else if (numeral_candidato==7)
        {
            printf("|%s\t\t\t|\t%i\t\t|\t%i\t\t|\t\t%i\t\t|\t%i\t\t|\t%i\t|\t%.2f %%\t\t|\n",nombre_candidato,numero_votos_docente,numero_votos_estudiante,numero_votos_administrativo,numero_votos_egresado,numero_votos_docente+numero_votos_estudiante+numero_votos_administrativo+numero_votos_egresado,formula(numeral_candidato));
        }
        
    }
    else
    {
        printf("|%s\t|\t%i\t\t|\t%i\t\t|\t\t%i\t\t|\t%i\t\t|\t%i\t|\t%.2f %%\t\t|\n",nombre_candidato,numero_votos_docente,numero_votos_estudiante,numero_votos_administrativo,numero_votos_egresado,numero_votos_docente+numero_votos_estudiante+numero_votos_administrativo+numero_votos_egresado,formula(numeral_candidato));
    }
    
    
}

void tabla(){
    printf(" ______________________________________________________________________________________________________________________________________________________________________________\n");
    printf("|\t  CANDIDATOS\t\t|\tDOCENTES 40%%\t|\tESTUDIANTES 35%%\t|\tADMINISTRATIVO 10%%\t|\tEGRESADO 15%%\t|\tTOTALES\t|\tRESULTADOS\t|\n");
    candidatos_tabla(1);
    candidatos_tabla(2);
    candidatos_tabla(3);
    candidatos_tabla(4);
    candidatos_tabla(5);
    candidatos_tabla(6);
    candidatos_tabla(7);
    printf(" _______________________________________________________________________________________________________________________________________________________________________________\n");
    printf("|\tTOTALES\t\t\t|\t%i\t\t|\t%i\t\t|\t\t%i\t\t|\t%i\t\t|\t%i\t|\t100 %%\t\t|",total_tipo_usuario("Docente"),total_tipo_usuario("Estudiante"),total_tipo_usuario("Administrativo"),total_tipo_usuario("Egresado"),total_votos_candidato(1)+total_votos_candidato(2)+total_votos_candidato(3)+total_votos_candidato(4)+total_votos_candidato(5)+total_votos_candidato(6));
    printf("\n -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    system("pause");
}