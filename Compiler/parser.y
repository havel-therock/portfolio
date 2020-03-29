%{
    // change int ot long long
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <map>
    #include <vector>
    #include <algorithm>
    #include <queue>
    #include <iostream>
    #include <fstream>

    using namespace std;
    
    extern FILE *yyin;
    ofstream outfile;
    //extern FILE *yyout;
    //?
// Lex stuff
    int yylex(void);
    void yyerror(const char*);
    extern int linum;
    int one_place = 10;
    int minus_one_place = 9;
    int next_free_address = 8;
    

//Memory    
    // 0 - not usable 
    // 1-10 - register like for operations 
    // in 10 always value 1
    // in 9 always value -1 
    // 11-? - iterators then variables then arrays in memory
    unsigned long long memory_counter = 11;
    map<string, struct iter_for*> iter_memory_map;
    map<string, unsigned long long> vars_memory_map;
    map<string, struct array_prop*> arrays_memory_map;
    
    queue<struct three_address_code*> tacodes;

    vector<string> asm_instructions;
    long long asm_lineno = 0;

    map<string, string> jumps; //index = number of label to jump to || value = jump type [JUMP, Jneg, Jpos, Jzero]
    map<string, int> labels; //index = number of label || value = number of line where the label stand (asm_lineno)

// distinct number for label generation
    long long label_number;

    struct array_prop{
        long long min_index;
        long long max_index;
        unsigned long long first_element_addr;
    };
    struct array_prop* newArrayProp(long long min_index, long long max_index, unsigned long long first_element_addr);

// Lex token
    struct token {
        string name;
        long long number_value;
        int linum;
    };
    struct token* newToken(string name, long long number_value, int linum);

// Abstract syntax tree
    struct ast {
        struct ast* node1;
        struct ast* node2;
        struct ast* node3;
        struct ast* node4;
        string type; // rule that match tokens eg. program, expression

        string name; // terminal (pid) name of token. Non-terminal name of subrule. 
        long long number_value; // value of NUM token 
        int linum;
        
    };
    struct ast* newSubtree(string type, struct ast* node1, struct ast* node2, struct ast* node3, struct ast* node4, string name, long long number_value, int linum);

//Semantic analysis 
    void semanticAnalysis(struct ast* root); // main function that runs all the other semantic functions
    void iteratorsMemoryReservation(vector<string> iterators, struct ast* root); // 
    void memoryReservation(struct ast* root); // variables + arrays reservations
    void checkProperVariableUsage(struct ast* root); // array out of bounds + undeclared variables
    void checkVariablesInit(vector<string> &initialized, struct ast* root); // go through ast and check for usage of uninitilize variables

    struct iter_for{
        unsigned long long memory_index;
        bool visibility;
    };

    struct iter_for* newIterFor(unsigned long long memory_index, bool visibility);
    void set_visibility(struct iter_for*, bool visibility);
// Three Address Code
    enum instruction { PLUS2, MINUS2, TIMES2, DIV2, MOD2, DEC2, INC2, 
                       LOAD2, STORE2, LOADI, STOREI, LOADNEXT2, STORENEXT2, 
                       JUMP2, JPOS2, JZERO2, JNEG2, 
                       READ2, WRITE2, 
                       HALT2, 
                       LABEL2};

    struct tac_argument {
        string type; // [ITER, VAR, ARR_VAR, ARR_NUM, NUM, LAB]
        string name;
        string array_index;
        long long num_value;
    };
    struct tac_argument* newTacArg(string type, string name, string array_index, long long num_value);

    struct three_address_code {
        enum instruction instr;
        struct tac_argument* arg1;
        struct tac_argument* arg2;
    };
    struct three_address_code* newTac(enum instruction instr, struct tac_argument* arg1, struct tac_argument* arg2);

    void generateTAC(struct ast* root);
    void genTACCommands(struct ast* commands_node);

    void genTACCommand(struct ast* command_node);
    void genTACAssign(struct ast* assign_node);
    void genTACIfelse(struct ast* ifelse_node);
    void genTACIf(struct ast* if_node);
    void genTACWhile(struct ast* while_node);
    void genTACDowhile(struct ast* dowhile_node);
    void genTACFor(struct ast* for_node);
    void genTACFordown(struct ast* fordown_node);
    void genTACRead(struct ast* read_node);
    void genTACWrite(struct ast* write_node);

    void genTACExpression(struct ast* expression_node);
    void genTACValue(struct ast* value_node);
    void genTACPlus(struct ast* plus_node);
    void genTACMinus(struct ast* minus_node);
    void genTACTimes(struct ast* times_node);
    void genTACDiv(struct ast* div_node);
    void genTACMod(struct ast* mod_node);

    void genTACCondition(struct ast* condition_node, struct tac_argument* label_start, struct tac_argument* label_end);
    void genTACEq(struct ast* eq_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACNeq(struct ast* neq_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACLe(struct ast* le_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACGe(struct ast* ge_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACLeq(struct ast* leq_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACGeq(struct ast* geq_node, struct tac_argument* true_l, struct tac_argument* false_l);

    struct tac_argument* genTACArgument(struct ast* value_node);

// generate asm
    void genASM();
    void genASMPlus(struct three_address_code* code);
    void genASMMinus(struct three_address_code* code);
    void genASMINC(struct three_address_code* code);
    void genASMDEC(struct three_address_code* code);
    void genASMTimes(struct three_address_code* code);
    void genASMDiv(struct three_address_code* code);
    void genASMMod(struct three_address_code* code);
    void genASMLoad(struct three_address_code* code);
    void genASMLoadNext(struct three_address_code* code);
    void genASMStore(struct three_address_code* code);
    void genASMStoreNext(struct three_address_code* code); 
    void genASMJump(struct three_address_code* code);
    void genASMJpos(struct three_address_code* code);
    void genASMJzero(struct three_address_code* code);
    void genASMJneg(struct three_address_code* code);
    void genASMRead(struct three_address_code* code);
    void genASMWrite(struct three_address_code* code);
    void genASMHalt(struct three_address_code* code);
    void genASMLabel(struct three_address_code* code);

    void genASMConst(long long const_value);

    void genASMParityVector(struct tac_argument* arg);
    void genASMCheckParity(unsigned long long mem_cell);
    
    void loadArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell);
    void loadNextArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell);

    void asmStoreHelp(struct tac_argument* arg); // use memory cell 1, 2
    void asmStoreHelpNext(struct tac_argument* arg); // use memory cell 1, 2
// label generator
    struct tac_argument* newLabel(); 
//utils 
    void printTACQueue();
    void printTAC(struct three_address_code* root);
    void printTACArgument(struct tac_argument* arg);

    void preProcess();

%}

%define parse.error verbose

%union {
    struct token* token;
    struct ast* tree;
}

%token <token> PLUS MINUS DIV TIMES MOD
%token <token> EQ NEQ LE GE LEQ GEQ
%token <token> DECLARE BEGIN2 ASSIGN THEN ELSE ENDIF ENDWHILE WHILE ENDDO FOR DO IF END FROM TO ENDFOR READ WRITE DOWNTO
%token <token> ';' ':' '(' ')' ','
%token <token> PID NUM

%type <tree> program
%type <tree> declarations
%type <tree> commands
%type <tree> command
%type <tree> expression 
%type <tree> condition
%type <tree> value 
%type <tree> identifier

%%

program:  
    DECLARE declarations BEGIN2 commands END {
        $$ = newSubtree("program", $2, $4, NULL, NULL, "", 0, $1->linum);
        semanticAnalysis($$);
        generateTAC($$);
        //printTACQueue();
        genASM();
};

declarations: 
    declarations',' PID {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, $3->name, 0, $3->linum);
        $$ = newSubtree("declarations", $1, leaf, NULL, NULL, "decPID", 0, $3->linum);
    }

|   declarations',' PID'('NUM':'NUM')'{
        struct ast* leaf1 = newSubtree("PID", NULL, NULL, NULL, NULL, $3->name, 0, $3->linum);
        struct ast* leaf2 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", $5->number_value, $5->linum);
        struct ast* leaf3 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", $7->number_value, $7->linum);
        $$ = newSubtree("declarations", $1, leaf1, leaf2, leaf3, "decARR", 0, $3->linum);
    }
|
    PID {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, $1->name, 0, $1->linum);
        $$ = newSubtree("declarations", NULL, leaf, NULL, NULL, "decPID", 0, $1->linum);
    }
|
    PID'('NUM':'NUM')'{
        struct ast* leaf1 = newSubtree("PID", NULL, NULL, NULL, NULL, $1->name, 0, $1->linum);
        struct ast* leaf2 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", $3->number_value, $3->linum);
        struct ast* leaf3 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", $5->number_value, $5->linum);
        $$ = newSubtree("declarations", NULL, leaf1, leaf2, leaf3, "decARR", 0, $1->linum);
    }
|
    {
        $$ = NULL;
    }
;

commands: 
    commands command {
        $$ = newSubtree("commands", $1, $2, NULL, NULL, "", 0, $2->linum);
    }
|
    {
        $$ = NULL;
    }
;

command: 
    identifier ASSIGN expression';' {
        $$ = newSubtree("command", $1, $3, NULL, NULL, "ASSIGN", 0, $2->linum);
    }
|
    IF condition THEN commands ELSE commands ENDIF {
        $$ = newSubtree("command", $2, $4, $6, NULL, "IFELSE", 0, $1->linum);
    }
|
    IF condition THEN commands ENDIF {
        $$ = newSubtree("command", $2, $4, NULL, NULL, "IF", 0, $1->linum);
    }
|
    WHILE condition DO commands ENDWHILE {
        $$ = newSubtree("command", $2, $4, NULL, NULL, "WHILE", 0, $1->linum);
    }
|
    DO commands WHILE condition ENDDO {
        $$ = newSubtree("command", $2, $4, NULL, NULL, "DOWHILE", 0, $1->linum);
    }
|
    FOR PID FROM value TO value DO commands ENDFOR {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, $2->name, 0,$2->linum);
        $$ = newSubtree("command", leaf, $4, $6, $8, "UPFOR", 0, $1->linum);
    }
