#ifndef _CMD_LINE_H_
#define _CMD_LINE_H_
#include "life.h"
#include "../lib/common.h"

// Struct contendo os membros de uma simulação.
struct Simulation{
    std::string filename;       //!< Nome do arquivo.
    uint maxgen;           //!< Número máximo de simulações. 
    uint blocksize;        //!< Tamanho de cada pixel da imagem.
    life::Color bkgcolor;       //!< Cor do fundo da imagem.
    life::Color alivecolor;     //!< Cor das células.

    Simulation();
};

void usage();
Simulation get_options(int argc,  char**);

#endif