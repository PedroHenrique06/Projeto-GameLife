#include <iostream>
#include <cstdlib>  // EXIT_SUCCESS
#include <fstream>
#include <iomanip>
#include "life.h"
#include "cmd_line.h"

int main(int argc, char* argv[]){
    Simulation entry;
    entry = get_options(argc, argv);

    std::fstream file(entry.filename, std::ios::in);
    if(file.is_open()){
        int linha, coluna;

        file >> linha >> coluna;
        
        life::LifeCfg simulation(linha, coluna);
        uint i = 1;
        uint g = i+1;
        simulation.set_alive(file);
        simulation.prepare_matrix();
        std::cout << "\nGeração " << i << '\n';
        simulation.show_configuration();

        while(i < entry.maxgen){
            std::cout << "Geração " << g << '\n';
            simulation.update();
            simulation.prepare_matrix();
            simulation.show_configuration();
            
            if(simulation.extinct()){
            std::cout << "\nFoi extinta na " << " Geração " << g << "\n";
            break;
            }
            
            i++; g++;
        }
    }
    else{
        if((argc != 4 )  && (string(argv[1]) == "-h" || string(argv[1]) == "--help" || string(argv[1]) == "--maxgen")){}

        else{
            std::cout << "arquivo de configuração inválido!\n";
        }
    }


    return EXIT_SUCCESS;
}