|
    FOR PID FROM value DOWNTO value DO commands ENDFOR {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, $2->name, 0,$2->linum);
        $$ = newSubtree("command", leaf, $4, $6, $8, "DOWNFOR", 0, $1->linum);
    }
|
    READ identifier';' {
        $$ = newSubtree("command", $2, NULL, NULL, NULL, "READ", 0, $1->linum);
    }
|
    WRITE value';' {
        $$ = newSubtree("command", $2, NULL, NULL, NULL, "WRITE", 0, $1->linum);
    }
;

expression: 
    value {
        $$ = newSubtree("expression", $1, NULL, NULL, NULL, "VALUE", 0, $1->linum);
    }
|
    value PLUS value {
        $$ = newSubtree("expression", $1, $3, NULL, NULL, "PLUS", 0, $1->linum);
    }
|
    value MINUS value {
        $$ = newSubtree("expression", $1, $3, NULL, NULL, "MINUS", 0, $1->linum);
    }
|
    value TIMES value {
        $$ = newSubtree("expression", $1, $3, NULL, NULL, "TIMES", 0, $1->linum);
    }
|
    value DIV value {
        $$ = newSubtree("expression", $1, $3, NULL, NULL, "DIV", 0, $1->linum);
    }
|
    value MOD value {
        $$ = newSubtree("expression", $1, $3, NULL, NULL, "MOD", 0, $1->linum);
    }
;

condition: 
    value EQ value {
        $$ = newSubtree("condition", $1, $3, NULL, NULL, "EQ", 0, $1->linum);
    }
|
    value NEQ value {
        $$ = newSubtree("condition", $1, $3, NULL, NULL, "NEQ", 0, $1->linum);
    }
|
    value LE value {
        $$ = newSubtree("condition", $1, $3, NULL, NULL, "LE", 0, $1->linum);
    }
|
    value GE value {
        $$ = newSubtree("condition", $1, $3, NULL, NULL, "GE", 0, $1->linum);
    }
|
    value LEQ value {
        $$ = newSubtree("condition", $1, $3, NULL, NULL, "LEQ", 0, $1->linum);
    }
|
    value GEQ value {
        $$ = newSubtree("condition", $1, $3, NULL, NULL, "GEQ", 0, $1->linum);
    }
;

value: 
    NUM {
        struct ast* leaf =  newSubtree("NUM", NULL, NULL, NULL, NULL, "", $1->number_value, $1->linum);
        $$ = newSubtree("value", leaf, NULL, NULL, NULL, "NUM", 0, $1->linum); 
    }
|
    identifier {
        $$ = newSubtree("value", $1, NULL, NULL, NULL, "IDENTIFIER", 0, $1->linum); 
    }
;
identifier: 
    PID {
        struct ast* leaf =  newSubtree("PID", NULL, NULL, NULL, NULL, $1->name, 0, $1->linum);
        $$ = newSubtree("identifier", leaf, NULL, NULL, NULL, "PID", 0, $1->linum); 
    }
|
    PID'('PID')' {
        struct ast* leaf1 =  newSubtree("PID", NULL, NULL, NULL, NULL, $1->name, 0, $1->linum);
        struct ast* leaf2 =  newSubtree("PID", NULL, NULL, NULL, NULL, $3->name, 0, $3->linum);
        $$ = newSubtree("identifier", leaf1, leaf2, NULL, NULL, "PIDPID", 0, $1->linum); 
    }
|
    PID'('NUM')' {
        struct ast* leaf1 =  newSubtree("PID", NULL, NULL, NULL, NULL, $1->name, 0, $1->linum);
        struct ast* leaf2 =  newSubtree("NUM", NULL, NULL, NULL, NULL, "", $3->number_value, $3->linum);
        $$ = newSubtree("identifier", leaf1, leaf2, NULL, NULL, "PIDNUM", 0, $1->linum); 
    }
;

%%


