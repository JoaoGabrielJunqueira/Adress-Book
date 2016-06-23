#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int DetectaSistemaOperacional() 
/*Se o SO for Linux retorna 0, caso seja Windows retorna 1. 
  Usada para casos de definição de métodos exclusivos do SO como system("cls") no Windows ou system("clear") no Linux.*/
{
	#ifdef __APPLE__
		return 0;
	#elif defined __linux__
		return 0;
	#elif defined WIN32
		return 1;
	#else
		return 2;
	#endif
}

int QuantidadeContatos(char *nome_arquivo) //Retorna quantidade de contatos inseridos no arquivo
{
	FILE *arquivo;
	char *result, linha[100];
	int qt_contato = 0;
	
	arquivo = fopen(nome_arquivo, "rt");	
	
	while (!feof(arquivo))
	{
		result = fgets(linha,100,arquivo);
		if (result)
			qt_contato++;
	}
	fclose(arquivo);
	
	return qt_contato;
}

int CodigoContatoValido(int cd_contato, int qt_contato) //Retorna se o usúario escolheu um número de contato válido
{
	if (cd_contato > 0 && cd_contato <= qt_contato)
		return 1;
	else
		return 0;
}

void AdicionaContato() //Adiciona contato no arquivo
{
	FILE *arquivo;
	char nm_contato[99], cd_telefone[15], nm_email[55];

	arquivo = fopen("Agenda.txt", "a");
	if(arquivo == NULL)
		arquivo = fopen("Agenda.txt", "wt");
	else
		arquivo = fopen("Agenda.txt", "a");

	printf("\n\t\tNome: ");
	scanf("%s",nm_contato);

	printf("\t\tTelefone: ");
	scanf("%s",cd_telefone);

	printf("\t\tEmail: ");
	scanf("%s",nm_email);
	
	strcat(nm_contato," ");
	strcat(cd_telefone," ");
	strcat(nm_email,"\n");

	fputs(nm_contato,arquivo);
	fputs(cd_telefone,arquivo);
	fputs(nm_email,arquivo);

	fclose(arquivo);

	printf("\n\t\tContato adicionado com sucesso!");
	printf("\n\n\t\tAperte qualquer tecla para voltar...");
	
	if (DetectaSistemaOperacional() == 0)
		system("read b");
	else
		getchar();
}

void ListarContatos() //Exibe os contatos cadastrados
{
	FILE *agenda;
	char nm_contato[99], cd_telefone[15], nm_email[55];
	int cd_contato = 0, qt_contato;

	qt_contato = QuantidadeContatos("Agenda.txt");
	
	agenda = fopen("Agenda.txt", "rt");
	
	if (agenda == NULL)
		printf("\n\t\tArquivo Agenda.txt nao encontrado.");
	else
		{
			printf("\n");
			
			if (qt_contato > 0)
			{
				while (!feof(agenda))
				{
					fscanf(agenda,"%s %s %s ", nm_contato, cd_telefone, nm_email);
					cd_contato++;
					printf("  %d - Nome: %s  -  Telefone: %s  -  Email: %s\n", cd_contato, nm_contato, cd_telefone, nm_email);
				}
			}
			else
				printf("  Nenhum contato inserido.");

			fclose(agenda);
		}
	
	if (DetectaSistemaOperacional() == 0)
		system("read b");
	else
		getchar();
}

void AlterarContato() //Altera as informações de um contato
{
    FILE *agenda, *temporario;
	char nm_contato[99], cd_telefone[15], nm_email[55];
    int cd_contato, i = 1, qt_contato;
	
	qt_contato = QuantidadeContatos("Agenda.txt");
	
	if (qt_contato > 0)
	{
		ListarContatos();

		printf("\n  Digite o numero do contato a ser alterado: ");
		scanf("%d",&cd_contato);
		
		if (CodigoContatoValido(cd_contato, qt_contato) == 1)
		{

			temporario = fopen("Temporario.txt", "wt");
			agenda = fopen("Agenda.txt", "rt");
	
			if (agenda == NULL)
				printf("\n\t\tArquivo Agenda.txt nao encontrado.");
			else
			{
				while (!feof(agenda))
				{
					fscanf(agenda,"%s %s %s ", nm_contato, cd_telefone, nm_email);
					
					if (i != cd_contato)
					{
						strcat(nm_contato," ");
						strcat(cd_telefone," ");
						strcat(nm_email,"\n");

						fputs(nm_contato,temporario);
						fputs(cd_telefone,temporario);
						fputs(nm_email,temporario);
					}
					else
						{
							printf("\n  Novo nome: ");
							scanf("%s",nm_contato);

							printf("  Novo telefone: ");
							scanf("%s",cd_telefone);

							printf("  Novo email: ");
							scanf("%s",nm_email);

							strcat(nm_contato," ");
							strcat(cd_telefone," ");
							strcat(nm_email,"\n");

							fputs(nm_contato,temporario);
							fputs(cd_telefone,temporario);
							fputs(nm_email,temporario);
						}
					i++;
				}
				
				fclose(agenda);
				fclose(temporario);
				
				temporario = fopen("Temporario.txt", "rt");
				agenda = fopen("Agenda.txt", "wt");

				while (!feof(temporario))
				{
					fscanf(temporario,"%s %s %s ", nm_contato, cd_telefone, nm_email);
					
					strcat(nm_contato," ");
					strcat(cd_telefone," ");
					strcat(nm_email,"\n");

					fputs(nm_contato,agenda);
					fputs(cd_telefone,agenda);
					fputs(nm_email,agenda);
				}
				
				fclose(temporario);
				fclose(agenda);
			}

			printf("\n  Contato alterado com sucesso!");
		}
		else
			printf("\n  Codigo invalido\n");
	}
	else
		printf("\n  Nenhum contato inserido");
	
		printf("\n  Aperte qualquer tecla para voltar...");

	if (DetectaSistemaOperacional() == 0)
		system("read b");
	else
		getchar();
}

