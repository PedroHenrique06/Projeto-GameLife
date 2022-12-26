#include "cmd_line.h"
#include "../lib/common.h"

// Construtor padrão.
Simulation::Simulation() : filename{""}, maxgen{0}, blocksize{0}, bkgcolor{life::GREEN}, alivecolor{life::RED} {}

// Mostra o menu de uso.
void usage(){
    std::cout << "Usage: glife [options] input_cfg_file\n"
                << "\tRunning options:\n"
                << "\t\t--help                    Print this help text.\n"
                << "\t\t--maxgen <num>            Maximum number of generations to simulate. Default = 10.\n"
                << "\t\t--imgdir <path>           Images output directory\n"
                << "\t\t--blocksize <num>         Pixel size of a square cell. Default = 5\n"
                << "\t\t--bkgcolor <color>        Color name for background. Default = GREEN\n"
                << "\t\t--alivecolor <color>       Color name for the alive cells. Default = RED\n";      
}

// Variável auxiliar.
Simulation input;
// Captura as opções de entrada da linha de comando.
Simulation get_options(int argc, char** argv){
    
    // Case 1: glife
    if(argc == 1){
        usage();
    }
    // Case 2: glife [-h, --help, --maxgen or filename]
    else if(argc == 2){
        if(string(argv[1]) == "-h" or string(argv[1]) == "--help"){
            usage();
        }
        else if(string(argv[1]) == "--maxgen"){
            std::cout << "\nThe option '--maxgen' is lacking a complement.\n";
            usage();
        }
        else if(argc == 2){
            input.filename = string(argv[1]);
            input.maxgen = 10;
        }
    }
    // Case 3: testar se o argumento dps do --maxgen é um número.
    else if(argc == 3){
        if(string(argv[1]) == "--maxgen"){
            
        }
    }


/*     for(int arg = 1; arg < argc; arg++ ){
        if(argc == 2 && (string(argv[arg]) == "-h" || string(argv[arg]) == "--help")){
            usage();
        }
        else if(argc == 2 && (string(argv[arg]) == "--maxgen")){
            usage();
        }
        else if(argc == 2){
            input.filename = string(argv[arg]);
            input.maxgen = 8;
        }
        else if(arg == 1 && string(argv[arg]) == "--maxgen"){
            input.maxgen = atol(argv[arg+1]);
            if(argc > 3){
                input.filename = string(argv[arg+2]);
            }else{
                std::cout << "Faltou Informar o arquivo com a configuração de entrada!\n";
                usage();
            }
        } 
    } */
      return input;
}