struct token* newToken(string name, long long number_value, int linum){
    struct token* nt = new token();//(struct token*) malloc(sizeof(struct token));
    if(!nt){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    if(!name.empty()){
        nt->name = name;
    }
    nt->number_value = number_value;
    nt->linum = linum;
    
    return nt;
}

struct ast* newSubtree(string type, struct ast* node1, struct ast* node2, struct ast* node3, struct ast* node4, string name, long long number_value, int linum){
    struct ast* nst = new ast();//(struct ast*) malloc(sizeof(struct ast));
    if(!nst){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    nst->type = type;
    nst->node1 = node1;
    nst->node2 = node2;
    nst->node3 = node3;
    nst->node4 = node4;
    if(!name.empty()){ // miss this maybe
        nst->name = name;
    }
    nst->number_value = number_value;
    nst->linum = linum;
    
    return nst;
}

void freeSubtree(struct ast* root){
    if(root == NULL)
        return;
    freeSubtree(root->node1);
    root->node1 = NULL;
    freeSubtree(root->node2);
    root->node2 = NULL;
    freeSubtree(root->node3);
    root->node3 = NULL;
    freeSubtree(root->node4);
    root->node4 = NULL;

    free(root);
    root = NULL;
}

struct array_prop* newArrayProp(long long min_index, long long max_index, unsigned long long first_element_addr){
    struct array_prop* ap = new array_prop();//(struct array_prop*) malloc(sizeof(struct array_prop));
    if(!ap){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    ap->min_index = min_index;
    ap->max_index = max_index;
    ap->first_element_addr = first_element_addr;
    return ap;
}

//semantic analysis
void semanticAnalysis(struct ast* root){
    vector<string> iterators;
    iteratorsMemoryReservation(iterators, root->node2);
    memoryReservation(root->node1);
    checkProperVariableUsage(root->node2);
    vector<string> vars_init;
    checkVariablesInit(vars_init, root->node2);

}

void iteratorsMemoryReservation(vector<string> iterators, struct ast* node){
    if(node == NULL){
        return;
    } else if(node->type.compare("commands") == 0){
        vector<string> copy_iter = iterators; //???
        iteratorsMemoryReservation(copy_iter, node->node1);
        iteratorsMemoryReservation(iterators, node->node2);
        return;
    
    } else if(node->name.compare("UPFOR") == 0 || node->name.compare("DOWNFOR") == 0){
        // add to iterators new iterator
        string new_iterator_name = node->node1->name;
        if(find(iterators.begin(), iterators.end(), new_iterator_name) != iterators.end()){
            //found
            string msg = "Bad usage of iterators in line " + to_string(node->node1->linum);
            yyerror(&msg[0]);
        }else{
            //not found
            iterators.push_back(new_iterator_name);
            // memory reservation 
            struct iter_for* new_it = newIterFor(memory_counter, false); 
            memory_counter++;
            //struct iter_for* new_it = newIterFor(memory_counter, false);
            memory_counter++;
            // second memory cell is for limit in for // needed for constant range in fors
            iter_memory_map[new_iterator_name] = new_it;
            iteratorsMemoryReservation(iterators, node->node2);
            iteratorsMemoryReservation(iterators, node->node3);
            set_visibility(new_it, true);
            iteratorsMemoryReservation(iterators, node->node4);
            set_visibility(new_it, false);
            return;
        }   
    } else if(node->name.compare("ASSIGN") == 0){
        string check_variable = node->node1->node1->name;
         if(find(iterators.begin(), iterators.end(), check_variable) != iterators.end()){
            //found
            string msg = "Bad iterator value modyfication in line " + to_string(node->node1->linum);
            yyerror(&msg[0]);
        }
        return;

    } else if(node->type.compare("identifier") == 0){
        if(iter_memory_map[node->node1->name] != NULL){
            if(iter_memory_map[node->node1->name]->visibility == false){
                string msg = "Iterator used out of scope in line " + to_string(node->node1->linum);
                yyerror(&msg[0]);
            }
        }
        if(node->node2 != NULL && iter_memory_map[node->node2->name] != NULL){
            if(iter_memory_map[node->node2->name]->visibility == false){
                string msg = "Iterator used out of scope in line " + to_string(node->node2->linum);
                yyerror(&msg[0]);
            }
        }
        return;
    } else {
        iteratorsMemoryReservation(iterators, node->node1);
        iteratorsMemoryReservation(iterators, node->node2);
        iteratorsMemoryReservation(iterators, node->node3);
        iteratorsMemoryReservation(iterators, node->node4);
    }
    
} 

void memoryReservation(struct ast* node){
    if(node == NULL){
        return;
    }
    memoryReservation(node->node1);
    if(node->name.compare("decPID") == 0){
        if(vars_memory_map[node->node2->name] == 0){ // simple type so 0 and not NULL
            vars_memory_map[node->node2->name] = memory_counter;
            memory_counter++;
        }else{
            string msg = "Redeclaration error in line " + to_string(node->node2->linum);
            yyerror(&msg[0]);
        }

        if(iter_memory_map[node->node2->name] != NULL){
            string msg = "Variable " + node->node2->name +" declared in line " + to_string(node->node2->linum) + ". Later used as iterator.";
            yyerror(&msg[0]);
        }

        if(arrays_memory_map[node->node2->name] != NULL){
            string msg = "In line " + to_string(node->node2->linum) + " variable " + node->node2->name + ", aleready declared as array.";
            yyerror(&msg[0]);
        }
        return;
        
    } else if(node->name.compare("decARR") == 0){
        if(arrays_memory_map[node->node2->name] == NULL){
            long long min_index = node->node3->number_value;
            long long max_index = node->node4->number_value;
            if(max_index < min_index){
                string msg = "Wrong range in array in line " + to_string(node->node2->linum);
                yyerror(&msg[0]);
            }

            unsigned long long first_memory_index = memory_counter;
            struct array_prop* new_array = newArrayProp(min_index, max_index, first_memory_index);
            memory_counter += (max_index - min_index + 1);
            arrays_memory_map[node->node2->name] = new_array;
        }else{
            string msg = "Redeclaration error in line " + to_string(node->node2->linum);
            yyerror(&msg[0]);
        }

        if(iter_memory_map[node->node2->name] != NULL){
            string msg = "Array " + node->node2->name +" declared in line " + to_string(node->node2->linum) + ". Later used as iterator.";
            yyerror(&msg[0]);
        }

        if(vars_memory_map[node->node2->name] != 0){
            string msg = "In line " + to_string(node->node2->linum) + " array " + node->node2->name + ", aleready declared as variable.";
            yyerror(&msg[0]);
        }
        return;
    } else {
        printf("Tu nigdy nie powinien byc - %s\n", &node->name[0]);
        return;
    }
    
}

void checkProperVariableUsage(struct ast* node){
    if(node == NULL){
        return;
    } else if(node->name.compare("UPFOR") == 0 || node->name.compare("DOWNFOR") == 0){
        string new_iterator_name = node->node1->name;
        struct iter_for* it = iter_memory_map[new_iterator_name];
        checkProperVariableUsage(node->node2);
        checkProperVariableUsage(node->node3);
        set_visibility(it, true);
        checkProperVariableUsage(node->node4);
        set_visibility(it, false);
        return;
    
    }/* else if(node->name.compare("ASSIGN")){
        if(iter_memory_map[node->node1->node1->name] != NULL){
            string msg = "In line " + to_string(node->node1->node1->linum) + " forbidden modification of iterator value.";
            yyerror(&msg[0]);
        }else{
            checkProperVariableUsage(node->node1);
            checkProperVariableUsage(node->node2);
            return;
        }
    } */
    else if(node->type.compare("identifier") == 0){
        if(node->name.compare("PID") == 0){
            if(iter_memory_map[node->node1->name] == NULL && vars_memory_map[node->node1->name] == 0){
                string msg = "In line " + to_string(node->node1->linum) + " undeclared variable or wrong usage of array.";
                yyerror(&msg[0]);
            } else if(iter_memory_map[node->node1->name] != NULL){
                if(iter_memory_map[node->node1->name]->visibility == false){
                    string msg = "In line " + to_string(node->node1->linum) + " iterator out of scope.";
                    yyerror(&msg[0]);
                }
            }
        } else if(node->name.compare("PIDPID") == 0){
            if(arrays_memory_map[node->node1->name] == NULL){
                string msg = "In line " + to_string(node->node1->linum) + " undeclared array or wrong usage of variable.";
                yyerror(&msg[0]);
            }

            if(iter_memory_map[node->node2->name] == NULL && vars_memory_map[node->node2->name] == 0){
                string msg = "In line " + to_string(node->node2->linum) + " undeclared variable or wrong usage of array.";
                yyerror(&msg[0]);
            } else if(iter_memory_map[node->node2->name] != NULL){
                if(iter_memory_map[node->node2->name]->visibility == false){
                    string msg = "In line " + to_string(node->node2->linum) + " iterator out of scope.";
                    yyerror(&msg[0]);
                }
            }
        } else if(node->name.compare("PIDNUM") == 0){
            if(arrays_memory_map[node->node1->name] == NULL){
                string msg = "In line " + to_string(node->node1->linum) + " undeclared array or wrong usage of variable.";
                yyerror(&msg[0]);
            } else {
                struct array_prop* ap = arrays_memory_map[node->node1->name];
                long long check_index = node->node2->number_value;
                if(ap->min_index > check_index || ap->max_index < check_index){
                    string msg = "In line " + to_string(node->node1->linum) + " index out of arrays bound.";
                    yyerror(&msg[0]);
                }
            }
        }
    } else {
        checkProperVariableUsage(node->node1);
        checkProperVariableUsage(node->node2);
        checkProperVariableUsage(node->node3);
        checkProperVariableUsage(node->node4);
    }
    return;
}

void checkVariablesInit(vector<string> &initialized, struct ast* node){
    if(node == NULL){
        return;
    } else if(node->name.compare("ASSIGN") == 0){
        checkVariablesInit(initialized, node->node2); // right side
        checkVariablesInit(initialized, node->node1->node2); // arrays goes to the same case as variables 
        string var_name = node->node1->node1->name;
        if(find(initialized.begin(), initialized.end(), var_name) == initialized.end()){
            //not found
            initialized.push_back(var_name);
        } 
    } else if(node->type.compare("identifier") == 0){
        string var_name = node->node1->name;
        if(find(initialized.begin(), initialized.end(), var_name) == initialized.end()){
                if(iter_memory_map[var_name] == NULL){
                    string msg = "In line " + to_string(node->node1->linum) + " variable " + node->node1->name + " not initialized.";
                    yyerror(&msg[0]);
                }
        } 
    } else if(node->name.compare("READ") == 0){
        string var_name = node->node1->node1->name;
        initialized.push_back(var_name);
    } else {
        checkVariablesInit(initialized, node->node1);
        checkVariablesInit(initialized, node->node2);
        checkVariablesInit(initialized, node->node3);
        checkVariablesInit(initialized, node->node4);
    }
    return;
}


struct iter_for* newIterFor(unsigned long long memory_index, bool visibility){
    struct iter_for* it = new iter_for(); //(struct iter_for*) malloc(sizeof(struct iter_for));
    if(!it){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    it->memory_index = memory_index;
    it->visibility = visibility;
    return it;
}
// visibility for iterators
void set_visibility(struct iter_for* it, bool visibility){
    it->visibility = visibility;
}

// TAC
struct three_address_code* newTac(enum instruction instr, struct tac_argument* arg1, struct tac_argument* arg2){
    struct three_address_code* tac = new three_address_code(); //(struct three_address_code*) malloc(sizeof(struct three_address_code));
    if(!tac){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    tac->instr = instr;
    tac->arg1 = arg1;
    tac->arg2 = arg2;
    return tac;
}

struct tac_argument* newTacArg(string type, string name, string array_index, long long num_value){
    struct tac_argument* tac_arg = new tac_argument();//(struct tac_argument*) malloc(sizeof(struct tac_argument));
    if(!tac_arg){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    tac_arg->type = &type[0]; 
    // maybe change this to type 
    if(name.empty()){
        name = " ";
    }
    tac_arg->name = name;

    if(array_index.empty()){
        array_index = " ";
    }
    tac_arg->array_index = array_index;

    tac_arg->num_value = num_value;

    return tac_arg;
}

//TAC generation section

void generateTAC(struct ast* root){
    if(root != NULL){
        genTACCommands(root->node2);
    }
    struct three_address_code* h = newTac(HALT2, NULL, NULL);
    tacodes.push(h);
}

void genTACCommands(struct ast* commands_node){
    if(commands_node == NULL){
        return;
    }
    genTACCommands(commands_node->node1);
    genTACCommand(commands_node->node2);

}

void genTACCommand(struct ast* command_node){
    if(command_node->name.compare("ASSIGN") == 0){
        genTACAssign(command_node);
    } else if(command_node->name.compare("IFELSE") == 0){
        genTACIfelse(command_node);
    } else if(command_node->name.compare("IF") == 0){
        genTACIf(command_node);
    } else if(command_node->name.compare("WHILE") == 0){
        genTACWhile(command_node);
    } else if(command_node->name.compare("DOWHILE") == 0){
        genTACDowhile(command_node);
    } else if(command_node->name.compare("UPFOR") == 0){
        genTACFor(command_node);
    } else if(command_node->name.compare("DOWNFOR") == 0){
        genTACFordown(command_node);
    } else if(command_node->name.compare("READ") == 0){
        genTACRead(command_node);
    } else if(command_node->name.compare("WRITE") == 0){
        genTACWrite(command_node);
    } else {
        string msg = "Error in ast command node.";
        yyerror(&msg[0]);
    }
}

void genTACAssign(struct ast* assign_node){
    genTACExpression(assign_node->node2);
    struct tac_argument* arg1 = NULL;
    if(assign_node->node1->name.compare("PID") == 0){
        arg1 = newTacArg("VAR", assign_node->node1->node1->name, "", 0);
    } else if(assign_node->node1->name.compare("PIDPID") == 0){
        arg1 = newTacArg("ARR_VAR", assign_node->node1->node1->name, assign_node->node1->node2->name, 0);
    } else if(assign_node->node1->name.compare("PIDNUM") == 0){
        arg1 = newTacArg("ARR_NUM", assign_node->node1->node1->name, "", assign_node->node1->node2->number_value);
    }

    struct three_address_code* tac = newTac(STORE2, arg1, NULL);
    tacodes.push(tac);
    
}

void genTACIfelse(struct ast* ifelse_node){
    struct tac_argument* label_start = newLabel();
    struct tac_argument* label_else = newLabel();
    struct tac_argument* label_end = newLabel();

    genTACCondition(ifelse_node->node1, label_start, label_else);
    struct three_address_code* tac_label_start = newTac(LABEL2, label_start, NULL);
    tacodes.push(tac_label_start);
    
    genTACCommands(ifelse_node->node2);
    struct three_address_code* tac_jump = newTac(JUMP2, label_end, NULL);
    tacodes.push(tac_jump);
    struct three_address_code* tac_label_else = newTac(LABEL2, label_else, NULL);
    tacodes.push(tac_label_else);

    genTACCommands(ifelse_node->node3);
    struct three_address_code* tac_label_end = newTac(LABEL2, label_end, NULL);
    tacodes.push(tac_label_end);
}

void genTACIf(struct ast* if_node){
    struct tac_argument* label_start = newLabel();
    struct tac_argument* label_end = newLabel();
    genTACCondition(if_node->node1, label_start, label_end);
    
    struct three_address_code* tac_label_start = newTac(LABEL2, label_start, NULL);
    tacodes.push(tac_label_start);
    genTACCommands(if_node->node2);

    struct three_address_code* tac_label_end = newTac(LABEL2, label_end, NULL);
    tacodes.push(tac_label_end);
}

void genTACWhile(struct ast* while_node){
    struct tac_argument* label_while_start = newLabel();
    struct tac_argument* label_while_true = newLabel();
    struct tac_argument* label_while_false = newLabel();

    struct three_address_code* tac_while_start = newTac(LABEL2, label_while_start, NULL);
    tacodes.push(tac_while_start);
    
    genTACCondition(while_node->node1, label_while_true, label_while_false);
    struct three_address_code* tac_while_true = newTac(LABEL2, label_while_true, NULL);
    tacodes.push(tac_while_true);

    genTACCommands(while_node->node2);

    struct three_address_code* tac_while_jump_start = newTac(JUMP2, label_while_start, NULL);
    tacodes.push(tac_while_jump_start);

    struct three_address_code* tac_while_false = newTac(LABEL2, label_while_false, NULL);
    tacodes.push(tac_while_false);

}


void genTACDowhile(struct ast* dowhile_node){
    struct tac_argument* label_while_start = newLabel();
    struct tac_argument* label_while_true = newLabel();
    struct tac_argument* label_while_false = newLabel();

    struct three_address_code* tac_while_start = newTac(LABEL2, label_while_start, NULL);
    tacodes.push(tac_while_start);
    genTACCommands(dowhile_node->node1);

    genTACCondition(dowhile_node->node2, label_while_true, label_while_false);
    
    struct three_address_code* tac_while_true = newTac(LABEL2, label_while_true, NULL);
    tacodes.push(tac_while_true);
    
    struct three_address_code* tac_while_jump_true = newTac(JUMP2, label_while_start, NULL);
    tacodes.push(tac_while_jump_true);

    struct three_address_code* tac_while_false = newTac(LABEL2, label_while_false, NULL);
    tacodes.push(tac_while_false);
}

void genTACFor(struct ast* for_node){
// FOR DYNAMIC RANGE 
/*

//pre for
    struct tac_argument* value1 = genTACArgument(for_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);

    struct tac_argument* iter1 = newTacArg("ITER", for_node->node1->name, " ", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* label_for_start = newLabel();
    //struct tac_argument* label_for_true = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);

// IF iter < val2 
    struct tac_argument* value2 = genTACArgument(for_node->node3);

    struct three_address_code* tac_minus_val2_iter1 = newTac(MINUS2, value2, iter1);
    tacodes.push(tac_minus_val2_iter1);

    //struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL); // something wrong here perhaps
    //tacodes.push(tac_jump_pos); //push here ? switch with this under
    struct three_address_code* tac_jump_neg = newTac(JNEG2, label_for_false, NULL); // something wrong here perhaps
    tacodes.push(tac_jump_neg); //push here ?   
//
    genTACCommands(for_node->node4);

// increment of iterator    
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_plus_iter1_1 = newTac(PLUS2, iter1, one);
    tacodes.push(tac_plus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL);
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);
*/
// FOR DYNAMIC RANGE END

//###########################################################

// FOR CONST RANGE 

//pre for
    struct tac_argument* value1 = genTACArgument(for_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);

    struct tac_argument* iter1 = newTacArg("ITER", for_node->node1->name, " ", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* value2 = genTACArgument(for_node->node3); 
    //struct three_address_code* tac_load_limit = newTac(LOAD2, value2, NULL); // perhaps it is useless
    //tacodes.push(tac_load_limit);

    struct three_address_code* tac_value2_minus_value1 = newTac(MINUS2, value2, value1);
    tacodes.push(tac_value2_minus_value1);

    struct three_address_code* tac_store_limit = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit);

    struct tac_argument* label_for_start = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);

// IF iter <= val2
    // IF limit >= 0
    struct three_address_code* load_limit_for_check = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(load_limit_for_check);

