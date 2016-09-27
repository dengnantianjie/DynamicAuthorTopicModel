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


/* 
 * References:
 * + The Java code of Gregor Heinrich (gregor@arbylon.net)
 *   http://www.arbylon.net/projects/LdaGibbsSampler.java
 * + "Parameter estimation for text analysis" by Gregor Heinrich
 *   http://www.arbylon.net/publications/text-est.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>    ///////////
#include "constants.h"
#include "strtokenizer.h"
#include "utils.h"
#include "dataset.h"
#include "model.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <math.h>

using namespace std;

#ifndef M_PIl
/** The constant Pi in high precision */
#define M_PIl 3.1415926535897932384626433832795029L
#endif
#ifndef M_GAMMAl
/** Euler's constant in high precision */
#define M_GAMMAl 0.5772156649015328606065120900824024L
#endif
#ifndef M_LN2l
/** the natural logarithm of 2 in high precision */
#define M_LN2l 0.6931471805599453094172321214581766L
#endif


model::~model() {
    if (p) {
	delete p;
    }

    if (p_pa) {
    delete p_pa;
    }

    if (pa) {
    delete pa;
    }

    if (ptrndata) {
	delete ptrndata;
    }
    
    if (pnewdata) {
	delete pnewdata;
    }

    if (z) {
	for (int m = 0; m < M; m++) {
	    if (z[m]) {
		delete z[m];
	    }
	}
    }

    if (x) {
    for (int m = 0; m < M; m++) {
        if (x[m]) {
        delete x[m];
        }
    }
    }
    
    if (nw) {
	for (int w = 0; w < V; w++) {
	    if (nw[w]) {
		delete nw[w];
	    }
	}
    }

    if (na) {
    for (int a = 0; a < A; a++) {
        if (na[a]) {
        delete na[a];
        }
    }
    }

    if (nd) {
	for (int m = 0; m < M; m++) {
	    if (nd[m]) {
		delete nd[m];
	    }
	}
    } 
    
    if (nwsum) {
	delete nwsum;
    }  

    if (beta_phi){
    delete beta_phi;
    } 

    if (alpha_theta){
    delete alpha_theta;
    }
    
    if (ndsum) {
	delete ndsum;
    }

    if (nasum) {
    delete nasum;
    }
    
    if (theta) {
	for (int m = 0; m < A; m++) {
	    if (theta[m]) {
		delete theta[m];
	    }
	}
    }

    if (alpha_tim) {
    
        delete alpha_tim;
    
    }
    
    if (phi) {
	for (int k = 0; k < K; k++) {
	    if (phi[k]) {
		delete phi[k];
	    }
	}
    }

     if (beta_tim) {
     
         delete beta_tim;
       
     }

    // only for inference
    if (newz) {
	for (int m = 0; m < newM; m++) {
	    if (newz[m]) {
		delete newz[m];
	    }
	}
    }

    if (newx) {
    for (int m = 0; m < newM; m++) {
        if (newx[m]) {
        delete newx[m];
        }
    }
    }
    
    if (newnw) {
	for (int w = 0; w < newV; w++) {
	    if (newnw[w]) {
		delete newnw[w];
	    }
	}
    }

    if (newnd) {
	for (int m = 0; m < newM; m++) {
	    if (newnd[m]) {
		delete newnd[m];
	    }
	}
    } 

    if (newna) {
    for (int a = 0; a < newA; a++) {
        if (newna[a]) {
        delete newna[a];
        }
    }
    } 
    
    if (newnwsum) {
	delete newnwsum;
    }   
    
    if (newndsum) {
	delete newndsum;
    }

    if (newnasum) {
    delete newnasum;
    }
    
    if (newtheta) {
	for (int m = 0; m < newM; m++) {
	    if (newtheta[m]) {
		delete newtheta[m];
	    }
	}
    }
    
    if (newphi) {
	for (int k = 0; k < K; k++) {
	    if (newphi[k]) {
		delete newphi[k];
	    }
	}
    }
}

void model::set_default_values() {      //////// finish 
    wordmapfile = "wordmap.txt";
    trainlogfile = "trainlog.txt";
    tassign_suffix = ".tassign";
    theta_suffix = ".theta";
    phi_suffix = ".phi";
    others_suffix = ".others";
    twords_suffix = ".twords";

    aassign_suffix = ".aassign";
    atopics_suffix = ".atopics";
    
    dir = "./";
    dfile = "trndocs.dat";
    model_name = "model-final";    
    model_status = MODEL_STATUS_UNKNOWN;
    
    ptrndata = NULL;
    pnewdata = NULL;
    
    M = 0;
    V = 0;
    K = 100;
    alpha = 0.1;  //////////////////50 /  K
    beta = 1;
    A = 9;    //////
    A_perD = 1; //////
    niters = 2000;
    liter = 0;
    savestep = 200;    
    twords = 0;
    withrawstrs = 0;
    
    p = NULL;
    pa = NULL;
    p_pa = NULL;
    z = NULL;
    x = NULL; ///////
    nw = NULL;
    nd = NULL;
    na = NULL;
    nwsum = NULL;
    ndsum = NULL;
    beta_phi = NULL;
    alpha_theta = NULL;
    newnasum = NULL;   ///////
    theta = NULL;
    phi = NULL;
    alpha_tim = NULL;
    beta_tim = NULL;
    
    newM = 0;
    newV = 0;
    newA = 0;
    newz = NULL;
    newx = NULL;   /////////
    newnw = NULL;
    newnd = NULL;
    newna = NULL;   ////
    newnwsum = NULL;
    newndsum = NULL;
    newtheta = NULL;
    newphi = NULL;
}

int model::parse_args(int argc, char ** argv) {
    return utils::parse_args(argc, argv, this);
}

int model::init(int argc, char ** argv, int start , int end) {
    // call parse_args
    if (parse_args(argc, argv)) {
	return 1;
    }
    
    if (model_status == MODEL_STATUS_EST) {
	// estimating the model from scratch
	if (init_est(start, end)) {
	    return 1;
	}
	
    } else if (model_status == MODEL_STATUS_ESTC) {
	// estimating the model from a previously estimated one
	if (init_estc()) {
	    return 1;
	}
	
    } else if (model_status == MODEL_STATUS_INF) {
	// do inference
	if (init_inf()) {
	    return 1;
	}
    }
    
    return 0;
}

