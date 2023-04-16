#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int pid;

void traite_octet(unsigned char c, int courant)
{
	static int nb_bons = 0;
			if (nb_bons == 0 && c=='P')
				nb_bons++;
			else if (nb_bons == 1 && c=='l')
				nb_bons++;
			else if (nb_bons == 2 && c=='a')
				nb_bons++;
			else if (nb_bons == 3 && c=='y')
				nb_bons++;
			else if (nb_bons == 4 && c=='e')
				nb_bons++;
			else if (nb_bons == 5 && c=='r')
			{
				unsigned long a;
				a=ptrace(PTRACE_PEEKDATA,pid,(void *) (courant-1),NULL);
				printf("mot=%lx\n",a);
				a&=0xFFFFFF00;
				a|=0x00000066;
				ptrace(PTRACE_POKEDATA,pid,(void *) (courant-1),&a);
/*				fseek(fichier,-1,SEEK_CUR);
				fputc('R',fichier);*/
				nb_bons=0;
			}
			else
				nb_bons=0;

}



int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	FILE *fichier;
	FILE *map;

	pid = atoi(argv[1]);
	char nom[15];
	ptrace(PTRACE_ATTACH,pid,NULL,NULL);
	sprintf(nom,"/proc/%d/mem",pid);
	fichier = fopen(nom,"rw");
	sprintf(nom,"/proc/%d/maps",pid);
	map = fopen(nom,"r");
	if (fichier == NULL || map == NULL)
	{
		printf("aie\n");
		return 1;
	}
	unsigned int a;
	unsigned int courant = 0;
	unsigned int nb = 0;
	int fin = 0;
	char s[500];
	int nb_bons = 0;
	while (fgets(s,500,map))
	{
		sscanf(s,"%8x-%8x",&courant,&fin);
		fseek(fichier, courant, SEEK_SET);
		while(courant < fin)
		{
			a=ptrace(PTRACE_PEEKDATA,pid,courant,NULL);
			traite_octet(a&0xFF,courant);
			traite_octet((a>>8)&0xFF,courant+1);
			traite_octet((a>>16)&0xFF,courant+2);
			traite_octet((a>>24)&0xFF,courant+3);
	
			courant+=4;
			nb++;
		}
	}
	printf("%d evalues\n", nb);
	fclose(fichier);
	fclose(map);
	return 0;

}