    //struct three_address_code* tac_minus_val2_iter1 = newTac(MINUS2, value2, iter1);
    //tacodes.push(tac_minus_val2_iter1);

    //struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL); // something wrong here perhaps
    //tacodes.push(tac_jump_pos); //push here ? switch with this under
    struct three_address_code* tac_jump_neg = newTac(JNEG2, label_for_false, NULL); // something wrong here perhaps
    tacodes.push(tac_jump_neg); //push here ?   
//

//  do in loop commands
    genTACCommands(for_node->node4);
//

// increment of iterator  //optimize with INC  
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_plus_iter1_1 = newTac(PLUS2, iter1, one);
    tacodes.push(tac_plus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//

// decrement of iterator limit
    struct three_address_code* tac_load_limit_before_dec = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(tac_load_limit_before_dec);

    struct three_address_code* tac_limit_minus_1 = newTac(DEC2, NULL, NULL);
    tacodes.push(tac_limit_minus_1);

    struct three_address_code* tac_store_limit_after_dec = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit_after_dec);

//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL);
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);

// FOR CONST RANGE END

}

void genTACFordown(struct ast* fordown_node){
//FORDOWN DYNAMIC RANGE
/*
//pre for
    struct tac_argument* value1 = genTACArgument(fordown_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);
    struct tac_argument* iter1 = newTacArg("ITER", fordown_node->node1->name, "", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* label_for_start = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);
// IF iter > val2 
    struct tac_argument* value2 = genTACArgument(fordown_node->node3);

    struct three_address_code* tac_minus_iter1_val2 = newTac(MINUS2, value2, iter1); //update memory te dwa miejsca ostatnie i przed maybe not
    tacodes.push(tac_minus_iter1_val2);

    struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL);
    tacodes.push(tac_jump_pos); // push here ?? 
//
    genTACCommands(fordown_node->node4);
// decrement of iterator    
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_minus_iter1_1 = newTac(MINUS2, iter1, one);
    tacodes.push(tac_minus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL); // possibly problem  endless loops change from jump to jump pos or jump neg
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);

*/    
//FORDOWN DYNAMIC RANGE END

//###########################################################

// FORDOWN CONST RANGE 

//pre for
    struct tac_argument* value1 = genTACArgument(fordown_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);

    struct tac_argument* iter1 = newTacArg("ITER", fordown_node->node1->name, " ", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* value2 = genTACArgument(fordown_node->node3); 
    //struct three_address_code* tac_load_limit = newTac(LOAD2, value2, NULL); // perhaps it is useless
    //tacodes.push(tac_load_limit);

// limit set
    struct three_address_code* tac_value1_minus_value2 = newTac(MINUS2, value1, value2);
    tacodes.push(tac_value1_minus_value2);

    struct three_address_code* tac_store_limit = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit);
// 

    struct tac_argument* label_for_start = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);

// IF iter >= val2
    // IF limit >= 0
    struct three_address_code* load_limit_for_check = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(load_limit_for_check);

    //struct three_address_code* tac_minus_val2_iter1 = newTac(MINUS2, value2, iter1);
    //tacodes.push(tac_minus_val2_iter1);

