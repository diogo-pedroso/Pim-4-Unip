#include<stdio.h>
#include<string.h>

int login(){

    char login[20];

    printf("Digite o login: ");
    scanf("%s",login);

    char senha[15];

    printf("Digite a senha: ");
    scanf("%s", senha);

    if(strcmp(login,"uns_covid") == 0){
        if(strcmp(senha,"123456789") == 0){
            printf("Acesso Liberado \n");
            return 1;
        } else {
            printf("Senha incorreta \n");

        }

    } else {
        printf("O login esta incorreto \n");

    }

    return 0;
}

int main(){
    while(login() == 0){}

}
