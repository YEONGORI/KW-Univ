import java.util.Scanner;

public class Hello {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int iNumbers[] = new int[1000];
        int primeFactors[][][] = new int[1000][2][100];
        int GCD = 1, LCN = 1;

        for (int i = 0; true; i++) {
            System.out.print("\nInput : ");
            iNumbers[i] = scanner.nextInt();
            if (iNumbers[i] == 0) {
                break;
            }

            primeFactorization(primeFactors, iNumbers[i], i); // Space where prime factors and exponents are stored for
                                                              // each input
            GCD = getGCD(primeFactors, i);
            LCN = getLCN(primeFactors, i);

            System.out.print("Input Numbers : ");
            for (int j = -1; j < i; j++) {
                System.out.printf("%d ", iNumbers[j + 1]);
            }

            System.out.printf("\nLCN : %d", LCN);
            System.out.printf("\nGCD : %d", GCD);
        }

        scanner.close();
    }

    public static int[][][] primeFactorization(int primeFactors[][][], int iNumber, int iNumberCnt) { // Prime factorize
                                                                                                      // iNumber and
                                                                                                      // store prime
                                                                                                      // factors and
                                                                                                      // exponents using
                                                                                                      // a
                                                                                                      // three-dimensional
                                                                                                      // array.
        int exponent, cnt = 0; // First factor and exponent

        primeFactors[iNumberCnt][0][cnt] = 1; // Every number has 1 as its prime factor.
        primeFactors[iNumberCnt][1][cnt] = 1;

        for (exponent = 0; iNumber % 2 == 0; exponent++) { // Use 2 to determine how many factors can be factorized
            iNumber /= 2;
        }

        cnt++; // Next factor and exponent
        primeFactors[iNumberCnt][0][cnt] = 2;
        primeFactors[iNumberCnt][1][cnt] = exponent;

        for (int divNumber = 3; iNumber != 1; divNumber += 2) { // Find the prime factor and exponent by adding 3 to 2.
            cnt++;
            for (exponent = 0; iNumber % divNumber == 0; exponent++) { // The factorization ends when the remainder
                                                                       // reaches 1.
                iNumber /= divNumber;
            }
            primeFactors[iNumberCnt][0][cnt] = divNumber; // The number of divisions become factor
            primeFactors[iNumberCnt][1][cnt] = exponent; // and the number of divisions become exp.
        }
        primeFactors[iNumberCnt][0][cnt + 1] = -1; // When the factorization is finished, store -1 indicating the end in
                                                   // the last factor + 1.
        primeFactors[iNumberCnt][1][cnt + 1] = cnt; // And store the total number of factors.

        return primeFactors;
    }

    public static int getGCD(int primeFactors[][][], int iNumberCnt) {
        int GCD = 1, minExponent = 1, cnt = 0;

        for (int k = 0; primeFactors[0][0][k] != -1; k++) { // GCD should have the same factor in all the user's inputs.
                                                            // Therefore, only the element of the first input can be
                                                            // used as a criterion.
            cnt = 0;
            minExponent = primeFactors[0][1][k];
            for (int i = 0; i < iNumberCnt + 1; i++) {
                if (primeFactors[i][1][k] > 0) {
                    if (primeFactors[i][1][k] < minExponent) { // Find the smallest exponent.
                        minExponent = primeFactors[i][1][k];
                    }

                    if (cnt == iNumberCnt) { // If the number of iNumbers and the factor that those numbers have are all
                                             // the same,
                        GCD *= Math.pow(primeFactors[0][0][k], minExponent);
                    }
                    cnt++;
                }
            }
        }
        return GCD;
    }

    public static int getLCN(int primeFactors[][][], int iNumberCnt) { // GET LCN
        int LCN = 1, maxExponent;

        int factorsNum[] = new int[iNumberCnt + 1];
        for (int i = 0; i < iNumberCnt + 1; i++) { // Finds the number of factors of iNumbers
            for (int k = 0; true; k++) {
                if (primeFactors[i][0][k] == -1) {
                    factorsNum[i] = primeFactors[i][1][k];
                    break;
                }
            }
        }

        int maxFactorInputCnt = 0; // The input with the largest prime factor among the inputs
        int tmp = 0;
        for (int i = 0; i < iNumberCnt + 1; i++) { // Find which input has the largest prime factor.
            if (factorsNum[i] > tmp) {
                tmp = factorsNum[i];
                maxFactorInputCnt = i;
            }
        }

        for (int k = 0; primeFactors[maxFactorInputCnt][0][k] != -1; k++) { // Repeat until the end of the array with
                                                                            // the largest number of prime factor
            maxExponent = 0;

            for (int i = 0; i < iNumberCnt + 1; i++) { // Inspect all arrays created by input iNnumber
                if (primeFactors[i][1][k] > 0 && primeFactors[i][0][k] != -1) {
                    if (primeFactors[i][1][k] > maxExponent) { // Find an array with the largest exponenet.
                        maxExponent = primeFactors[i][1][k];
                    }
                }
            }

            LCN *= Math.pow(primeFactors[maxFactorInputCnt][0][k], maxExponent); // Calculate the LCN by multiplying the
                                                                                 // prime factor with the largest index
        }
        return LCN;
    }
}