    //struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL); // something wrong here perhaps
    //tacodes.push(tac_jump_pos); //push here ? switch with this under
    struct three_address_code* tac_jump_neg = newTac(JNEG2, label_for_false, NULL); // something wrong here perhaps
    tacodes.push(tac_jump_neg); //push here ?   
//

//  do in loop commands
    genTACCommands(fordown_node->node4);
//

// decrement of iterator    //optimize with DEC
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_minus_iter1_1 = newTac(MINUS2, iter1, one);
    tacodes.push(tac_minus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//

// decrement of iterator limit
    struct three_address_code* tac_load_limit_before_dec = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(tac_load_limit_before_dec);

    struct three_address_code* tac_limit_minus_1 = newTac(DEC2, NULL, NULL);
    tacodes.push(tac_limit_minus_1);

    struct three_address_code* tac_store_limit_after_dec = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit_after_dec);

//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL); // possibly problem  endless loops change from jump to jump pos or jump neg
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);

// FORDOWN CONST RANGE END

}

void genTACRead(struct ast* read_node){
    struct tac_argument* arg1 = NULL;
    if(read_node->node1->name.compare("PID") == 0){ // node1  --
        arg1 = newTacArg("VAR", read_node->node1->node1->name, "", 0);
    } else if(read_node->node1->name.compare("PIDPID") == 0){ // node1  --
        arg1 = newTacArg("ARR_VAR", read_node->node1->node1->name, read_node->node1->node2->name, 0);
    } else if(read_node->node1->name.compare("PIDNUM") == 0){ // node1  --
        arg1 = newTacArg("ARR_NUM", read_node->node1->node1->name, "", read_node->node1->node2->number_value);
    }

    struct three_address_code* tac_read = newTac(READ2, arg1, NULL);
    tacodes.push(tac_read);   
}
void genTACWrite(struct ast* write_node){
    struct tac_argument* arg1 = genTACArgument(write_node->node1); 
    struct three_address_code* tac_write = newTac(WRITE2, arg1, NULL);
    tacodes.push(tac_write); 
}

void genTACExpression(struct ast* expression_node){
    if(expression_node->name.compare("VALUE") == 0){
        genTACValue(expression_node);
    } else if(expression_node->name.compare("PLUS") == 0){
        genTACPlus(expression_node);
    } else if(expression_node->name.compare("MINUS") == 0){
        genTACMinus(expression_node);
    } else if(expression_node->name.compare("TIMES") == 0){
        genTACTimes(expression_node);
    } else if(expression_node->name.compare("DIV") == 0){
        genTACDiv(expression_node);
    } else if(expression_node->name.compare("MOD") == 0){
        genTACMod(expression_node);
    }
}

void genTACValue(struct ast* value_node){
    struct tac_argument* arg1 = genTACArgument(value_node->node1);
    struct three_address_code* load = newTac(LOAD2, arg1, NULL);
    tacodes.push(load);
}

void genTACPlus(struct ast* plus_node){
    struct tac_argument* arg1 = genTACArgument(plus_node->node1);
    struct tac_argument* arg2 = genTACArgument(plus_node->node2);
    struct three_address_code* plus = newTac(PLUS2, arg1, arg2);
    tacodes.push(plus);
}

void genTACMinus(struct ast* minus_node){
    struct tac_argument* arg1 = genTACArgument(minus_node->node1);
    struct tac_argument* arg2 = genTACArgument(minus_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);
}

// change here?
void genTACTimes(struct ast* times_node){
    struct tac_argument* arg1 = genTACArgument(times_node->node1);
    struct tac_argument* arg2 = genTACArgument(times_node->node2);
    struct three_address_code* times = newTac(TIMES2, arg1, arg2);
    tacodes.push(times);
}

void genTACDiv(struct ast* div_node){
    struct tac_argument* arg1 = genTACArgument(div_node->node1);
    struct tac_argument* arg2 = genTACArgument(div_node->node2);
    struct three_address_code* div = newTac(DIV2, arg1, arg2);
    tacodes.push(div);
}

void genTACMod(struct ast* mod_node){
    struct tac_argument* arg1 = genTACArgument(mod_node->node1);
    struct tac_argument* arg2 = genTACArgument(mod_node->node2);
    struct three_address_code* mod = newTac(MOD2, arg1, arg2);
    tacodes.push(mod);
}
// change here end?

void genTACCondition(struct ast* condition_node, struct tac_argument* true_l, struct tac_argument* false_l){
    if(condition_node->name.compare("EQ") == 0){
        genTACEq(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("NEQ") == 0){
        genTACNeq(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("LE") == 0){
        genTACLe(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("GE") == 0){
        genTACGe(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("LEQ") == 0){
        genTACLeq(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("GEQ") == 0){
        genTACGeq(condition_node, true_l, false_l);
    }
}

void genTACEq(struct ast* eq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(eq_node->node1);
    struct tac_argument* arg2 = genTACArgument(eq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_zero = newTac(JZERO2, true_l, NULL);
    tacodes.push(j_zero);
    struct three_address_code* jump_end = newTac(JUMP2, false_l, NULL);
    tacodes.push(jump_end);
}

void genTACNeq(struct ast* neq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(neq_node->node1);
    struct tac_argument* arg2 = genTACArgument(neq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_zero = newTac(JZERO2, false_l, NULL);
    tacodes.push(j_zero);
    struct three_address_code* jump_end = newTac(JUMP2, true_l, NULL);
    tacodes.push(jump_end);
}


void genTACLe(struct ast* le_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(le_node->node1);
    struct tac_argument* arg2 = genTACArgument(le_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, true_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, false_l, NULL);
    tacodes.push(jump_end);
}

void genTACGe(struct ast* ge_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(ge_node->node1);
    struct tac_argument* arg2 = genTACArgument(ge_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg2, arg1);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, true_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, false_l, NULL);
    tacodes.push(jump_end);
}

void genTACLeq(struct ast* leq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(leq_node->node1);
    struct tac_argument* arg2 = genTACArgument(leq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg2, arg1);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, false_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, true_l, NULL);
    tacodes.push(jump_end);
}
void genTACGeq(struct ast* geq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(geq_node->node1);
    struct tac_argument* arg2 = genTACArgument(geq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, false_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, true_l, NULL);
    tacodes.push(jump_end);
}

struct tac_argument* genTACArgument(struct ast* value_node){
    if(value_node->name.compare("NUM") == 0){
        struct tac_argument* num = newTacArg("NUM", "", "", value_node->node1->number_value);
        return num;
    } else {
        if(value_node->node1->name.compare("PID") == 0){
            struct tac_argument* pid = NULL;
            string name_check = value_node->node1->node1->name; // where it's belong iters  or vars
            if(iter_memory_map[name_check] != NULL){
                pid = newTacArg("ITER", name_check, "", 0); // iterators
            } else {
                pid = newTacArg("VAR", name_check, "", 0); // variable
            }
            return pid;
        } else if(value_node->node1->name.compare("PIDPID") == 0){
            struct tac_argument* arr = newTacArg("ARR_VAR", value_node->node1->node1->name, value_node->node1->node2->name, 0); // iterators
            return arr;
        } else if(value_node->node1->name.compare("PIDNUM") == 0){
            struct tac_argument* arr = newTacArg("ARR_NUM", value_node->node1->node1->name, "", value_node->node1->node2->number_value); // iterators
            return arr;
        }
    }
    return NULL;
}

//label generator
struct tac_argument* newLabel(){
    label_number++;
    return newTacArg("LAB", " ", "", label_number);
}    

//TAC prints
void printTACQueue(){
    queue<struct three_address_code*> p = tacodes;
    while(!p.empty()){
        printTAC(p.front());
        p.pop();
    }
}
    
void printTAC(struct three_address_code* root){
    switch (root->instr){
        case PLUS2:
            printf("PLUS ");
            break;
        case MINUS2:
            printf("MINUS ");
            break;
        case INC2:
            printf("INC");
            break;
        case DEC2:
            printf("DEC");
            break;
        case TIMES2:
            printf("TIMES ");
            break;
        case DIV2:
            printf("DIV ");
            break;
        case MOD2:
            printf("MOD ");
            break;
        case LOAD2:
            printf("LOAD ");
            break;
        case STORE2: 
            printf("STORE ");
            break;//, LOADI, STOREI, 
        case LOADNEXT2:
            printf("LOADNEXT ");
            break;
        case STORENEXT2: 
            printf("STORENEXT ");
            break;//, LOADI, STOREI, 
        case JUMP2:
            printf("JUMP ");
            break;
        case JPOS2:
            printf("JPOS ");
            break;
        case JZERO2:
            printf("JZERO ");
            break;
        case JNEG2:
            printf("JNEG ");
            break;
        case READ2:
            printf("READ ");
            break;
        case WRITE2:
            printf("WRITE ");
            break; 
        case HALT2:
            printf("HALT ");
            break;
        case LABEL2:
            printf("LABEL "); 
            break;
        default: 
            printf(" ???? ");
            break;
    }
    
    printTACArgument(root->arg1);
    printTACArgument(root->arg2);
    printf("\n");

}

//print tac argument
void printTACArgument(struct tac_argument* arg){
    if(arg == NULL){
        return;
    }else if(arg->type.compare("ITER") == 0){
        printf("%s ", &arg->name[0]);
    } else if(arg->type.compare("VAR") == 0){
        printf("%s ", &arg->name[0]);
    } else if(arg->type.compare("ARR_VAR") == 0){
        printf("%s(%s) ", &arg->name[0], &arg->array_index[0]);
    } else if(arg->type.compare("ARR_NUM") == 0){
        printf("%s(%lld) ", &arg->name[0], arg->num_value);
    } else if(arg->type.compare("NUM") == 0){
        printf("%lld ", arg->num_value);
    } else if(arg->type.compare("LAB") == 0){
        printf("%s%lld ", &arg->type[0], arg->num_value);
    }
}

// generate asm
void genASM(){
    preProcess();
    // qureue froent 
    // pop
    // if odpowiedni uruchamiam 
    //first run over tacodes when jump convert into label number
    //and labels gone while labels map are being set to return proper number line of 'label'
    queue<struct three_address_code*> tac_copy = tacodes;
    while(!tac_copy.empty()){
        struct three_address_code* tac_into_asm = tac_copy.front();
        tac_copy.pop();
        switch (tac_into_asm->instr){
        case PLUS2:
            genASMPlus(tac_into_asm);
            //printf("PLUS ");
            break;
        case MINUS2:
            genASMMinus(tac_into_asm);
            //printf("MINUS ");
            break;
        case INC2:
            genASMINC(tac_into_asm);
            //printf("MINUS ");
            break;
        case DEC2:
            genASMDEC(tac_into_asm);
            //printf("MINUS ");
            break;
        case TIMES2: // Start ? to throw out
            genASMTimes(tac_into_asm);
            //printf("TIMES ");
            break;
        case DIV2:
            genASMDiv(tac_into_asm);
            //printf("DIV ");
            break;
        case MOD2:
            genASMMod(tac_into_asm); // end?
            //printf("MOD ");
            break;
        case LOAD2:
            genASMLoad(tac_into_asm);
            //printf("LOAD ");
            break;
        case STORE2:
            genASMStore(tac_into_asm); 
            //printf("STORE ");
            break;//, LOADI, STOREI, 
        case LOADNEXT2:
            genASMLoadNext(tac_into_asm);
            //printf("LOAD ");
            break;
        case STORENEXT2:
            genASMStoreNext(tac_into_asm); 
            //printf("STORE ");
            break; 
        case JUMP2:
            genASMJump(tac_into_asm);
            //printf("JUMP ");
            break;
        case JPOS2:
            genASMJpos(tac_into_asm);
            //printf("JPOS ");
            break;
        case JZERO2:
            genASMJzero(tac_into_asm);
            //printf("JZERO ");
            break;
        case JNEG2:
            genASMJneg(tac_into_asm);
            //printf("JNEG ");
            break;
        case READ2:
            genASMRead(tac_into_asm);
            //printf("READ ");
            break;
        case WRITE2:
            genASMWrite(tac_into_asm);
            //printf("WRITE ");
            break; 
        case HALT2:
            genASMHalt(tac_into_asm);
            //printf("HALT ");
            break;
        case LABEL2:
            genASMLabel(tac_into_asm);
            //printf("LABEL "); 
            break;
        default: 
            printf("    # ???? ");
            break;
    }

    }
    // now we have numbers instead of jumps, we need to repair this here
    // second run over the asm_instructions this time,  we convert numbers of labels  to real line numbers
    for(int i = 0; i < asm_instructions.size(); i++){
        if(asm_instructions[i].compare(to_string(atoll(&asm_instructions[i][0]))) == 0){
            //number so it is a jump to label
            asm_instructions[i] = jumps[asm_instructions[i]] + to_string(labels[asm_instructions[i]]); //+ "   " + asm_instructions[i];
        }
    }

    //third run over the asm_instructions to print everything 
    for(int i = 0; i < asm_instructions.size(); i++){
        // change to output file
        outfile << asm_instructions[i] << endl;
    }



    // else stuff

    

}

void genASMPlus(struct three_address_code* code){
    loadArgIntoMemory(code->arg1, 1);
    loadArgIntoMemory(code->arg2, 0);
    asm_instructions.push_back("ADD 1");
    asm_lineno++;
}

void genASMMinus(struct three_address_code* code){
    loadArgIntoMemory(code->arg2, 1);
    loadArgIntoMemory(code->arg1, 0);
    asm_instructions.push_back("SUB 1");
    asm_lineno++;
}

void genASMINC(struct three_address_code* code){
    asm_instructions.push_back("INC");
    asm_lineno++;
}

void genASMDEC(struct three_address_code* code){
    asm_instructions.push_back("DEC");
    asm_lineno++;
}

void genASMTimes(struct three_address_code* code){ // use memory cells 1, 2, 3.

    struct tac_argument* l_start = newLabel(); 
    struct three_address_code* label_start = newTac(LABEL2, l_start, NULL);

    struct tac_argument* l_arg2_less_0 = newLabel(); 
    struct three_address_code* label_arg2_less_0 = newTac(LABEL2, l_arg2_less_0, NULL);

    struct tac_argument* l_end_end = newLabel(); 
    struct three_address_code* label_end_end = newTac(LABEL2, l_end_end, NULL);

    struct tac_argument* l_shift = newLabel(); 
    struct three_address_code* label_shift = newTac(LABEL2, l_shift, NULL);
    
    struct tac_argument* l_add = newLabel(); 
    struct three_address_code* label_add = newTac(LABEL2, l_add, NULL);
    
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    
    //optimize multiplication by one 

    // generate parity form smaller argument 
    // how to check if arg1 < arg2 or arg1 > arg2
    //loadArgIntoMemory(code->arg1, 0);
    //struct three_address_code jpos_arg1_g_zero = newTac(JPOS2, l_arg1_g_0, NULL);
    genASMParityVector(code->arg2); //temp arg2
    
//p[2] value of arg1
    loadArgIntoMemory(code->arg1, 2);  
    // only here change for TIMES rejestr 0 * arg2

//p[3] current value of multiplication. start from 0

    asm_instructions.push_back("SUB 0");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;

// LABEL START
    genASMLabel(label_start);
// decrement memory counter
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;        
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    memory_counter--;
//
//check parity & end condition
    asm_instructions.push_back("LOADI "+ to_string(next_free_address));
    asm_lineno++;
    struct three_address_code* jpos_shift = newTac(JPOS2, l_shift, NULL);
    genASMJpos(jpos_shift);
    struct three_address_code* jneg_add = newTac(JNEG2, l_add, NULL);
    genASMJneg(jneg_add);
    struct three_address_code* jzero_end = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end);
//
//Label shift
    genASMLabel(label_shift);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_as = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_as);
// label ADD
    genASMLabel(label_add);
    asm_instructions.push_back("LOAD 2");
    asm_lineno++;
    asm_instructions.push_back("ADD 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_aa = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_aa);
// Label end
    genASMLabel(label_end);
// pointer of memory to after p[memory_counter] = 0 cell
    memory_counter++;
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    
    //sign correction when
    // IF a < 0 && b < 0
    // IF a > 0 && b < 0
    //BOTH CASES looks identical in ASM
    // najpierw STORE 1
    
    //asm_instructions.push_back("STORE 3");
    //asm_lineno++;
    loadArgIntoMemory(code->arg2, 0); // when optimize need this to change
    struct three_address_code* jneg_arg2_l_0 = newTac(JNEG2, l_arg2_less_0, NULL);
    genASMJneg(jneg_arg2_l_0);
    struct three_address_code* jump_end_end = newTac(JUMP2, l_end_end, NULL);
    genASMJump(jump_end_end);
// label arg2 less tthan 0
    genASMLabel(label_arg2_less_0);

    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
// label end end
    genASMLabel(label_end_end);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;

    // Jneg B
    // JUMP END
    //LABEL NEGB
    // JNEG A
// CASE IF a > 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //JUMP END
//lABEL IF a < 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //LABEL END
    
}

void genASMTimes2(unsigned long long memory_cell_arg1, struct three_address_code* code){ // use memory cells 1, 2, 3.

    struct tac_argument* l_start = newLabel(); 
    struct three_address_code* label_start = newTac(LABEL2, l_start, NULL);

    struct tac_argument* l_arg2_less_0 = newLabel(); 
    struct three_address_code* label_arg2_less_0 = newTac(LABEL2, l_arg2_less_0, NULL);

    struct tac_argument* l_end_end = newLabel(); 
    struct three_address_code* label_end_end = newTac(LABEL2, l_end_end, NULL);

    struct tac_argument* l_shift = newLabel(); 
    struct three_address_code* label_shift = newTac(LABEL2, l_shift, NULL);
    
    struct tac_argument* l_add = newLabel(); 
    struct three_address_code* label_add = newTac(LABEL2, l_add, NULL);
    
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    
    //optimize multiplication by one 

    // generate parity form smaller argument 
    // how to check if arg1 < arg2 or arg1 > arg2
    //loadArgIntoMemory(code->arg1, 0);
    //struct three_address_code jpos_arg1_g_zero = newTac(JPOS2, l_arg1_g_0, NULL);
    genASMParityVector(code->arg2); //temp arg2
    
//p[2] value of arg1
//    loadArgIntoMemory(code->arg1, 2);  
    asm_instructions.push_back("LOAD " + to_string(memory_cell_arg1));
    asm_lineno++;
    asm_instructions.push_back("STORE 2");
    asm_lineno++;
// only here change for TIMES rejestr 0 * arg2

//p[3] current value of multiplication. start from 0

    asm_instructions.push_back("SUB 0");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;

// LABEL START
    genASMLabel(label_start);
// decrement memory counter
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;        
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    memory_counter--;
//
//check parity & end condition
    asm_instructions.push_back("LOADI "+ to_string(next_free_address));
    asm_lineno++;
    struct three_address_code* jpos_shift = newTac(JPOS2, l_shift, NULL);
    genASMJpos(jpos_shift);
    struct three_address_code* jneg_add = newTac(JNEG2, l_add, NULL);
    genASMJneg(jneg_add);
    struct three_address_code* jzero_end = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end);
//
//Label shift
    genASMLabel(label_shift);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_as = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_as);
// label ADD
    genASMLabel(label_add);
    asm_instructions.push_back("LOAD 2");
    asm_lineno++;
    asm_instructions.push_back("ADD 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_aa = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_aa);
// Label end
    genASMLabel(label_end);
// pointer of memory to after p[memory_counter] = 0 cell
    memory_counter++;
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    
    //sign correction when
    // IF a < 0 && b < 0
    // IF a > 0 && b < 0
    //BOTH CASES looks identical in ASM
    // najpierw STORE 1
    
    //asm_instructions.push_back("STORE 3");
    //asm_lineno++;
    loadArgIntoMemory(code->arg2, 0); // when optimize need this to change
    struct three_address_code* jneg_arg2_l_0 = newTac(JNEG2, l_arg2_less_0, NULL);
    genASMJneg(jneg_arg2_l_0);
    struct three_address_code* jump_end_end = newTac(JUMP2, l_end_end, NULL);
    genASMJump(jump_end_end);
// label arg2 less tthan 0
    genASMLabel(label_arg2_less_0);

    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
// label end end
    genASMLabel(label_end_end);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;

    // Jneg B
    // JUMP END
    //LABEL NEGB
    // JNEG A
// CASE IF a > 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //JUMP END
//lABEL IF a < 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //LABEL END
    
}

void plusPlusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    //???
    loadArgIntoMemory(code->arg2, 7); 
    //???
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jpos_max_mul = newTac(JPOS2, l_set_max_mul, NULL);
    genASMJpos(jpos_max_mul);
//
// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

    struct three_address_code* jneg_reduce_mul = newTac(JNEG2, l_reduce_mul, NULL);
    genASMJneg(jneg_reduce_mul);

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);
    
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++;    
}   

void plusMinusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    
    loadArgIntoMemory(code->arg2, 7); 
    
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jpos_max_mul = newTac(JPOS2, l_set_max_mul, NULL);
    genASMJpos(jpos_max_mul);
//

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

// modyfication
    asm_instructions.push_back("SUB 7");
    asm_lineno++;
    asm_instructions.push_back("DEC");
    asm_lineno++;
//
    struct three_address_code* jneg_reduce_mul = newTac(JNEG2, l_reduce_mul, NULL);
    genASMJneg(jneg_reduce_mul);

// modyfication
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("ADD 7");
    asm_lineno++;
//   

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    asm_instructions.push_back("DEC");
    asm_lineno++;

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++; 
}

void minusPlusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    
    loadArgIntoMemory(code->arg2, 7); 
    
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jneg_max_mul = newTac(JNEG2, l_set_max_mul, NULL);
    genASMJneg(jneg_max_mul);
//

