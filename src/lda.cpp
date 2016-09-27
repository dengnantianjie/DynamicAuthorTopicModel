/*
 * Copyright (C) 2007 by
 * 
 * 	Xuan-Hieu Phan
 *	hieuxuan@ecei.tohoku.ac.jp or pxhieu@gmail.com
 * 	Graduate School of Information Sciences
 * 	Tohoku University
 *
 * GibbsLDA++ is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * GibbsLDA++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GibbsLDA++; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include "model.h"
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

//const int time_doc[] = {0, 1631, 3510, 5350, 7200, 8947, 10650, 12405, 13976, 15515, 17357, 19136, 20448, 21765, 23366, 25081, 26843, 28588, 30155, 31930, 33646, 35310, 36162};
const int time_doc[] = {0, 7200, 13976, 20448, 26843, 33646};

//  a week
void show_help();

int main(int argc, char ** argv) {
    model lda;

    std::vector<int> times_doc (time_doc, time_doc + sizeof(time_doc) / sizeof(time_doc[0]) );

    for (std::vector<int>::iterator it = times_doc.begin(); it != times_doc.end() - 1; ++it){
        int start = *it;
        int end = *(it+1);
        cout << start << "\n" << "--------------" << "\n";
        //printf("%i",end);

        if (lda.init(argc, argv, start, end)) {
            show_help();
            return 1;
        }
    
        if (lda.model_status == MODEL_STATUS_EST || lda.model_status == MODEL_STATUS_ESTC) {
            // parameter estimation
            lda.estimate(start,end);
        }
    
        if (lda.model_status == MODEL_STATUS_INF) {
            // do inference
            lda.inference();
    }

    }
    
    
    
    return 0;
}

void show_help() {
    printf("Command line usage:\n");
    printf("\tlda -est -alpha <double> -beta <double> -ntopics <int> -niters <int> -savestep <int> -twords <int> -dfile <string>\n");
    printf("\tlda -estc -dir <string> -model <string> -niters <int> -savestep <int> -twords <int>\n");
    printf("\tlda -inf -dir <string> -model <string> -niters <int> -twords <int> -dfile <string>\n");
    // printf("\tlda -inf -dir <string> -model <string> -niters <int> -twords <int> -dfile <string> -withrawdata\n");
}

