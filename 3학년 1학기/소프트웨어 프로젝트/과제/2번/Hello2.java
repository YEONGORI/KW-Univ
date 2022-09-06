import java.util.Scanner;

public class Hello2 {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        scanner.useDelimiter("\\D"); // Use , as a delimiter

        int iNumberInt[];
        int iNumberCnt, totalLength, maxHeignth;
        String iNumberStr[];
        char mountain[][];

        while (true) {
            System.out.print("input : ");
            String str = scanner.nextLine();
            iNumberStr = str.split(",");
            iNumberInt = new int[iNumberStr.length];

            for (int i = 0; i < iNumberStr.length; i++) { // Parsing to integer array after input to string array
                iNumberInt[i] = Integer.parseInt(iNumberStr[i]);
            }

            iNumberCnt = iNumberStr.length; // Number of iNumber

            if (iNumberInt[0] == 0) {
                break;
            }

            totalLength = getTotalLength(iNumberInt, iNumberCnt); // Find the total length of the mountain.
            maxHeignth = getMaxHeight(iNumberInt, iNumberCnt); // Find the highest height of a mountain

            mountain = new char[totalLength][maxHeignth]; // The mountain picture presented in the question will be
                                                          // rotated 90 degrees to the right to create a mountain with
                                                          // the top of the mountain facing to the right.

            for (int i = 0; i < totalLength; i++) { // Initialize all fields to ' before drawing mountains
                for (int j = 0; j < maxHeignth; j++) {
                    mountain[i][j] = '\'';
                }
            }

            mountain = makeMountain(mountain, iNumberInt, iNumberCnt);

            for (int i = maxHeignth - 1; i >= 0; i--) { // Draw mountains
                for (int j = 0; j < totalLength; j++) {
                    System.out.print(mountain[j][i]);
                }
                System.out.println();
            }
        }

        scanner.close();
    }

    public static int getMaxHeight(int height[], int TotalNumMt) {
        int maxHeignth = 0;

        for (int orderOfMt = 0; orderOfMt < TotalNumMt; orderOfMt++) { // Gets the largest value of the input.
            if (height[orderOfMt] > maxHeignth) {
                maxHeignth = height[orderOfMt];
            }
        }
        maxHeignth += 1; // To distinguish between mountains and input areas

        return maxHeignth;
    }

    public static int getTotalLength(int height[], int totalNumMt) { // The length between the mountains is obtained
                                                                     // by using the difference of height.
        int totalLength = height[0];

        for (int orderOfMt = 0; orderOfMt < totalNumMt; orderOfMt++) {
            if (orderOfMt == totalNumMt - 1) { // When it was the last mountain,
                totalLength += height[orderOfMt] - 1;
                break;
            } else if (height[orderOfMt] > height[orderOfMt + 1]) { // When the height of the mountain in the front is
                                                                    // higher than the mountain in the back mountain,
                totalLength += height[orderOfMt] - height[orderOfMt + 1];
            } else if (height[orderOfMt] == height[orderOfMt + 1]) { // When the height of the mountain in the front and
                                                                     // the mountain in the back is the same
                totalLength += 1;
            } else { // When the height of the mountain in the front is lower than the mountain in
                     // the back
                totalLength += height[orderOfMt + 1] - height[orderOfMt];
            }
        }
        return totalLength;
    }

    public static char[][] makeMountain(char mountain[][], int height[], int TotalNumMt) {
        int start;
        for (start = 0; start < height[0]; start++) { // Draw the top of the first mountain.
            for (int j = 0; j < start + 1; j++) {
                mountain[start][j] = '@';
            }
        }

        for (int orderOfMt = 0; orderOfMt < TotalNumMt; orderOfMt++) {
            if (orderOfMt == TotalNumMt - 1) { // last mountain
                for (int j = 0; j < height[orderOfMt]; j++) {
                    for (int k = 0; k < height[orderOfMt] - j - 1; k++) { // Draw it to the bottom
                        mountain[start][k] = '@';
                    }
                    start++;
                }
                break;
            } else if (height[orderOfMt] > height[orderOfMt + 1]) { // When the mountain in the front is higher than the
                                                                    // mountain in the back
                for (int j = 0; j < height[orderOfMt] - height[orderOfMt + 1]; j++) {
                    for (int k = 0; k < height[orderOfMt] - j - 1; k++) { // It draws to be lower and lower.
                        mountain[start][k] = '@';
                    }
                    start++;
                }
            } else if (height[orderOfMt] == height[orderOfMt + 1]) { // When the height of the mountain in the front and
                                                                     // the mountain in the back is the sames
                for (int k = 0; k < height[orderOfMt]; k++) {
                    mountain[start][k] = '@';
                }
                start++;
            } else {
                for (int j = 0; j < height[orderOfMt + 1] - height[orderOfMt]; j++) { // When the mountain in front is
                                                                                      // lower than the mountain in the
                                                                                      // back
                    for (int k = 0; k < height[orderOfMt] + j + 1; k++) { // It draws higher and higher.
                        mountain[start][k] = '@';
                    }
                    start++;
                }
            }
        }

        return mountain;
    }
}
