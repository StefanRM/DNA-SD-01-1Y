#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASSERT(cond, msg) if (!(cond)) { printf("Testul %s nu a fost trecut.\n", msg); return 0; } else { printf("."); }

#include "dna.h"


int main() {
    char *s;
    Nucleotides *n;

    printf("Se testeaza countNucleotides\n");

    s = "";
    n = countNucleotides(s);
    ASSERT((n->A == 0 && n->C == 0 && n->G == 0 && n->T == 0), "countNucleotides-01");
    free(n);

    s = "ACGT";
    n = countNucleotides(s);
    ASSERT((n->A == 1 && n->C == 1 && n->G == 1 && n->T == 1), "countNucleotides-02");
    free(n);

    s = "AAAA";
    n = countNucleotides(s);
    ASSERT((n->A == 4 && n->C == 0 && n->G == 0 && n->T == 0), "countNucleotides-03");
    free(n);

    s = "AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC";
    n = countNucleotides(s);
    ASSERT((n->A == 20 && n->C == 12 && n->G == 17 && n->T == 21), "countNucleotides-04");
    free(n);

    //////////////////

    printf("\nSe testeaza computeRNA\n");

    s = computeRNA("");
    ASSERT(!strcmp(s, ""), "computeRNA-01");
    free(s);

    s = computeRNA("ACGT");
    ASSERT(!strcmp(s, "ACGU"), "computeRNA-02");
    free(s);

    s = computeRNA("TTTT");
    ASSERT(!strcmp(s, "UUUU"), "computeRNA-03");
    free(s);

    s = computeRNA("ACGG");
    ASSERT(!strcmp(s, "ACGG"), "computeRNA-04");
    free(s);

    s = computeRNA("GATGGAACTTGACTACGTAAATT");
    ASSERT(!strcmp(s, "GAUGGAACUUGACUACGUAAAUU"), "computeRNA-05");
    free(s);

    /////////////////

    printf("\nSe testeaza complementDNA\n");

    s = complementDNA("");
    ASSERT(!strcmp(s, ""), "complementDNA-01");
    free(s);

    s = complementDNA("AAAA");
    ASSERT(!strcmp(s, "TTTT"), "complementDNA-02");
    free(s);

    s = complementDNA("C");
    ASSERT(!strcmp(s, "G"), "complementDNA-03");
    free(s);

    s = complementDNA("ATATA");
    ASSERT(!strcmp(s, "TATAT"), "complementDNA-04");
    free(s);

    s = complementDNA("AAAACCCGGT");
    ASSERT(!strcmp(s, "ACCGGGTTTT"), "complementDNA-05");
    free(s);

    /////////////////

    printf("\nSe testeaza countMutations\n");

    ASSERT(countMutations("", "") == 0, "computeMutations-01");
    ASSERT(countMutations("AAA", "AAA") == 0, "computeMutations-02");
    ASSERT(countMutations("ACGT", "GATC") == 4, "computeMutations-03");
    ASSERT(countMutations("AAAAT", "AAAAC") == 1, "computeMutations-04");
    ASSERT(countMutations("GAGCCTACTAACGGGAT", "CATCGTAATGACGGCCT") == 7, "computeMutations-05");
	
    printf("\n");
    
    printf("\nSe testeaza levensteinDistance\n");
    ASSERT(levenshteinDistance("", "") == 0, "levenshteinDistance-01");
    ASSERT(levenshteinDistance("AAAA", "ACAC") == 2, "levenshteinDistance-02");
    ASSERT(levenshteinDistance("AAAA", "ACACGGG") == 5, "levenshteinDistance-03");
    ASSERT(levenshteinDistance("ACGT", "A") == 3, "levenshteinDistance-04");
    return 0;
}

