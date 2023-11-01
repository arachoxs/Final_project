#include <stdio.h>
#include <string.h>
#include <windows.h>

struct
{
    char name[20];
    char password[20];
}admin;

char login_admin(FILE *admin);


int main(){
//inicio del file
FILE *admin_user;

int opcion_menu;

char login_succesful=login_admin(admin_user);

while (login_succesful=='t')
{
    printf("----Menu----\n\n");
    printf("1.Ingresar candidatos\n2.Ingresar usuarios\n0.salir\n\n"); 
    printf("Digite la opcion a accerder: "); scanf("%i",&opcion_menu);
}


    return 0;
}



char login_admin(FILE *admin_user){
    char band='f';
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