  //  asm_instructions.push_back("LOAD 6");
  //  asm_lineno++;
  //  asm_instructions.push_back("SUB 6");
  //  asm_lineno++;
  //  asm_instructions.push_back("SUB 6");
  //  asm_lineno++;
  //  asm_instructions.push_back("STORE 6");
  //  asm_lineno++;

// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

// modyfication
    asm_instructions.push_back("SUB 7");
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
//
    struct three_address_code* jpos_reduce_mul = newTac(JPOS2, l_reduce_mul, NULL);
    genASMJpos(jpos_reduce_mul);

// modyfication
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("ADD 7");
    asm_lineno++;
//   

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    asm_instructions.push_back("DEC");
    asm_lineno++;

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++; 
}

void minusMinusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    //???
    loadArgIntoMemory(code->arg2, 7); 
    //???
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jneg_max_mul = newTac(JNEG2, l_set_max_mul, NULL);
    genASMJneg(jneg_max_mul);
//
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

    struct three_address_code* jpos_reduce_mul = newTac(JPOS2, l_reduce_mul, NULL);
    genASMJpos(jpos_reduce_mul);

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);
    
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++;   
}


void genASMDiv(struct three_address_code* code){ // use cells (1,2,3) <= multiplication (4,5,6,7) <= division part
    // 4 current value of division
    // 5 current rest from division

    struct tac_argument* l_arg1_plus = newLabel(); 
    struct three_address_code* label_arg1_plus = newTac(LABEL2, l_arg1_plus, NULL);
    struct tac_argument* l_arg1_minus = newLabel(); 
    struct three_address_code* label_arg1_minus = newTac(LABEL2, l_arg1_minus, NULL);
    struct tac_argument* l_arg_zero = newLabel(); 
    struct three_address_code* label_arg_zero = newTac(LABEL2, l_arg_zero, NULL);

    struct tac_argument* l_arg1_plus_arg2_plus = newLabel(); 
    struct three_address_code* label_arg1_plus_arg2_plus = newTac(LABEL2, l_arg1_plus_arg2_plus, NULL);
    struct tac_argument* l_arg1_plus_arg2_minus = newLabel(); 
    struct three_address_code* label_arg1_plus_arg2_minus = newTac(LABEL2, l_arg1_plus_arg2_minus, NULL);
    struct tac_argument* l_arg1_minus_arg2_plus = newLabel(); 
    struct three_address_code* label_arg1_minus_arg2_plus = newTac(LABEL2, l_arg1_minus_arg2_plus, NULL);
    struct tac_argument* l_arg1_minus_arg2_minus = newLabel(); 
    struct three_address_code* label_arg1_minus_arg2_minus = newTac(LABEL2, l_arg1_minus_arg2_minus, NULL);

    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
   

// dont know if necessary
    asm_instructions.push_back("SUB 0");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 5");
    asm_lineno++;
// set starter as zero

// determine case
    loadArgIntoMemory(code->arg1, 0);
    
    struct three_address_code* jpos_arg1_plus = newTac(JPOS2, l_arg1_plus, NULL);
    genASMJpos(jpos_arg1_plus);
    struct three_address_code* jneg_arg1_minus = newTac(JNEG2, l_arg1_minus, NULL);
    genASMJneg(jneg_arg1_minus);
    struct three_address_code* jzero_arg1_zero = newTac(JZERO2, l_arg_zero, NULL);
    genASMJzero(jzero_arg1_zero);
// L+
    genASMLabel(label_arg1_plus);
    loadArgIntoMemory(code->arg2, 0);
    struct three_address_code* jpos_arg1_plus_arg2_plus = newTac(JPOS2, l_arg1_plus_arg2_plus, NULL);
    genASMJpos(jpos_arg1_plus_arg2_plus);
    struct three_address_code* jneg_arg1_plus_arg2_minus = newTac(JNEG2, l_arg1_plus_arg2_minus, NULL);
    genASMJneg(jneg_arg1_plus_arg2_minus);
    struct three_address_code* jzero_arg2_zero = newTac(JZERO2, l_arg_zero, NULL);
    genASMJzero(jzero_arg2_zero);

// L-
    genASMLabel(label_arg1_minus);
    loadArgIntoMemory(code->arg2, 0);
    struct three_address_code* jpos_arg1_minus_arg2_plus = newTac(JPOS2, l_arg1_minus_arg2_plus, NULL);
    genASMJpos(jpos_arg1_minus_arg2_plus);
    struct three_address_code* jneg_arg1_minus_arg2_minus = newTac(JNEG2, l_arg1_minus_arg2_minus, NULL);
    genASMJneg(jneg_arg1_minus_arg2_minus);
    struct three_address_code* jzero_arg22_zero = newTac(JZERO2, l_arg_zero, NULL);
    genASMJzero(jzero_arg22_zero);
// L++
    genASMLabel(label_arg1_plus_arg2_plus);
    plusPlusDivide(code);
    struct three_address_code* jump_end1 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end1);