int model::load_model(string model_name) {  //// not yet
    int i, j;
    
    string filename = dir + model_name + tassign_suffix;
    FILE * fin = fopen(filename.c_str(), "r");
    if (!fin) {
	printf("Cannot open file %s to load model!\n", filename.c_str());
	return 1;
    }
    
    char buff[BUFF_SIZE_LONG];
    string line;

    // allocate memory for z and ptrndata
    z = new int*[M];
    ptrndata = new dataset(M);
    ptrndata->V = V;

    for (i = 0; i < M; i++) {
	char * pointer = fgets(buff, BUFF_SIZE_LONG, fin);
	if (!pointer) {
	    printf("Invalid word-topic assignment file, check the number of docs!\n");
	    return 1;
	}
	
	line = buff;
	strtokenizer strtok(line, " \t\r\n");
	int length = strtok.count_tokens();
	
	vector<int> words;
	vector<int> topics;
	for (j = 0; j < length; j++) {
	    string token = strtok.token(j);
    
	    strtokenizer tok(token, ":");
	    if (tok.count_tokens() != 2) {
		printf("Invalid word-topic assignment line!\n");
		return 1;
	    }
	    
	    words.push_back(atoi(tok.token(0).c_str()));
	    topics.push_back(atoi(tok.token(1).c_str()));
	}
	
	// allocate and add new document to the corpus
	document * pdoc = new document(words);
	ptrndata->add_doc(pdoc, i);
	
	// assign values for z
	z[i] = new int[topics.size()];
	for (j = 0; j < topics.size(); j++) {
	    z[i][j] = topics[j];
	}
    }   
    
    fclose(fin);
    
    return 0;
}

int model::load_model_author(string model_name) {  //// not yet
    int i, j;
    
    string filename = dir + model_name + aassign_suffix;
    FILE * fin = fopen(filename.c_str(), "r");
    if (!fin) {
    printf("Cannot open file %s to load model!\n", filename.c_str());
    return 1;
    }
    
    char buff[BUFF_SIZE_LONG];
    string line;

    // allocate memory for z and ptrndata
    x = new int*[M];
    ptrndata = new dataset(M);
    ptrndata->V = V;

    for (i = 0; i < M; i++) {
    char * pointer = fgets(buff, BUFF_SIZE_LONG, fin);
    if (!pointer) {
        printf("Invalid word-topic assignment file, check the number of docs!\n");
        return 1;
    }
    
    line = buff;
    strtokenizer strtok(line, " \t\r\n");
    int length = strtok.count_tokens();
    
    vector<int> words;
    vector<int> authors;
    for (j = 0; j < length; j++) {
        string token = strtok.token(j);
    
        strtokenizer tok(token, ":");
        if (tok.count_tokens() != 2) {
        printf("Invalid word-topic assignment line!\n");
        return 1;
        }
        
        words.push_back(atoi(tok.token(0).c_str()));
        authors.push_back(atoi(tok.token(1).c_str()));
    }
    
    // allocate and add new document to the corpus
    document * pdoc = new document(words);
    ptrndata->add_doc(pdoc, i);
    
    // assign values for z
    z[i] = new int[authors.size()];
    for (j = 0; j < authors.size(); j++) {
        x[i][j] = authors[j];
    }
    }   
    
    fclose(fin);
    
    return 0;
}

int model::save_model_temp(string model_name,int start,int end) {   //////// finish
    if (save_model_tassign(dir + model_name + tassign_suffix, start, end)) {
    return 1;
    }
    
    

    if (save_model_aassign(dir + model_name + aassign_suffix, start, end)) {
    return 1;
    }

    if (save_model_theta(dir + model_name + theta_suffix, start, end)) {
    return 1;
    }

    if (save_model_phi(dir + model_name + phi_suffix, start, end)) {
    return 1;
    }

    if (twords > 0) {
    if (save_model_twords(dir + model_name + twords_suffix, start, end)) {
        return 1;
    }
    }
    cout<<"twords";
    
    if (save_model_atopics(dir + model_name + atopics_suffix, start, end)) {
    return 1;
    }
    cout<<"atopics";


    
    return 0;
}

int model::save_model(string model_name,int start,int end) {   //////// finish
 //    if (save_model_tassign(dir + model_name + tassign_suffix, start, end)) {
	// return 1;
 //    }
    
    if (save_model_others(dir + model_name + others_suffix, start, end)) {
	return 1;
    }
    
    if (save_model_theta(dir + model_name + theta_suffix, start, end)) {
	return 1;
    }
    
    if (save_model_phi(dir + model_name + phi_suffix, start, end)) {
	return 1;
    }

    if (save_model_aassign(dir + model_name + aassign_suffix, start, end)) {
     return 1;
     }

    if (twords > 0) {
    if (save_model_twords(dir + model_name + twords_suffix, start, end)) {
        return 1;
    }
    }
    cout<<"twords";
    
    if (save_model_atopics(dir + model_name + atopics_suffix, start, end)) {
    return 1;
    }
    cout<<"atopics";

    
    return 0;
}

int model::save_model_tassign(string filename,int start,int end) {
    int i, j;
    cout << "save topic assign";
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    // wirte docs with topic assignments for words
    for (i = start; i < end; i++) {  
        
    //for (i = start; i < end; i++) {    
	for (j = 0; j < ptrndata->docs[i]->length; j++) {
	    fprintf(fout, "%d:%d ", ptrndata->docs[i]->words[j], z[i][j]);
	}
	fprintf(fout, "\n");
    }

    fclose(fout);
    
    return 0;  ////// finish    ///// done  ////// done
}

int model::save_model_aassign(string filename,int start,int end) {   //////// finish
    int i, j;
    cout << "save author ";
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
    printf("Cannot open file %s to save!\n", filename.c_str());
    return 1;
    }

    // wirte docs with topic assignments for words
    //for (i = 0; i < ptrndata->M; i++) {   
    for (i = start; i < end; i++) {    
    for (j = 0; j < ptrndata->docs[i]->length; j++) {
        fprintf(fout, "%d:%d ", ptrndata->docs[i]->words[j], x[i][j]);
    }
    fprintf(fout, "\n");
    }

    fclose(fout);
    
    return 0;
}

