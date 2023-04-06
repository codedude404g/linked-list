/**** This is the Mic-1 linker ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADERS         1
#define NO_HEADERS      0

typedef struct nament{
        char   name[26];
        int    addr;
        struct nament *next;
}SYMTABENTRY;


void  add_symbol(char * symbol, int line_number);
void  generate_code(FILE *fp);
void  print_first_pass(FILE *fp);
//void  append_table(void);
void  dump_table(void);
int   search_table(char *symbol);
void  print_binary_num(FILE * fp, int num, int digit);

SYMTABENTRY *symtab = NULL;
FILE  *p1, *p2;
char  cstr_12[13];

int main(int argc, char *argv[])
{
	int  i, start, pc_offset=0, pc=0;
	int  linum=0, object_file=0, dump_tab=0;
        int  line_number, new_pc;
	char instruction[18];
	char symbol[26];

/***
	for(i=0; i<argc; i++){
	  printf("arg %d is %s\n", i, argv[i]);
	}
***/

        if(argc > 1 && (strcmp(argv[1], "-s") == 0)) dump_tab = linum = 1;
        else if(argc > 1 && (strcmp(argv[1], "-o") == 0)) object_file = 1;

	if(dump_tab == 1 || object_file == 1)start=2;
	else start = 1; 

	p1 = fopen("/tmp/passone", "w+");
        unlink("/tmp/passone");

	for(i=start; i<argc; ++i){
		if((p2 = fopen(argv[i], "r")) == NULL){
		  printf("ERROR: cannot open file %s\n", argv[i]);
		  exit(6);
		}
		while(fscanf(p2,"%d %s", &pc, instruction) != EOF){
		  if(pc == 4096)break;
		  new_pc = pc + pc_offset;
		  symbol[0] = '\0';
		  if(instruction[0] == 'U'){
            	    fscanf(p2, "%s", symbol);
		  }
		  fprintf(p1, "  %d  %s  %s\n", new_pc, instruction, symbol);
		}
		while(fscanf(p2,"%s %d",symbol, &line_number) != EOF){
		  add_symbol(symbol, line_number+pc_offset);
		}
		pc_offset = new_pc + 1;
		fclose(p2);
	}

	if (object_file == 1)
		print_first_pass(p1);
	else
		generate_code(p1);

	return 0;
}

void add_symbol(char * symbol, int pc){
 	SYMTABENTRY * STE = (SYMTABENTRY *)malloc(sizeof(SYMTABENTRY));
	strcpy(STE->name, symbol);
	STE->addr = pc;
	STE->next = symtab;
	symtab = STE;
	return;
}

void  print_first_pass(FILE *fp)
{
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp))
	{
		printf("%c", fgetc(fp));
	}

	printf("4096 x");

	dump_table();

	return;
}

void  dump_table(void)
{
	SYMTABENTRY * STE = NULL;

	for (STE = symtab; STE != NULL; STE = STE->next)
	{
		printf("%-26s %d\n", STE->name, STE->addr);
	}

	return;
}

int search_table(char *symbol)
{
	SYMTABENTRY * STE = NULL;

	for (STE = symtab; STE != NULL; STE = STE->next)
        {
        	if (strlen(symbol) == strlen(STE->name))
			if (strcmp(symbol, STE->name) == 0)
				return STE->addr;
        }

        return -1;
}

void print_binary_num(FILE *fp, int num, int digit)
{
	int toPrint = num % 2;

	if ( digit > 0 )
	{
		print_binary_num(fp, num / 2, digit - 1);
		fprintf(fp, "%d", toPrint);
	}
	return;
}

void generate_code(FILE *fp)
{
        char instruction[18];
        char symbol[26];
	int pc = 0;

	fseek(fp, 0, SEEK_SET);
	
	while(fscanf(fp,"%d %s", &pc, instruction) != EOF)
	{
                  if(pc == 4096)break;
                  symbol[0] = '\0';
                  if(instruction[0] == 'U')
		  {
                    	fscanf(fp, "%s", symbol);
			int addr = search_table(symbol);
			instruction[5] = '\0'; // force %s to stop after 4 chars
			fprintf(stdout, "%s", instruction + 1); // start printing at instruction[1], skipping 'U'
			print_binary_num(stdout, addr, 12);
			fprintf(stdout, "\n");
                  }
		  else
		  {
                  	fprintf(stdout, "%s\n", instruction);
		  }
        }

	return;
}