// L+-
    genASMLabel(label_arg1_plus_arg2_minus);
    plusMinusDivide(code);
    struct three_address_code* jump_end2 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end2);
// L-+
    genASMLabel(label_arg1_minus_arg2_plus);
    minusPlusDivide(code);
    struct three_address_code* jump_end3 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end3);
// L--
    genASMLabel(label_arg1_minus_arg2_minus);
    minusMinusDivide(code);
    struct three_address_code* jump_end4 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end4);
// L0
    genASMLabel(label_arg_zero);
// L END
    genASMLabel(label_end);
}

void genASMMod(struct three_address_code* code){
    //the worst idea
    genASMDiv(code);
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    //
}

void genASMJump(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JUMP ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}

void genASMJpos(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JPOS ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}
void genASMJzero(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JZERO ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}
void genASMJneg(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JNEG ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}

void genASMLabel(struct three_address_code* code){
    labels[to_string(code->arg1->num_value)] = asm_lineno;
    //asm_instructions.push_back("LAB " + to_string(code->arg1->num_value) + " lineno:"+ to_string(asm_lineno));
    //asm_lineno++;
}

void genASMLoad(struct three_address_code* code){
    loadArgIntoMemory(code->arg1, 0);
}

void genASMLoadNext(struct three_address_code* code){
    loadNextArgIntoMemory(code->arg1, 0);
}

void genASMStoreNext(struct three_address_code* code){
    asmStoreHelpNext(code->arg1);
}


void genASMStore(struct three_address_code* code){ 
    asmStoreHelp(code->arg1);
}
void asmStoreHelp(struct tac_argument* arg){ // use memory cell 1, 2
    if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name];
        asm_instructions.push_back("STORE " + to_string(var_address));
        asm_lineno++;
   
    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value;
        asm_instructions.push_back("STORE " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        if(iter_memory_map[arg->array_index] != NULL){
            //cout << "array[iter]" << endl;
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }else{
        //if arg->var->type iter to z map iteratorow wyciagnij wartosc
           // cout << "array[var]" << endl;
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index]));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }

    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index;
        asm_instructions.push_back("STORE " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    /*(if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }*/
}