int model::save_model_theta(string filename,int start,int end) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    cout << "save theta ";
    for (int i = 0; i < A; i++) {
	for (int j = 0; j < K; j++) {
	    fprintf(fout, "%f ", theta[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);
    
    return 0;    ///// done
}

int model::save_model_phi(string filename,int start,int end) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    cout << "save phi ";
    for (int i = 0; i < K; i++) {
	for (int j = 0; j < V; j++) {
	    fprintf(fout, "%f ", phi[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);    
    
    return 0;        ///// done
}

int model::save_model_others(string filename,int start,int end) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    fprintf(fout, "alpha=%f\n", alpha);
    fprintf(fout, "beta=%f\n", beta);
    fprintf(fout, "ntopics=%d\n", K);
    fprintf(fout, "ndocs=%d\n", M);
    fprintf(fout, "nwords=%d\n", V);
    fprintf(fout, "liter=%d\n", liter);
    
    fclose(fout);    
    
    return 0;      ///// done
}

int model::save_model_twords(string filename,int start,int end) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    if (twords > V) {
	twords = V;
    }
    mapid2word::iterator it;
    cout << twords;
    for (int k = 0; k < K; k++) {
	vector<pair<int, double> > words_probs;
	pair<int, double> word_prob;
	for (int w = 0; w < V; w++) {
	    word_prob.first = w;
	    word_prob.second = phi[k][w];
	    words_probs.push_back(word_prob);
	}
    //cout << "save topic words";
        // quick sort to sort word-topic probability
	//utils::quicksort(words_probs, 0, words_probs.size() - 1);
	
	fprintf(fout, "Topic %dth:\n", k);
    
	//for (int i = 0; i < twords; i++) {
    for (int i = 0; i < V; i++) {
	    it = id2word.find(words_probs[i].first);
	    if (it != id2word.end()) {
		fprintf(fout, "\t%s   %f\n", (it->second).c_str(), words_probs[i].second);
	    }
	}
    }
    
    fclose(fout);    
    
    return 0;           ///// done
}

int model::save_model_atopics(string filename,int start,int end) {   ///////// finish 
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
    printf("Cannot open file %s to save!\n", filename.c_str());
    return 1;
    }
    printf("atopics good");
    for (int a = 0; a < A; a++) {
    vector<pair<int, double> > topics_probs;
    pair<int, double> topic_prob;
    for (int k = 0; k < K; k++) {
        topic_prob.first = k;
        topic_prob.second = theta[a][k];
        topics_probs.push_back(topic_prob);
    }
    cout << "save topic assign";
        // quick sort to sort word-topic probability
    utils::quicksort(topics_probs, 0, topics_probs.size() - 1);
    
    fprintf(fout, "Author %dth:\n", a);
    for (int i = 0; i < 20; i++) {
    
        fprintf(fout, "\t%d   %f\n", topics_probs[i].first, topics_probs[i].second);
    }
    }
    
    fclose(fout);    
    
    return 0;    
}

int model::save_inf_model(string model_name) {
    if (save_inf_model_tassign(dir + model_name + tassign_suffix)) {
	return 1;
    }
    
    if (save_inf_model_others(dir + model_name + others_suffix)) {
	return 1;
    }
    
    if (save_inf_model_newtheta(dir + model_name + theta_suffix)) {
	return 1;
    }
    
    if (save_inf_model_newphi(dir + model_name + phi_suffix)) {
	return 1;
    }

    if (twords > 0) {
	if (save_inf_model_twords(dir + model_name + twords_suffix)) {
	    return 1;
	}
    }
    if (save_inf_model_aassign(dir + model_name + aassign_suffix)) {
    return 1;
    }
    
    if (save_inf_model_atopics(dir + model_name + atopics_suffix)) {
    return 1;
    }
    
    return 0;       //////// finish
}

int model::save_inf_model_tassign(string filename) {
    int i, j;
    
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    // wirte docs with topic assignments for words
    for (i = 0; i < pnewdata->M; i++) {    
	for (j = 0; j < pnewdata->docs[i]->length; j++) {
	    fprintf(fout, "%d:%d ", pnewdata->docs[i]->words[j], newz[i][j]);
	}
	fprintf(fout, "\n");
    }

    fclose(fout);
    
    return 0;  //// done 
}

int model::save_inf_model_aassign(string filename) {   //////// finish
    int i, j;
    
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
    printf("Cannot open file %s to save!\n", filename.c_str());
    return 1;
    }

    // wirte docs with topic assignments for words
    for (i = 0; i < pnewdata->M; i++) {    
    for (j = 0; j < pnewdata->docs[i]->length; j++) {
        fprintf(fout, "%d:%d ", pnewdata->docs[i]->words[j], newx[i][j]);
    }
    fprintf(fout, "\n");
    }

    fclose(fout);
    
    return 0;
}

int model::save_inf_model_atopics(string filename) {   ///////// finish 
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
    printf("Cannot open file %s to save!\n", filename.c_str());
    return 1;
    }
    
    for (int a = 0; a < A; a++) {
    vector<pair<int, double> > topics_probs;
    pair<int, double> topic_prob;
    for (int k = 0; k < K; k++) {
        topic_prob.first = k;
        topic_prob.second = newtheta[a][k];
        topics_probs.push_back(topic_prob);
    }
    
        // quick sort to sort word-topic probability
    utils::quicksort(topics_probs, 0, topics_probs.size() - 1);
    
    fprintf(fout, "Author %dth:\n", a);
    for (int i = 0; i < (sizeof theta[a] / sizeof theta[a][0]); i++) {
    
        fprintf(fout, "\t%d   %f\n", topics_probs[i].first, topics_probs[i].second);
    }
    }
    
    fclose(fout);    
    
    return 0;    
}