void ExcluirContato() //Exclui um contato
{
	FILE *agenda, *temporario;
	char nm_contato[99], cd_telefone[15], nm_email[55];
    int cd_contato, i = 1, qt_contato;
	
	qt_contato = QuantidadeContatos("Agenda.txt");
	
	if (qt_contato > 0)
	{
		ListarContatos();

		printf("\n  Digite o numero do contato a ser excluido: ");
		scanf("%d",&cd_contato);
		
		if (CodigoContatoValido(cd_contato, qt_contato) == 1)
		{
			temporario = fopen("Temporario.txt", "wt");
			agenda = fopen("Agenda.txt", "rt");
			
			while (!feof(agenda))
			{
				fscanf(agenda,"%s %s %s ", nm_contato, cd_telefone, nm_email);
				
				if (i != cd_contato)
				{
					strcat(nm_contato," ");
					strcat(cd_telefone," ");
					strcat(nm_email,"\n");

					fputs(nm_contato,temporario);
					fputs(cd_telefone,temporario);
					fputs(nm_email,temporario);
				}
				i++;
			}
			
			fclose(agenda);
			fclose(temporario);
			
			int qt_contato_temporario = QuantidadeContatos("Temporario.txt");
			
			if (qt_contato_temporario > 0)
			{
				temporario = fopen("Temporario.txt", "rt");
				agenda = fopen("Agenda.txt", "wt");

				while (!feof(temporario))
				{
					fscanf(temporario,"%s %s %s ", nm_contato, cd_telefone, nm_email);
					
					strcat(nm_contato," ");
					strcat(cd_telefone," ");
					strcat(nm_email,"\n");

					fputs(nm_contato,agenda);
					fputs(cd_telefone,agenda);
					fputs(nm_email,agenda);
				}
				
				fclose(temporario);
				fclose(agenda);
			}
			else
				{
					agenda = fopen("Agenda.txt", "wt");
					fclose(agenda);
				}
			
			printf("\n  Contato excluido com sucesso.");
		}
		else
			printf("Codigo invalido");
	}
	else
		printf("\n  Nenhum contato inserido");

	if (DetectaSistemaOperacional() == 0)
		system("read b");
	else
		getchar();
}

void Menu() //Exibe Menu
{
	int cd_opcao;
	do
	{
		if (DetectaSistemaOperacional() == 0)
			system("clear");
		else
			system("cls");
		
        printf("\n\n\t--------------------AGENDA--------------------\n");
		printf("\t");
        printf("\n\t\t1 - Listar Contatos     \t\t\n");
        printf("\t\t2 - Novo Contato\n");
        printf("\t\t3 - Alterar Contato\n");
        printf("\t\t4 - Excluir Contato\n");
        printf("\t\t5 - Sair\n");

		printf("\n\t\tDigite uma opcao: ");
		scanf("%d", &cd_opcao);

		switch(cd_opcao)
		{
			case 1:
				ListarContatos();
				getchar();
				break;
			case 2:
				AdicionaContato();
				break;
            case 3:
				AlterarContato();
				break;
			case 4:
				ExcluirContato();
				break;
			case 5:
				printf("\n\t\tThanks for using our services...\n");
				break;
			default:
				printf("\n\t\tOpcao invalida!");
				if (DetectaSistemaOperacional() == 0)
					system("read b");
				else
					getchar();
		}
	}while (cd_opcao != 5);
}

int main()
{
	Menu();

	return(0);

	exit(0);
}
