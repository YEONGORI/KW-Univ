import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Scanner;

public class Hello3 {
    public static void main(String argsp[]) {
        System.out.println("년도를 입력하세요 :");
        Scanner scanner = new Scanner(System.in);
        int iYear = scanner.nextInt();

        Calendar calendar = new GregorianCalendar(); // use GregorianCalendar class

        for (int a = 0; a < 4; a++) { // To make a 4x3 format, make it 4 spaces long
            for (int i = -1; i < 8; i++) { // status
                for (int j = a * 3; j < a * 3 + 3; j++) { // 3 spaces across
                    calendar.set(iYear, j, 1); // The entered year, selected month, and day are passed as arguments of
                                               // the method.
                    int startDay = calendar.get(Calendar.DAY_OF_WEEK); // startDay is the start day of the month.
                    int totalDay = calendar.getActualMaximum(Calendar.DAY_OF_MONTH); // totalDay is the total number of
                                                                                     // days of the month.
                    drawCalendar(i, j + 1, startDay, totalDay);
                }
                System.out.println();
            }
            System.out.println("");
        }

        scanner.close();
    }

    public static void drawCalendar(int status, int month, int startDay, int totalDay) {
        String tmp[] = { "일", "월", "화", "수", "목", "금", "토" };
        int days;
        switch (status) {
            case -1: // case -1 corresponds to the month of the calendar.
                System.out.printf("%-28s", month + "월");
                break;
            case 0: // case 0 corresponds to the day of the week of the calendar.
                for (int i = 0; i < 7; i++) {
                    System.out.printf("%-3s", tmp[i]);
                }
                if (month % 3 != 0) {
                    System.out.printf("%s", "|");
                }
                break;
            case 1: // case 1 corresponds to the first week of the calendar.
                    // Future cases are the calendar of the week.
                days = 1;
                for (int i = 0; i < 7; i++) {
                    if (startDay < i + 2) {
                        System.out.printf("%4s", days);
                        days++;
                    } else {
                        System.out.printf("%4s", "");
                    }
                }
                break;
            case 2:
                days = 9 - startDay; // From Sunday to Saturday, startDay is expressed from 1 to 7.
                                     // Therefore, we have to do 9-startDay to meet the corresponding date next week.
                for (int i = 0; i < 7; i++) {
                    System.out.printf("%4s", days);
                    days++;
                }
                break;
            case 3:
                days = 16 - startDay;
                for (int i = 0; i < 7; i++) {
                    System.out.printf("%4s", days);
                    days++;
                }
                break;
            case 4:
                days = 23 - startDay;
                for (int i = 0; i < 7; i++) {
                    System.out.printf("%4s", days);
                    days++;
                }
                break;
            case 5:
                days = 30 - startDay;
                for (int i = 0; i < 7; i++) {
                    if (days > totalDay) { // When we reach the maximum number of days of the month, fill in the
                                           // remaining space and exit the switch door.
                        for (; i < 7; i++) {
                            System.out.printf("%4s", "");
                        }
                        break;
                    }
                    System.out.printf("%4s", days);
                    days++;
                }
                break;
            case 6:
                days = 37 - startDay;
                for (int i = 0; i < 7; i++) {
                    if (days > totalDay) {
                        for (; i < 7; i++) {
                            System.out.printf("%4s", "");
                        }
                        break;
                    }
                    System.out.printf("%4s", days);
                    days++;
                }
                break;
            default:
                break;
        }
    }
}