int model::save_inf_model_newtheta(string filename) {
    int i, j;

    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    for (i = 0; i < newA; i++) {
	for (j = 0; j < K; j++) {
	    fprintf(fout, "%f ", newtheta[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);
    
    return 0;  ////// done
}

int model::save_inf_model_newphi(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    for (int i = 0; i < K; i++) {
	for (int j = 0; j < newV; j++) {
	    fprintf(fout, "%f ", newphi[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);    
    
    return 0;  ////// done
}

int model::save_inf_model_others(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    fprintf(fout, "alpha=%f\n", alpha);
    fprintf(fout, "beta=%f\n", beta);
    fprintf(fout, "ntopics=%d\n", K);
    fprintf(fout, "ndocs=%d\n", newM);
    fprintf(fout, "nwords=%d\n", newV);
    fprintf(fout, "liter=%d\n", inf_liter);
    
    fclose(fout);    
    
    return 0;  ////// done
}

int model::save_inf_model_twords(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    if (twords > newV) {
	twords = newV;
    }
    mapid2word::iterator it;
    map<int, int>::iterator _it;
    
    for (int k = 0; k < K; k++) {
	vector<pair<int, double> > words_probs;
	pair<int, double> word_prob;
	for (int w = 0; w < newV; w++) {
	    word_prob.first = w;
	    word_prob.second = newphi[k][w];
	    words_probs.push_back(word_prob);
	}
    
        // quick sort to sort word-topic probability
	utils::quicksort(words_probs, 0, words_probs.size() - 1);
	
	fprintf(fout, "Topic %dth:\n", k);
	for (int i = 0; i < twords; i++) {
	    _it = pnewdata->_id2id.find(words_probs[i].first);
	    if (_it == pnewdata->_id2id.end()) {
		continue;
	    }
	    it = id2word.find(_it->second);
	    if (it != id2word.end()) {
		fprintf(fout, "\t%s   %f\n", (it->second).c_str(), words_probs[i].second);
	    }
	}
    }
    
    fclose(fout);    
    
    return 0;       ////// done
}


int model::init_est(int start, int end) {     ///////// finish 
    int m, n, w, k;
    int a;
    printf("init good \n");
    p = new double[K];
    pa = new double[A];
    p_pa = new double[A*K];
    
    // + read training data  first time //////////////// first time
    if (start == 0){
    ptrndata = new dataset;
    if (ptrndata->read_trndata(dir + dfile, dir + wordmapfile)) {
        printf("Fail to read training data!\n");
        return 1;
    }
	
    // + allocate memory and assign values for variables
    M = ptrndata->M;
    V = ptrndata->V;
    
    }
    // K: from command line or default value
    // alpha, beta: from command line or default values
    // niters, savestep: from command line or default values

    nw = new int*[V];
    for (w = 0; w < V; w++) {
        nw[w] = new int[K];
        for (k = 0; k < K; k++) {
    	    nw[w][k] = 0;
        }
    }
	
    nd = new int*[M];
    for (m = 0; m < M; m++) {
        nd[m] = new int[K];
        for (k = 0; k < K; k++) {
    	    nd[m][k] = 0;
        }
    }

    na = new int*[A];
    for (a = 0; a < A; a++) {
        na[a] = new int[K];
        for (k = 0; k < K; k++) {
            na[a][k] = 0;
        }
    }

    beta_phi = new double[K];
    for (k = 0; k < K; k++) {
    beta_phi[k] = 0;
    }

    alpha_theta = new double[A];
    for (a = 0; a < A; a++) {
    alpha_theta[a] = 0;
    }
    
    nwsum = new int[K];
    for (k = 0; k < K; k++) {
	nwsum[k] = 0;
    }
    
    ndsum = new int[M];
    for (m = 0; m < M; m++) {
	ndsum[m] = 0;
    }

    nasum = new int[A];
    for (a = 0; a < A; a++) {
    nasum[a] = 0;
    }

    z = new int*[M];
    x = new int*[M];
////////////--------------------------
    if (start == 0){
    theta = new double*[A];
    for (a = 0; a < A; a++) {
        theta[a] = new double[K];
        for (k = 0; k < K; k++) {
            theta[a][k] = 0.05;
        }
    }

    phi = new double*[K];
    for (k = 0; k < K; k++) {
        phi[k] = new double[V];
        for (w = 0; w < V; w++) {
            phi[k][w] = 0.000002;
        }
    }  

    alpha_tim = new float[K];
    for (k = 0; k < K; k++) {  
        alpha_tim[k] = alpha;
    }

    beta_tim = new float[V];
    
        for (w = 0; w < V; w++) {
            beta_tim[w] = beta;
    }
   
    

    }

    


    

    


////////---------------------
    srandom(time(0)); // initialize for random number generation
    
    for (m = start; m < end; m++) {
	int N = ptrndata->docs[m]->length;

	z[m] = new int[N];
	x[m] = new int[N];
        // initialize for z
        for (n = 0; n < N; n++) {
    	    int topic = (int)(((double)random() / RAND_MAX) * K);
            int author = (int)(((double)random() / RAND_MAX) * A);
            //cout <<"topic" << topic << "\n";
            //cout <<"author" << author << "\n";
            
    	    z[m][n] = topic;
            x[m][n] = author;
    	    
    	    // number of instances of word i assigned to topic j
    	    nw[ptrndata->docs[m]->words[n]][topic] += 1;
    	    // number of words in document i assigned to topic j
    	    nd[m][topic] += 1;
            na[author][topic] += 1;
    	    // total number of words assigned to topic j
    	    nwsum[topic] += 1;
            nasum[author] += 1;
            
            alpha_theta[author] = alpha_theta[author] + alpha_tim[topic]*theta[author][topic];

            int w = ptrndata->docs[m]->words[n];
            beta_phi[topic] = beta_phi[topic] + beta_tim[w]*phi[topic][w];
        } 
        // total number of words in document i
        ndsum[m] = N;      
    }

    
    return 0;
}

int model::init_estc() {     ////////// finish
    // estimating the model from a previously estimated one
    int m, n, w, k;

    int a;

    p = new double[K];
    pa = new double[A];

    // load moel, i.e., read z and ptrndata
    if (load_model(model_name)) {
    printf("Fail to load word-topic assignmetn file of the model!\n");
    return 1;
    }

    if (load_model_author(model_name)) {
    printf("Fail to load author-topic assignmetn file of the model!\n");
    return 1;
    }

    nw = new int*[V];
    for (w = 0; w < V; w++) {
        nw[w] = new int[K];
        for (k = 0; k < K; k++) {
            nw[w][k] = 0;
        }
    }
    
    nd = new int*[M];
    for (m = 0; m < M; m++) {
        nd[m] = new int[K];
        for (k = 0; k < K; k++) {
            nd[m][k] = 0;
        }
    }

    na = new int*[A];
    for (a = 0; a < A; a++) {
        na[a] = new int[K];
        for (k = 0; k < K; k++) {
            na[a][k] = 0;
        }
    }
    
    nwsum = new int[K];
    for (k = 0; k < K; k++) {
    nwsum[k] = 0;
    }
    
    ndsum = new int[M];
    for (m = 0; m < M; m++) {
    ndsum[m] = 0;
    }

    nasum = new int[A];
    for (a = 0; a < A; a++) {
    nasum[a] = 0;
    }

    for (m = 0; m < ptrndata->M; m++) {
    int N = ptrndata->docs[m]->length;

    // assign values for nw, nd, nwsum, and ndsum   
        for (n = 0; n < N; n++) {
            int w = ptrndata->docs[m]->words[n];
            int topic = z[m][n];
            int author = x[m][n];
            
            // number of instances of word i assigned to topic j
            nw[w][topic] += 1;
            // number of words in document i assigned to topic j
            nd[m][topic] += 1;
            na[author][topic] += 1;
            // total number of words assigned to topic j
            nwsum[topic] += 1;
            nasum[author] += 1;
        } 
        // total number of words in document i
        ndsum[m] = N;      
    }
    
    theta = new double*[A];
    for (a = 0; a < A; a++) {
        theta[a] = new double[K];
    }
    
    phi = new double*[K];
    for (k = 0; k < K; k++) {
        phi[k] = new double[V];
    }      

    return 0;      
}

void model::estimate(int start, int end) {    /////////////  finish
    if (twords > 0) {
	// print out top words per topic
	dataset::read_wordmap(dir + wordmapfile, &id2word);
    }
   // printf("1 good \n");
   // printf("1 good \n");
   // printf("1 good \n");
    
    
    if (start == 0){
        tem_iter = liter;
    }else{
        liter = tem_iter;
    }

    int last_iter = liter;
    cout << phi[0][0];
    cout << "\n";
    cout << alpha_tim[0];
    cout << "\n" << "--------";

    for (liter = last_iter + 1; liter <= niters + last_iter; liter++) {
	
	// for all z_i
    
    
	for (int m = start; m < end; m++) {


	    for (int n = 0; n < ptrndata->docs[m]->length; n++) {
		// (z_i = z[m][n])
		// sample from p(z_i|z_-i, w)
		//int topic = sampling(m, n);
        

        pair<int, int> topic_author = sampling(m,n);
        // if (topic_author.first > 99)
        //     {cout<< topic_author.first;
        //     cout<< "topics\n";}
        // if (topic_author.second > 8)
        //     {cout<< topic_author.second;
        //     cout<< "author\n";}
		z[m][n] = topic_author.first;
        x[m][n] = topic_author.second;
	    }
	}
	//printf("2 good \n");
	if (savestep > 0) {
	    if (liter % savestep == 0) {
		// saving the model
		
        //printf("3 good \n");
		compute_theta();
        //printf("4 good \n");
		compute_phi();
		save_model(utils::generate_model_name(liter),start,end);
	    }
	}
    }
    
    printf("Gibbs sampling completed!\n");
    printf("Saving the final model!\n");
    printf("Saving the final model!\n");
    update_theta();
    printf("1!\n");
    update_phi(start,end);
    printf("2!\n");
    update_alpha();
    printf("3!\n");
    update_beta(start,end);
    printf("4!\n");
    save_model_temp(utils::generate_model_name(start),start,end);    

    
    liter--;
    cout << end;
    if (end == 36162){
        save_model(utils::generate_model_name(-1),start,end);
    }
    
}

pair<int, int> model::sampling(int m, int n) {   //////////// finish
    // remove z_i from the count variables
    
    
    int topic = z[m][n];
    int author = x[m][n];

    int w = ptrndata->docs[m]->words[n];
    nw[w][topic] -= 1;
    nd[m][topic] -= 1;
    na[author][topic] -= 1;
    nwsum[topic] -= 1;
    nasum[author] -= 1;
    ndsum[m] -= 1;

    //double Vbeta = V * beta;
    //double Kalpha = K * alpha;

    vector<pair<int, int> > topic_author_pairs;

    // do multinomial sampling via cumulative method
    for (int k = 0; k < K; k++) {
	p[k] =  (nw[w][k] + beta_tim[w]*phi[k][w]) / (nwsum[k] + beta_phi[k]) *
             (na[author][k] + alpha_tim[k]*theta[author][k]) / (nasum[author] + alpha_theta[author]);
    
    }

    for (int a = 0; a < A; a++){
    pa[a] = (na[a][topic] + alpha_tim[topic]*theta[a][topic]) / (nasum[a] + alpha_theta[a]);
    }
    //printf("stop1");
    // for (int a = 0; a < A; a++){
    //     for (int k = 0; k < K; k++) {
    //     topic_author_pairs.push_back(std::make_pair(a, k));
    //     p_pa[K*a+k] = (nw[w][k] + beta_tim[k][w]*phi[k][w]) / (nwsum[k] + beta_phi[k]) *
    //         (na[a][k] + alpha_tim[a][k]*theta[a][k]) / (nasum[a] + alpha_theta[a]);
        
        
    // }
    // }
    //printf("stop1");
    //printf("1 %i \n", n);
    // cumulate multinomial parameters
 //    for (int i = 1; i < A*K; i++){
	// p_pa[i] += p_pa[i - 1];
 //    }
    
    for (int a = 1; a < A; a++){
    pa[a] += pa[a - 1];
    }

    for (int k = 1; k < K; k++){
    p[k] += p[k - 1];
    }
    // scaled sample because of unnormalized p[]
    double u = ((double)random() / RAND_MAX) * p[K - 1];
    double uu = ((double)random() / RAND_MAX) * pa[A - 1];
    //printf("N %f ...\n", p_pa[A-1][K-1]);
    //double u = ((double)random() / RAND_MAX) * p_pa[A*K - 1];
    //printf("M %f  ...\n", u);
        //printf("M %i ...\n", topic);
 //    for (int j = 0; j < A * K; j++)
	// if (p_pa[j] > u) {
 //        std::pair<int, int> new_elem = topic_author_pairs.at(j);
 //        author = new_elem.first;
 //        topic = new_elem.second;
 //        //printf("author %i  ...\n", author);
 //        //printf("topic %i  ...\n", topic);
 //        break;
 //    }
    //printf("stop1");
    //for (author = 0; author < A; author++) {
    //if (pa[author] > uu) {
    //    break;
    //}
    //}
    for (topic = 0; topic < K; topic++) {
    if (p[topic] > u) {
        break;
    }
    }

    for (author = 0; author < A; author++) {
    if (pa[author] > uu) {
        break;
    }
    }

    /////// 
    // add newly estimated z_i to count variables
    nw[w][topic] += 1;
    nd[m][topic] += 1;
    na[author][topic] += 1;
    nwsum[topic] += 1;
    ndsum[m] += 1;  
    nasum[author] += 1;  
    
    return make_pair(topic,author);
}

void model::compute_theta() {     ///////////////////// finish
    for (int a = 0; a < A; a++) {  ////////////////
	for (int k = 0; k < K; k++) {
	    theta[a][k] = (na[a][k] + alpha) / (nasum[a] + K * alpha);
	}
    }
}

void model::update_theta() { 
    printf("update_theta");    ///////////////////// finish
    for (int a = 0; a < A; a++) {  ////////////////
    for (int k = 0; k < K; k++) {
        if ((nasum[a] + alpha_theta[a]) == 0){
            theta[a][k] = theta[a][k];
        }else if((na[a][k] + alpha_tim[k]*theta[a][k]) / (nasum[a] + alpha_theta[a])>pow(10,-2)){
            theta[a][k] = (na[a][k] + alpha_tim[k]*theta[a][k]) / (nasum[a] + alpha_theta[a]);
        }else{
            //theta[a][k] = theta[a][k];
            theta[a][k] = theta[a][k];
        }

           

    }
    }
}

void model::compute_phi() {    ////////////// finish
    for (int k = 0; k < K; k++) {
	for (int w = 0; w < V; w++) {
        
            phi[k][w] = (nw[w][k] + beta) / (nwsum[k] + V * beta);
        
	}
    }
}

void model::update_phi(int start, int end){
    printf("update theta");

    for (int k = 0; k < K; k++) {
    for (int m = start; m < end; m++) {
        int N = ptrndata->docs[m]->length;
        for (int n = 0; n < N; n++) {
            int w = ptrndata->docs[m]->words[n];
            if ((nwsum[k] + beta_phi[k]) == 0){
            phi[k][w] = phi[k][w];
        }else if(((nw[w][k] + beta_tim[w]*phi[k][w]) / (nwsum[k] + beta_phi[k]))>pow(10,-5)){
            phi[k][w] = (nw[w][k] + beta_tim[w]*phi[k][w]) / (nwsum[k] + beta_phi[k]);
        }else{
            //phi[k][w] = phi[k][w];
            phi[k][w] = phi[k][w];
        }


        }
    }}
}

void model::update_alpha(){
    printf("update alpha");
    
    for (int k = 0; k < K; k++){
        float numerator = 0;
        float denominator = 0;
        float sum1 = 0;
        float sum2 = 0;
        for (int a = 0; a < A; a++){

        if ((na[a][k] + alpha_tim[k]*theta[a][k]) != 0){
            sum1 = alpha_tim[k] * (digammal(na[a][k] + alpha_tim[k]*theta[a][k]) - digammal(alpha_tim[k]*theta[a][k]));
        // cout << nasum[a] + alpha_theta[a];
        // cout << "\n";
        // cout << alpha_theta[a];
        // cout << "\n";
            numerator = numerator + sum1;
        }else{
            numerator = numerator + 0;
        }
        if ((nasum[a] + alpha_theta[a])!=0){
            //sum2 = log(theta[a][k])*(digammal(nasum[a] + alpha_theta[a])-digammal(alpha_theta[a]));
            sum2 = (digammal(nasum[a] + alpha_theta[a])-digammal(alpha_theta[a]));
            denominator = denominator + sum2;
        }else{
            denominator = denominator + 0;
        }
        
        
        
        }
        if (denominator != 0 && pow(10,-2) < (numerator/denominator) && (numerator/denominator) <10){
            alpha_tim[k] = numerator/denominator;
        }else{
            //alpha_tim[k] = alpha_tim[k];
            alpha_tim[k] = alpha_tim[k];
            //cout << alpha_tim[k] << "\n" << "    this is alpha" << "\n";
        }
        
        
    // for (int a = 0; a < A; a++){
    //     alpha_tim[a][k] = numerator/denominator;
    //     cout << alpha_tim[a][k] ;
    //     cout << "\n";
        
    // }
    }
    

}

void model::update_beta(int start, int end){
    printf( "update beta");

      
    std::vector<double> C (K);  
    for (int k = 0; k < K; k++) {
            //cout << k << "\n" ;
            double temp ;
            if ((nwsum[k] + beta_phi[k])!=0){
             temp = digammal(nwsum[k] + beta_phi[k]) - digammal(beta_phi[k]);
        }else{
             temp = 0;
        }
            //cout << temp << "\n" << "    this is temp" << "\n";

            C.at(k) = temp;
            
        }


    for (int m = start; m < end; m++) {
        
        int N = ptrndata->docs[m]->length;
        //cout << m << "\n";
        //printf("m %d iterations for inference!\n", m);
        
        for (int n = 0; n < N; n++) {
            int w = ptrndata->docs[m]->words[n];
            float numerator = 0;
            float denominator = 0;
            for (int k = 0; k < K; k++) {
            // cout << beta_tim[k][w];
            // cout << "\n";
            // cout << nw[w][k];
            // cout << "\n";
            // cout << phi[k][w];
            // cout << "\n";
            //cout << k << "\n";
            //  cout << nwsum[k];
            //  cout << "\n" << "------------";
            // cout << beta_phi[k];
            //  cout << "\n";
            // cout << phi[k][w];
            // cout << "\n";
            // cout << "--------------";
            // cout << "\n";

            if (((nw[w][k] + beta_tim[w]*phi[k][w]) != 0) && (beta_tim[w]*phi[k][w] != 0)){
                numerator = numerator + beta_tim[w] * phi[k][w] * (digammal(nw[w][k] + beta_tim[w]*phi[k][w])-digammal(beta_tim[w]*phi[k][w]));

            }else
            {
                numerator = numerator + 0;
            }
            // else{
            //     numerator = numerator;
            // }
            //denominator = denominator + (digammal(nwsum[k] + beta_phi[k]) - digammal(beta_phi[k]))*phi[k][w];
            //cout << C[k] << "\n" << "    this is C";
            
                denominator = denominator + (C[k]*phi[k][w]);
            // }else{
            //     denominator = denominator;
            // }
            
            //cout << nw[w][k] << "," <<(nw[w][k] + beta_tim[w]*phi[k][w]) << "," << digammal(nw[w][k] + beta_tim[w]*phi[k][w]) << "," << (beta_tim[w]*phi[k][w]) << "," << digammal(beta_tim[w]*phi[k][w])<<"\n";
            //cout << nwsum[k] << "," <<(nwsum[k] + beta_phi[k]) << "," << digammal(nwsum[k] + beta_phi[k]) << "," << (beta_phi[k]) << "," << digammal(beta_phi[k])<<"\n";
            
        }

        //cout << numerator << "\n" << denominator << "----" << "\n";
        if (denominator != 0 && pow(10,-2) < (numerator/denominator) && (numerator/denominator) <10){
            beta_tim[w] = numerator/denominator;
            //cout << beta_tim[w] << "\n" << "    this is beta" << "\n";
        }else{
            //beta_tim[w] = beta_tim[w] ;
            beta_tim[w] = beta_tim[w];
        }
       
        

        // float temp_value = numerator/denominator;
        
        // for (int k = 0; k < K; k++) {
        //     beta_tim[k][w] = temp_value;
            

        // }
        
    }
    }

    
}


 

int model::init_inf() {     //////// finish 
    // estimating the model from a previously estimated one
    int m, n, w, k;
    int a;

    p = new double[K];

    // load moel, i.e., read z and ptrndata
    if (load_model(model_name)) {
	printf("Fail to load word-topic assignmetn file of the model!\n");
	return 1;
    }

    if (load_model_author(model_name)) {
    printf("Fail to load author-topic assignmetn file of the model!\n");
    return 1;
    }

    nw = new int*[V];
    for (w = 0; w < V; w++) {
        nw[w] = new int[K];
        for (k = 0; k < K; k++) {
    	    nw[w][k] = 0;
        }
    }
	
    nd = new int*[M];
    for (m = 0; m < M; m++) {
        nd[m] = new int[K];
        for (k = 0; k < K; k++) {
    	    nd[m][k] = 0;
        }
    }

    na = new int*[A];
    for (a = 0; a < A; a++) {
        na[a] = new int[K];
        for (k = 0; k < K; k++) {
            na[a][k] = 0;
        }
    }
	
    nwsum = new int[K];
    for (k = 0; k < K; k++) {
	nwsum[k] = 0;
    }
    
    ndsum = new int[M];
    for (m = 0; m < M; m++) {
	ndsum[m] = 0;
    }

    nasum = new int[A];
    for (a = 0; a < A; a++) {
    nasum[a] = 0;
    }

    for (m = 0; m < ptrndata->M; m++) {
	int N = ptrndata->docs[m]->length;

	// assign values for nw, nd, nwsum, and ndsum	
        for (n = 0; n < N; n++) {
    	    int w = ptrndata->docs[m]->words[n];
    	    int topic = z[m][n];
            int author = x[m][n];
    	    
    	    // number of instances of word i assigned to topic j
    	    nw[w][topic] += 1;
    	    // number of words in document i assigned to topic j
    	    nd[m][topic] += 1;
            na[author][topic] += 1;
    	    // total number of words assigned to topic j
    	    nwsum[topic] += 1;
            nasum[author] += 1;
        } 
        // total number of words in document i
        ndsum[m] = N;      
    }
    
    // read new data for inference
    pnewdata = new dataset;
    if (withrawstrs) {
	if (pnewdata->read_newdata_withrawstrs(dir + dfile, dir + wordmapfile)) {
    	    printf("Fail to read new data!\n");
    	    return 1;
	}    
    } else {
	if (pnewdata->read_newdata(dir + dfile, dir + wordmapfile)) {
    	    printf("Fail to read new data!\n");
    	    return 1;
	}    
    }
    
    newM = pnewdata->M;
    newV = pnewdata->V;
    newA = A;
    
    newnw = new int*[newV];
    for (w = 0; w < newV; w++) {
        newnw[w] = new int[K];
        for (k = 0; k < K; k++) {
    	    newnw[w][k] = 0;
        }
    }
	
    newnd = new int*[newM];
    for (m = 0; m < newM; m++) {
        newnd[m] = new int[K];
        for (k = 0; k < K; k++) {
    	    newnd[m][k] = 0;
        }
    }

    newna = new int*[A];
    for (a = 0; a < A; a++) {
        newna[a] = new int[K];
        for (k = 0; k < K; k++) {
            newna[a][k] = 0;
        }
    }

	
    newnwsum = new int[K];
    for (k = 0; k < K; k++) {
	newnwsum[k] = 0;
    }
    
    newndsum = new int[newM];
    for (m = 0; m < newM; m++) {
	newndsum[m] = 0;
    }

    newnasum = new int[A];
    for (a = 0; a < A; a++) {
    newnasum[a] = 0;
    }

    srandom(time(0)); // initialize for random number generation
    newz = new int*[newM];
    newx = new int*[newM];
    for (m = 0; m < pnewdata->M; m++) {
	int N = pnewdata->docs[m]->length;
	newz[m] = new int[N];
    newx[m] = new int[N];

	// assign values for nw, nd, nwsum, and ndsum	
        for (n = 0; n < N; n++) {
    	    int w = pnewdata->docs[m]->words[n];
    	    int _w = pnewdata->_docs[m]->words[n];
    	    int topic = (int)(((double)random() / RAND_MAX) * K);
            int author = (int)(((double)random() / RAND_MAX) * A);
    	    newz[m][n] = topic;
            newx[m][n] = author;
    	    
    	    // number of instances of word i assigned to topic j
    	    newnw[_w][topic] += 1;
    	    // number of words in document i assigned to topic j
    	    newnd[m][topic] += 1;
            newna[author][topic] += 1;
    	    // total number of words assigned to topic j
    	    newnwsum[topic] += 1;
            newnasum[author] += 1;
        } 
        // total number of words in document i
        newndsum[m] = N;      
    }    
    
    newtheta = new double*[newA];
    for (a = 0; a < newA; a++) {
        newtheta[a] = new double[K];
    }
	
    newphi = new double*[K];
    for (k = 0; k < K; k++) {
        newphi[k] = new double[newV];
    }    
    
    return 0;        
}

void model::inference() {      /////// finish 
    if (twords > 0) {
	// print out top words per topic
	dataset::read_wordmap(dir + wordmapfile, &id2word);
    }

    printf("Sampling %d iterations for inference!\n", niters);
    
    for (inf_liter = 1; inf_liter <= niters; inf_liter++) {
	printf("Iteration %d ...\n", inf_liter);
	
	// for all newz_i
	for (int m = 0; m < newM; m++) {
	    for (int n = 0; n < pnewdata->docs[m]->length; n++) {
		// (newz_i = newz[m][n])
		// sample from p(z_i|z_-i, w)
		pair<int, int> topic_author = inf_sampling(m, n);
		newz[m][n] = topic_author.first;
        newx[m][n] = topic_author.second;;
	    }
	}
    }
    
    printf("Gibbs sampling for inference completed!\n");
    printf("Saving the inference outputs!\n");
    compute_newtheta();
    compute_newphi();
    inf_liter--;
    save_inf_model(dfile);
}

pair<int, int> model::inf_sampling(int m, int n) {    ///////// finish
    // remove z_i from the count variables
    int topic = newz[m][n];
    int author = newx[m][n];
    int w = pnewdata->docs[m]->words[n];
    int _w = pnewdata->_docs[m]->words[n];
    newnw[_w][topic] -= 1;
    newnd[m][topic] -= 1;
    newna[author][topic] -= 1;
    newnwsum[topic] -= 1;
    newnasum[author] -= 1;
    newndsum[m] -= 1;
    
    double Vbeta = V * beta;
    double Kalpha = K * alpha;
    // do multinomial sampling via cumulative method
    for (int k = 0; k < K; k++) {
	p[k] = (nw[w][k] + newnw[_w][k] + beta) / (nwsum[k] + newnwsum[k] + Vbeta) *
		    (newna[author][k] + alpha) / (newnasum[author] + Kalpha);

    pa[k] = (newna[author][k] + alpha) / (newnasum[author] + Kalpha);

    }
    // cumulate multinomial parameters
    for (int k = 1; k < K; k++) {
	p[k] += p[k - 1];
    pa[k] += pa[k - 1];
    }
    // scaled sample because of unnormalized p[]
    double u = ((double)random() / RAND_MAX) * p[K - 1];
    double uu = ((double)random() / RAND_MAX) * pa[K - 1];
    
    for (topic = 0; topic < K; topic++) {
	if (p[topic] > u) {
	    break;
	}
    }

    for (author = 0; author < A; author++) {
    if (pa[author] > uu) {
        break;
    }
    }
    
    // add newly estimated z_i to count variables
    newnw[_w][topic] += 1;
    newnd[m][topic] += 1;
    newna[author][topic] += 1;
    newnwsum[topic] += 1;
    newndsum[m] += 1;  
    newnasum[author] += 1;    
    
    return make_pair(topic,author);
}

void model::compute_newtheta() {      ///////// finsih 
    for (int a = 0; a < newA; a++) {
	for (int k = 0; k < K; k++) {
	    newtheta[a][k] = (newna[a][k] + alpha) / (newnasum[a] + K * alpha);
	}
    }
}

void model::compute_newphi() {     ////////// finish
    map<int, int>::iterator it;
    for (int k = 0; k < K; k++) {
	for (int w = 0; w < newV; w++) {
	    it = pnewdata->_id2id.find(w);
	    if (it != pnewdata->_id2id.end()) {
		newphi[k][w] = (nw[it->second][k] + newnw[w][k] + beta) / (nwsum[k] + newnwsum[k] + V * beta);
	    }
	}
    }
}

long double model::digammal(long double x)
{
    /* force into the interval 1..3 */
    if( x < 0.0L )
        return digammal(1.0L-x)+M_PIl/tanl(M_PIl*(1.0L-x)) ;    /* reflection formula */
    else if( x < 1.0L )
        return digammal(1.0L+x)-1.0L/x ;
    else if ( x == 1.0L)
        return -M_GAMMAl ;
    else if ( x == 2.0L)
        return 1.0L-M_GAMMAl ;
    else if ( x == 3.0L)
        return 1.5L-M_GAMMAl ;
    else if ( x > 3.0L)
    /* duplication formula */
        return 0.5L*(digammal(x/2.0L)+digammal((x+1.0L)/2.0L))+M_LN2l ;
    else
    {
        /* Just for your information, the following lines contain
         * the Maple source code to re-generate the table that is
         * eventually becoming the Kncoe[] array below
         * interface(prettyprint=0) :
         * Digits := 63 :
         * r := 0 :
         *
         * for l from 1 to 60 do
         *  d := binomial(-1/2,l) :
         *  r := r+d*(-1)^l*(Zeta(2*l+1) -1) ;
         *  evalf(r) ;
         *  print(%,evalf(1+Psi(1)-r)) ;
         *o d :
         *
         * for N from 1 to 28 do
         *  r := 0 :
         *  n := N-1 :
         *
         *  for l from iquo(n+3,2) to 70 do
         *      d := 0 :
         *      for s from 0 to n+1 do
         *       d := d+(-1)^s*binomial(n+1,s)*binomial((s-1)/2,l) :
         *      od :
         *      if 2*l-n > 1 then
         *      r := r+d*(-1)^l*(Zeta(2*l-n) -1) :
         *      fi :
         *  od :
         *  print(evalf((-1)^n*2*r)) ;
         *od :
         *quit :
         */
        static long double Kncoe[] = { .30459198558715155634315638246624251L,
            .72037977439182833573548891941219706L, -.12454959243861367729528855995001087L,
            .27769457331927827002810119567456810e-1L, -.67762371439822456447373550186163070e-2L,
            .17238755142247705209823876688592170e-2L, -.44817699064252933515310345718960928e-3L,
            .11793660000155572716272710617753373e-3L, -.31253894280980134452125172274246963e-4L,
            .83173997012173283398932708991137488e-5L, -.22191427643780045431149221890172210e-5L,
            .59302266729329346291029599913617915e-6L, -.15863051191470655433559920279603632e-6L,
            .42459203983193603241777510648681429e-7L, -.11369129616951114238848106591780146e-7L,
            .304502217295931698401459168423403510e-8L, -.81568455080753152802915013641723686e-9L,
            .21852324749975455125936715817306383e-9L, -.58546491441689515680751900276454407e-10L,
            .15686348450871204869813586459513648e-10L, -.42029496273143231373796179302482033e-11L,
            .11261435719264907097227520956710754e-11L, -.30174353636860279765375177200637590e-12L,
            .80850955256389526647406571868193768e-13L, -.21663779809421233144009565199997351e-13L,
            .58047634271339391495076374966835526e-14L, -.15553767189204733561108869588173845e-14L,
            .41676108598040807753707828039353330e-15L, -.11167065064221317094734023242188463e-15L } ;
        
        register long double Tn_1 = 1.0L ;  /* T_{n-1}(x), started at n=1 */
        register long double Tn = x-2.0L ;  /* T_{n}(x) , started at n=1 */
        register long double resul = Kncoe[0] + Kncoe[1]*Tn ;
        
        x -= 2.0L ;
        
        for(int n = 2 ; n < sizeof(Kncoe)/sizeof(long double) ;n++)
        {
            const long double Tn1 = 2.0L * x * Tn - Tn_1 ;  /* Chebyshev recursion, Eq. 22.7.4 Abramowitz-Stegun */
            resul += Kncoe[n]*Tn1 ;
            Tn_1 = Tn ;
            Tn = Tn1 ;
        }
        return resul ;
    }
}

