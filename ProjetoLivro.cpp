#include <iostream>
#include <cstring>
using namespace std;

struct Livros{
    char livro[100];
    char autor[100];
    int pagina;
    int publicacao;
    int id;
    int estoque;
    int emprestimo;
    char nomeExemplar[100][100];
};
void CadastrarLivro (struct Livros livro[], int &tam)
{
    if(tam>100)
    {
        cout<<"Quantidade de livros cadastrados excedido!";
        return;
    }
    else
    {
        cout<<"Título do livro: ";
        cin.ignore(); 
        cin.getline(livro[tam].livro, 100);  
        
        cout<<"Autor do livro: ";
        cin.getline(livro[tam].autor, 100);  

        cout<<"Páginas do livro: ";
        cin>>livro[tam].pagina;
        
        cout<<"Ano de publicação: ";
        cin>>livro[tam].publicacao;
        
        cout<<"ID do livro: ";
        cin>>livro[tam].id;
        
        cout<<"Quantidade em estoque: ";
        cin>>livro[tam].estoque;
        
        livro[tam].emprestimo = 0;
        tam++;
    }
}

void ConsultarLivro(struct Livros livro[], int tam)
{
    int opcao;
    cout<<"1 - Listar todos os livros cadastrados"<<endl;
    cout<<"2 - Buscar um livro por ID ou título"<<endl;
    cout<<"Escolha um opção: ";
    cin>>opcao;
    
    if(opcao==1)
    {
        for(int i=0; i<tam; i++)
        {
            cout<<endl;
            cout<<"Título do livro: "<<livro[i].livro<<endl;
            cout<<"Autor do livro: "<<livro[i].autor<<endl;
            cout<<"Páginas do livro: "<<livro[i].pagina<<endl;
            cout<<"Ano de publicação: "<<livro[i].publicacao<<endl;
            cout<<"ID do livro: "<<livro[i].id<<endl;
            cout<<"Quantidade em estoque: "<<livro[i].estoque<<endl;
            if(livro[i].emprestimo>0)
            {
                cout<<"Emprestado por: ";
                for(int j=0; j<livro[i].emprestimo; j++)
                {
                    cout<<livro[i].nomeExemplar[j];
                    if(j<livro[i].emprestimo-1)
                    {
                        cout<<", ";
                    }
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
    else if(opcao==2)
    {
        int resp, idConsul;
        char tituloConsul[100];
        cout<<"1- ID\n2-Titulo"<<endl;
        cout<<"Deseja buscar o livro por: ";
        cin>>resp;
        
        if(resp==1)
        {
            cout<<"Informe o ID do livro: ";
            cin>>idConsul;
            for(int i=0; i<tam; i++)
            {
                if(livro[i].id==idConsul)
                {
                    cout<<endl;
                    cout<<"Título do livro: "<<livro[i].livro<<endl;
                    cout<<"Autor do livro: "<<livro[i].autor<<endl;
                    cout<<"Páginas do livro: "<<livro[i].pagina<<endl;
                    cout<<"Ano de publicação: "<<livro[i].publicacao<<endl;
                    cout<<"ID do livro: "<<livro[i].id<<endl;
                    cout<<"Quantidade em estoque: "<<livro[i].estoque<<endl;
                    cout<<endl;
                }
            }
        }
        
        else if(resp==2)
        {
            cout<<"Informe o título do livro: ";
            cin.ignore(); 
            cin.getline(tituloConsul, 100); 
            for(int i=0; i<tam; i++)
            {
                if(strcmp(livro[i].livro, tituloConsul) == 0)
                {
                    cout<<endl;
                    cout<<"Título do livro: "<<livro[i].livro<<endl;
                    cout<<"Autor do livro: "<<livro[i].autor<<endl;
                    cout<<"Páginas do livro: "<<livro[i].pagina<<endl;
                    cout<<"Ano de publicação: "<<livro[i].publicacao<<endl;
                    cout<<"ID do livro: "<<livro[i].id<<endl;
                    cout<<"Quantidade em estoque: "<<livro[i].estoque<<endl;
                    cout<<endl;
                }
            }
        }
    }
}

void EmprestimoLivro (struct Livros livro[], int tam)
{
    int id;
    char pessoa[50];
    cout<<"Digite o ID do livro que deseja emprestar: ";
    cin>>id;
    
    cout<<"Digite o nome da pessoa que irá emprestar: ";
    cin.ignore();
    cin.getline(pessoa,50);
    
    for(int i=0; i<tam; i++)
    {
        if(livro[i].id==id)
        {
            if(livro[i].estoque>0)
            {
                livro[i].estoque--;
                strcpy(livro[i].nomeExemplar[livro[i].emprestimo], pessoa);
                livro[i].emprestimo++;
                cout<<"Livro emprestado com sucesso!"<<endl;
                return;
            }
            else
            {
                cout<<"Livro não dísponivel para empréstimo!"<<endl;
                return;
            }
        }
    }
    cout<<"Livro não encontrado!"<<endl;
}

void DevolucaoLivro (struct Livros livro[], int tam)
{
    int id;
    char pessoa[50];
    cout<<"Digite o ID do livro que deseja devolver: ";
    cin>>id;
    
    cout<<"Digite o nome da pessoa que irá devolver: ";
    cin.ignore();
    cin.getline(pessoa,50);
    
    for(int i=0; i<tam; i++)
    {
        if(livro[i].id==id)
        {
            for(int j=0; j<livro[i].emprestimo; j++)
            {
                if(strcmp(livro[i].nomeExemplar[j], pessoa)==0)
                {
                    livro[i].estoque++;
                    for(int k=j; k<livro[i].emprestimo-1;k++)
                    {
                        strcpy(livro[i].nomeExemplar[k], livro[i].nomeExemplar[k+1]);
                    }
                    livro[i].emprestimo--;
                    cout<<"Livro devolvido com sucesso!"<<endl;
                    return;
                }
            }
            cout<<"Nome não encontrado na lista de empréstimos!";
            return;
        }
    }
    cout<<"Livro não encontrado!"<<endl;
}

void RemocaoLivro (struct Livros livro[], int &tam)
{
    int resp;
    cout<<"Digite o ID do livro que deseja remover o cadastro: ";
    cin>>resp;
    for(int i=0; i<tam; i++)
    {
        if(livro[i].id==resp)
        {
            for(int j=i; j<tam-1; j++)
            {
                livro[j]=livro[j+1];
            }
            tam--;
            cout<<"Livro removido com sucesso!"<<endl;
            return;
        }
    }
    cout<<"Livro não encontrado!"<<endl;
}

int main()
{
    const int max=100;
    Livros livro[max];
    int tam=0, opcao=0;
    
    while(opcao != 6)
    {
        cout<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"1 - Cadastrar Livro"<<endl;
        cout<<"2 - Consultar Livro"<<endl;
        cout<<"3 - Empréstimo do Livro"<<endl;
        cout<<"4 - Devolução do Livro"<<endl;
        cout<<"5 - Remover Livro"<<endl;
        cout<<"6 - Sair"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Escolha uma opcao: ";
        cin>>opcao;
        cout<<endl;
    
        switch (opcao)
        {
            case 1: CadastrarLivro(livro, tam);
            break;
            case 2: ConsultarLivro(livro, tam);
            break;
            case 3: EmprestimoLivro(livro, tam);
            break;
            case 4: DevolucaoLivro(livro, tam);
            break;
            case 5: RemocaoLivro(livro, tam);
            break;
        }
            
    }
    return 0;
}
