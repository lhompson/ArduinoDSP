/*
 * This file contains function which implement convolution,
 * and the dot product for digital signal processing purposes.
 * 
 * 
 * Written by leethompson94@gmail.com, 2020
 */
 
void setup() {
    Serial.begin(9600);
}

void loop() {
   float arr1[7] = {0.0, 1.0, 2.0, 3.44, 4.0, 5.0, 6.0};
   float arr2[7] = {0.0, 0.0, 0.0, 1.00, 0.0, 0.0, 0.0};
   float conv[13];
   Serial.println("convolution = ");
   slowConvolve(arr1, arr2, conv, 7, 7);
   printVec(conv, 21);
   delay(5000);
}

void printVec(float vec[], int N) {
  /*
   * Simple utility for printing arrays.
   */
  for (int index=0; index<N; index++) {
    Serial.println(vec[index]);
  }
}

float dotProduct(float x[], float y[], int n) {
  /*
   * This function performs the dot product of vectors X and Y.
   * Vectors must be of the same length.
   */
   float runningsum = 0.0;
   for (int i = 0; i < n; i++) {
    runningsum = runningsum + round((x[i] * y[i])*100)/100.0; 
   }
   return runningsum;
}

void slowConvolve(float x[], float y[], float conv[], int N, int M) {
  /*
   * Implements convolution with O(N^2). Vector x is of size N,
   * vector Y is of size M. Operations are peformed on result in place.
   */
   int totalsize = N + M - 1;
   float ypadded[totalsize];
   float xpadded[totalsize];

   // Properly pad the Y vector.
   for (int i = 0; i < N; i++) {
    ypadded[i] = 0;
   }
   for (int i = N; i < N+M; i++) {
    ypadded[i] = y[i - N];
   }
   for (int i = N+M; i < totalsize; i++) {
    ypadded[i] = 0;
   }

   for (int j=0; j < totalsize; j++) {
    // Properly pad the X vector with time shifting.
    // Need to reverse the order of the X vector.
    for (int i=0; i < j; i ++) {
      xpadded[i] = 0;
    }
    for (int i=0; i < N; i ++) {
      xpadded[i+j] = x[N - i];
    }
    for (int i=j+N; i < totalsize; i ++) {
      xpadded[i] = 0;
    }

    conv[j] = dotProduct(xpadded, ypadded, totalsize);
   }
}
 
