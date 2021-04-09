/* Data initial */
// int max_time = 20;
// tproc tasks[] = {
//     {1,0,3,3},
//     {2,2,6,6},
//     {3,4,4,4},
//     {4,6,5,5},
//     {5,8,2,2}
// };

/* quantum q pour le scheduler rr */
int q = 1;

/* test pour les proprietees de FCFS */
// int max_time = 49;
// tproc tasks[] = {
//     {1,0,12,12},
//     {2,2,6,6},
//     {3,4,24,24},
//     {4,6,5,5},
//     {5,8,2,2}
// };

/* test pour les proprietees de RR */
// int q = 6;

/* TD7 */
// int max_time = 40;
// tproc tasks[] = {
//   //pid  //activation  //length  //remaining  //period
//   {1,0,1,1,3},
//   {2,0,1,1,4},
//   {3,0,2,2,6},
// };

/* mise en evidance des taches qui ne satisfont pas leurs echeances */
int max_time = 40;
tproc tasks[] = {
  //pid  //activation  //length  //remaining  //period
  {1,0,2,2,5},
  {2,0,2,2,6},
  {3,0,2,2,7},
  {4,0,2,2,8},
};

/* Ce test est ordonnancable avec EDF mais pas avec RM */
// int max_time = 40;
// tproc tasks[] = {
//   //pid  //activation  //length  //remaining  //period
//   {1,0,8,8,13},
//   {2,0,6,6,19},
// };
