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
FILE *admin_user;

int n;

admin_user=fopen("user_admin.txt","r");

if (login_admin(admin_user)=='t')
{
    printf("hola");
}
else
{
    printf("Sistema Finalizado!");
    return 0;
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
        printf("Digite el usuario: "); scanf("%s",&try_admin);
        printf("Digite la contraseña: "); scanf("%s",&try_password);

        fread(&admin,sizeof(admin),1,admin_user);

        if ((strcmp(admin.name,try_admin)==0)&&(strcmp(admin.password,try_password)==0))
        {
            printf("Sesion iniciada!\n");
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