void asmStoreHelpNext(struct tac_argument* arg){ // use memory cell 1, 2
    if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name] + 1;
        asm_instructions.push_back("STORE " + to_string(var_address));
        asm_lineno++;
   
    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value + 1;
        asm_instructions.push_back("STORE " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        //if arg->var->type iter to z map iteratorow wyciagnij wartosc
        if(iter_memory_map[arg->array_index] != NULL){
           // cout << "array[iter]" << endl;
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index + 1));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }else{
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index] + 1));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }

    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index + 1;
        asm_instructions.push_back("STORE " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    /*(if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }*/
}


void genASMRead(struct three_address_code* code){
    asm_instructions.push_back("GET");
    asm_lineno++;
    asmStoreHelp(code->arg1);
}

void genASMWrite(struct three_address_code* code){
    loadArgIntoMemory(code->arg1, 0);
    asm_instructions.push_back("PUT");
    asm_lineno++;
}

void genASMHalt(struct three_address_code* code){
    asm_instructions.push_back("HALT");
    asm_lineno++;
}

void genASMConst(long long const_value){
    vector<string> q; 
    string zero = "SUB 0";
    //asm_instructions.push_back(zero); // if not working try unncoment
    //asm_lineno++; // if not working try unncoment
    // optimization with SHIFT / rozklad na czynniki pierwsze ////////////////////////////////////////////////////////
    while(const_value != 0){
        if(const_value > 0){
            if(const_value%2 == 0){
                q.push_back("SHIFT " + to_string(one_place));
                const_value = const_value/2;
            }else{
                q.push_back("INC");
                const_value--;
            }
        } else { // const value < 0
            if(const_value%2 == 0){
                q.push_back("SHIFT " + to_string(one_place));
                const_value = const_value/2;
            }else{
                q.push_back("DEC");
                const_value++;
            }
        }
    }
    q.push_back(zero);
    
    for(int i = q.size() - 1; i >= 0; i--){
        asm_instructions.push_back(q[i]);
        asm_lineno++;
    }

}

void loadArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell){  //using cell 1 // 0-8 memory cells
    if(arg->type.compare("NUM") == 0){
        genASMConst(arg->num_value);
   
    } else if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name];
        asm_instructions.push_back("LOAD " + to_string(var_address));
        asm_lineno++;

    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value;
        asm_instructions.push_back("LOAD " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        if(iter_memory_map[arg->array_index] != NULL){
            //cout << "array[iter] load" << endl;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index));
            asm_lineno++;
            // load?
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }else{
            //if arg->var->type iter to z map iteratorow wyciagnij wartosc
            //??????????????
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index]));
            asm_lineno++;
            // load?
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }

    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index;
        asm_instructions.push_back("LOAD " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }
}

void loadNextArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell){  // 0-8 memory cells
    if(arg->type.compare("NUM") == 0){
        genASMConst(arg->num_value);
   
    } else if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name] + 1;
        asm_instructions.push_back("LOAD " + to_string(var_address));
        asm_lineno++;

    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value + 1;
        asm_instructions.push_back("LOAD " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        //if arg->var->type iter to z map iteratorow wyciagnij wartosc
        if(iter_memory_map[arg->array_index] != NULL){
            //cout << "array[iter] load next" << endl;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index + 1));
            asm_lineno++;
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }else{

            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index] + 1));
            asm_lineno++;
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }
    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index + 1;
        asm_instructions.push_back("LOAD " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }
}



// arguments proper order make
/*
void swapArgs(struct three_address_code* code){
    struct tac_argument* arg1 = code->arg1;
    struct tac_argument* arg2 = code->arg2;
    if(code->) {

    }
}*/

// pre process function set some constans 
void genASMCheckParity(unsigned long long mem_cell){ // if p[0] == 0 it's even number, else odd
    asm_instructions.push_back("LOAD " + to_string(mem_cell)); 
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place)); 
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place)); 
    asm_lineno++;
    asm_instructions.push_back("SUB " + to_string(mem_cell));
    asm_lineno++;
}

void genASMParityVector(struct tac_argument* arg){ //use p[1]
    struct tac_argument* l_start = newLabel(); 
    struct three_address_code* label_start = newTac(LABEL2, l_start, NULL);
    struct tac_argument* l_odd1 = newLabel(); 
    struct three_address_code* label_odd1 = newTac(LABEL2, l_odd1, NULL);
    //struct tac_argument* l_odd2 = newLabel(); 
    //struct three_address_code* label_odd2 = newTac(LABEL2, l_odd2, NULL);
   

    struct tac_argument* l_arg_under_0 = newLabel(); 
    struct three_address_code* label_arg_under_0 = newTac(LABEL2, l_arg_under_0, NULL);

    struct tac_argument* l_end_id = newLabel(); 
    struct three_address_code* label_end_id = newTac(LABEL2, l_end_id, NULL);

    struct tac_argument* l_even = newLabel(); 
    struct three_address_code* label_even = newTac(LABEL2, l_even, NULL);
    struct tac_argument* l_memo_update = newLabel(); 
    struct three_address_code* label_memo_update = newTac(LABEL2, l_memo_update, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    

    loadArgIntoMemory(arg, 1);
    //asm_instructions.push_back("STORE 1"); 
    //asm_lineno++;
//LABEL START 
    genASMLabel(label_start);
//
    asm_instructions.push_back("LOAD 1"); 
    asm_lineno++;
    struct three_address_code* jzero_end = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end);
    genASMCheckParity(1);

// odd arg > 0
    struct three_address_code* jneg_odd1 = newTac(JNEG2, l_odd1, NULL);
    genASMJneg(jneg_odd1);
// odd arg < 0
    //struct three_address_code* jpos_odd2 = newTac(JPOS2, l_odd2, NULL);
   // genASMJpos(jpos_odd2);
// even
    struct three_address_code* jzero_even = newTac(JZERO2, l_even, NULL);
    genASMJzero(jzero_even);

// LABEL ODD1
    genASMLabel(label_odd1);
//save parity
// optimize with store od memorycounter ? not storeI
    asm_instructions.push_back("STOREI " + to_string(next_free_address));
    asm_lineno++;
    memory_counter++;
//
    asm_instructions.push_back("LOAD 1");
    asm_lineno++;
    //jneg
    struct three_address_code* jneg_under_0 = newTac(JNEG2, l_arg_under_0, NULL);
    genASMJneg(jneg_under_0);
    asm_instructions.push_back("DEC");
    asm_lineno++;
    struct three_address_code* jump_end_id = newTac(JUMP2, l_end_id, NULL);
    genASMJump(jump_end_id);
// label arg <0
    genASMLabel(label_arg_under_0);
//
    asm_instructions.push_back("INC"); 
    asm_lineno++;
// label en of increment / decrement
    genASMLabel(label_end_id);

    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    struct three_address_code* jump_memo_update1 = newTac(JUMP2, l_memo_update, NULL);
    genASMJump(jump_memo_update1);
// LABEL ODD2
   /* genASMLabel(label_odd2);
    //save parity
// optimize with store od memorycounter ? not storeI
    asm_instructions.push_back("DEC");
    asm_lineno++;
    //asm_instructions.push_back("SUB 0"); 
    //asm_lineno++;
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("STOREI " + to_string(next_free_address));
    asm_lineno++;
    memory_counter++;
//
    asm_instructions.push_back("LOAD 1");
    asm_lineno++;
    asm_instructions.push_back("INC"); 
    asm_lineno++;
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    struct three_address_code* jump_memo_update2 = newTac(JUMP2, l_memo_update, NULL);
    genASMJump(jump_memo_update2);*/
// LABEL EVEN
    genASMLabel(label_even);
//save parity
// optimize with store od memorycounter ? not storeI    
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STOREI " + to_string(next_free_address));
    asm_lineno++;
    memory_counter++;
//
    asm_instructions.push_back("LOAD 1");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    struct three_address_code* jump_memo_update3 = newTac(JUMP2, l_memo_update, NULL);
    genASMJump(jump_memo_update3);
// LABEL memoUPDATE
    genASMLabel(label_memo_update);
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;

    struct three_address_code* jump_start = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start);
// LABEL END
    genASMLabel(label_end);
}

void preProcess(){
    // p[10] = 1
    genASMConst(1);
    asm_instructions.push_back("STORE " + to_string(one_place));
    asm_lineno++;
    
    // p[9] = -1
    genASMConst(-1);
    asm_instructions.push_back("STORE " + to_string(minus_one_place));
    asm_lineno++;
    
    // p[memory_counter] = 0;
    genASMConst(0);
    asm_instructions.push_back("STORE " + to_string(memory_counter));
    asm_lineno++;
    
    // memory_counter++
    memory_counter++;
    
    // p[8] = pierwszy wolny adres pamieci
    genASMConst(memory_counter);
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
}

void yyerror(char const* msg){
    fprintf(stderr, "\x1B[31m%s.\x1B[0m\n", msg);
    exit(-1);
}


int main(int argc, char const *argv[]) {
    if(argc == 2){
        //if(argv[1] != "/dev/stdin"){
            yyin = fopen(argv[1], "r");
            outfile.open("/dev/stdout");
        //}
    } else if(argc == 3){
        //if(argv[1] != "/dev/stdin"){
            yyin = fopen(argv[1], "r");
        //}
        //if(argv[2] != "/dev/stdout"){
           // ofstream outfile; 
            outfile.open(argv[2]);
        //}
    } else {
           // ofstream outfile; 
            outfile.open("/dev/stdout");
    }
    yyparse();

    fclose(yyin);
    outfile.close();
    
    return 0;
}

